#include "Cart.hpp"
using namespace std;

void Cart::putOfferInCart(Offer* offer, int amount, double discountPercent) {
    double unitPrice = offer->getPrice();
    double discountedPrice = calculateDiscountPrice(unitPrice, amount, discountPercent);
    goods newGoods = {
        offer,
        amount,
        discountedPrice,

    };
    offersInCard.push_back(newGoods);  
}


double Cart::calculateDiscountPrice(double unitPrice, int amount,  double discountPercent) {
    double remainedPercent = FULL_PERCENT - discountPercent;
    double totalPrice = amount * unitPrice;
    double discountedPrice = (remainedPercent * totalPrice) / FULL_PERCENT;
    return discountedPrice;
}


string Cart::getCartInfo() {
    if(offersInCard.size() == 0)
        return EMPTY;
    string ans = "";
    double sumPrice = 0;
    for(unsigned int i = offersInCard.size(); i > 0 ; i--) {
        int productId = offersInCard[i-1].offer->getProduct()->getId();
        string productName = offersInCard[i-1].offer->getProduct()->getName();
        int offerId = offersInCard[i-1].offer->getId();
        int sellerId = offersInCard[i-1].offer->getSellerId();
        double totalDiscountedPrice = offersInCard[i-1].discountedPrice;
        int amount = offersInCard[i-1].amount;
        sumPrice += totalDiscountedPrice;
        ans += printCartInfo(productId, productName, offerId, sellerId, totalDiscountedPrice, amount);
    }
    ans += "Total Price :" + to_string(sumPrice);
    return ans;

}


string Cart::printCartInfo(int productId, string productName, int offerId, int sellerId, double totalDiscountedPrice, int amount) {
    string ans = "";
    ans += to_string(productId);
    ans += " | ";
    ans += productName;
    ans += " | ";
    ans += to_string(offerId);
    ans += " | ";
    ans += to_string(sellerId);
    ans += " | ";
    ans += to_string(totalDiscountedPrice);
    ans += " | ";
    ans += to_string(amount);
    ans += "\n";
    
    return ans;
}


double Cart::getTotoalPrice() {
    double totalPrice = 0;
    for(unsigned int i = 0; i < offersInCard.size(); i++) {
        totalPrice += offersInCard[i].discountedPrice;
    }
    return totalPrice;
}


vector<pair<int,double>> Cart::getPayInfo() {
    vector<pair<int, double>> allPayInfos;
    for(unsigned int i = 0; i < offersInCard.size(); i++) {
        int sellerId = offersInCard[i].offer->getSellerId();
        double moneyToPay = offersInCard[i].discountedPrice;
        pair<int, double> payInfo (sellerId, moneyToPay);
        allPayInfos.push_back(payInfo);
    }
    return allPayInfos;
}