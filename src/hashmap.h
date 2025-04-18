//
// Created by diego on 4/14/2025.
//
// Modified by Jesse on 4/15/2025
//
#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
using namespace std;

//Can modify max load
constexpr float MAX_LOAD = 0.80;
constexpr int BASE_SIZE_OF_HASH_MAP = 100;

unsigned long long int HashFunction_one(const std::string& word, const int curr_size_map_);


class HM_separateChaining {
public:
    int entries_counter = 0;
    int collision_count = 0;
    int curr_size_of_hash_map = BASE_SIZE_OF_HASH_MAP;
    std::vector<std::vector<std::pair<std::string, int>>> map;

    HM_separateChaining() {
        for (int i = 0; i < BASE_SIZE_OF_HASH_MAP; i++) {
            std::vector<std::pair<std::string, int>> temp;
            map.push_back(temp);
        }
    }

    void insert(const unsigned long long int hash_code, const string& word, int score) {
        if (!map[hash_code].empty()){
            ++collision_count;
        }
        map[hash_code].push_back(make_pair(word, score));
        entries_counter++;
        if (entries_counter/curr_size_of_hash_map > MAX_LOAD) {
            std::cout << "the vector needs to be resized" << std::endl;
        }
    }

    int get_collision_count() const {
        return collision_count;
    }

    int search(const string& word) {
        unsigned long long int hash_code = HashFunction_one(word, curr_size_of_hash_map);
        bool found = false;
        for (size_t i = 0; i < map[hash_code].size(); i++) {
            if (map[hash_code][i].first == word) {
                cout << "The score of the word " << map[hash_code][i].first
                          << " is: " << map[hash_code][i].second << endl;
                found = true;
                return map[hash_code][i].second;
            }
        }
        //if (!found) {
        cout << "The word: " << word << " is not present in the map" << endl;
        return -1;
        //}
    }
};


class HM_linearProbing {
public:
    int entries_counter = 0;
    int collision_count = 0;
    vector<pair<string, int>> map[BASE_SIZE_OF_HASH_MAP] = {};
    int curr_size_of_hash_map = BASE_SIZE_OF_HASH_MAP;

    void insert(const unsigned long long int hash_code, const string& word, int score) {
        int idx = hash_code;
        int start = idx;
        while (!map[idx].empty()) {
            ++collision_count;
            if (map[idx][0].first == word) {
                map[idx][0].second = score;
                return;
            }
            idx = (idx + 1) % BASE_SIZE_OF_HASH_MAP;
            if (idx == start) {
                cerr << "Hash table is full." << endl;
                return;
            }
        }
        map[idx].push_back(make_pair(word, score));
        entries_counter++;
    }

    int get_collision_count() const {
        return collision_count;
    }

    int search(const string& word) {
        unsigned long long int hash_code = HashFunction_one(word, curr_size_of_hash_map);
        int idx = hash_code;
        int start = idx;
        while (!map[idx].empty()) {
            if (map[idx][0].first == word) {
                cout << "The score of the word " << word
                          << " is: " << map[idx][0].second << endl;
                return map[idx][0].second;
            }
            idx = (idx + 1) % BASE_SIZE_OF_HASH_MAP;
            if (idx == start) break;
        }
        cout << "The word: " << word << " is not present in the map" << endl;
        return -1;
    }
};

void ProcessTweet_oneSC(const string& tweet_, HM_separateChaining& a_map, const int score);
void ProcessTweet_oneLP(const string& tweet_, HM_linearProbing& a_map, const int score);

void ParseDataFileSC(const string& fileName, HM_separateChaining& a_map);
void ParseDataFileLP(const string& fileName, HM_linearProbing& a_map);

void ProcessInputSC(const string& tweet_, HM_separateChaining& a_map);
void ProcessInputLP(const string& tweet_, HM_linearProbing& a_map);

float ProcessInputReturnSC(const string &tweet_, HM_separateChaining &a_map);
float ProcessInputReturnLP(const string &tweet_, HM_linearProbing &a_map);

void ParseMovieDataFile(const string& fileName, HM_separateChaining &a_map);
void Process_MovieTitle(const string& tweet_, HM_separateChaining& a_map, const int movieID);




#endif // HASHMAP_H
