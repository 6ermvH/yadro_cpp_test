#ifndef TIME_HPP
#define TIME_HPP

#include "config.hpp"

class Time {
public:
  explicit Time(const std::string& time_str, const std::string& format = "HH:MM");
  Time(const Time& other) = default;
  Time& operator=(const Time& other) = default;

  bool operator==(const Time& other) const;
  bool operator!=(const Time& other) const;
  bool operator<(const Time& other) const;
  bool operator<=(const Time& other) const;
  bool operator>(const Time& other) const;
  bool operator>=(const Time& other) const;

  std::string to_string() const;
private:
  minute_t minute_;
}

#endif // !TIME_HPP
