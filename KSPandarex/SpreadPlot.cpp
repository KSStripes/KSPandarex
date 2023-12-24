//
//  SpreadPlot.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 23/12/2023.
//

#include "SpreadPlot.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <set> //included to set unique timestamps
#include "OrderBook.hpp"
#include "PandaMain.hpp"


// Constructor that takes timestamps and an OrderBook reference
SpreadPlot::SpreadPlot(const std::string& currentTime,
                       OrderBook& orderBook)
    : orderBookRef(orderBook)
{
    // Constructor initialization
}


/**function to create a vector of objects of all spreadplots, taking as inputs the current time and the orderbook entry **/
std::vector<double> SpreadPlot::getAllSpreads(const std::string& currentTime) {
    std::vector<double> spreads;  // Initialize a vector to store spread values

    // Get all known products
    std::vector<std::string> products = orderBookRef.getKnownProducts();

    // Iterate over all products
    for (const std::string& product : products) {
        // Calculate the spread for the current product and timestamp
        double spread = orderBookRef.getSpread(product, currentTime);
        // Round to 4 decimal places
        spread = std::round(spread * 10000) / 10000;
        // Add the calculated spread to the vector
        spreads.push_back(spread);
    }

    return spreads;
}



// Function to calculate the bar chart string
void SpreadPlot::calculateBarChart(double spread) {
    // Define a scale for the spread values (adjust as needed)
    double scale = 0.1; // Each character represents 0.1 spread

    // Calculate the number of characters in the bar
    int numChars = static_cast<int>(spread / scale);

    // Create the bar chart string
    std::string chart = "[";

    for (int i = 0; i < numChars; ++i) {
        chart += "#"; // Use '#' character for the bar
    }

    chart += "]";

    // Print the spread value and its bar chart
    std::cout << "Spread: " << spread << " " << chart << std::endl;
}

// Function to print the enhanced bar chart for each spread value
void SpreadPlot::printSpreadBarChart(const std::vector<double>& spreads) {
    // Iterate over each spread value in the vector
    for (const double& spread : spreads) {
        calculateBarChart(spread); // Print the bar chart for each spread
    }
}
//void SpreadPlot::printSpreadCharts() {
//    // Define a minimum chart length (minimum number of characters)
//    int minChartLength = 50;
//    
//    // Define a scale for the spread values (adjust as needed)
//    double scale = 0.1; // Each character represents 0.1 spread
//
//    // Print a box around the bar chart
//    std::string boxTop = "+" + std::string(minChartLength, '-') + "+";
//    std::cout << boxTop << std::endl;
//
//    // Iterate over each spread value in the vector
//    for (const double& spread : spreadData) {
//        // Calculate the number of characters in the bar
//        int numChars = static_cast<int>(spread / scale);
//
//        // Create the bar chart string
//        std::string chart = "[";
//
//        for (int i = 0; i < numChars; ++i) {
//            chart += "#"; // Use '#' character for the bar
//        }
//
//        chart += "]";
//
//        // Print the spread value and its bar chart
//        std::cout << "Spread: " << spread << " " << chart << std::endl;
//    }
//    // Print the bottom of the box
//    std::cout << boxTop << std::endl;
//}


