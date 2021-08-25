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
  int  stat(80);
  int  var(2);
  if(argc < 2)
    std::cerr << "p1 <condition>? <var>? <pow>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = std::atoi(argv[2]);
  }
  std::cerr << "continue with p1 " << stat << " " << var << std::endl;
  P1I<num_t, linearFeeder<num_t, sumFeeder<num_t> > > p(abs(stat), var);
  P1I<num_t, arctanFeeder<num_t, sumFeeder<num_t> > > q(abs(stat), var);
  std::string s;
  num_t d(0);
  auto  M(d);
  auto  D(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D = d * M;
    M = stat < 0 ? q.next(d) : p.next(d);
    std::cout << D << ", " << M << std::endl << std::flush;
  }
  return 0;
}

