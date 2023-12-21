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
    Candlestick(OrderBook& orderBook);

    // Public member variables for open, high, low, and close
    double open;
    double high;
    double low;
    double close;
    
    // Function to create a vector of Candlestick objects from OrderBook data
    std::vector<Candlestick> generateCandlesticks(OrderBook& orderBook);


private:
    OrderBook& orderBookRef;   // Reference to OrderBook instance
};



#endif /* CandleStick_hpp */
