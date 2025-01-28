#ifndef BASE_SUBSTRING_SEARCHER_HPP_
#define BASE_SUBSTRING_SEARCHER_HPP_

#include <string>
#include <optional>

enum class SubstringSearchAlgorithm { kNaive };

class BaseSubstringSearcher {
public:
    BaseSubstringSearcher(std::string name) : name_(std::move(name)) {}

    virtual bool Contains(const std::string &text, const std::string &substring) const = 0;

    virtual ~BaseSubstringSearcher() = default;

    const std::string &getName() const { return name_; }

    static std::optional<SubstringSearchAlgorithm> GetAlgorithmByName(const std::string &name);

protected:
    std::string name_;
};

#endif
