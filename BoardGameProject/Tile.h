#ifndef TILE_H
#define TILE_H

#include <string> // Includes the standard string library for managing text data

class Tile {
private:
    std::string type;  // Represents the type of the tile (e.g., "Regular", "Start", "Oasis")
    int effect;        // Holds the effect value of the tile (positive, negative, or zero)
    std::string description; // Describes the tile's purpose or effect

public:
    Tile(); // Default constructor initializes a tile with default values
    Tile(const std::string& type, int effect = 0, const std::string& description = ""); // Parameterized constructor

    std::string getType() const; // Returns the type of the tile
    int getEffect() const; // Returns the effect value of the tile
    std::string getDescription() const; // Returns the description of the tile

    void setType(const std::string& type); // Sets the type of the tile
    void setEffect(int effect); // Sets the effect value of the tile
    void setDescription(const std::string& description); // Sets the description of the tile

    void triggerEffect() const; // Executes the tile's effect and displays an appropriate message

};

#endif