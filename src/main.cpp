/**
 * Refactoring #1 --- Rename Method
 *
 *    In ``FrequencyMap``, we renamed ``clear()`` to ``clear_contents()`` to
 *    better clarify that it will clear every dataset the map contains.
 *
 * Refactoring #2 --- Encapsulate Collection (or Replace Operator with Method)
 *
 *    We previously overloaded the ``operator[]`` for both read and write
 *    access, but this created ambiguity about whether the user intended to
 *    read or write. This forced the user to manually call an update method to
 *    notify the map of changes, which contradicted our documentation that
 *    stated ``FrequencyMap`` is sorted. To resolve this, we replaced the
 *    overloaded operator with four explicit functions: ``set_frequency()``,
 *    ``increment_frequency()``, ``get_frequency()``, and ``erase_frequency()``.
 *
 * Refactoring #3 --- Rename Method
 *
 *    In ``FrequencyMap``, we renamed ``size()`` to ``num_unique()`` to better
 *    clarify that "size" represents the number of unique strings in the
 *    dataset.
 *
 * Refactoring #4 --- Rename Method
 *
 *    In ``FrequencyMap``, we renamed ``total()`` to ``sum_frequency()`` to
 *    better clarify that "total" represents the sum of all frequencies in the
 *    dataset.
 *
 * Refactoring #5 --- Rename Method
 *
 *    In ``TextProcessor``, we renamed ``clear()`` to ``clear_stats()`` to
 *    better clarify that it clear every dataset the processor has processed
 *    during its lifetime.
 *
 * Refactoring #6 --- Extract Method
 *
 *    Originally, ``TextProcessor::process()`` handled both words and ngrams,
 *    making the method unnecessarily long. We also duplicated code to calculate
 *    bigrams and trigrams, which would complicate expanding the calculation to
 *    larger ngrams (e.g., bigrams to 100-grams). To address this, we introduced
 *    a new method to ``process_ngrams()`` within ``TextProcessor``, which
 *    processes all possible ngrams from a word list. Additionally, to improve
 *    performance, we now require the user to include the ngrams they want to
 *    keep track of via ``include_ngram()``.
 *
 * Refactoring #7 --- Extract Method  (an honorable mention)
 *
 *    Originally, to get the number of unique words processed, you would call
 *    ``TextProcessor::num_words(true)``. This was unintuitive, and it caused
 *    us to mistakenly retrieve the total number of words processed when we
 *    actually needed the number of unique words. To resolve this, we created
 *    two separate methods: one for getting the total number of words processed
 *    and another for getting the number of unique words.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "text_processor.h"

std::string ngram_name(const int n)
{
    if (n <= 1)
    {
        return "";
    }
    if (n == 2)
    {
        return "bigram";
    }
    if (n == 3)
    {
        return "trigram";
    }
    return std::to_string(n) + "-gram";
}

void print_statistics_summary(const TextProcessor& processor)
{
    std::cout << "Number of valid documents: "
              << processor.num_processed() << std::endl;
    std::cout << "Number of words: "
              << processor.num_words() << std::endl;
    std::cout << "Number of unique words: "
              << processor.num_unique_words() << std::endl;

    for (int n = 2; n <= 5; ++n)
    {
        std::cout << "Number of \"interesting\" " + ngram_name(n) + "s: "
                  << processor.num_ngrams(n) << std::endl;
        std::cout << "Number of unique \"interesting\" " + ngram_name(n) + "s: "
                  << processor.num_unique_ngrams(n) << std::endl;
    }
}

void print_top_statistics_summary(TextProcessor& processor)
{
    int num_words = std::min(processor.num_unique_words(), 128);
    std::cout << "Top " << num_words << " words:\n";
    for (const auto& pair : processor.word_frequency(num_words))
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }

    std::vector<int> max_num_ngrams = {64, 32, 16, 8};
    for (int n = 2; n <= 5; ++n)
    {
        int num_ngrams = std::min(processor.num_unique_ngrams(n),
                                  max_num_ngrams[n - 2]);

        std::cout << "\nTop " << num_ngrams << " interesting "
                  << ngram_name(n) << "s:\n";

        for (const auto& pair : processor.ngram_frequency(n, num_ngrams))
        {
            std::cout << pair.second << " " << pair.first << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    TextProcessor processor;
    for (int i = 2; i <= 5; ++i)
    {
        processor.include_ngram(i);
    }

    for (int i = 1; i < argc; ++i)
    {
        if (!processor.process_file(argv[i]))
        {
            std::cerr << "ERROR: cannot access \"" << argv[i] << "\"\n";
        }
    }

    print_statistics_summary(processor);
    std::cout << std::endl;
    print_top_statistics_summary(processor);
}
