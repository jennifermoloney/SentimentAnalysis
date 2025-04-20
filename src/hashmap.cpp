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


unsigned long long int HashFunction_one(const std::string& word, const int curr_size_map_) {
    unsigned long long int value = 0;
    for (size_t i = 0; i < word.size(); i++) {
        value = value * 131 + static_cast<int>(word[i]);
    }
    return value % curr_size_map_;
}

// ProcessTweet_one: Processes a tweet and splits it into words, inserting
// each word (with the tweet's score) into the provided map (SC or LP).
void ProcessTweet_oneSC(const std::string& tweet_, HM_separateChaining& a_map, const int score) {
    std::string word;
    std::istringstream message_string(tweet_);
    while (getline(message_string, word, ' ')) {
        unsigned long long int hash_code = HashFunction_one(word, a_map.curr_size_of_hash_map);
        a_map.insert(hash_code, word, score);
    }
}
void ProcessTweet_oneLP(const std::string& tweet_, HM_linearProbing& a_map, const int score) {
    std::string word;
    std::istringstream message_string(tweet_);
    while (getline(message_string, word, ' ')) {
        unsigned long long int hash_code = HashFunction_one(word, a_map.curr_size_of_hash_map);
        a_map.insert(hash_code, word, score);
    }
}

// ParseDataFile: Opens a file, reads each line, extracts the tweet and its score,
// and processes the tweet using ProcessTweet_one.
void ParseDataFileSC(const std::string& fileName, HM_separateChaining& a_map) {
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
        ProcessTweet_oneSC(tweet, a_map, std::stoi(score));
    }
}

void ParseDataFileLP(const std::string& fileName, HM_linearProbing& a_map) {
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
        ProcessTweet_oneLP(tweet, a_map, std::stoi(score));
    }
}

// Same function as above- just returns a float instead of being void
// Do we need both?
float ProcessInputReturnSC(const string &tweet_, HM_separateChaining &a_map) {
    int inputTweetScore = 0;
    int valid_word_counter = 0;
    std::istringstream token(tweet_);
    std::string single_word;
    while (getline(token, single_word, ' ')) {
        int temp = a_map.search(single_word);
        if (temp != -1) {
            inputTweetScore += temp;
            ++valid_word_counter;
        }
    }

    float final_result = (float) inputTweetScore / (float)valid_word_counter;
    return final_result;
}

float ProcessInputReturnLP(const string &tweet_, HM_linearProbing &a_map) {
    int inputTweetScore = 0;
    int valid_word_counter = 0;
    std::istringstream token(tweet_);
    std::string single_word;
    while (getline(token, single_word, ' ')) {
        int temp = a_map.search(single_word);
        if (temp != -1) {
            inputTweetScore += temp;
            ++valid_word_counter;
        }
    }

    float final_result = (float) inputTweetScore / (float)valid_word_counter;
    return final_result;
}