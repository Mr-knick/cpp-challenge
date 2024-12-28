#include "word_processing.h"
#include <unistd.h>
#include <iostream>

WordProcessor::WordProcessor()
{
  m_workerThread = std::thread(&WordProcessor::workerThreadFunction, this);
}

WordProcessor::~WordProcessor() {
  m_endEncountered = true;
  if (m_workerThread.joinable()) {
    m_workerThread.join();
  }
}

void WordProcessor::readInputWords() {
  std::string inputWord;

  while (!m_endEncountered) {
    if (!m_inputWordsQueue.empty()) {
      sleep(0); // Yield to allow worker thread to process. Use callback if longer wait time
      continue;
    }

    // STDIN can be grabbed using C++'s cin command
    std::cin >> inputWord;

    // Grabs one line at a time and clears multiple inputs. Does not deal with rate use case of space within a word
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    std::lock_guard<std::mutex> lock(m_inputMutex);
    m_inputWordsQueue.push(inputWord);
  }
}

void WordProcessor::lookupWords() {
  std::string lookupWord;

  for (;;) {
    std::cout << "\nEnter a word for lookup:" << std::endl;
    std::cin >> lookupWord;
    if (std::cin.eof()) {
      std::cout << "EOF detected" << std::endl;
      std::cout << "\n=== Total words found: " << std::to_string(m_totalFound) << std::endl;
      return;
    }

    std::lock_guard<std::mutex> lock(m_inputMutex);
    auto it = m_words.find(lookupWord);
    if (it != m_words.end()) {
      std::cout << "SUCCESS: " << lookupWord << " was present " << std::to_string(it->second)
                << " times in the initial word list" << std::endl;
      m_totalFound++;
    } else {
      std::cout << lookupWord << " was NOT found in the initial word list" << std::endl;
    }
  }
}

void WordProcessor::printWordList() {
  std::lock_guard<std::mutex> lock(m_inputMutex);
  std::cout << "\n=== Word list:" << std::endl;
  for (const auto& wordAndCount : m_words) {
    std::cout << wordAndCount.first << " " << wordAndCount.second << std::endl;
  }
}

void WordProcessor::workerThreadFunction() {
  while (!m_endEncountered) {
    if (!m_inputWordsQueue.empty()) {
      std::lock_guard<std::mutex> lock(m_inputMutex);
      std::string currentWord = m_inputWordsQueue.front();
      m_inputWordsQueue.pop();
      if (currentWord == "end") {
        m_endEncountered = true;
        break;
      }
      auto it = m_words.find(currentWord);
      if (it == m_words.end()) {
        m_words.insert({currentWord, 1});
      } else {
        it->second++;
      }
    }
  }
}