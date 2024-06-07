#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(const std::string& type) : type(type) {}

std::string DevelopmentCard::getType() const {
    return type;
}
