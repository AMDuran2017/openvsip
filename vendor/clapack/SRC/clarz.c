#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int clarz_(char *side, integer *m, integer *n, integer *l, 
	complex *v, integer *incv, complex *tau, complex *c__, integer *ldc, 
	complex *work)
{
/*  -- LAPACK routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    CLARZ applies a complex elementary reflector H to a complex   
    M-by-N matrix C, from either the left or the right. H is represented   
    in the form   

          H = I - tau * v * v'   

    where tau is a complex scalar and v is a complex vector.   

    If tau = 0, then H is taken to be the unit matrix.   

    To apply H' (the conjugate transpose of H), supply conjg(tau) instead   
    tau.   

    H is a product of k elementary reflectors as returned by CTZRZF.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': form  H * C   
            = 'R': form  C * H   

    M       (input) INTEGER   
            The number of rows of the matrix C.   

    N       (input) INTEGER   
            The number of columns of the matrix C.   

    L       (input) INTEGER   
            The number of entries of the vector V containing   
            the meaningful part of the Householder vectors.   
            If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0.   

    V       (input) COMPLEX array, dimension (1+(L-1)*abs(INCV))   
            The vector v in the representation of H as returned by   
            CTZRZF. V is not used if TAU = 0.   

    INCV    (input) INTEGER   
            The increment between elements of v. INCV <> 0.   

    TAU     (input) COMPLEX   
            The value tau in the representation of H.   

    C       (input/output) COMPLEX array, dimension (LDC,N)   
            On entry, the M-by-N matrix C.   
            On exit, C is overwritten by the matrix H * C if SIDE = 'L',   
            or C * H if SIDE = 'R'.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace) COMPLEX array, dimension   
                           (N) if SIDE = 'L'   
                        or (M) if SIDE = 'R'   

    Further Details   
    ===============   

    Based on contributions by   
      A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA   

    =====================================================================   


       Parameter adjustments */
    /* Table of constant values */
    static complex c_b1 = {1.f,0.f};
    static integer c__1 = 1;
    
    /* System generated locals */
    integer c_dim1, c_offset;
    complex q__1;
    /* Local variables */
    extern /* Subroutine */ int cgerc_(integer *, integer *, complex *, 
	    complex *, integer *, complex *, integer *, complex *, integer *),
	     cgemv_(char *, integer *, integer *, complex *, complex *, 
	    integer *, complex *, integer *, complex *, complex *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int cgeru_(integer *, integer *, complex *, 
	    complex *, integer *, complex *, integer *, complex *, integer *),
	     ccopy_(integer *, complex *, integer *, complex *, integer *), 
	    caxpy_(integer *, complex *, complex *, integer *, complex *, 
	    integer *), clacgv_(integer *, complex *, integer *);
#define c___subscr(a_1,a_2) (a_2)*c_dim1 + a_1
#define c___ref(a_1,a_2) c__[c___subscr(a_1,a_2)]


    --v;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    if (lsame_(side, "L")) {

/*        Form  H * C */

	if (tau->r != 0.f || tau->i != 0.f) {

/*           w( 1:n ) = conjg( C( 1, 1:n ) ) */

	    ccopy_(n, &c__[c_offset], ldc, &work[1], &c__1);
	    clacgv_(n, &work[1], &c__1);

/*           w( 1:n ) = conjg( w( 1:n ) + C( m-l+1:m, 1:n )' * v( 1:l ) ) */

	    cgemv_("Conjugate transpose", l, n, &c_b1, &c___ref(*m - *l + 1, 
		    1), ldc, &v[1], incv, &c_b1, &work[1], &c__1);
	    clacgv_(n, &work[1], &c__1);

/*           C( 1, 1:n ) = C( 1, 1:n ) - tau * w( 1:n ) */

	    q__1.r = -tau->r, q__1.i = -tau->i;
	    caxpy_(n, &q__1, &work[1], &c__1, &c__[c_offset], ldc);

/*           C( m-l+1:m, 1:n ) = C( m-l+1:m, 1:n ) - ...   
                                 tau * v( 1:l ) * conjg( w( 1:n )' ) */

	    q__1.r = -tau->r, q__1.i = -tau->i;
	    cgeru_(l, n, &q__1, &v[1], incv, &work[1], &c__1, &c___ref(*m - *
		    l + 1, 1), ldc);
	}

    } else {

/*        Form  C * H */

	if (tau->r != 0.f || tau->i != 0.f) {

/*           w( 1:m ) = C( 1:m, 1 ) */

	    ccopy_(m, &c__[c_offset], &c__1, &work[1], &c__1);

/*           w( 1:m ) = w( 1:m ) + C( 1:m, n-l+1:n, 1:n ) * v( 1:l ) */

	    cgemv_("No transpose", m, l, &c_b1, &c___ref(1, *n - *l + 1), ldc,
		     &v[1], incv, &c_b1, &work[1], &c__1);

/*           C( 1:m, 1 ) = C( 1:m, 1 ) - tau * w( 1:m ) */

	    q__1.r = -tau->r, q__1.i = -tau->i;
	    caxpy_(m, &q__1, &work[1], &c__1, &c__[c_offset], &c__1);

/*           C( 1:m, n-l+1:n ) = C( 1:m, n-l+1:n ) - ...   
                                 tau * w( 1:m ) * v( 1:l )' */

	    q__1.r = -tau->r, q__1.i = -tau->i;
	    cgerc_(m, l, &q__1, &work[1], &c__1, &v[1], incv, &c___ref(1, *n 
		    - *l + 1), ldc);

	}

    }

    return 0;

/*     End of CLARZ */

} /* clarz_ */

#undef c___ref
#undef c___subscr


