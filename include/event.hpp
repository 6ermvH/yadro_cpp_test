#ifndef EVENT_HPP
#define EVENT_HPP

#include "club.hpp"
#include "time.hpp"

#include <ostream>
#include <string>
#include <memory>

class Event {
 public:
  Event(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  virtual ~Event() = default;

  virtual void handle() const;
  virtual void print(std::ostream&) const;
  friend std::ostream& operator<<(std::ostream&, const Event&);

 protected:
  std::shared_ptr<Club> club_;
  Time time_point_;
  std::size_t id_;
  std::string name_;
};

class ClientComeIn : public Event {
 public:
  ClientComeIn(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() const override;
  void print(std::ostream&) const override;
};

class ClientUsePC : public Event {
 public:
  ClientUsePC(std::shared_ptr<Club>, Time, std::size_t, const std::string&,
              std::size_t);
  void handle() const override = 0;
  void print(std::ostream&) const override = 0;

 private:
  std::size_t pc_id_;
};

class ClientWait : public Event {
 public:
  ClientWait(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() const override;
  void print(std::ostream&) const override;
};

class ClientLeave : public Event {
 public:
  ClientLeave(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() const override;
  void print(std::ostream&) const override;
};

class ErrorEvent : public Event {
 public:
  ErrorEvent(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() const override;
  void print(std::ostream&) const override;
};

#endif  // !EVENT_HPP
