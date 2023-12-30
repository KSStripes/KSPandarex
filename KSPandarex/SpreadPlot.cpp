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
#include <iomanip> // Included <iomanip> for setw
#include "OrderBook.hpp"
#include "PandaMain.hpp"


// Constructor that takes timestamps and an OrderBook reference
SpreadPlot::SpreadPlot(const std::string& currentTime,
                       OrderBook& orderBook)
    : orderBookRef(orderBook)
{
    // Constructor initialization
}

std::vector<std::pair<std::string, double>> SpreadPlot::getAllSpreads(const std::string& currentTime) {
    std::vector<std::pair<std::string, double>> spreadPairs;  // Initialize a vector of pairs

    // Get all known products
    std::vector<std::string> products = orderBookRef.getKnownProducts();

    // Iterate over all products
    for (const std::string& product : products) {
        // Calculate the spread for the current product and timestamp
        double spread = orderBookRef.getSpread(product, currentTime);
        // Round to 6 decimal places
        spread = std::round(spread * 1000000) / 1000000;
        
        // Create a pair of product name and spread and add it to the vector
        spreadPairs.push_back(std::make_pair(product, spread));
    }

    return spreadPairs;
}


void SpreadPlot::calculateBarChart(const std::vector<std::pair<std::string,
                                   double>>& spreadPairs) {
    // Define a scale for the spread values (adjust as needed)
    double scale = 0.01; // Each character represents 0.01 spread
    
    // Create the bar chart for each product
    for (const auto& pair : spreadPairs) {
        const std::string& product = pair.first;
        double spread = pair.second;
        
        // Calculate the number of characters in the bar
        int numChars = static_cast<int>(spread / scale);
        
        // Create the bar chart string
        std::string chart = "╔══════════════════════════════════════╗\n";
        chart += "║ " + product + " Spread: " + std::to_string(spread) + "                  \n";
        chart += "║ ";
        
        // Add '#' characters to the bar
        for (int i = 0; i < numChars; ++i) {
            chart += "█";
        }
        
        // Add spaces to fill the bar width
        for (int i = numChars; i < 50; ++i) {
            chart += " ";
        }
        
        chart += "\n";
        chart += "╚══════════════════════════════════════╝";
        
        // Print the bar chart
        std::cout << chart << std::endl;
    }
}





