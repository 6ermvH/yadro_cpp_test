#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>
#include <ostream>
#include <string>

#include "club.hpp"
#include "time.hpp"

class Event {
 public:
  Event(std::shared_ptr<Club>, utils::Time, std::size_t, std::string);
  virtual ~Event() = default;

  virtual std::unique_ptr<Event> handle() const = 0;
  virtual void print(std::ostream&) const = 0;
  friend std::ostream& operator<<(std::ostream&, const Event&);

 protected:
  std::shared_ptr<Club> club_;
  utils::Time time_point_;
  std::size_t id_;
  std::string name_;
};

class ClientComeIn : public Event {
 public:
  ClientComeIn(std::shared_ptr<Club>, utils::Time, std::size_t,
               const std::string&);
  std::unique_ptr<Event> handle() const override;
  void print(std::ostream&) const override;
};

class ClientUsePC : public Event {
 public:
  ClientUsePC(std::shared_ptr<Club>, utils::Time, std::size_t,
              const std::string&, std::size_t);
  std::unique_ptr<Event> handle() const override;
  void print(std::ostream&) const override;

 private:
  std::size_t pc_id_;
};

class ClientWait : public Event {
 public:
  ClientWait(std::shared_ptr<Club>, utils::Time, std::size_t,
             const std::string&);
  std::unique_ptr<Event> handle() const override;
  void print(std::ostream&) const override;
};

class ClientLeave : public Event {
 public:
  ClientLeave(std::shared_ptr<Club>, utils::Time, std::size_t,
              const std::string&);
  std::unique_ptr<Event> handle() const override;
  void print(std::ostream&) const override;
};

class ErrorEvent : public Event {
 public:
  ErrorEvent(std::shared_ptr<Club>, utils::Time, std::size_t,
             const std::string&);
  std::unique_ptr<Event> handle() const override;
  void print(std::ostream&) const override;
};

#endif  // !EVENT_HPP
