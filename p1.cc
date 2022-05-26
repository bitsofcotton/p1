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
#include "p1.hh"
typedef P1I<num_t, idFeeder<num_t> > plin_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int status(20);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  const int var(max(num_t(int(2)), status < 0 ? sqrt(num_t(- status)) : pow(num_t(status), num_t(int(1)) / num_t(int(3)))));
  shrinkMatrix<num_t, plin_t> p;
  plin_t q;
  if(status < 0)
    q = plin_t(- status, var);
  else
    p = shrinkMatrix<num_t, plin_t>(plin_t(status, var, var), var);
  std::string s;
  num_t d(int(0));
  auto  Mx(d);
  auto  M(d);
  auto  S(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    Mx = max(Mx, abs(d) * num_t(int(2)));
    if(d == num_t(int(0)))
      std::cout << D << ", " << M << ", " << (S += D) << std::endl << std::flush;
    else {
      M = max(- Mx, min(Mx, status < 0 ? q.next(d) : p.next(d) ));
      std::cout << D << ", " << (M = abs(M) == Mx ? num_t(int(0)) : M) << ", " << (S += D) << std::endl << std::flush;
  }
    }
  return 0;
}

