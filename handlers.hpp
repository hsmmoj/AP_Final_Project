#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include "Interface.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>


class SignupHandler : public RequestHandler {
public:
  SignupHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class LogoutHandler: public RequestHandler {
public:
  LogoutHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class HomePageHandler : public RequestHandler {
public:
  HomePageHandler(App* _app) {app = _app;}
  Response *callback(Request *);
  std::string makeHtml();
private:
  App* app;
};

class UploadHandler : public RequestHandler {
public:
  UploadHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class ShowAddOfferPage : public RequestHandler {
public:
  ShowAddOfferPage(App* _app) {app = _app;}
  Response *callback(Request *);
  std::string makeHtml();
private:
  App* app;
};

class AddOfferHandler : public RequestHandler {
public:
  AddOfferHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class WalletHandler : public RequestHandler {
public:
  WalletHandler(App* _app) {app = _app;}
  Response *callback(Request *);
  std::string makeHtml();
private:
  App* app;
};

class ChargeHandler : public RequestHandler {
public:
  ChargeHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class ProductDetailHandler : public RequestHandler {
public:
  ProductDetailHandler(App* _app) {app = _app;}
  Response *callback(Request *);
  std::string makeHtml(Request *);
private:
  App* app;
};

class CommentHandler : public RequestHandler {
public:
  CommentHandler(App* _app) {app = _app; }
  Response *callback(Request *);
private:
  App* app;
};

class AddToCartHandler : public RequestHandler {
public:
  AddToCartHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

class CartHandler : public RequestHandler {
public:
  CartHandler(App* _app) {app = _app;}
  Response *callback(Request *);
  std::string makeHtml();
private:
  App* app;
};

class BuyHandler : public RequestHandler {
public:
  BuyHandler(App* _app) {app = _app;}
  Response *callback(Request *);
private:
  App* app;
};

#endif
