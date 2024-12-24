#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
    int position; 
    std::string advisor;
    std::string path;

public:
    Player();
    Player(const std::string& name, int age, int strength, int stamina, int wisdom, int pridePoints);

    std::string getName() const;
    int getAge() const;
    int getStrength() const;
    int getStamina() const;
    int getWisdom() const;
    int getPridePoints() const;
    int getPosition() const; 
    std::string getAdvisor() const;
    std::string getPath() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPridePoints(int pridePoints);
    void setPosition(int pos); 
    void setAdvisor(const std::string& advisor);
    void setPath(const std::string& path); 

    void adjustStats(int pridePoints, int strength, int stamina, int wisdom);
    void adjustWisdom(int wisdomPoints);
    void printStats() const;
};

#endif

