#include "event.hpp"

#include <iostream>
#include <utility>

#include "errors.hpp"

Event::Event(std::shared_ptr<Club> club, utils::Time time, std::size_t id,
             std::string name)
    : club_(std::move(club)),
      time_point_(time),
      id_(id),
      name_(std::move(name)) {}

auto operator<<(std::ostream& os, const Event& ev) -> std::ostream& {
  ev.print(os);
  return os;
}

// ClientComeIn

ClientComeIn::ClientComeIn(std::shared_ptr<Club> club, utils::Time time,
                           std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

auto ClientComeIn::handle() const -> std::unique_ptr<Event> {
  try {
    club_->add_user(time_point_, name_);
  } catch (const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientShallNotPass) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
    if (e.code() == ErrorCode::NotOpenYet) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  return nullptr;
}

void ClientComeIn::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' << id_ << ' ' << name_;
}

// ClientComeIn

// ClientUsePC

ClientUsePC::ClientUsePC(std::shared_ptr<Club> club, utils::Time time,
                         std::size_t id, const std::string& name,
                         std::size_t pc_id)
    : Event(club, time, id, name), pc_id_(pc_id) {}

auto ClientUsePC::handle() const -> std::unique_ptr<Event> {
  try {
    club_->use_user_pc(time_point_, name_, pc_id_);
  } catch (const ErrorClub& e) {
    if (e.code() == ErrorCode::PlaceIsBusy) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
    if (e.code() == ErrorCode::ClientUnknown) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  return nullptr;
}

void ClientUsePC::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' << id_ << ' ' << name_ << ' '
     << pc_id_ + 1;
}

// ClientUsePC

// ClientWait

ClientWait::ClientWait(std::shared_ptr<Club> club, utils::Time time,
                       std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

auto ClientWait::handle() const -> std::unique_ptr<Event> {
  try {
    club_->add_user_wait(time_point_, name_);
  } catch (const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientCantWaitLonger) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
    if (e.code() == ErrorCode::FullWaitQueue) {
      return std::make_unique<ClientLeave>(club_, time_point_, 11, name_);
    }
  }
  return nullptr;
}

void ClientWait::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' << id_ << ' ' << name_;
}

// ClientWait

// ClientLeave

ClientLeave::ClientLeave(std::shared_ptr<Club> club, utils::Time time,
                         std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

auto ClientLeave::handle() const -> std::unique_ptr<Event> {
  try {
    club_->remove_user(time_point_, name_);
  } catch (const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientUnknown) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  std::string username = club_->get_waited_user();
  if (!username.empty() && club_->has_free_pc()) {
    club_->pop_waited_user();
    return std::make_unique<ClientUsePC>(club_, time_point_, 12, username,
                                         club_->get_free_pc());
  }
  return nullptr;
}

void ClientLeave::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' << id_ << ' ' << name_;
}

// ClientLeave

// ErrorEvent

ErrorEvent::ErrorEvent(std::shared_ptr<Club> club, utils::Time time,
                       std::size_t id, const std::string& error_text)
    : Event(club, time, id, error_text) {}

auto ErrorEvent::handle() const -> std::unique_ptr<Event> { return nullptr; }

void ErrorEvent::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' << id_ << ' ' << name_;
}

// ErrorEvent
