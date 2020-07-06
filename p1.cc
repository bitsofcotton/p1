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

#include "simplelin.hh"
#include "p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  int range(8);
  int slen(16);
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
    }
    std::cout << d0 << "," << MM << std::endl;
  }
  return 0;
}

