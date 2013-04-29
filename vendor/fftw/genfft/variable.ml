(*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 *)

type variable = 
      (* temporary variables generated automatically *)
  | Temporary of int
      (* memory locations, e.g., array elements *)
  | Locative of (Unique.unique * Unique.unique *
		   (int -> string) * int * string)
      (* constant values, e.g., twiddle factors *)
  | Constant of (Unique.unique * string)

let hash v = Hashtbl.hash v

let same a b = (a == b)

let is_constant = function
  | Constant _ -> true
  | _ -> false

let is_temporary = function
  | Temporary _ -> true
  | _ -> false

let is_locative = function
  | Locative _ -> true
  | _ -> false

let same_location a b = 
  match (a, b) with
  | (Locative (location_a, _, _, _, _), Locative (location_b, _, _, _, _)) ->
      Unique.same location_a location_b
  | _ -> false

let same_class a b = 
  match (a, b) with
  | (Locative (_, class_a, _, _, _), Locative (_, class_b, _, _, _)) ->
      Unique.same class_a class_b
  | (Constant (class_a, _), Constant (class_b, _)) ->
      Unique.same class_a class_b
  | _ -> false

let make_temporary =
  let tmp_count = ref 0
  in fun () -> begin
    tmp_count := !tmp_count + 1;
    Temporary !tmp_count
  end

let make_constant class_token name = 
  Constant (class_token, name)

let make_locative location_token class_token name i vs =
  Locative (location_token, class_token, name, i, vs)

let vstride_of_locative = function
  | Locative (_, _, _, _, vs) -> vs
  | _ -> failwith "vstride_of_locative"

(* special naming conventions for variables *)
let rec base62_of_int k = 
  let x = k mod 62 
  and y = k / 62 in
  let c = 
    if x < 10 then 
      Char.chr (x + Char.code '0')
    else if x < 36 then
      Char.chr (x + Char.code 'a' - 10)
    else 
      Char.chr (x + Char.code 'A' - 36)
  in
  let s = String.make 1 c in
  let r = if y == 0 then "" else base62_of_int y in
  r ^ s

let varname_of_int k =
  if !Magic.compact then
    base62_of_int k
  else
    string_of_int k

let unparse = function
  | Temporary k -> "T" ^ (varname_of_int k)
  | Constant (_, name) -> name
  | Locative (_, _, name, i, _) -> name i

let unparse_for_alignment m = function
  | Locative (_, _, name, i, _) -> name (i mod m)
  | _ -> failwith "unparse_for_alignment"

