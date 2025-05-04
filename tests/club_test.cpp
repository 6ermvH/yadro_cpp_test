#include "club.hpp"

#include <gtest/gtest.h>

#include "errors.hpp"

TEST(ClubBase, Add) {
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_NO_THROW(club.add_user(Time("09:00"), "German"));
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_NO_THROW(club.add_user(Time("18:00"), "German"));
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_NO_THROW(club.add_user(Time("21:00"), "German"));
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_NO_THROW(club.add_user(Time("10:00"), "German"));
    EXPECT_THROW(club.add_user(Time("11:00"), "German"), ErrorClub);
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_THROW(club.add_user(Time("08:59"), "German"), ErrorClub);
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    EXPECT_THROW(club.add_user(Time("21:01"), "German"), ErrorClub);
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    try {
      club.add_user(Time("09:01"), "u1");
      club.add_user(Time("11:11"), "u2");
      club.add_user(Time("12:15"), "u3");
      club.add_user(Time("13:03"), "u4");
      club.add_user(Time("21:00"), "u5");
    } catch (...) {
      EXPECT_TRUE(false);
    }
  }
}

TEST(ClubBase, UsePC) {
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "German");
    EXPECT_NO_THROW(club.use_user_pc(Time("11:00"), "German", 0));
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("12:00"), "u3");
    club.add_user(Time("13:00"), "u4");
    EXPECT_NO_THROW(club.use_user_pc(Time("11:00"), "u1", 0));
    EXPECT_NO_THROW(club.use_user_pc(Time("12:00"), "u2", 1));
    EXPECT_NO_THROW(club.use_user_pc(Time("13:00"), "u3", 2));
    EXPECT_THROW(club.use_user_pc(Time("14:00"), "u4", 3), std::runtime_error);
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("12:00"), "u3");
    club.add_user(Time("13:00"), "u4");
    EXPECT_NO_THROW(club.use_user_pc(Time("11:00"), "u1", 0));
    EXPECT_NO_THROW(club.use_user_pc(Time("12:00"), "u2", 1));
    EXPECT_NO_THROW(club.use_user_pc(Time("13:00"), "u3", 2));
    EXPECT_THROW(club.use_user_pc(Time("14:00"), "u4", 2), ErrorClub);
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("11:00"), "u3");
    EXPECT_NO_THROW(club.use_user_pc(Time("11:00"), "u1", 0));
    EXPECT_NO_THROW(club.use_user_pc(Time("12:00"), "u2", 1));
    EXPECT_NO_THROW(club.use_user_pc(Time("13:00"), "u2", 2));
    EXPECT_NO_THROW(club.use_user_pc(Time("13:00"), "u3", 1));
  }
}

TEST(ClubBase, Wait) {
  {
    Club club(1, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "Anthon");
    club.add_user(Time("10:00"), "German");
    club.use_user_pc(Time("11:00"), "Anthon", 0);
    EXPECT_NO_THROW(club.add_user_wait(Time("11:00"), "German"));
  }
  {
    Club club(1, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.use_user_pc(Time("11:00"), "u1", 0);
    club.add_user(Time("10:00"), "u2");
    club.add_user(Time("10:00"), "u3");
    EXPECT_NO_THROW(club.add_user_wait(Time("18:00"), "u2"));
    EXPECT_THROW(club.add_user_wait(Time("18:00"), "u3"), ErrorClub);
  }
}

TEST(ClubBase, Remove) {
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "German");
    EXPECT_NO_THROW(club.remove_user(Time("11:00"), "German"));
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("12:00"), "u3");
    EXPECT_NO_THROW(club.remove_user(Time("11:00"), "u1"));
    EXPECT_NO_THROW(club.remove_user(Time("12:00"), "u2"));
    EXPECT_NO_THROW(club.remove_user(Time("13:00"), "u3"));
  }
}

TEST(ClubBase, Stats) {
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("12:00"), "u3");
    club.use_user_pc(Time("13:00"), "u1", 0);
    club.use_user_pc(Time("14:00"), "u2", 1);
    club.use_user_pc(Time("15:00"), "u3", 2);
    club.remove_user(Time("14:00"), "u1");
    club.remove_user(Time("15:00"), "u2");
    club.remove_user(Time("16:00"), "u3");
    EXPECT_EQ(club.get_revenue()[0].first, 10);
    EXPECT_EQ(club.get_revenue()[1].first, 10);
    EXPECT_EQ(club.get_revenue()[2].first, 10);
    EXPECT_EQ(club.get_revenue()[0].second.to_string(), "01:00");
    EXPECT_EQ(club.get_revenue()[1].second.to_string(), "01:00");
    EXPECT_EQ(club.get_revenue()[2].second.to_string(), "01:00");
  }
  {
    Club club(3, 10, Time("09:00"), Time("21:00"));
    club.add_user(Time("10:00"), "u1");
    club.add_user(Time("11:00"), "u2");
    club.add_user(Time("12:00"), "u3");
    club.use_user_pc(Time("13:00"), "u1", 0);
    club.use_user_pc(Time("14:00"), "u2", 1);
    club.use_user_pc(Time("15:00"), "u3", 2);
    club.remove_user(Time("14:01"), "u1");
    club.remove_user(Time("15:01"), "u2");
    club.remove_user(Time("16:01"), "u3");
    EXPECT_EQ(club.get_revenue()[0].first, 20);
    EXPECT_EQ(club.get_revenue()[1].first, 20);
    EXPECT_EQ(club.get_revenue()[2].first, 20);
    EXPECT_EQ(club.get_revenue()[0].second.to_string(), "01:01");
    EXPECT_EQ(club.get_revenue()[1].second.to_string(), "01:01");
    EXPECT_EQ(club.get_revenue()[2].second.to_string(), "01:01");
  }
}
