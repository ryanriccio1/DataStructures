#include <gtest/gtest.h>
#include <stdlib.h>
#include <cstdint>
extern "C"
{
#include "console_util.h"
}

TEST(console_util, string_to_long_withValidData_returnsSuccess)
{
    char data1[] = "123";
    char data2[] = "-124";
    int64_t result = 0;
    uint8_t isSuccess = string_to_long(data1, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(123, result);

    isSuccess = string_to_long(data2, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(-124, result);
}

TEST(console_util, string_to_long_withInvalidData_returnsFailure)
{
    char data[] = "abc";
    int64_t result = 0;
    uint8_t isSuccess = string_to_long(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_long_withDataTooLarge_returnsFailure)
{
    char data[] = "92233720368547758071";
    int64_t result = 0;
    uint8_t isSuccess = string_to_long(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_int_withValidData_returnsSuccess)
{
    char data1[] = "123";
    char data2[] = "-124";
    int32_t result = 0;
    uint8_t isSuccess = string_to_int(data1, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(123, result);

    isSuccess = string_to_int(data2, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(-124, result);
}

TEST(console_util, string_to_int_withInvalidData_returnsFailure)
{
    char data[] = "abc";
    int32_t result = 0;
    uint8_t isSuccess = string_to_int(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_int_withDataTooLarge_returnsFailure)
{
    char data[] = "21474836475";
    int32_t result = 0;
    uint8_t isSuccess = string_to_int(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_double_withValidData_returnsSuccess)
{
    char data1[] = "123.01234";
    char data2[] = "-124.01234";
    double result = 0;
    uint8_t isSuccess = string_to_double(data1, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(123.01234, result);

    isSuccess = string_to_double(data2, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ(-124.01234, result);
}

TEST(console_util, string_to_double_withInvalidData_returnsFailure)
{
    char data[] = "abc";
    double result = 0;
    uint8_t isSuccess = string_to_double(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_double_withDataTooLarge_returnsFailure)
{
    char data[] = "1797693134862315708145274237317043567980705675258449965989174768031572607800285387605895586327668781715404589535143824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032229481658085593321233482747978262041447231687381771809192998812504040261841248583680.000000";
    double result = 0;
    uint8_t isSuccess = string_to_double(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_float_withValidData_returnsSuccess)
{
    char data1[] = "123.01234";
    char data2[] = "-124.01234";
    float result = 0;
    uint8_t isSuccess = string_to_float(data1, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ((float)123.01234, result);

    isSuccess = string_to_float(data2, &result);
    EXPECT_EQ(EXIT_SUCCESS, isSuccess);
    EXPECT_EQ((float)-124.01234, result);
}

TEST(console_util, string_to_float_withInvalidData_returnsFailure)
{
    char data[] = "abc";
    float result = 0;
    uint8_t isSuccess = string_to_float(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}

TEST(console_util, string_to_float_withDataTooLarge_returnsFailure)
{
    char data[] = "3402823466385288598117041834845169254400.000000";
    float result = 0;
    uint8_t isSuccess = string_to_float(data, &result);
    EXPECT_EQ(EXIT_FAILURE, isSuccess);
    EXPECT_EQ(0, result);
}