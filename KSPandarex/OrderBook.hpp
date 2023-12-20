//
//  OrderBook.hpp
//  KSPandarex
/* OrderBook class presents a high level interface on all the orders in the order book data set, including query functions to find out which products are in the data set, and to retrieve a subset of the orders using filters. */
//  Created by Kristin Schumann on 12/12/2023.
//

#ifndef OrderBook_hpp
#define OrderBook_hpp

#include <stdio.h>
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include <string>


class OrderBook{
public:
    /** construct, reading a CSV data file*/
    OrderBook(std::string filename);
    /** vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();
    /** return vector of orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    
    /** functionality to move through time*/
    /** returns the earliest time in the orderbook*/
    std::string getEarliesttime();
    /** returns the next time after the
     * sent time in the orderbook
     * If there is no next timestamp, wraps around to the start
     * */
    std::string getNexttime(std::string timestamp);
    
    /** functionality to push user-typed order to end of OrderBookEntry() vector and to insert it by sorting through the timestamps*/
    void insertOrder(OrderBookEntry& order);
    
    /** function for the matching algorithm to process orders*/
    std::vector<OrderBookEntry> matchAsksToBids(std::string product,
                                                std::string timestamp);
    
    /** functionality for analysis of entries*/
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getMinPrice(std::vector<OrderBookEntry>& orders);
    
    /** KSStripes declaration of function to get a mean price at a given timestep*/
    double getMeanPrice(std::vector<OrderBookEntry>& orders);
    /** KSStripes declaration of a spread statistic - difference between lowest ask price and highest price bid*/
    double getSpread(const std::string& product, const std::string& timestamp);
    /**end of KSStripes addition**/
    
    

    
    
private:
    /** vector to store order book entries */
    std::vector<OrderBookEntry> orders;
    
    
};



#endif /* OrderBook_hpp */
