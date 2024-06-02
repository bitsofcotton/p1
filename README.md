# bitsofcotton/p1
Generic predictor on \[- alpha, alpha\[-register consisted one function computed streams (up to aleph_0).

# Contexts
There exists toeplitz matrix and their solver faster algorithms,
so this is extension to them.  

For another meaning of this in randtools generic tips 6 ~ 9, D that
excludes complexity into accuracy on inner product,
P1I class returns invariant structure that \[- &alpha;, &alpha;\[
register computer with whole input and whole deterministic computed output
has on the enough variable dimension whether if status dimension is or isn't.

N.B. if the function has inner status variable that to be projected into
series, with proper calculated invariant arguments, \<a,x\>+\<b,y\>==\<a,x\>==0
which x is shown variable, y is inner status bits, we can collect
Xa=B\*y\_0, this is equivalent to with large enough X',
X'a'=\[B\*y O\], y=some X''\*a.
So this is calculate with larger variable dimension.

And if we need enough accuracy on full rank, with converting dimension into accuracy on
the computer reigister, status should be vanished.

If we predict one of these by not enough status length, then, re-predict with
some skipped input of them, some recursion makes it better result.
This is because x+:=\[A_0,...,A_n\]x, with first predict, x+\_p=Bx,
then, next skipped prediction, we predict x+\_skip:=(\[A_0,...,A_n\]-\[B,O,...,O\])x
if we are lucky, x+\_skip=(\[O,A_1,...,A_n\]x, so we predict: x+\_skip\_p=Bx, the data
remains is the data another status bits, so recursive of them, cut some invariant.
But in fact, the result we have is unstable if original status bits is too small because of splitted status causes no use what we calculate into status bits (rank shrink on everywhere).

# Tips:
There exists trivial invariant that if((for all k, x_k==a_k) or ...) return 1; program. This is also described as det diag X x with large enough X, this concludes tan(&lt;a, \[1, x\]&gt; \* (1 x_0 ... x_n)^m) (some m) for the program. But in some case, this condition cannot be satisfised with rank A isn't full, but with this case, we can reduce them with ||Ax-1\*some x'|| -&gt; min.

However, the worst case of right side minimum is max rank case. So we might always get some of the one function by giving some input streams.

# General Tips:
We also get the result to make periods, this is because periodical data input causes mod n program, but this makes if ... status number == program.

# How to use:
    PBond<double, P01<double> > q(P01<double>(/* variable */), /* status */);
    ...
      residue = q.next(/* value */);

# How to use (command line):
    ./p1 <status>? < data.txt
    # -1 > status for return to range average.
    # -1 == status for return to average but weight heavy to heavy.
    # 0 == status for return to average.
    # 1 == status for copycat one step before.
    # 1 <  status for P1I prediction.

# Tips
If we heavy tune original input with P1 alternative, we get the form:

tan(A\[x, y, z, 1\])==x, tan(A^k\[x, y, z, 1\])==x^(+k \* A.rows)

So if we can find some better step to step in or only we average input:

tan\<a, \[x, y, z, 1\]\> == x, tan\<a^2, \[x, y, z, 1\]\> == x+.

So this concludes: x0 == tan\<a, \[x_-4, x_-3, x_-2, x_-1\]\> structures on some of the step or some average on input.

So in fact, we must get average of input to predict with, but this isn't.

Either, we get with this: a in R^n, a^k definition on tan\<a,x\> meaning.

# Bug
We want to take plain makeProgramInvariant revert invariant.
However, we use invariant on R^n instead of them.

The difference between the randtools description and this p1 implementation is:

-1 &leq; Ax &leq; 1 vs. -1 &leq; Ax + \[..., m_k, ...\] &leq; 1 which m_k in Z.

This is to make x in \[0,1\]^n, Ax in Z^n', ||Ax + m|| -&gt; epsilon with finite accuracy A.
In ideal, large ||x||, ||m|| causes ||Ax + m|| -&gt; epsilon because m=-Ax exists on such accuracy.
In randtools, we can adjust \[0,1\] to \[0,alpha\] input range with having some period, so the condition satisfies in such case.

To make such condition valid, our p1 implementation causes: ||Ax|| -&gt; |some alpha| on geometric average meaning, however, this isn't directly guarantees to satisfy the ||x|| : ||m|| condition.

In opposite side, ||Px'|| -&gt; |alpha|, |alpha| &leq;&leq; 1/sqrt(min(P.rows(), P.cols())) : const., this isn't optimal upper bound.
So ||x|| := 1 optimization causes to have complexity depend upper bound they have constant upper bound on the taken invariant result.
Also, the calculation itself has upper bound on complexity floating point accuracy, so if former one vs. latter one has a better result, we can take they're a hard tuned one.

The dimension limit in this method saturate to take invariant is: .5 (.5y)^2 &leq; .5 x log_2 x, this region is somewhere 1 \< x and |y| \< 2/sqrt(log(2)) sqrt(x log(x)), where y is variable number in calculation with a single bit per each variable, x is P.rows, so when this condition satisfies, there exists hard tuned layer per each, (vector per each)?. Lower bound of |y| is 3 in this context.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Real close
2023/02/28
2023/03/09 bug fix after close #1
2023/03/13 integrate all files into lieonn.hh after close #2
2023/03/24 code clean, after close #3.
2023/03/31 merge prand.
2023/04/02 merge catg fix.
2023/04/03 merge.
2023/04/05 fix makeProgramInvariant scale accuracy stability.
2023/04/21 make/revert ProgramInvariant algorithm change.
2023/06/24 fix to avoid observation matters.
2023/07/07 update the .cc comment.
2023/07/08 invariant cause +1, ok.
2023/10/30 update readme. copy structure reliably with randtools meaning.
2024/03/25 P1I to P01 change.
2024/04/09 add some of the tips.
2024/04/18 update readme.
2024/05/06 bitsofcotton/p0:p0.cc argv\[1\]\<0 case integrated into p1.cc.
2024/05/31 compile jammer.
2024/06/01 fix JAM.
2024/06/02 JAM into p2/cr.py.

