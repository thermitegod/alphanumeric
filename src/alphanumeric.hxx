/**
 * Released under the MIT License - https://opensource.org/licenses/MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <functional>

#include <string>
#include <string_view>

#include <sstream>

#include <cctype>

#ifdef DOJDEBUG
#include <iostream>
#include <typeinfo>
#endif

// TODO: make comparison with hexadecimal numbers. Extend the alphanum_comp() function by traits to
// choose between decimal and hexadecimal.

namespace AlphaNumeric
{
    namespace
    {
        enum class Mode
        {
            STRING,
            NUMBER
        };

        /**
         * compare l and r with strcmp() semantics, but using
         * the "Alphanum Algorithm". This function is designed to read
         * through the l and r strings only one time, for
         * maximum performance. It does not allocate memory for
         * substrings.
         *
         * @param l C-style string
         * @param r C-style string
         * @return negative if left<right, 0 if left==right, positive if left>right.
         */
        static inline int
        alphanum_impl(const char* l, const char* r)
        {
            Mode mode = Mode::STRING;

            while (*l && *r)
            {
                if (mode == Mode::STRING)
                {
                    char l_char, r_char;
                    while ((l_char = *l) && (r_char = *r))
                    {
                        // check if this are digit characters
                        const bool l_digit = isdigit(l_char);
                        const bool r_digit = isdigit(r_char);
                        // if both characters are digits, we continue in NUMBER mode
                        if (l_digit && r_digit)
                        {
                            mode = Mode::NUMBER;
                            break;
                        }
                        // if only the left character is a digit, we have a result
                        if (l_digit)
                            return -1;
                        // if only the right character is a digit, we have a result
                        if (r_digit)
                            return +1;
                        // compute the difference of both characters
                        const int diff = l_char - r_char;
                        // if they differ we have a result
                        if (diff != 0)
                            return diff;
                        // otherwise process the next characters
                        ++l;
                        ++r;
                    }
                }
                else // mode==NUMBER
                {
                    // get the left number
                    char* end;
                    unsigned long l_int = strtoul(l, &end, 0);
                    l = end;

                    // get the right number
                    unsigned long r_int = strtoul(r, &end, 0);
                    r = end;

                    // if the difference is not equal to zero, we have a comparison result
                    const long diff = l_int - r_int;
                    if (diff != 0)
                        return diff;

                    // otherwise we process the next substring in STRING mode
                    mode = Mode::STRING;
                }
            }

            if (*r)
                return -1;
            if (*l)
                return +1;
            return 0;
        }

    } // namespace

    /**
     * Compare left and right with the same semantics as strcmp(), but with the
     * "Alphanum Algorithm" which produces more human-friendly
     * results. The classes lT and rT must implement "std::ostream
     * operator<< (std::ostream&, const Ty&)".
     *
     * @return negative if left<right, 0 if left==right, positive if left>right.
     */
    template<typename lT, typename rT>
    static inline int
    alphanum_comp(const lT& left, const rT& right)
    {
#ifdef DOJDEBUG
        std::clog << "alphanum_comp<" << typeid(left).name() << "," << typeid(right).name() << "> "
                  << left << "," << right << std::endl;
#endif
        std::ostringstream l;
        l << left;
        std::ostringstream r;
        r << right;
        return alphanum_impl(l.str().c_str(), r.str().c_str());
    }

    /**
     * Compare l and r with the same semantics as strcmp(), but with
     * the "Alphanum Algorithm" which produces more human-friendly
     * results.
     *
     * @return negative if left<right, 0 if left==right, positive if left>right.
     */
    static inline int
    alphanum_comp(std::string_view l, std::string_view r)
    {
#ifdef DOJDEBUG
        std::clog << "alphanum_comp<std::string_view,std::string_view> " << l << "," << r << std::endl;
#endif
        return alphanum_impl(l.data(), r.data());
    }

    ////////////////////////////////////////////////////////////////////////////

    /**
     * Functor class to compare two objects with the "Alphanum
     * Algorithm". If the objects are no std::string, they must
     * implement "std::ostream operator<< (std::ostream&, const Ty&)".
     */
    template<class Ty> struct alphanum_less: public std::binary_function<Ty, Ty, bool>
    {
        bool
        operator()(const Ty& left, const Ty& right) const
        {
            return alphanum_comp(left, right) < 0;
        }
    };
} // namespace AlphaNumeric
