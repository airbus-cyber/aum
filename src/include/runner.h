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

#pragma once

#include <aum/test_suite.h>
#include <aum/runner.h>

/*!
 * \brief Runner intialization
 *
 * \deprecated Use macro AUM_MAIN_RUN instead
 */
aum_runner_t *runner_create(aum_test_suite_t *test_suites[], int test_suites_count);

/*!
 * \brief Register test suites
 *
 * \return              true     Success
 * \return              false    Failure
 */
bool runner_register_suite(aum_runner_t *this, aum_test_suite_t *suite);

/*!
 * \brief Executes all tests
 *
 * \return              AUM_SUCCESS     All tests successful
 * \return              AUM_FAILURE     At least one test failed
 * \return              AUM_ERROR       Fatal error during the tests execution
 */
aum_runner_result_t runner_execute_tests(aum_runner_t *this);

/*!
 * \brief 
 *
 */
bool runner_print_xml_report(aum_runner_t *this, const char *path);

/*!
 * \brief 
 *
 */
void runner_destroy(aum_runner_t *this);

