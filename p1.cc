#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <assert.h>

#if !defined(_FLOAT_BITS_)
  #include <complex>
  #include <cmath>
  using namespace std;
  typedef long double num_t;
  #include <limits>
#else
  #include "ifloat.hh"
  template <typename T> using complex = Complex<T>;
# if _FLOAT_BITS_ == 32
    typedef uint32_t myuint;
    typedef int32_t  myint;
    typedef SimpleFloat<myuint, uint64_t, 32, int64_t> num_t;
    #define mybits 32
# elif _FLOAT_BITS_ == 64
    typedef uint64_t myuint;
    typedef int64_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 64>, 64, int64_t> num_t;
    #define mybits 64
# elif _FLOAT_BITS_ == 128
    typedef DUInt<uint64_t, 64> uint128_t;
    typedef Signed<uint128_t, 128> int128_t;
    typedef uint128_t myuint;
    typedef int128_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 128>, 128, int64_t> num_t;
    #define mybits 128
# else
#   error cannot handle float
# endif
#endif

#include "simplelin.hh"
#include "p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int eslen(2);
  int vrange(8);
  int ignore(- 2);
  int recur(1);
  int mul(1);
  int origin(0);
  if(argc < 4) {
    std::cerr << "p1 <extra status> <variable> <ignore> <recur>? <mul>? <origin>?" << std::endl;
    std::cerr << "continue with p1 " << eslen << " " << vrange << " " << ignore << " " << recur << " " << mul << " " << origin << std::endl;
  } else {
    eslen  = std::atoi(argv[1]);
    vrange = std::atoi(argv[2]);
    ignore = std::atoi(argv[3]);
    if(4 < argc) recur  = std::atoi(argv[4]);
    if(5 < argc) mul    = std::atoi(argv[5]);
    if(6 < argc) origin = std::atoi(argv[6]);
  }
  const auto ee(eslen < 0 || (1 < argc && argv[1][0] == '-'));
  std::vector<P1I<num_t> > p;
  p.resize(abs(recur), P1I<num_t>(abs(eslen) + abs(ignore), abs(vrange)));
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  s4(d);
  int   tp(0);
  auto  tm(tp);
  std::vector<num_t> M;
  M.resize(p.size(), num_t(0));
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    d *= num_t(mul);
    if(ee) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto  delta(vrange < 0 ? atan(d - bd) : d - bd);
          auto& MM(M[M.size() - 1]);
    if(d != bd) {
      if(bd != num_t(0) && MM != num_t(0)) {
        tp ++;
        tm ++;
        s0 += delta * MM * num_t(recur < 0 ? tp - tm : 1);
        s1 += delta - MM;
        s2 += (d - bd) * MM * num_t(recur < 0 ? tp - tm : 1);
        s3 += delta * MM * num_t(tp);
        s4 -= delta * MM * num_t(tm);
      }
      std::vector<num_t> rdelta;
      rdelta.resize(p.size(), delta);
      for(int i = 0; i < rdelta.size(); i ++)
        rdelta[i] -= M[i];
      M[0] = (p[0].next(delta, - ignore, num_t(origin)) - num_t(origin)) / num_t(origin ? origin : 1);
      for(int i = 1; i < p.size(); i ++) {
        if(rdelta[i - 1] + num_t(origin) == p[i].last()) break;
        M[i] = M[i - 1] + (p[i].next(rdelta[i - 1], - ignore, num_t(origin)) - num_t(origin)) / num_t(origin ? origin : 1);
      }
      if(! isfinite(MM) || isnan(MM)) MM = num_t(0);
      if(0 < s3) s3 = num_t(tp = 0);
      if(0 < s4) s4 = num_t(tm = 0);
    }
    std::cout << MM << ", " << s0 << ", " << s1 << ", " << s2 << ", " << tp << ", " << tm << std::endl << std::flush;
  }
  return 0;
}

