#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ls_flags(void)
{
    // TEST_IGNORE(); // until we fix our code, we will ignore this test unit
    FILE *pipe;
    system("make"); // run 'make' to generate executable

    char *test_flags[] = {"-fmar", "-f1i", "-fl", "-fa", "-fla"}; // list of flags to test
    char error_msg[100];
    int flag_cnt = sizeof(test_flags) / sizeof(char *); // get the number of flags

    // Make sizes large enough to store outputs
    char ls_output[1024] = {0};
    char our_output[1024] = {0};
    char command[128];

    for (int i = 0; i < flag_cnt; ++i)
    {
        // Run original ls command and capture output
        sprintf(command, "ls folder/ %s", test_flags[i]);
        pipe = popen(command, "r");
        fread(ls_output, 1, 1024, pipe);
        pclose(pipe);

        // Run our code and capture output
        sprintf(command, "./ls %s", test_flags[i]);
        pipe = popen(command, "r");
        fread(our_output, 1, 1024, pipe);
        pclose(pipe);

        // Compare
        sprintf(error_msg, "\nFailed flag: %s", test_flags[i]);
        TEST_ASSERT_EQUAL_STRING_MESSAGE(ls_output, our_output, error_msg);
    }
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_ls_flags);

    return UNITY_END();
}
