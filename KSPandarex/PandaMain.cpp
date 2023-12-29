//
//  PandaMain.cpp
//  KSPandarex
/* The PandaMain class represents the application itself, and it deals with user input and menu printing */
//  Created by Kristin Schumann on 10/12/2023.
//

#include "PandaMain.hpp"
#include "OrderBookEntry.hpp"
#include "CandleStick.hpp"
#include "SpreadPlot.hpp"
#include "UserInput.hpp"
#include "OrderBook.hpp"
#include <iostream>
#include <vector>
#include <iomanip>


PandaMain::PandaMain(){
}

/*initialisation*/
void PandaMain::init(){
    int input;
    currentTime = orderBook.getEarliesttime(); //set up time
    wallet.insertCurrency("BTC", 10.0); //set up wallet with inital currency and amount
    wallet.insertCurrency("ETH", 1.0); //set up wallet with inital currency and amount
    
//    // Create a vector of doubles representing spread data
//    std::vector<double> spreadData = {0.25, 0.35, 0.15, 0.28, 0.20};
//    
//    // Create an instance of SpreadPlot with the spread data
//    SpreadPlot spreadPlot(spreadData);
    
    
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
    std::cout << "4: Print Spread Stats" << std::endl;
    std::cout << "5: Enter Ask" << std::endl;
    std::cout << "6: Enter Bid" << std::endl;
    std::cout << "7: Print Wallet" << std::endl;
    std::cout << "8: Complete Operation and Continue to Next Time Step" << std::endl;
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "Type in 1-8" << std::endl;
}

/*function for option 1*/
void PandaMain::printHelp(){
    std::cout << std::endl;
    std::cout << "HELP!! Type number to choose option from menu." << std::endl;
    std::cout << "Follow onscreen instructions." << std::endl;
    std::cout << std::endl;
    orderBook.clusterOrdersIntoBuckets();
}

/*function for option 2 using OrderBook*/
void PandaMain::printMarketStats(){
    std::string nextT = orderBook.getNexttime(currentTime);
    std::string prevT = orderBook.getPreviousTime(currentTime);
    
    
    // Define column width for headers and data
    int timeWidth = 20;
    int headerWidth = 15;
    int dataWidth = 10;
    
    // Set the floating-point output to two decimal places
    std::cout << std::fixed << std::setprecision(2);

    // Print Times
    std::cout << std::left << std::setw(timeWidth) << "Current Time:" << currentTime << std::endl;
    std::cout << std::left << std::setw(timeWidth) << "Next Timestamp:" << nextT << std::endl;
    std::cout << std::left << std::setw(timeWidth) << "Prev Timestamp:" << prevT << std::endl;
    std::cout << "=================================================================================" << std::endl;

    // Print data headers - product names
    std::cout << std::left << std::setw(headerWidth) << "Product" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << std::left << std::setw(dataWidth) << p << " | ";
    }
    std::cout << std::endl;
    
    std::cout << "=================================================================================" << std::endl;

    // Print data for "Total Asks"
    std::cout << std::left << std::setw(headerWidth) << "Total Asks" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << std::right << std::setw(dataWidth) << entries.size() << " | ";
    }
    std::cout << std::endl;

    // Print data for "Maximum Asks"
    std::cout << std::left << std::setw(headerWidth) << "Max Asks" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        double maxAsk = OrderBook::getHighPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << maxAsk << " | ";
    }
    std::cout << std::endl;

    // Print data for "Minimum Asks"
    std::cout << std::left << std::setw(headerWidth) << "Min Asks" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        double minAsk = OrderBook::getMinPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << minAsk << " | ";
    }
    std::cout << std::endl;
    
    // Print data for "Mean Open Ask"
    std::cout << std::left << std::setw(headerWidth) << "Mean Open Ask" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        double meanOpenAsk = orderBook.getMeanOpen(OrderBookType::ask, p, prevT);
        std::cout << std::right << std::setw(dataWidth) << meanOpenAsk << " | ";
    }
    std::cout << std::endl;
    
    // Print data for "Mean Close Ask"
    std::cout << std::left << std::setw(headerWidth) << "Mean Close Ask" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        double meanCloseAsk = OrderBook::getMeanPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << meanCloseAsk << " | ";
    }
    std::cout << std::endl;

    std::cout << "=================================================================================" << std::endl;

    // Print data for "Total Bids"
    std::cout << std::left << std::setw(headerWidth) << "Total Bids" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << std::right << std::setw(dataWidth) << entries.size() << " | ";
    }
    std::cout << std::endl;

    // Print data for "Maximum Bids"
    std::cout << std::left << std::setw(headerWidth) << "Max Bids" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double maxAsk = OrderBook::getHighPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << maxAsk << " | ";
    }
    std::cout << std::endl;

    // Print data for "Minimum Bids"
    std::cout << std::left << std::setw(headerWidth) << "Min Bids" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double minAsk = OrderBook::getMinPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << minAsk << " | ";
    }
    std::cout << std::endl;
    
    // Print data for "Mean Open Bids"
    std::cout << std::left << std::setw(headerWidth) << "Mean Open Bid" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double meanOpenAsk = orderBook.getMeanOpen(OrderBookType::ask, p, prevT);
        std::cout << std::right << std::setw(dataWidth) << meanOpenAsk << " | ";
    }
    std::cout << std::endl;
    
    // Print data for "Mean Close Bids"
    std::cout << std::left << std::setw(headerWidth) << "Mean Close Bid" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double meanCloseAsk = OrderBook::getMeanPrice(entries);
        std::cout << std::right << std::setw(dataWidth) << meanCloseAsk << " | ";
    }
    std::cout << std::endl;

        std::cout << "=================================================================================" << std::endl;
    
    // Print data for "Spread"
    std::cout << std::left << std::setw(headerWidth) << "Spread" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double meanCloseAsk = orderBook.getSpread(p, currentTime);
        std::cout << std::right << std::setw(dataWidth) << meanCloseAsk << " | ";
    }
    std::cout << std::endl;
    
    std::cout << "=================================================================================" << std::endl;

std::cout << std::endl;

}

/**KSStripes implemented the function in userinput to go to options for the candlestick menu**/
void PandaMain::printCandlesticks() {
    Candlestick candlestick(orderBook); // Create a Candlestick instance
    /** Print the candlestick chart - served as dummy test data*/
//    candlestick.printCandlestickChart(open, high, low, close);
//    candlestick.printCandlestickChart(5, 8, 3, 6, currentTime);
//    candlestick.printCandlestickChart(6, 8, 3, 5, currentTime);
//    candlestick.printCandlestickChart(0.0221, 0.0222, 0.0218, 0.0220, currentTime);
//    candlestick.printCandlestickChart(119.501, 121.099, 117.329, 119.442, currentTime);

    
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.candlestickRequest();
}

/**KSStripes implemented the this function in seperate bar chart class**/
void PandaMain::printSpreadBar(){
    std::cout << "Your Spread Statistics!" << std::endl;
    std::cout << "See the difference between lowest ask prices and highest price bids!" << std::endl;
    
    /**print the spread stats as reference values**/
    for (std::string const& p : orderBook.getKnownProducts()){
        // Call the getSpread function to calculate the spread
        double spread = orderBook.getSpread(p, currentTime);
        // Print the result
        std::cout << "Spread for Product " << p << " at Timestamp " << currentTime << ": " << spread << std::endl;
    }
    std::cout << "========================" << std::endl;
    
    
    // Create an instance of the SpreadPlot class
    SpreadPlot spreadPlot(currentTime, orderBook);
    std::vector<double> spreads = spreadPlot.getAllSpreads(currentTime);;
    // Print the spread charts
    spreadPlot.printSpreadBarChart(spreads);

}

/**KSStripes implemented the function for option 5 making an ask in seperate UserInput Class*/
void PandaMain::goToAsk() {
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterAsk();
}

/**KSStripes implemented the function for option 6 making and ask in seperate UserInput Class*/
void PandaMain::goToBid(){
    UserInput userInput(currentTime, wallet, orderBook);
    userInput.enterBid();
}

/**KSStripes implemented the function for printing the wallet in the Wallet  Class - deleted here*/


/*function for option 8 - continue*/
void PandaMain::nextTimeStep(){
    std::cout << "Sales Statistics" << std::endl;
    std::cout << std::endl;
    
    // Define column width for headers and data
    int headerWidth = 18;
    int dataWidth = 10;
    
    // Set the floating-point output to two decimal places
    std::cout << std::fixed << std::setprecision(2);

    // Print data headers - product names
    std::cout << std::left << std::setw(headerWidth) << "Products Matched" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << std::right << std::setw(dataWidth) << p << " | ";
    }
    std::cout << std::endl;

    // Print stats for "Sales
    std::cout << std::left << std::setw(headerWidth) << "Sales" << " | ";
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << std::right << std::setw(dataWidth) << sales.size() << " | ";
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
    std::cout << std::endl;
    std::cout << "===================================================================================" << std::endl;
    
    currentTime = orderBook.getNexttime(currentTime);
    std::cout << "Current Time: " << currentTime << std::endl;
    std::cout << "================" << std::endl;
    std::cout << std::endl;
}

/*function for invalid keyboard input*/
void PandaMain::invalidChoice(){
    std::cout << "Invalid choice. Choose 1-8" << std::endl;
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
    std::cout << "================" << std::endl;//prints seperator line
    
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
            printSpreadBar();
            break;
        case 5:
            goToAsk();
            break;
        case 6:
            goToBid();
            break;
        case 7:
            wallet.printWallet();
            break;
        case 8:
            nextTimeStep();
            break;
        default:
            invalidChoice();
            break;
    }
}
/**end addition KSStripes**/
