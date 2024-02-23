#include <iostream>
#include <string>
#include <C:\Users\dnast\OneDrive\Documents\AERSP 424\HW1\HW1_Problem3_4\FlightMap.h>

class Plane {
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;
    const FlightMap& flightMap; // Container from Question 2

public:
    // Constructor
    Plane(const std::string& from, const std::string& to, const FlightMap& map)
        : origin(from), destination(to), pos(0), vel(0), distance(0), at_SCE(from == "SCE"), flightMap(map) { // Initializes all values
        if (flightMap.find(destination) != flightMap.end()) { //Checks if the key is in the map
            distance = flightMap.at(destination);
        }
        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor
    ~Plane() {
        std::cout << "Plane Destroyed" << std::endl;

    }

    // Operate function
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * (dt / 3600);
            at_SCE = 0;
        }
        else if (destination == "SCE") {
            at_SCE = 1;
            auto temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
        else {
            std::cout << "Plane has landed at " << destination << "." << endl;
            auto temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        };
    }

    // Getter for pos
    double getPos() const { return pos; }

    // Getter for origin
    std::string getOrigin() const { return origin; }

    // Getter for destination
    std::string getDestination() const { return destination; }

    // Getter for at_SCE
    bool getAt_SCE() const { return at_SCE; }

    // Getter and setter for vel
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
};

class Pilot {
private:
    std::string name;
public:
    //Constructor
    Pilot(const std::string& pilotName) :name(pilotName), myPlane(nullptr) {
        std::cout << "Pilot " << name << " is at the gate, ready to board the plane. " << "Memory address: " << this << std::endl;
    }
    //Destructor
    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    //Getter for name
    std::string getName() { return name };

    //Pointer
    Plane* myPlane;
};

int main() {
    Plane plane1("SCE", "EWR", globalFlightMap);
    plane1.setVel(450);

    for (int i = 0; i < 15000; i + 15) {
        plane1.operate(i);
        double pos_temp = plane1.getPos();

        std::cout << "Time: " << i << " seconds, Position: " << pos_temp << " miles." << std::endl;
    }
    return 0;
}