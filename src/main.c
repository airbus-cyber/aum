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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include <runner.h>

#include <aum/main.h>


typedef struct {
  char *xml_output_path;
} _runner_arguments_t;


static _runner_arguments_t *_main_parse_arguments(char *arguments[], int count) {
    _runner_arguments_t *result = malloc(sizeof(_runner_arguments_t));
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

static bool _run_test_suites(aum_test_suite_t *test_suites[], int test_suites_count, _runner_arguments_t *arguments) {
    aum_runner_t *runner = runner_create(test_suites, test_suites_count);
    if (runner == NULL) {
        return false;
    }

    aum_runner_result_t result = runner_execute_tests(runner);
    if (arguments->xml_output_path != NULL) {
        runner_print_xml_report(runner, arguments->xml_output_path);
    }

    runner_destroy(runner);
    if (result == AUM_ERROR) {
        return false;
    }
    return true;

}


int aum_main_run(char *command_line_arguments[], int command_line_arguments_count, aum_test_suite_t *test_suites[], int test_suites_count) {
    _runner_arguments_t *arguments = _main_parse_arguments(command_line_arguments, command_line_arguments_count);
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
