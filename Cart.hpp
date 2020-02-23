#ifndef __CART__
#define __CART__
#include<string>
#include<vector>
#include<iostream>
#include "Offer.hpp"
#define FULL_PERCENT 100    
#define EMPTY "Empty\n"

class Cart {
    public:
    Cart() {};
    void putOfferInCart(Offer* _offer, int _amount, double _discountPercent);
    std::string getCartInfo();
    double getTotoalPrice();
    std::vector<std::pair<int,double>> getPayInfo();

    private:
    struct goods {Offer* offer; int amount; double discountedPrice; };
    std::vector<goods> offersInCard;
    double calculateDiscountPrice(double unitPrice, int amount, double discountPercent);
    std::string printCartInfo(int productId, std::string productName, int offerId, int sellerId, double totalDiscountedPrice, int amount);
};



#endif