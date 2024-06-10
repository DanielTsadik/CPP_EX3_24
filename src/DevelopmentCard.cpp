#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(const string& type) : type(type) {}

string DevelopmentCard::getType() const {
    return type;
}