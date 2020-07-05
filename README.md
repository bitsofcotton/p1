# bitsofcotton/p1
Generic predictor that completely depends on data itself but doesn't win good randoms. This suppose original data have conserved value with the meaning of inner product.  

# How to use:
    P1<double> p(40, 20);
    SimpleVector<double> b(40 + 20);
    ...
    pred = p.next(b);
    ...
    // or we can use:
    P1B<double> p(40, 20);
    ...
    xnext = p.next(x);
    ...

# How to use (command line):
    ./p1 <variable range> <status range> < data.txt

# Tips
If P1 class lasterr has larger absolute value than minimum change, this is useless for the problem nor unreliable for them.
If the status length is not enough, edge clear change will come with suddenly. This is observable by each P1::fvec cosine value.  

