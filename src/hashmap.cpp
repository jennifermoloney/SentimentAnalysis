//
// Created by diego on 4/14/2025.
//

#include "hashmap.h"
#include <iostream>

unsigned long long int HashFunction_one(const std::string& word) {
	// do the calculations
	// use prime number 131 for even distribution and since it is bigger than 128 of ASCII characters.
	unsigned long long int value = 0;
	int alpha = word.size();
	for ( int i = word.size() - 1; i > -1; i--) {
		value += static_cast<int>(word[i]) * (131 ^ word.size() - 1 - i);
	}
	//value %= 100000;
	// also reduce it for a final output
	return value % 100;
}

void ProcessTweet_one(const std::string& tweet_, HM_separateChaining& a_map, const int score) {
	std::string word;
	std::istringstream message_string(tweet_);
	while (getline(message_string, word, ' ')) {
		unsigned long long int hash_code = HashFunction_one(word);
		a_map.insert(hash_code, word, score);
	}
}


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

	if(dataFile.is_open()) {
		std::cout << "Data file open!" << std::endl;
	}
	else {
		std::cout << "Data file FAILED to open!" << std::endl;
	}
	int counter = 0;
	while (std::getline(dataFile, line) && counter != 100000){
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
		//std::cout << "jee" << std::endl;
		++counter;
		// now we have proper score and tweet message
		// time to process the message word by word into the hash map
		ProcessTweet_one(tweet, a_map, std::stoi(score));
	}
}