#include "Person.hpp"
using namespace std;
#define INITIAL_CEDIT 0


Person::Person(string _email, string _username, size_t _password, int _id)
{
    email = _email;
    username = _username;
    password = _password;
    id = _id;
    transactions.push_back(INITIAL_CEDIT);
}



string Person::getUsername(){
    return username;
}

size_t Person::getPassword() {
    return password;
}


string Person::getEmail() {
    return email;
}


int Person::getId() {
    return id;
}


Offer* Seller::findOfferByProductId(int id) {
    for(unsigned int i = 0; i < offers.size(); i++) {
        if(offers[i]->getProductId() == id)
            return offers[i];
    }
    return NULL;
}


void Seller::addOffer(Offer* newoffer) {
    offers.push_back(newoffer);
}


vector<Offer*> Seller::getSellerOffers() {
    return offers;
}


void Buyer::addGoodsToCart(Offer* offer, int amount, double discountPercent) {
    buyerCart->putOfferInCart(offer, amount, discountPercent);
    
}


Cart* Buyer::getCart() {
    return buyerCart;
}



double Person::getCredit() {
    int endNum = transactions.size();
    return transactions[endNum - 1];
}


void Person::addTransaction(double transaction) {
    double credit = getCredit();
    double newCredit = credit + transaction;
    transactions.push_back(newCredit);
}


void Buyer::resetCart() {
    buyerCart = new Cart;
}


void Buyer::addOrder(Cart* cart) {
    previousOrders.push_back(cart);
}


string Buyer::getOrdersInfo(int count) {
    int orderSize = previousOrders.size();
    if(orderSize == 0)
        throw NotFoundException();
    if(orderSize < count)
        count = orderSize;
    string ans = ORDER_INFO_NOMINATOR;
    for(unsigned int i = count ; i > 0; i--) {
        ans += previousOrders[i-1]->getCartInfo();
        if(i != 1)
            ans += "****\n"; 
    }
    return ans;
}


string Person::getTransactionInfo(int count) {
    int transactionSize = transactions.size();
    if(transactionSize < count)
        count = transactionSize;
    string ans = TRANSACTION_INFO_NOMINATOR;
    for(unsigned int i = count; i > 0; i--) {
        ans += to_string(transactions[i-1]);
        ans += "\n";
    }
    return ans;
}


Offer*  Seller::findOfferByOfferId(int id) {
    for(unsigned int i = 0; i < offers.size(); i++) {
        if(offers[i]->getId() == id)
            return offers[i];
    }
    return NULL;

}

size_t Person::hashing(string password) {
    hash<string> hasher;
    return hasher(password);
}