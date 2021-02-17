/*
BSD 3-Clause License

Copyright (c) 2020-2021, kazunobu watatsu
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(_P1_)

// Get invariant structure that
// \[0, &alpha;\[ register computer with deterministic calculation
// that whole in/out is shown in the varlen.
// Please refer bitsofcotton/randtools .
// [[A I], [I A^-1]] [x y], if rank A = dim x = dim y,
// rank [[A I], [I A^-1]] == rank A.
// so with this, U [[B], [O]] [x y] == 0.
// this returns one of u_k that concerns 0.
// skip attemps maximum skip status number if original data has a noised ones.
template <typename T> SimpleVector<T> invariantP1(const SimpleVector<T>& in, const SimpleVector<T>& stin, const int& varlen, const int& skip = 0, const int& guard = 0) {
  assert(varlen < in.size());
#if defined(_FLOAT_BITS_)
  static const auto epsilon(T(1) >> int64_t(mybits - 2));
#else
  static const auto epsilon(std::numeric_limits<T>::epsilon());
#endif
  static const auto threshold_inner(sqrt(epsilon));
  const auto statlen(max(varlen + stin.size() - in.size() + guard, 0));
  SimpleMatrix<T> A((in.size() - varlen - guard) * 2 + 1,
    varlen + 1 + statlen);
  SimpleVector<T> fvec(A.cols());
  SimpleVector<T> one(A.rows());
  const auto nin(sqrt(in.dot(in)));
  const auto nst(stin.size() ? sqrt(stin.dot(stin)) : T(1));
#if defined(_OPENMP)
#pragma omp parallel
#pragma omp for schedule(static, 1)
#endif
  for(int i = 0; i < in.size() - varlen - guard; i ++) {
    for(int j = 0; j < varlen; j ++)
      A(i, j) = in[i + j] / nin;
    A(i, varlen - 1) = in[i + varlen - 1 + guard] / nin;
    A(i, varlen) = T(1) / sqrt(T(A.rows() * A.cols()));
    for(int j = 0; j < statlen; j ++)
      A(i, j + varlen + 1) = stin[i + j] / nst;
    A.row(i + A.rows() / 2) = - A.row(i);
  }
#if defined(_OPENMP)
#pragma omp for schedule(static, 1)
#endif
  for(int i = 0; i < A.rows(); i ++)
    one[i] = T(1);
  one /= sqrt(one.dot(one));
#if defined(_OPENMP)
#pragma omp for schedule(static, 1)
#endif
  for(int i = 0; i < fvec.size() - 1; i ++)
    A(A.rows() - 1, i) = fvec[i] = T(0);
  A(A.rows() - 1, A.cols() - 1) = T(1);
  fvec[fvec.size() - 1] = T(0);
  SimpleMatrix<T> Pt(A.cols(), A.rows());
  for(int i = 0; i < Pt.rows(); i ++)
    for(int j = 0; j < Pt.cols(); j ++)
      Pt(i, j) = T(0);
  for(int i = 0; i < A.cols(); i ++) {
    const auto Atrowi(A.col(i));
    const auto work(Atrowi - Pt.projectionPt(Atrowi));
    Pt.row(i) = work / sqrt(work.dot(work));
    const auto npt(Pt.row(i).dot(Pt.row(i)));
    if(! (isfinite(npt) && ! isnan(npt)))
      return fvec;
  }
  const auto R(Pt * A);
  const auto mone(Pt * (- one));
  SimpleVector<T> on;
  SimpleVector<T> orth;
  for(int n_fixed = 0 ; n_fixed < Pt.rows() - 1; n_fixed ++) {
    on = Pt.projectionPt(- one);
    std::vector<pair<T, int> > onM;
    onM.reserve(on.size());
    for(int j = 0; j < on.size(); j ++)
      onM.emplace_back(std::make_pair(on[j], j));
    std::sort(onM.begin(), onM.end());
    auto fidx(- 1);
    for(int i = onM.size() - 1 - skip; i < onM.size(); i ++)
      if(threshold_inner < onM[i].first) {
        fidx = onM[i].second;
        break;
      }
    if(fidx < 0)
      break;
    orth = Pt.col(fidx);
    const auto norm2orth(orth.dot(orth));
#if defined(_OPENMP)
#pragma omp for schedule(static, 1)
#endif
    for(int j = 0; j < Pt.cols(); j ++)
      Pt.setCol(j, Pt.col(j) - orth * Pt.col(j).dot(orth) / norm2orth);
  }
  fvec = R.solve(mone - Pt * on);
  const auto nfv(fvec.dot(fvec));
  return (isfinite(nfv) ? (nfv == T(0) ? fvec : fvec / sqrt(nfv))
    : fvec * T(0));
}


template <typename T> class P1Istatus {
public:
  typedef SimpleVector<T> Vec;
  typedef SimpleMatrix<T> Mat;
  inline P1Istatus();
  inline P1Istatus(const int& stat, const int& var, const int& instat, const int& guard);
  inline ~P1Istatus();
         T next(const T& in, const int& skip = 0);
  inline T nextAvg(const T& in, const int& skip = 0);
  Vec invariant_abs;
  Vec invariant_sgn;
  Vec s_buf;
  Vec s_sbuf;
  T   rabs;
  T   rsgn;
  std::vector<Vec> hist_abs;
  std::vector<Vec> hist_sgn;
private:
  inline const T& sgn(const T& x) const;
  Vec buf;
  Vec sbuf;
  Vec projinv_abs;
  Vec projinv_sgn;
  int varlen;
  int guard;
  int t;
  int si;
};

template <typename T> inline P1Istatus<T>::P1Istatus() {
  rabs = rsgn = T(varlen = guard = t = si = 0);
}

template <typename T> inline P1Istatus<T>::P1Istatus(const int& stat, const int& var, const int& instat, const int& guard) {
  buf.resize(stat + (varlen = var) + (this->guard = guard) - 1);
  for(int i = 0; i < buf.size(); i ++)
    buf[i] = T(0);
  sbuf = buf;
  s_buf.resize(stat + instat - 1);
  for(int i = 0; i < s_buf.size(); i ++)
    s_buf[i] = T(0);
  s_sbuf = s_buf;
  rabs = rsgn = T(t = si = 0);
}

template <typename T> inline P1Istatus<T>::~P1Istatus() {
  ;
}

template <typename T> inline const T& P1Istatus<T>::sgn(const T& x) const {
  static const T zero(0);
  static const T one(1);
  static const T mone(- one);
  return x != zero ? (x < zero ? mone : one) : zero;
}

// Get invariant with inner status.
// Get <a, [x0 y0 x1 y1]> = 0 case, which is <a', [x0 x1]> = <a'', [y0 y1]> .
// With non invariant case on them, we get X a' == b == B [y0 y1].
template <typename T> T P1Istatus<T>::next(const T& in, const int& skip) {
  assert(buf.size() == sbuf.size());
  for(int i = 0; i < buf.size() - 1; i ++) {
    buf[i]  = buf[i + 1];
    sbuf[i] = sbuf[i + 1];
  }
  buf[ buf.size()  - 1] = abs(in);
  sbuf[sbuf.size() - 1] = sgn(in) + T(2);
  if(t ++ < buf.size()) return T(0);
  // N.B. to compete with cheating, we calculate long term same invariant each.
  projinv_abs = invariantP1<T>(buf , Vec(), varlen, skip, guard);
  projinv_sgn = invariantP1<T>(sbuf, Vec(), varlen, skip, guard);
  assert(projinv_abs.size() == projinv_sgn.size());
  if(buf.size() + s_buf.size() < t) {
    invariant_abs = invariantP1<T>(buf , s_buf,  varlen, skip, guard);
    invariant_sgn = invariantP1<T>(sbuf, s_sbuf, varlen, skip, guard);
    assert(invariant_abs.size() == invariant_sgn.size());
  }
  assert(s_buf.size() == s_sbuf.size());
  for(int i = 0; i < s_buf.size() - 1; i ++) {
    s_buf[i]  = s_buf[i + 1];
    s_sbuf[i] = s_sbuf[i + 1];
  }
  const auto statlen(max(varlen + s_buf.size() - buf.size() + guard, 0));
  const auto ratio0(T(1) / sqrt(T((buf.size() - varlen - guard) * 2 + 1) * T(varlen + 1)));
  auto& vva(s_buf[ s_buf.size() - 1]);
  auto& vvs(s_sbuf[s_sbuf.size() - 1]);
  vva = projinv_abs[varlen] * ratio0;
  vvs = projinv_sgn[varlen] * ratio0;
  for(int i = 0; i < projinv_abs.size() - 1; i ++) {
    vva +=  buf[i - projinv_abs.size() +  buf.size() - guard + 1] * projinv_abs[i];
    vvs += sbuf[i - projinv_sgn.size() + sbuf.size() - guard + 1] * projinv_sgn[i];
  }
  if(! (invariant_abs.size() && invariant_sgn.size())) return T(0);
  if(buf.size() - varlen - guard == s_buf.size()) {
    rabs = projinv_abs[varlen] * ratio0;
    rsgn = projinv_sgn[varlen] * ratio0;
    for(int i = 0; i < varlen - 1; i ++) {
      rabs +=  buf[i - varlen +  buf.size() - guard + 1] * invariant_abs[i];
      rsgn += sbuf[i - varlen + sbuf.size() - guard + 1] * invariant_abs[i];
    }
    return (rabs = abs(rabs / projinv_abs[varlen - 1])) *
      (rsgn = sgn(abs(rsgn / projinv_sgn[varlen - 1]) - T(2)));
  }
  const auto ratio(T(1) / sqrt(T((buf.size() - varlen - guard) * 2 + 1) * T(varlen + statlen + 1)));
  rabs = invariant_abs[varlen] * ratio;
  rsgn = invariant_sgn[varlen] * ratio;
  for(int i = 0; i < varlen - 1; i ++) {
    rabs +=  buf[i - varlen +  buf.size() - guard + 1] * invariant_abs[i];
    rsgn += sbuf[i - varlen + sbuf.size() - guard + 1] * invariant_abs[i];
  }
  for(int i = 0; i < statlen; i ++) {
    rabs += s_buf[ i - statlen +  s_buf.size()] * invariant_abs[i + varlen + 1];
    rsgn += s_sbuf[i - statlen + s_sbuf.size()] * invariant_sgn[i + varlen + 1];
  }
  return (rabs = abs(rabs / invariant_abs[varlen - 1])) *
    (rsgn = sgn(abs(rsgn / invariant_sgn[varlen - 1]) - T(2)));
}

template <typename T> inline T P1Istatus<T>::nextAvg(const T& in, const int& skip) {
  assert(hist_abs.size() == hist_sgn.size());
  const auto res(next(in, skip));
  if(skip <= 0) return res;
  const auto nostat(buf.size() - varlen - guard == s_buf.size());
  if(hist_abs.size() < skip) {
    if(nostat ? projinv_abs.size() : invariant_abs.size()) {
      hist_abs.emplace_back(nostat ? projinv_abs : invariant_abs);
      hist_sgn.emplace_back(nostat ? projinv_sgn : invariant_sgn);
    }
    return T(0);
  }
  auto avg_abs(hist_abs[0]);
  auto avg_sgn(hist_sgn[0]);
  for(int i = 1; i < hist_abs.size(); i ++) {
    avg_abs += hist_abs[i];
    avg_sgn += hist_sgn[i];
  }
  const auto statlen(max(varlen + s_buf.size() - buf.size() + guard, 0));
  const auto ratio(T(1) / sqrt(nostat ?
    T((buf.size() - varlen - guard) * 2 + 1) * T(varlen + 1) :
    T((buf.size() - varlen - guard) * 2 + 1) * T(varlen + statlen + 1) ));
  rabs = avg_abs[varlen] * ratio;
  rsgn = avg_sgn[varlen] * ratio;
  for(int i = 0; i < varlen - 1; i ++) {
    rabs +=  buf[i - varlen +  buf.size() - guard + 1] * avg_abs[i];
    rsgn += sbuf[i - varlen + sbuf.size() - guard + 1] * avg_abs[i];
  }
  if(! nostat)
    for(int i = 0; i < statlen; i ++) {
      rabs += s_buf[ i - statlen +  s_buf.size()] * avg_abs[i + varlen + 1];
      rsgn += s_sbuf[i - statlen + s_sbuf.size()] * avg_sgn[i + varlen + 1];
    }
  return (rabs = abs(rabs / avg_abs[varlen - 1])) *
    (rsgn = sgn(abs(rsgn / avg_sgn[varlen - 1]) - T(2)));
}

#define _P1_
#endif

