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

bool ManagerUser::has_user(const std::string& username) const {
  return user_map_.find(username) != user_map_.end();
}

user_id_t ManagerUser::get_user_id(const std::string& username) const {
  auto it = user_map_.find(username);
  if (it == user_map_.end()) {
    throw ErrorClub(ErrorCode::ClientUnknown);
  }
  return it->second;
}

std::string ManagerUser::get_user_name(user_id_t user_id) const {
  for (const auto& pair : user_map_) {
    if (pair.second == user_id) {
      return pair.first;
    }
  }
  throw ErrorClub(ErrorCode::ClientUnknown);
}

std::size_t ManagerUser::count_waited() const {
  return waiting_group_.size();
}

user_id_t ManagerUser::get_waited_user() const {
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
