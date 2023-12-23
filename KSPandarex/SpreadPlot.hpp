//
//  SpreadPlot.hpp
//  KSPandarex
//
//  Created by Kristin Schumann on 23/12/2023.
//

#ifndef SpreadPlot_hpp
#define SpreadPlot_hpp

#include <stdio.h>
#include <vector>


class SpreadPlot {
public:
    // Constructor that takes a vector of doubles
    SpreadPlot(const std::vector<double>& spreadData);

    // Function to print the enhanced bar chart for each spread value
    void printSpreadCharts();

private:
    std::vector<double> spreadData_; // Store the spread data

    // Function to calculate the bar chart string with a minimum length
    std::string calculateBarChart(double spread, int minChartLength);
};

#endif /* SpreadPlot_hpp */
