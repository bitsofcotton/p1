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

We can weaken this variable dimension condition to
guard length, this is guaranteed with randtools general tips a and
lagrange multipliers.  


# How to use:
    P1I<double> p(/* status length */, /* variable dimension */,
      /* inner status length */, /* middle guard status length */);
    ...
      residue = p.next(/* value */, /* condition maximum skip number */);
    //     p have: invariant_(abs|sgn), s_(buf|sbuf) vectors.
    // Or we can use:
    const auto invariant(invariantP1<T>(SimpleVector<T>(/* some initialized */,
      /* variable dimension */, /* condition maximum skip number */,
      /* middle guard condition skip number */));

# How to use (command line):
    ./p1 <extra> <variable> <guard> <ignore> < data.txt
    # subtract invariant structure from input number series, then output.
    # extra    < 0 for atan(input) prediction subtraction.
    # variable < 0 for atan(delta) prediction subtraction.
    # ignore   < 0 for average prediction subtraction with average invariant.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bug reports, will no change.

