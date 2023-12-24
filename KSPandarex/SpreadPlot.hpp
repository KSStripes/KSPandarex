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
#include <string>
#include "OrderBook.hpp"
#include "PandaMain.hpp"


class SpreadPlot {
public:
    // Constructor that takes a vector of doubles and a vector of timestamps
    SpreadPlot(const std::string& currentTime,
               OrderBook& orderBook);

    // Function to calculate the spread data
    void calculateSpreadData();
    // Function to print the enhanced bar chart for each spread value
    void printSpreadCharts();

private:
//    std::vector<std::pair<double, std::string>> data; // A vector of pairs for spread data and timestamps
//
//    // Function to calculate the bar chart string with a minimum length
//    std::string calculateBarChart(double spread, int minChartLength);
//    
//    OrderBook& orderBookRef;   // Reference to OrderBook instance
//    std::vector<double> spreadData_; // Member variable to store spread data
//    OrderBookType orderType_;       // Member variable to store order type
//};
    
    OrderBook& orderBookRef;
     std::vector<std::string> timestamps;
     std::vector<double> spreadData; // Stores calculated spread data

     // Function to calculate the bar chart string with a minimum length
     std::string calculateBarChart(double spread, int minChartLength);
 };

#endif /* SpreadPlot_hpp */

    

