//
//  Wallet.cpp
//  KSPandarex
//
//  Created by Kristin Schumann on 19/12/2023.
//

#include "Wallet.hpp"
#include "CSVReader.hpp"
#include <iostream>

//public:
//Constructor
Wallet::Wallet(){
    
}
    /** add cash to the wallet */
void Wallet::insertCurrency(std::string type, double amount){
    double balance;
    if (amount < 0){
        throw std::exception{};
    }
    if(currencies.count(type) == 0)//not there yet
    {
        balance = 0;
    }else{
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

/** remove currency from the wallet */
bool Wallet::removeCurrency(std::string type, double amount){
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0) // not there yet
    {
        //std::cout << "No currency for " << type << std::endl;
        return false;
    }
    else { // if we have currency, is there enough?
        if (containsCurrency(type, amount))// we have enough
        {
            //std::cout << "Removing " << type << ": " << amount << std::endl;
            currencies[type] -= amount;
            return true;
        }
        else // they have it but not enough.
            return false;
    }
}


    
    /**check if wallet contains this much or more currency*/
bool Wallet::containsCurrency(std::string type, double amount){
    if(currencies.count(type) == 0) return false;
    else return currencies[type] >= amount;
}
    
/**process to string what's currently in the wallet and print it in pairs of currency and amount**/
std::string Wallet::toString(){
    std::string s;
    for (std::pair<std::string,double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}


/** checks if the wallet can cope with this ask or bid.*/
bool Wallet::canFulfillOrder(OrderBookEntry order){
    std::vector<std::string> currs = CSVReader::tokenize(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0]; //Access currency befor '/'
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;

        return containsCurrency(currency, amount);
    }
    // bid
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1]; //access currency after '/'
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }


    return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{
    std::vector<std::string> currs = CSVReader::tokenize(sale.product, '/');
    // ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;

    }
    // bid
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

/**include overloaded operator to display the contents of the wallet object in the format defined by toString()**/
std::ostream& operator<<(std::ostream& os,  Wallet& wallet)
{
    os << wallet.toString();
    return os;
}

/**KSStripes modified how the wallet is displayed to make it more visual for the user**/
void Wallet::printWallet(){
    std::cout << "================" << std::endl;//prints seperator line
    
    //Print wallet image
    std::cout << "YOUR WALLET" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⡿⠛⠛⠛⢻⡇⠀⠀⠀⢠⡿⠈⠉⠛⠻⠿⣿⣿⣿⣿⣿⣿⣿" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⢸⡇⠀⠀⢀⣾⠃⠀⠀⠀⠀⠀⠀⠀⢙⣿⣿⣿⣿" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⣿⠃⠀⠀⣼⠇⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿" << std::endl;
    std::cout << "⣿⣿⡿⠛⠛⠛⣿⠀⠀⠀⣿⠀⠀⢰⡟⠀⠀⠀⠀⠀⠀⠀⠀⢰⡟⠛⢛⣿⣿" << std::endl;
    std::cout << "⣿⣿⡷⠤⠤⠤⠿⠤⠤⠾⠿⠤⠤⠿⠧⠤⠤⠤⠤⠤⠤⠤⠿⠧⠤⠼⢿⣿⣿" << std::endl;
    std::cout << "⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⢸⣿⣿" << std::endl;
    std::cout << "⣿⣿⡇Your wallet contains:    ⢸⣿⣿" << std::endl;
    std::cout << "⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣸⣿⣿" << std::endl;
    std::cout << "⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡟⠉⣿⠻⣯⠉⠉⢹⣿" << std::endl;
    std::cout << "⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀⠀⠘⢷⣤⣽⣿⣯⣤⣤⣼⣿" << std::endl;
    
    // wallet text in between
            std::string walletString = toString(); // Get the wallet content as a string
            if (walletString.empty()) {
                std::cout << "⣿⣿⡇Your wallet is empty!     ⢸⣿⣿" << std::endl;
            } else {
                std::cout << walletString << std::endl;
            }
    //bottom border
    std::cout << "⣿⣿⣧⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣼⣿⣿" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "image source: https://emojicombos.com" << std::endl;
}
/**end modification KSStripes*/
