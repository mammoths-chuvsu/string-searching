
#include <climits>
#include <cstdint>
#include <stdexcept>
#include <string-searching/shift_or_substring_searcher.hpp>
#include <string>
#include <unordered_map>

ShiftOrSubstringSearcher::ShiftOrSubstringSearcher() : BaseSubstringSearcher("shift-or") {}

bool ShiftOrSubstringSearcher::Contains(const std::string& text,
                                        const std::string& substring) const {
    size_t pattern_length = substring.length();
    size_t text_length = text.length();

    // If the substring is empty, return true (empty substring is always contained)
    if (pattern_length == 0) {
        return true;
    }

    // Check if the pattern length exceeds the limit (e.g., assuming 64-bit words)
    if (pattern_length > (sizeof(uint64_t) * CHAR_BIT)) {
        throw std::runtime_error("The pattern is too long!");
    }

    uint64_t current_state = ~1UL;  // Initialize with all bits set except the least significant bit
    std::unordered_map<char, uint64_t> character_masks;

    // Initialize the character masks with all bits set
    for (int character = 0; character <= CHAR_MAX; ++character) {
        character_masks[static_cast<char>(character)] = ~0UL;
    }

    // Compute the character_masks for the given pattern
    for (size_t index = 0; index < pattern_length; ++index) {
        character_masks[substring[index]] &= ~(1UL << index);
    }

    for (size_t index = 0; index < text_length; ++index) {
        // Update the current_state: Shift left, and apply the mask for the current character
        current_state |= character_masks[text[index]];
        current_state <<= 1;

        // Check if the match bit position is clear, indicating a pattern match
        if ((current_state & (1UL << pattern_length)) == 0) {
            return true;
        }
    }

    return false;
}
