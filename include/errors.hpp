#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>
#include <string>

enum class ErrorCode {
  ClientShallNotPass,
  NotOpenYet,
  PlaceIsBusy,
  ClientUnknown,
  ClientCantWaitLonger,
  FullWaitQueue,
  EmptyWaitQueue
};

class ErrorClub : public std::exception {
 public:
  explicit ErrorClub(ErrorCode code) : code_(code) {}

  const char* what() const noexcept override {
    switch (code_) {
      case ErrorCode::ClientShallNotPass:
        return "YouShallNotPass";
      case ErrorCode::NotOpenYet:
        return "NotOpenYet";
      case ErrorCode::PlaceIsBusy:
        return "PlaceIsBusy";
      case ErrorCode::ClientUnknown:
        return "ClientUnknown";
      case ErrorCode::ClientCantWaitLonger:
        return "ICanWaitNoLonger!";
      case ErrorCode::FullWaitQueue:
        return "Waiting order is full";
      case ErrorCode::EmptyWaitQueue:
        return "Waiting order is empty";
      default:
        return "Unknown error";
    }
  }

  ErrorCode code() const noexcept { return code_; }

 private:
  ErrorCode code_;
};

#endif  // !ERROR_HPP
