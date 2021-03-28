/*
    Copyright 2017-2021 (C) Alexey Dynda

    This file is part of Tiny Protocol Library.

    Protocol Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Protocol Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Protocol Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>

void tiny_serial_close(tiny_serial_handle_t port)
{
    port->end();
}

tiny_serial_handle_t tiny_serial_open(const char *name, uint32_t baud)
{
    tiny_serial_handle_t handle = reinterpret_cast<tiny_serial_handle_t>(name);
    m_handle->begin( baud );
    return handle;
}

int tiny_serial_send(tiny_serial_handle_t port, const void *buf, int len)
{
    port->setTimeout( 100 );
    return port->write( buf, len );
}

int tiny_serial_send_timeout(tiny_serial_handle_t port, const void *buf, int len, uint32_t timeout_ms)
{
    port->setTimeout( timeout_ms );
    return port->write( buf, len );
}

int tiny_serial_read(tiny_serial_handle_t port, void *buf, int len)
{
    port->setTimeout( 100 );
    return port->readBytes( buf, len );
}

int tiny_serial_read_timeout(tiny_serial_handle_t port, void *buf, int len, uint32_t timeout_ms)
{
    port->setTimeout( timeout_ms );
    return port->readBytes( buf, len );
}
