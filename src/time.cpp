#include "time.hpp"

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
    throw std::invalid_argument("Unsupported format");
  }
}

bool Time::operator==(const Time& other) const {
  return minute_ == other.minute_;
}

bool Time::operator!=(const Time& other) const {
  return !(*this == other);
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
  ss << static_cast<int>(hour) 
     << ":"
     << static_cast<int>(minute);
  return ss.str();
}


