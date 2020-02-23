#include "Check.hpp"
using namespace std;
#include <iostream>


bool SignUpCheck::check(){
    Person* foundPerson = app->findPersonByUsername(username);
    if(foundPerson == NULL)
        return false;
    else
        return true;
}


LoginCheck::LoginCheck(App* app, std::string _email, std::size_t _password)
    : Check(app) {
        email = _email;
        password = _password;
}

bool LoginCheck::check() {
    Person* foundPerson = app->findPersonByEmail(email);
    if(foundPerson == NULL || foundPerson->getPassword() != password)
        return true;
    else
        return false;
}


bool addProductPermissionCheck::check () {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    Manager* manger = dynamic_cast<Manager*>(loggedPerson);
    if(manger == NULL)
        check = true;
    return check;
}


bool getProductPermissionCheck::check() {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    string type = loggedPerson->getType();
    if(type != SELLER_TYPE && type != BUYER_TYPE)
        check = true;

    return check;

}

bool managerAccessCheck::check () {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    Manager* manger = dynamic_cast<Manager*>(loggedPerson);
    if(manger == NULL)
        check = true;
    
    return check;
}


bool sellerAccessCheck::check() {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(seller == NULL)
        check = true;
    return check;
}


bool addOfferCheck::check() {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(app->findProductById(id) == NULL || seller->findOfferByProductId(id) != NULL)
        check = true;
    return check;

}


bool buyerAccessCheck::check() {
    bool check = false;
    Person* loggedPerson = app->getLoggedPerson();
    string type = loggedPerson->getType();
    if(type != BUYER_TYPE)
        check = true;

    return check;
}

bool CheckCommentValidity::check() {
    bool ans = model->predict(comment);
    return ans;
}