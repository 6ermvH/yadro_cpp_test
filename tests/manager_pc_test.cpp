#include "manager_pc.hpp"

#include <gtest/gtest.h>

TEST(ManagerPCTest, AssignPC) {
    ManagerPC manager(5);
    Time start_time(9, 0);
    user_id_t user_id = 1;

    manager.assign(0, user_id, start_time);
    EXPECT_EQ(manager.get_free_pc(), 1);
}
