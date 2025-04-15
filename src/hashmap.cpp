//
// Created by diego on 4/14/2025.
//
// Modified by Jesse on 4/15/2025
//
#include "hashmap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>


unsigned long long int HashFunction_one(const std::string& word) {
    unsigned long long int value = 0;
    for (size_t i = 0; i < word.size(); i++) {
        value = value * 131 + static_cast<int>(word[i]);
    }
    return value % SIZE_OF_HASH_MAP;
}

// ProcessTweet_one: Processes a tweet and splits it into words, inserting
// each word (with the tweet's score) into the provided separate chaining map.
void ProcessTweet_one(const std::string& tweet_, HM_separateChaining& a_map, const int score) {
    std::string word;
    std::istringstream message_string(tweet_);
    while (getline(message_string, word, ' ')) {
        unsigned long long int hash_code = HashFunction_one(word);
        a_map.insert(hash_code, word, score);
    }
}

// ParseDataFile: Opens a file, reads each line, extracts the tweet and its score,
// and processes the tweet using ProcessTweet_one.
void ParseDataFile(const std::string& fileName, HM_separateChaining& a_map) {
    std::ifstream dataFile(fileName);
    std::string line;

    std::string temp;
    std::string score;
    std::string id;
    std::string date;
    std::string flag;
    std::string user;
    std::string tweet;

    if (dataFile.is_open()) {
        std::cout << "Data file open!" << std::endl;
    } else {
        std::cout << "Data file FAILED to open!" << std::endl;
    }
    int counter = 0;
    while (std::getline(dataFile, line) && counter != 100000) {
        std::istringstream token(line);
        getline(token, temp, '"');
        getline(token, score, '"');
        getline(token, temp, '"');
        getline(token, id, '"');
        getline(token, temp, '"');
        getline(token, date, '"');
        getline(token, temp, '"');
        getline(token, flag, '"');
        getline(token, temp, '"');
        getline(token, user, '"');
        getline(token, temp, '"');
        getline(token, tweet, '"');
        ++counter;
        ProcessTweet_one(tweet, a_map, std::stoi(score));
    }
}
