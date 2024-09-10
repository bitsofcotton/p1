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
  int stat(80);
  if(argc < 2) std::cerr << argv[0] << " <lines>? : continue with ";
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << stat << std::endl;
  assert(0 < stat);
  idFeeder<SimpleVector<num_t> > feed(abs(stat));
  std::string s;
  SimpleVector<num_t> d;
  auto  M(d);
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
    if(M.size() - 1 == d.size())
      for(int i = 0; i < d.size(); i ++)
        std::cout << d[i] * M[i] << ", ";
    else
      for(int i = 0; i < d.size(); i ++)
        std::cout << "0, ";
    for(int i = 0; i < d.size(); i ++) {
      d[i] += num_t(1);
      d[i] /= num_t(2);
    }
    feed.next(d);
    if(feed.full) {
#define _PREDV_ 3
#if defined(_PNOISE_)
      M = predvq0<num_t, false>(feed.res);
#else
      M = predv<  num_t, false>(feed.res.entity);
#endif
      for(int i = 0; i < M.size(); i ++) {
        M[i] *= num_t(2);
        M[i] -= num_t(1);
      }
    } else {
      M.resize(d.size());
      M.O();
    }
    for(int i = 0; i < M.size() - 1; i ++)
      std::cout << M[i] << ", ";
    std::cout << M[M.size() - 1] << std::endl << std::flush;
  }
  return 0;
}

