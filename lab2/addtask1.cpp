#include <string>

class PairOfStrings
{
private:
    std::string firstString;
    std::string secondString;

public:
    PairOfStrings() {}
    PairOfStrings(const std::string &first, const std::string &second) : firstString(first), secondString(second) {}

    void setFirstString(const std::string &str)
    {
        firstString = str;
    }

    void setSecondString(const std::string &str)
    {
        secondString = str;
    }
    std::string getFirstString() const
    {
        return firstString;
    }

    std::string getSecondString() const
    {
        return secondString;
    }
};
