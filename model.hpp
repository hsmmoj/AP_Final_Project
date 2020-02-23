#ifndef __MODEL__
#define __MODEL__
#include <unordered_map> 
#include<string>
#include<vector>
#include<cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "data.hpp"

#define BAD_COMMENT_LABEL "1"

class Model {
    public:
    Model();
    void readCsv(std::string filePath);
    bool predict(std::string inputData);

    private:
    std::unordered_map<std::string,Data*> weightsMap;
    std::vector<std::string> spliter(std::string & input);
    std::vector<std::string> spaceSpliter(std::string & input);
    std::string classifier(std::vector<std::string> splittedSentence);
    void readGoodCommentPrior(std::string filePath);
    double goodCommentPrior;


};

#endif