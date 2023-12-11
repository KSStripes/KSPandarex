//
//  OrderBookEntry.cpp
//  KSPandarex
//
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
