//
//  OrderBookEntry.cpp
//  KSPandarex
/* The OrderBookEntry represents a row in the order book data set (i.e. a single order in the order book). It can be a bid or an ask order. */
//  Created by Kristin Schumann on 10/12/2023.
//

#include "OrderBookEntry.hpp"
#include "iostream"

OrderBookEntry::OrderBookEntry(double _price,
               double _amount,
               std::string _timestamp,
               std::string _product,
               OrderBookType _orderType)
/*initialize the member variables and pass arguments*/
:   price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    orderType(_orderType)
{
    
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if ( s== "ask"){
        return OrderBookType::ask;
    }
    if (s== "bid"){
        return OrderBookType::bid;;
    }
    return OrderBookType::unknown;
}

/**function to sort  OrderBookEntry() vector by timestamp, in case new input has been addedt**/
static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.timestamp < e2.timestamp; //if this is true, elements need no swapping
}
