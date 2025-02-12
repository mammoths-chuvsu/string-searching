#ifndef BASE_SUBSTRING_SEARCHER_HPP_
#define BASE_SUBSTRING_SEARCHER_HPP_

#include <string>

/**
 * \brief Base class of string searching algorithm.
 */
class BaseSubstringSearcher {
public:
    /**
     * \brief Constructor.
     * \param name algorithm name.
     */
    BaseSubstringSearcher(std::string name) : name_(std::move(name)) {}

    virtual ~BaseSubstringSearcher() = default;

    /**
     * \brief Run algorithm.
     * \param text text where to search string.
     * \param substring string to search in text.
     * \return Returns true if text contains substring.
     */
    virtual bool Contains(const std::string &text, const std::string &substring) const = 0;

    /**
     * \brief Get algorithm name.
     */
    std::string GetName() const { return name_; }

protected:
    std::string name_;  ///< Algorithm name.
};

#endif  // BASE_SUBSTRING_SEARCHER_HPP_
