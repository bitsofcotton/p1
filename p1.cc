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
  int status(20);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  const int var(max(num_t(int(2)), pow(num_t(status), num_t(int(1)) / num_t(int(2)))));
  PBond<num_t, P1I<num_t>, idFeeder<num_t>, deltaFeeder<num_t, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > p;
  SimpleVector<num_t> q0;
  idFeeder<num_t> q(max(int(1), int(abs(status))));
  if(status <= 0) {
    q0.resize(max(int(1), int(- status)) + 1);
    q0.O();
  } else
    p = PBond<num_t, P1I<num_t>, idFeeder<num_t>, deltaFeeder<num_t, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > >(P1I<num_t>(max(num_t(int(2)), pow(num_t(status), num_t(int(1)) / num_t(int(3)) ))), status);
  std::string s;
  num_t d(int(0));
  auto  Mx(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    Mx = max(Mx, abs(d) * num_t(int(2)));
    if(! status) M -= d;
    else if(status == - 1) M = - d;
    else if(status < 0) {
      auto qm(makeProgramInvariant<num_t>(q.next(d)));
      q0 += std::move(qm.first) * pow(qm.second, ceil(- log(SimpleMatrix<num_t>().epsilon())));
      auto qq(q);
      auto qqm(makeProgramInvariant<num_t>(qq.next(d)));
      M = revertProgramInvariant<num_t>(make_pair(
        - (q0.dot(qqm.first) - q0[q0.size() - 2] *
             qqm.first[qqm.first.size() - 2]) / q0[q0.size() - 2] /
             num_t(int(q0.size())), qqm.second));
    } else M = max(- Mx, min(Mx, p.next(d) ));
    std::cout << M << std::endl << std::flush;
  }
  return 0;
}

