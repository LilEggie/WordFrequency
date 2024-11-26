#include <algorithm>
#include <cctype>

#include "text_utils.h"

size_t first_alpha_occurrence(const std::string& text)
{
    for (size_t i = 0; i < text.length(); ++i)
    {
        if (std::isalpha(text[i]))
        {
            return i;
        }
    }
    return std::string::npos;
}

size_t first_delim_occurrence(const std::string& text, const size_t index = 0)
{
    int single_quote_at = -1;
    for (size_t i = index; i < text.length(); ++i)
    {
        if (text[i] == '\'' && single_quote_at < 0)
        {
            single_quote_at = i;
            continue;
        }

        if (!std::isalpha(text[i]))
        {
            return (int) i != single_quote_at + 1
                   ? i
                   : i - 1;  // for words like "parents'"
        }
    }
    return text.length();
}

bool readtext(std::string& text, std::string& result)
{
    size_t start = first_alpha_occurrence(text);
    if (start == std::string::npos)
    {
        text.clear();
        result.clear();
        return false;
    }

    size_t end = first_delim_occurrence(text, start);
    result = text.substr(start, end - start);

    text = text.substr(
        end == text.length()
        ? end
        : end + 1
    );
    return true;
}

void tolower(std::string& text)
{
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c)
        {
            return std::tolower(c);
        });
}
