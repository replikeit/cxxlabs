//
// Created by replikeit on 9/19/21.
//

#ifndef LAB1_WORDS_COUNTER_H
#define LAB1_WORDS_COUNTER_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

int get_unique_words_count(std::string str);

int get_unique_words_count(std::ifstream& file);

#endif //LAB1_WORDS_COUNTER_H
