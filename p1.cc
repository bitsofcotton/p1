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
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int status(26);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  idFeeder<num_t> f(std::max(int(1), abs(status)));
  // N.B. randtools meaning, there exists v2v tanglement.
  //      so to avoid them, we only use 3 dimension for original points.
  //      P1I treats input as non commutative ones, so up to 7 is no chance.
  PBond<num_t, P01<num_t> > p(P01<num_t>(std::max(int(1), std::min(int(4), int(sqrt(num_t(int(status))))))), std::max(int(3), status) + 2);
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
#if defined(_JAM_)
    std::cout << (d *= M) << ", ";
#else
    std::cout << d * M << ", ";
#endif
    if(status == - 1) M -= d * num_t(++ t);
    else if(status < 0) {
      const auto& ff(f.next(d));
      if(f.full) {
        M = num_t(int(0));
        for(int i = 0; i < ff.size(); i ++) M += ff[i];
        M = - M;
      }
    } else if(! status) M -= d;
    else if(status == 1) M = - d;
    else M = p.next(d);
#if defined(_JAM_)
    if((M = sgn<num_t>(arc4random_uniform(2) & 1 ? - M : M)) == num_t(int(0)))
      M = num_t(int(1));
#endif
    std::cout << M << std::endl << std::flush;
  }
  return 0;
}

