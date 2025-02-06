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
#include <stdint.h>
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
  int step(0);
  int stat(0);
  if(argc < 2) std::cerr << argv[0] << " <step>? <lines>? : continue with ";
  if(1 < argc) step = std::atoi(argv[1]);
  if(2 < argc) stat = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << step << " " << stat << std::endl;
  assert(0 <= stat && 0 <= step);
  idFeeder<SimpleVector<num_t> > feed(stat);
  SimpleVector<SimpleVector<num_t> > feed0;
  idFeeder<SimpleVector<num_t> > f(step ? step : 1);
  vector<SimpleVector<num_t> > heavy;
  std::string s;
  SimpleVector<num_t> d;
  while(std::getline(std::cin, s, '\n')) {
    const auto& M(heavy.size() ? heavy[0] : f.res[0]);
    std::stringstream ins(s);
    int n(0);
    for(int i = 0; 0 <= i && i < s.size(); i ++)
      if(s[i] == ',') n ++;
    if(! d.size()) {
      d.resize(n + 1);
      d.O();
    }
    for(int i = 0; i < d.size(); i ++) {
      ins >> d[i];
      ins.ignore(s.size(), ',');
    }
    if(d.size() <= M.size() && (f.full || heavy.size()) )
      for(int i = 0; i < d.size(); i ++)
#if defined(_CHAIN_)
        std::cout << d[i] - M[i] << ", ";
#else
        std::cout << d[i] * M[i] << ", ";
#endif
    else
      for(int i = 0; i < d.size(); i ++)
        std::cout << num_t(int(0)) << ", ";
    for(int i = 0; i < d.size(); i ++) {
      d[i] += num_t(1);
      d[i] /= num_t(2);
    }
    if(stat) feed.next(d);
    else feed0.entity.emplace_back(d);
    if((stat && feed.full) || (! stat && 8 + step < feed0.entity.size()) ) {
      // N.B. exhaust of the resource, so we expect the chain pp3n | p0 .
      if(step) {
        auto work(predv0<num_t, 0>(stat ? feed.res.entity : feed0.entity, string(""), stat ? feed.res.entity.size() : feed0.entity.size(), step));
        for(int i = 0; i < work.size(); i ++) {
          work[i] *= num_t(2);
          work[i] -= num_t(1);
        }
        f.next(move(work));
        if(f.full) {
          for(int i = 0; i < f.res[f.res.size() - 1].size() - 1; i ++)
            std::cout << f.res[f.res.size() - 1][i] << ", ";
          std::cout <<
            f.res[f.res.size() - 1][f.res[f.res.size() - 1].size() - 1] <<
              std::endl << std::flush;
          continue;
        }
      } else {
        if(heavy.size()) {
          for(int i = 1; i < heavy.size(); i ++)
            heavy[i - 1] = move(heavy[i]);
          heavy[heavy.size() - 1] = SimpleVector<num_t>(d.size()).O();
        }
        if(8 < feed0.entity.size()) {
          heavy.emplace_back(SimpleVector<num_t>(d.size()).O());
          for(int i = 1; i <= heavy.size(); i ++) {
            auto work(predv0<num_t, 0>(feed0.entity, string(""), feed0.entity.size(), i).subVector(0, d.size()));
            for(int j = 0; j < work.size(); j ++) {
              work[j] *= num_t(2);
              work[j] -= num_t(1);
            }
            heavy[i - 1] += work;
          }
          heavy[0] /= num_t(int(heavy.size()));
          for(int i = 0; i < heavy[0].size() - 1; i ++)
            std::cout << heavy[0][i] << ", ";
          std::cout << heavy[0][heavy[0].size() - 1] << std::endl << std::flush;
          continue;
        }
      }
    }
    for(int i = 0; i < d.size(); i ++)
      std::cout << num_t(int(0)) << ", ";
    std::cout << std::endl << std::flush;
  }
  return 0;
}

