#include <algorithm>
#include <string>
#include <vector>

#include "frequency_map.h"

void FrequencyMap::set_frequency(const std::string& key, const int frequency)
{
    m_data[key] = frequency;
    m_needs_sorting = true;
}

void FrequencyMap::increment_frequency(const std::string& key, const int amount)
{
    this->set_frequency(key, this->get_frequency(key) + amount);
}

int FrequencyMap::get_frequency(const std::string& key) const
{
    if (m_data.find(key) == m_data.end())
    {
        return 0;
    }
    return m_data.at(key);
}

void FrequencyMap::erase_frequency(const std::string& key)
{
    m_data.erase(key);
    m_needs_sorting = true;
}

void FrequencyMap::clear_contents()
{
    m_data.clear();
    m_sorted_data.clear();
    m_needs_sorting = false;
}

int FrequencyMap::num_unique() const
{
    return m_data.size();
}

int FrequencyMap::sum_frequency() const
{
    int sum = 0;
    for (const auto& pair : m_data)
    {
        sum += pair.second;
    }
    return sum;
}

std::vector<FrequencyPair> FrequencyMap::sorted_data(int n)
{
    if (m_needs_sorting)
    {
        this->sort_data();
        m_needs_sorting = false;
    }

    int data_size = m_sorted_data.size();
    if (n < 0 || n > data_size)
    {
        n = data_size;
    }

    std::vector<FrequencyPair> result;
    result.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        result.push_back(m_sorted_data[i]);
    }
    return result;
}

void FrequencyMap::sort_data()
{
    auto compare = [](const auto& a, const auto& b)
    {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    };

    m_sorted_data.assign(m_data.begin(), m_data.end());
    std::sort(m_sorted_data.begin(), m_sorted_data.end(), compare);
}
