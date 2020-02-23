#include "Offer.hpp"
using namespace std;
#include <iostream>

Offer::Offer(int _id, double _price, Product* _product, int _amount, int _sellerId) {

    id = _id;
    price =_price;
    product = _product;
    amount = _amount;
    sellerId = _sellerId;
}   

int Offer::getId() {
    return id;
}

double Offer::getPrice() {
    return price;
}

string Offer::getInfoForManager() {
    string ans;
    ans += to_string(product->getId());
    ans += " | ";
    ans += to_string(id);
    ans += " | ";
    ans += to_string(price);
    ans += " | ";
    ans += to_string(amount);
    ans += "\n";
    return ans;
}

string Offer::getInfoForBuyer() {
    string ans;
    ans += to_string(product->getId());
    ans += " | ";
    ans += product->getName();
    ans += " | ";
    ans += to_string(id);
    ans += " | ";
    ans += to_string(price);
    ans += " | ";
    ans += to_string(amount);
    ans += "\n";
    return ans;
}

void Offer::changeAmount(int _amount) {
    amount = _amount;
}


void Offer::changePrice(double _price) {
    price = _price;
}


void Offer::addDiscountCode(string _code, double _percent) {
    discountCodes.insert(pair<string, double>(_code, _percent));
}


double Offer::useDiscountCode(string code) {
    map<string, double>::iterator it;
    it = discountCodes.find(code);
    if(it != discountCodes.end()) {
        double percent = it->second;
        discountCodes.erase(it);
        return percent;
    }
    throw  BadRequestException() ;
}


Product* Offer::getProduct() {
    return product;
}


string Offer::getOfferInfo() {
    string ans = "";
    ans += to_string(product->getId());
    ans += " | ";
    ans += product->getName();
    ans += " | ";
    ans += to_string(id);
    ans += " | ";
    ans += to_string(price);
    ans += " | ";
    ans += to_string(amount);
    ans += "\n";
    return ans;
}


int Offer::getAmount() {
    return amount;
}

int Offer::getSellerId() {
    return sellerId;
}

int Offer::getProductId () {
    return product->getId();
}