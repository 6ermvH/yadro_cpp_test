#ifndef EVENT_HPP
#define EVENT_HPP

#include "club.hpp"
#include "time.hpp"

class Event {
public:
  Event(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  virtual ~Event() = default;

  virtual void handle() const;
  virtual void print(std::ostream&);
  friend operator<<(std::ostream&, const Event& );
protected:
  std::shared_ptr<Club> club_;
  Time time_point_;
  std::size_t id_;
  std::string name_;
};

class ClientComeIn : public Event {
public:
  ClientComeIn(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() override const;
  void print(std::ostream&) override;
};

class ClientUsePC : public Event {
public:
  ClientUsePC(std::shared_ptr<Club>, Time, 
              std::size_t, const std::string&, std::size_t);
  void handle() override const;
  void print(std::ostream&) override;
private:
  std::size_t pc_id_;
};

class ClienWait : public Event {
public:
  ClienWait(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() override const;
  void print(std::ostream&) override;
};

class ClientLeave : public Event {
public:
  ClientLeave(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() override const;
  void print(std::ostream&) override;
};

class ErrorEvent : public Event {
public:
  ErrorEvent(std::shared_ptr<Club>, Time, std::size_t, const std::string&);
  void handle() override const;
  void print(std::ostream&) override;
}

#endif // !EVENT_HPP
