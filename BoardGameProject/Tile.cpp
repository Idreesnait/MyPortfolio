#include "Tile.h" // Includes the Tile class definition
#include <iostream>   // Provides functionality for input and output operations

// Default constructor for the Tile class
// Initializes the tile as a "Regular" tile with no effect and a default description
Tile::Tile() : type("Regular"), effect(0), description("A regular tile with no special effect.") {}

// Parameterized constructor for the Tile class
// Allows the initialization of a tile with a specific type, effect, and description
Tile::Tile(const std::string& type, int effect, const std::string& description)
    : type(type), effect(effect), description(description) {}

// Returns the type of the tile (e.g., "Start", "Oasis", "Graveyard")
std::string Tile::getType() const {
    return type;
}

// Returns the effect of the tile (e.g., positive or negative points)
int Tile::getEffect() const {
    return effect;
}

// Returns the description of the tile
std::string Tile::getDescription() const {
    return description;
}

// Sets the type of the tile to the given value
void Tile::setType(const std::string& type) {
    this->type = type;
}

// Sets the effect of the tile to the given value (positive or negative points)
void Tile::setEffect(int effect) {
    this->effect = effect;
}

// Sets the description of the tile to the given value
void Tile::setDescription(const std::string& description) {
    this->description = description;
}

// Triggers the effect of the tile and displays a message based on the effect value
void Tile::triggerEffect() const {
    if (effect > 0) { // Positive effect (gain points)
        std::cout << "You gained " << effect << " points!\n";
    } else if (effect < 0) { // Negative effect (lose points)
        std::cout << "You lost " << -effect << " points!\n";
    } else { // No effect
        std::cout << "Nothing happens on this tile.\n";
    }
}
