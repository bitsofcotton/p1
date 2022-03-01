#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;
#include "p1.hh"
typedef P1I<num_t, idFeeder<num_t> > plin_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  const auto stat(3 * 3);
  const auto var(3);
        int  step(1);
  if(argc < 2)
    std::cerr << argv[0] << " <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with " << argv[0] << " " << step << std::endl;
  shrinkMatrix<num_t, plin_t> p;
  plin_t q;
  if(step < 0) q = plin_t(max(abs(step) + int(3), (step - 1) * (step - 1)), abs(step));
  else p = shrinkMatrix<num_t, plin_t>(plin_t(stat * (step + 1), var, step), step);
  std::string s;
  num_t d(0);
  auto  M(d);
  auto  Mx(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    if(Mx < abs(d)) Mx = abs(d) * num_t(int(2));
    std::cout << D << ", " << (M = max(- Mx, min(Mx, step < 0 ? q.next(d) : p.next(d))) / (Mx != num_t(int(0)) ? Mx : num_t(int(1)))) << std::endl << std::flush;
  }
  return 0;
}

