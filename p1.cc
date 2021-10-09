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

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;
#include "p1.hh"
typedef P1I<num_t, linearFeeder<num_t, idFeeder<num_t> > > plin_pt;
typedef P1I<num_t, deltaFeeder<num_t, arctanFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > patan_pt;
typedef shrinkMatrix<num_t, plin_pt>  plin_t;
typedef shrinkMatrix<num_t, patan_pt> patan_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
/*
  const auto stat(7 * 7);
  const auto var(7);
*/
  const auto stat(3 * 3);
  const auto var(3);
        int  step(1);
  if(argc < 2)
    std::cerr << "p1 <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with p1 " << step << std::endl;
  // please refer bitsofcotton/p2/catgp.cc
  vector<plin_t>  p;
  vector<patan_t> q;
  if(step < 0) {
    q.reserve(abs(step));
    for(int i = 0; i < abs(step); i ++) {
      const int ss(pow(num_t(int(2)), num_t(int(i))));
      q.emplace_back(patan_t(patan_pt(stat * ss, var, ss), ss));
    }
  } else {
    p.reserve(abs(step));
    for(int i = 0; i < abs(step); i ++) {
      const int ss(pow(num_t(int(2)), num_t(int(i))));
      p.emplace_back(plin_t(plin_pt(stat * ss, var, ss), ss));
    }
  }
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = num_t(int(0));
    for(int i = 0; i < (step < 0 ? q.size() : p.size()); i ++)
      M += step < 0 ? q[i].next(d) : p[i].next(d);
    std::cout << D << ", " << M << std::endl << std::flush;
  }
  return 0;
}

