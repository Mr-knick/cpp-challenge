#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <queue>
#include <string>

std::queue<std::string> inputWordsQueue{};
std::mutex inputMutex{};
//std::map automatically sorts keys/words
std::map<std::string, int> words{};
int totalFound = 0;

// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (words), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread (std::atomic_bool& endEncountered)
{
  while (!endEncountered) {
    if (!inputWordsQueue.empty()){
      inputMutex.lock();
      std::string currentWord = inputWordsQueue.front();
      inputWordsQueue.pop();
      if (currentWord == "end") {
        endEncountered = true;
        inputMutex.unlock();
        break;
      }
      auto it = words.find(currentWord);
      if (it == words.end()) {
        words.insert({currentWord, 1});
      }
      else {
        it->second++;
      }
      inputMutex.unlock();
    }
  }
}

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords ()
{
  std::atomic_bool endEncountered = false;
  std::string inputWord;
  auto * worker = new std::thread( workerThread , std::ref(endEncountered));

  // If there is a need to have words that contain spaces use the following snippet.
  // ie. last names with a space. Or build custom solution in std. ie range or for loop
  // #include <boost/algorithm/string.hpp>
  // std::getline(std::cin, inputWord);
  // boost::algorithm::trim(inputWord);

  while (!endEncountered) {
    // By default cin will only do one word at a time
    std::cin >> inputWord;

    // Clear any additional information that may have been input on the line.
    // This will ensure only one word is accepted at a time
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    inputMutex.lock();
    inputWordsQueue.push(inputWord);
    inputMutex.unlock();
    if (inputWord == "end") {
      break;
    }
  }
  worker->join();
  delete worker;
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords ()
{
  std::string lookupWord{};

  for(;;) {
    std::cout << "\nEnter a word for lookup:" << std::endl;
    std::cin >> lookupWord;
    if (std::cin.eof()) {
      // NOTE EOF will behave differently depending on if ran with IDE and terminal
      std::cout << "EOF detected" << std::endl;
      return;
    }
    auto it = words.find(lookupWord);
    if (it != words.end()) {
      std::cout << "SUCCESS: " << lookupWord << " was present " << std::to_string(it->second) <<
        " times in the initial word list" << std::endl;
      totalFound++;
    }
    else {
      std::cout << lookupWord << "was NOT found in the initial word list" << std::endl;
    }
  }
}

int main ()
{
  try
  {
    readInputWords();

    // Print the word list
    std::cout << "\n=== Word list:" << std::endl;
    for (const auto& wordAndCount: words) {
      std::cout << wordAndCount.first << " " << wordAndCount.second << std::endl;
    }

    lookupWords();
    std::cout << "\n=== Total words found: " << std::to_string(totalFound) << std::endl;
  }
  catch (std::exception & e)
  {
    std::cout << "error " << e.what() << std::endl;
  }
  
  return 0;
}