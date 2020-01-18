# bitsofcotton/P1
Generic predictor that completely depends on data. This suppose original data have conserved value with the meaning of cdot.  
This is the better hypothesis because any taylor seriies can described as cdot, and, recursive predictions are also be in taylor series, and, orthogonal variable x and y, their taylor series are in same meaning.

# How to use:
    P1<double> p(40, 20, 2);
    SimpleVector<double> b(40 + 20);
    // ... on b operation.
    pred = p.next(b);
    ...

# How to use (command line):
    ./p1 <variable range> <status range> <vanish range> < data.txt
