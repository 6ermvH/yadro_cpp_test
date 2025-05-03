#ifndef TIME_HPP
#define TIME_HPP

#include <string>

#include "config.hpp"

using hour_t = std::uint32_t;
using minute_t = std::uint32_t;

class Time {
 public:
  Time(hour_t hour = 0, minute_t minute = 0);
  explicit Time(const std::string& time_str,
                const std::string& format = "HH:MM");
  Time(const Time& other) = default;
  Time& operator=(const Time& other) = default;

  bool operator==(const Time& other) const;
  bool operator!=(const Time& other) const;
  bool operator<(const Time& other) const;
  bool operator<=(const Time& other) const;
  bool operator>(const Time& other) const;
  bool operator>=(const Time& other) const;

  std::string to_string() const;

  hour_t get_hour() const;

  friend Time duration(const Time& start, const Time& end);

 private:
  minute_t minute_;
};

#endif  // !TIME_HPP
