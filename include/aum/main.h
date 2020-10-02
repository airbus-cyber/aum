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
 * \brief Interface to create the main function with the test runner
 */

#pragma once

#include <aum/test_suite.h>

int aum_main_run(char *command_line_arguments[], int command_line_arguments_count, aum_test_suite_t *test_suites[], int test_suites_count);

/*! \def AUM_MAIN_RUN(suites...)
 *
 * Creates a main function to run the suites
 */
#define AUM_MAIN_RUN(__suites...)                                                         \
    int main(int arguments_count, char *arguments[])                                      \
    {                                                                                     \
        aum_test_suite_t *test_suites[] = { __suites };                                   \
        int test_suites_count = sizeof(test_suites)/sizeof(aum_test_suite_t *);           \
                                                                                          \
        return aum_main_run(arguments, arguments_count, test_suites, test_suites_count);  \
    }

