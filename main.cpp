#include <iostream>
#include <fstream>
#include <chrono>

#include "AutoComplete.h"

std::vector<std::string> readWordsFromFile(const std::string &path) {
    std::ifstream inputStream(path);
    std::vector<std::string> words;
    std::string word;
    while (inputStream >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    using namespace std;
    using namespace std::chrono;
    using namespace Completion;

    vector<string> wordsFromFile = readWordsFromFile("<path to words.txt>");

    const int wordsInCompletion = 10;
    SlowAutoCompleter slowAutoCompleter(wordsFromFile, wordsInCompletion);
    FastAutoCompleter fastAutoCompleter(wordsFromFile, wordsInCompletion);

    while (true) {
        string prefix;
        cin >> prefix;
        auto timeBefore = high_resolution_clock::now();
        vector<string> words = fastAutoCompleter.getWords(prefix);
        auto timeAfter = high_resolution_clock::now();
        cout << "--- Completion Result ---" << endl;
        for (const auto &word: words) {
            cout << word << endl;
        }
        cout << "------" << endl;
        cout << "Elapsed time:" << endl;
        cout << duration_cast<seconds>(timeAfter - timeBefore).count() << " s" << std::endl;
        cout << duration_cast<milliseconds>(timeAfter - timeBefore).count() << " ms" << std::endl;
        cout << duration_cast<microseconds>(timeAfter - timeBefore).count() << " micros" << std::endl;
    }
    return 0;
}
