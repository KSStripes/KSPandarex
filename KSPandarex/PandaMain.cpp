//
//  PandaMain.cpp
//  KSPandarex
//
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
    loadOrderBook();
    int input;
        /*while loop to continue running after the user has picked an option*/
        while (true) {
            printMenu();
            input = getUserOption();
            processUserOption(input);
        }
}

/*function to load Orderbook*/
void PandaMain::loadOrderBook(){
    /*populate vector with an instance of the object orderBookEntry*/
    orders = CSVReader::readCSV("orders_20200317.csv");
}


/*function to print the user menu*/
void PandaMain::printMenu(){
    std::cout << "1: Print Help" << std::endl;
    std::cout << "2: Print Market Statistics" << std::endl;
    std::cout << "3: Make Offer" << std::endl;
    std::cout << "4: Make Bid" << std::endl;
    std::cout << "5: Print Wallet" << std::endl;
    std::cout << "6: Continue to next time step" << std::endl;
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Type in 1-6" << std::endl;
}

/*function for option 1*/
void PandaMain::printHelp(){
    std::cout << "Help - choose options from the menu." << std::endl;
    std::cout << "and follow the onscreen instructions." << std::endl;
}

/*function for option 2 using orders vector from loadOrderBook()*/
void PandaMain::printMarketStats(){
    std::cout << "OrderBook contains " << orders.size() << " entries" << std::endl;
    
    /*print stats to keep track of all asks and bids in order book*/
    unsigned int bids = 0;
    unsigned int asks = 0;
    for (OrderBookEntry& e : orders){
        if (e.orderType == OrderBookType::ask){
            asks++;
        }
        if (e.orderType == OrderBookType::bid){
            bids++;
        }
    }
    std::cout << "OrderBook asks: " << asks << " , bids: " << bids << std::endl;
}

/*function for option 3*/
void PandaMain::makeOffer(){
    std::cout << "Make an offer. Enter the amount." << std::endl;
}

/*function for option 4*/
void PandaMain::makeBid(){
    std::cout << "Enter the amount of your bid." << std::endl;
}

/*function for option 5*/
void PandaMain::printWallet(){
    std::cout << "Your wallet is empty" << std::endl;
}

/*function for option 6*/
void PandaMain::nextTimeStep(){
    std::cout << "Going to the next timestep" << std::endl;
}

/*function for invalid keyboard input*/
void PandaMain::invalidChoice(){
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
}

/*function to read user input from console, print it and return it*/
int PandaMain::getUserOption(){
    int userOption; //create data type to populate with keyboard choice
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    
    return userOption;
}

/*switch function to display the right output based on getUserOption()*/
void PandaMain::processUserOption(int userOption){
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            makeOffer();
            break;
        case 4:
            makeBid();
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
