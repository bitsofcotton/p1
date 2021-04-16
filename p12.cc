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
  int loop(1);
  if(argc < 4) {
    std::cerr << "p1 <variable> <extra> <ratio>? <loop>?" << std::endl;
    std::cerr << "continue with p1 " << vrange << " " << eslen << " " << ratio << " " << loop << std::endl;
  } else {
    vrange = std::atoi(argv[1]);
    if(2 < argc) eslen = std::atoi(argv[2]);
    if(3 < argc) ratio = std::atoi(argv[3]);
    if(4 < argc) loop  = std::atoi(argv[4]);
  }
  std::vector<P1I<num_t> > p;
  p.resize(loop, P1I<num_t>(eslen, vrange));
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M0(d);
  std::vector<num_t> dd(p.size(), num_t(0));
  auto  rr(dd);
  auto  M(dd);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd0(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd0) {
      if(bd0 != num_t(0) && M0 != num_t(0)) {
        s0 += (d - bd0) - M0;
        s1 += (d - bd0) * M0;
      }
      const auto bd(dd);
      for(int i = 0; i < p.size(); i ++) {
        dd[i] += (d - bd0) * rr[i];
        const auto bf(M[i] * (dd[i] - bd[i]));
        rr[i] += num_t(int(arc4random_uniform(0x10000) + arc4random_uniform(0x10000) - 0x8000 * 2)) / num_t(int(0x8000));
        if(dd[i] != num_t(0))
          M0 += (M[i] = p[i].next(dd[i] - bd[i], ratio)) * bf * rr[i];
      }
      M0 /= num_t(int(p.size()));
      if(! isfinite(M0) || isnan(M0)) M0 = num_t(0);
    }
    std::cout << M0 << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

