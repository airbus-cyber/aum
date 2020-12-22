# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [Unreleased]

### Added
- type `aum_test_function_t`

### Changed
- signature of `aum_main_run` so that the `test_suites_count` is now an `unsigned int`

### Removed
- methods `aum_runner_create`, `aum_runner_register_suite`, `aum_runner_execute_tests`, `aum_runner_execute_single_test`, `aum_runner_print_xml_report`, `aum_runner_destroy`
- types `aum_runner_result_t`, `aum_runner_t`
- header `aum/runner.h`
- methods `aum_test_suite_count_ignored_tests`, `aum_test_suite_has_name`


## [0.10.0](https://github.com/airbus-cyber/aum/releases/tag/0.10.0)

### Added
- function `aum_mock_will_skip` configures a mock so that it does nothing when called. Applies only to mock of function with a `void` return type.


## [0.9.2](https://github.com/airbus-cyber/aum/releases/tag/0.9.2)

### Fixed
- calls to a mocked function with a `jmp_buf` argument do not fail anymore. However, the `jmp_buf` argument is not stored correctly. And so, for these functions, macros `AUM_ASSERT_WAS_CALLED_WITH` and `AUM_ASSERT_WAS_CALLED_WITH_AT` will not work as expected.


## [0.9.1](https://github.com/airbus-cyber/aum/releases/tag/0.9.1)

### Fixed
- calls to a mocked function with a `va_list` argument do not fail anymore. However, the `va_list` argument is not stored correctly. And so, for these functions, macros `AUM_ASSERT_WAS_CALLED_WITH` and `AUM_ASSERT_WAS_CALLED_WITH_AT` will not work as expected.


## [0.9.0](https://github.com/airbus-cyber/aum/releases/tag/0.9.0)

### Added
- macro AUM_MAIN_RUN to replace the hand-written main function
- README.md
- flag -Wmissing-declarations when compiling source
- target install to Makefile
- aum.pc into the RPM package

### Deprecated
- all functions in aum/runner.h in favor of macro AUM_MAIN_RUN

### Changed
- Simplified console output


## [0.8.1](https://github.com/airbus-cyber/aum/releases/tag/0.8.1)

### Fixed
- the .so was not included in the generated RPM package


## [0.8.0](https://github.com/airbus-cyber/aum/releases/tag/0.8.0)

### Added
- RPM packaging


## [0.7.0](https://github.com/airbus-cyber/aum/releases/tag/0.7.0)

### Added
- Debian packaging


## [0.6.1](https://github.com/airbus-cyber/aum/releases/tag/0.6.1)

### Fixed
- default target in Makefile was failing in the absence of the .git directory
- target `debian` was incorrectly documented in Makefile


## [0.6.0](https://github.com/airbus-cyber/aum/releases/tag/0.6.0)

### Added
- First open source release

