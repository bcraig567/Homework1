#include <iostream>
#include <string>
#include "FlightMap.h" // Assuming FlightMap is properly defined in "FlightMap.h"

class Plane {
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;
    const FlightMap& flightMap; // Container from Question 2

public:
    // Constructor below
    Plane(const std::string& from, const std::string& to, const FlightMap& map)
        : origin(from), destination(to), pos(0), vel(0), distance(0), at_SCE(from == "SCE"), flightMap(map) { // Initializes all values
        if (flightMap.find(destination) != flightMap.end()) { // Checks if the key is in the map
            distance = flightMap.at(destination);
        }
        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor below
    ~Plane() {
        std::cout << "Plane Destroyed" << std::endl;
    }

    // Operate function for plane land
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * (dt / 3600);
            at_SCE = false;
        }
        else if (destination == "SCE") {
            at_SCE = true;
            std::swap(origin, destination);
            pos = 0;
        }
        else {
            std::cout << "Plane has landed at " << destination << "." << std::endl;
            std::swap(origin, destination);
            pos = 0;
        }
    }

    // Pos getter
    double getPos() const { return pos; }

    // Origin getter
    std::string getOrigin() const { return origin; }

    // Destination getter
    std::string getDestination() const { return destination; }

    // at_SCE getter
    bool getAt_SCE() const { return at_SCE; }

    // vel getter (also setter for vel)
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
};

class Pilot {
private:
    std::string name;

public:
    // Constructor
    Pilot(const std::string& pilotName) : name(pilotName), myPlane(nullptr) {
        std::cout << "Pilot " << name << " is at the gate, ready to board the plane. " << "Memory address: " << this << std::endl;
    }

    // Destructor
    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    // Getter for name
    std::string getName() const { return name; }

    // Pointer
    Plane* myPlane;
};

int main() {
    FlightMap globalFlightMap; // Assuming globalFlightMap is defined and initialized
    Plane plane1("SCE", "EWR", globalFlightMap);
    plane1.setVel(450);

    for (int i = 0; i < 15000; i += 15) {
        plane1.operate(i);
        double pos_temp = plane1.getPos();

        std::cout << "Time: " << i << " seconds, Position: " << pos_temp << " miles." << std::endl;
    }
    return 0;
}