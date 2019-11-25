#ifndef OSMIUM_GEOM_COORDINATES_HPP
#define OSMIUM_GEOM_COORDINATES_HPP

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

#include <osmium/osm/location.hpp>
#include <osmium/util/double.hpp>

#include <cmath>
#include <iosfwd>
#include <limits>
#include <string>

namespace osmium {

    namespace geom {

        struct Coordinates {

            double x;
            double y;

            /**
             * Default constructor creates invalid coordinates.
             */
            Coordinates() noexcept :
                x(std::numeric_limits<double>::quiet_NaN()),
                y(std::numeric_limits<double>::quiet_NaN()) {
            }

            /**
             * Create Coordinates from doubles. If any of them is NaN, the
             * coordinates are invalid.
             */
            explicit Coordinates(double cx, double cy) noexcept :
                x(cx),
                y(cy) {
            }

            /**
             * Create Coordinates from a Location. Will throw
             * osmium::invalid_location if the location is not valid.
             *
             * This constructor is not explicit on purpose allowing use of
             * a Location everywhere a Coordinates object is needed.
             */
            Coordinates(const osmium::Location& location) : // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
                x(location.lon()),
                y(location.lat()) {
            }

            /**
             * Coordinates are invalid if they have been default constructed.
             */
            bool valid() const noexcept {
                return !std::isnan(x) && !std::isnan(y);
            }

            /**
             * Convert coordinates to text and append to given string. If the
             * coordinate is invalid, the fixed string "invalid" will be
             * added to the string.
             *
             * @param s String to append the coordinates to.
             * @param infix Character to print between the two coordinates.
             * @param precision Number of digits after the decimal point the
             *        coordinate will be rounded to.
             */
            void append_to_string(std::string& s, const char infix, int precision) const {
                if (valid()) {
                    osmium::double2string(s, x, precision);
                    s += infix;
                    osmium::double2string(s, y, precision);
                } else {
                    s.append("invalid");
                }
            }

            /**
             * Convert coordinates to text and append to given string. If the
             * coordinate is invalid, the fixed string "invalid" will be
             * added to the string between the prefix and suffix characters.
             *
             * @param s String to append the coordinates to.
             * @param prefix Character to print before the first coordinate.
             * @param infix Character to print between the two coordinates.
             * @param suffix Character to print after the second coordinate.
             * @param precision Number of digits after the decimal point the
             *        coordinate will be rounded to.
             */
            void append_to_string(std::string& s, const char prefix, const char infix, const char suffix, int precision) const {
                s += prefix;
                append_to_string(s, infix, precision);
                s += suffix;
            }

        }; // struct coordinates

        /**
         * Check whether two Coordinates are equal. Invalid coordinates are
         * equal to other invalid coordinates but not equal to any valid
         * coordinates.
         *
         * Because this is comparing floating point values, it might not give
         * the right result if the coordinates have been the result of some
         * calculation that introduced rounding errors.
         */
        inline bool operator==(const Coordinates& lhs, const Coordinates& rhs) noexcept {
            if (!lhs.valid() && !rhs.valid()) {
                return true;
            }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
            return lhs.x == rhs.x && lhs.y == rhs.y;
#pragma GCC diagnostic pop
        }

        inline bool operator!=(const Coordinates& lhs, const Coordinates& rhs) noexcept {
            return !(lhs == rhs);
        }

        template <typename TChar, typename TTraits>
        inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const Coordinates& c) {
            return out << '(' << c.x << ',' << c.y << ')';
        }

    } // namespace geom

} // namespace osmium

#endif // OSMIUM_GEOM_COORDINATES_HPP
