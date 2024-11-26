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
     * @brief  Processes the given text into useful statistics.
     *
     * Only words containing at least two alpha characters are processed.
     *
     * Stop words will not be processed for ngram statistics. These
     * include the top 50 words from the AP89 dataset and words that are one
     * alpha character long.
     *
     * ``update()`` should be called after all processings are completed.
     *
     * @param text    The text to process.
     *
     * @param append  If the processed data should be added. If this is false,
     *                then the previous dataset will be cleared. Defaults to
     *                true.
     */
    void process(std::string text, const bool append = true);

    /**
     * @brief  Processes the given file into useful statistics.
     *
     * Only words containing at least two alpha characters are processed.
     *
     * Stop words will not be processed for ngram statistics. These
     * include the top 50 words from the AP89 dataset and words that are one
     * alpha character long.
     *
     * ``update()`` should be called after all processings are completed.
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

    /** @brief  Updates all the statistics the processor has collected. */
    void update();

    /** @brief  Clears all the statistics the processor has collected. */
    void clear();

    /** @brief  The number of texts that were processed. */
    int num_processed() const
    {
        return m_num_processed;
    }

    /**
     * @brief  Gets the number of valid words.
     *
     * @param unique  If the statistic is for unique words. Defaults to false.
     */
    int num_words(const bool unique = false) const;

    /**
     * @brief  Gets the number of bigrams.
     *
     * @param unique  If the statistic is for unique bigrams. Defaults to
     *                false.
     */
    int num_bigrams(const bool unique = false) const;

    /**
     * @brief  Gets the number of trigrams.
     *
     * @param unique  If the statistic is for unique trigrams. Defaults to
     *                false.
     */
    int num_trigrams(const bool unique = false) const;

    /**
     * @brief  Gets the top list of frequent words.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of words to return. If this is negative, then all
     *           of the words in the dataset will be returned.
     */
    std::vector<FrequencyPair> word_frequency(int n = -1) const;

    /**
     * @brief  Gets the top list of frequent bigrams.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of bigrams to return. If this is negative, then all
     *           of the bigrams in the dataset will be returned.
     */
    std::vector<FrequencyPair> bigram_frequency(int n = -1) const;

    /**
     * @brief  Gets the top list of frequent trigrams.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of trigrams to return. If this is negative, then
     *           all of the trigrams in the dataset will be returned.
     */
    std::vector<FrequencyPair> trigram_frequency(int n = -1) const;

private:
    /** The words and their frequencies. */
    FrequencyMap m_word_frequency;

    /** The bigrams and their frequencies. */
    FrequencyMap m_bigram_frequency;

    /** The trigrams and their frequencies. */
    FrequencyMap m_trigram_frequency;

    /** @brief  The number of texts that were processed. */
    int m_num_processed;
};

#endif
