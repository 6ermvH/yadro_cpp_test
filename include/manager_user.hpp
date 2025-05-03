#ifndef MANAGER_USER_HPP
#define MANAGER_USER_HPP

#include <list>
#include <string>
#include <unordered_map>

#include "config.hpp"

class ManagerUser {
 public:
  ManagerUser() = default;
  ~ManagerUser() = default;

  void add(const std::string& username, user_id_t user_id);
  void wait(const std::string& username);
  void remove(const std::string& username);
  bool has_user(const std::string& username) const;
  user_id_t get_waited_user() const;
  void pop_waited_user();

 private:
  std::unordered_map<std::string, user_id_t> user_map_;
  std::list<user_id_t> waiting_group_;
};

#endif  // !MANAGER_USER_HPP
