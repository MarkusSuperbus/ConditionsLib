#include <gtest/gtest.h>

#include "ConditionsLib/VectorialBooleanFunction.hpp"
#include "ConditionsLib/enumeration_algorithm/MinLeaves.hpp"
#include "utils/Cons.hpp"

namespace testing {

using namespace testing::utils;

void testStartSearch(VectorialBooleanFunction function,
                     Cons::ConsPtr expected) {
  auto result = Cons::FromVbf(MinLeaves::StartSearch(function));
  EXPECT_EQ(*result, *expected);
}

TEST(MinLeavesTest, StartSearch_1DFunctionIsStump_FindsStump) {
  testStartSearch({{1, 0}, 1, 1}, cons(1, leaf(1), leaf(0)));
}

TEST(MinLeavesTest, StartSearch_2DFunctionIsStump_FindsStump) {
  testStartSearch({{0, 0, 1, 1}, 2, 1}, cons(2, leaf(0), leaf(1)));
}

} // namespace testing
