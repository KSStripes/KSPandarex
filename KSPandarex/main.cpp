//
//  main.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 10/12/2023.
//

#include "OrderBookEntry.hpp"
#include "PandaMain.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

/*some functions based on W3 Challenge Exercises*/
/*double computeAveragePrice(std::vector<OrderBookEntry>& orders){
    double sum = 0.0;
    for (const auto& order : orders) {
        sum += order.price;
    }
    return orders.empty() ? 0.0 : sum / orders.size();
}

double computeLowPrice(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        return 0.0;
    }
    double lowPrice = std::numeric_limits<double>::max();
    for (const auto& order : orders) {
        lowPrice = std::min(lowPrice, order.price);
    }
    return lowPrice;
}

double computeHighPrice(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        return 0.0;
    }
    double highPrice = std::numeric_limits<double>::min();
    for (const auto& order : orders) {
        highPrice = std::max(highPrice, order.price);
    }
    return highPrice;
}

double computePriceSpread(std::vector<OrderBookEntry>& orders){
    if (orders.empty()) {
        return 0.0;
    }
    double lowPrice = std::numeric_limits<double>::max();
    double highPrice = std::numeric_limits<double>::min();

    for (const auto& order : orders) {
        lowPrice = std::min(lowPrice, order.price);
        highPrice = std::max(highPrice, order.price);
    }
    return highPrice - lowPrice;
}
*/

int main(){
    PandaMain app{};
    app.init();
    
    /*new vector for all orders*/
   // std::vector<OrderBookEntry> orders;
    
    /*populate vector with an instance of the object orderBookEntry*/
  /*  orders.push_back(OrderBookEntry(10000, 0.00023, "WorldTime", "UTC/BTC", OrderBookType::bid));
    orders.push_back(OrderBookEntry(10500, 0.000116, "Another time", "THE/BTC", OrderBookType::ask));
    orders.push_back(OrderBookEntry(3000, 0.0006666, "Another time", "Calin/BTC", OrderBookType::bid));
    orders.push_back(OrderBookEntry(500, 0.0007266, "Another time", "Alain/BTC", OrderBookType::ask));
    orders.push_back(OrderBookEntry(400010, 0.0025, "Another time", "Alain/BTC", OrderBookType::ask));
*/
    /* & avoids data being copied into order, indirectly accesses*/
   // for (const OrderBookEntry& order : orders){
        
        /* Accessing and printing the values*/
        /*std::cout << "================" << std::endl;
        std::cout << "Price: " << order.price << std::endl;
        std::cout << "Amount: " << order.amount << std::endl;
        std::cout << "Timestamp: " << order.timestamp << std::endl;
        std::cout << "Product: " << order.product << std::endl;*/

        /*Printing the enum class value*/
    /*    std::cout << "Order Type: ";
        if (order.orderType == OrderBookType::bid) {
            std::cout << "Bid" << std::endl;
        } else {
            std::cout << "Ask" << std::endl;
        }
    }*/
    
    /*Call math functions and print the result*/
    /*double averagePrice = computeAveragePrice(orders);
    std::cout << "Average Price: " << averagePrice << std::endl;

    double lowPrice = computeLowPrice(orders);
    std::cout << "Lowest Price: " << lowPrice << std::endl;
    
    double highPrice = computeHighPrice(orders);
    std::cout << "Highest Price: " << highPrice << std::endl;
    
    double priceSpread = computePriceSpread(orders);
    std::cout << "Price Spread: " << priceSpread<< std::endl;*/
    
    return 0;
}
