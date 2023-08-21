#include <unity.h>
#include <SerializedCommands.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_serialize_command(void) {
    uint8_t *expected = new uint8_t[3];
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x03;
    uint8_t *actual = CommandBuilder(0x0001).build();
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, 3);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    UNITY_END();
}
