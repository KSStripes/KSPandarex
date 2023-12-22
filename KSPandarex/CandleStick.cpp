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
#include <set>

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


/** KSStripes Define the function to get all candlestick data based on the orderbook at one time*/
std::vector<Candlestick> Candlestick::getAllCandlesticks(OrderBook& orderBook,
                                                           const std::string& currentTime) {
    std::vector<Candlestick> candlesticks; // Initialize vector of Candlestick objects
    
//    std::string currentTime = orderBook.getEarliesttime(); // Set up time
    OrderBookType orderType = OrderBookType::ask;

    
    // Get all known products
    std::vector<std::string> products = orderBook.getKnownProducts();

    // Iterate over all products
    for (const std::string& product : products) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        std::set<std::string> uniqueTimestamps; // Keep track of unique timestamps

        // Iterate over the entries for the current product
        for (const OrderBookEntry& entry : entries) {
            const std::string& timestamp = entry.timestamp;

            // Check if the timestamp is unique
            if (uniqueTimestamps.find(timestamp) == uniqueTimestamps.end()) {
                // Calculate open for the previous timestamp
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = orderBook.getMeanOpen(orderType, product, prevT);
                // Calculate high, low, close values for the current timestamp
                double high = OrderBook::getHighPrice(entries);
                double low = OrderBook::getMinPrice(entries);
                double close = orderBook.getMeanPrice(entries);

                // Create a Candlestick object and set its member variables
                Candlestick candlestick(orderBook);
                candlestick.open = open;
                candlestick.high = high;
                candlestick.low = low;
                candlestick.close = close;

                // Add the Candlestick object to the vector
                candlesticks.push_back(candlestick);

                // Mark the timestamp as seen
                uniqueTimestamps.insert(timestamp);
            }
        }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
}

/**KSStripes defined function to create a vector of one Candlestick object based on user request
 *passing current time from PandaMain
 *passing OrderBooktype and product from UserInput
 *non-static because it will call different aspects of the OrderBook or of the UserInput at each vector generation*/
std::vector<Candlestick> Candlestick::getOneCandlestick(OrderBook& orderBook,
                                                        const std::string& currentTime,
                                                        const std::string& product,
                                                        OrderBookType orderType){
    
    std::vector<Candlestick> candlesticks; // Initialize vector of Candlestick objects

    // Iterate over all products
//    for (const std::string& product : products) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        std::set<std::string> uniqueTimestamps; // Keep track of unique timestamps

        // Iterate over the entries for the current product
        for (const OrderBookEntry& entry : entries) {
            const std::string& timestamp = entry.timestamp;

            // Check if the timestamp is unique
            if (uniqueTimestamps.find(timestamp) == uniqueTimestamps.end()) {
                // Calculate open for the previous timestamp
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = orderBook.getMeanOpen(orderType, product, prevT);
                // Calculate high, low, close values for the current timestamp
                double high = OrderBook::getHighPrice(entries);
                double low = OrderBook::getMinPrice(entries);
                double close = orderBook.getMeanPrice(entries);

                // Create a Candlestick object and set its member variables
                Candlestick candlestick(orderBook);
                candlestick.open = open;
                candlestick.high = high;
                candlestick.low = low;
                candlestick.close = close;

                // Add the Candlestick object to the vector
                candlesticks.push_back(candlestick);

                // Mark the timestamp as seen
                uniqueTimestamps.insert(timestamp);
            }
//        }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
    
    
    
    
}


