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
    
private:
    /*function to tokenize into a vector*/
    static std::vector<std::string> tokenize(std::string csvLine, char seperator);
    /*function to return one OrderBookEntry*/
    OrderBookEntry stringsToOBE(std::vector<std::string> strings);

};



#endif /* CSVReader_hpp */
