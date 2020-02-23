#ifndef __DATA__
#define __DATA__
#include<string>
#include<vector>


class Data {

    public:
    Data(std::string _name, double _weightGood, double _weightBad) {name = _name; weightGood = _weightGood; _weightBad = weightBad;};
    double getGoodWeight();
    double getBadWeight();

    private:
    std::string name;
    double weightGood;
    double weightBad;
    

};


#endif