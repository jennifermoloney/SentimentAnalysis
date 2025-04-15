//
// Created by diego on 4/14/2025.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

constexpr float MAX_LOAD = 0.80; // this can be modified if needed

class HM_separateChaining {
public:
	int entries_counter = 0;
	std::vector<std::pair<std::string, int>> a[100] = {};
	//consider making this a pointer so that we can late "resize" the map by creating a new array and update the pointer
	// current problem cannot make array of 100000 elements.

	void insert(const unsigned long long int hash_code_, const std::string& word_, int score_) {
		a[hash_code_].push_back(std::pair<std::string, int>(word_, score_));
		entries_counter++;
	}
	void search();
};

unsigned long long int HashFunction_one(const std::string& word);

void ProcessTweet_one(const std::string& tweet_, HM_separateChaining& a_map, const int score);

void ParseDataFile(const std::string& fileName, HM_separateChaining& a_map);


#endif //HASHMAP_H
