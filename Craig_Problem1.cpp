#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

int main()
{
    int FrontSeatOccupants, RearSeatOccupants, FuelGallons;
    double emptyWeight, emptyWeightMoment, BaggageWeight, BaggageMomentArm, FrontSeatMomentArm, RearSeatMomentArm, FuelWeightPerGallon, FuelMomentArm;
    std::vector<double> FrontSeatWeight;
    std::vector<double> RearSeatWeight;
    double maxGrossWeight = 2950, forwardCGLimit = 82.1, aftCGLimit = 84.7;

    //Input
    std::cout << "Enter airplane empty weight (pounds):";
    std::cin >> emptyWeight;
    std::cout << "Enter airplane empty-weight moment (pounds-inches): ";
    std::cin >> emptyWeightMoment;
    std::cout << "Enter number of front seat occupants:";
    std::cin >> FrontSeatOccupants;
    for (int i = 0; i < FrontSeatOccupants; ++i) {
        int w = 0;
        std::cout << "Enter weight of each front seat occupant (pounds):";
        std::cin >> w;
        FrontSeatWeight.push_back(w);
    }
    std::cout << "Enter front seat moment arm (inches):";
    std::cin >> FrontSeatMomentArm;
    std::cout << "Enter number of rear seat occupants:";
    std::cin >> RearSeatOccupants;
    for (int i = 0; i < RearSeatOccupants; ++i) {
        int w = 0;
        std::cout << "Enter weight of each rear seat occupant (pounds):";
        std::cin >> w;
        RearSeatWeight.push_back(w);
    }
    std::cout << "Enter rear seat moment arm (inches):";
    std::cin >> RearSeatMomentArm;
    std::cout << "Enter number of gallons of usable fuel (gallons):";
    std::cin >> FuelGallons;
    std::cout << "Enter usable fuel weights per gallon (pounds):";
    std::cin >> FuelWeightPerGallon;
    std::cout << "Enter fuel tank moment arm (inches):";
    std::cin >> FuelMomentArm;
    std::cout << "Enter baggage weight (pounds):";
    std::cin >> BaggageWeight;
    std::cout << "Enter baggage moment arm (inches): ";
    std::cin >> BaggageMomentArm;

    // Calculations
    double FuelWeight = FuelGallons * FuelWeightPerGallon;
    double TotalFrontSeatWeight = std::accumulate(FrontSeatWeight.begin(), FrontSeatWeight.end(), 0);
    double TotalRearSeatWeight = std::accumulate(RearSeatWeight.begin(), RearSeatWeight.end(), 0);

    double totalWeight = emptyWeight + TotalFrontSeatWeight + TotalRearSeatWeight + FuelWeight + BaggageWeight;
    double totalMoment = emptyWeightMoment + TotalFrontSeatWeight * FrontSeatMomentArm + TotalRearSeatWeight * RearSeatMomentArm + FuelWeight * FuelMomentArm + BaggageWeight * BaggageMomentArm;
    double cgLocation = totalMoment / totalWeight;
    std::cout << "\nInitial Gross Weight: " << totalWeight << " lbs\n";
    std::cout << "Initial C.G. Location: " << cgLocation << " inches\n";

    // Check if within limits and adjust fuel if necessary
    if (totalWeight > maxGrossWeight || cgLocation < forwardCGLimit || cgLocation > aftCGLimit) {
        std::cout << "Adjustments needed to meet design limits.\n";

        bool adjust = true;
        while (adjust) {
            if (totalWeight > maxGrossWeight) {
                FuelGallons--; // Reduce fuel by one gallon at a time if overweight
            }
            else if (cgLocation < forwardCGLimit || cgLocation > aftCGLimit) {
                if (cgLocation < forwardCGLimit) {
                    FuelGallons--; // Reduce fuel if CG is too forward
                }
                else {
                    FuelGallons++; // Add fuel if CG is too aft, and still under max weight
                }
            }
            else {
                adjust = false;
                continue;
            }

            // Recalculate after adjustment
            FuelWeight = FuelGallons * FuelWeightPerGallon;
            totalWeight = emptyWeight + TotalFrontSeatWeight + TotalRearSeatWeight + FuelWeight + BaggageWeight;
            totalMoment = emptyWeightMoment + (TotalFrontSeatWeight * FrontSeatMomentArm) + (TotalRearSeatWeight * RearSeatMomentArm) + (FuelWeight * FuelMomentArm) + (BaggageWeight * BaggageMomentArm);
            cgLocation = totalMoment / totalWeight;

            // Check for more adjustments
            if (totalWeight <= maxGrossWeight && cgLocation >= forwardCGLimit && cgLocation <= aftCGLimit) {
                adjust = false;
            }
        }

        std::cout << "After adjustment:\n";
        std::cout << "New Gross Weight: " << totalWeight << " lbs\n";
        std::cout << "New C.G. Location: " << cgLocation << " inches\n";
    }
    else {
        std::cout << "No adjustments needed. Within design limits.\n";
    }
    return 0;
}