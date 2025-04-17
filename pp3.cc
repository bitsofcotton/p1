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
#include <stdint.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int step(1);
  int stat(0);
  if(argc < 2) std::cerr << argv[0] << " <step>? <lines>? : continue with ";
  if(1 < argc) step = std::atoi(argv[1]);
  if(2 < argc) stat = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << step << " " << stat << std::endl;
  assert(0 < step && 0 <= stat);
  idFeeder<SimpleVector<num_t> > feed(stat);
  idFeeder<SimpleVector<num_t> > f(step);
  std::string s;
  SimpleVector<num_t> d;
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    const auto& M(f.res[0]);
    int n(0);
    for(int i = 0; 0 <= i && i < s.size(); i ++)
      if(s[i] == ',') n ++;
    if(! d.size()) {
      d.resize(n + 1);
      d.O();
    }
    for(int i = 0; i < d.size(); i ++) {
      ins >> d[i];
      ins.ignore(s.size(), ',');
    }
    if(d.size() <= M.size())
      for(int i = 0; i < d.size(); i ++)
#if defined(_CHAIN_)
        std::cout << d[i] - M[i] << ", ";
#else
        std::cout << d[i] * M[i] << ", ";
#endif
    else
      for(int i = 0; i < d.size(); i ++)
        std::cout << num_t(int(0)) << ", ";
    for(int i = 0; i < d.size(); i ++) {
      d[i] += num_t(1);
      d[i] /= num_t(2);
    }
    feed.next(d);
    if((stat && feed.full) || (! stat && 9 < feed.res.entity.size()) ) {
      // N.B. exhaust of the resource, so we expect the chain pp3n | p0 .
      f.next(predv0<num_t, 0>(feed.res.entity, string(""), feed.res.entity.size(), step));
      for(int i = 0; i < f.res[f.res.size() - 1].size(); i ++) {
        f.res[f.res.size() - 1][i] *= num_t(2);
        f.res[f.res.size() - 1][i] -= num_t(1);
      }
      if(f.res[f.res.size() - 1].size()) {
        for(int i = 0; i < f.res[f.res.size() - 1].size() - 1; i ++)
          std::cout << f.res[f.res.size() - 1][i] << ", ";
        std::cout << f.res[f.res.size() - 1][f.res[f.res.size() - 1].size() - 1] << std::endl << std::flush;
      } else {
        for(int i = 0; i < d.size() - 1; i ++)
          std::cout << num_t(int(0)) << ", ";
        std::cout << num_t(int(0)) << std::endl << std::flush;
      }
    } else {
      for(int i = 0; i < d.size(); i ++)
        std::cout << num_t(int(0)) << ", ";
      std::cout << std::endl << std::flush;
    }
  }
  return 0;
}

