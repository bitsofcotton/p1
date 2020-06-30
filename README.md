# bitsofcotton/p1
Generic predictor that completely depends on data itself but doesn't win good randoms. This suppose original data have conserved value with the meaning of inner product.  
This is the better hypothesis because any taylor series can be described as a inner product, and, recursive predictions are also be in taylor series, lagrange multiplier, and, orthogonal variable x and y, their taylor series are in them with same meaning (which converges). And, if there's a triangular series like wavelet transform like fourier transform, and, their linear operations, also they are in this form. And, if the original stream is uncontinuous at all, it relates {(-1)^k} stream multiplication with subtracting cont. . It trivialy in this form. And, some strategic copycats are also in this form.

# How to use:
    P1<double> p(40, 20);
    SimpleVector<double> b(40 + 20);
    // ... on b operation.
    pred = p.next(b);
    ...

# How to use (command line):
    ./p1 <variable range> <status range> <vanish> < data.txt

# Tips
If P1 class lasterr has larger absolute value than minimum change, this is useless for the problem nor unreliable for them.
If the status length is not enough, edge clear change will come with suddenly. This is observable by each P1::fvec cosine value.  
And, if the status length is enough, vanish can be used to drill the conserved value, otherwise, edge clear catastrophy can destroy the advantage.

