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
  int stat(67);
  if(argc < 2) std::cerr << argv[0] << " <lines>? : continue with ";
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << stat << std::endl;
  assert(0 < stat);
#if defined(_MULTI_)
  idFeeder<SimpleVector<num_t> > feed(abs(stat));
#else
  idFeeder<num_t> feed(abs(stat));
#endif
  std::string s;
#if defined(_MULTI_)
  SimpleVector<num_t> d;
#else
  num_t d(int(0));
#endif
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
#if defined(_MULTI_)
    int n(0);
    for(int i = 0; 0 <= i && i < s.size(); i ++)
      if(s[i] == ',') n ++;
    if(! d.size()) {
      d.resize(n + 1);
      d.O();
    }
    for(int i = 0; i < d.size(); i ++) {
      ins >> d[i];
      d[i] += num_t(1);
      d[i] /= num_t(2);
      ins.ignore(s.size(), ',');
    }
    if(M.size() - 1 == d.size())
      for(int i = 0; i < d.size(); i ++)
        std::cout << d[i] * M[i] << ", ";
    else
      for(int i = 0; i < d.size(); i ++)
        std::cout << "0, ";
    feed.next(d);
    if(feed.full) {
      M = predv<num_t>(feed.res.entity).second;
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
#else
    ins >> d;
    std::cout << d * M << ", ";
    std::cout << (M = PP3<num_t>().next(feed.next(d), feed.res.size() / 6)) << std::endl << std::flush;
#endif
  }
  return 0;
}

