//
//  CandleStick.cpp
//  KSPandarex
//
/* Candlestick class presents a the interface to retrieve the OrderBookEnntry vectors and the timesteps from the orderbook. From this the candlestick computes for each product the high, low, open and close values. These values are then passed into a vector for one candlestick for one product at one timeframe. Finally this vector is presented graphically.  */

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
    :   orderBookEntries(entries),
        orderBookRef(orderBook)
{
    //Constructor
}


/** functionality for analysis of entries*/
/**getting the highest price of one product, at a specific timestamp in orderBookType bid or ask*/
double Candlestick::getHighPrice(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        // Handle the case where the orders vector is empty
        return 0.0;
    }
    double max = orders[0].price;
    for (OrderBookEntry& e : orders){
        if (e.price > max)max = e.price;
    }
    return max;
}


/**getting the lowest price of one product, at a specific timestamp in orderBookType bid or ask*/
double Candlestick::getMinPrice(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        // Handle the case where the orders vector is empty
        return 0.0;
    }
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders){
        if (e.price < min)
            min = e.price;
    }
    return min;
}


/**add function to calculate getOpen = the average price per unit in the previous timeframe**/
double Candlestick::getMeanOpen(OrderBookType type,
                                const std::string& product,
                                const std::string& timestamp,
                                OrderBook& orderBookRef) {
                                
    // Get the previous timestamp using OrderBook's getPreviousTime function
    std::string previousTimestamp = orderBookRef.getPreviousTime(timestamp);

    // Get orders for the specified product, the previous timestamp, and the specified order book type
    std::vector<OrderBookEntry> orders = orderBookRef.orderAtPrevTime(type, product, previousTimestamp);


    if (orders.empty()) {
        return 0.0; // Return 0 if there are no orders for the specified product, type, and previous timestamp.
    }

    double sum = 0.0;
    for (const OrderBookEntry& e : orders) {
        sum += e.price; // Calculate the sum of prices for all orders at the previous timestamp.
    }

    double meanOpen = sum / orders.size(); // Calculate the mean open price by dividing the sum by the number of orders.
    return meanOpen;
}


/**add function to calculate getClose = the average price per unit in the current timeframe**/
double Candlestick::getMeanClose(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        return 0.0; // or some appropriate default value
    }

    double sum = 0.0;
    for (const OrderBookEntry& e : orders){
        sum += e.price;
    }

    double meanClose = sum / orders.size();
    return meanClose;
}

/**end of KSStripes addition to code**/

////////////////

//vector for one candlestick for one product at one timeframe.
std::vector<Candlestick> generateCandlesticks(const OrderBook& orderBook) {
    std::vector<Candlestick> candlesticks;
    
    // Generate Candlestick objects and add them to the vector
    // You can adjust the logic for creating candlesticks based on your requirements
    
    // For example, you can create a Candlestick for each time period in the OrderBook
    // and add them to the vector
    
    return candlesticks;
}




/** KSStripes implementation of spread statistics - difference between lowest ask price and highest price bid*/
//double Candlestick::getSpread(const std::string& product, const std::string& timestamp){
//    //vector for all asks of a given product at one timestamp
//    std::vector<OrderBookEntry> numAsks = orderBookRef.getOrders(OrderBookType::ask, product, timestamp);
//    //vector for all bids of a given product at one timestamp
//    std::vector<OrderBookEntry> numBids = orderBookRef.getOrders(OrderBookType::bid, product, timestamp);
//    
//    double minAsk = getMinPrice(numAsks);
//    double maxBid = getHighPrice(numBids);
//    
//    return minAsk - maxBid;
//}
/**end of KSStripes addition to code**/
