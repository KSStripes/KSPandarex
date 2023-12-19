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

/**
 * Constructs an OrderBook object by reading order data from a CSV file.
 *
 * @param filename The path to the CSV file containing order book entries.
 */
OrderBook::OrderBook(std::string filename) {
    // Read orders from a CSV file. Assumes the CSVReader class handles parsing.
    orders = CSVReader::readCSV(filename);
}

/**
 * Retrieves a list of unique products present in the order book.
 *
 * This method iterates over all orders, uses a map to identify unique products,
 * and then converts the map keys to a vector.
 *
 * @return A vector of strings, each representing a unique product.
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
 *
 * This method filters the orders based on the type, product, and timestamp,
 * creating a subset of orders that match all these criteria.
 *
 * @param type The type of the order (e.g., bid, ask).
 * @param product The product for which orders are to be filtered.
 * @param timestamp The timestamp at which orders are to be filtered.
 * @return A vector of OrderBookEntry objects that match the specified criteria.
 */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                  std::string product,
                                                  std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;

    // Iterate over all orders and select those that match the given type, product, and timestamp.
    for (OrderBookEntry& e : orders) {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp) {
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

/** functionality for analysis of entries*/
//getting the highest price
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for (OrderBookEntry& e : orders){
        if (e.price > max)max = e.price;
    }
    return max;
}

//getting the lowest price
double OrderBook::getMinPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders){
        if (e.price < min)
            min = e.price;
    }
    return min;
}

/** KS implementation of the mean price*/
double OrderBook::getMeanPrice(std::vector<OrderBookEntry>& orders){
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

/** KS implement the spread statistics - difference between lowest ask price and highest price bid*/
double OrderBook::getSpread(const std::string& product, const std::string& timestamp){
    //vector for all asks of a given product at one timestamp
    std::vector<OrderBookEntry> numAsks = getOrders(OrderBookType::ask, product, timestamp);
    //vector for all bids of a given product at one timestamp
    std::vector<OrderBookEntry> numBids = getOrders(OrderBookType::bid, product, timestamp);
    
    double minAsk = getMinPrice(numAsks);
    double maxBid = getHighPrice(numBids);
    
    return minAsk - maxBid;
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
    
    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAscend);
    
    //sort bids lowest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDescend);
    
    //for ref ask in asks (entry ref e in asks)
    for (OrderBookEntry& ask : asks){
        //iterate over the bids (entry ref bid in bids)
        for (OrderBookEntry& bid : bids){
            //if bid.price >= ask.price we have a match
            if (bid.price >= ask.price){
                /** 1. create a new sale passing all OrderBookEntry constructor arguments, setting the sale price to the ask price, not the bid price*/
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};
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
