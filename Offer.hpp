#ifndef __OFFER__
#define __OFFER__
#include <string>
#include<map>
#include<iterator>
#include "Product.hpp"
#include "Exception.hpp"


class Offer{
    public:
    Offer(int _id, double _price, Product* _product, int _amount, int _sellerId);
    int getId();
    double getPrice();
    std::string getInfoForManager();
    std::string getInfoForBuyer();
    void changePrice(double _price);
    void changeAmount(int _amount);
    void addDiscountCode(std::string code, double percent);
    double useDiscountCode(std::string code);
    Product* getProduct();
    std::string getOfferInfo();
    int getAmount();
    int getSellerId();
    int getProductId ();
    


    private:
    int id;
    int amount;
    double price;
    Product* product;
    std::map<std::string, double> discountCodes;
    int sellerId;
};

#endif