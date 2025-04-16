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
constexpr int SIZE_OF_HASH_MAP = 100;

unsigned long long int HashFunction_one(const string& word);


class HM_separateChaining {
public:
    int entries_counter = 0;
    vector<pair<string, int>> a[SIZE_OF_HASH_MAP] = {};

    void insert(const unsigned long long int hash_code, const string& word, int score) {
        a[hash_code].push_back(make_pair(word, score));
        entries_counter++;
    }

    int search(const string& word) {
        unsigned long long int hash_code = HashFunction_one(word);
        bool found = false;
        for (size_t i = 0; i < a[hash_code].size(); i++) {
            if (a[hash_code][i].first == word) {
                cout << "The score of the word " << a[hash_code][i].first
                          << " is: " << a[hash_code][i].second << endl;
                found = true;
                return a[hash_code][i].second;
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
    vector<pair<string, int>> map[SIZE_OF_HASH_MAP] = {};

    void insert(const unsigned long long int hash_code, const string& word, int score) {
        int idx = hash_code;
        int start = idx;
        while (!map[idx].empty()) {
            if (map[idx][0].first == word) {
                map[idx][0].second = score;
                return;
            }
            idx = (idx + 1) % SIZE_OF_HASH_MAP;
            if (idx == start) {
                cerr << "Hash table is full." << endl;
                return;
            }
        }
        map[idx].push_back(make_pair(word, score));
        entries_counter++;
    }

    void search(const string& word) {
        unsigned long long int hash_code = HashFunction_one(word);
        int idx = hash_code;
        int start = idx;
        while (!map[idx].empty()) {
            if (map[idx][0].first == word) {
                cout << "The score of the word " << word
                          << " is: " << map[idx][0].second << endl;
                return;
            }
            idx = (idx + 1) % SIZE_OF_HASH_MAP;
            if (idx == start) break;
        }
        cout << "The word: " << word << " is not present in the map" << endl;
    }
};

void ProcessTweet_one(const string& tweet_, HM_separateChaining& a_map, const int score);
void ParseDataFile(const string& fileName, HM_separateChaining& a_map);
void ProcessInput(const string& tweet_, HM_separateChaining& a_map);
float ProcessInputReturn(const string &tweet_, HM_separateChaining &a_map);
#endif // HASHMAP_H
