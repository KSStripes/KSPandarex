//
//  CandleStick.hpp
//  KSPandarex
//
//  Created by Kristin Schumann on 20/12/2023.
//

#ifndef CandleStick_hpp
#define CandleStick_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "OrderBook.hpp"
#include "OrderBookEntry.hpp"

class Candlestick {
public:
    // Constructor that takes references to OrderBook and initializes the candlestick data
    Candlestick(OrderBook& orderBook);

    /** functionality for analysis of entries*/
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getMinPrice(std::vector<OrderBookEntry>& orders);
    
    /** KSStripes declaration of function to get a mean price at a given timestep*/
    static double getMeanPrice(std::vector<OrderBookEntry>& orders);
    /** KSStripes declaration of a spread statistic - difference between lowest ask price and highest price bid*/
    double getSpread(const std::string& product, const std::string& timestamp);
    /**end of KSStripes addition**/
    
    // Function to create a vector of Candlestick objects from OrderBook data
    std::vector<Candlestick> generateCandlesticks(const OrderBook& orderBook);


private:
    OrderBook& orderBookRef; // Declare orderBookRef as a member
};



#endif /* CandleStick_hpp */
