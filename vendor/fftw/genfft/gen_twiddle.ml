(*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 *)

open Util
open Genutil
open C


type ditdif = DIT | DIF
let ditdif = ref DIT
let usage = "Usage: " ^ Sys.argv.(0) ^ " -n <number> [ -dit | -dif ]"

let urs = ref Stride_variable
let ums = ref Stride_variable

let speclist = [
  "-dit",
  Arg.Unit(fun () -> ditdif := DIT),
  " generate a DIT codelet";

  "-dif",
  Arg.Unit(fun () -> ditdif := DIF),
  " generate a DIF codelet";

  "-with-rs",
  Arg.String(fun x -> urs := arg_to_stride x),
  " specialize for given i/o stride";

  "-with-ms",
  Arg.String(fun x -> ums := arg_to_stride x),
  " specialize for given ms"
]

let generate n =
  let rioarray = "ri"
  and iioarray = "ii"
  and rs = "rs"
  and twarray = "W"
  and m = "m" and mb = "mb" and me = "me" and ms = "ms" in

  let sign = !Genutil.sign 
  and name = !Magic.codelet_name 
  and byvl x = choose_simd x (ctimes (CVar "(2 * VL)", x)) in
  let ename = expand_name name in

  let (bytwiddle, num_twiddles, twdesc) = Twiddle.twiddle_policy 0 false in
  let nt = num_twiddles n in

  let byw = bytwiddle n sign (twiddle_array nt twarray) in

  let vrs = either_stride (!urs) (C.SVar rs) in
  let sms = stride_to_string "ms" !ums in

  let locations = unique_array_c n in
  let iloc = 
    locative_array_c n 
      (C.array_subscript rioarray vrs)
      (C.array_subscript iioarray vrs)
      locations sms
  and oloc = 
    locative_array_c n 
      (C.array_subscript rioarray vrs)
      (C.array_subscript iioarray vrs)
      locations sms
  in
  let liloc = load_array_c n iloc in
  let output =
    match !ditdif with
    | DIT -> array n (Fft.dft sign n (byw liloc))
    | DIF -> array n (byw (Fft.dft sign n liloc))
  in
  let odag = store_array_c n oloc output in
  let annot = standard_optimizer odag in

  let vm = CVar m and vmb = CVar mb and vme = CVar me in

  let body = Block (
    [Decl ("INT", m)],
    [For (list_to_comma
	    [Expr_assign (vm, vmb);
	     Expr_assign (CVar twarray, 
			  CPlus [CVar twarray; 
				 ctimes (vmb, Integer nt)])],
	  Binop (" < ", vm, vme),
	  list_to_comma 
	    [Expr_assign (vm, CPlus [vm; byvl (Integer 1)]);
	     Expr_assign (CVar rioarray, CPlus [CVar rioarray; 
						byvl (CVar sms)]);
	     Expr_assign (CVar iioarray, CPlus [CVar iioarray; 
						byvl (CVar sms)]);
	     Expr_assign (CVar twarray, CPlus [CVar twarray; 
					       byvl (Integer nt)]);
	     make_volatile_stride (CVar rs)
	    ],
	  Asch annot)])
  in

  let tree = 
    Fcn (((if !Magic.standalone then "" else "static ") ^ "void"),
	 ename,
	 [Decl (C.realtypep, rioarray);
	  Decl (C.realtypep, iioarray);
	  Decl (C.constrealtypep, twarray);
	  Decl (C.stridetype, rs);
	  Decl ("INT", mb);
	  Decl ("INT", me);
	  Decl ("INT", ms)],
         add_constants body)
  in
  let twinstr = 
    Printf.sprintf "static const tw_instr twinstr[] = %s;\n\n" 
      (twinstr_to_string "(2 * VL)" (twdesc n))
  and desc = 
    Printf.sprintf
      "static const ct_desc desc = {%d, \"%s\", twinstr, &GENUS, %s, %s, %s, %s};\n\n"
      n name (flops_of tree) 
      (stride_to_solverparm !urs) "0"
      (stride_to_solverparm !ums) 
  and register = 
    match !ditdif with
    | DIT -> "X(kdft_dit_register)"
    | DIF -> "X(kdft_dif_register)"

  in
  let init =
    "\n" ^
    twinstr ^ 
    desc ^
    (declare_register_fcn name) ^
    (Printf.sprintf "{\n%s(p, %s, &desc);\n}" register ename)
  in

  (unparse tree) ^ "\n" ^
    (if !Magic.standalone then "" else init)


let main () =
  begin 
    parse (speclist @ Twiddle.speclist) usage;
    print_string (generate (check_size ()));
  end

let _ = main()
