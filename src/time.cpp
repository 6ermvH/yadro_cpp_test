#include "time.hpp"

#include <sstream>
#include <limits>

Time::Time(hour_t hour, minute_t minute) : minute_(minute + hour * 60) {}

Time::Time(const std::string& time_str, const std::string& format) {
  if (format == "HH:MM") {
    std::istringstream ss(time_str);
    std::string hour_str, minute_str;
    std::getline(ss, hour_str, ':');
    std::getline(ss, minute_str, ':');
    hour_t hour = static_cast<hour_t>(std::stoi(hour_str));
    minute_ = static_cast<minute_t>(std::stoi(minute_str));
    minute_ += hour * 60;
  } else {
    minute_ = std::numeric_limits<minute_t>::max();
  }
}

bool Time::operator==(const Time& other) const {
  return minute_ == other.minute_;
}

bool Time::operator!=(const Time& other) const {
  return minute_ != other.minute_;
}

bool Time::operator<(const Time& other) const {
  return minute_ < other.minute_;
}

bool Time::operator<=(const Time& other) const {
  return minute_ <= other.minute_;
}

bool Time::operator>(const Time& other) const {
  return minute_ > other.minute_;
}

bool Time::operator>=(const Time& other) const {
  return minute_ >= other.minute_;
}

std::string Time::to_string() const {
  hour_t hour = minute_ / 60;
  minute_t minute = minute_ % 60;
  std::ostringstream ss;
  if (hour < 10) {
    ss << 0;
  }
  ss << static_cast<int>(hour) 
     << ":";
  if (minute < 10) {
    ss << 0;
  }
  ss << static_cast<int>(minute);
  return ss.str();
}

hour_t Time::get_hour() const {
  return static_cast<hour_t>(minute_ / 60) + 
         static_cast<hour_t>( (minute_ % 60) != 0 );
}

Time duration(const Time& start, const Time& end) {
  return Time(0, end.minute_ - start.minute_);
}
