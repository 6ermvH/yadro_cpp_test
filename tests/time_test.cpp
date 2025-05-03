#include "time.hpp"

#include <gtest/gtest.h>

TEST(TimeBase, Construct) {
  {
    Time t;
    EXPECT_EQ(t.to_string(), "00:00");
  }
  {
    Time t(1, 30);
    EXPECT_EQ(t.to_string(), "01:30");
  }
  {
    Time t(5, 0);
    EXPECT_EQ(t.to_string(), "05:00");
  }
  {
    Time t(10, 0);
    EXPECT_EQ(t.to_string(), "10:00");
  }
  {
    Time t(23, 59);
    EXPECT_EQ(t.to_string(), "23:59");
  }
  {
    Time t("01:30");
    EXPECT_EQ(t.to_string(), "01:30");
  }
  {
    Time t("05:00");
    EXPECT_EQ(t.to_string(), "05:00");
  }
  {
    Time t("10:00");
    EXPECT_EQ(t.to_string(), "10:00");
  }
  {
    Time t("23:59");
    EXPECT_EQ(t.to_string(), "23:59");
  }
}

TEST(TimeBase, operators) {
  // ==
  EXPECT_TRUE(Time(1, 30) == Time(1, 30));
  EXPECT_TRUE(Time() == Time(0, 0));
  EXPECT_TRUE(Time("10:59") == Time(10, 59));
  EXPECT_FALSE(Time(1, 30) == Time(2, 30));
  EXPECT_FALSE(Time() == Time(0, 1));
  EXPECT_FALSE(Time("10:58") == Time(10, 59));
  // ==

  // !=
  EXPECT_TRUE(Time(1, 30) != Time(2, 30));
  EXPECT_TRUE(Time() != Time(0, 1));
  EXPECT_TRUE(Time("10:58") != Time(10, 59));
  EXPECT_FALSE(Time(1, 30) != Time(1, 30));
  EXPECT_FALSE(Time() != Time(0, 0));
  EXPECT_FALSE(Time("10:59") != Time(10, 59));
  // !=

  // <
  EXPECT_TRUE(Time(1, 30) < Time(2, 30));
  EXPECT_TRUE(Time() < Time(0, 1));
  EXPECT_TRUE(Time("10:58") < Time(10, 59));
  EXPECT_FALSE(Time(2, 30) < Time(1, 30));
  EXPECT_FALSE(Time(0, 1) < Time());
  EXPECT_FALSE(Time("10:58") < Time(10, 57));
  // <

  // >
  EXPECT_FALSE(Time(1, 30) > Time(2, 30));
  EXPECT_FALSE(Time() > Time(0, 1));
  EXPECT_FALSE(Time("10:58") > Time(10, 59));
  EXPECT_TRUE(Time(2, 30) > Time(1, 30));
  EXPECT_TRUE(Time(0, 1) > Time());
  EXPECT_TRUE(Time("10:58") > Time(10, 57));
  // >
}

TEST(TimeBase, get_hour) {
  EXPECT_EQ(Time(1, 30).get_hour(), 2);
  EXPECT_EQ(Time(3, 0).get_hour(), 3);
  EXPECT_EQ(Time(3, 1).get_hour(), 4);
  EXPECT_EQ(Time(0, 0).get_hour(), 0);
  EXPECT_EQ(Time("10:59").get_hour(), 11);
  EXPECT_EQ(Time(23, 59).get_hour(), 24);
  EXPECT_EQ(Time(1, 1).get_hour(), 2);
}

TEST(TimeBase, duration) {
  EXPECT_EQ(duration(Time(), Time(0, 1)), Time(0, 1));
  EXPECT_EQ(duration(Time(), Time(1, 0)), Time(1, 0));
  EXPECT_EQ(duration(Time(), Time(1, 59)), Time(1, 59));
  EXPECT_EQ(duration(Time(10, 0), Time(11, 0)), Time(1, 0));
  EXPECT_EQ(duration(Time(10, 0), Time(11, 1)), Time(1, 1));
  EXPECT_EQ(duration(Time(10, 30), Time(10, 30)), Time());
  EXPECT_EQ(duration(Time(11, 0), Time(10, 0)), Time(1, 0));
  EXPECT_EQ(duration(Time(11, 1), Time(10, 0)), Time(1, 1));
}

TEST(TimeBase, Copy) {
  Time t1(10, 0);
  Time t2 = t1;
  EXPECT_EQ(t2.to_string(), "10:00");
}
