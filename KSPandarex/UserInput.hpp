//
//  UserInput.hpp
//  KSPandarex
//
//  Created by Kristin Schumann on 20/12/2023.
//

#ifndef UserInput_hpp
#define UserInput_hpp
#include "OrderBook.hpp"
#include "Wallet.hpp"
#include "PandaMain.hpp"

#include <stdio.h>

/** KSStripes created this class to seperate user input functionality from the PandaMain app*/
class UserInput{
    
public:
    /**Constructor that uses existing instances of Wallet, OrderBook and PandaMain current time*/
    UserInput(const std::string& currentTime, Wallet& wallet, OrderBook& orderBook);
    /** function to deal with menu item 3 to enter a ask*/
    void enterAsk();
    
    /** function to deal with menu item 4 to enter a bid*/
    void enterBid();
    
private:
    std::string currentTimeRef; // Reference to current time string
    Wallet& walletRef;         // Reference to Wallet instance
    OrderBook& orderBookRef;   // Reference to OrderBook instance
};

#endif /* UserInput_hpp */
