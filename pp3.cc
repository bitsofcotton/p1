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
#include <limits>
#include <assert.h>
#include <stdint.h>

#if defined(_OPENMP)
#include <omp.h>
#endif

#if defined(_P_VULKAN_)
#include <vulkan/vulkan.h>
#endif

#if defined(_MIMALLOC_)
#define MIMALLOC_OVERRIDE_H
#define MIMALLOC_NEW_DELETE_H
#include <mimalloc.h>
#endif

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;
lieonn_t lieonn;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  lieonnStaticInit();
  const int len(loop22<num_t>() + 2);
  std::string s;
#if defined(_CHAIN_)
  const bool chain(true);
#else
  const bool chain(false);
# endif
#endif
  idFeeder<SimpleVector<num_t> > b(len);
  SimpleVector<num_t> M;
  SimpleVector<num_t> bd;
  while(std::getline(std::cin, s, '\n')) {
    SimpleVector<num_t> d(s2sv<num_t>(s));
    if(M.size() < d.size()) {
      bd.resize(d.size()).O();
      M.resize(d.size() * 4).O();
    }
    for(int i = 0; i < d.size(); i ++) for(int j = 0; j < 4; j ++)
      std::cout << (chain ? d[i] - bd[i] - M[i * 4 + j] :
        M[i * 4 + j] * (d[i] - bd[i])) << ", ";
    bd = d;
    std::cout << flush;
    if(chain) {
      for(int j = 0; j < M.size() - 1; j ++)
        std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << endl << flush;
    }
    b.next(d);
    if(b.full) {
      SimpleVector<vector<SimpleVector<num_t> > > work(b.res.size());
      for(int i = 0; i < b.res.size(); i ++)
        work[i].resize(1, offsetHalf<num_t>(
          const_cast<const SimpleVector<num_t>&>(b.res[i]) ));
      M = unOffsetHalf<num_t>(predVec4<num_t, 20, false>(move(work), 2)[0]);
    }
    if(! chain) {
      for(int j = 0; j < M.size() - 1; j ++)
        std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << endl << flush;
    }
  }
#if !defined(_ONEBINARY_)
  lieonnStaticDestroy();
  return 0;
}
#endif

