#include "Tile.h"
#include <iostream>

Tile::Tile() : type("Regular"), effect(0), description("A regular tile with no special effect.") {}

Tile::Tile(const std::string& type, int effect, const std::string& description)
    : type(type), effect(effect), description(description) {}

std::string Tile::getType() const {
    return type;
}

int Tile::getEffect() const {
    return effect;
}

std::string Tile::getDescription() const {
    return description;
}

void Tile::setType(const std::string& type) {
    this->type = type;
}

void Tile::setEffect(int effect) {
    this->effect = effect;
}

void Tile::setDescription(const std::string& description) {
    this->description = description;
}

void Tile::triggerEffect() const {
    if (effect > 0) {
        std::cout << "You gained " << effect << " points!\n";
    } else if (effect < 0) {
        std::cout << "You lost " << -effect << " points!\n";
    } else {
        std::cout << "Nothing happens on this tile.\n";
    }
}
