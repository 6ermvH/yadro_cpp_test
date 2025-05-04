#include "manager_user.hpp"

#include <gtest/gtest.h>

#include "errors.hpp"

TEST(ManagerUserBase, Add) {
  {
    ManagerUser manager;
    EXPECT_FALSE(manager.has_user("German"));
    manager.add("German", 123);
    EXPECT_TRUE(manager.has_user("German"));
    EXPECT_FALSE(manager.has_user("Anthon"));
    EXPECT_FALSE(manager.has_user("german"));
    EXPECT_EQ(manager.get_user_id("German"), 123);
  }
  {
    ManagerUser manager;
    manager.add("German", 123);
    EXPECT_THROW(manager.add("German", 123), ErrorClub);
    EXPECT_THROW(manager.add("German", 321), ErrorClub);
  }
}

TEST(ManagerUserBase, remove) {
  {
    ManagerUser manager;
    EXPECT_FALSE(manager.has_user("German"));
    manager.add("German", 123);
    EXPECT_TRUE(manager.has_user("German"));
    manager.remove("German");
    EXPECT_FALSE(manager.has_user("German"));
  }
  {
    ManagerUser manager;
    EXPECT_FALSE(manager.has_user("German"));
    EXPECT_THROW(manager.remove("German"), ErrorClub);
  }
}

TEST(ManagerUserBase, Wait) {
  {
    ManagerUser manager;
    manager.add("German", 123);
    manager.wait("German");
    EXPECT_EQ(manager.get_waited_user(), 123);
    EXPECT_EQ(manager.count_waited(), 1);
    EXPECT_NO_THROW(manager.pop_waited_user());
  }
  {
    ManagerUser manager;
    manager.add("German", 123);
    manager.add("Anthon", 111);
    manager.wait("German");
    manager.wait("Anthon");
    EXPECT_EQ(manager.count_waited(), 2);
    EXPECT_EQ(manager.get_waited_user(), 123);
    EXPECT_NO_THROW(manager.pop_waited_user());
    EXPECT_EQ(manager.get_waited_user(), 111);
    EXPECT_NO_THROW(manager.pop_waited_user());
    EXPECT_THROW(manager.pop_waited_user(), ErrorClub);
  }
}

TEST(ManagerUserBase, Complex) {
  {
    ManagerUser manager;
    manager.add("German", 123);
    manager.add("Anthon", 111);
    manager.wait("German");
    manager.wait("Anthon");

    manager.remove("Anthon");

    EXPECT_EQ(manager.get_waited_user(), 123);
    EXPECT_NO_THROW(manager.pop_waited_user());
    EXPECT_THROW(manager.get_waited_user(), ErrorClub);
  }
  {
    ManagerUser manager;
    manager.add("German", 123);
    manager.add("Anthon", 111);
    manager.wait("German");
    manager.wait("Anthon");

    manager.remove("German");

    EXPECT_EQ(manager.get_waited_user(), 111);
    EXPECT_NO_THROW(manager.pop_waited_user());
    EXPECT_THROW(manager.get_waited_user(), ErrorClub);
  }
}

TEST(ManagerUserBase, GetUserName) {
  ManagerUser manager;
  manager.add("German", 123);
  manager.add("Anthon", 456);
  EXPECT_EQ(manager.get_user_name(123), "German");
  EXPECT_EQ(manager.get_user_name(456), "Anthon");
  EXPECT_THROW(manager.get_user_name(789), ErrorClub);
}

TEST(ManagerUserBase, GetUserIdThrows) {
  ManagerUser manager;
  EXPECT_THROW(manager.get_user_id("Ghost"), ErrorClub);
}

