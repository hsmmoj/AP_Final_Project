#include "App.hpp"
using namespace std;

#define BAD_REQUEST_RESPONSE "Bad Request\n"
#define SUCCESS "OK\n"
#define BUYER_MODIFIER "buyer"
#define SELLER_MODIFIER "seller"
#define MOBILE_REP "mobile"
#define TV_REP "tv"
#define CAR_REP "car"
#define GET_PRODUCT_NOMINATOR "productId | productName\n"
#define GET_OFFERS_NOMINATOR "productId | offerId | offerUnitPrice | offerAmount\n"
#define ASCEND_MODIFIER "ASCEND"
#define DESCEND_MODIFIER "DESCEND"
#define OFFER_ID_MODIFIER "offerId"
#define OFFER_PRICE_MODIFIER "offerPrice"
#define RANDOM_STRING_LENGTH 8
#define CHARACTERS_TO_MAKE_RANDOM_STRING "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_?!@&"
#define OFFER_ON_PRODUCT_NOMINATOR "productId | productName | offerId | offerUnitPrice | offerAmount\n"
#define ZERO_PERCENT 0
#define CODE_NOT_FOUND -1
#define CART_INFO_NOMINATOR "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount\n"


App::App() {
    Manager* manager = new Manager();
    loggedPerson = manager;
    people.push_back(manager);
    currentPersonId  = 1;
    currentProductId = 1;
    currentOfferId = 1;
    model = new Model();
}

size_t App::hashing(string password) {
    hash<string> hasher;
    return hasher(password);
}

Person* App::findPersonByUsername(string username) {
    for(unsigned int i = 0; i<people.size(); i++)
        if(people[i]->getUsername() == username)
            return people[i];
    
    return NULL;
}


Person* App::findPersonByEmail(string email) {
       for(unsigned int i = 0; i<people.size(); i++)
        if(people[i]->getEmail() == email)
            return people[i];
    
    return NULL;
}

string App::signUp(string _email,string _username, size_t _password, string _type) {
    SignUpCheck* check = new SignUpCheck(this, _username);
    bool findUser = check->check();

    if(findUser)
        throw SignUpException();
    
    else if(_type == SELLER_MODIFIER){
        Seller* seller = new Seller(_email, _username, _password, currentPersonId);
        loggedPerson = seller;
        people.push_back(seller);
        currentPersonId = currentPersonId + 1 ;
        return SUCCESS;
    }

    else if(_type == BUYER_MODIFIER){
        Buyer* buyer = new Buyer(_email, _username, _password, currentPersonId);
        loggedPerson = buyer;
        people.push_back(buyer);
        currentPersonId = currentPersonId + 1 ;
        return SUCCESS;
    }
}

string App::login(string email, size_t password) {

    LoginCheck* check = new LoginCheck(this, email, password);
    bool failure = check->check();
    if(failure)
        throw LoginException();

    Person* userTologin = findPersonByEmail(email);
    loggedPerson = userTologin;

    string sessionId = randomStringGenerator(SESSION_ID_LENGTH)[0];
    sessionIds[loggedPerson] = sessionId;
    return sessionId;
}

Person* App::findPersonBySessionId(string sessionId) {
    Person* ans;
    map<Person*, string>::iterator it;
    for(it = sessionIds.begin(); it != sessionIds.end(); ++it) {
        if(it->second == sessionId)
            return it->first;
    }
    return NULL;
}

string App::login(std::string sessionId) {
    Person* userTologin = findPersonBySessionId(sessionId);
    if(userTologin == NULL)
        throw NotFoundException();
    
    loggedPerson = userTologin;
    return sessionId;
}


Person* App::getLoggedPerson() {
    return loggedPerson;
}

string App::logout(string sessionId) {
    Person* toLogout = findPersonBySessionId(sessionId);
    if(toLogout == NULL)
        throw LogoutException();
    sessionIds.erase(toLogout);
    return SUCCESS;
}


vector<string> App::readCsv(string filePath) {
    vector<string> output;
    string row;
    stringstream fileS(filePath);
    getline(fileS, row);
    while(getline(fileS, row)) {
        output.push_back(row);
    }
    return output;
}


vector<string> App::spliter(string & input) {
    vector<string> tokens;
    stringstream check(input);
    string intermadiate;
    while(getline(check,intermadiate,','))
        tokens.push_back(intermadiate);
    return tokens;  
}


vector<vector<string>> App::process_info(string filePath) {
    vector<string> infoFromCsv = readCsv(filePath);
    vector<vector<string>> result;
    for(unsigned int i = 0; i < infoFromCsv.size(); i++)
    {
        vector<string> splited_info = spliter(infoFromCsv[i]);
        result.push_back(splited_info);
    }
    return result;
}


void App::mobileInfoFiller(vector<vector<string>> info) {
    for(unsigned int i = 0; i < info.size(); i++) {
        Product* newProduct = new Mobile(info[i][0], info[i][1], info[i][2], info[i][3], info[i][4], info[i][5], info[i][6], info[i][7], currentProductId);
        products.push_back(newProduct);
        currentProductId = currentProductId + 1;
    }
}


void App::tvInfoFiller(vector<vector<string>> info) {
    for(unsigned int i = 0; i < info.size(); i++) {
        Product* newProduct = new Tv(info[i][0], info[i][1], info[i][2], info[i][3], info[i][4], info[i][5], currentProductId);
        products.push_back(newProduct);
        currentProductId = currentProductId + 1;
    }
}


void App::carInfoFiller(vector<vector<string>> info) {
    for(unsigned int i = 0; i < info.size(); i++) {
        Product* newProduct = new Car(info[i][0], info[i][1], info[i][2], info[i][3], info[i][4], info[i][5], currentProductId);
        products.push_back(newProduct);
        currentProductId = currentProductId + 1;
    }
}


string App::importProduct(string type, string filePath) {
    addProductPermissionCheck* check = new addProductPermissionCheck(this);
    bool failure = check->check();
    if(failure)
        throw importProductException();
    cout<< "file "<< filePath<< endl;
    vector<vector<string>> info = process_info(filePath);
    for(int i=0; i<info.size(); i++) {
        for(int j=0; j<info[i].size(); j++)
            cout<< info[i][j]<< " ";
        cout<< endl;
    }
    cout<<"type"<< type<< endl;
    cout<< endl;
    if(type == MOBILE_REP)
        mobileInfoFiller(info);
    if(type == TV_REP)
        tvInfoFiller(info);
    if(type == CAR_REP)
        carInfoFiller(info);
    return SUCCESS;   
}


string App::printProducts() {
    string output = GET_PRODUCT_NOMINATOR ;
    for(unsigned int i = 0; i < products.size(); i++) {
        output = output  + to_string(products[i]->getId()) + " | " +  products[i]->getName() + "\n";
    }
    return output;
}


string App::getProducts() {
    getProductPermissionCheck* check = new getProductPermissionCheck(this);         
    bool failure = check->check();
    if(failure)
        throw illigalAccessException();
    string output = printProducts();
    return output;
    
}

Product* App::findProductById(int id) {
    for(unsigned int i = 0; i < products.size(); i++) {
        if(products[i]->getId() == id)
            return products[i];
    }
    return NULL;
}


string App::offer(string productId, string price, string amount) {
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(seller == NULL)
        throw illigalAccessException();
    check = new addOfferCheck(this, stoi(productId));
    bool failure = check->check();
    if(failure)
        throw BadRequestException();
    Product* product = findProductById(stoi(productId));
    Offer* newOffer = new Offer(currentOfferId, stod(price), product, stoi(amount), seller->getId());
    currentOfferId = currentOfferId + 1;
    seller->addOffer(newOffer);
    offers.push_back(newOffer);
    return SUCCESS;
}

string App::handleOffers(string order, string field) {
    managerAccessCheck* check = new managerAccessCheck(this);
    bool failure = check->check();
    if(failure)
        throw illigalAccessException();
    string record = GET_OFFERS_NOMINATOR;
    sortOffers(order, field);
    for(int i=0; i<offers.size(); i++)
        record += offers[i]->getInfoForManager();
    return record;  
}


void App::sortOffers(string order, string field) {
    if(field == OFFER_ID_MODIFIER) {
        sortOffersByID(order);
    }
    else if(field == OFFER_PRICE_MODIFIER) {
        sortOffersByPrice(order);
    }
}

void App::sortOffersByID(string order) {
    if(order == ASCEND_MODIFIER)
        sort(offers.begin(), offers.end(), App::ascendCompareOfferByID);
    else if(order == DESCEND_MODIFIER)
        sort(offers.begin(), offers.end(), App::descendCompareOfferByID);
}

void App::sortOffersByPrice(string order) {
    if(order == ASCEND_MODIFIER)
        sort(offers.begin(), offers.end(), App::ascendCompareOfferByPrice);
    else if(order == DESCEND_MODIFIER)
        sort(offers.begin(), offers.end(), App::descendCompareOfferByPrice);
}

bool App::ascendCompareOfferByID(Offer* one, Offer* two) {
    return one->getId() < two->getId();
}

bool App::descendCompareOfferByID(Offer* one, Offer* two) {
    return one->getId() > two->getId();
}

bool App::ascendCompareOfferByPrice(Offer* one, Offer* two) {
    if(one->getPrice() != two->getPrice())
        return one->getPrice() < two->getPrice();
    return one->getId() < two->getId();
}

bool App::descendCompareOfferByPrice(Offer* one, Offer* two) {
    if(one->getPrice() != two->getPrice())
        return one->getPrice() > two->getPrice();
    return one->getId() > two->getId();
}


string App::myOffers() {
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(seller == NULL)
        throw illigalAccessException();
    string record = GET_OFFERS_NOMINATOR;
    vector<Offer*> sellerOffers = seller->getSellerOffers();
    for(int i=0; i<sellerOffers.size(); i++)
        record += sellerOffers[i]->getInfoForManager();
    return record;  
}


string App::changeOffer(string offerId, string price, string amount) {
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(seller == NULL)
        throw illigalAccessException();
    Offer* foundOffer = seller->findOfferByOfferId(stoi(offerId));
    if(foundOffer == NULL)
        throw BadRequestException();
    foundOffer->changeAmount(stoi(amount));
    foundOffer->changePrice(stod(price));
    return SUCCESS;
}



vector<string> App::randomStringGenerator(int count) {
    const std::string characters = CHARACTERS_TO_MAKE_RANDOM_STRING;
    const int length = RANDOM_STRING_LENGTH;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);
    std::vector<std::string> ans = {};
    for(unsigned int i = 0; i < count; i++) {
    std::string random_string = "";
        for (std::size_t i = 0; i < length; ++i)
        {
            random_string += characters[distribution(generator)];
        }
        ans.push_back(random_string);
    }
    return ans;
}


string App::generateDiscountCode(string offerId, string discountPercent, string discountNumber) {
    Seller* seller = dynamic_cast<Seller*>(loggedPerson);
    if(seller == NULL)
        throw illigalAccessException();
    Offer* foundOffer = seller->findOfferByOfferId(stoi(offerId));
    if(foundOffer == NULL)
        throw BadRequestException();
    vector<string> discountcodes = randomStringGenerator(stoi(discountNumber));
    for(unsigned int i = 0; i < discountcodes.size(); i++) {
        foundOffer->addDiscountCode(discountcodes[i], stod(discountPercent));
    }
    string ans = printDiscountCodes(discountcodes);
    return ans;
    
}


string App::printDiscountCodes(vector<string> codes) {
    string ans = "";
    for(unsigned int i; i < codes.size(); i++) {
        ans = ans + codes[i] + "\n";
    }

    return ans;
}



string App::offersOnProduct(string productId) {
    buyerAccessCheck* check = new buyerAccessCheck(this);
    int failure = check->check();
    if(failure)
        throw illigalAccessException();
    vector<Offer*> productOffers;
    for(unsigned int i = 0; i < offers.size(); i++) {
        Product* product = offers[i]->getProduct();
        if(product->getId() == stoi(productId))
            productOffers.push_back(offers[i]);
    }
    if(productOffers.size() == 0)
        throw NotFoundException();
    string ans = printOffersOnProduct(productOffers);
    return ans;
}


string App::printOffersOnProduct(vector<Offer*> productOffers) {
    string ans = OFFER_ON_PRODUCT_NOMINATOR;
    for(unsigned int i = productOffers.size(); i > 0; i--) {
        ans += productOffers[i-1]->getOfferInfo();
    }
    return ans;
}


string App::productDetail(string productId) {
    string ans = "";
    buyerAccessCheck* check = new buyerAccessCheck(this);
    int failure = check->check();
    if(failure)
        throw illigalAccessException();
    Product* foundProduct = findProductById(stoi(productId));
    if(foundProduct == NULL)
        throw NotFoundException();
    ans = foundProduct->printProductDetails();
    return ans;
}


string App::getComments(string productId) {
    buyerAccessCheck* check = new buyerAccessCheck(this);
    int failure = check->check();
    if(failure)
        throw illigalAccessException();
    Product* foundProduct = findProductById(stoi(productId));
    if(foundProduct == NULL)
        throw NotFoundException();
    string ans = foundProduct->getComments();
    return ans;
}


Offer* App::findOfferById(int id) {
    for(unsigned int i = 0; i < offers.size(); i++) {
        if(offers[i]->getId() == id)
            return offers[i];
        
    }
    return NULL;
}


string App::addToCart(string OfferId, string requiredAmount, string discountCode) {
    Buyer* buyer = dynamic_cast<Buyer*>(loggedPerson);
    if(buyer == NULL)
        throw illigalAccessException();
    Offer* foundOffer = findOfferById(stoi(OfferId));
    if(foundOffer == NULL)
        throw NotFoundException();
    int offerAmount = foundOffer->getAmount();
    if(stoi(requiredAmount) > offerAmount)
        throw BadRequestException();
    if(discountCode == "") 
        buyer->addGoodsToCart(foundOffer, stoi(requiredAmount), ZERO_PERCENT);
    else {
        double discountPercent = foundOffer->useDiscountCode(discountCode);
        buyer->addGoodsToCart(foundOffer, stoi(requiredAmount), discountPercent);
    }
    int newAmount = offerAmount - stoi(requiredAmount);
    foundOffer->changeAmount(newAmount);
    return SUCCESS;   
}


string App::showCart() {
    
    Buyer* buyer = dynamic_cast<Buyer*>(loggedPerson);
    if(buyer == NULL)
        throw illigalAccessException();
    Cart* cart = buyer->getCart();
    string ans = CART_INFO_NOMINATOR;
    ans += cart->getCartInfo();
    return ans;
}


string App::submitCart() {
    Buyer* buyer = dynamic_cast<Buyer*>(loggedPerson);
    if(buyer == NULL)
        throw illigalAccessException();
    double totalPrice = buyer->getCart()->getTotoalPrice();
    if(totalPrice > buyer->getCredit())
        throw BadRequestException();
    Cart* cart = buyer->getCart();
    buyer->addTransaction(-totalPrice);
    payToSellers(cart);
    buyer->addOrder(cart);
    buyer->resetCart();
    return SUCCESS;
}


void App::payToSellers(Cart* cart) {

    vector<pair<int, double>> allPayInfos = cart->getPayInfo();
    vector<int> sellerIds = {};

    for(unsigned int i = 0; i < allPayInfos.size(); i++) 
        sellerIds.push_back(allPayInfos[i].first);
    for(unsigned int i = 0; i < sellerIds.size(); i++) {
        int moneyToPay = 0;
       for(unsigned int j = 0; j < allPayInfos.size(); j++) {
           if(allPayInfos[j].first == sellerIds[i])
            moneyToPay = moneyToPay + allPayInfos[j].second;
       }
        Seller* seller = findSellerById(sellerIds[i]);
        seller->addTransaction(moneyToPay);
    }
}


Seller* App::findSellerById(int id) {
    for(unsigned int i = 0; i<people.size(); i++)
        if(people[i]->getId() == id) {
            Seller* seller = dynamic_cast<Seller*>(people[i]);
            return seller;
        }
    return NULL;
}


string App::orders(string counts) {
    Buyer* buyer = dynamic_cast<Buyer*>(loggedPerson);
    if(buyer == NULL)
        throw illigalAccessException();
    string ans = buyer->getOrdersInfo(stoi(counts));
    return ans;    
}


string App::wallet(string count) {
    string type = loggedPerson->getType();
    if(type != BUYER_TYPE && type != SELLER_TYPE)
        throw illigalAccessException();
    string ans = loggedPerson->getTransactionInfo(stoi(count));
    return ans;
}


string App::chargeWallet(string amount) {
    string type = loggedPerson->getType();
    if(type != BUYER_TYPE)
        throw illigalAccessException();
    // double newCredit = loggedPerson->getCredit() + stod(amount);
    loggedPerson->addTransaction(stod(amount));
    return SUCCESS;
}



string App::makeComment(string productId, string comment) {
    Buyer* buyer = dynamic_cast<Buyer*>(loggedPerson);
    if(buyer == NULL)
        throw illigalAccessException();
    Product* product = findProductById(stoi(productId));
    if(product == NULL)
        throw NotFoundException();
    CheckCommentValidity* check = new CheckCommentValidity(this, model, comment);
    bool failure = check->check();
    cout<< "comment validity "<< failure<< endl;
    if(!failure)
        throw BadCommentException();

    string buyerUsername = buyer->getUsername();
    product->setComment(buyerUsername, comment);
    return SUCCESS;  
}


string App::compareTwoProducts(string productId1, string productId2) {
    string type = loggedPerson->getType();
    if(type != BUYER_TYPE)
        throw illigalAccessException();
    Product* product1 = findProductById(stoi(productId1));
    Product* product2 = findProductById(stoi(productId2));
    if(product1 == NULL || product2 == NULL)
        throw NotFoundException();
    string product1Type = product1->getType();
    string product2Type = product2->getType();
    if(product1Type != product2Type)
        throw BadRequestException();
    string ans = "";
    if(product1Type == CAR_TYPE)
        ans = printComparisonCar(product1, product2);
    if(product1Type == MOBILE_TYPR )
        ans = printComparisonMobile(product1, product2);
    if(product1Type == TV_TYPE)
        ans = printComparisonTV(product1, product2);
    return ans; 
}



string App::printComparisonCar(Product* product1, Product* product2) {
    vector<string> product1Details = product1->getProductDetails();
    vector<string> product2Details = product2->getProductDetails();
    string ans = product1Details[0] + SEPRATOR + product2Details[0] + NEXT_LINE;
    ans = ans + WEIGHT +  product1Details[1] + SEPRATOR + product2Details[1] + NEXT_LINE ;
    ans = ans + NUM_OF_SEATS + product1Details[2] + SEPRATOR + product2Details[2] + NEXT_LINE;
    ans = ans + NUM_OF_CYL + product1Details[3] + SEPRATOR + product2Details[3] + NEXT_LINE;
    ans = ans + ENGINE_CAPACITY + product1Details[4] + SEPRATOR + product2Details[4] + NEXT_LINE;
    ans = ans + PARKING_SENSOR + product1Details[5] + SEPRATOR + product2Details[5] + NEXT_LINE;
    return ans;
} 


string App:: printComparisonMobile(Product* product1, Product* product2) {
    vector<string> product1Details = product1->getProductDetails();
    vector<string> product2Details = product2->getProductDetails();
    string ans = product1Details[0] + SEPRATOR + product2Details[0] + NEXT_LINE;
    ans = ans + CPU_FRE + product1Details[1] + SEPRATOR + product2Details[1] + NEXT_LINE;
    ans = ans + MEMORY_IN + product1Details[2] + SEPRATOR + product2Details[2] + NEXT_LINE;
    ans = ans + RAM + product1Details[3] + SEPRATOR + product2Details[3] + NEXT_LINE;
    ans = ans + DISPLAY_SIZE + product1Details[4] + SEPRATOR + product2Details[4] + NEXT_LINE;
    ans = ans + CAMERA_RES + product1Details[5] + SEPRATOR + product2Details[5] + NEXT_LINE;
    ans = ans + OPERATING_SYS + product1Details[6] + SEPRATOR + product2Details[6] + NEXT_LINE;
    return ans;

}


string App:: printComparisonTV(Product* product1, Product* product2) {
    vector<string> product1Details = product1->getProductDetails();
    vector<string> product2Details = product2->getProductDetails();
    string ans = product1Details[0] + SEPRATOR + product2Details[0] + NEXT_LINE;
    ans = ans + SCREEN_SIZE + product1Details[1] + SEPRATOR + product2Details[1] + NEXT_LINE;
    ans = ans + SCREEN_TYPE + product2Details[2] + SEPRATOR + product2Details[2] + NEXT_LINE;
    ans = ans + RESOLOTION + product1Details[3] + SEPRATOR + product2Details[3] + NEXT_LINE;
    ans = ans + THREE_D + product1Details[4] + SEPRATOR + product2Details[4] + NEXT_LINE;
    ans = ans + HDR + product1Details[5] + SEPRATOR + product2Details[5] + NEXT_LINE;
    return ans;
}


string App::getOffers() {
    string type = loggedPerson->getType();
    if(type != BUYER_TYPE)
        throw illigalAccessException();
    
    sort(offers.begin(), offers.end(), App::ascendCompareOfferByID);

    string ans;
    ans = GET_OFFERS_HEADER;

    for(int i=0; i<offers.size(); i++) {
        ans += offers[i]->getInfoForBuyer();
    }
    return ans;
}


vector<vector<string> >App::parser(string record, char sign) {
    stringstream recordS(record);
    vector<vector<string> >ans;
    string line;
    string cell;
    while(getline(recordS, line)) {
        vector<string> tmpAns;
        stringstream lineS(line);
        while(getline(lineS, cell, sign)) {
            string tmp;
            int i = 0;
            while(i < cell.size()) {
                if(cell[i] != ' ')
                    break;
                i++;
            }
            for(i; i<cell.size(); i++) {
                tmp.push_back(cell[i]);
            }
            while(tmp.size() > 0 && tmp[tmp.size()-1] == ' ')
                tmp.pop_back();
            if(tmp.size() > 0)
                tmpAns.push_back(tmp);
        }
        ans.push_back(tmpAns);
    }
    return ans;
}