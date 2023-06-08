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
  int status(35);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(0 <= status);
  // XXX: 2^2^5 : 2^6^2 : upper bound invariant reasonable causes 11 dimension.
  //                      concat them, it's up to 6.
  PBond<num_t, P1I<num_t> > p(P1I<num_t>(std::max(int(2), std::min(int(5), int(sqrt(num_t(int(status))))))), std::max(int(8), status));
  std::string s;
  num_t d(int(0));
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    if(! status) M -= d;
    else if(status == 1) M = - d;
    else M = p.next(d);
    std::cout << M << std::endl << std::flush;
  }
  return 0;
}

