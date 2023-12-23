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
#include "CandleStick.hpp"


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


/**KSStripes added a function to map user input done as a string to an enum class in the OrderBookEntry.
 *Necessary conversion to pass userinput into the candleStickRequest function*/
OrderBookType UserInput::stringToOrderBookType(const std::string& orderTypeStr) {
    if (orderTypeStr == "bid") {
        return OrderBookType::bid;
    } else if (orderTypeStr == "ask") {
        return OrderBookType::ask;
    } else if (orderTypeStr == "unknown") {
        return OrderBookType::unknown;
    } else if (orderTypeStr == "asksale") {
        return OrderBookType::asksale;
    } else if (orderTypeStr == "bidsale") {
        return OrderBookType::bidsale;
    } else {
        // Handle the case when the input doesn't match any enum value
        throw std::invalid_argument("Invalid order type: " + orderTypeStr);
    }
}


/** KSStripes created function to deal with menu item 3 to enter a Candlestick product and ordertype
 * this function was meant to print a menu for the user and some instructions to type a product and an ordertype
 * process the userinput into the console and tokenize it
 * generate the candlestick corresponding to the product and ordertype by the user
 * candlestick should use the pandamain current time, */
void UserInput::candlestickRequest(){
    /**some text to explain the menu**/
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Your options: " << std::endl;
    std::cout << "Ordertyes: bid or ask " << std::endl;
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Enter your analysis request!" << std::endl;
    std::cout << "For all asks to buy USDT with DOGE, enter DOGE/USDT,ask" << std::endl;
    std::cout << "For all bids to buy DOGE with USDT, enter USDT/DOGE,bid" << std::endl;

    
    /**print types of orders mapped in OrderBook*/
    for (std::string const& p : orderBookRef.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
    }
    
    
    
    //get user-typed input and save as string to input
    std::string input;
    std::getline(std::cin, input);

    
    //use input string, break it into its parts, use its values using currently CSVReader functions
    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    
    //check if user has typed string as per example (3 typed CSV, ex eg ETH/BTC,200,0.5)
    if (tokens.size() != 2){
        std::cout << "UserInput::enterAsk(): Bad input! " << input << std::endl;
    }
    else{
        std::string product = tokens[0];   // Extract product from user input
        std::string orderType = tokens[1]; // Extract orderType from user input
        OrderBookType orderBookType = stringToOrderBookType(orderType); // Convert to enum

        std::cout << "You typed: " << input << std::endl;
        std::cout << "================" << std::endl;//prints seperator line
        try{
            /** instantiate  candlestick for userinput*/
            Candlestick candlestick(orderBookRef);
            /**Create vector and pass tokenized user input for product and orderType*/
            std::vector<Candlestick> candlestickData =
                candlestick.getOneCandlestick(orderBookRef,
                                              currentTimeRef,
                                              product,
                                              orderBookType);
        

            /**Loop through the candlestickData and print candlestick to the terminal
             *My intention was to print 6 graphs for 6 timestamps next to each other but I couldn't get it to work*/
            for (int i = 0; i < std::min(6, static_cast<int>(candlestickData.size())); ++i) {
                // Access and print the member variables of each Candlestick object
                const Candlestick& candlestick = candlestickData[i];
                std::cout << "Timestamp: " << candlestick.timestamp << std::endl;
                std::cout << "Open: " << candlestick.open << std::endl;
                std::cout << "High: " << candlestick.high << std::endl;
                std::cout << "Low: " << candlestick.low << std::endl;
                std::cout << "Close: " << candlestick.close << std::endl;
                std::cout << "========================" << std::endl;

                // Print the candlestick chart for the current candlestick
                candlestick.printCandlestickChart(candlestickData,
                                                  currentTimeRef);
            }
        }catch (const std::exception& e){
            std::cout << "UserInput::candlestickRequest(): Bad input!" << std::endl;
        }
    }
}


/**function for option 4 - entering an ask */
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

///*function for option 5 - making a bid*/
void UserInput::enterBid(){
    /**some text to explain the menu**/
    std::cout << "================" << std::endl;//prints seperator line
    std::cout << "Enter your bid. Format: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::cout << "Your options: " << std::endl;
    
    /**print types of orders mapped in OrderBook*/
    for (std::string const& p : orderBookRef.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
    }
    
    std::cout << "If you have ETH and want DOGE, enter DOGE/ETH,xx,xx" << std::endl;
    
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
