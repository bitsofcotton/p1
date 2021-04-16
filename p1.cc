#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

#include "ifloat.hh"
typedef myfloat num_t;
#include "simplelin.hh"
#include "p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int vrange(12);
  int eslen(0);
  int ratio(0);
  if(argc < 3) {
    std::cerr << "p1 <variable> <extra>? <ratio>?" << std::endl;
    std::cerr << "continue with p1 " << vrange << " " << eslen << " " << ratio << std::endl;
  } else {
    vrange = std::atoi(argv[1]);
    if(2 < argc) eslen = std::atoi(argv[2]);
    if(3 < argc) ratio = std::atoi(argv[3]);
  }
  P1I<num_t> p(eslen, vrange);
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
      M = p.next(d - bd, ratio);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

