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

// Constructor implementation
SpreadPlot::SpreadPlot(const std::vector<double>& spreadData)
    : spreadData_(spreadData) {
    // Constructor code here
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

    // Iterate over each spread value in the vector
    for (const double& spread : spreadData_) {
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


