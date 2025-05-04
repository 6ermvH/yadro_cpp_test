#ifndef CLUB_HPP
#define CLUB_HPP

#include "manager_pc.hpp"
#include "manager_user.hpp"
#include "time.hpp"

#include <memory>

class Club {
public:
  explicit Club(std::size_t pc_count, std::uint32_t price_per_hour, Time start, Time end);

  void add_user(Time time, const std::string& username);
  void use_user_pc(Time time, const std::string& username, std::size_t pc_id);
  void add_user_wait(Time time, const std::string& username);
  void remove_user(Time time, const std::string& username);

private:
  Time start_;
  Time end_;
  std::uint32_t price_per_hour_;
  ManagerUser manager_user_;
  ManagerPC manager_pc_;
  std::vector<std::uint32_t> revenue_;

  bool is_correct_time(Time time) const;
};

#endif // !CLUB_HPP
