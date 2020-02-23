#ifndef __PRODUCT__
#define __PRODUCT__
#include <string>
#include <vector>
#define CAR_TYPE "car"
#define MOBILE_TYPR "mobile"
#define TV_TYPE "tv"

class Product {
    public:
    Product(std::string _name, int _productId) { name = _name; productId = _productId;};
    std::string getName();
    int getId();
    virtual std::string printProductDetails() = 0;
    std::string getComments();
    void setComment(std::string userName, std::string comment);
    virtual std::vector<std::string> getProductDetails() = 0;
    std::string getType();

    protected:
    std::string name;
    int productId;
    std::vector<std::pair<std::string, std::string>> comments;
    std::string type;
    
};


class Car : public Product {
    public:
    Car(std::string _name, std::string _weight, std::string _numOfSeats, std::string _numOfCyl, std::string _engineCapa, std::string _parkingSensor, int _productId);
    virtual std::string printProductDetails();
    virtual std::vector<std::string> getProductDetails();
    private:
    std::string weight;
    std::string numOfSeats;
    std::string numOfCyl;
    std::string engineCapa;
    std::string parkingSensor;
};


class Mobile : public Product {
    public:
    Mobile(std::string _name, std::string _weight, std::string _cpuFre, std::string _memory, std::string _ram, std::string _displaySize, std::string _cameraRes, std::string _operatingSys, int _productId);
    virtual std::string printProductDetails();
    virtual std::vector<std::string> getProductDetails();
    private:
    std::string weight;
    std::string cpuFre;
    std::string memory;
    std::string ram;
    std::string displaySize;
    std::string cameraRes;
    std::string operatingSys;
};


class Tv : public Product {
    public:
    Tv(std::string name, std::string _screenSize, std::string _screenType, std::string _resolution, std::string _threeD, std::string _HDR, int _productId);
    virtual std::string printProductDetails();
    virtual std::vector<std::string> getProductDetails();
    private:
    std::string screnSize;
    std::string screenType;
    std::string resolution;
    std::string threeD;
    std::string HDR;

};
    

#endif