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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include "../src/alphanumeric.hxx"

TEST_CASE("alphanumeric")
{
    REQUIRE(AlphaNumeric::alphanum_comp("", "") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("", "a") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a", "") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a", "a") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("", "9") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("9", "") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("1", "1") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("1", "2") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("3", "2") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a1", "a1") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a1", "a2") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a2", "a1") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a1a2", "a1a3") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a1a2", "a1a0") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("134", "122") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("12a3", "12a3") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("12a1", "12a0") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("12a1", "12a2") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("a", "aa") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("aaa", "aa") > 0);
    REQUIRE(AlphaNumeric::alphanum_comp("Alpha 2", "Alpha 2") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp("Alpha 2", "Alpha 2A") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("Alpha 2 B", "Alpha 2") > 0);

    REQUIRE(AlphaNumeric::alphanum_comp(1, 1) == 0);
    REQUIRE(AlphaNumeric::alphanum_comp(1, 2) < 0);
    REQUIRE(AlphaNumeric::alphanum_comp(2, 1) > 0);
    REQUIRE(AlphaNumeric::alphanum_comp(1.2, 3.14) < 0);
    REQUIRE(AlphaNumeric::alphanum_comp(3.14, 2.71) > 0);
    REQUIRE(AlphaNumeric::alphanum_comp(true, true) == 0);
    REQUIRE(AlphaNumeric::alphanum_comp(true, false) > 0);
    REQUIRE(AlphaNumeric::alphanum_comp(false, true) < 0);

    std::string str("Alpha 2");
    REQUIRE(AlphaNumeric::alphanum_comp(str, "Alpha 2") == 0);
    REQUIRE(AlphaNumeric::alphanum_comp(str, "Alpha 2A") < 0);
    REQUIRE(AlphaNumeric::alphanum_comp("Alpha 2 B", str) > 0);

    REQUIRE(AlphaNumeric::alphanum_comp(str, strdup("Alpha 2")) == 0);
    REQUIRE(AlphaNumeric::alphanum_comp(str, strdup("Alpha 2A")) < 0);
    REQUIRE(AlphaNumeric::alphanum_comp(strdup("Alpha 2 B"), str) > 0);
}
