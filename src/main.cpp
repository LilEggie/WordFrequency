#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "text_processor.h"

void print_statistics_summary(const TextProcessor& processor)
{
    std::cout << "Number of valid documents: "
              << processor.num_processed() << std::endl;
    std::cout << "Number of words: "
              << processor.num_words() << std::endl;
    std::cout << "Number of unique words: "
              << processor.num_words(true) << std::endl;
    std::cout << "Number of \"interesting\" bigrams: "
              << processor.num_bigrams() << std::endl;
    std::cout << "Number of unique \"interesting\" bigrams: "
              << processor.num_bigrams(true) << std::endl;
    std::cout << "Number of \"interesting\" trigrams: "
              << processor.num_trigrams() << std::endl;
    std::cout << "Number of unique \"interesting\" trigrams: "
              << processor.num_trigrams(true) << std::endl;
}

void print_top_statistics_summary(const TextProcessor& processor)
{
    int num_words = std::min(processor.num_words(true), 64);
    int num_bigrams = std::min(processor.num_bigrams(true), 32);
    int num_trigrams = std::min(processor.num_trigrams(true), 16);

    std::cout << "Top " << num_words << " words:\n";
    for (const auto& pair : processor.word_frequency(num_words))
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }

    std::cout << "\nTop " << num_bigrams << " interesting bigrams:\n";
    for (const auto& pair : processor.bigram_frequency(num_bigrams))
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }

    std::cout << "\nTop " << num_trigrams << " interesting trigrams:\n";
    for (const auto& pair : processor.trigram_frequency(num_trigrams))
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }
}

int main(int argc, char* argv[])
{
    TextProcessor processor;

    for (int i = 1; i < argc; ++i)
    {
        if (!processor.process_file(argv[i]))
        {
            std::cerr << "ERROR: cannot access \"" << argv[i] << "\"\n";
        }
    }

    processor.update();

    print_statistics_summary(processor);
    std::cout << std::endl;
    print_top_statistics_summary(processor);
}
