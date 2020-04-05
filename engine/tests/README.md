# Tests

It is advised to create as simple and as small a test function as possible, thus one has it easier to debug a failing test.
Creating more slightly differing tests is not ill-advised unless it impacts the runtime of all tests dramatically.

The following is a mwe to create your own tests:

file: `test_something.h`:
```cpp
#pragma once
#include "tests.h" // for defines and Tester class
#include the things you want to test

void TestSomething()
{
	// guard against adding tests twice
	static bool alreadyRun = false;
	if(alreadyRun) return;
	alreadyRun = true;

	using namespace Something;
	Tester::addTest([=]()
	{
		// The argument of this macro will be displayed as text when testing
		// along with the name of this file and the linenumber it is appearing in.
		// It checks wether the argument results in a bool of true/false,
		// meaning the test has or has not passed
		// and returns a test_status::TEST_OK or test_status::TEST_FAILED accordingly
		BE_TEST_ONCE(1 == (2-1));
	});

	Tester::addTest([=]()
	{
		// BE_TEST_MULTI can be used as many times as needed per test,
		// it will continue testing,
		// but it will terminate the test if the expression results in a fail
		BE_TEST_MULTI(1 != -1);
		BE_TEST_ONCE(1 == (2-1));
	});

	Tester::addTest([=]()
	{
		for(int i = 0; i < 10; ++i)
		{
			BE_TEST_MULTI(i != -1);
		}

		// BE_TEST_MULTI doesn't return upon success, only upon failure
		return test_status::TEST_OK;
	});
}
```

Then one needs to include the Header for the newly created _`TestSomething`_ in `./engine/tests/main.cpp` and call _`TestSomething()`_ such that the tests get created and added to a list to be ran when testing.

