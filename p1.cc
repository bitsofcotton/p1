#include <cstdio>
#include <cstring>
#include <iostream>
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
  int range(8);
  int slen(16);
  if(1 < argc)
    range = std::atoi(argv[1]);
  if(2 < argc)
    slen  = std::atoi(argv[2]);
  P1B<num_t> p(abs(slen), abs(range));
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  dd(d);
  auto  bbd(d);
  auto  M(d);
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    d0 += slen < 0 ? d - bd - M : (d - bd) * M;
    if(d != bd) {
      if(range < 0)
        M = p.next(d - bd);
      else {
        dd += d - bbd;
        M   = p.next(dd) - dd + (M - (d - bbd)) / num_t(2);
        bbd = bd;
      }
      if(t ++ <= slen + range || ! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << d0 << ", " << M << std::endl << std::flush;
  }
  return 0;
}

