//
//  UserInput.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 20/12/2023.
//

#include "UserInput.hpp"
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "OrderBook.hpp"
#include "Wallet.hpp"


/** KSStripes created this class to seperate user input functionality from the PandaMain app*/
UserInput::UserInput(Wallet& wallet, OrderBook& orderBook)
    : walletRef(wallet), orderBookRef(orderBook) {
    // Constructor that initializes references
}

/*function for option 3*/
void UserInput::enterAsk(){
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Make an Ask. Enter the amount: product, price amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    //get user-typed input and save as string to input
    std::getline(std::cin, input);
    
    // get current time
    std::string currentTime = orderBookRef.getEarliesttime();
    
    //use input string, break it into its parts, use its values using currently CSVReader functions
    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    
    //check if user has typed string as per example (3 typed CSV, ex eg ETH/BTC,200,0.5)
    if (tokens.size() != 3){
        std::cout << "UserInput::enterAsk(): Bad input! " << input << std::endl;
    }
    else{
        std::cout << "You typed: " << input << std::endl;
        try{
            //create order obe for new item
            OrderBookEntry obe = CSVReader::stringItemsToOBE(tokens[1],
                                                             tokens[2],
                                                             currentTime,
                                                             tokens[0],
                                                             OrderBookType::ask);
            //set username for new dataset to simuser
            obe.username = "simuser";
            //check if user user has enough money in wallet for order obe
            if (walletRef.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBookRef.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        }catch (const std::exception& e){
            std::cout << "UserInput::enterAsk(): Bad input!" << std::endl;
        }
        
    }
}

///*function for option 4*/
void UserInput::enterBid(){
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    //get user-typed input and save as string to input
    std::getline(std::cin, input);

    // get current time
    std::string currentTime = orderBookRef.getEarliesttime();
    
    
    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "UserInput::enterBid(): Bad input! " << input << std::endl;
    }
    else {
        std::cout << "You typed: " << input << std::endl;
        try {
            //create order obe for new item
            OrderBookEntry obe = CSVReader::stringItemsToOBE(tokens[1],
                                                             tokens[2],
                                                             currentTime,
                                                             tokens[0],
                                                             OrderBookType::bid);
            //set username for new dataset to simuser
            obe.username = "simuser";
            //check if user user has enough money in wallet for order obe
            if (walletRef.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBookRef.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " PandaMain::enterBid(): Bad input " << std::endl;
        }
    }
}
