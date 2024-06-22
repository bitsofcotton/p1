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
  int progression(1);
  if(argc < 2) std::cerr << argv[0] << " <progression num>? : continue with ";
  if(1 < argc) progression = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << progression << std::endl;
  if(1 < abs(progression)) {
    const auto& pn(pnTinySingle(abs(progression) - 1));
    progression = sgn<int>(progression);
    for(int i = 0; i < pn.size(); i ++) progression *= pn[i];
    std::cerr << "using raw progression: " << progression << std::endl;
  }
  // N.B. randtools meaning, there exists v2v tanglement.
  //      so to avoid them, we only use 3 dimension for original points.
  //      P1I treats input as non commutative ones, so up to 7 is no chance.
  Pprogression<num_t, P01<num_t> > p(progression ? progression : 1, 5 * 5 - 4 + 2);
  std::string s;
  num_t d(int(0));
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    if(! progression) M -= d;
    else if(progression == - 1) M = - d;
    else M = p.next(d);
    std::cout << M << std::endl << std::flush;
  }
  return 0;
}

