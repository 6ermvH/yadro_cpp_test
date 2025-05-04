#include "time.hpp"

#include <limits>
#include <sstream>

namespace utils {

Time::Time(hour_t hour, minute_t minute) : minute_(minute + (hour * 60)) {}

Time::Time(const std::string& time_str, const std::string& format) {
  if (format == "HH:MM") {
    std::istringstream ss(time_str);
    std::string hour_str;
    std::string minute_str;
    std::getline(ss, hour_str, ':');
    std::getline(ss, minute_str, ':');
    auto hour = static_cast<hour_t>(std::stoi(hour_str));
    minute_ = static_cast<minute_t>(std::stoi(minute_str));
    minute_ += hour * 60;
  } else {
    minute_ = std::numeric_limits<minute_t>::max();
  }
}

auto Time::operator==(const Time& other) const -> bool {
  return minute_ == other.minute_;
}

auto Time::operator!=(const Time& other) const -> bool {
  return minute_ != other.minute_;
}

auto Time::operator<(const Time& other) const -> bool {
  return minute_ < other.minute_;
}

auto Time::operator<=(const Time& other) const -> bool {
  return minute_ <= other.minute_;
}

auto Time::operator>(const Time& other) const -> bool {
  return minute_ > other.minute_;
}

auto Time::operator>=(const Time& other) const -> bool {
  return minute_ >= other.minute_;
}

auto Time::to_string() const -> std::string {
  hour_t hour = minute_ / 60;
  minute_t minute = minute_ % 60;
  std::ostringstream ss;
  if (hour < 10) {
    ss << 0;
  }
  ss << static_cast<int>(hour) << ":";
  if (minute < 10) {
    ss << 0;
  }
  ss << static_cast<int>(minute);
  return ss.str();
}

auto Time::get_hour() const -> hour_t {
  return static_cast<hour_t>(minute_ / 60) +
         static_cast<hour_t>((minute_ % 60) != 0);
}

auto duration(const Time& start, const Time& end) -> Time {
  if (end >= start) {
    return {0, end.minute_ - start.minute_};
  }
  return {0, start.minute_ - end.minute_};
}

auto operator+(Time lhs, Time rhs) -> Time {
  return {0, lhs.minute_ + rhs.minute_};
}

auto Time::operator+=(Time tm) -> Time& {
  minute_ += tm.minute_;
  return *this;
}

}  // namespace utils
