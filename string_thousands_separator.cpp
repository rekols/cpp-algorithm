
/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 ~ 2018 Rekols
 *
 * Author:     Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cctype>
#include <regex>
#include <list>

inline std::string format_thousands_sep(const std::string &str)
{
    std::string result = str;
    int start_position = 0;

    if (start_position >= 0) {
        int end_position = result.find('.');

        if (end_position < 0) {
            end_position = result.length();
        }

        for (int i = end_position - 3; i >= start_position + 1; i -= 3) {
            result.insert(i, ",");
        }
    }

    return result;;
}

inline bool string_is_diagit(const std::string &str)
{
    bool is_digit = true;

    for (const char &ch : str) {
        if (!isdigit(ch) && ch != '.') {
            is_digit = false;
            break;
        }
    }

    return is_digit;
}

inline std::string reformat(const std::string &str)
{
    std::string expression = str;
    std::string seg;
    std::list<std::string> exp_list;

    for (int i = 0; i < expression.length(); ++i) {
        const char ch = expression.at(i);

        if (isdigit(ch) || ch == '.') {
            seg.push_back(ch);
        } else {
            exp_list.push_back(seg);
            seg.clear();
            seg.push_back(ch);
            exp_list.push_back(seg);
            seg.clear();
        }

        if (i == expression.length() - 1) {
            exp_list.push_back(seg);
        }
    }

    std::string format_str;
    for (std::string exp : exp_list) {
        if (string_is_diagit(exp)) {
            exp = format_thousands_sep(exp);
        }

        format_str += exp;
    }

    return format_str;
}

int main(int argc, char *argv[])
{
    while (1) {
        std::string str;
        std::cin >> str;

        if (str == "q") {
            break;
        }

        std::cout << reformat(str) << std::endl;
    }

    return 0;
}
