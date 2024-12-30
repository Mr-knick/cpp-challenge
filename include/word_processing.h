#ifndef WORD_PROCESSING_H
#define WORD_PROCESSING_H

#include <thread>
#include <map>
#include <queue>
#include <string>

class WordProcessor {
public:
    // Initializes class and worker thread
    WordProcessor();

    // Destructs class and cleans up worker thread
    ~WordProcessor();

    // Delete copy constructor
    WordProcessor(const WordProcessor&) = delete;

    // Delete copy assignment constructor
    WordProcessor& operator=(const WordProcessor&) = delete;

    // Delete move constructor
    WordProcessor(WordProcessor&&) = delete;

    // Delete move assignment constructor
    WordProcessor& operator=(WordProcessor&&) = delete;

    // Reads the input words from STDIN
    void readInputWords();

    // Looks up the words within m_words
    void lookupWords();

    // Prints words within m_words
    void printWordList() ;

private:
    // A Queue is overkill but allows multiple input streams to be added later
    std::queue<std::string> m_inputWordsQueue{};

    // Ensures logic with "end" string is resolved before attempting another read of STDIN
    // Also is used to ensure safe read/write of m_words
    std::mutex m_inputMutex{};

    // Map is alphabetical by default and has good access times
    std::map<std::string, int> m_words{};

    // Counter of discovered words
    int m_totalFound{};

    // Processing Thread
    std::thread m_workerThread;

    // Thread safe cancellation
    std::atomic_bool m_endEncountered{false};

    void workerThreadFunction();
};

#endif //WORD_PROCESSING_H
