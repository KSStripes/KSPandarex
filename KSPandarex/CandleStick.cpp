//
//  CandleStick.cpp
//  KSPandarex
///

//  Created by Kristin Schumann on 20/12/2023.
//

#include "CandleStick.hpp"
#include "OrderBook.hpp"
#include "OrderBookEntry.hpp"
#include <iostream>
#include <vector>
#include <set> //included to set unique timestamps
#include <iomanip> //inluded to set maximum print lenght of a double to 2decimals
#include <regex> //added to allow for string manipulation of the timestamp for printing

/** function generateCandlesticks
 * takes orderBook as a reference
 * initializes a vector of vectors std::vector<Candlestick> candlesticks returns a vector of candlestick objects
 * declares double variables for open, high, low and close as arguments of each candlestick object
 * computes these four variables by calling the corresponding OrderBook functions
 * : open = orderBook.getMeanOpen(OrderBookType::ask, p, prevT)
 * : high = OrderBook::getHighPrice(entries)
 * : low = OrderBook::getMinPrice(entries)
 * : close = OrderBook::getMeanPrice(entries)
 * Loops over all orderBookEntry& orders
 * for each timestep retrieves open, high, low, close and passes them into an object candlestick
 * pushes this object back into the vector of vectors <Candlestick>
 * returns a vector of candlestick objects
 */



/**constructor passing OrderBook as a reference**/
Candlestick::Candlestick(OrderBook& orderBook)
    :   orderBookRef(orderBook)
{
    //Constructor
}


/**KSStripes added a helper function to allow for string manipulation that will make it possible to print shorter timestamps**/
std::string Candlestick::extractTime(const std::string& currentTime) const {
    // Define a regular expression pattern to match the time portion
    std::regex pattern("\\d{2}:\\d{2}:\\d{2}");

    // Search for the pattern in the timestamp
    std::smatch match;
    if (std::regex_search(currentTime, match, pattern)) {
        // The first match found contains the time portion
        return match[0];
    }

    // Return an empty string if no match is found
    return "";
}


/** KSStripes Define the function to get all candlestick data based on the orderbook at one time*/
std::vector<Candlestick> Candlestick::getAllCandlesticks(OrderBook& orderBook,
                                                        const std::string& currentTime) {
    std::vector<Candlestick> candlesticks; // Initialize vector of Candlestick objects
    
//    std::string currentTime = orderBook.getEarliesttime(); // Set up time
    OrderBookType orderType = OrderBookType::ask;

    
    // Get all known products
    std::vector<std::string> products = orderBook.getKnownProducts();

    // Iterate over all products
    for (const std::string& product : products) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        std::set<std::string> uniqueTimestamps; // Keep track of unique timestamps

        // Iterate over the entries for the current product
        for (const OrderBookEntry& entry : entries) {
            const std::string& timestamp = entry.timestamp;

            // Check if the timestamp is unique
            if (uniqueTimestamps.find(timestamp) == uniqueTimestamps.end()) {

                /** Calculate open for the previous timestamp, round to 5 decimal places*/
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = std::round(orderBook.getMeanOpen(orderType, product, prevT) * 100000) / 100000;

                /**Calculate high, low, close values for the current timestamp rounded to 5 decimal places*/
                double high = std::round(OrderBook::getHighPrice(entries) * 100000) / 100000;
                double low = std::round(OrderBook::getMinPrice(entries) * 100000) / 100000;
                double close = std::round(orderBook.getMeanPrice(entries) * 100000) / 100000;

                // Create a Candlestick object and set its member variables
                Candlestick candlestick(orderBook);
                candlestick.open = open;
                candlestick.high = high;
                candlestick.low = low;
                candlestick.close = close;

                // Add the Candlestick object to the vector
                candlesticks.push_back(candlestick);

                // Mark the timestamp as seen
                uniqueTimestamps.insert(timestamp);
            }
        }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
}

/**KSStripes defined function to create a vector of one Candlestick object based on user request
 *passing current time from PandaMain
 *passing OrderBooktype and product from UserInput
 *non-static because it will call different aspects of the OrderBook or of the UserInput at each vector generation*/
std::vector<Candlestick> Candlestick::getOneCandlestick(OrderBook& orderBook,
                                                        const std::string& currentTime,
                                                        const std::string& product,
                                                        OrderBookType orderType){
    
    std::vector<Candlestick> candlesticks; // Initialize vector of Candlestick objects

    // Iterate over all products
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        std::set<std::string> uniqueTimestamps; // Keep track of unique timestamps

        // Iterate over the entries for the current product
        for (const OrderBookEntry& entry : entries) {
            const std::string& timestamp = entry.timestamp;

            // Check if the timestamp is unique
            if (uniqueTimestamps.find(timestamp) == uniqueTimestamps.end()) {
                /** Calculate open for the previous timestamp, round to 5 decimal places*/
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = std::round(orderBook.getMeanOpen(orderType, product, prevT) * 100000) / 100000;

                /**Calculate high, low, close values for the current timestamp rounded to 5 decimal places*/
                double high = std::round(OrderBook::getHighPrice(entries) * 100000) / 100000;
                double low = std::round(OrderBook::getMinPrice(entries) * 100000) / 100000;
                double close = std::round(orderBook.getMeanPrice(entries) * 100000) / 100000;

                // Create a Candlestick object and set its member variables
                Candlestick candlestick(orderBook);
                candlestick.open = open;
                candlestick.high = high;
                candlestick.low = low;
                candlestick.close = close;

                // Add the Candlestick object to the vector
                candlesticks.push_back(candlestick);

                // Mark the timestamp as seen
                uniqueTimestamps.insert(timestamp);
            }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
    
}

void Candlestick::printCandlestickChart(const std::vector<Candlestick>& candlesticks,
                                        const std::string& currentTime) const
{
    // Check if the candlesticks vector is empty
     if (candlesticks.empty()) {
         std::cout << "No data to display." << std::endl;
         return;
     }
    
    // Iterate over each Candlestick object in the vector
//    for (const Candlestick& candlestick : candlesticks) {
        
        // Check if any of the values are 0 or smaller
        if (open <= 0 || high <= 0 || low <= 0 || close <= 0) {
            std::cout << "Graph cannot be displayed because one or more values are not greater than 0." << std::endl;
            return;  // Skip displaying the graph
        }
        
        // Determine the range of values to display on the y-axis
        double minValue = std::min(low, std::min(open, close));
        double maxValue = std::max(high, std::max(open, close));
        
        /** Calculate the step size for y-axis labels - graph over 30 lines, but I would like there to be a margin of 3 stepsizes to the top and to the bottom, so 24 parts for calculation of stepsize*/
        double stepSize = (maxValue - minValue) / 23;
        
        
        // Print the y-axis labels and candlestick chart
        for (int i = 0; i < 30; ++i) {
            double yValue = (maxValue + 3 * stepSize) - i * stepSize;
            
            // Print the y-axis label with fixed precision
            std::cout << std::fixed << std::setprecision(3) << std::setw(7) << yValue << " | ";
            
            // Check if 'yValue' falls within the range of 'open' to 'close'
            if (yValue >= open && yValue <= close && open >= close) {
                // Print '=====' to represent the candlestick body with a sinking market
                std::cout << "=====";
            } else if (yValue >= open && yValue <= close && open <= close) {
                // Print '^^^^^' to represent the candlestick body with a rising market
                std::cout << "^^^^^";
            } else if (yValue >= low && yValue <= high) {
                // Check if 'yValue' falls within the range of 'low' to 'high'
                // Print '  |  ' to represent the candlestick wick
                std::cout << "  |  ";
            } else {
                // If 'yValue' is not within any of the above ranges, print spaces
                std::cout << "     ";
            }
            // Move to the next line after each row of the candlestick is printed
            std::cout << std::endl;
        }
        
        // Print the x-axis labels
        std::cout << "      +------+------+"
        << std::endl;
        
    // Extract and print the timestamp for the current candlestick
    std::string time = extractTime(currentTime);
    std::cout << "      " << time << std::endl;
        // Move to the next line after each row of the candlestick is printed
        std::cout << std::endl;
//    }
}

