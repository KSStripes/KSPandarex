//
//  PandaMain.cpp
//  KSPandarex
/* The PandaMain class represents the application itself, and it deals with user input and menu printing */
//  Created by Kristin Schumann on 10/12/2023.
//

#include "PandaMain.hpp"
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <vector>


PandaMain::PandaMain(){
}

/*initialisation*/
void PandaMain::init(){
    int input;
    currentTime = orderBook.getEarliesttime();
        /*while loop to continue running after the user has picked an option*/
        while (true) {
            printMenu();
            input = getUserOption();
            processUserOption(input);
        }
}

/*function to print the user menu*/
void PandaMain::printMenu(){
    std::cout << "1: Print Help" << std::endl;
    std::cout << "2: Print Market Statistics" << std::endl;
    std::cout << "3: Enter Ask" << std::endl;
    std::cout << "4: Enter Bid" << std::endl;
    std::cout << "5: Print Wallet" << std::endl;
    std::cout << "6: Continue to next time step" << std::endl;
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "Type in 1-6" << std::endl;
}

/*function for option 1*/
void PandaMain::printHelp(){
    std::cout << "Help - choose options from the menu." << std::endl;
    std::cout << "and follow the onscreen instructions." << std::endl;
}

/*function for option 2 using OrderBook*/
void PandaMain::printMarketStats(){
    
    //print types of orders mapped in OrderBook
    for (std::string const& p : orderBook.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
        
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Minimum ask: " << OrderBook::getMinPrice(entries) << std::endl;
        //KS function on mean price
    std::cout << "Mean ask: " << orderBook.getMeanPrice(entries) << std::endl;
        //KS function on spread
    std::cout << "The spread between lowest ask and highest bid: " << orderBook.getSpread(p, currentTime) << std::endl;
        
    }
}

/*function for option 3*/
void PandaMain::enterAsk(){
    std::cout << "Make an Ask. Enter the amount: product, price amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    //clear current console input until previous '\n' char - not implemented in the end because of getline
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //get user-typed input and save as string to input
    std::getline(std::cin, input);
    
    //use input string, break it into its parts, use its values using currently CSVReader functions
    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    //check if user has typed string as per example (3 typed CSV, ex eg ETH/BTC,200,0.5)
    if (tokens.size() != 3){
        std::cout << "Bad input! " << input << std::endl;
    }
    else{
        try{
            CSVReader csvReader; //create an instance of csvReader
            OrderBookEntry obe = csvReader.stringItemsToOBE(tokens[1],
                                                             tokens[2],
                                                             currentTime,
                                                             tokens[0],
                                                             OrderBookType::ask);
            orderBook.insertOrder(obe);
        }catch (const std::exception& e){
            std::cout << "PandaMain::enterAsk(): Bad input!" << std::endl;
        }
        
    }
    
    std::cout << "You typed: " << input << std::endl;
}

/*function for option 4*/
void PandaMain::enterBid(){
    std::cout << "Enter the amount of your bid." << std::endl;
}

/*function for option 5*/
void PandaMain::printWallet(){
    std::cout << "Your wallet is empty" << std::endl;
}

/*function for option 6*/
void PandaMain::nextTimeStep(){
    std::cout << "Going to the next timestep" << std::endl;
    currentTime = orderBook.getNexttime(currentTime);
}

/*function for invalid keyboard input*/
void PandaMain::invalidChoice(){
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
}

/*function to read user input from console, print it and return it*/
int PandaMain::getUserOption(){
    int userOption = 0;
    std::string line;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line); //convert user string to integer
    }catch(const std::exception& e)
    {
        //
    }
    std::cout << "You wrote: " << line << std::endl;
    
    return userOption;
}

/** KS wrote switch function display the right output based on getUserOption()*/
void PandaMain::processUserOption(int userOption){
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            nextTimeStep();
            break;
        default:
            invalidChoice();
            break;
    }
}
