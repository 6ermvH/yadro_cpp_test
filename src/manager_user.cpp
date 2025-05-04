#include "manager_user.hpp"

#include "errors.hpp"

void ManagerUser::add(const std::string& username, user_id_t user_id) {
  if (has_user(username)) {
    throw ErrorClub(ErrorCode::ClientShallNotPass);
  }
  user_map_[username] = user_id;
}

void ManagerUser::wait(const std::string& username) {
  if (!has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  waiting_group_.push_back(user_map_[username]);
}

void ManagerUser::remove(const std::string& username) {
  if (!has_user(username)) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  user_id_t user_id = user_map_[username];
  waiting_group_.remove(user_id);
  user_map_.erase(username);
}

auto ManagerUser::has_user(const std::string& username) const -> bool {
  return user_map_.find(username) != user_map_.end();
}

auto ManagerUser::get_user_id(const std::string& username) const -> user_id_t {
  auto it = user_map_.find(username);
  if (it == user_map_.end()) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  return it->second;
}

auto ManagerUser::get_user_name(user_id_t user_id) const -> std::string {
  for (const auto& pair : user_map_) {
    if (pair.second == user_id) {
      return pair.first;
    }
  }
  throw ErrorClub(ErrorCode::ClientUnknown);
}

auto ManagerUser::count_waited() const -> std::size_t {
  return waiting_group_.size();
}

auto ManagerUser::get_waited_user() const -> user_id_t {
  if (waiting_group_.empty()) {
    throw ErrorClub(ErrorCode::EmptyWaitQueue);
  }
  return waiting_group_.front();
}

void ManagerUser::pop_waited_user() {
  if (waiting_group_.empty()) {
    throw ErrorClub(ErrorCode::EmptyWaitQueue);
  }
  waiting_group_.pop_front();
}

auto ManagerUser::get_users() const -> std::vector<std::string> {
  std::vector<std::string> users;
  for (const auto& pair : user_map_) {
    users.push_back(pair.first);
  }
  return users;
}
