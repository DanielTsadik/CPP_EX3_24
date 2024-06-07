#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

class DevelopmentCard {
public:
    explicit DevelopmentCard(const std::string& type);
    std::string getType() const;

private:
    std::string type;
};

#endif // DEVELOPMENTCARD_HPP
