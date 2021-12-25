#include <gtest/gtest.h>
#include <words_counter.h>

#include <string>

using namespace std;

TEST(WordsCounterTesting, CommonStr) {
    ASSERT_EQ( get_unique_words_count("a bb ccc"), 3);
}

TEST(WordsCounterTesting, EmptyStr) {
    ASSERT_EQ(get_unique_words_count(""), 0);
}

TEST(WordsCounterTesting, SpacesStr) {
    ASSERT_EQ(get_unique_words_count("a bb            ccc"), 3);
}

TEST(WordsCounterTesting, AnotherSeparatorsStr) {
    ASSERT_EQ(get_unique_words_count("str    ,, , str  word"), 2);
}

TEST(WordsCounterTesting, TwoEqualsWordsStr) {
    ASSERT_EQ(get_unique_words_count("a a bb        "), 2);
}