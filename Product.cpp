#include "Product.hpp"
using namespace std;

Car::Car(string _name, string _weight, string _numOfSeats, string _numOfCyl, string _engineCapa, string _parkingSensor, int _productId) : Product(_name, _productId) {
    weight = _weight;
    numOfSeats = _numOfSeats;
    numOfCyl = _numOfCyl;
    engineCapa = _engineCapa;
    parkingSensor = _parkingSensor;
    type = CAR_TYPE;

}


Mobile::Mobile(string _name, string _weight, string _cpuFre, string _memory, string _ram, string _displaySize, string _cameraRes, std::string _operatingSys, int _productId) : Product(_name, _productId) {
    weight = _weight;
    cpuFre = _cpuFre;
    memory = _memory;
    ram = _ram;
    displaySize = _displaySize;
    cameraRes = _cameraRes;
    operatingSys = _operatingSys;
    type = MOBILE_TYPR;
}


Tv::Tv(string _name, string _screenSize, string _screenType, string _resolution, string _threeD, string _HDR, int _productId) : Product(_name, _productId) {
    screnSize = _screenSize;
    screenType = _screenType;
    resolution = _resolution;
    threeD = _threeD;
    HDR = _HDR;
    type = TV_TYPE;

}


string Product::getName() {
    return name;
}


int Product::getId() {
    return productId;
}


string Car::printProductDetails() {
    string ans = "";
    ans += name;
    ans += "\n";
    ans += "Weight: " + weight + '\n';
    ans += "Num. of Seats: " + numOfSeats + '\n';
    ans += "Num. of Cylinders: " + numOfCyl + "\n";
    ans += "Engine Capacity: " + engineCapa + "\n";
    ans += "Reverse Parking Sensors: " +  parkingSensor + "\n";
    return ans;
}


string Mobile::printProductDetails() {
    string ans  = "";
    ans += name + "\n";
    ans += "Weight: " + weight + "\n";
    ans += "CPU Frequency: " + cpuFre + "\n";
    ans += "Built-in Memory: " + memory + "\n";
    ans += "RAM: " + ram + "\n";
    ans += "Display Size: " + displaySize + "\n";
    ans += "Camera Resolution: " + cameraRes + "\n";
    ans += "Operating System: " + operatingSys + "\n";
    return ans;
}


string Tv::printProductDetails() {
    string ans = "";
    ans += name + "\n";
    ans += "Screen Size: " + screnSize + "\n";
    ans += "Screen Type: " + screenType  + "\n";
    ans += "Resolution: " + resolution + "\n";
    ans += "3D: " + threeD + "\n";
    ans += "HDR: " + HDR + "\n";
    return ans;
}






void Product::setComment(string userName, string comment) {
    pair<string, string> newComment (userName, comment);
    comments.push_back(newComment);
}


string Product::getComments() {
    string ans = name + "\n";
    for(unsigned int i = comments.size(); i > 0; i--) {
        ans += comments[i-1].first;
        ans += " | ";
        ans += comments[i-1].second;
        ans += "\n";
    }
    return ans;
}


string Product::getType() {
    return type;
}


vector<string> Car::getProductDetails() {
    vector<string> ans = {name, weight, numOfSeats, numOfSeats, engineCapa, parkingSensor};
    return ans;
}


vector<string> Mobile::getProductDetails() {
    vector<string> ans = {name, weight, cpuFre, memory, ram, displaySize, cameraRes, operatingSys};
    return ans;
}



vector<string> Tv::getProductDetails() {
    vector<string> ans = {name, screnSize, screenType, resolution, threeD, HDR};
    return ans;
}



