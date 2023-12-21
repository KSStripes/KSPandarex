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
    // Constructor that the orderbook as a reference
    Candlestick(const std::vector<OrderBookEntry>& entries,
                OrderBook& orderBook);

    /** functionality for analysis of entries */
    /**highest price of all orders of one product**/
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    /**lowest price of all orders of one product**/
    static double getMinPrice(std::vector<OrderBookEntry>& orders);
    
    /**add function to calculate getOpen = the average price per unit in the previous timeframe**/
    static double getMeanOpen(OrderBookType type,
                              const std::string& product,
                              const std::string& timestamp,
                              OrderBook& orderBookRef);
    /**add function to calculate getClose = the average price per unit in the current timeframe**/
    static double getMeanClose(std::vector<OrderBookEntry>& orders);
    
    
    /** KSStripes declaration of a spread statistic - difference between lowest ask price and highest price bid*/
    //double getSpread(const std::string& product, const std::string& timestamp);
    /**end of KSStripes addition**/
    
    // Function to create a vector of Candlestick objects from OrderBook data
    std::vector<Candlestick> generateCandlesticks(const OrderBook& orderBook);


private:
    const std::vector<OrderBookEntry>& orderBookEntries; // Reference to order book entries
    OrderBook& orderBookRef; // Declare orderBookRef as a member
};



#endif /* CandleStick_hpp */
