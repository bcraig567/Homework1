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
            at_SCE = false;
        }
        else if (destination == "SCE") {
            at_SCE = true;
            std::cout << "Plane has landed at " << destination << "." << std::endl;
            auto temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
        else {
            std::cout << "Plane has landed at " << destination << "." << std::endl;
            auto temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
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

    // Function to board the plane
    void boardPlane(Plane* plane) {
        myPlane = plane;
        std::cout << "Pilot " << name << " has boarded the plane. Plane memory address: " << myPlane << std::endl;
    }

    // Function to disembark the plane
    void leavePlane() {
        std::cout << "Pilot " << name << " is leaving the plane." << std::endl;
        myPlane = nullptr;
    }
};

int main() {
    // Instantiate the FlightMap and create a plane
    FlightMap globalFlightMap; // Assuming you have a proper FlightMap constructor
    Plane plane1("SCE", "EWR", globalFlightMap);
    plane1.setVel(450);

    // Instantiate two pilots
    Pilot pilot1("Pilot-in-Command");
    Pilot pilot2("Co-Pilot");

    // Board the plane with the first pilot
    pilot1.boardPlane(&plane1);

    // Simulation loop
    for (int i = 0; i < 15000; i += 15) {
        // Operate the plane
        plane1.operate(i);

        // Check if the plane has landed at SCE
        if (plane1.getAt_SCE()) {
            std::cout << "Plane is at SCE. Memory address: " << &plane1 << std::endl;

            // Switch control to the other pilot
            if (pilot1.getName() == "Pilot-in-Command") {
                pilot1.leavePlane();
                pilot2.boardPlane(&plane1);
            }
            else {
                pilot2.leavePlane();
                pilot1.boardPlane(&plane1);
            }
            // Print the current pilot and the plane they are controlling
            std::cout << "Current Pilot: " << (pilot1.getName() == "Pilot-in-Command" ? "Pilot-in-Command" : "Co-Pilot")
                << ", Plane Memory Address: " << pilot1.myPlane << std::endl;
        }

        // Print the time and position of the plane
        double pos_temp = plane1.getPos();
        std::cout << "Time: " << i << " seconds, Position: " << pos_temp << " miles." << std::endl;
    }

    return 0;
}
