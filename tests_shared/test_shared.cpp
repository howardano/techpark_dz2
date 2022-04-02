#include <gtest/gtest.h>
#include <math.h>

extern "C" {
    #include "generate_report.h"
}

TEST(ReportCreation, failed) {
    EXPECT_EQ(NULL, safe_malloc(0));
}