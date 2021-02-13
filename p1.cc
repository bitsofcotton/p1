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
  int wslen(20);
  int vrange(8);
  int grange(4);
  int srange(2);
  int ignore(2);
  if(argc < 5) {
    std::cerr << "p1 <whole status> <variable> <guard> <status> <ignore>" << std::endl;
    std::cerr << "continue with p1 " << wslen << " " << vrange << " " << grange << " " << srange << " " << ignore << std::endl;
  } else {
    wslen  = std::atoi(argv[1]);
    vrange = std::atoi(argv[2]);
    grange = std::atoi(argv[3]);
    srange = std::atoi(argv[4]);
    ignore = std::atoi(argv[5]);
  }
  const auto gg(grange < 0 || (3 < argc && argv[3][0] == '-'));
  assert(0 <= ignore);
  P1Istatus<num_t> p(wslen, abs(vrange), abs(srange), abs(grange));
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  auto  tilt(d);
  auto  s2(d);
  auto  s3(d);
  auto  M(d);
  auto  MM(d);
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(wslen < 0) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto delta(vrange < 0 ? atan(d - bd) : d - bd);
    if(bd != num_t(0)) {
      if(M == num_t(0)) {
        s0 += delta;
        s2 += delta;
      } else {
        s0 += delta * M;
        s1 += delta - M;
        if(MM == num_t(0))
          s2 += delta;
        else {
          s2 += delta * MM;
          s3 += delta - MM;
        }
        t  ++;
      }
    }
    if(d != bd) {
      M = p.next(delta, ignore);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
      MM = t ? M + s1 / num_t(t) : num_t(0);
    }
    std::cout << M << ", " << (gg ? s2 : s0) << ", " << (gg ? s3 : s1) << std::endl << std::flush;
  }
  return 0;
}

