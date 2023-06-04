#include <rational/rational.hpp>

#include <iostream>
#include <string>
#include <numeric>

Rational::Rational(const int32_t num) noexcept {
  num_ = num;
  den_ = 1;
}

Rational::Rational(const int32_t num, const int32_t denom) {
  if (denom == 0) {
    throw "Error";
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
  return { -num(), denom() };
}

Rational::operator bool() const noexcept {
  return num() != 0 && denom() != 0;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
  return *this = Rational(num() * rhs.num(), denom() * rhs.denom());
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
  return *this = Rational(num() * rhs.denom() + rhs.num() * denom(), denom() * rhs.denom());
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
  return *this = *this + (-rhs);
}

Rational& Rational::operator/=(const Rational& rhs) {
  return *this = Rational(num() * rhs.denom(), denom() * rhs.num());
}

Rational& Rational::operator*=(const int& rhs) noexcept {
  return *this *= Rational(rhs);
}
Rational& Rational::operator+=(const int& rhs) noexcept {
  return *this += Rational(rhs);
}
Rational& Rational::operator-=(const int& rhs) noexcept {
  return *this -= Rational(rhs);
}
Rational& Rational::operator/=(const int& rhs) {
  return *this /= Rational(rhs);
}

void Rational::normalize() noexcept {
  int g = std::gcd(std::abs(num_), std::abs(den_));
  num_ /= g;
  den_ /= g;
  if (num_ <= 0 && den_ < 0) {
    num_ = -num_;
    den_ = -den_;
  }
  else {
    if (num_ >= 0 && den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }
  }
}

std::istream& Rational::read_from(std::istream& istrm) noexcept {
  std::string str, n1 = "", n2 = "", trash = "";
  int nm = 0, dn = 1;
  istrm >> str;
  bool fl = false;
  if (str[0] == '-') {
    n1 += '-';
  }
  for (int i = n1.size(); i < str.size(); ++i) {
    if (isdigit(str[i]) && !fl) {
      n1 += str[i];
    }
    else {
      if (str[i] == '/' && !fl && !n1.empty()) {
        fl = true;
      }
      else {
        if (isdigit(str[i]) && fl && trash.empty()) {
          n2 += str[i];
        }
        else {
          if (!n2.empty() && !isdigit(str[i])) {
            trash += str[i];
          }
          else {
            n1 = "";
            n2 = "";
            break;
          }
        }
      }
    }
  }
  if (!n1.empty() && !n2.empty()) {
    nm = std::stoi(n1);
    dn = std::stoi(n2);
    *this = Rational(nm, dn);
    istrm.setstate(std::ios_base::goodbit);
  }
  else {
    istrm.setstate(std::ios_base::failbit);
  }
  return istrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
  return rhs.read_from(istrm);
}

std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
  return ostrm << num() << '/' << denom();
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r) noexcept {
  return r.write_to(ostr);
}