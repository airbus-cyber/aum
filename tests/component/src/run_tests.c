/*
    AUM: Airbus Unit tests with Mocks for C. AUM is a unit testing framework for C that allows the easy definition and request of mocks.
    Copyright (C) 2019  Airbus Defence and Space

    You should have received a copy of the AUTHORS.md file which lists all contributors.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


/*!
 * \file
 * \brief Point d'entrée de la suite de tests unitaires
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <aum.h>
/* PKG Test Includes */
#include <test/test_suites.h>

typedef struct {
  char *xml_output_path;
} aum_runner_arguments_t;


static aum_runner_arguments_t *_main_parse_arguments(char *arguments[], int count) {
    aum_runner_arguments_t *result = malloc(sizeof(aum_runner_arguments_t));
    if (result == NULL) {
        return NULL;
    }

    int   option;

    while ((option = getopt(count, arguments, "o:")) != -1) {
        switch (option) {
            case 'o':
                result->xml_output_path = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-o xml_output_path]\n", arguments[0]);
                exit(EXIT_FAILURE);
        }
    }

    return result;
}

static bool _run_test_suites(aum_test_suite_t *test_suites[], int test_suites_count, aum_runner_arguments_t *arguments) {
    aum_runner_t * runner = aum_runner_create();
    if (runner == NULL) {
        return false;
    }

    for (int i = 0; i < test_suites_count; i++) {
        aum_runner_register_suite(runner, test_suites[i]);
    }

    printf("Execution of all tests\n");
    aum_runner_result_t result = aum_runner_execute_tests(runner);
    if (arguments->xml_output_path != NULL) {
        aum_runner_print_xml_report(runner, arguments->xml_output_path);
    }

    printf("\n\nExecution of a single test\n");
    aum_runner_execute_single_test(runner, "test_suite_simple", "AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer");

    aum_runner_destroy(runner);
    if (result == AUM_ERROR) {
        return false;
    }
    return true;

}

static int _main_run(char *command_line_arguments[], int command_line_arguments_count, aum_test_suite_t *test_suites[], int test_suites_count) {
    aum_runner_arguments_t *arguments = _main_parse_arguments(command_line_arguments, command_line_arguments_count);
    if (arguments == NULL) {
        return EXIT_FAILURE;
    } 

    bool success = _run_test_suites(test_suites, test_suites_count, arguments);
    free(arguments);

    if (!success) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int arguments_count, char *arguments[])
{
    aum_test_suite_t *test_suites[] = {
        &test_suite_simple,
        &test_suite_with_mock
    };
    int test_suites_count = sizeof(test_suites)/sizeof(aum_test_suite_t *);

    return _main_run(arguments, arguments_count, test_suites, test_suites_count);
}

