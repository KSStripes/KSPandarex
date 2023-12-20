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
#include "PandaMain.hpp"


/** KSStripes created this class to seperate user input functionality from the PandaMain app*/

UserInput::UserInput(const std::string& currentTime, 
                     Wallet& wallet,
                     OrderBook& orderBook)
    :   currentTimeRef(currentTime),
        walletRef(wallet),
        orderBookRef(orderBook)
{
    // Constructor that initializes references and currentTime
}


/*function for option 3*/
void UserInput::enterAsk(){
    /**some text to explain the menu**/
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Enter your ask. Format: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::cout << "Your options: " << std::endl;
    
    /**print types of orders mapped in OrderBook*/
    for (std::string const& p : orderBookRef.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
    }
    
    std::cout << "If you have DOGE and want USDT, enter DOGE/USDT,xx,xx" << std::endl;
    
    //get user-typed input and save as string to input
    std::string input;
    std::getline(std::cin, input);

    
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
                                                             currentTimeRef,
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
    /**some text to explain the menu**/
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Enter your bid. Format: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::cout << "Your options: " << std::endl;
    
    /**print types of orders mapped in OrderBook*/
    for (std::string const& p : orderBookRef.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
    }
    
    std::cout << "If you have ETH and want DOGE, enter ETH/DOGE,xx,xx" << std::endl;
    
    //get user-typed input and save as string to input
    std::string input;
    std::getline(std::cin, input);

    /**use input string, break it into its parts, use its values using currently CSVReader functions*/
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
                                                             currentTimeRef,
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
