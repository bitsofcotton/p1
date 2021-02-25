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
  int skip(1);
  int mul(1);
  int origin(0);
  if(argc < 5) {
    std::cerr << "p1 <extra status> <variable> <ignore> <skip> <mul>? <origin>?" << std::endl;
    std::cerr << "continue with p1 " << eslen << " " << vrange << " " << ignore << " " << skip << std::endl;
  } else {
    eslen  = std::atoi(argv[1]);
    vrange = std::atoi(argv[2]);
    ignore = std::atoi(argv[3]);
    skip   = std::atoi(argv[4]);
    if(5 < argc) mul    = std::atoi(argv[5]);
    if(6 < argc) origin = std::atoi(argv[6]);
  }
  const auto ee(eslen < 0 || (1 < argc && argv[1][0] == '-'));
  std::vector<P1I<num_t> > p;
  p.resize(skip, P1I<num_t>(abs(eslen) + abs(ignore), abs(vrange)));
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  std::vector<num_t> M;
  M.resize(p.size(), num_t(0));
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    d *= num_t(mul);
    if(ee) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto delta(vrange < 0 ? atan(d - bd) : d - bd);
    if(d != bd) {
      if(bd != num_t(0)) {
        s0 += delta * M[0];
        s1 += M[0] == num_t(0) ? num_t(0) : delta - M[0];
      }
      for(int i = 0; i < M.size() - 1; i ++)
        M[i] = M[i + 1];
      auto& MM(M[M.size() - 1]);
      MM = p[(t ++) % p.size()].next(delta + num_t(origin), - ignore, 4 < argc) - num_t(origin);
      MM = MM == num_t(0) ? num_t(0) : (MM < num_t(0) ? - pow(- MM, num_t(1) / num_t(p.size())) : pow(MM, num_t(1) / num_t(p.size())));
      if(! isfinite(MM) || isnan(MM)) MM = num_t(0);
    }
    std::cout << M[M.size() - 1] << ", " << s0 << ", " << s1 <<  std::endl << std::flush;
  }
  return 0;
}

