//
//  PandaMain.cpp
//  KSPandarex
/* The PandaMain class represents the application itself, and it deals with user input and menu printing */
//  Created by Kristin Schumann on 10/12/2023.
//

#include "PandaMain.hpp"
#include "OrderBookEntry.hpp"
#include "CandleStick.hpp"
#include "UserInput.hpp"
#include "OrderBook.hpp"
#include <iostream>
#include <vector>


PandaMain::PandaMain(){
}

/*initialisation*/
void PandaMain::init(){
    int input;
    currentTime = orderBook.getEarliesttime(); //set up time
    wallet.insertCurrency("BTC", 10.0); //set up wallet with inital currency and amount
    wallet.insertCurrency("ETH", 1.0); //set up wallet with inital currency and amount
    
    
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
    std::cout << "2: Print Market Stats" << std::endl;
    std::cout << "3: Candlesticks Stats" << std::endl;
    std::cout << "4: Enter Ask" << std::endl;
    std::cout << "5: Enter Bid" << std::endl;
    std::cout << "6: Print Wallet" << std::endl;
    std::cout << "7: Complete Operation and Continue to Next Time Step" << std::endl;
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "Type in 1-7" << std::endl;
}

/*function for option 1*/
void PandaMain::printHelp(){
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "HELP!! Type number to choose option from menu." << std::endl;
    std::cout << "Follow onscreen instructions. \n" << std::endl;
}

/*function for option 2 using OrderBook*/
void PandaMain::printMarketStats(){
    Candlestick candlestick(orderBook); // Create a Candlestick instance

        // Print the candlestick chart
//    candlestick.printCandlestickChart(open, high, low, close);
    candlestick.printCandlestickChart(5, 8, 3, 6, currentTime);
    candlestick.printCandlestickChart(6, 8, 3, 5, currentTime);
    candlestick.printCandlestickChart(0.0221, 0.0222, 0.0218, 0.0220, currentTime);
    candlestick.printCandlestickChart(119.501, 121.099, 117.329, 119.442, currentTime);

//    std::string nextT = orderBook.getNexttime(currentTime);
//    std::string prevT = orderBook.getPreviousTime(currentTime);
//    
//    std::cout << "Current Time: " << currentTime << std::endl;
//    std::cout << "Next Timestamp: " << nextT << std::endl;
//    std::cout << "Prev Timestamp: " << prevT << std::endl;
//    std::cout << "========================" << std::endl;
//
//    for (std::string const& p : orderBook.getKnownProducts()){
//        std::cout << "Product: " << p << std::endl;
//        
//        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
//                                                                  p,
//                                                                  currentTime);
//        std::cout << "Asks seen: " << entries.size() << std::endl;
//        std::cout << "Max ask : " << OrderBook::getHighPrice(entries) << std::endl;
//        std::cout << "Min ask : " << OrderBook::getMinPrice(entries) << std::endl;
//        /**KSStripes added function outputs for open, close and  spread*/
//        std::cout << "Mean Open ask : " << orderBook.getMeanOpen(OrderBookType::ask, p, prevT) << std::endl;
//        std::cout << "Mean Close ask : " << OrderBook::getMeanPrice(entries) << std::endl;
//        std::cout << "The spread between lowest ask and highest bid: " << orderBook.getSpread(OrderBookType::ask, p, currentTime) << std::endl;
//        std::cout << "========================" << std::endl;
//        /**end addition KSStripes**/
//    }
}

/**KSStripes implemented the function in userinput to go to options for the candlestick menu**/
void PandaMain::printCandlesticks() {
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.candlestickRequest();
    
    /** Code in case I wanted to run all 5 graphs for the Candlesticks without passing through the user input
//    Candlestick candlestick(orderBook); // Create a Candlestick instance
//    // Call generateCandlesticks to get candlestick data
//    std::vector<Candlestick> candlestickData = candlestick.getAllCandlesticks(orderBook, currentTime);
//
//    // Loop through the candlestickData and print the data to the terminal
//    for (const Candlestick& candlestick : candlestickData) {
//        // Access and print the member variables of each Candlestick object
//        std::cout << "Timestamp: " << currentTime << std::endl;
//        std::cout << "Open: " << candlestick.open << std::endl;
//        std::cout << "High: " << candlestick.high << std::endl;
//        std::cout << "Low: " << candlestick.low << std::endl;
//        std::cout << "Close: " << candlestick.close << std::endl;
//        std::cout << "========================" << std::endl;
//    }*/
}


/**KSStripes implemented the function for option 4 making an ask in seperate UserInput Class*/
void PandaMain::goToAsk() {
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterAsk();
}

/**KSStripes implemented the function for option 5 making and ask in seperate UserInput Class*/
void PandaMain::goToBid(){
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterBid();
}

/**KSStripes implemented the function for printing the wallet in the Wallet  Class - deleted here*/


/*function for option 7 - continue*/
void PandaMain::nextTimeStep(){
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }
    
    currentTime = orderBook.getNexttime(currentTime);
}

/*function for invalid keyboard input*/
void PandaMain::invalidChoice(){
    std::cout << "Invalid choice. Choose 1-7" << std::endl;
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

/** KSStripes wrote switch function display the right output based on getUserOption()*/
void PandaMain::processUserOption(int userOption){
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            printCandlesticks();
            break;
        case 4:
            goToAsk();
            break;
        case 5:
            goToBid();
            break;
        case 6:
            wallet.printWallet();
            break;
        case 7:
            nextTimeStep();
            break;
        default:
            invalidChoice();
            break;
    }
}
/**end addition KSStripes**/
