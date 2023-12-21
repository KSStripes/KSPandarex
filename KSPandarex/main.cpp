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

int main(){
    PandaMain app{};
    app.init();
}
    /**testing code to test wallet directly from main.cpp**/
    //Wallet wallet;
    //wallet.insertCurrency("BTC", 10.0);
    //wallet.insertCurrency("USD", 100000.0);
    //std::cout << wallet.toString() << std::endl;
    //wallet.removeCurrency("USD", 10700.0);
    //std::cout << wallet.toString() << std::endl;
    
