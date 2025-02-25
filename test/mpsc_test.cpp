#include <gtest/gtest.h>

import mpsc;

TEST(MPSCQueue, BasicTest) {
    struct List {};
    mpsc::Sender<List> sender;

    EXPECT_TRUE(true); // Replace with actual tests
}
