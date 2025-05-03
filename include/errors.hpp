#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>
#include <string>

enum class ErrorCode {
  ClientShallNotPass,
  NotOpenYet,
  PlaceIsBusy,
  ClientUnknown,
  ClientCantWaitLonger
};

class ErrorClub : public std::exception {
 public:
  explicit ErrorClub(ErrorCode code) : code_(code) {}

  const char* what() const noexcept override {
    switch (code_) {
      case ErrorCode::ClientShallNotPass:
        return "Client shall not pass";
      case ErrorCode::NotOpenYet:
        return "Not open yet";
      case ErrorCode::PlaceIsBusy:
        return "Place is busy";
      case ErrorCode::ClientUnknown:
        return "Client unknown";
      case ErrorCode::ClientCantWaitLonger:
        return "Client can't wait longer";
      default:
        return "Unknown error";
    }
  }

  ErrorCode code() const noexcept { return code_; }

 private:
  ErrorCode code_;
};

#endif  // !ERROR_HPP
