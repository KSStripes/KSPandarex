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
    //function to calculate all spreads based on current time and on orderbook spread calc
    std::vector<std::pair<std::string, double>> getAllSpreads(const std::string& currentTime);
    void calculateBarChart(const std::vector<std::pair<std::string, double>>& spreadPairs);

private:
    OrderBook& orderBookRef;
    std::vector<std::string> timestamps;
    std::vector<double> spreadData; // Stores calculated spread data

    
 };

#endif /* SpreadPlot_hpp */

    

