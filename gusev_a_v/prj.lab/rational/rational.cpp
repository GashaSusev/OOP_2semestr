#include "rational.hpp"
#include <iostream>
#include <string>
#include <numeric>

Rational::Rational(const int32_t num) noexcept {
  num_ = num;
  den_ = 1;
}

Rational::Rational(const int32_t num, const int32_t denom) {
  if (denom == 0) {
    throw "Division by zero";
  }
  num_ = num;
  den_ = denom;
  normalize();
}

bool Rational::operator==(const Rational& rhs) const noexcept {
  return num() == rhs.num() && denom() == rhs.denom();
}

bool Rational::operator!=(const Rational& rhs) const noexcept {
  return !(*this == rhs);
}

bool Rational::operator>(const Rational& rhs) const noexcept {
  return num() * rhs.denom() > rhs.num() * denom();
}

bool Rational::operator<(const Rational& rhs) const noexcept {
  return num() * rhs.denom() < rhs.num() * denom();
}

bool Rational::operator>=(const Rational& rhs) const noexcept {
  return !(*this < rhs);
}
bool Rational::operator<=(const Rational& rhs) const noexcept {
  return !(*this > rhs);
}

Rational Rational::operator-() const noexcept {
  return { -this->num(), this->denom() };
}

Rational::operator bool() const noexcept {
  return this->num() != 0 && this->denom() != 0;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
  return *this = Rational(this->num() * rhs.num(), this->denom() * rhs.denom());
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
  return *this = Rational(num() * rhs.denom() + rhs.num() * denom(), denom() * rhs.denom());
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
  return *this = *this + (-rhs);
}

Rational& Rational::operator/=(const Rational& rhs) {
  return *this = Rational(this->num() * rhs.denom(), this->denom() * rhs.num());
}

Rational& Rational::operator*=(const int& rhs) noexcept {
  *this *= Rational(rhs);
}
Rational& Rational::operator+=(const int& rhs) noexcept {
  *this += Rational(rhs);
}
Rational& Rational::operator-=(const int& rhs) noexcept {
  *this -= Rational(rhs);
}
Rational& Rational::operator/=(const int& rhs) {
  *this /= Rational(rhs);
}

void Rational::normalize() noexcept {
  int g = std::gcd(std::abs(num_), std::abs(den_));
  num_ /= g;
  den_ /= g;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
  int a, b;
  char c;
  istrm >> a >> c >> b;
  rhs = Rational(a, b);
  return istrm;
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r) noexcept {
  return ostr << std::to_string(r.num()) << '/' << std::to_string(r.denom());
}
