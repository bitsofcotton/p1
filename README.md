# bitsofcotton/p1
Eliminate invariant structure from given series if argument is proper and
input series is deterministic with or without inner status.

# Contexts
There exists toeplitz matrix and their solver faster algorithms,
so this is extension to them.  

For another meaning of this in randtools generic tips 6 ~ 9 that
excludes complexity into accuracy on inner product,
invariantP1 function returns invariant structure that \[- &alpha;, &alpha;\[
register computer with whole input and whole deterministic computed output
has on the enough variable dimension whether if status dimension is or isn't.

N.B. if the function has inner status variable that to be projected into
series, with proper calculated invariant arguments, \<a,x\>+\<b,y\>==\<a,x\>==0
which x is shown variable, y is inner status bits, we can collect
Xa=B\*y\_0, this is equivalent to with large enough X',
X'a'=\[B\*y O\], y=some X''\*a.
So this is calculate with larger variable dimension.

If we predict one of these by not enough status length, then, re-predict with
some skipped input of them, some recursion makes it better result.
This is because x+:=\[A_0,...,A_n\]x, with first predict, x+\_p=Bx,
then, next skipped prediction, we predict x+\_skip:=(\[A_0,...,A_n\]-\[B,O,...,O\])x
if we are lucky, x+\_skip=(\[O,A_1,...,A_n\]x, so we predict: x+\_skip\_p=Bx, the data
remains is the data another status bits, so recursive of them, cut some invariant.
But in fact, the result we have is unstable if original status bits is too small because of splitted status causes no use what we calculate into status bits (rank shrink on everywhere).

# Tips:
There exists trivial invariant that if((for all k, x_k==a_k) or ...) return 1; program. This is also described as det diag X x with large enough X, this concludes &lt;a, tan(x)x&gt;\*(tan(x_0)\*...\*tan(x_n))^m (some m) for the program. But in some case, this condition cannot be satisfised with rank A isn't full, but with this case, we can reduce them with ||Ax-1\*some x'|| -&gt; min.

# How to use:
    P1I<double> p(/* status length */, /* variable dimension */);,
    ...
      residue = p.next(/* value */, /* complexity */);
    // Or we can use:
    const auto invariant(linearInvariant<T>(
      std::vector<SimpleVector<T> >(/* some initialized with normalized*/));

# How to use (command line):
    ./p1 <variable> <extra>? <ratio>? < data.txt
    # ratio < 0 for plain linear, ratio == 0 for linear,
    # 0 < ratio for nonlinear, ratio depends program complexity itself.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bug reports, will no change.

