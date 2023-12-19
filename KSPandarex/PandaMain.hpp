//
//  PandaMain.hpp
//  KSPandarex
/* The PandaMain class represents the application itself, and it deals with user input and menu printing */
//  Created by Kristin Schumann on 10/12/2023.
//

#ifndef PandaMain_hpp
#define PandaMain_hpp

#include <stdio.h>
#include <vector>
#include "OrderBookEntry.hpp"
#include "OrderBook.hpp"

class PandaMain{
public:
    /*constructor + init() to start cim*/
    PandaMain();
    void init();
    
private:
    /** pass orderbook */
    //OrderBook orderBook{"orders_20200317.csv"};
    
    /** pass test data */
    OrderBook orderBook{"test.csv"};
    
    /** get  current time*/
    std::string currentTime;
    
    /*function to print the user menu*/
    void printMenu();
    /*function for option 1*/
    void printHelp();
    /*function for option 2*/
    void printMarketStats();
    /*function for option 3*/
    void enterAsk();
    /*function for option 4*/
    void enterBid();
    /*function for option 5*/
    void printWallet();
    /*function for option 6*/
    void nextTimeStep();
    /*function for invalid keyboard input*/
    void invalidChoice();
    /*function to read user input from console, print it and return it*/
    int getUserOption();
    /*switch function to display the right output based on getUserOption()*/
    void processUserOption(int userOption);
    

};

#endif /* PandaMain_hpp */
