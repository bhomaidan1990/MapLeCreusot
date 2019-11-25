#ifndef OSMIUM_UTIL_MINMAX_HPP
#define OSMIUM_UTIL_MINMAX_HPP

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

#include <limits>

namespace osmium {

    template <typename T>
    inline T min_op_start_value() {
        return std::numeric_limits<T>::max();
    }

    /**
     * Class for calculating the minimum of a bunch of values.
     * Works with any numeric type.
     *
     * Usage:
     *
     *    min_op<int> x;
     *    x.update(27);
     *    x.update(12);
     *    auto min = x.get(); // 12
     */
    template <typename T>
    class min_op {

        T m_value;

    public:

        explicit min_op(T start_value = min_op_start_value<T>()) :
            m_value(start_value) {
        }

        void update(T value) noexcept {
            if (value < m_value) {
                m_value = value;
            }
        }

        T operator()() const noexcept {
            return m_value;
        }

    };

    template <typename T>
    inline T max_op_start_value() {
        return std::numeric_limits<T>::min();
    }

    /**
     * Class for calculating the maximum of a bunch of values.
     * Works with any numeric type.
     *
     * Usage:
     *
     *    max_op<int> x;
     *    x.update(27);
     *    x.update(12);
     *    auto max = x.get(); // 27
     */
    template <typename T>
    class max_op {

        T m_value;

    public:

        explicit max_op(T start_value = max_op_start_value<T>()) :
            m_value(start_value) {
        }

        void update(T value) noexcept {
            if (value > m_value) {
                m_value = value;
            }
        }

        T operator()() const noexcept {
            return m_value;
        }

    };

} // namespace osmium

#endif // OSMIUM_UTIL_MINMAX_HPP
