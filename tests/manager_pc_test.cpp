#include "manager_pc.hpp"

#include <gtest/gtest.h>

#include "errors.hpp"

TEST(ManagerPCBase, AssignPC) {
  ManagerPC manager(3, 10);
  for (std::size_t pc_id = 0, user_id = 0; pc_id < 3; ++pc_id, ++user_id) {
    EXPECT_TRUE(manager.has_free_pc());
    manager.assign(pc_id, user_id, utils::Time("09:00"));
  }
  EXPECT_FALSE(manager.has_free_pc());

  EXPECT_THROW(manager.assign(0, 555, utils::Time("10:00")), ErrorClub);
}

TEST(ManagerPCBase, GetFreePC) {
  {
    ManagerPC manager(3, 10);
    EXPECT_EQ(manager.get_free_pc(), 0);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(0, 0, utils::Time("09:00"));
    EXPECT_EQ(manager.get_free_pc(), 1);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(1, 0, utils::Time("09:00"));
    EXPECT_EQ(manager.get_free_pc(), 0);
  }
  {
    ManagerPC manager(3, 10);
    manager.assign(1, 0, utils::Time("09:00"));
    manager.assign(0, 2, utils::Time("09:00"));
    manager.assign(2, 1, utils::Time("09:00"));
    EXPECT_THROW(manager.get_free_pc(), ErrorClub);
  }
}

TEST(ManagerPCBase, Release) {
  ManagerPC pc(2, 10);
  pc.assign(0, 100, utils::Time("10:00"));
  EXPECT_NO_THROW(pc.release(100, utils::Time("11:00")));
  EXPECT_TRUE(pc.has_free_pc());
  EXPECT_EQ(pc.get_free_pc(), 0);
}

TEST(ManagerPCBase, Stats) {
  ManagerPC pc(1, 20);
  pc.assign(0, 123, utils::Time("09:00"));
  pc.release(123, utils::Time("11:00"));
  auto stats = pc.get_stats_pc(0);
  EXPECT_EQ(stats.first, 40); 
  EXPECT_EQ(stats.second.to_string(), "02:00");
}

TEST(ManagerPCBase, InvalidAssign) {
  ManagerPC pc(1, 10);
  EXPECT_THROW(pc.assign(5, 999, utils::Time("10:00")), std::runtime_error);
}

TEST(ManagerPCBase, InvalidStatsAccess) {
  ManagerPC pc(1, 10);
  EXPECT_THROW(pc.get_stats_pc(2), std::runtime_error);
}

