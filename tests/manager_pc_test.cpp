#include "manager_pc.hpp"

#include <gtest/gtest.h>

#include "errors.hpp"

TEST(ManagerPCBase, AssignPC) {
  ManagerPC manager(3, 10);
  for (std::size_t pc_id = 0, user_id = 0; pc_id < 3; ++pc_id, ++user_id) {
    EXPECT_TRUE(manager.has_free_pc());
    manager.assign(pc_id, user_id, Time("09:00"));
  }
  EXPECT_FALSE(manager.has_free_pc());

  EXPECT_THROW(manager.assign(0, 555, Time("10:00")), ErrorClub);
}

TEST(ManagerPCBase, GetFreePC) {
  {
    ManagerPC manager(3, 10);
    EXPECT_EQ(manager.get_free_pc(), 0);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(0, 0, Time("09:00"));
    EXPECT_EQ(manager.get_free_pc(), 1);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(1, 0, Time("09:00"));
    EXPECT_EQ(manager.get_free_pc(), 0);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(1, 0, Time("09:00"));
    manager.assign(0, 2, Time("09:00"));
    manager.assign(2, 1, Time("09:00"));
    EXPECT_THROW(manager.get_free_pc(), ErrorClub);
  }
}
