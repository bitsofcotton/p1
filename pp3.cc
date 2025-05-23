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
  int stat(0);
  if(argc < 2) std::cerr << argv[0] << " <lines>? : continue with ";
  if(1 < argc && argv[1][0] != 'd')
    std::cerr << argv[0] << " " << (stat = std::atoi(argv[1])) << std::endl;
  else if(argc <= 1)
    std::cerr << argv[0] << " " << stat << std::endl;
  else
    std::cerr << argv[0] << " d" << std::endl;
  assert(0 <= stat);
  idFeeder<SimpleVector<num_t> > feed(stat);
  std::string s;
  SimpleVector<num_t> d;
  auto M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
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
    feed.next(offsetHalf<num_t>(d));
    if((stat && feed.full) || (! stat && 9 < feed.res.entity.size()) ) {
      // N.B. exhaust of the resource, so we expect the chain pp3n | p0 .
      M = 1 < argc && argv[1][0] == 'd' ?
        unOffsetHalf<num_t>(predv0<num_t, 0, PPcultivatedDeep<num_t> >(
          feed.res.entity, feed.res.entity.size() )) :
        unOffsetHalf<num_t>(predv0<num_t, 0, PP<num_t> >(
          feed.res.entity, feed.res.entity.size() ));
      if(M.size()) {
        for(int i = 0; i < M.size() - 1; i ++)
          std::cout << M[i] << ", ";
        std::cout << M[M.size() - 1] << std::endl << std::flush;
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

