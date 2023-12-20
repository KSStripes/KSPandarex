//
//  main.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 10/12/2023.
//

#include "PandaMain.hpp"
//#include "Wallet.hpp"
#include "CandleStick.hpp"
#include <iostream>

//int main(){
//    PandaMain app{};
//    app.init();
//}
    /**testing code to test wallet directly from main.cpp**/
    //Wallet wallet;
    //wallet.insertCurrency("BTC", 10.0);
    //wallet.insertCurrency("USD", 100000.0);
    //std::cout << wallet.toString() << std::endl;
    //wallet.removeCurrency("USD", 10700.0);
    //std::cout << wallet.toString() << std::endl;
    

int main() {
    // Create an instance of the OrderBook class and populate it with data
    OrderBook orderBook{"orders_20200317.csv"};
    std::string currentT = orderBook.getEarliesttime();
    std::string nextT = orderBook.getNexttime(currentT);
    std::string prevT = orderBook.getPreviousTime(currentT);
    
    std::cout << "Current Time: " << currentT << std::endl;
    std::cout << "Next Timestamp: " << nextT << std::endl;
    std::cout << "Prev Timestamp: " << prevT << std::endl;
    std::cout << "========================" << std::endl;
    
    //call generateCandlesticks
    //std::vector<Candlestick> candlesticks = generateCandlesticks(orderBook);

    // Loop through the generated Candlestick objects and print their data
//    for (const Candlestick& candlestick : candlesticks) {
       // std::cout << "Open: " << candlestick.getOpen() << std::endl;
        //std::cout << "High: " << candlestick.getHighPrice() << std::endl;
        //std::cout << "Low: " << candlestick.getMinPrice() << std::endl;
       // std::cout << "Close: " << candlestick.getClose() << std::endl;
        
   // }

    for (std::string const& p : orderBook.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
        
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentT);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << Candlestick::getHighPrice(entries) << std::endl;
        std::cout << "Minimum ask: " << Candlestick::getMinPrice(entries) << std::endl;
        std::cout << "Mean ask: " << Candlestick::getMeanPrice(entries) << std::endl;
        std::cout << "Highest ask at current Time: " << Candlestick::highestAtOneTime(p, currentT, OrderBookType::ask, orderBook) << std::endl;
        std::cout << "Minimum ask at current Time: " << Candlestick::highestAtOneTime(p, currentT, OrderBookType::ask, orderBook) << std::endl;
        std::cout << "Mean ask: " << Candlestick::getMeanPrice(entries) << std::endl;
        std::cout << "========================" << std::endl;
        
    }
    
    
    return 0;
}
