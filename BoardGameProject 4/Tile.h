#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {
private:
    std::string type;  
    int effect;       
    std::string description; 

public:
    Tile(); 
    Tile(const std::string& type, int effect = 0, const std::string& description = "");

    std::string getType() const;
    int getEffect() const;
    std::string getDescription() const;

    void setType(const std::string& type);
    void setEffect(int effect);
    void setDescription(const std::string& description);

   void triggerEffect() const; 

};

#endif
