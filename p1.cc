#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

#include "lieonn.hh"
typedef myfloat num_t;
#include "p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int stat(80);
  int var(2);
  int comp(2);
  if(argc < 2)
    std::cerr << "p1 <condition>? <context>? <complement>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = comp = std::atoi(argv[2]);
    if(3 < argc) comp = std::atoi(argv[3]);
  }
  std::cerr << "continue with p1 " << stat << " " << var << " " << comp << std::endl;
  P1I<num_t, false> p(abs(stat), var, comp);
  P1I<num_t, true>  q(abs(stat), var, comp);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        s0 += (d - bd) - M;
        s1 += (d - bd) * M;
      }
      M = (stat < 0 ? p.next(d) : q.next(d));
      if(M != num_t(0)) M -= d;
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

