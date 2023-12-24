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
#include "OrderBook.hpp"
#include "PandaMain.hpp"


// Constructor that takes timestamps and an OrderBook reference
SpreadPlot::SpreadPlot(const std::string& currentTime,
                       OrderBook& orderBook)
    : orderBookRef(orderBook){
    // Constructor initialization
}

// Function to calculate the spread data
void SpreadPlot::calculateSpreadData() {
    spreadData.clear(); // Clear any existing data

    for (const std::string& timestamp : timestamps) {
        // Calculate and get the spread for each timestamp using orderBookRef
        double spread = orderBookRef.getSpread(OrderBookType::ask, "product", timestamp);

        // Add the calculated spread to the spreadData vector
        spreadData.push_back(spread);
    }
}

// Function to calculate the bar chart string with a minimum length
std::string SpreadPlot::calculateBarChart(double spread, int minChartLength) {
    // Define a scale for the spread values (adjust as needed)
    double scale = 0.1; // Each character represents 0.1 spread

    // Calculate the number of characters in the bar
    int numChars = static_cast<int>(spread / scale);

    // Ensure the chart has at least the specified minimum length
    if (numChars < minChartLength) {
        numChars = minChartLength;
    }

    // Create the bar chart string
    std::string chart = "[";

    for (int i = 0; i < numChars; ++i) {
        chart += "#"; // Use '#' character for the bar
    }

    chart += "]";

    return chart;
}

// Function to print the enhanced bar chart for each spread value
void SpreadPlot::printSpreadCharts() {
    // Define a minimum chart length (minimum number of characters)
    int minChartLength = 50;
    
    // Define a scale for the spread values (adjust as needed)
    double scale = 0.1; // Each character represents 0.1 spread

    // Print a box around the bar chart
    std::string boxTop = "+" + std::string(minChartLength, '-') + "+";
    std::cout << boxTop << std::endl;

    // Calculate the spread data if not already calculated
    if (spreadData.empty()) {
        calculateSpreadData();
    }

    // Iterate over each spread value in the vector
    for (const double& spread : spreadData) {
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
    // Print the bottom of the box
    std::cout << boxTop << std::endl;
}


//// Implementation of the constructor
//SpreadPlot::SpreadPlot(const std::vector<double>& spreadData, 
//                       const std::vector<std::string>& timestamps,
//                       OrderBook& orderBook)
//    : orderBookRef(orderBook)
//{
//    // Make sure both vectors have the same size
//    if (spreadData.size() != timestamps.size()) {
//        throw std::invalid_argument("Input vectors must have the same size.");
//    }
//
//    // Combine the spreadData and timestamps into pairs and store in the data vector
//    for (size_t i = 0; i < spreadData.size(); ++i) {
//        data.push_back(std::make_pair(spreadData[i], timestamps[i]));
//    }
//}
//
//
///**function to create a vector of objects of all spreadplots, taking as inputs the current time and the orderbook entry **/
// std::vector<std::pair<double, std::string>>SpreadPlot::getAllSpreads(OrderBook& orderBook,
//                                                                      const std::string& currentTime) 
//{
//     std::vector<std::pair<double, std::string>> spreadPairs; // Initialize vector of pairs
//     OrderBookType orderType = OrderBookType::ask;
//
//     // Get all known products
//      std::vector<std::string> products = orderBook.getKnownProducts();
//     
//     // Iterate over all products
//      for (const std::string& product : products) {
//          std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);
//
//          // Iterate over the entries for the current product
//          for (const OrderBookEntry& entry : entries) {
//              const std::string& timestamp = entry.timestamp;
//
//              // Call orderBook.getSpread() to obtain the spread data
//              double spread = orderBook.getSpread(orderType, product, timestamp);
//
//              // Create a pair of spread data and timestamp and push it into the vector
//              spreadPairs.push_back(std::make_pair(spread, timestamp));
//          }
//      }
//
//      // Return the vector of pairs
//      return spreadPairs;
//  }
//
//// Function to calculate the bar chart string with a minimum length
//std::string SpreadPlot::calculateBarChart(double spread, int minChartLength) {
//    // Define a scale for the spread values (adjust as needed)
//    double scale = 0.1; // Each character represents 0.1 spread
//
//    // Calculate the number of characters in the bar
//    int numChars = static_cast<int>(spread / scale);
//
//    // Ensure the chart has at least the specified minimum length
//    if (numChars < minChartLength) {
//        numChars = minChartLength;
//    }
//
//    // Create the bar chart string
//    std::string chart = "[";
//
//    for (int i = 0; i < numChars; ++i) {
//        chart += "#"; // Use '#' character for the bar
//    }
//
//    chart += "]";
//
//    return chart;
//}
//
//// Function to print the enhanced bar chart for each spread value
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
//    for (const double& spread : spreadData_) {
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


