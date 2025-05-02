#ifndef MANAGER_PC_HPP
#define MANAGER_PC_HPP

#include <queue>
#include <vector>

#include "config.hpp"

class ManagerPC {
public:
  explicit ManagerPC(std::size_t num_computers);
  ~ManagerPC() = default;

  void assign(std::size_t pc_id, user_id_t user_id);
  void release(std::size_t pc_id);
  std::size_t get_free_pc();
  std::size_t count() const;

private:
  struct PC {
    std::optional<user_id_t> id;

    bool is_used() const;
  };

  std::vector<PC> computers_;
};

#endif // !MANAGER_PC_HPP
