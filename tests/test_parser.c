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

void test_time_sort_ll_with_t(void)
{

    parse_flags((char *[]){"-ltu"}, 1, &options);

    TEST_ASSERT_EQUAL_MESSAGE(LIST_FORMAT, options.print_style, "Print style is wrong!");
    TEST_ASSERT_TRUE(options.ll_settings.show_extra_data);
    TEST_ASSERT_EQUAL_MESSAGE(BY_ACCESS_TIME, options.sort_by, "Sort by is wrong!");


}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_time_sort_ll_with_t);

    return UNITY_END();
}
