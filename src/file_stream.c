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


#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <file_stream.h>

struct file_stream_s {
    int file;
    bool status;
};

file_stream_t *file_stream_create(const char *filename)
{
    file_stream_t *this = (file_stream_t *) calloc(1, sizeof(file_stream_t));
    if (this == NULL) {
        return NULL;
    }
    int file = creat(filename, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    if (file == -1) {
        free(this);
        return NULL;
    }
    this->file = file;
    return this;
}

// TODO would it be possible to provide file_stream_write_line and append the \n?
void file_stream_write(file_stream_t *this, const char *format, ...)
{
    va_list message_arguments;

    va_start(message_arguments, format);
    if (vdprintf(this->file, format, message_arguments) < 0) {
        this->status = false;
    }
    va_end(message_arguments);
}

bool file_stream_get_status(file_stream_t *this)
{
    return this->status;
}

void file_stream_destroy(file_stream_t *this)
{
    close(this->file);
    free(this);
}
