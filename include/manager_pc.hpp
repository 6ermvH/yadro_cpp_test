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
  explicit ManagerPC(std::size_t num_computers, std::uint32_t price_per_hour);
  ~ManagerPC() = default;

  void assign(std::size_t pc_id, user_id_t user_id, utils::Time start_time);
  void release(user_id_t user_id,
                 utils::Time end_time);
  std::size_t get_free_pc() const;
  bool has_free_pc() const;  // -> count() > used_pc_
  std::size_t count_pc() const;
  
  std::pair<std::uint32_t, utils::Time> get_stats_pc(std::size_t pc_id) const;

 private:
  struct PC {
    utils::Time start_time;
    std::optional<user_id_t> id;

    std::uint32_t result_revenue;
    utils::Time result_tm;

    bool is_used() const;
  };

  std::vector<PC> computers_;
  std::uint32_t price_per_hour_;
  std::size_t used_pc_;

  void _clean_pc(std::size_t pc_id);
};

#endif  // !MANAGER_PC_HPP
