#ifndef MANAGER_PC_HPP
#define MANAGER_PC_HPP

#include <queue>
#include <vector>

#include "config.hpp"

class ManagerPC {
public:

private:
  struct PC {
    user_id_t id;
    bool is_used;
  };

  struct compare_PC {
    bool operator()(const std::unique_ptr<PC>& lhs, const std::unique_ptr<PC>& rhs) const;
  };

  std::priority_queue<std::unique_ptr<PC>,
                      std::vector<std::unique_ptr<PC>>,
                      compare_PC> computers_;
  std::vector<user_id_t> waiting_order_;
};

#endif // !MANAGER_PC_HPP
