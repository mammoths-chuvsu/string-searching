#ifndef BASE_SUBSTRING_SEARCHER_HPP_
#define BASE_SUBSTRING_SEARCHER_HPP_

#include <optional>
#include <string>

/**
 * \brief Enumeration of implemented algorithms.
 */
enum class SubstringSearchAlgorithm {
    kNaive,     ///< Naive algorithm
    kKmp,       ///< Knuth-Morris-Pratt algorithm
    kZFunction  ///< Z function algorithm
};

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

    /**
     * \brief Run algorithm.
     * \param text text where to search string.
     * \param substring string to search in text.
     * \return Returns true if text contains substring.
     */
    virtual bool Contains(const std::string &text, const std::string &substring) const = 0;

    virtual ~BaseSubstringSearcher() = default;

    /**
     * \brief Get algorithm name.
     */
    std::string GetName() const { return name_; }

    /**
     * \brief Get concrete implementation of BaseSubstringSearcher class by algorithm name.
     * \param name algorithm name.
     * \return Returns implementation object or std::nullopt if name is wrong.
     */
    static std::optional<SubstringSearchAlgorithm> GetAlgorithmByName(const std::string &name);

protected:
    std::string name_;  ///< Algorithm name.
};

#endif
