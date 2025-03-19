#ifndef MATH_H
#define MATH_H

namespace common {
    namespace utils {

        /**
         * Given a start value, an end value, and a parameter t (typically between 0 and 1),
         * this function calculates the intermediate value.
         *
         * @tparam T The data type for the values (e.g., float, double).
         * @param start The starting value.
         * @param end The ending value.
         * @param t The interpolation parameter, typically in the range [0, 1].
         * @return The interpolated value.
         */
        template <typename T>
        T tween(T start, T end, T t) {
            return start + (end - start) * t;
        }

    } // namespace utils
} // namespace common

#endif // MATH_H