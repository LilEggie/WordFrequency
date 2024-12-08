#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "frequency_map.h"
#include "text_processor.h"
#include "text_utils.h"

static std::unordered_set<std::string> STOP_WORDS = {
    "the", "of", "to", "a", "and", "in", "said", "for", "that", "was", "on",
    "he", "is", "with", "at", "by", "it", "from", "as", "be", "were", "an",
    "have", "his", "but", "has", "are", "not", "who", "they", "its", "had",
    "will", "would", "about", "i", "been", "this", "their", "new", "or",
    "which", "we", "more", "after", "us", "percent", "up", "one", "people"
};

void TextProcessor::include_ngram(const int n)
{
    if (n <= 1)
    {
        return;
    }
    if (m_ngrams.find(n) == m_ngrams.end())
    {
        m_ngrams[n] = FrequencyMap();
    }
}

void TextProcessor::exclude_ngram(const int n)
{
    m_ngrams.erase(n);
}

void TextProcessor::process_ngrams(const std::vector<std::string>& word_list)
{
    int size = word_list.size();

    for (auto& pair : m_ngrams)
    {
        int n = pair.first;
        FrequencyMap& fmap = pair.second;

        for (int i = 0; i <= size - n; ++i)
        {
            std::string s;
            for (int j = 0; j < n; ++j)
            {
                s += word_list[i + j] + " ";
            }
            s.erase(s.length() - 1);
            fmap.increment_frequency(s);
        }
    }
}

void TextProcessor::process(std::string& text, const bool append)
{
    tolower(text);
    if (!append)
    {
        this->clear_stats();
    }

    std::vector<std::string> word_list;
    std::string word;

    while (readtext(text, word))
    {
        if (word.length() < 2)
        {
            this->process_ngrams(word_list);
            word_list.clear();
            continue;
        }

        m_word_frequency.increment_frequency(word);

        if (STOP_WORDS.find(word) != STOP_WORDS.end())
        {
            this->process_ngrams(word_list);
            word_list.clear();
            continue;
        }

        word_list.push_back(word);
    }
    this->process_ngrams(word_list);
    m_num_processed++;
}

bool TextProcessor::process_file(const std::string& filename, const bool append)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string tmp = buffer.str();

    this->process(tmp, append);
    return true;
}

void TextProcessor::clear_stats()
{
    m_word_frequency.clear_contents();
}

int TextProcessor::num_words() const
{
    return m_word_frequency.sum_frequency();
}

int TextProcessor::num_unique_words() const
{
    return m_word_frequency.num_unique();
}

std::vector<FrequencyPair> TextProcessor::word_frequency(const int n)
{
    return m_word_frequency.sorted_data(n);
}

int TextProcessor::num_ngrams(const int n) const
{
    if (m_ngrams.find(n) == m_ngrams.end())
    {
        return 0;
    }
    return m_ngrams.at(n).sum_frequency();
}

int TextProcessor::num_unique_ngrams(const int n) const
{
    if (m_ngrams.find(n) == m_ngrams.end())
    {
        return 0;
    }
    return m_ngrams.at(n).num_unique();
}

std::vector<FrequencyPair> TextProcessor::ngram_frequency(const int n,
                                                          const int size)
{
    if (m_ngrams.find(n) == m_ngrams.end())
    {
        return std::vector<FrequencyPair>();
    }
    return m_ngrams.at(n).sorted_data(size);
}
