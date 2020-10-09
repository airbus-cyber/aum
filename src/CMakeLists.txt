add_library(aum aum_asserts.c aum_mock.c aum_mock_create.c aum_test_suite.c error.c file_stream.c list.c main.c mock.c mock_call_sequence.c
                mock_library.c mock_list.c runner.c test_framework.c tests.c test_suite_list.c)

target_include_directories(aum PUBLIC ../include)
target_include_directories(aum PRIVATE include)

# TODO generating header from a template with .in extension seems the preferred way to propagate the project version into the code, do that instead...
target_compile_definitions(aum PRIVATE _AUM_VERSION="${PROJECT_VERSION}")

