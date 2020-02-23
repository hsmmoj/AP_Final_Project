#include "model.hpp"
#include <limits>
#define TRAIN_CSV_FILE_NAME "train.csv"
#define GOOD_COMMENT_PRIOR_FILE_NAME "class probabilities"
#define FULL_PRABOLITY 1
#define GOOD_COMMENT_LABEL "0"
#define BAD_COMMENT_LABEL "1"

using namespace std;

Model::Model() {
    readCsv(TRAIN_CSV_FILE_NAME);
    readGoodCommentPrior(GOOD_COMMENT_PRIOR_FILE_NAME);

}

void Model::readGoodCommentPrior(string filePath) {
    ifstream file;
    file.open(filePath);
    if(!file.is_open()) {
        cerr<< "File Not Found"<< endl;
        return;
    }
    string prior;
    file >> prior;
    goodCommentPrior = stod(prior);
}


void Model::readCsv(string filePath) {
    string row;
    std::ifstream myFile(filePath);
    if (myFile.is_open())
    {
        getline(myFile, row);
        while(getline(myFile,row))
        {   
            vector<string> splittedRow = spliter(row);
            Data* newData = new Data(splittedRow[0], stod(splittedRow[1]), stod(splittedRow[2]));
            weightsMap.insert({splittedRow[0], newData});
        }
    }
    else
        cerr << "File Not Found"<< endl;
       
}


vector<string> Model::spliter(string & input) {
    vector<string> tokens;
    stringstream check(input);
    string intermadiate;
    while(getline(check,intermadiate,','))
        tokens.push_back(intermadiate);
    return tokens;  
}


vector<string> Model::spaceSpliter(string & input) {
    vector<string> tokens;
    stringstream check(input);
    string intermadiate;
    while(getline(check,intermadiate,' '))
        tokens.push_back(intermadiate);
    return tokens;  
}


bool Model::predict(string inputData) {
    bool ans = false;
    vector<string> splittedSentence = spaceSpliter(inputData);
    string label = classifier(splittedSentence);
    if(label ==  BAD_COMMENT_LABEL)
        ans = true;
    return ans;
}


string Model::classifier(vector<string> splittedSentence) {
    double goodScore = 0;
    double badScore = 0;
    for(unsigned int i = 0; i < splittedSentence.size(); i++) {
        if(weightsMap.find(splittedSentence[i]) == weightsMap.end())
            continue;
        else {
            double eps = numeric_limits<double>::min();
            goodScore = goodScore + log(weightsMap.at(splittedSentence[i])->getGoodWeight() + eps);
            if(weightsMap.at(splittedSentence[i])->getBadWeight() > 0)
            badScore = badScore  + log(weightsMap.at(splittedSentence[i])->getBadWeight() + eps);
        }
    }
    goodScore += log(goodCommentPrior);
    badScore += log(FULL_PRABOLITY - goodCommentPrior);
    if(goodScore > badScore)
        return GOOD_COMMENT_LABEL;
    else
        return BAD_COMMENT_LABEL;    
}