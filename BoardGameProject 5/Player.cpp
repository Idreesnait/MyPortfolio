#include "Player.h"
#include <iostream>

Player::Player() : name("Unnamed"), age(0), strength(100), stamina(100), wisdom(100), pridePoints(20000), advisor("None"), position(0) {}

Player::Player(const std::string& name, int age, int strength, int stamina, int wisdom, int pridePoints)
    : name(name), age(age), strength(strength), stamina(stamina), wisdom(wisdom), pridePoints(pridePoints), advisor("None"), position(0) {}

std::string Player::getName() const {
    return name;
}

int Player::getAge() const {
    return age;
}

int Player::getStrength() const {
    return strength;
}

int Player::getStamina() const {
    return stamina;
}

int Player::getWisdom() const {
    return wisdom;
}

int Player::getPridePoints() const {
    return pridePoints;
}

std::string Player::getAdvisor() const {
    return advisor;
}

int Player::getPosition() const {
    return position;
}

std::string Player::getPath() const {
    return path;
}

void Player::setName(const std::string& name) {
    this->name = name;
}

void Player::setAge(int age) {
    this->age = age;
}

void Player::setStrength(int strength) {
    this->strength = (strength < 100) ? 100 : strength; 
}

void Player::setStamina(int stamina) {
    this->stamina = (stamina < 100) ? 100 : stamina; 
}

void Player::setWisdom(int wisdom) {
    this->wisdom = (wisdom < 100) ? 100 : wisdom; 
}

void Player::setPridePoints(int pridePoints) {
    this->pridePoints = pridePoints;
}

void Player::setPosition(int pos) {
    this->position = pos;
}

void Player::setAdvisor(const std::string& advisor) {
    this->advisor = advisor;
}

void Player::setPath(const std::string& path) {
    this->path = path;
}

void Player::adjustStats(int pridePointsChange, int strengthChange, int staminaChange, int wisdomChange) {
    pridePoints += pridePointsChange;
    strength += strengthChange;
    stamina += staminaChange;
    wisdom += wisdomChange;

    if (strength < 100) strength = 100;
    if (stamina < 100) stamina = 100;
    if (wisdom < 100) wisdom = 100;
}

void Player::printStats() const {
    std::cout << "Player: " << name << "\n"
              << "Age: " << age << "\n"
              << "Strength: " << strength << "\n"
              << "Stamina: " << stamina << "\n"
              << "Wisdom: " << wisdom << "\n"
              << "Pride Points: " << pridePoints << "\n"
              << "Advisor: " << advisor << "\n";
}

void Player::adjustWisdom(int points) {
    wisdom += points;
    if (wisdom < 100) {
        wisdom = 100; 
    }
}
