#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <vector>
#include <assert.h>

#include <complex>
#include <cmath>
using namespace std;
typedef double num_t;
/*
#include "ifloat.hh"
template <typename T> using complex = Complex<T>;
typedef SimpleFloat<uint64_t, DUInt<uint64_t, 64>, 64, Signed<DUInt<uint64_t, 64>, 128> > num_t;
*/

#include "simplelin.hh"
#include "p1.hh"

template <typename T> const T& sgn(const T& x) {
  const static T zero(0);
  const static T one(1);
  const static T mone(- 1);
  if(zero < x)
    return one;
  if(x < zero)
    return mone;
  return zero;
}

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  int range(8);
  int slen(16);
  int loop(6);
  if(1 < argc)
    range = std::atoi(argv[1]);
  if(2 < argc)
    slen  = std::atoi(argv[2]);
  P1B<num_t> p(slen, range);
  num_t d0(0);
  auto  bd(d0);
  auto  MM(d0);
  while(std::getline(std::cin, s, '\n')) {
    num_t d;
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      d0 += (d - bd) * MM;
      MM  = p.next(d - bd);
      bd  = d;
      if(! isfinite(MM) | isnan(MM))
        MM = num_t(0);
    }
    std::cout << d0 << "," << MM << std::endl;
  }
  return 0;
}

