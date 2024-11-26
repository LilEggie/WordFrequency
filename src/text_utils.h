#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>

/**
 * @brief  Extracts the first occurring word from the given text.
 *
 * The extracted word will always start and end with an alpha character. Single
 * quotes are specially handled to capture contractions such as "don't" and
 * "wouldn't."
 *
 * The extracted word is removed from the provided text, allowing the caller to
 * iteratively read until the text is empty.
 *
 * @param text  A reference to the string to extract the word from. This string
 *              will be modified to remove the extracted word.
 *
 * @param result  A reference to a string where the first occurring word will
 *                be stored. If no word is found, then this will be an empty
 *                string.
 *
 * @return  If the end of the text has not been reached.
 */
bool readtext(std::string& text, std::string& result);

/** @brief  Converts all the characters in a text to lowercase. */
void tolower(std::string& text);

#endif
