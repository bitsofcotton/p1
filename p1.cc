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

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  const auto stat(144);
  const auto var(10);
        int  step(1);
  if(argc < 2)
    std::cerr << "p1 <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with p1 " << step << std::endl;
  shrinkMatrix<num_t, P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > > > p(P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > >(stat, var, abs(step)), abs(step));
  shrinkMatrix<num_t, P1I<num_t, arctanFeeder<num_t, idFeeder<num_t> > > > q(P1I<num_t, arctanFeeder<num_t, idFeeder<num_t> > >(stat, var, abs(step)), abs(step));
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    std::cout << D << ", " << (M = step < 0 ? q.next(d) : p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

