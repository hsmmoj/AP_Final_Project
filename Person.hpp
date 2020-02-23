#ifndef __PERSON__
#define __PERSON__
#include<string>
#include <iostream>
#include "Offer.hpp"
#include "Cart.hpp"
#define MANAGER_EMAIL "admin@gmail.com"
#define MANAGER_USERNAME "admin"
#define MANAGER_PASSWORD "admin"
#define MANAGER_ID 0
#define MANAGER_TYPE "Manger"
#define SELLER_TYPE "Seller"
#define BUYER_TYPE "Buyer"
#define ORDER_INFO_NOMINATOR "productId | productName | offerId | sellerId | soldPrice | amount\n"
#define TRANSACTION_INFO_NOMINATOR "credit\n"
class Person {

    public:
        Person(std::string _email, std::string _username, std::size_t _password, int _id);
        std::string getUsername();
        std::size_t getPassword();
        std::string getEmail();
        int getId();
        virtual std::string getType() = 0;
        double getCredit();
        void addTransaction(double transaction);
        std::string getTransactionInfo(int count);
    private:
        std::string email;
        std::string username;
        std::size_t password;
        int id;

    protected:
        std::vector<double> transactions;
        size_t hashing(std::string password);
        
};


class Manager : public Person {
    public:
        Manager() : Person(MANAGER_EMAIL, MANAGER_USERNAME, hashing(MANAGER_PASSWORD), MANAGER_ID) {};
        virtual std::string getType() {return MANAGER_TYPE;};

};


class Seller : public Person {
    public:
    Seller(std::string _email, std::string _username, std::size_t _password, int _id) : Person(_email, _username, _password, _id) {};
    virtual std::string getType() {return SELLER_TYPE;};
    Offer* findOfferByProductId(int id);
    Offer* findOfferByOfferId(int id);
    void addOffer(Offer* newoffer);
    std::vector<Offer*> getSellerOffers();
    private:
    std::vector<Offer*> offers;
};



class Buyer : public Person {
    public:
    Buyer(std::string _email, std::string _username, std::size_t _password, int _id) : Person(_email, _username, _password, _id) {buyerCart = new Cart;};
    virtual std::string getType() {return BUYER_TYPE;};
    void addGoodsToCart(Offer* offer, int amount, double discountPercent);
    Cart* getCart();
    void addOrder(Cart* cart);
    void resetCart();
    std::string getOrdersInfo(int count);
    std::vector<Cart*> getSellerCarts(int sellerId);
    private:
    Cart* buyerCart;
    std::vector<Cart*> previousOrders;
};


#endif