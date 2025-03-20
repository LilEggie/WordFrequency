# WordFrequency

## Overview
This repository contains my solutions for **LSPT Homework 2 and 3**, which involved implementing a word and n-gram frequency statistics calculator in C++. Both versions received a full score of **45/45** for the quality of the code implementation. You can access the different versions by exploring the commit history.

## Features  
- Computes word frequency statistics from text files.
- Supports **n-gram analysis**, allowing users to analyze sequences of words.
- Efficient implementation using C++ and standard libraries.
- Cross-platform compatibility—runs on Windows (via MinGW-w64) and Ubuntu.

## Versions  

### Homework 2
Homework 2 received a perfect score of **45/45**. This version manually calculates n-gram frequency statistics, making it less maintainable if additional n-gram calculations are required. Additionally, this version is unfortunately incompatible with Ubuntu/Linux.

### Homework 3 (Current)
Homework 3 also received a perfect score of **45/45**. This version introduces a dedicated class for calculating n-gram frequency statistics, making the program more flexible and scalable. This version is compatible for both Windows and Ubuntu/Linux.

## Installation

### Cloning the Repository
To install the project, clone the repository using:
```sh
git clone https://github.com/LilEggie/WordFrequency.git
cd WordFrequency
```

### Compilation & Execution
Using Batch Files (Windows, MinGW-w64)
```sh
./compile.bat
./run.bat
```

Manual Compilation (Windows, MinGW-w64)
```sh
g++ -Wall -Werror src/*.cpp -o a.out
./a.out [filenames]
```

Ubuntu/Linux
```
g++ -Wall -Werror src/*.cpp -o a.out
./a.out [filenames]
```

## How to Use The N-Gram Calculator (Homework 3)

### 1. Include the Necessary Header
To use `TextProcessor`, include the following header file in your C++ program:
```cpp
#include "text_processor.h"
```
Then, initialize a `TextProcessor` instance to start processing text:
```
TextProcessor processor;
```

### 2. Including Specific N-Grams
To add n-grams to the calculations, use the `include_ngram(const int n)` method. By default, `TextProcessor` will only be processing 1-grams when first created.
- `n`: The n-gram size to include from the calculations.
```cpp
processor.include_ngram(3);  // Includes trigrams in the calculations
```

### 3. Excluding Specific N-Grams
To remove n-grams from the calculations, use the `exclude_ngram(const int n)` method. By default, `TextProcessor` will only be processing 1-grams when first created.
- `n`: The n-gram size to exclude from the calculations.
```cpp
processor.exclude_ngram(3);  // Excludes trigrams from the calculations
```

### 4. Processing Text
To process a string of text, use the `process(const std::string& text, bool append = true)` method.
- `text`: The string of text to process.
- `append`: If true, the new data is added to previously processed data. If false, previous data is cleared before processing.
```cpp
processor.process("Hello World!");
```

### 5. Processing Text Files
To process a text file, use the `process_file(const std::string& filename, bool append = true)` method.
- `filename`: The path to the text file.
- `append`: If true, the new data is added to previously processed data. If false, previous data is cleared before processing.
```cpp
processor.process_file("resources/lion.txt");
```

### 6. Statistics Output
`int num_processed()`: Returns the number of processed texts and files the dataset contains.

`int num_words()`: Returns the total number of words (1-gram) in the processed dataset.

`int num_unique_words()`: Returns the total number of unique words (1-gram) in the processed dataset.

`int num_ngrams(const int n)`: Returns the total number of n-grams  of size `n` in the processed dataset.
- `n`: The n-gram size.

`int num_unique_ngrams(const int n)`: Returns the total number of unique n-grams of size `n` in the processed dataset.
- `n`: The n-gram size.

`vector<FrequencyPair> ngram_frequency(const int n, const int size = -1)`: Returns a list of n-grams and their frequencies in the dataset.
- `n`: The n-gram size.
- `size`: The number of top n-grams to return. If this is negative, all n-grams in the dataset are included.

### 7. Example
```cpp
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
    std::cout << "Number of valid documents processed: " << processor.num_processed() << std::endl;
    std::cout << "Number of words in dataset: " << processor.num_words() << std::endl;
    std::cout << "Number of unique words in dataset: " << processor.num_unique_words() << std::endl;

    for (int n = 2; n <= 5; ++n)
    {
        std::cout << "Number of \"interesting\" " + ngram_name(n) + "s in the dataset: " << processor.num_ngrams(n) << std::endl;
        std::cout << "Number of unique \"interesting\" " + ngram_name(n) + "s in the dataset: " << processor.num_unique_ngrams(n) << std::endl;
    }
}

void print_top_statistics_summary(TextProcessor& processor)
{
    // Print the top 128 words and their frequencies in the dataset.
    int num_words = std::min(processor.num_unique_words(), 128);
    std::cout << "Top " << num_words << " words:\n";
    for (const auto& pair : processor.word_frequency(num_words))
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }

    // Print the top N words and their frequencies for bigrams, trigrams, 4-grams, 5-grams, respectively
    std::vector<int> max_num_ngrams = {64, 32, 16, 8};
    for (int n = 2; n <= 5; ++n)
    {
        int num_ngrams = std::min(processor.num_unique_ngrams(n), max_num_ngrams[n - 2]);
        std::cout << "\nTop " << num_ngrams << " interesting " << ngram_name(n) << "s:\n";

        for (const auto& pair : processor.ngram_frequency(n, num_ngrams))
        {
            std::cout << pair.second << " " << pair.first << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    // Initialize a text processor to start processing text files
    TextProcessor processor;

    // Include bigrams, trigrams, 4-grams, and 5-grams to our calculations
    for (int i = 2; i <= 5; ++i)
    {
        processor.include_ngram(i);
    }

    // Process our files
    for (int i = 1; i < argc; ++i)
    {
        if (!processor.process_file(argv[i]))
        {
            std::cerr << "ERROR: cannot access \"" << argv[i] << "\"\n";
        }
    }

    // Statistics Output
    print_statistics_summary(processor);
    std::cout << std::endl;
    print_top_statistics_summary(processor);
}
```
