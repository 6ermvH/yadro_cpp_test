#include "manager_pc.hpp"

#include "errors.hpp"

ManagerPC::ManagerPC(std::size_t num_computers, std::uint32_t price_per_hour)
    : computers_(num_computers), price_per_hour_(price_per_hour), used_pc_(0) {}

bool ManagerPC::PC::is_used() const { return id.has_value(); }

void ManagerPC::assign(std::size_t pc_id, user_id_t user_id, Time start_time) {
  if (computers_[pc_id].is_used()) {
    throw ErrorClub(ErrorCode::PlaceIsBusy);
  }

  computers_[pc_id].start_time = start_time;
  computers_[pc_id].id = user_id;
  ++used_pc_;
}

std::pair<hour_t, std::size_t> ManagerPC::release(user_id_t user_id, Time end_time) {
  for (std::size_t pc_id = 0; pc_id < computers_.size(); ++pc_id) {
    auto& pc = computers_[pc_id];
    if (pc.is_used() && pc.id == user_id) {
      hour_t result = duration(pc.start_time, end_time).get_hour();
      _clean_pc(pc_id);
      return {result, pc_id};
    }
  }
  throw ErrorClub(ErrorCode::ClientUnknown);
}

std::size_t ManagerPC::get_free_pc() {
  for (std::size_t i = 0; i < computers_.size(); ++i) {
    if (!computers_[i].is_used()) {
      return i;
    }
  }
  throw ErrorClub(ErrorCode::PlaceIsBusy);
}

std::pair<std::uint32_t, Time> ManagerPC::get_stats_pc(std::size_t pc_id) const {
  if (pc_id >= computers_.size()) {
    throw std::runtime_error("bad pc");
  } 
  return {computers_[pc_id].result_revenue, computers_[pc_id].result_tm};
}

bool ManagerPC::has_free_pc() const { return used_pc_ < computers_.size(); }

void ManagerPC::_clean_pc(std::size_t pc_id) {
  if (computers_[pc_id].is_used()) {
    --used_pc_;
  }
  computers_[pc_id].start_time = Time();
  computers_[pc_id].id.reset();
}

std::size_t ManagerPC::count_pc() const {
  return computers_.size();
}
