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

template <typename T> const T& sgn(const T& x) {
  static const T zero(0);
  static const T one(1);
  static const T mone(- one);
  return x != zero ? (x < zero ? mone : one) : zero;
}

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int slen(16);
  int range(8);
  int skip(4);
  if(1 < argc)
    slen  = std::atoi(argv[1]);
  if(2 < argc)
    range = std::atoi(argv[2]);
  if(3 < argc)
    skip  = std::atoi(argv[3]);
  assert(slen && range && 0 <= skip);
  P1<num_t> p(abs(slen), abs(range));
  auto  q(p);
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(slen < 0) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto delta(range < 0 ? atan(d - bd) : d - bd);
    if(bd != num_t(0)) {
      if(M == num_t(0))
        s0 += delta;
      else {
        s0 += delta * M;
        s1 += delta - M;
      }
    }
    if(d != bd) {
      M = abs(p.next(abs(delta), skip)) * sgn<num_t>(abs(q.next(sgn<num_t>(delta) + num_t(2), skip)) - num_t(2));
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

