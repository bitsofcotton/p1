# bitsofcotton/P1
Generic predictor that completely depends on data. This suppose original data have conserved value with the meaning of cdot.

# How to use:
  P1<double> p(40, 20, 2);
  SimpleVector<double> b(40 + 20);
  // ... on b operation.
  p.next(b);

# How to use (command line):
  ./p1 <variable range> <status range> <vanish range> < data.txt
