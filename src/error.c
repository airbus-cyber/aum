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


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <error.h>

#define MAX_LEN 512

// TODO this method is really not nice. I am sure we can do better by propagating nicely the errors up...
void error(const char *error_message, ...)
{
    //FIXME FREE ALL ???
    // TODO factor code with test_framework_vassert
    va_list message_args;
    char    message_buffer[MAX_LEN];

    va_start(message_args, error_message);
    vsnprintf(message_buffer, MAX_LEN, error_message, message_args);
    va_end(message_args);

    fprintf(stderr, "A fatal error occured : %s\n", message_buffer);
    abort();
}
