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

#include <test_failure.h>


AUM_TEST(test_failure_create__should_not_fail)
{
    test_failure_t *subject = test_failure_create("file_name", 1, "some error message");
    AUM_ASSERT_PTR_NOT_NULL(subject);
    test_failure_destroy(subject);
}

AUM_TEST(test_failure_create__should_return_NULL__when_vasprintf_fails)
{
    aum_mock_will_return("vasprintf", -1);
    test_failure_t *subject = test_failure_create("file_name", 1, "some error message");
    AUM_ASSERT_PTR_NULL(subject);    
}

AUM_TEST_SUITE(
    test_suite_test_failure,
    &test_failure_create__should_not_fail,
    &test_failure_create__should_return_NULL__when_vasprintf_fails
);
