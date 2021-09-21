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
  // N.B. R^8 with index, we use const. twice, R^7 is at last.
  const auto stat(49);
  const auto var(5);
        int  step(1);
  if(argc < 2)
    std::cerr << "p1 <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with p1 " << step << std::endl;
  P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat) + abs(step), var, abs(step));
  P1I<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat) + abs(step), var, abs(step));
  std::string s;
  num_t d(0);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (step < 0 ? q.next(d) : p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

