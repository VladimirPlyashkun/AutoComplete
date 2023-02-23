
#include "AutoComplete.h"


Completion::SlowAutoCompleter::SlowAutoCompleter(const std::vector<std::string> &words, int wordsInCompletion)
        : wordsInCompletion(wordsInCompletion) {
    for (auto &word: words) {
        addWord(word);
    }
}

void Completion::SlowAutoCompleter::addWord(const std::string &word) {
    words.push_back(word);
}

std::vector<std::string> Completion::SlowAutoCompleter::getWords(const std::string &prefix) const {
    std::vector<std::string> result;
    for (auto &word: words) {
        if (word.find(prefix) == 0) {
            result.push_back(word);
            if (result.size() == wordsInCompletion) {
                break;
            }
        }
    }
    return result;
}

Completion::FastAutoCompleter::FastAutoCompleter(const std::vector<std::string> &words, int wordsInCompletion)
        : wordsInCompletion(wordsInCompletion) {
    for (auto &word: words) {
        addWord(word);
    }
}

void Completion::FastAutoCompleter::addWord(const std::string &word) {
    calculateHash(word, true);
}

Completion::FastAutoCompleter::longType Completion::FastAutoCompleter::calculateHash(const std::string &word,
                                                                                     bool isDictionaryWord) {
    longType hash = 0;
    longType prime = 1;
    for (int index = 0; index < word.size(); ++index) {
        hash += word[index] * prime;
        prime *= 31;
        if (isDictionaryWord) {
            hashToWords[hash].push_back(word);
        }
    }
    return hash;
}

std::vector<std::string> Completion::FastAutoCompleter::getWords(const std::string &prefix) {
    longType prefixHash = calculateHash(prefix, false);
    std::vector<std::string> result;
    auto &foundWords = hashToWords[prefixHash];
    for (auto &word: foundWords) {
        if (word.find(prefix) == 0) {
            result.push_back(word);
            if (result.size() == wordsInCompletion) {
                break;
            }
        }
    }
    return result;
}

