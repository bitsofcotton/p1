# bitsofcotton/p1
Generic predictor that completely depends on data itself but doesn't win good randoms. This suppose original data have conserved value with the meaning of inner product.  
This is the better hypothesis because any taylor series can described as inner product, and, recursive predictions are also be in taylor series, lagrange multiplier, and, orthogonal variable x and y, their taylor series are in them with same meaning (which converges). And, if there's a triangular series like wavelet transform like fourier transform, and, their linear operations, also they are in this form.

# How to use:
    P1<double> p(40, 20);
    SimpleVector<double> b(40 + 20);
    // ... on b operation.
    pred = p.next(b);
    ...

# How to use (command line):
    ./p1 <variable range> <status range> < data.txt
