//
//  PandaMain.cpp
//  KSPandarex
/* The PandaMain class represents the application itself, and it deals with user input and menu printing */
//  Created by Kristin Schumann on 10/12/2023.
//

#include "PandaMain.hpp"
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include "UserInput.hpp"
#include "CandleStick.hpp"
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
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "HELP!! Type number to choose option from menu." << std::endl;
    std::cout << "Follow onscreen instructions. \n" << std::endl;
}

/*function for option 2 using OrderBook*/
void PandaMain::printMarketStats(){
    
    std::string currentT = orderBook.getEarliesttime();
    std::string nextT = orderBook.getNexttime(currentT);
    std::string prevT = orderBook.getPreviousTime(currentT);
    
    std::cout << "Current Time: " << currentT << std::endl;
    std::cout << "Next Timestamp: " << nextT << std::endl;
    std::cout << "Prev Timestamp: " << prevT << std::endl;
    std::cout << "========================" << std::endl;

    for (std::string const& p : orderBook.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
        
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p,
                                                                  currentT);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask : " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask : " << OrderBook::getMinPrice(entries) << std::endl;
        std::cout << "Mean Open ask : " << orderBook.getMeanOpen(OrderBookType::ask, p, prevT) << std::endl;
        std::cout << "Mean Close ask : " << OrderBook::getMeanPrice(entries) << std::endl;
        std::cout << "========================" << std::endl;
            
        
        /**KSStripes added function on spread*/
//    std::cout << "The spread between lowest ask and highest bid: " << Candlestick::getSpread(p, currentTime) << std::endl;
        /**end addition KSStripes**/
    }
}

/**KSStripes implemented the function for option 3 in seperate UserInput Class*/
void PandaMain::goToAsk() {
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterAsk();
}

/**KSStripes implemented the function for option 4 in seperate UserInput Class*/
void PandaMain::goToBid(){
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterBid();
}

/**KSStripes implemented the function for option 5 in Wallet  Class*/


/*function for option 6*/
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
            goToAsk();
            break;
        case 4:
            goToBid();
            break;
        case 5:
            wallet.printWallet();
            break;
        case 6:
            nextTimeStep();
            break;
        default:
            invalidChoice();
            break;
    }
}
/**end addition KSStripes**/
