#include "Interface.hpp"
#include "Exception.hpp"
#define LAST_SPACE_INDEX 5
#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define IMPORT_PRODUCT "importProducts"
#define OFFERS "offers"
#define GET_PRODUCTS "getProducts"
#define  OFFER "offer"
#define  MY_OFFERS "myOffers"
#define CHANGE_OFFER "changeOffer"
#define GENERATE_DISCOUNT_CODE "generateDiscountCode"
#define OFFERS_ON_PRODUCTS "offersOnProduct"
#define PRODUCT_DETAILS "productDetail"
#define COMMENTS "comments"
#define ADD_TO_CART "addToCart"
#define CART "cart"
#define SUBMIT_CART "submitCart"
#define ORDERS "orders"
#define WALLET "wallet"
#define CHARGE_WALLET "chargeWallet"
#define COMMENT "comment"
#define COMPARE "compare"
#define POST "POST"
#define GET "GET"
#define SIGN "?"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define TYPE "type"




using namespace std;

Interface::Interface()
{
    app = new App;
}

vector<string> Interface::parse(string command) {
    vector<string> ans;
    stringstream tmp(command);
    string word;

    while(getline(tmp, word, ' '))
        ans.push_back(word);
    return ans;
}


string Interface::extractComment(string command) {
    int count = 0;
    string comment = "";
    for(unsigned int i = 0; i < command.size(); i++){
        if(command[i] == ' ')
            count ++;
        if(count == LAST_SPACE_INDEX)
            comment = command.substr(i+2,command.size());
    }
    return comment;
}



string Interface::process(string command) {
    string ans = "\n";
    vector<string> parsedCommand = parse(command);
    if(parsedCommand.size() < 2)
        throw BadRequestException();
    if(!(parsedCommand[0] == GET || parsedCommand[0] == POST))
        throw BadRequestException();
    string commandType = parsedCommand[1];

    if(commandType == SIGNUP) {
        if(parsedCommand.size() < 9 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != EMAIL || parsedCommand[5] != USERNAME || parsedCommand[7] != PASSWORD)
            throw BadRequestException();

        if(parsedCommand.size() == 9)
            ans = app->signUp(parsedCommand[4], parsedCommand[6], hashing(parsedCommand[8]));
        else if(parsedCommand.size() == 11)
        {   if(parsedCommand[9] != TYPE)
                throw BadRequestException();
            ans = app->signUp(parsedCommand[4], parsedCommand[6], hashing(parsedCommand[8]), parsedCommand[10]);
        }
        else
            throw BadRequestException();
    }
    else if(commandType == LOGIN) {
        if(parsedCommand.size() < 7 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != EMAIL || parsedCommand[5] != PASSWORD)
            throw BadRequestException();
        // if(parsedCommand[4] == MANAGER_EMAIL)
        //     ans = app->login(stoi(parsedCommand[6]));
        else
            ans = app->login(parsedCommand[4], hashing(parsedCommand[6]));
    }
    // else if(commandType == LOGOUT) {
    //     if(parsedCommand.size() < 2 || parsedCommand[0] != POST)
    //         throw BadRequestException();
    //     ans = app->logout();
    // }
    else if(commandType == IMPORT_PRODUCT) {
        if(parsedCommand.size() < 7 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != TYPE || !(parsedCommand[4] == "mobile" || parsedCommand[4] == "tv" || parsedCommand[4] == "car") || parsedCommand[5] != "filePath")
            throw BadRequestException();
        ans = app->importProduct(parsedCommand[4], parsedCommand[6]);
    }
    else if(commandType == OFFERS) {
        if(parsedCommand.size() == 2) {
            if(parsedCommand[0] != GET)
                throw BadRequestException();
            ans = app->getOffers();
        }
        else if(parsedCommand.size() < 7 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "order" || !(parsedCommand[4] == "ASCEND" || parsedCommand[4] == "DESCEND") || parsedCommand[5] != "field" || !(parsedCommand[6] == "offerId" || parsedCommand[6] == "offerPrice"))
            throw BadRequestException();
        else
            ans = app->handleOffers(parsedCommand[4], parsedCommand[6]);
    }
    else if(commandType == GET_PRODUCTS)
        ans = app->getProducts();

    else if(commandType == OFFER) {
        if(parsedCommand.size() < 9 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "productId" || parsedCommand[5] != "offerUnitPrice" || parsedCommand[7] != "offerAmount")
            throw BadRequestException();
        ans = app->offer(parsedCommand[4], parsedCommand[6], parsedCommand[8]);
    }
    else if(commandType == MY_OFFERS) {
        if(parsedCommand[0] != GET)
            throw BadRequestException();
        ans = app->myOffers();
    }
    else if(commandType == CHANGE_OFFER) {
        if(parsedCommand.size() < 9 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "offerId" || parsedCommand[5] != "offerUnitPrice" || parsedCommand[7] != "offerAmount")
            throw BadRequestException();
        ans = app->changeOffer(parsedCommand[4], parsedCommand[6], parsedCommand[8]);
    }
    else if(commandType == GENERATE_DISCOUNT_CODE) {
        if(parsedCommand.size() < 9 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "offerId" || parsedCommand[5] != "discountPercent" || parsedCommand[7] != "discountNumber")
            throw BadRequestException();
        ans = app->generateDiscountCode(parsedCommand[4], parsedCommand[6], parsedCommand[8]);
    }
    else if(commandType == OFFERS_ON_PRODUCTS) {
        if(parsedCommand.size() < 5 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "productId")
            throw BadRequestException();
        ans = app->offersOnProduct(parsedCommand[4]);
    }
    else if(commandType == PRODUCT_DETAILS) {
        if(parsedCommand.size() < 5 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "productId")
            throw BadRequestException();
        ans = app->productDetail(parsedCommand[4]);
    }
    else if(commandType == COMMENTS) {
        if(parsedCommand.size() < 5 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "productId")
            throw BadRequestException();
        ans = app->getComments(parsedCommand[4]);
    }
    else if(commandType == ADD_TO_CART) {
        if(parsedCommand.size() < 7 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "offerId" ||parsedCommand[5] != "amount")
            throw BadRequestException();
        if(parsedCommand.size() == 7)
            ans = app->addToCart(parsedCommand[4], parsedCommand[6]);
        else if(parsedCommand.size() < 9 || parsedCommand[7] != "discountCode")
            throw BadRequestException();
        else
            ans = app->addToCart(parsedCommand[4], parsedCommand[6], parsedCommand[8]);
    }
    else if(commandType == CART) {
        if(parsedCommand[0] != GET)
            throw BadRequestException();
        ans = app->showCart();
    }
    else if(commandType == SUBMIT_CART) {
        if(parsedCommand[0] != POST)
            throw BadRequestException();
        ans = app->submitCart();
    }
    else if(commandType == ORDERS) {
        if(parsedCommand.size() < 5 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "count")
            throw BadRequestException();
        ans = app->orders(parsedCommand[4]);
    }
    else if(commandType == WALLET) {
        if(parsedCommand.size() < 5 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "count")
            throw BadRequestException();
        ans = app->wallet(parsedCommand[4]);
    }
    else if(commandType == CHARGE_WALLET){
        if(parsedCommand.size() < 5 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "amount")
            throw BadRequestException();
        ans = app->chargeWallet(parsedCommand[4]);
    }
    else if(commandType == COMMENT) {
        if(parsedCommand.size() < 7 || parsedCommand[0] != POST || parsedCommand[2] != SIGN || parsedCommand[3] != "productId" || parsedCommand[5] != "comment")
            throw BadRequestException();
        ans = app->makeComment(parsedCommand[4], extractComment(command));
    }
    else if(commandType == COMPARE) {
        if(parsedCommand.size() < 7 || parsedCommand[0] != GET || parsedCommand[2] != SIGN || parsedCommand[3] != "productId1" || parsedCommand[5] != "productId2")
            throw BadRequestException();
        ans = app->compareTwoProducts(parsedCommand[4], parsedCommand[6]);
    }

    else
        throw NotFoundException();
    return ans;
}

void Interface::read() {
    string command, result;
    while(getline(cin, command)) {
        try{
        result = process(command);
        cout << result;
        }
        catch(Exception &exception) {
            cout << exception.what() <<endl;
        }
    }
}

size_t Interface::hashing(string password) {
    hash<string> hasher;
    return hasher(password);
}