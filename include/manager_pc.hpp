#ifndef MANAGER_PC_HPP
#define MANAGER_PC_HPP

#include <queue>
#include <vector>

#include "time.hpp"
#include "config.hpp"

class ManagerPC {
public:
  explicit ManagerPC(std::size_t num_computers);
  ~ManagerPC() = default;

  void assign(std::size_t pc_id, user_id_t user_id, Time start_time);
  hour_t release(std::size_t pc_id, Time end_time); // return duration start - end
  std::size_t get_free_pc();
  bool has_free_pc() const; // -> count() > used_pc_

private:
  struct PC {
    Time start_time;
    std::optional<user_id_t> id;

    bool is_used() const;
  };

  std::vector<PC> computers_;
  std::size_t used_pc_;
};

#endif // !MANAGER_PC_HPP
