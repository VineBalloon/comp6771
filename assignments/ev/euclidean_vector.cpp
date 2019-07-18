#include "assignments/ev/euclidean_vector.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

/* exception helper */
EuclideanVectorError euclideanDimensionError(const EuclideanVector& X, const EuclideanVector& Y) {
  return EuclideanVectorError(static_cast<std::string>("Dimensions of LHS(") +
                              std::to_string(X.GetNumDimensions()) + ") and RHS(" +
                              std::to_string(Y.GetNumDimensions()) + ") do not match");
}

/* constructors */
EuclideanVector::EuclideanVector(int siz) noexcept
  : size_(siz), magnitudes_(std::make_unique<double[]>(siz)) {
  for (int i = 0; i < siz; i++) {
    magnitudes_[i];
  }
}

EuclideanVector::EuclideanVector(int siz, double mag) noexcept
  : size_(siz), magnitudes_(std::make_unique<double[]>(siz)) {
  for (int i = 0; i < siz; i++) {
    magnitudes_[i] = mag;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator beg,
                                 std::vector<double>::const_iterator end) noexcept
  : size_(std::distance(beg, end)), magnitudes_(std::make_unique<double[]>(end - beg)) {
  int i = 0;
  for (auto it = beg; it != end; it++) {
    magnitudes_[i++] = *it;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& oth) noexcept
  : size_(oth.size_), magnitudes_(std::make_unique<double[]>(size_)) {
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] = oth[i];
  }
}

EuclideanVector::EuclideanVector(EuclideanVector&& oth) noexcept
  : size_(oth.size_), magnitudes_(std::move(oth.magnitudes_)) {
  oth.size_ = 0;
}

/* enemies */
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& oth) noexcept {
  size_ = oth.size_;
  magnitudes_ = std::make_unique<double[]>(size_);

  for (int i = 0; i < size_; i++) {
    magnitudes_[i] = oth[i];
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& oth) noexcept {
  size_ = oth.size_;
  magnitudes_ = std::move(oth.magnitudes_);
  return *this;
}

double& EuclideanVector::operator[](unsigned i) noexcept {
  assert(static_cast<int>(i) < size_);
  return magnitudes_[i];
}

double EuclideanVector::operator[](unsigned i) const noexcept {
  assert(static_cast<int>(i) < size_);
  return magnitudes_[i];
}

EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& oth) {
  if (size_ != oth.size_) {
    throw euclideanDimensionError(*this, oth);
  }
  for (int i = 0; i < size_; i++) {
    magnitudes_[i] += oth[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& oth) {
  if (this->size_ != oth.size_) {
    throw euclideanDimensionError(*this, oth);
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
    throw EuclideanVectorError("Invalid vector division by 0");
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
    throw euclideanDimensionError(a, b);
  }
  EuclideanVector ret(a);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] + b[i];
  }
  return ret;
}

EuclideanVector operator-(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    throw euclideanDimensionError(a, b);
  }
  EuclideanVector ret(a);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] - b[i];
  }
  return ret;
}

double operator*(const EuclideanVector& a, const EuclideanVector& b) {
  if (a.size_ != b.size_) {
    throw euclideanDimensionError(a, b);
  }
  double ret = 0;
  for (int i = 0; i < a.size_; i++) {
    ret += a[i] * b[i];
  }
  return ret;
}

EuclideanVector operator*(const EuclideanVector& a, const double& b) noexcept {
  EuclideanVector ret(a);
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
  EuclideanVector ret(a);
  for (int i = 0; i < a.size_; i++) {
    ret[i] = a[i] / b;
  }
  return ret;
}

/* methods */
double EuclideanVector::at(int ind) const {
  if (ind < 0 || ind >= size_) {
    throw EuclideanVectorError(static_cast<std::string>("Index ") + std::to_string(ind) +
                               " is not valid for this EuclideanVector object");
  }
  return magnitudes_[ind];
}

double& EuclideanVector::at(int ind) {
  if (ind < 0 || ind >= size_) {
    throw EuclideanVectorError(static_cast<std::string>("Index ") + std::to_string(ind) +
                               " is not valid for this EuclideanVector object");
  }
  return magnitudes_[ind];
}

int EuclideanVector::GetNumDimensions() const noexcept {
  return size_;
}

double EuclideanVector::GetEuclideanNorm() const {
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

EuclideanVector EuclideanVector::CreateUnitVector() const {
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

