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

#include <test_report.h>
#include <stdio.h>


static test_report_t *_subject;

AUM_TEST(dummy_test)
{
   test_failure_t *failure = test_failure_create("file_name", 0, "");
   test_report_break_on_failure(_subject, failure);
}

AUM_TEST(test_report_destroy__should_free_failure)
{
    _subject = test_report_create(&dummy_test);
    test_report_run(_subject);
    test_report_destroy(_subject);
}


AUM_TEST_SUITE(test_suite_test_report,
    &test_report_destroy__should_free_failure
);
