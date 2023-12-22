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
    
    /** KSStripes Define the function to get all candlestick data based on the orderbook at one time*/
    std::vector<Candlestick> getAllCandlesticks(OrderBook& orderBook,
                                                const std::string& currentTime);
    
    /**Function to create a vector of one Candlestick object based on user request
     *passing current time from PandaMain
     *passing OrderBooktype and product from UserInput
     *non-static because it will call different aspects of the OrderBook or of the UserInput at each vector generation*/
    std::vector<Candlestick> getOneCandlestick(OrderBook& orderBook,
                                                  const std::string& currentTime,
                                                  const std::string& product,
                                                  OrderBookType orderType);
    
    

private:
    OrderBook& orderBookRef;   // Reference to OrderBook instance
};



#endif /* CandleStick_hpp */
