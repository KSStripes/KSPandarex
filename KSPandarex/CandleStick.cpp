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
std::string Candlestick::extractTime(const std::string& timestamp) {
    // Define a regular expression pattern to match the time portion
    std::regex pattern("\\d{2}:\\d{2}:\\d{2}");

    // Search for the pattern in the timestamp
    std::smatch match;
    if (std::regex_search(timestamp, match, pattern)) {
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
                // Calculate open for the previous timestamp
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = orderBook.getMeanOpen(orderType, product, prevT);
                // Calculate high, low, close values for the current timestamp
                double high = OrderBook::getHighPrice(entries);
                double low = OrderBook::getMinPrice(entries);
                double close = orderBook.getMeanPrice(entries);

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
//    for (const std::string& product : products) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        std::set<std::string> uniqueTimestamps; // Keep track of unique timestamps

        // Iterate over the entries for the current product
        for (const OrderBookEntry& entry : entries) {
            const std::string& timestamp = entry.timestamp;

            // Check if the timestamp is unique
            if (uniqueTimestamps.find(timestamp) == uniqueTimestamps.end()) {
                // Calculate open for the previous timestamp
                std::string prevT = orderBook.getPreviousTime(timestamp);
                double open = orderBook.getMeanOpen(orderType, product, prevT);
                // Calculate high, low, close values for the current timestamp
                double high = OrderBook::getHighPrice(entries);
                double low = OrderBook::getMinPrice(entries);
                double close = orderBook.getMeanPrice(entries);

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
//        }
    }

    // Return the vector of Candlestick objects
    return candlesticks;
    
}


/**function to take the four elements of the candlestick object and print them as one candlestick**/
void Candlestick::printCandlestickChart(double open,
                                        double high,
                                        double low,
                                        double close,
                                        const std::string& currentTime)
{
    
    // Determine the range of values to display on the y-axis
//    double minValue = std::min(low, close);
//    double maxValue = std::max(high, close);
    double minValue = low;
    double maxValue = high;
    
    // Calculate the step size for y-axis labels - graph over 20 lines
    double stepSize = (maxValue - minValue) / 19; // Divide by 19 to get 20 lines


    // Print the y-axis labels and candlestick chart
    for (int i = 0; i < 20; ++i) {
        double yValue = maxValue - i * stepSize;

        // Print the y-axis label with fixed precision
        std::cout << std::fixed << std::setprecision(3) << std::setw(7) << yValue << " | ";

        // Check if 'yValue' falls within the range of 'open' to 'close'
        if (yValue >= open && yValue <= close) {
            // Print '=====' to represent the candlestick body
            std::cout << "=====";
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
    std::cout << "      +------+------+------+------+------+------+------+------+------+------+"
              << std::endl;
//    std::cout << "      Open   High   Low    Close" << std::endl;
    
    std::string time = extractTime(currentTime);
    std::cout << "      " << time << std::endl;
    // Move to the next line after each row of the candlestick is printed
    std::cout << std::endl;
    
}
//    // Calculate the maximum value between 'high' and 'close'
//    double maxValue = std::max(high, close);
//
//    // Calculate the minimum value between 'low' and 'close'
//    double minValue = std::min(low, close);
//
//    // Loop through the values from 'maxValue' down to 'minValue'
//    for (double i = maxValue; i >= minValue; --i) {
//        // Check if 'i' falls within the range of 'open' to 'close'
//        if (i >= open && i <= close) {
//            // Print '=====' to represent the candlestick body
//            std::cout << "=====";
//        } else if (i >= low && i <= high) {
//            // Check if 'i' falls within the range of 'low' to 'high'
//            // Print '  |  ' to represent the candlestick wick
//            std::cout << "  |  ";
//        } else {
//            // If 'i' is not within any of the above ranges, print spaces to fill the gap
//            std::cout << "     ";
//        }
//        // Move to the next line after each row of the candlestick is printed
//        std::cout << std::endl;
//    }
//
//    
//    // Print the timestamp at the bottom
////    std::cout << "Timestamp: " << timestamp << std::endl;
//    
//    // Print x-axis labels
//    std::cout << "Open: " << open << " High: " << high << " Low: " << low << " Close: " << close << std::endl;
//}
