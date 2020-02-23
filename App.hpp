#ifndef __APP__
#define __APP__
class App;
#include<vector>
#include<string>
#include<iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include "Person.hpp"
#include "Check.hpp"
#include "Exception.hpp"
#include "Product.hpp"
#include <unordered_map> 
#include "model.hpp"
#include "model.hpp"

#define SEPRATOR "|"
#define NEXT_LINE "\n"
#define WEIGHT "Weight: "
#define NUM_OF_SEATS "Num. of Seats: "
#define NUM_OF_CYL "Num. of Cylinders: "
#define ENGINE_CAPACITY "Engine Capacity: "
#define PARKING_SENSOR "Reverse Parking Sensors: "
#define CPU_FRE "CPU Frequency: "
#define MEMORY_IN "Built-in Memory: "
#define RAM "RAM: "
#define DISPLAY_SIZE "Display Size: "
#define CAMERA_RES "Camera Resolution: "
#define OPERATING_SYS "Operating System: "
#define SCREEN_SIZE "Screen Size: "
#define SCREEN_TYPE "Screen Type: "
#define RESOLOTION "Resolution: "
#define THREE_D "3D: "
#define HDR "HDR: "
#define GET_OFFERS_HEADER "productId | productName | offerId | offerUnitPrice | offerAmount\n"
#define SESSION_ID_LENGTH   17


class App{

    public:
    App();
    std::size_t hashing(std::string password);
    std::string signUp(std::string email, std::string username, std::size_t password, std::string type = "buyer");
    std::string login(std::string email, std::size_t password);
    std::string login(std::string sessionId);
    std::string logout(std::string sessionId);
    std::string importProduct(std::string type, std::string filePath);
    std::string handleOffers(std::string order, std::string field);
    std::string getProducts();
    std::string offer(std::string productId, std::string price, std::string amount);
    std::string myOffers();
    std::string changeOffer(std::string offerId, std::string price, std::string amount);
    std::string generateDiscountCode(std::string offerId, std::string discountPercent, std::string discoutNumber);
    std::string offersOnProduct(std::string productId);
    std::string productDetail(std::string productId);
    std::string getComments(std::string productId);
    std::string addToCart(std::string OfferId, std::string amount, std::string discountCode = "");
    std::string showCart();
    std::string submitCart();
    std::string orders(std::string counts);
    std::string wallet(std::string);
    std::string chargeWallet(std::string amount);
    std::string makeComment(std::string productId, std::string comment);
    std::string compareTwoProducts(std::string productId1, std::string productId2);
    std::string getOffers();
    bool isAdmin() {return loggedPerson->getType() == MANAGER_TYPE;}
    bool isSeller() {return loggedPerson->getType() == SELLER_TYPE; }
    bool isBuyer() {return loggedPerson->getType() == BUYER_TYPE; }
    std::vector<std::vector<std::string>> static parser(std::string record, char sign);
    


    Person* findPersonByUsername(std::string username);
    Person* findPersonByEmail   (std::string email);
    Person* getLoggedPerson();
    Product* findProductById(int id);
    
    private:
    std::vector<Person*> people;
    int currentPersonId;
    int currentProductId;
    int currentOfferId;
    Person* loggedPerson;
    Check* check;
    std::vector<Product*> products;
    std::vector<Offer*> offers;
    Model* model;
    std::vector<std::string> readCsv(std::string filePath);
    std::vector<std::string> spliter(std::string & input);
    std::vector<std::vector<std::string>> process_info(std::string filePath);
    std::map<Person*, std::string> sessionIds;
    void mobileInfoFiller(std::vector<std::vector<std::string>> info);
    void carInfoFiller(std::vector<std::vector<std::string>> info);
    void tvInfoFiller(std::vector<std::vector<std::string>> info);
    std::string printProducts();
    void sortOffers(std::string order, std::string field);
    void sortOffersByID(std::string order);
    void sortOffersByPrice(std::string order);
    bool static ascendCompareOfferByID(Offer* one, Offer* two);
    bool static descendCompareOfferByID(Offer* one, Offer* two);
    bool static ascendCompareOfferByPrice(Offer* one, Offer* two);
    bool static descendCompareOfferByPrice(Offer* one, Offer* two);
    std::vector<std::string> randomStringGenerator(int count);
    std::string printDiscountCodes(std::vector<std::string> codes);
    std::string printOffersOnProduct(std::vector<Offer*> productOffers);
    Offer* findOfferById(int id);
    Person* findPersonBySessionId(std::string sessionId);
    void payToSellers(Cart* cart);
    Seller* findSellerById(int id);
    std::string printComparisonCar(Product* product1, Product* product2);
    std::string printComparisonMobile(Product* product1, Product* product2);
    std::string printComparisonTV(Product* product1, Product* product2);

    



};


#endif