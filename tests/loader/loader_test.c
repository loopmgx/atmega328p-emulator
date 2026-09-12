#include "./loader_test.h"
#include "./../../include/loader.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

void loader_test(void) 
{
    byte_t arr1 [10] = {};
    assert(bin_loader(NULL, NULL, 10) == -1);
    assert(bin_loader(NULL, "./tests/loader/empty_file.bin", 10) == -1);
    assert(bin_loader(arr1, NULL, 10) == -1);

    byte_t arr2 [10] = {};
    assert(bin_loader(arr2, "./tests/loader/empty_file.bin", 10) == 0);

    byte_t arr3 [162] = {};
    assert(bin_loader(arr3, "./tests/loader/file.bin", 162) == 0);
    byte_t expected3[] =
        "```text\n"
        "Hello, this is a test file for the VM binary loader.\n"
        "1234567890\n"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
        "abcdefghijklmnopqrstuvwxyz\n"
        "!@#$%^&*()_+-=[]{};:',.<>/?\n"
        "END\n"
        "```\n";

    assert(!memcmp(arr3, expected3, sizeof(expected3) - 1));

    byte_t arr4 [161] = {};
    assert(bin_loader(arr4, "./tests/loader/file.bin", 161) == -3);
    byte_t expected4[] =
        "```text\n"
        "Hello, this is a test file for the VM binary loader.\n"
        "1234567890\n"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
        "abcdefghijklmnopqrstuvwxyz\n"
        "!@#$%^&*()_+-=[]{};:',.<>/?\n"
        "END\n"
        "```";

    assert(!memcmp(arr4, expected4, sizeof(expected4) - 1));
}
