// Copyright [2019] Vincent Chen
#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <list>
#include <memory>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  explicit EuclideanVector(int i) noexcept;
  EuclideanVector(int i, double jd) noexcept;
  EuclideanVector(std::vector<double>::const_iterator begin,
                  std::vector<double>::const_iterator end) noexcept;
  EuclideanVector(const EuclideanVector&) noexcept;
  EuclideanVector(EuclideanVector&&) noexcept;

  ~EuclideanVector() noexcept = default;

  EuclideanVector& operator=(const EuclideanVector&) noexcept;
  EuclideanVector& operator=(EuclideanVector&&) noexcept;
  double& operator[](unsigned) noexcept;
  double operator[](unsigned) const noexcept;
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(const double) noexcept;
  EuclideanVector& operator/=(const double);
  explicit operator std::vector<double>() noexcept;
  explicit operator std::list<double>() noexcept;

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept;
  friend bool operator==(const EuclideanVector&, const EuclideanVector&) noexcept;
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&) noexcept;
  friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
  friend double operator*(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator*(const EuclideanVector&, const double&)noexcept;
  friend EuclideanVector operator*(const double&, const EuclideanVector&)noexcept;
  friend EuclideanVector operator/(const EuclideanVector&, const double&);

  double at(int) const;
  double& at(int);
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

 private:
  // Private parts
  int size_;
  std::unique_ptr<double[]> magnitudes_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
