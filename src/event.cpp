#include "event.hpp"

#include "errors.hpp"


#include <iostream>

Event::Event(std::shared_ptr<Club> club, utils::Time time, std::size_t id, const std::string& name)
  : club_(club), time_point_(time), id_(id), name_(name) {}

std::ostream& operator<<(std::ostream& os, const Event& ev) {
  ev.print(os);
  return os;
}

// ClientComeIn

ClientComeIn::ClientComeIn(std::shared_ptr<Club> club, utils::Time time, 
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

std::unique_ptr<Event> ClientComeIn::handle() const {
  try {
    club_->add_user(time_point_, name_);
  } catch(const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientShallNotPass) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    } else if (e.code() == ErrorCode::NotOpenYet) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  return nullptr;
}

void ClientComeIn::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' 
     << id_ << ' '
     << name_;
}

// ClientComeIn

// ClientUsePC

ClientUsePC::ClientUsePC(std::shared_ptr<Club> club, utils::Time time,
    std::size_t id, const std::string& name, std::size_t pc_id)
    : Event(club, time, id, name), pc_id_(pc_id) {}

std::unique_ptr<Event> ClientUsePC::handle() const {
  try {
    club_->use_user_pc(time_point_, name_, pc_id_);
  } catch(const ErrorClub& e) {
    if (e.code() == ErrorCode::PlaceIsBusy) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    } else if (e.code() == ErrorCode::ClientUnknown) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  return nullptr;
}

void ClientUsePC::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_ << ' '
     << pc_id_;
}

// ClientUsePC

// ClientWait

ClientWait::ClientWait(std::shared_ptr<Club> club, utils::Time time,
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

std::unique_ptr<Event> ClientWait::handle() const {
  try {
    club_->add_user_wait(time_point_, name_);
  } catch(const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientCantWaitLonger) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    } else if (e.code() == ErrorCode::FullWaitQueue) {
      return std::make_unique<ClientLeave>(club_, time_point_, 11, name_);
    }
  }
  return nullptr;
}

void ClientWait::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

// ClientWait

// ClientLeave

ClientLeave::ClientLeave(std::shared_ptr<Club> club, utils::Time time,
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

std::unique_ptr<Event> ClientLeave::handle() const {
  try {
    club_->remove_user(time_point_, name_);
  } catch(const ErrorClub& e) {
    if (e.code() == ErrorCode::ClientUnknown) {
      return std::make_unique<ErrorEvent>(club_, time_point_, 13, e.what());
    }
  }
  std::string username = club_->get_waited_user();
  if (username != "" && club_->has_free_pc()) {
      club_->pop_waited_user();
      return std::make_unique<ClientUsePC>(club_, time_point_, 12, username, club_->get_free_pc());
  }
  return nullptr;
}

void ClientLeave::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

//ClientLeave

// ErrorEvent

ErrorEvent::ErrorEvent(std::shared_ptr<Club> club, utils::Time time,
    std::size_t id, const std::string& error_text)
    : Event(club, time, id, error_text) {}

std::unique_ptr<Event> ErrorEvent::handle() const {
  return nullptr;
}

void ErrorEvent::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

// ErrorEvent
