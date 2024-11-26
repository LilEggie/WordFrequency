#ifndef FREQUENCY_MAP_H
#define FREQUENCY_MAP_H

#include <unordered_map>
#include <vector>

using FrequencyPair = std::pair<std::string, int>;

/**
 * @brief  Keeps track of string frequencies.
 *
 * Datasets are sorted first by highest frequency and then alphabetically.
 */
class FrequencyMap
{
public:
    FrequencyMap() : m_total(0)
    {
    }

    /** @brief  For getting and setting values of certain keys. */
    int& operator[](const std::string& key);

    /** @brief  The number of unique strings. */
    int size() const
    {
        return m_data.size();
    }

    /** @brief  The sum of all the frequencies. */
    int total() const
    {
        return m_total;
    }

    /**
     * @brief  Gets the top list of frequent strings.
     *
     * The list is sorted first by highest frequency and then alphabetically.
     *
     * @param n  The number of strings to return. If this is negative, then all
     *           of the strings in the dataset will be returned.
     */
    std::vector<FrequencyPair> sorted_data(int n = -1) const;

    /**
     * @brief  Updates the frequency map.
     *
     * This should be called when changes occur, such as adding new strings or
     * changing the frequencies.
     */
    void update();

    /** @brief  Clears the frequency map. */
    void clear();

private:
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
     * @brief  The sum of all the frequencies.
     *
     * This will not be updated when the dataset changes, and thus must be
     * manually updated.
     */
    int m_total;
};

#endif
