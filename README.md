# bitsofcotton/p1
Eliminate invariant structure from given series if argument is proper and
the series is deterministic.

# Contexts
There exists toeplitz matrix and their solver faster algorithms,
so this is extension to them.  
For another meaning of this in randtools generic tips 6 that
excludes complexity into accuracy on inner product,
invariantP1 function returns invariant structure that \[0, &alpha;\[ register
computer with whole input and whole deterministic computed output
has on the variable dimension if status dimension is enough.
We can weaken this variable dimension condition to status dimension and
guard length, this is guaranteed with randtools general tips a and
lagrange multipliers.  
And, if the function has inner status variable that to be projected into
series, the fixed point on the series with status variable dimension
is important.

# How to use:
    P1<double> p(/* status length */, /* variable dimension */);
    ...
    residue = p.next(/* value */, /* condition maximum skip number */,
      /* middle guard status length that ignored */);
    // Or we can use:
    ...
    const auto invariant(invariantP1<T>(SimpleVector<T>(/* some initialized */,
      /* variable dimension */, /* condition maximum skip number */,
      /* middle guard condition skip number */));

# How to use (command line):
    ./p1 <status range> <variable range> <maximum skip> <guard length> < data.txt
    # subtract invariant structure from input number series, then output.
    # status   range < 0 for atan(input) prediction subtraction.
    # variable range < 0 for atan(delta) prediction subtraction.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bug reports, will no change.

