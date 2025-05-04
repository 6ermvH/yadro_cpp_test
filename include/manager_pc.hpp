#ifndef MANAGER_PC_HPP
#define MANAGER_PC_HPP

#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

#include "config.hpp"
#include "time.hpp"

class ManagerPC {
 public:
  explicit ManagerPC(std::size_t num_computers);
  ~ManagerPC() = default;

  void assign(std::size_t pc_id, user_id_t user_id, Time start_time);
  std::pair<hour_t, std::size_t> release(user_id_t user_id,
                 Time end_time);
  std::size_t get_free_pc();
  bool has_free_pc() const;  // -> count() > used_pc_

 private:
  struct PC {
    Time start_time;
    std::optional<user_id_t> id;

    bool is_used() const;
  };

  std::vector<PC> computers_;
  std::size_t used_pc_;

  void _clean_pc(std::size_t pc_id);
};

#endif  // !MANAGER_PC_HPP
