//
//  CSVReader.hpp
//  KSPandarex
//
//  Created by Kristin Schumann on 11/12/2023.
//

#ifndef CSVReader_hpp
#define CSVReader_hpp

#include <stdio.h>
#include "OrderBookEntry.hpp"
#include <vector>
#include <string>

class CSVReader{
    
public:
    /*constructor function*/
    CSVReader();
    
    /*function to read CSV into a vector*/
    static std::vector<OrderBookEntry> readCSV (std::string csvFile);
    
    /*function to tokenize into a vector*/
    static std::vector<std::string> tokenize(std::string csvLine, char seperator);
    
    /*function to return one OrderBookEntry based the 5 distinct elements, incl by user*/
    static OrderBookEntry stringItemsToOBE(std::string price,
                                std::string amount,
                                std::string timestamp,
                                std::string product,
                                OrderBookType OrderBookType);
    
private:

    /*function to return one OrderBookEntry based the 5 elements of one CSV file line, created by stringToOrderBookType() vector*/
    static OrderBookEntry stringVectorToOBE(std::vector<std::string> strings);

};



#endif /* CSVReader_hpp */
