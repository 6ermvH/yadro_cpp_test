#include "event.hpp"

#include <gtest/gtest.h>
#include "errors.hpp"

TEST(Event, ClientComeIn_Success) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  ClientComeIn e(club, Time("10:00"), 1, "alice");
  EXPECT_EQ(e.handle(), nullptr);
}

TEST(Event, ClientComeIn_BeforeOpen) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  ClientComeIn e(club, Time("08:00"), 1, "bob");
  auto r = e.handle();
  EXPECT_NE(r, nullptr);
  EXPECT_NE(dynamic_cast<ErrorEvent*>(r.get()), nullptr);
}

TEST(Event, ClientUsePC_WithoutLogin) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  ClientUsePC e(club, Time("10:00"), 2, "ghost", 0);
  auto r = e.handle();
  EXPECT_NE(r, nullptr);
  EXPECT_NE(dynamic_cast<ErrorEvent*>(r.get()), nullptr);
}

TEST(Event, ClientUsePC_AfterLogin) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  club->add_user(Time("10:00"), "jack");
  ClientUsePC e(club, Time("10:01"), 3, "jack", 0);
  EXPECT_EQ(e.handle(), nullptr);
}

TEST(Event, ClientWait_Accepted) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  club->add_user(Time("09:00"), "dave");
  club->add_user(Time("09:00"), "u1");
  club->add_user(Time("09:00"), "u2");
  club->add_user(Time("09:00"), "u3");
  club->use_user_pc(Time("09:00"), "u1", 0);
  club->use_user_pc(Time("09:00"), "u2", 1);
  club->use_user_pc(Time("09:00"), "u3", 2);
  ClientWait e(club, Time("09:30"), 4, "dave");
  EXPECT_EQ(e.handle(), nullptr);
}

TEST(Event, ClientLeave_WaitedTakesPC) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  club->add_user(Time("09:00"), "a");
  club->add_user(Time("09:00"), "b");
  club->add_user(Time("09:00"), "x");
  club->add_user(Time("09:00"), "y");

  club->use_user_pc(Time("09:00"), "a", 0);
  club->use_user_pc(Time("09:00"), "x", 1);
  club->use_user_pc(Time("09:00"), "y", 2);

  club->add_user_wait(Time("09:00"), "b");

  ClientLeave e(club, Time("09:45"), 5, "a");
  auto r = e.handle();
  EXPECT_NE(dynamic_cast<ClientUsePC*>(r.get()), nullptr);
}


TEST(Event, ErrorEvent_IsTerminal) {
  auto club = std::make_shared<Club>(3, 100, Time("09:00"), Time("21:00"));
  ErrorEvent e(club, Time("10:00"), 99, "err");
  EXPECT_EQ(e.handle(), nullptr);
}

