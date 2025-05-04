#include "club.hpp"
#include "errors.hpp"
#include "config.hpp"

namespace {
  user_id_t generate_user_id(const std::string& username) {
    std::hash<std::string> hash_fn;
    return hash_fn(username);
  }
}

Club::Club(std::size_t pc_count, std::uint32_t price_per_hour, Time start, Time end) 
    : start_(start), 
      end_(end),
      price_per_hour_(price_per_hour),
      manager_pc_(pc_count),
      revenue_(pc_count, 0) {}

bool Club::is_correct_time(Time time) const {
  if (time < start_ || time > end_) {
    return false;
  }
  return true;
}

void Club::add_user(Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  manager_user_.add(username, generate_user_id(username));
}

void Club::use_user_pc(Time time, const std::string& username, std::size_t pc_id) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  std::pair<hour_t, std::size_t> result = {0, 0};
  try {
    result = manager_pc_.release(manager_user_.get_user_id(username), time);
  } catch (const ErrorClub& e) {}
  manager_pc_.assign(pc_id, manager_user_.get_user_id(username), time);
  revenue_[pc_id] += result.first * price_per_hour_;
}

void Club::add_user_wait(Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  if (manager_pc_.has_free_pc()) {
    throw ErrorClub(ErrorCode::ClientCantWaitLonger);
  }
  if (revenue_.size() == manager_user_.count_waited()) {
    throw ErrorClub(ErrorCode::FullWaitQueue);
  }
  manager_user_.wait(username);
}

void Club::remove_user(Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  std::pair<hour_t, std::size_t> result = {0, 0};
  try {
    result = manager_pc_.release(manager_user_.get_user_id(username), time);
  } catch (const ErrorClub& e) {}
  manager_user_.remove(username);
  revenue_[result.second] += result.first * price_per_hour_;
}
