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


    
    // Function to create a vector of Candlestick objects from OrderBook data
    std::vector<Candlestick> generateCandlesticks(const OrderBook& orderBook);


private:

};



#endif /* CandleStick_hpp */
