#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/parser.c"

options_t options;

void setUp(void)
{
    init_options(&options);
}

void tearDown(void)
{
}

void test_ltu(void)
{
    parse_flags((char *[]){"-ltu"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(LIST_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_TRUE(options.ll_settings.show_extra_data);
    TEST_ASSERT_EQUAL_MESSAGE(ACCESS_TIMESTAMP, options.ll_settings.show_timestamp, "Wrong timestamp for long list!");
    TEST_ASSERT_EQUAL_MESSAGE(BY_ACCESS_TIME, options.sort_by, "Sort by is wrong!");
}

void test_lut(void)
{
    // -t should not override -u
    parse_flags((char *[]){"-lut"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(LIST_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_TRUE(options.ll_settings.show_extra_data);
    TEST_ASSERT_EQUAL_MESSAGE(ACCESS_TIMESTAMP, options.ll_settings.show_timestamp, "Wrong timestamp for long list!");
    TEST_ASSERT_EQUAL_MESSAGE(BY_ACCESS_TIME, options.sort_by, "Sort by is wrong!");
}

void test_flut(void)
{
    // -f should be overriden by rest
    parse_flags((char *[]){"-flut"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(LIST_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_TRUE(options.ll_settings.show_extra_data);
    TEST_ASSERT_EQUAL_MESSAGE(BY_ACCESS_TIME, options.sort_by, "Sort by is wrong!");
}

void test_lftc(void)
{
    // -f overrides -l, but -tc overrides -f
    parse_flags((char *[]){"-lftc"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(TABULAR_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_FALSE(options.colorful_output);
    TEST_ASSERT_EQUAL_MESSAGE(BY_CHANGE_TIME, options.sort_by, "Sort by is wrong!");
}

void test_ltfu(void)
{
    // -f overrides everything
    parse_flags((char *[]){"-ltfu"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(TABULAR_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_FALSE(options.colorful_output);
    TEST_ASSERT_EQUAL_MESSAGE(NO_SORT, options.sort_by, "Sort by is wrong!");
}

void test_tflu(void)
{
    // -f overrides everything except -l
    parse_flags((char *[]){"-tflu"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(LIST_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_EQUAL_MESSAGE(ACCESS_TIMESTAMP, options.ll_settings.show_timestamp, "Wrong timestamp for long list!");
    TEST_ASSERT_FALSE(options.colorful_output);
    TEST_ASSERT_EQUAL_MESSAGE(NO_SORT, options.sort_by, "Sort by is wrong!");
}

void test_lctf(void)
{
    int a = -123;
    printf("%d", DIGIT_COUNT(a));
    // -f overrides everything
    parse_flags((char *[]){"-lctf"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(TABULAR_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_FALSE(options.colorful_output);
    TEST_ASSERT_EQUAL_MESSAGE(NO_SORT, options.sort_by, "Sort by is wrong!");
}

void test_c(void)
{
    // No sort option defined, -c should be sort option
    parse_flags((char *[]){"-c"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(TABULAR_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_EQUAL_MESSAGE(BY_CHANGE_TIME, options.sort_by, "Sort by is wrong!");
}

void test_fc(void)
{
    // -c cannot override -f
    parse_flags((char *[]){"-fc"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(TABULAR_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_EQUAL_MESSAGE(NO_SORT, options.sort_by, "Sort by is wrong!");
} 

void test_fA(void)
{
    // -A overrides -f
    parse_flags((char *[]){"-fA"}, 1, &options);

    TEST_ASSERT_FALSE(options.colorful_output);

    TEST_ASSERT_TRUE(options.show_hidden_files);
    TEST_ASSERT_FALSE(options.show_curr_prev_dirs);
}

void test_Af(void)
{
    // -f overrides -A
    parse_flags((char *[]){"-Af"}, 1, &options);

    TEST_ASSERT_FALSE(options.colorful_output);

    TEST_ASSERT_TRUE(options.show_hidden_files);
    TEST_ASSERT_TRUE(options.show_curr_prev_dirs);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_ltu);
    RUN_TEST(test_lut);
    RUN_TEST(test_flut);
    RUN_TEST(test_lftc);
    RUN_TEST(test_ltfu);
    RUN_TEST(test_tflu);
    RUN_TEST(test_lctf);

    RUN_TEST(test_c);
    RUN_TEST(test_fc);

    RUN_TEST(test_Af);
    RUN_TEST(test_fA);

    return UNITY_END();
}
