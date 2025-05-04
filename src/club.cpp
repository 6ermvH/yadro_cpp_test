#include "club.hpp"
#include "errors.hpp"
#include "config.hpp"

namespace {
  user_id_t generate_user_id(const std::string& username) {
    std::hash<std::string> hash_fn;
    return hash_fn(username);
  }
}

Club::Club(std::size_t pc_count, std::uint32_t price_per_hour, utils::Time start, utils::Time end) 
    : start_(start), 
      end_(end),
      manager_pc_(pc_count, price_per_hour) {}

bool Club::is_correct_time(utils::Time time) const {
  if (time < start_ || time > end_) {
    return false;
  }
  return true;
}

void Club::add_user(utils::Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  manager_user_.add(username, generate_user_id(username));
}

void Club::use_user_pc(utils::Time time, const std::string& username, std::size_t pc_id) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  try {
    manager_pc_.release(manager_user_.get_user_id(username), time);
  } catch (const ErrorClub& e) {}
  manager_pc_.assign(pc_id, manager_user_.get_user_id(username), time);
}

void Club::add_user_wait(utils::Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  if (manager_pc_.has_free_pc()) {
    throw ErrorClub(ErrorCode::ClientCantWaitLonger);
  }
  if (manager_pc_.count_pc() == manager_user_.count_waited()) {
    throw ErrorClub(ErrorCode::FullWaitQueue);
  }
  manager_user_.wait(username);
}

void Club::remove_user(utils::Time time, const std::string& username) {
  if (!is_correct_time(time)) {
    throw ErrorClub(ErrorCode::NotOpenYet);
  }
  if (!manager_user_.has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  try {
    manager_pc_.release(manager_user_.get_user_id(username), time);
  } catch (const ErrorClub& e) {}
  manager_user_.remove(username);
}

const std::vector<std::pair<std::uint32_t, utils::Time> > Club::get_revenue() const {
  std::vector<std::pair<std::uint32_t, utils::Time> > result;
  for (std::size_t i = 0; i < manager_pc_.count_pc(); ++i) {
    result.push_back(manager_pc_.get_stats_pc(i));
  }
  return result;
}

std::string Club::get_waited_user() const {
  std::string username;
  try {
  user_id_t user_id = manager_user_.get_waited_user();
  username = manager_user_.get_user_name(user_id);
  } catch (const ErrorClub& e) {
    username = "";
  }
  return username;
}

void Club::pop_waited_user() {
  manager_user_.pop_waited_user();
}

std::size_t Club::get_free_pc() const {
  return manager_pc_.get_free_pc(); 
}

bool Club::has_free_pc() const {
  return manager_pc_.has_free_pc();
}

std::vector<std::string> Club::get_users() const {
  return manager_user_.get_users();
}
