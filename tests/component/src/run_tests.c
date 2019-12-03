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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <aum.h>
/* PKG Test Includes */
#include <test/test_suites.h>

typedef struct aum_runner_arguments_s {
  char *xml_output_path;
} aum_runner_arguments_t;

#define AUM_RUNNER_ARGUMENTS_INIT ((aum_runner_arguments_t){NULL})

static void _main_parse_arguments(int argc, char **argv, aum_runner_arguments_t *arguments) {
  int   option;

  while ((option = getopt(argc, argv, "o:")) != -1) {
    switch (option) {
    case 'o':
      arguments->xml_output_path = optarg;
      break;
    default:
      fprintf(stderr, "Usage: %s [-o xml_output_path]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char **argv)
{
    aum_runner_arguments_t arguments = AUM_RUNNER_ARGUMENTS_INIT;

    _main_parse_arguments(argc, argv, &arguments);

    aum_runner_t * runner = aum_runner_create();
    if (runner == NULL) {
        return EXIT_FAILURE;
    }

    /* Appel aux fonctions d'initialisation des suites de tests */
    aum_runner_register_suite(runner, &test_suite_simple);
    aum_runner_register_suite(runner, &test_suite_with_mock);

    printf("Execution of all tests\n");
    aum_runner_result_t result = aum_runner_execute_tests(runner);
    if (arguments.xml_output_path != NULL) {
        aum_runner_print_xml_report(runner, arguments.xml_output_path);
    }

    printf("\n\nExecution of a single test\n");
    aum_runner_execute_single_test(runner, "test_suite_simple", "AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer");

    aum_runner_destroy(runner);
    if (result == AUM_ERROR) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
