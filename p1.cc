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
  int  stat(49);
  if(argc < 2)
    std::cerr << "p1 <condition>?" << std::endl;
  if(1 < argc) stat = std::atoi(argv[1]);
  stat = max(min(stat, int(49)), - int(49));
  const auto var(min(8, max(2, int(sqrt(num_t(abs(int(stat))))))));
  std::cerr << "continue with p1 " << stat << std::endl;
  P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat), var);
  P1I<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat), var);
  std::string s;
  num_t d(0);
  auto  D(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D  = d * M;
    M = stat < 0 ? q.next(d) : p.next(d);
    std::cout << D << ", " << M << ", " << d << std::endl << std::flush;
  }
  return 0;
}

