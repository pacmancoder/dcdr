#include <gtest/gtest.h>
#include "fixtures/UmathTest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}