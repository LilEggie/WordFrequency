#include <algorithm>

#include "frequency_map.h"

int& FrequencyMap::operator[](const std::string& key)
{
    if (m_data.find(key) == m_data.end())
    {
        m_data[key] = 0;
    }
    return m_data[key];
}

std::vector<FrequencyPair> FrequencyMap::sorted_data(int n) const
{
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

void FrequencyMap::update()
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

    m_total = 0;

    for (const auto& pair : m_data)
    {
        m_total += pair.second;
    }
}

void FrequencyMap::clear()
{
    m_data.clear();
    m_sorted_data.clear();
    m_total = 0;
}
