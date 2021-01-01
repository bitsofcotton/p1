# bitsofcotton/p1
Generic predictor that completely depends on data itself but doesn't win good randoms.  
This suppose original data have conserved value with the meaning of inner product.  

# Contexts
There exists toeplitz matrix and their solver faster algorithms, so this is extension of them.

# How to use:
    P1<double> p(40, 20);
    SimpleVector<double> b(40 + 20);
    ...
    pred = p.next(b);
    // Or we can use:
    P1B<double> p(40, 20);
    ...
    xnext = p.next(x);

# How to use (command line):
    ./p1 <variable range> <status range> < data.txt

# Tips
If P1 class lasterr has larger absolute value than minimum change, this is useless for the problem nor unreliable for them.
If the status length is not enough, edge clear change will come with suddenly. This is observable by each P1::fvec cosine value.  

# General Tips
If original series is consisted with x_2:=Integrate^x_1 f(x), this prediction is valid. So in random walk case, this seems to be valid operations. (But infact, this with specific condition is ok.)

# Known bug
This don't fixes Ax<=b+1&epsilon; case, so b+1&epsilon;<=Ax case would be gained. When so, with -Ax<=-b-1&epsilon; condition, x will be also a result because Ax<=b also means -Ax<=-b in this condition.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bug reports, will no change.
