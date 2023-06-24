# bitsofcotton/p1
Generic predictor on expectation value strongly depends on data itself.

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
There exists trivial invariant that if((for all k, x_k==a_k) or ...) return 1; program. This is also described as det diag X x with large enough X, this concludes &lt;a, x&gt; \* (x_0 ... x_n)^m (some m) + b for the program. But in some case, this condition cannot be satisfised with rank A isn't full, but with this case, we can reduce them with ||Ax-1\*some x'|| -&gt; min.

# General Tips:
We also get the result to make periods, this is because periodical data input causes mod n program, but this makes if ... status number == program.

# How to use:
    P1I<double, /* feeder */> p(/* status */, /* variable */);
    ...
      residue = p.next(/* value */);

# How to use (command line):
    ./p1 <status>? < data.txt
    # 0 <  status for plain fixed size prediction on expectation value.
    # 0 == status for return to average.
    # 1 == status for copycat one step before.

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

