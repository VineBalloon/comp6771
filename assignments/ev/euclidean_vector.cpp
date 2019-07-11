#include "euclidean_vector.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>

/* constructors */
EuclideanVector::EuclideanVector(int siz) noexcept {
  EuclideanVector(siz, 0.0);
}

EuclideanVector::EuclideanVector(int siz, double mag) noexcept {
  magnitudes_ = std::make_unique<double[]>(siz);
  size_ = siz;
  for (int i = 0; i < siz; i++) {
    magnitudes_[i] = mag;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator beg,
                                 std::vector<double>::const_iterator end) noexcept {
  magnitudes_ = std::make_unique<double[]>(end - beg);
  size_ = end - beg;
  int i = 0;
  for (auto it = beg; it != end; it++) {
    magnitudes_[i++] = *it;
  }
}

EuclideanVector::EuclideanVector(EuclideanVector&& o) noexcept
  : magnitudes_{std::move(o.magnitudes_)}, size_{o.size_} {
  o.size_ = 0;
}

/* enemies */
double& EuclideanVector::operator[](unsigned i) noexcept {
  assert(i >= 0 && static_cast<int>(i) < size_);
  return magnitudes_[i];
}

double EuclideanVector::operator[](unsigned i) const noexcept {
  assert(i >= 0 && static_cast<int>(i) < size_);
  return magnitudes_[i];
}

EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& oth) {
  if (size_ != oth.size_) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] += oth[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& oth) {
  if (this->size_ != oth.size_) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] -= oth[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double oth) noexcept {
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] *= oth;
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double oth) {
  if (oth == 0) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] /= oth;
  }
  return *this;
}

EuclideanVector::operator std::vector<double>() noexcept {
  std::vector<double> ret;
  for (int i = 0; i < size_; i++) {
    ret.push_back(magnitudes_[i]);
  }
  return ret;
}

EuclideanVector::operator std::list<double>() noexcept {
  std::list<double> ret;
  for (int i = 0; i < size_; i++) {
    ret.push_back(magnitudes_[i]);
  }
  return ret;
}

/* friends */
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
  os << "[";
  for (int i = 0; i < v.size_; i++) {
    os << v.magnitudes_[i];
    if (i == v.size_ - 1) {
      break;
    }
    os << " ";
  }
  os << "]";
  return os;
}

bool operator==(const EuclideanVector& a, const EuclideanVector& b) noexcept {
  if (a.size_ != b.size_) {
    return false;
  }
  for (int i = 0; i < a.size_; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

bool operator!=(const EuclideanVector& a, const EuclideanVector& b) noexcept {
  return !(a == b);
}

EuclideanVector operator+(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector ret(a.size_);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] + b[i];
  }
  return ret;
}

EuclideanVector operator-(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector ret(a.size_);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] - b[i];
  }
  return ret;
}

EuclideanVector operator*(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector ret(a.size_);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] * b[i];
  }
  return ret;
}

EuclideanVector operator*(const EuclideanVector& a, const double& b) noexcept {
  EuclideanVector ret(a.size_);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] * b;
  }
  return ret;
}

EuclideanVector operator*(const double& a, const EuclideanVector& b) noexcept {
  return b * a;
}

EuclideanVector operator/(const EuclideanVector& a, const double& b) {
  if (b == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  EuclideanVector ret(a.size_);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] / b;
  }
  return ret;
}

/* methods */
double EuclideanVector::at(int ind) const {
  if (ind < 0 || ind >= size_) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector"
                               " object");
  }
  return magnitudes_[ind];
}

double& EuclideanVector::at(int ind) {
  if (ind < 0 || ind >= size_) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector"
                               " object");
  }
  return magnitudes_[ind];
}

int EuclideanVector::GetNumDimensions() noexcept {
  return size_;
}

double EuclideanVector::GetEuclideanNorm() {
  if (size_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not"
                               " have a norm");
  }
  double sum = 0;
  for (int i = 0; i < size_; i++) {
    sum += magnitudes_[i] * magnitudes_[i];
  }
  return sqrt(sum);
}

EuclideanVector EuclideanVector::CreateUnitVector() {
  if (size_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not"
                               " have a unit vector");
  }
  if (GetEuclideanNorm() == 0) {
    throw EuclideanVectorError("EuclideanVector with euclidean normal of 0"
                               " does not have a unit vector");
  }
  EuclideanVector ret(size_);
  double norm = GetEuclideanNorm();
  for (int i = 0; i < size_; i++) {
    ret.magnitudes_[i] = magnitudes_[i] / norm;
  }
  return ret;
}

