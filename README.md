# bitsofcotton/p1
Eliminate invariant structure from given series.
But residue might also have a different invariant structure.

# Contexts
There exists toeplitz matrix and their solver faster algorithms,
so this is extension to them.
For another meaning of this in randtools generic tips 6 that
excludes complexity into accuracy on inner product,
invariantP1 function returns invariant structure that \[0, &alpha;\[ register
computer with whole input and whole deterministic computed output
has on the variable dimension if status dimension is enough.

# How to use:
    P1<double> p(/* status length */, /* variable dimension */);
    ...
    residue = p.next(/* value */, /* condition maximum skip number */);
    // Or we can use:
    ...
    const auto invariant(invariantP1<T>(SimpleVector<T>(/* some initialized */,
      /* variable dimension */, /* condition maximum skip number */));

# How to use (command line):
    ./p1 <status range> <variable range> <maximum skip> < data.txt
    # subtract invariant structure from input number series, then output.
    # status   range < 0 for atan(input) prediction subtraction.
    # variable range < 0 for atan(delta) prediction subtraction.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bug reports, will no change.

