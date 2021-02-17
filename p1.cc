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
  int grange(4);
  int srange(1);
  int ignore(2);
  int origin(0);
  if(argc < 5) {
    std::cerr << "p1 <extra status> <variable> <guard> <status> <ignore>" << std::endl;
    std::cerr << "continue with p1 " << eslen << " " << vrange << " " << grange << " " << srange << " " << ignore << std::endl;
  } else {
    eslen  = std::atoi(argv[1]);
    vrange = std::atoi(argv[2]);
    grange = std::atoi(argv[3]);
    srange = std::atoi(argv[4]);
    ignore = std::atoi(argv[5]);
    if(5 < argc) origin = std::atoi(argv[6]);
  }
  const auto ee(eslen  < 0 || (1 < argc && argv[1][0] == '-'));
  const auto gg(grange < 0 || (3 < argc && argv[3][0] == '-'));
  const auto ss(srange < 0 || (4 < argc && argv[4][0] == '-'));
  const auto ii(ignore < 0 || (5 < argc && argv[5][0] == '-'));
  P1Istatus<num_t> p(abs(eslen) + abs(ignore), abs(vrange), abs(srange), abs(grange));
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  M(d);
  auto  MM(d);
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(ee) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto delta00(vrange < 0 ? atan(d - bd) : d - bd);
    const auto delta0(ii ? delta00 : delta00);
    const auto delta(ii ? pow(delta00 + num_t(origin), num_t(abs(vrange) + abs(srange) + 1)) : delta00);
    if(d != bd && bd != num_t(0)) {
      if(M == num_t(0)) {
        s0 += delta0;
        s2 += delta0;
      } else {
        s0 += delta0 * M;
        s1 = delta0 - M;
        if(MM == num_t(0))
          s2 += delta0;
        else {
          s2 += delta0 * MM;
          s3 = delta0 - MM;
        }
        t  ++;
      }
    }
    if(d != bd) {
      M = ss ? p.nextAvg(delta, abs(ignore)) : p.next(delta, abs(ignore));
      M = ii ? pow(M, num_t(1) / num_t(abs(vrange) + abs(srange) + 1)) / num_t(2) - num_t(origin) : M;
      if(! isfinite(M) || isnan(M)) M = num_t(0);
      MM = t ? M + s1 / num_t(t) : num_t(0);
    }
    std::cout << M << ", " << (gg ? s2 : s0) << ", " << (gg ? s3 : s1) <<  ", " << delta0 << std::endl << std::flush;
  }
  return 0;
}

