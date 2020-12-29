// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <sstream>

#include "HashData.h"

TEST(HashData, Construct) {
  HashData hash1(2, "0555", "abvgd");

  EXPECT_TRUE(hash1.time == 2);
  EXPECT_TRUE(hash1.hash == "0555");
  EXPECT_TRUE(hash1.data == "abvgd");
}
TEST(HashData, Construct_2_0) {
  size_t time = 2;
  std::string h = "0555";
  std::string d = "abvgd";
  HashData hash1(time, h, d);
  EXPECT_EQ(hash1.time, time);
  EXPECT_EQ(hash1.data, d);
  EXPECT_EQ(hash1.hash, h);
  HashData hash2(hash1);
  EXPECT_EQ(hash1.time, hash2.time);
  EXPECT_EQ(hash1.data, hash1.data);
  EXPECT_EQ(hash1.hash, hash2.hash);
}

TEST(HashData, Correct_hash) {
  HashData hash1(2, "123213210000", "abvgd");
  EXPECT_TRUE(is_right_hash(hash1.hash));
  hash1.hash = "12321321000";
  EXPECT_FALSE(is_right_hash(hash1.hash));
}

TEST(HashData, Recording) {
  HashData hash1(2, "123213210000", "abvgd");
  std::ostringstream out;
  WriteHash(out, hash1);
  ASSERT_EQ(out.str(),
            "     {\n      \"timestamp\":  2,\n      \"hash\": "
            "\"123213210000\",\n      \"data\": \"abvgd\",\n     },\n"

  );
}
