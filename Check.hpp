#ifndef __CHECK__
#define __CHECK__
class Check;
#include <string>
#include <vector>
#include "App.hpp"
#include "Person.hpp"
#include "model.hpp"

class Check {

    public:
    Check(App* _app) {app = _app;};
    virtual bool check() = 0;

    protected:
    App* app;

};

class SignUpCheck : public Check{
    public:
    SignUpCheck(App* app, std::string _username) : Check(app) { username = _username; };
    virtual bool check();

    private:
    std::string username;
  
};

class LoginCheck : public Check{
    public:
    LoginCheck(App* app, std::string _email, std::size_t _password);
    virtual bool check();

    private:
    std::string email;
    std::size_t password;
    
};


class addProductPermissionCheck : public Check{
    public:
    addProductPermissionCheck(App* app) : Check(app) {};
    virtual bool check();
};

class getProductPermissionCheck : public Check {
    public:
    getProductPermissionCheck(App* app) : Check(app) {};
    virtual bool check();
};

class sellerAccessCheck : public Check {
    public:
    sellerAccessCheck(App* app)  : Check(app) {};
    virtual bool check();
}; 


class addOfferCheck : public Check {
    public:
    addOfferCheck(App* app, int _id) : Check(app) {id = _id;};
    virtual bool check();
    private:
    int id;
};

class managerAccessCheck : Check {
    public:
    managerAccessCheck(App* app) : Check(app) {};
    virtual bool check();
};


class buyerAccessCheck : Check {
    public:
    buyerAccessCheck(App* app) : Check(app) {};
    virtual bool check();
};

class CheckCommentValidity : Check {
    public:
    CheckCommentValidity(App* app, Model* _model, std::string _comment) : Check(app) {model = _model; comment = _comment;}
    virtual bool check();
    private:
    Model* model;
    std::string comment;
};


#endif
