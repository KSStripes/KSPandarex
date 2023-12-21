//
//  CandleStick.cpp
//  KSPandarex
//
/* Candlestick class presents a the interface to retrieve the OrderBookEnntry vectors and the timesteps from the orderbook.  These values are then passed into a vector for one candlestick for one product at one timeframe. Finally this vector is presented graphically.  */

//  Created by Kristin Schumann on 20/12/2023.
//

#include "CandleStick.hpp"
#include "OrderBook.hpp"
#include "OrderBookEntry.hpp"
#include <iostream>
#include <vector>

/**constructor passing OrderBook as a reference**/
Candlestick::Candlestick(const std::vector<OrderBookEntry>& entries,
                         OrderBook& orderBook)
//    :   orderBookEntries(entries),
//        orderBookRef(orderBook)
{
    //Constructor
}




//vector for one candlestick for one product at one timeframe.
std::vector<Candlestick> generateCandlesticks(const OrderBook& orderBook) {
    std::vector<Candlestick> candlesticks;

//    
//    // Get the list of unique products from the OrderBook
//    std::vector<std::string> products = orderBook.getKnownProducts();
//
//    // Iterate through each product
//    for (const std::string& product : products) {
//        // Get the list of unique timestamps for the product
//        std::vector<std::string> timestamps = orderBook.getUniqueTimestamps(product);
//
//        // Iterate through each timestamp
//        for (const std::string& timestamp : timestamps) {
//            // Get orders for the product and timestamp
//            std::vector<OrderBookEntry> orders = orderBook.getOrders(product, timestamp);
//
//            if (!orders.empty()) {
//                // Calculate the open, high, low, and close for the timeframe
//                double open = Candlestick::getMeanOpen(OrderBookType::ask, product, timestamp, orderBook);
//                double high = Candlestick::getHighPrice(orders);
//                double low = Candlestick::getMinPrice(orders);
//                double close = Candlestick::getMeanClose(orders);
//
//                // Create a Candlestick object with these values
//                Candlestick candlestick(open, high, low, close);
//
//                // Add the Candlestick to the vector
//                candlesticks.push_back(candlestick);
//            }
//        }
//    }

    return candlesticks;
}





