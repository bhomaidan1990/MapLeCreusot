#ifndef OSMIUM_IO_ERROR_HPP
#define OSMIUM_IO_ERROR_HPP

/*

This file is part of Osmium (https://osmcode.org/libosmium).

Copyright 2013-2019 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <stdexcept>
#include <string>

namespace osmium {

    /**
     * Exception thrown when some kind of input/output operation failed.
     */
    struct io_error : public std::runtime_error {

        explicit io_error(const std::string& what) :
            std::runtime_error(what) {
        }

        explicit io_error(const char* what) :
            std::runtime_error(what) {
        }

    }; // struct io_error

    struct unsupported_file_format_error : public io_error {

        explicit unsupported_file_format_error(const std::string& what) :
            io_error(what) {
        }

        explicit unsupported_file_format_error(const char* what) :
            io_error(what) {
        }

    }; // struct unsupported_file_format_error

} // namespace osmium

#endif // OSMIUM_IO_ERROR_HPP
