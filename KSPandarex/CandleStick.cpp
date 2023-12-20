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
Candlestick::Candlestick(OrderBook& orderBook)
    : orderBookRef(orderBook)
{
}


/** functionality for analysis of entries*/
//getting the highest price
double Candlestick::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for (OrderBookEntry& e : orders){
        if (e.price > max)max = e.price;
    }
    return max;
}

//getting the lowest price
double Candlestick::getMinPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders){
        if (e.price < min)
            min = e.price;
    }
    return min;
}

/** KSStripes  implementation of the mean price*/
double Candlestick::getMeanPrice(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        return 0.0; // or some appropriate default value
    }

    double sum = 0.0;
    for (const OrderBookEntry& e : orders){
        sum += e.price;
    }

    double mean = sum / orders.size();
    return mean;
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
double Candlestick::getSpread(const std::string& product, const std::string& timestamp){
    //vector for all asks of a given product at one timestamp
    std::vector<OrderBookEntry> numAsks = orderBookRef.getOrders(OrderBookType::ask, product, timestamp);
    //vector for all bids of a given product at one timestamp
    std::vector<OrderBookEntry> numBids = orderBookRef.getOrders(OrderBookType::bid, product, timestamp);
    
    double minAsk = getMinPrice(numAsks);
    double maxBid = getHighPrice(numBids);
    
    return minAsk - maxBid;
}
/**end of KSStripes addition to code**/
