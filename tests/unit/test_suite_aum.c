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


#include <aum.h>
#include <test_suites.h>

// note: it is problematic to test aum with aum => some cases will not work...
AUM_TEST_IGNORE(aum_run__should_return_AUM_SUCCESS_on_success)
{
    aum_runner_t *aum = aum_runner_create();
    bool result = aum_runner_execute_tests(aum);
    AUM_ASSERT_EQUAL(true, result);
    aum_runner_destroy(aum);
}

AUM_TEST_SUITE(test_suite_aum,
               &aum_run__should_return_AUM_SUCCESS_on_success
);
