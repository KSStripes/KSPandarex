//
//  CSVReader.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 11/12/2023.
//

#include "CSVReader.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


/*constructor function*/
CSVReader::CSVReader(){
    
}


/*function to read CSV into a vector*/
std::vector<OrderBookEntry> CSVReader::readCSV (std::string csvFilename){
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFilename};
    std::string line;
    
    if (csvFile.is_open()) {
            while (std::getline(csvFile, line)) {
                CSVReader csvReader;  // Create an instance of the CSVReader class
                try {
                    OrderBookEntry obe = csvReader.stringsToOBE(tokenize(line, ','));
                    entries.push_back(obe);  // Add the OrderBookEntry to the vector
                } catch (const std::exception& e) {
                    std::cout << "CSVReader::readCSV bad data" << std::endl;
                }
            }

            csvFile.close();  // Close the file after reading all lines
            std::cout << "CSVReader::readCSV " << entries.size() << " entries" << std::endl;
            return entries;
        }
    // Handle the case where the file couldn't be opened
    std::cout << "CSVReader::readCSV could not open file: " << csvFilename << std::endl;
    return entries;  // Return an empty vector
}
    

/*function to tokenize into a vector*/
std::vector<std::string> CSVReader::tokenize (std::string csvLine, char seperator){

    std::vector<std::string> tokens;
        
    /*declare variables start and end used to delineate the positions of the tokens*/
    //signed int start;
    //signed int end;
    /*changed to string type rather than unsigned int, as code was giving warnings*/
    std::string::size_type start;
    std::string::size_type end;
    std::string token;
        
    /*initialize start*/
    start = csvLine.find_first_not_of(seperator, 0);
        
    do{
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    }
    while(end != std::string::npos);
    return tokens;
}
    
/*function to return one OrderBookEntry*/
OrderBookEntry CSVReader::stringsToOBE (std::vector<std::string> tokens){
    
    double price, amount;
    
    /*check if line has 5 items, if not create exception and throw line*/
    if (tokens.size() != 5) {
        std::cout << "Bad Line" << std::endl;
        throw std::exception{};

        }else{
        /*we have 5 tokens, convert strings into numbers*/
        /*exception handling if one of the lines containes no value for stod*/
            try{
                price = std::stod(tokens[3]);
                amount = std::stod(tokens[4]);
              
            }catch(const std::exception& e){
                std::cout << "Bad Float; " << tokens[3] << std::endl;
                std::cout << "Bad Float; " << tokens[4] << std::endl;
                throw;
            }
        }
    
    OrderBookEntry obe {price,
                        amount,
                        tokens[0], /*timestamp is first in the array but third in the function*/
                        tokens[1], /*vector position for product*/
                        OrderBookEntry::stringToOrderBookType(tokens[2])};
    
    return obe;
}


