#include "words_counter.h"

using namespace std;

int8_t magic_arr[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

set<string> get_words_set(string str, set<string> words_set){
    int start_index = 0, str_size = str.size();
    int last_len = 0;

    for (int i = 0; i <= str_size; ++i)
    {
        if (i == str_size || magic_arr[str[i]] != 1)
        {
            if (start_index == i)
            {
                start_index++;
                continue;
            }

            string current_word = str.substr(start_index, i - start_index);
            start_index = i + 1;

            words_set.emplace(current_word);
        }
    }

    return words_set;
}

int get_unique_words_count(string str)
{
    set<string> init_set;
    return get_words_set(str, init_set).size();
}

int get_unique_words_count(ifstream& file)
{
    size_t buffer_size = 1<<25;
    char *buffer = new char[buffer_size];
    string last_word = "";
    set<string> last_set;
    while (file)
    {
        string sub_word = "";
        file.read(buffer, buffer_size);
        size_t count = file.gcount();
        if (!count)
            break;

        auto part = string(buffer);

        int i = part.size() - 1;
        if (part.size() == buffer_size)
        {

            for (; i > 0; --i)
            {
                if (magic_arr[part[i]] != 1 && i + 1 != part.size())
                {
                    sub_word = part.substr(i + 1, part.size() - i);
                    break;
                }
            }
        }

        string txt = last_word + part.substr(0, i + 1);
        last_set = get_words_set(txt, last_set);
        last_word = sub_word;
    }

    delete[] buffer;

    return last_set.size();
}

