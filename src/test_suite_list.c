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


#include <test_suite_list.h>

static void _accumulate_ignored_tests_count(void *element, void *data)
{
    aum_test_suite_t *suite = (aum_test_suite_t *) element;
    int *result = (int *) data;
    *result += aum_test_suite_count_ignored_tests(suite);
}

int test_suite_list_count_ignored_tests(test_suite_list_t *this)
{
    int result = 0;
    list_iter(this, _accumulate_ignored_tests_count, &result);
    return result;
}

test_suite_list_t *test_suite_list_append(test_suite_list_t *this, aum_test_suite_t *suite)
{
    return (test_suite_list_t *) list_append(this, suite);
}

static bool _test_suite_has_name(void *element, const char *name)
{
    aum_test_suite_t *test_suite = (aum_test_suite_t *) element;
    return aum_test_suite_has_name(test_suite, name);
}

aum_test_suite_t *test_suite_list_search(test_suite_list_t *this, const char *name)
{
    return list_search(this, _test_suite_has_name, name);
}

void test_suite_list_destroy(test_suite_list_t *this)
{
    list_destroy(this);
}

