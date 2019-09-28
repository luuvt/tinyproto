/*
    Copyright 2017 (C) Alexey Dynda

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

#ifndef _FAKE_WIRE_H_
#define _FAKE_WIRE_H_

#include <stdint.h>
#include <pthread.h>
#include <mutex>

class FakeWire
{
public:
    FakeWire();
    ~FakeWire();
    int read(uint8_t * data, int length);
    int write(const uint8_t * data, int length);
    void generate_error_on_byte(int byte_num) { m_error_byte_num = byte_num; };
    void reset();
private:
    int          m_writeptr;
    int          m_readptr;
    std::mutex   m_mutex{};
    uint8_t      m_buf[1024];
    int          m_error_byte_num = 0;
    int          m_byte_counter = 0;
};


#endif /* _FAKE_WIRE_H_ */
