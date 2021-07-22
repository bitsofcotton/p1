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
  int  var(3);
  bool whole(false);
  if(argc < 2)
    std::cerr << "p1 <condition>? <var>? <whole|partial>?" << std::endl;
  else {
    if(1 < argc) stat  = std::atoi(argv[1]);
    if(2 < argc) var   = std::atoi(argv[2]);
    if(3 < argc) whole = argv[3][0] == 'w';
  }
  std::cerr << "continue with p1 " << stat << " " << var << " " << (const char*)(whole ? "whole" : "partial") << std::endl;
  P1I<num_t, linearFeeder<num_t> > p(stat, var);
  P1I<num_t, arctanFeeder<num_t, true> > q(stat, var);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    if(d != num_t(0)) {
      if(M != num_t(0)) {
        s0 += (s3 = d - M);
        s1 += (s2 = M / d);
      }
      M = tan(stat < 0 ? p.next(atan(d)) : q.next(atan(d)) );
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << ", " << s2 << ", " << s3 << std::endl << std::flush;
  }
  return 0;
}

