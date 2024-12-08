#ifndef FREQUENCY_MAP_H
#define FREQUENCY_MAP_H

#include <unordered_map>
#include <vector>

using FrequencyPair = std::pair<std::string, int>;

/**
 * @brief  Tracks the frequency of strings and maintains a sorted dataset.
 *
 * Strings with higher frequencies will appear first in the dataset. In the
 * case that their frequencies are the same, the strings will be further sorted
 * alphabetically.
 *
 * This class stores frequencies in an unordered map for efficient lookup,
 * insertion, and deletion operations. When sorted data is requested, the class
 * checks the cache first. If the cache is empty or outdated, the dataset is
 * sorted, cached, and then returned.
 */
class FrequencyMap
{
public:
    FrequencyMap() : m_needs_sorting(false)
    {
    }

    /**
     * @brief  Sets the frequency of a string.
     *
     * Any calls made to change the dataset will be flagged. When sorted data is
     * requested, the class will resort the dataset, cache it, and then return
     * it.
     */
    void set_frequency(const std::string& key, const int frequency);

    /**
     * @brief  Increments the frequency by a certain amount.
     *
     * @param key  The string to increment.
     *
     * @param amount  The amount to increment the string by. Defaults to 1.
     */
    void increment_frequency(const std::string& key, const int amount = 1);

    /**
     * @brief  Gets the frequency of a string.
     *
     * If a string does not exist in the dataset, 0 will be returned.
     */
    int get_frequency(const std::string& key) const;

    /**
     * @brief  Erases the string and its frequency from the dataset.
     *
     * Any calls made to change the dataset will be flagged. When sorted data is
     * requested, the class will resort the dataset, cache it, and then return
     * it.
     */
    void erase_frequency(const std::string& key);

    /** @brief  Clears the frequency map. */
    void clear_contents();

    /** @brief  The number of unique strings in the dataset. */
    int num_unique() const;

    /**
     * @brief  The sum of all the frequencies in the dataset.
     *
     * Every frequency stored in the dataset will be added up and returned.
     */
    int sum_frequency() const;

    /**
     * @brief  Gets the top list of frequent strings.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of strings to return. If this is negative, then all
     *           of the strings in the dataset will be returned. Defaults to -1.
     */
    std::vector<FrequencyPair> sorted_data(int n = -1);

private:
    /**
     * @brief  Sorts the dataset.
     *
     * The sorted data of the unordered map ``m_data`` will be stored into a
     * vector ``m_sorted_data``. This vector will store pairs of strings and
     * integers.
     */
    void sort_data();

    /** @brief  Unsorted frequency data */
    std::unordered_map<std::string, int> m_data;

    /**
     * @brief  Sorted frequency data
     *
     * This will not be updated when the dataset changes, and thus must be
     * manually updated.
     * */
    std::vector<FrequencyPair> m_sorted_data;

    /**
     * @brief  Flags that the dataset needs sorting.
     *
     * This will be true whenever a change has been made to the dataset, e.g.
     * setting or clearing a frequency.
     */
    bool m_needs_sorting;
};

#endif
