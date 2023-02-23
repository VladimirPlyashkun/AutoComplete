#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <string>
#include <vector>
#include <unordered_map>

namespace Completion {

    class SlowAutoCompleter {
    public:
        SlowAutoCompleter(const std::vector<std::string> &words, int wordsInCompletion);

        void addWord(const std::string &word);

        [[nodiscard]] std::vector<std::string> getWords(const std::string &prefix) const;

    private:
        std::vector<std::string> words;
        int wordsInCompletion;
    };

    class FastAutoCompleter {
    private:
        typedef unsigned long long longType;
    public:
        FastAutoCompleter(const std::vector<std::string> &words, int wordsInCompletion);

        void addWord(const std::string &word);

        std::vector<std::string> getWords(const std::string &prefix);

    private:
        longType calculateHash(const std::string &word, bool isDictionaryWord);

    private:
        std::unordered_map<longType, std::vector<std::string>> hashToWords;
        int wordsInCompletion;
    };
}

#endif //AUTOCOMPLETE_H
