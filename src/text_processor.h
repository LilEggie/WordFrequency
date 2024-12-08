#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>
#include <vector>

#include "frequency_map.h"

class TextProcessor
{
public:
    TextProcessor() : m_num_processed(0)
    {
    }

    /**
     * @brief  The ngrams to include when processing text.
     *
     * It is recommended to initialize what ngrams to record before processing
     * text.
     */
    void include_ngram(const int n);

    /** @brief  The ngrams to exclude when procesing text. */
    void exclude_ngram(const int n);

    /**
     * @brief  Processes the given text into useful statistics.
     *
     * Only words containing at least two alpha characters are processed.
     *
     * Stop words will not be processed for ngram statistics. These include the
     * top 50 words from the AP89 dataset and words that are one alpha character
     * long.
     *
     * @param text    The text to process.
     *
     * @param append  If the processed data should be added. If this is false,
     *                then the previous dataset will be cleared. Defaults to
     *                true.
     */
    void process(std::string& text, const bool append = true);

    /**
     * @brief  Processes the given file into useful statistics.
     *
     * Only words containing at least two alpha characters are processed.
     *
     * Stop words will not be processed for ngram statistics. These include the
     * top 50 words from the AP89 dataset and words that are one alpha character
     * long.
     *
     * @param filename  The name of the file to process.
     *
     * @param append  If the processed data should be added. If this is false,
     *                then the previous dataset will be cleared. Defaults to
     *                true.
     *
     * @return  If the file was successfully processed.
     */
    bool process_file(const std::string& filename, const bool append = true);

    /** @brief  Clears all the statistics the processor has collected. */
    void clear_stats();

    /** @brief  The number of texts that were processed. */
    int num_processed() const
    {
        return m_num_processed;
    }

    /** @brief  Gets the number of words that has been processed. */
    int num_words() const;

    /** @brief  Gets the number of unique words that has been processed. */
    int num_unique_words() const;

    /**
     * @brief  Gets the top list of frequent words.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of words to return. If this is negative, then all
     *           of the words in the dataset will be returned. Defaults to -1.
     */
    std::vector<FrequencyPair> word_frequency(const int n = -1);

    /** @brief  Gets the number of ngrams that has been processed. */
    int num_ngrams(const int n) const;

    /** @brief  Gets the number of unique ngrams that has been processed. */
    int num_unique_ngrams(const int n) const;

    /**
     * @brief  Gets the top list of frequent ngrams.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of ngrams to return. If this is negative, then all
     *           of the ngrams in the dataset will be returned. Defaults to -1.
     */
    std::vector<FrequencyPair> ngram_frequency(const int n, const int size = -1);

private:
    /** @brief  Processes all ngrams that can be produced from the word list. */
    void process_ngrams(const std::vector<std::string>& word_list);

    /** @brief  The words and their frequencies. */
    FrequencyMap m_word_frequency;

    std::unordered_map<int, FrequencyMap> m_ngrams;

    /** @brief  The number of texts that were processed. */
    int m_num_processed;
};

#endif
