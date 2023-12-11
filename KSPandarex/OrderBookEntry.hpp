//
//  OrderBookEntry.hpp
//  KSPandarex
//
//  Created by Kristin Schumann on 10/12/2023.
//

#ifndef OrderBookEntry_hpp
#define OrderBookEntry_hpp

#include <stdio.h>
#include <string>

/*enum class made globally accessible*/
enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry{
public:
    /* Constructor */
    OrderBookEntry(double _price,
                   double _amount,
                   std::string _timestamp,
                   std::string _product,
                   OrderBookType _orderType);
    static OrderBookType stringToOrderBookType(std::string s);

// make these private later when I have integrated the print option into the constructor
//private:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};

#endif /* OrderBookEntry_hpp */
