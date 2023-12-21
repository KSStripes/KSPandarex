//
//  CandleStick.cpp
//  KSPandarex
///

//  Created by Kristin Schumann on 20/12/2023.
//

#include "CandleStick.hpp"
#include "OrderBook.hpp"
#include "OrderBookEntry.hpp"
#include <iostream>
#include <vector>

/** function generateCandlesticks
 * takes orderBook as a reference
 * initializes a vector of vectors std::vector<Candlestick> candlesticks returns a vector of candlestick objects
 * declares double variables for open, high, low and close as arguments of each candlestick object
 * computes these four variables by calling the corresponding OrderBook functions
 * : open = orderBook.getMeanOpen(OrderBookType::ask, p, prevT)
 * : high = OrderBook::getHighPrice(entries)
 * : low = OrderBook::getMinPrice(entries)
 * : close = OrderBook::getMeanPrice(entries)
 * Loops over all orderBookEntry& orders
 * for each timestep retrieves open, high, low, close and passes them into an object candlestick
 * pushes this object back into the vector of vectors <Candlestick>
 * returns a vector of candlestick objects
 */



/**constructor passing OrderBook as a reference**/
Candlestick::Candlestick(OrderBook& orderBook)
    :   orderBookRef(orderBook)
{
    //Constructor
}


// Define the function generateCandlesticks
std::vector<Candlestick> Candlestick::generateCandlesticks(OrderBook& orderBook) {
    std::vector<Candlestick> candlesticks; // Initialize vector of Candlestick objects
    
    std::string currentTime = orderBook.getEarliesttime(); // Set up time

    // Loop over all products (you may need to get product names from orderBook)
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

        // Loop over all OrderBookEntry& orders
        for (OrderBookEntry& e : entries) {
            std::string prevT = orderBook.getPreviousTime(e.timestamp);
            double open = orderBook.getMeanOpen(OrderBookType::ask, e.product, prevT);
            double high = OrderBook::getHighPrice(entries);
            double low = OrderBook::getMinPrice(entries);
            double close = OrderBook::getMeanPrice(entries);

            // Create a Candlestick object and set its member variables
            Candlestick candlestick(orderBook);
            candlestick.open = open;
            candlestick.high = high;
            candlestick.low = low;
            candlestick.close = close;

            // Add the Candlestick object to the vector
            candlesticks.push_back(candlestick);
        }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
}





