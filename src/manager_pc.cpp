#include "manager_pc.hpp"

ManagerPC::ManagerPC(std::size_t num_computers)
    : computers_(num_computers), used_pc_(0) {}

bool ManagerPC::PC::is_used() const {
  return id.has_value();
}

void ManagerPC::assign(std::size_t pc_id, user_id_t user_id, Time start_time) {
  if (computers_[pc_id].is_used()) {
    throw std::runtime_error("PC is already in use");
  }

  computers_[pc_id].start_time = start_time;
  computers_[pc_id].id = user_id;
  ++used_pc_;
}

hour_t ManagerPC::release(user_id_t user_id, Time end_time) {
  for (std::size_t pc_id = 0; pc_id < computers_.size(); ++pc_id) {
    auto& pc = computers_[pc_id];
    if (pc.is_used() && pc.id == user_id) {
      _clean_pc(pc_id);
      return duration(pc.start_time, end_time).get_hour();
    }
  }
  throw std::runtime_error("ClientUnknown");
}

std::size_t ManagerPC::get_free_pc() {
  for (std::size_t i = 0; i < computers_.size(); ++i) {
    if (!computers_[i].is_used()) {
      return i;
    }
  }
  throw std::runtime_error("No free PC available");
}

bool ManagerPC::has_free_pc() const {
  return used_pc_ < computers_.size();
}

void ManagerPC::_clean_pc(std::size_t pc_id) {
  if (computers_[pc_id].is_used()) {
    --used_pc_;
  }
  computers_[pc_id].start_time = Time();
  computers_[pc_id].id.reset();
}
