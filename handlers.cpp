#include "handlers.hpp"

using namespace std;


Response* SignupHandler::callback(Request* req) {
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	string repass = req->getBodyParam("repassword");
	string email = req->getBodyParam("email");
	string type = req->getBodyParam("type");
	try {
		if (password != repass)
			throw Server::Exception("password does not match");
		app->signUp(email, username, app->hashing(password), type);
	}
	catch (Exception & ex) {
		throw Server::Exception(ex.what());
	}
	Response* res = Response::redirect("/login");
	return res;
}

Response* LoginHandler::callback(Request* req) {
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	string sessionId;
	try {
		sessionId = app->login(username, Interface::hashing(password));
	}
	catch (Exception & exception) {
		throw Server::Exception(exception.what());
	}
	Response* res = Response::redirect("/home");
	res->setSessionId(sessionId);
	return res;
}

Response* LogoutHandler::callback(Request* req) {
	string sessionId = req->getSessionId();
	try {
		app->logout(sessionId);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/login");
	return res;
}

Response* HomePageHandler::callback(Request* req) {
	string sessionId = req->getSessionId();
	try {
		app->login(sessionId);
	}
	catch (Exception & exception) {
		throw Server::Exception(exception.what());
	}
	if (app->isAdmin()) {
		Response* res = Response::redirect("/upload");
		return res;
	}

	Response* res = new Response();
	res->setHeader("Content-Type", "text/html");
	res->setBody(makeHtml());
	return res;
}

string topCode(string title, string type) {
	string res = "";
	res += "<!DOCTYPE html>";
	res += "<html>";
	res += "<head>";
	res += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">";
	res += "<meta content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0\" name=\"viewport\">";
	res += "<meta name=\"viewport\" content=\"width=device-width\">";
	res += "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">";
	res += "<style>body{margin-top:20px;background:#eee}.container{margin-right:auto;margin-left:auto;padding-right:15px;padding-left:15px;width:100%}@media (min-width:576px){.container{max-width:540px}}@media (min-width:768px){.container{max-width:720px}}@media (min-width:992px){.container{max-width:960px}}@media (min-width:1200px){.container{max-width:1140px}}.card-columns .card{margin-bottom:.75rem}@media (min-width:576px){.card-columns{column-count:3;column-gap:1.25rem}.card-columns .card{display:inline-block;width:100%}}.text-muted{color:#9faecb!important}p{margin-top:0;margin-bottom:1rem}.mb-3{margin-bottom:1rem!important}.input-group{position:relative;display:flex;width:100%}</style>";
	res += "<script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script>";
	res += "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\"></script>";
	res += "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\"></script>";
	res += "<link href=\"https://maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css\" rel=\"stylesheet\">";
	res += "</head>";
	res += "<body>";
	res += "<div class=\"container\">";
	res += "    <div class=\"row flex-lg-nowrap\">";
	res += "        <div class=\"col\">";
	res += "            <div class=\"row\">";
	res += "                <div class=\"col mb-3\">";
	res += "                    <div class=\"card\">";
	res += "                        <div class=\"card-body\">";
	res += "                            <div class=\"e-profile\">";
	res += "                                <div class=\"row\">";
	res += "                                    <div class=\"col d-flex flex-column flex-sm-row justify-content-between mb-3\">";
	res += "                                        <div class=\"text-center text-sm-left mb-2 mb-sm-0\">";
	res += "                                            <h1 class=\"pt-sm-2 pb-1 mb-0 text-nowrap\"> " + title + " </h1>";
	res += "                                        </div>";
	res += "                                        <div class=\"text-center text-sm-right\">";
	res += "                                            <span class=\"badge badge-secondary\"> " + type + " </span>";
	res += "                                        </div>";
	res += "                                    </div>";
	res += "                                </div>";
	res += "                                <hr />";
	return res;
}

string bottomCode(string type = "") {
	string res = "";
	res += "                                </div>";
	res += "                            </div>";
	res += "                        </div>";
	res += "                    </div>";
	res += "                    <div class=\"col-12 col-md-3 mb-3\">";
	res += "                        <div class=\"card mb-3\">";
	res += "                            <div class=\"card-body\">";
	res += "                                <div class=\"px-xl-3\">";
	res += "                                    <a href=\"/logout\" class=\"btn btn-block btn-secondary\"> <i class=\"fa fa-sign-out\"></i> <span>Logout</span> </a>";
	res += "                                </div>";
	res += "                            </div>";
	res += "                        </div>";
	res += "						<div class=\"card p-3\">";
	res += "						    <div class=\"e-navlist e-navlist--active-bg\">";
	res += "						        <ul class=\"nav flex-column bg-white mb-0\">";
	res += "						            <li class=\"nav-item\"><a class=\"nav-link px-2 active\" href=\"/home\"><i class=\"fa fa-fw fa-home mr-1\"></i><span>Home</span></a></li>";

	//buyer
	if (type == "buyer") {
		res += "						            <li class=\"nav-item\"><a class=\"nav-link px-2\" href=\"/wallet\"><i class=\"fa fa-fw fa-cog mr-1\"></i><span>Wallet</span></a></li>";
		res += "						            <li class=\"nav-item\"><a class=\"nav-link px-2\" href=\"/cart\"><i class=\"fa fa-fw fa-th mr-1\"></i><span>Cart</span></a></li>";
	}

	//seller
	if (type == "seller")
		res += "						            <li class=\"nav-item\"><a class=\"nav-link px-2\" href=\"/addOffer\"><i class=\"fa fa-fw fa-th mr-1\"></i><span>Add Offer</span></a></li>";

	res += "						        </ul>";
	res += "						    </div>";
	res += "						</div>";
	res += "                    </div>";
	res += "                </div>";
	res += "            </div>";
	res += "        </div>";
	res += "    </div>";
	res += "</body>";
	res += "</html>";
	return res;
}

string HomePageHandler::makeHtml() {
	string ans = "";

	if (app->isSeller()) {
		string offers = app->myOffers();
		vector<vector<string> >data = App::parser(offers, '|');

		ans += topCode("Seller Home", "Seller User");

		ans += "<div class=\"row p-3\">";
		ans += "<table class=\"table table-bordered table-hover\">";
		for (uint i = 0; i < data.size(); i++)
		{
			ans += "<tr>";
			for (uint j = 0; j < data[i].size(); j++)
			{
				ans += "<td>" + data[i][j] + "</td>";
			}
			ans += "</tr>";
		}
		ans += "</table>";
		ans += "</div>";

		ans += "<div class=\"row\">";
		ans += "<div class=\"col d-flex justify-content-end\">";
		ans += "<a class=\"btn btn-primary mr-2\" href=\"/addOffer\">add Offer</a>";
		ans += "</div>";
		ans += "</div>";
		ans += bottomCode("seller");
	}
	else {
		string products = app->getProducts();
		vector<vector<string> >data = App::parser(products, '|');

		ans += topCode("Buyer Home", "Buyer User");

		ans += "<div class=\"row p-3\">";
		ans += "<table class=\"table table-bordered table-hover\">";
		for (uint i = 1; i < data.size(); i++)
		{
			ans += "<tr><td><a href=\"/product?id=" + data[i][0] + "\">";
			ans += data[i][0];
			ans += " - ";
			ans += data[i][1];
			ans += "</a></tr></td>";
		}
		ans += "</table>";
		ans += "</div>";


		ans += "<div class=\"row\">";
		ans += "<div class=\"col d-flex justify-content-end\">";
		ans += "<a class=\"btn btn-primary mr-2\" href=\"/wallet\">Wallet</a>";
		ans += "<a class=\"btn btn-primary\" href=\"/cart\">Cart</a>";
		ans += "</div>";
		ans += "</div>";
		ans += bottomCode("buyer");
	}

	return ans;
}

Response* UploadHandler::callback(Request* req) {
	string type = req->getBodyParam("type");
	string file = req->getBodyParam("file");
	string sessionId = req->getSessionId();
	try {
		app->login(sessionId);
		app->importProduct(type, file);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/home");
	return res;
}

Response* ShowAddOfferPage::callback(Request* req) {
	try {
		app->login(req->getSessionId());
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	Response* res = new Response();
	res->setHeader("Content-Type", "text/html");
	res->setBody(makeHtml());
	return res;
}

string ShowAddOfferPage::makeHtml() {
	string data = app->getProducts();
	vector<vector<string>> products = App::parser(data, '|');

	string ans = topCode("Add Offer", "Seller User");

	ans += "<form class=\"form p-3\" action=\"/addOffer\" method=\"post\">";
	ans += "    <div class=\"row\">";
	ans += "        <div class=\"col-12 col-sm-12 mb-3\">";
	ans += "            <div class=\"row\">";
	ans += "                <div class=\"col\">";
	ans += "                    <div class=\"form-group\">";
	ans += "                        <label>Product Id</label>";
	ans += "                        <input class=\"form-control\" name=\"productId\" type=\"text\" placeholder=\"Enter Product Id\" required />";
	ans += "                    </div>";
	ans += "                </div>";
	ans += "            </div>";
	ans += "            <div class=\"row\">";
	ans += "                <div class=\"col\">";
	ans += "                    <div class=\"form-group\">";
	ans += "                        <label>Unit Price</label>";
	ans += "                        <input name=\"price\" class=\"form-control\" type=\"text\" placeholder=\"Enter Unit Price\" required />";
	ans += "                    </div>";
	ans += "                </div>";
	ans += "            </div>";
	ans += "            <div class=\"row\">";
	ans += "                <div class=\"col\">";
	ans += "                    <div class=\"form-group\">";
	ans += "                        <label>Amount</label>";
	ans += "                        <input name=\"amount\" class=\"form-control\" type=\"text\" placeholder=\"Enter Amount\" required />";
	ans += "                    </div>";
	ans += "                </div>";
	ans += "            </div>";
	ans += "        </div>";
	ans += "    </div>";
	ans += "    <div class=\"row\">";
	ans += "        <div class=\"col d-flex justify-content-end\">";
	ans += "            <button class=\"btn btn-primary\" type=\"submit\">  Add  </button>";
	ans += "        </div>";
	ans += "    </div>";
	ans += "</form>";


	ans += "<br/><div class=\"row p-3\">";
	ans += "<table class=\"table table-bordered table-hover\">";
	for (uint i = 0; i < products.size(); i++)
	{
		ans += "<tr>";
		ans += "<td>" + products[i][0] + "</td>";
		ans += "<td>" + products[i][1] + "</td>";
		ans += "</tr>";
	}
	ans += "</table>";
	ans += "</div>";

	ans += bottomCode("seller");
	return ans;
}

Response* AddOfferHandler::callback(Request* req) {
	string productId = req->getBodyParam("productId");
	string price = req->getBodyParam("price");
	string amount = req->getBodyParam("amount");
	try {
		app->login(req->getSessionId());
		app->offer(productId, price, amount);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/home");
	return res;
}

Response* WalletHandler::callback(Request* req) {
	try {
		app->login(req->getSessionId());
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	Response* res = new Response();
	res->setHeader("Content-Type", "text/html");
	res->setBody(makeHtml());
	return res;
}

string WalletHandler::makeHtml() {
	string wallet;
	try {
		wallet = app->wallet("85");
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	vector<vector<string>> record = App::parser(wallet, '/');
	string ans = topCode("Wallet Page", "All User");

	ans += "<div class=\"alert alert-primary\">Credit : " + record[1][0] + "</div>";

	ans += "<form class=\"form p-3\" action=\"/charge\" method=\"post\">";
	ans += "    <div class=\"row\">";
	ans += "        <div class=\"col-12 col-sm-12 mb-3\">";
	ans += "            <div class=\"row\">";
	ans += "                <div class=\"col\">";
	ans += "                    <div class=\"form-group\">";
	ans += "                        <label>Amount</label>";
	ans += "                        <input class=\"form-control\" name=\"charge\" type=\"text\" placeholder=\"Enter Amount\" required />";
	ans += "                    </div>";
	ans += "                </div>";
	ans += "            </div>";
	ans += "        </div>";
	ans += "    </div>";
	ans += "    <div class=\"row\">";
	ans += "        <div class=\"col d-flex justify-content-end\">";
	ans += "            <button class=\"btn btn-primary\" type=\"submit\"> Add </button>";
	ans += "        </div>";
	ans += "    </div>";
	ans += "</form>";

	ans += bottomCode("buyer");
	return ans;
}

Response* ChargeHandler::callback(Request* req) {
	try {
		app->login(req->getSessionId());
		string charge = req->getBodyParam("charge");
		string wallet = app->chargeWallet(charge);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/wallet");
	return res;
}

Response* ProductDetailHandler::callback(Request* req) {
	string productId;
	string recordProduct;
	string recordOffers;
	try {
		app->login(req->getSessionId());
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	Response* res = new Response();
	res->setHeader("Content-Type", "text/html");
	res->setBody(makeHtml(req));
	return res;
}

string ProductDetailHandler::makeHtml(Request* req) {
	string productId;
	string recordProduct;
	string recordOffers;
	string recordComments;
	try {
		productId = req->getQueryParam("id");
		recordProduct = app->productDetail(productId);
		recordOffers = app->offersOnProduct(productId);
		recordComments = app->getComments(productId);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	string ans = topCode("Product Page", "Buyer User");

	ans += "<div class=\"alert alert-primary\">" + recordProduct + "</div>";

	vector<vector<string>> record = App::parser(recordOffers, '|');
	for (uint i = 0; i < record.size(); i++)
	{
		ans += "<div class=\"row p-3\">";
		ans += "<table class=\"table table-bordered table-hover\"><tr>";
		for (uint j = 2; j < record[i].size(); j++) {
			ans += "<td>" + record[i][j] + "</td>";
		}
		ans += "</tr></table>";
		ans += "</div>";
		if(i > 0) {
			ans += "<div>";
			ans += "<form action=\"/addToCart\" method=\"post\">";
			ans += "<input name=\"id\" type=\"hidden\" value=\"" + record[i][2] + "\"/>";
			ans += "<div class=\"input-group mb-3\">";
			ans += "<input name=\"amount\" type=\"number\" min=\"0\" placeholder=\"Amount\" class=\"form-control\" required/>";
			ans += "<button type=\"submit\" class=\"btn btn-primary\">Add</button>";
			ans += "</div>";
			ans += "</form>";
			ans += "</div>";
		}
	}

	ans += "</br>";

	vector<vector<string>> comments = App::parser(recordComments, '|');
	for (uint i = 0; i < comments.size(); i++)
	{
		ans += "<div class=\"alert alert-secondary\">";
		for (uint j = 0; j < comments[i].size(); j++) {
			ans += comments[i][j];
			ans += " -- ";
		}
		ans += "</div>";
	}

	ans += "<form id=\"comment\" action=\"/comment\" method=\"post\">";
	ans += "<input name=\"id\" type=\"hidden\" value=\"" + productId + "\"/>";
	ans += "<button type=\"submit\" class=\"btn btn-success\"> Send </button>";
	ans += "</form></br>";

	ans += "<textarea name=\"comment\" form=\"comment\" class=\"form-control\" >";
	ans += "Comment ...";
	ans += "</textarea>";


	ans += bottomCode("buyer");
	return ans;
}

Response* CommentHandler::callback(Request* req) {
	string productId;
	string comment;
	try {
		app->login(req->getSessionId());
		productId = req->getBodyParam("id");
		comment = req->getBodyParam("comment");
		app->makeComment(productId, comment);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/product?id=" + productId);
	return res;
}

Response* AddToCartHandler::callback(Request* req) {
	string offerId;
	string amount;
	try {
		app->login(req->getSessionId());
		offerId = req->getBodyParam("id");
		amount = req->getBodyParam("amount");
		app->addToCart(offerId, amount);
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/home");
	return res;
}


Response* CartHandler::callback(Request* req) {
	try {
		app->login(req->getSessionId());
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}

	Response* res = new Response();
	res->setHeader("Content-Type", "text/html");
	res->setBody(makeHtml());
	return res;
}

string CartHandler::makeHtml() {
	string data;
	vector<vector<string>> cart;
	try {
		data = app->showCart();
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	cart = App::parser(data, '|');
	string ans = topCode("Cart", "Buyer User");

	ans += "<div class=\"row p-3\">";
	ans += "<table class=\"table table-bordered table-hover\">";
	for (uint i = 0; i < cart.size(); i++)
	{
		ans += "<tr>";
		for (uint j = 0; j < cart[i].size(); j++)
		{
			ans += "<td>" + cart[i][j] + "</td>";
		}
		ans += "</tr>";
	}
	ans += "</table>";
	ans += "</div>";

	ans += "<div class=\"row\">";
	ans += "<div class=\"col d-flex justify-content-end\">";
	ans += "<a class=\"btn btn-primary mr-2\" href=\"/buy\"> BUY </a>";
	ans += "</div>";
	ans += "</div>";

	ans += bottomCode("buyer");
	return ans;
}

Response* BuyHandler::callback(Request* req) {
	try {
		app->login(req->getSessionId());
		app->submitCart();
	}
	catch (Exception & exc) {
		throw Server::Exception(exc.what());
	}
	Response* res = Response::redirect("/home");
	return res;
}