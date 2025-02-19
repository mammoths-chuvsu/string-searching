#ifndef SHIFT_OR_SUBSTRING_SEARCHER_HPP
#define SHIFT_OR_SUBSTRING_SEARCHER_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "base_substring_searcher.hpp"

/**
 * @brief Implementation of the Shift-Or string searching algorithm.
 */
class ShiftOrSubstringSearcher : public BaseSubstringSearcher {
public:
    ShiftOrSubstringSearcher();

    bool Contains(const std::string& text, const std::string& substring) const override;
};

#endif  // SHIFT_OR_SUBSTRING_SEARCHER_HPP_
