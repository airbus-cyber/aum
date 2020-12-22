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
 * \deprecated Use macro AUM_MAIN_RUN instead
 */

#pragma once

#include <stdbool.h>
#include <aum/test_suite.h>

/*!
 *
 * \deprecated Use macro AUM_MAIN_RUN instead
 */
typedef enum {
  AUM_SUCCESS,
  AUM_FAILURE,
  AUM_ERROR
} aum_runner_result_t;

/*!
 *
 * \deprecated Use macro AUM_MAIN_RUN instead
 */
typedef struct aum_runner_s aum_runner_t;


