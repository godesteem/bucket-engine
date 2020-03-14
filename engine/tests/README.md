#Tests

Following rules shall apply to new tests:
- use `BE_TEST_ASSERT` from `test.h`
- success prints to stdout using `BE_TEST_SUCCESS`
- error prints to stderr using `BE_TEST_ERROR`
- one test per class/struct/template
- module test file name equals test method name
