#include "manager_pc.hpp"

#include "errors.hpp"

ManagerPC::ManagerPC(std::size_t num_computers, std::uint32_t price_per_hour)
    : computers_(num_computers), price_per_hour_(price_per_hour), used_pc_(0) {}

auto ManagerPC::PC::is_used() const -> bool { return id.has_value(); }

void ManagerPC::assign(std::size_t pc_id, user_id_t user_id,
                       utils::Time start_time) {
  if (pc_id >= computers_.size()) {
    throw std::runtime_error("bad pc");
  }
  if (computers_[pc_id].is_used()) {
    throw ErrorClub(ErrorCode::PlaceIsBusy);
  }

  computers_[pc_id].start_time = start_time;
  computers_[pc_id].id = user_id;
  ++used_pc_;
}

void ManagerPC::release(user_id_t user_id, utils::Time end_time) {
  for (std::size_t pc_id = 0; pc_id < computers_.size(); ++pc_id) {
    auto& pc = computers_[pc_id];
    if (pc.is_used() && pc.id == user_id) {
      utils::hour_t hours = duration(pc.start_time, end_time).get_hour();
      pc.result_revenue += hours * price_per_hour_;
      pc.result_tm += duration(pc.start_time, end_time);
      _clean_pc(pc_id);
      return;
    }
  }
  throw ErrorClub(ErrorCode::ClientUnknown);
}

auto ManagerPC::get_free_pc() const -> std::size_t {
  for (std::size_t i = 0; i < computers_.size(); ++i) {
    if (!computers_[i].is_used()) {
      return i;
    }
  }
  throw ErrorClub(ErrorCode::PlaceIsBusy);
}

auto ManagerPC::get_stats_pc(std::size_t pc_id) const
    -> std::pair<std::uint32_t, utils::Time> {
  if (pc_id >= computers_.size()) {
    throw std::runtime_error("bad pc");
  }
  return {computers_[pc_id].result_revenue, computers_[pc_id].result_tm};
}

auto ManagerPC::has_free_pc() const -> bool {
  return used_pc_ < computers_.size();
}

void ManagerPC::_clean_pc(std::size_t pc_id) {
  if (computers_[pc_id].is_used()) {
    --used_pc_;
  }
  computers_[pc_id].start_time = utils::Time();
  computers_[pc_id].id.reset();
}

auto ManagerPC::count_pc() const -> std::size_t { return computers_.size(); }
