#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;
#include "p1.hh"
typedef P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > > plin_pt;
typedef P1I<num_t, deltaFeeder<num_t, arctanFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > patan_pt;
typedef shrinkMatrix<num_t, plin_pt>  plin_t;
typedef shrinkMatrix<num_t, patan_pt> patan_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  // N.B. R^8 makes R^9 internal condition but we only need R^7 on the data.
  const auto stat(81);
  const auto var(7);
        int  step(2);
  if(argc < 2)
    std::cerr << "p1 <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with p1 " << step << std::endl;
  assert(1 < step);
  // N.B. we need original and pair-wise to denoise.
  //      we also denoise with arctan scale x-axis and original.
  plin_t  p0(plin_pt( stat, var, step), step);
  plin_t  p1(plin_pt( stat, var, step / 2), step / 2);
  patan_t q0(patan_pt(stat, var, step), step);
  patan_t q1(patan_pt(stat, var, step / 2), step / 2);
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    std::cout << D << ", " << (M = p0.next(d) + p1.next(d) + q0.next(d) + q1.next(d)) << std::endl << std::flush;
  }
  return 0;
}

