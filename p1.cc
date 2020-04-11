#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

#include <complex>
#include <cmath>
using namespace std;
typedef double num_t;
/*
#include "ifloat.hh"
template <typename T> using complex = Complex<T>;
typedef SimpleFloat<uint64_t, DUInt<uint64_t, 64>, 64, int32_t> num_t;
// typedef SimpleFloat<DUInt<uint64_t, 64>, DUInt<DUInt<uint64_t, 64>, 128>, 128, int16_t> num_t;
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
  std::string s;
  int range(8);
  int slen(16);
  int step(1);
  if(1 < argc)
    range = std::atoi(argv[1]);
  if(2 < argc)
    slen  = std::atoi(argv[2]);
  if(3 < argc)
    step  = std::atoi(argv[3]);
  P1<num_t> p(slen, range, false);
  SimpleVector<num_t> buf(slen + range * step);
  for(int i = 0; i < buf.size(); i ++)
    buf[i] = num_t(0);
  num_t d0(0);
  auto  MM(d0);
  auto  bd(d0);
  while(std::getline(std::cin, s, '\n')) {
    num_t d;
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      d0 += (d - bd) * MM;
      for(int i = 1; i < buf.size(); i ++)
        buf[i - 1] = buf[i];
      buf[buf.size() - 1] = d - bd;
      const auto& fvec(p.next(buf, step, ! false));
      MM = num_t(0);
      for(int i = 0; i < fvec.size(); i ++)
        MM += fvec[i] * buf[buf.size() - 1 - i * step];
      if(! isfinite(MM) || isnan(MM))
        MM = num_t(0);
      bd = d;
    }
    std::cout << d0 << "," << MM << "," << p.lasterr << std::endl;
  }
  return 0;
}

