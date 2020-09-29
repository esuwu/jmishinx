//
// Created by kira on 27.09.2020.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <regex>

using Key = long;
using Val = long;
using Map = std::unordered_map<Key, Val>;

void add_default(Map &map, Key key, Val val) {
    if (map.find(key) == map.end()) {
        map[key] = val;
    } else {
        map[key] += val;
    }

}

std::vector<std::pair<Key, Val>> parse(const std::string &polynomial) {
    Map map;
    std::smatch matches;

    static std::regex one_x{R"(([\+|\-]?)(\d*)?(?:\*)?(x?)(?:\^)?(\d*)?)"};
    enum Group : size_t { Sign = 1, Coef, X, Pow };

    auto matches_begin = std::sregex_iterator{
        polynomial.begin(),
        polynomial.end(),
        one_x
    };

    for (; matches_begin != std::sregex_iterator{}; ++matches_begin) {
        auto match = *matches_begin;
        if (match.str().empty() or match[X].str().empty()) {
            continue;
        }

        Key power = 1;
        Val coef = 1;

        if (match[Sign] == '-') {
            coef *= -1;
        }

        if (not match[Coef].str().empty()) {
            coef *= std::stol(match[Coef].str());
        }

        if (not match[Pow].str().empty()) {
            power *= std::stol(match[Pow].str());
        }

        add_default(map, power, coef);
    }

    std::vector<std::pair<Key, Val>> sorted_items;
    for (auto&[power, coef]: map) {
        sorted_items.emplace_back(
            power - 1,
            power * coef
        );
    }

    std::sort(sorted_items.begin(), sorted_items.end(), std::greater<std::pair<long, long>>{});

    return sorted_items;
}

std::string repr(const std::vector<std::pair<Key, Val>> &sorted_items) {
    std::string repr;
    bool first = true;
    for (auto[power, coef]: sorted_items) {
        bool negative = coef < 0;
        if (negative) {
            repr += '-';
        } else if (not first) {
            repr += '+';
        }
        first = false;

        coef = std::abs(coef);
        if (coef != 1 or power == 0) {
            repr += std::to_string(coef);
        }

        if (coef != 1 and power != 0) {
            repr += '*';
        }

        if (power != 0) {
            repr += 'x';
        }

        if (power > 1) {
            repr += '^' + std::to_string(power);
        }
    }
    return repr;
}

void solve(std::istream &in, std::ostream &out) {
    std::string polynomial;
    in >> polynomial;
    auto sorted = parse(polynomial);
    out << repr(sorted);
}

int main() {
    solve(std::cin, std::cout);
    return 0;
}
