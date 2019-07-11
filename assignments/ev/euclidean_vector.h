// Copyright [2019] Vincent Chen
#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <memory>
#include <string>
#include <vector>
#include <list>

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
    EuclideanVector(EuclideanVector&& o) noexcept;

    ~EuclideanVector() noexcept = default;

    double& operator[](unsigned) noexcept;
    double operator[](unsigned) const noexcept;
    EuclideanVector& operator+=(const EuclideanVector&);
    EuclideanVector& operator-=(const EuclideanVector&);
    EuclideanVector& operator*=(const double) noexcept;
    EuclideanVector& operator/=(const double);
    explicit operator std::vector<double>() noexcept;
    explicit operator std::list<double>() noexcept;

    friend std::ostream& operator<<(std::ostream& os,
                                     const EuclideanVector& v) noexcept;
    friend bool operator==(const EuclideanVector&,
                                     const EuclideanVector&) noexcept;
    friend bool operator!=(const EuclideanVector&,
                                     const EuclideanVector&) noexcept;
    friend EuclideanVector operator+(const EuclideanVector&,
                                     const EuclideanVector&);
    friend EuclideanVector operator-(const EuclideanVector&,
                                     const EuclideanVector&);
    friend EuclideanVector operator*(const EuclideanVector&,
                                     const EuclideanVector&);
    friend EuclideanVector operator*(const EuclideanVector&,
                                     const double&) noexcept;
    friend EuclideanVector operator*(const double&,
                                     const EuclideanVector&) noexcept;
    friend EuclideanVector operator/(const EuclideanVector&,
                                     const double&);

    double at(int) const;
    double& at(int);
    int GetNumDimensions() noexcept;
    double GetEuclideanNorm();
    EuclideanVector CreateUnitVector();

  private:
    // Private parts
    std::unique_ptr<double[]> magnitudes_;
    int size_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
