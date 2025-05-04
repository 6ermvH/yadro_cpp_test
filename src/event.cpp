#include "event.hpp"

Event::Event(std::shared_ptr<Club> club, Time time, std::size_t id, const std::string& name)
  : club_(club), time_point_(time), id_(id), name_(name) {}

std::ostream& operator<<(std::ostream& os, const Event& ev) {
  ev.print(os);
  return os;
}

// ClientComeIn

ClientComeIn::ClientComeIn(std::shared_ptr<Club> club, Time time, 
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

void ClientComeIn::handle() const {

}


void ClientComeIn::print(std::ostream& os) const {
  os << time_point_.to_string() << ' ' 
     << id_ << ' '
     << name_;
}

// ClientComeIn

// ClientUsePC

ClientUsePC::ClientUsePC(std::shared_ptr<Club> club, Time time,
    std::size_t id, const std::string& name, std::size_t pc_id)
    : Event(club, time, id, name), pc_id_(pc_id) {}

void ClientUsePC::handle() const {
}

void ClientUsePC::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_ << ' '
     << pc_id_;
}

// ClientUsePC

// ClientWait

ClientWait::ClientWait(std::shared_ptr<Club> club, Time time,
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

void ClientWait::handle() const {
}

void ClientWait::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

// ClientWait

// ClientLeave

ClientLeave::ClientLeave(std::shared_ptr<Club> club, Time time,
    std::size_t id, const std::string& name)
    : Event(club, time, id, name) {}

void ClientLeave::handle() const {
}

void ClientLeave::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

//ClientLeave

// ErrorEvent

ErrorEvent::ErrorEvent(std::shared_ptr<Club> club, Time time,
    std::size_t id, const std::string& error_text)
    : Event(club, time, id, error_text) {}

void ErrorEvent::handle() const {
}

void ErrorEvent::print(std::ostream& os) const {
  os << time_point_.to_string() << ' '
     << id_ << ' '
     << name_;
}

// ErrorEvent
