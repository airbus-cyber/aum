# AUM: All Ur Mocks are belong to us

## Introduction

AUM is a library that lets you easily write and execute unit tests in C with mocks.

## Installation

You can install the prebuilt debian or rpm package. If you prefer, you can also build from source.

### Debian package

```bash
sudo apt install ./aum_$VERSION.deb
```

### RPM package

```bash
sudo yum install aum-$VERSION-$RELEASE.x86_64.rpm
```

### Building from source

```bash
./configure
make
make test
sudo make install
ldconfig
```

## Usage

### First test suite

Create file `test.c` with this content:

```c
#include <aum.h>

AUM_TEST(AUM_FAIL__should_fail)
{
  AUM_FAIL("Voluntary test failure\n");
}

AUM_TEST_SUITE(first_suite, &AUM_FAIL__should_fail);

AUM_MAIN_RUN(&first_suite);
```

Then compile, link and execute:
```bash
$ gcc -c test.c -o test.o
$ gcc test.o -o test.out -laum
$ ./test.out
```

This should run the test suite and report that 1 test fails. Indeed we purposedly used assert `AUM_FAIL`. The list of all asserts provided by AUM can be found in header aum/asserts.h.


### First mock

This section explains how to declare and use a mock.
Create file `test_with_mock.c` with this content:
```c
#include <aum.h>
#include <aum_mock_create.h>
#include <stdlib.h>

AUM_MOCK_CREATE(void *, malloc, size_t);

AUM_TEST(aum_mock_will_return__should_set_return_code)
{
  aum_mock_will_return("malloc", 0);

  char *result = malloc(10 * sizeof(char));
  AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
}

AUM_TEST_SUITE(suite_with_mock, &aum_mock_will_return__should_set_return_code);

AUM_MAIN_RUN(&suite_with_mock);
```

Next, compile, link and execute the test suite as follows:
```bash
$ gcc -c test_with_mock.c -o test_with_mock.o
$ gcc test_with_mock.o -o test_with_mock.out -laum -Wl,-wrap,malloc
$ ./test_with_mock.out
```

Option `-Wl,-wrap,malloc` is required. It tells the linker to transfer all calls to `malloc` to function `__wrap_malloc` instead. This is the core technique that lets AUM intercept and redefine the behavior of mocked functions.

There are two steps when using mocks:
* declaration,
* exploitation

To declare a mock use macro `AUM_MOCK_CREATE`. It expects the return type, function name followed by each parameter type.:
```c
AUM_MOCK_CREATE(void *, malloc, size_t);
```

The mock can then be used in the code of each test to interact with the mocked function in two ways:
* to redefine its behaviour,
* to check how it was called.

In the example, function `malloc` is made to return `0` when called:
```c
  aum_mock_will_return("malloc", 0);
```

In the end of the test, we check that `malloc` was called with `10`:
```c
  AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
```

The mock declaration API is defined in header aum_mock_create.h. 
Header aum.h includes everything necessary to use mocks. It is split into:
* aum/mock.h contains the functions that control the behaviour of mocked functions,
* aum/asserts.h contains the list of assertions.


### Xunit report for continuous integration

You may want to execute your test suite during continuous integration. To present the result, Jenkins will then need to input the test report in the xunit format.

In order to generate this report, call the compiled test program with option `-o` to choose the path to the report:
```bash
$ ./test.out -o aum_test_results.xml
```

## Test suites organization

When dealing with larger test suites, we recommend to split your code into three types of files:
* collections of mock declarations,
* test suites,
* the test runner.

A mock collection groups mock declarations (macro `AUM_MOCK_CREATE`) for a given header (for instance `stdlib.h`). It is written once and can be reused in different projects, every time any function provided by the header needs to be mocked.

A test suite contains several tests (macro `AUM_TEST`). It exports a function (declared with macro `AUM_TEST_SUITE`) to register them in the test runner.

The test runner executes all the test suites registered with macro `AUM_MAIN_RUN`. For the time being, it accepts only one option (`-o`) which turns on xunit report generation.

## Known limitations

These limitations result from the technique used to intercept calls to mocked functions, the `-wrap` linker option:
* the linker does not reroute calls between functions belonging to the same compilation unit. Hence, it is not possible to mock calls to a function that belongs to the same module as the caller.
* it is recommended to compile unit tests without any optimisation (`-O0` option). In fact, some optimisations remove unnecessary calls or replace a function call by another. For instance, a call to `malloc` followed by `free` can be removed by the compiler. Similarly, a call to `malloc` followed by `memset` to `0` can be automatically replaced by a call to `calloc`.
* AUM does not handle variadic functions at all. So, functions like `printf` with a varying number of arguments can not be mocked. In such cases, there are two strategies. You can either wrap the variadic function or, on the contrary, extract its core implementation into another function with a `va_list` as its last argument. In the latter case, the variadic version can still be kept: it will simply converts its arguments into a `va_list` to then call this new function. For more details, see: http://c-faq.com/varargs/handoff.html.
* when a mocked function with a `va_list` argument is called, the `va_list` argument is not stored. So, for these functions, macros `AUM_ASSERT_WAS_CALLED_WITH` and `AUM_ASSERT_WAS_CALLED_WITH_AT` will not work as expected.
* when declaring a mock with macro `AUM_MOCK_CREATE` be extra vigilant that the number and argument types correspond to the mocked function signature. In theory, `AUM_MOCK_CREATE` is written so that the compiler signals an error otherwise. In practice, there may still be cases where you end up with weird errors which pop only during tests run.

## Meanings of AUM

The library name is a reference to an old video game with this phrase: [All your base are belong to us](https://en.wikipedia.org/wiki/All_your_base_are_belong_to_us).
At the same time, AUM stands for **Airbus Unit tests with Mocks for C**.


