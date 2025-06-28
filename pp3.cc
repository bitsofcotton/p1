#if !defined(_ONEBINARY_)
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
#define _COMPILE_PRED_
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
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << stat << std::endl;
  std::string s;
# if defined(_CHAIN_)
  const bool chain(true);
# else
  const bool chain(false);
# endif
#endif
  assert(0 <= stat);
  idFeeder<SimpleVector<num_t> > feed(stat);
  SimpleVector<num_t> d;
  SimpleVector<num_t> M(d);
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
        std::cout << (chain ? d[i] - M[i] : d[i] * M[i]) << ", ";
    else
      for(int i = 0; i < d.size(); i ++)
        std::cout << num_t(int(0)) << ", ";
    feed.next(offsetHalf<num_t>(d));
    if((stat && feed.full) || (! stat && 9 < feed.res.entity.size()) ) {
      // N.B. exhaust of the resource, so we expect the chain pp3n | p0 .
      M = unOffsetHalf<num_t>(predv0<num_t, 0>(feed.res.entity,
            feed.res.entity.size() ) );
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
#if !defined(_ONEBINARY_)
  return 0;
}
#endif

