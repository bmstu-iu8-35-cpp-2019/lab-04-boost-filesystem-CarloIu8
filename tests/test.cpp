// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(Boost, init) {
  otvet("../misc");
  EXPECT_EQ(1, 2 - 1);
}
