#include <fstream>
#include <list>
#include <sstream>
#include <unordered_set>

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

std::string stringify_ngram(const std::list<std::string> ngram)
{
    std::string result;
    for (const auto& s : ngram)
    {
        result += s + " ";
    }
    result.erase(result.length() - 1);
    return result;
}

void TextProcessor::process(std::string text, const bool append)
{
    tolower(text);
    if (!append)
    {
        this->clear();
    }

    std::list<std::string> bigram;
    std::list<std::string> trigram;
    std::string word;

    while(readtext(text, word))
    {
        if (word.length() < 2)
        {
            bigram.clear();
            trigram.clear();
            continue;
        }

        m_word_frequency[word]++;

        if (STOP_WORDS.find(word) != STOP_WORDS.end())
        {
            bigram.clear();
            trigram.clear();
            continue;
        }

        bigram.push_back(word);
        trigram.push_back(word);

        if (bigram.size() == 2)
        {
            m_bigram_frequency[stringify_ngram(bigram)]++;
            bigram.pop_front();
        }
        if (trigram.size() == 3)
        {
            m_trigram_frequency[stringify_ngram(trigram)]++;
            trigram.pop_front();
        }
    }
    m_num_processed++;
}

bool TextProcessor::process_file(const std::string& filename, const bool append)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    process(ss.str(), append);

    file.close();
    return true;
}

void TextProcessor::update()
{
    m_word_frequency.update();
    m_bigram_frequency.update();
    m_trigram_frequency.update();
}

void TextProcessor::clear()
{
    m_word_frequency.clear();
    m_bigram_frequency.clear();
    m_trigram_frequency.clear();
}

int TextProcessor::num_words(const bool unique) const
{
    return unique
           ? m_word_frequency.size()
           : m_word_frequency.total();
}

int TextProcessor::num_bigrams(const bool unique) const
{
    return unique
           ? m_bigram_frequency.size()
           : m_bigram_frequency.total();
}

int TextProcessor::num_trigrams(const bool unique) const
{
    return unique
           ? m_trigram_frequency.size()
           : m_trigram_frequency.total();
}

std::vector<FrequencyPair> TextProcessor::word_frequency(int n) const
{
    return m_word_frequency.sorted_data(n);
}

std::vector<FrequencyPair> TextProcessor::bigram_frequency(int n) const
{
    return m_bigram_frequency.sorted_data(n);
}

std::vector<FrequencyPair> TextProcessor::trigram_frequency(int n) const
{
    return m_trigram_frequency.sorted_data(n);
}
