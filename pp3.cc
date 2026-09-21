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
#if defined(_P_RAW_)
  int len(loop22<num_t>() + 1 + 3);
#else
  int len(loop22<num_t>() + 3 + 3);
#endif
  if(1 < argc) len = std::atoi(argv[1]);
  cerr << argv[0] << " " << len << endl;
  std::string s;
#if defined(_P_RAW_)
  const bool chain(true);
#else
  const bool chain(false);
# endif
#endif
  idFeeder<SimpleVector<num_t> > b(len);
  SimpleVector<num_t> M;
  while(std::getline(std::cin, s, '\n')) {
    SimpleVector<num_t> d(s2sv<num_t>(s));
    if(M.size() < d.size()) M.resize(d.size()).O();
    for(int i = 0; i < d.size(); i ++)
      std::cout << (chain ? d[i] - M[i] : d[i] * M[i]) << ", ";
    if(chain) {
      for(int j = 0; j < M.size() - 1; j ++) std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << endl << flush;
    } else std::cout << flush;
    b.next(d);
    if(b.full) {
      pair<SimpleVector<SimpleVector<num_t> >, num_t> bb(normalizeS<num_t>(
        b.res));
      SimpleVector<vector<SimpleVector<num_t> > > work(bb.first.size());
      for(int i = 0; i < b.res.size(); i ++)
        work[i].resize(1, offsetHalf<num_t>(bb.first[i]));
      M = unOffsetHalf<num_t>(predVec0<num_t, 20>(move(work), 2)[0]) * bb.second;
    }
    if(! chain) {
      for(int j = 0; j < M.size() - 1; j ++) std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << endl << flush;
    }
  }
#if !defined(_ONEBINARY_)
  lieonnStaticDestroy();
  return 0;
}
#endif

