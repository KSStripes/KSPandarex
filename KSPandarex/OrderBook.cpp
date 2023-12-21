//
//  OrderBook.cpp
//  KSPandarex
/* OrderBook class presents a high level interface on all the orders in the order book data set, including query functions to find out which products are in the data set, and to retrieve a subset of the orders using filters. */
//  Created by Kristin Schumann on 12/12/2023.
//

#include "OrderBook.hpp"
#include <string>
#include "CSVReader.hpp"
#include <map>
#include <algorithm>
#include <iostream>

/**
 * Constructs an OrderBook object by reading order data from a CSV file.
 */
OrderBook::OrderBook(std::string filename) {
    // Read orders from a CSV file. Assumes the CSVReader class handles parsing.
    orders = CSVReader::readCSV(filename);
}

/**
 * Retrieves a list of unique products present in the order book.
 * This method iterates over all orders, uses a map to identify unique products,
 * and then converts the map keys to a vector.
 */
std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    // Iterate over all orders and map each product to true (indicating its presence).
    for (OrderBookEntry& e : orders) {
        prodMap[e.product] = true;
    }

    // Convert the map keys (unique products) to a vector.
    for (auto const& e : prodMap) {
        products.push_back(e.first);
    }

    return products; // Returns a unique list of products
}

/**
 * Filters and returns a subset of orders based on specified criteria.
 * This method filters the orders based on the type, product, and timestamp,
 * creating a subset of orders that match all these criteria.
 */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                  std::string product,
                                                  std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;

    // Iterate over all orders and select those that match the given type, product, and timestamp.
    for (OrderBookEntry& e : orders) {
        if (e.orderType == type && 
            e.product == product &&
            e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }

    return orders_sub; // Returns the filtered list of orders
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
    //push typed order to the end of OrderBookEntry()vector
    orders.push_back(order);
    //insert new order at correct place by sorting through timestamps
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}


/** functionality to get earliest time*/
std::string OrderBook::getEarliesttime(){
    return orders[0].timestamp;
}

/** functionality to get next  time*/
std::string OrderBook::getNexttime(std::string timestamp){
    //if we find a timestamp that's higher than the previous one, go to next time 
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders){
        
        if (e.timestamp > timestamp){
            next_timestamp = e.timestamp;
            break;
        }
    }
    //if  there is no next timestamp in the OrderBook, loop to beginning
    if (next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }
    
    return next_timestamp;
}

/** KSStripess implemented functionality to get previous time*/
std::string OrderBook::getPreviousTime(std::string timestamp) {
    std::string previous_timestamp = "";

    // Iterate through the orders to find the previous timestamp
    for (OrderBookEntry& e : orders) {
        // If we find a timestamp that's lower than the given one, exit the loop
        if (e.timestamp < timestamp) {
            previous_timestamp = e.timestamp;
            break;
        }
    }

    // If there is no previous timestamp in the OrderBook, loop to the end
    if (previous_timestamp == "") {
        previous_timestamp = orders.back().timestamp;
    }

    return previous_timestamp;
}

std::vector<OrderBookEntry> OrderBook::orderAtPrevTime(OrderBookType type,
                                                       const std::string& product,
                                                       const std::string& timestamp){
    // Get the previous timestamp using OrderBook's getPreviousTime function
    std::string previousTimestamp = getPreviousTime(timestamp);

    // Get orders for the specified product, the previous timestamp, and the specified order book type
    std::vector<OrderBookEntry> prevOrders = getOrders(type, product, previousTimestamp);

    return prevOrders;
}

/**end of KSStripes addition**/


/** function for the matching algorithm to process orders*/
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product,
                                                       std::string timestamp){
    //asks = orderbook asks (reuse getOrders())
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
    
    //bids = orderbook bids (reuse getOrders())
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);
    
    // sales = []
    std::vector<OrderBookEntry> sales;
    
    // Check to ensure we have bids and asks to process.
    if (asks.size() == 0 || bids.size() == 0)
    {
        std::cout << " OrderBook::matchAsksToBids no bids or asks" << std::endl;
        return sales;
    }
    
    
    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAscend);
    
    //sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDescend);
    
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].price << std::endl;
    
    //for ref ask in asks (entry ref e in asks)
    for (OrderBookEntry& ask : asks){
        //iterate over the bids (entry ref bid in bids)
        for (OrderBookEntry& bid : bids){
            //if bid.price >= ask.price we have a match
            if (bid.price >= ask.price){
                
                /** 1. create a new sale passing all OrderBookEntry constructor arguments, setting the sale price to the ask price, not the bid price, implement logic to attribute bidsale or asksale according to user input*/
                OrderBookEntry sale{ask.price,
                                    0,
                                    timestamp,
                                    product,
                                    OrderBookType::asksale};

                    if (bid.username == "simuser")
                    {
                        sale.username = "simuser";
                        sale.orderType = OrderBookType::bidsale;
                    }
                    if (ask.username == "simuser")
                    {
                        sale.username = "simuser";
                        sale.orderType =  OrderBookType::asksale;
                    }
                /** 2. include logic to determine sales price and go to next order**/
                if (bid.amount == ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale); //add sale to sales
                    bid.amount = 0; //reset bid to make sure it is not processed again
                    break; //go onto next ask
                }
                if (bid.amount > ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale); //add sale to sales
                    bid.amount = bid.amount - ask.amount; //use bid.amount to process next ask
                    break; //go onto next ask, as ask has been fulfilled
                }
                if (bid.amount < ask.amount &&
                    bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale); //add sale to sales
                    ask.amount = ask.amount - bid.amount; //allow further bids to process the remaining amount
                    bid.amount = 0; //reset bid to make sure it is not processed again
                    continue; //go onto next bid as ask has not been fulfilled
                }
            }
        }
    }
    return sales;
}
