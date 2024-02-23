#ifndef FLIGHTMAP_H
#define FLIGHTMAP_H

#include <map>
#include <string>

using FlightMap = std::map<std::string, int>;

inline FlightMap globalFlightMap = {
    {"PHL", 160},
    {"ORD", 640},
    {"EWR", 220}
};

#endif#pragma once
