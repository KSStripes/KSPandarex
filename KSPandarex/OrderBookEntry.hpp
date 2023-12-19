//
//  OrderBookEntry.hpp
//  KSPandarex
/* The OrderBookEntry represents a row in the order book data set (i.e. a single order in the order book). It can be a bid or an ask order. */
//  Created by Kristin Schumann on 10/12/2023.
//

#ifndef OrderBookEntry_hpp
#define OrderBookEntry_hpp

#include <stdio.h>
#include <string>

/*enum class made globally accessible*/
enum class OrderBookType{bid, ask, unknown, sale};

class OrderBookEntry{
public:
    /* Constructor */
    OrderBookEntry(double _price,
                   double _amount,
                   std::string _timestamp,
                   std::string _product,
                   OrderBookType _orderType);
    static OrderBookType stringToOrderBookType(std::string s);
    
    /**function to sort  OrderBookEntry() vector by timestamp, to class a new input added to end**/
    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    }
    
    /**functions to sort  OrderBookEntry() vector by price - ascending and descending**/
    static bool compareByPriceAscend(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }
    
    static bool compareByPriceDescend(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};

#endif /* OrderBookEntry_hpp */
