#include <thread>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

#include <iostream>
#include <queue>
#include <string>

// struct Word
// {
//   char * data;
//   int count;
//
//   Word (const char * data_ ) :
//     data( ::strdup(data_) )
//   {}
//
//   Word () :
//     data((char *)"")
//   {}
// };

// std::vector<Word*> s_wordsArray;
// Word s_word;
// int s_totalFound;

std::vector<std::string> words;
std::queue<std::string> inputWordsQueue{};
std::mutex inputMutex{};

// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread (std::atomic_bool& endEncountered)
{
  bool found = false;
  std::cout << "begin process" << std::endl;
  while (!endEncountered) {
    if (!inputWordsQueue.empty()){
      std::cout << "process one word" << std::endl;
      inputMutex.lock();
      std::cout << "process locked" << std::endl;
      std::string currentWord = inputWordsQueue.front();
      inputWordsQueue.pop();
      if (currentWord == "end") {
        endEncountered = true;
        inputMutex.unlock();
        std::cout << "unlocked process" << std::endl;
        break;
      }
      std::cout << "push back word" << std::endl;
      words.push_back(currentWord);
      inputMutex.unlock();
      std::cout << "unlocked process" << std::endl;
    }


  }
  std::cout << "now end" << std::endl;
  // while (!endEncountered)
  // {
  //   if (s_word.data[0]) // Do we have a new word?
  //   {
  //     Word * w = new Word(s_word); // Copy the word
  //
  //     s_word.data[0] = 0; // Inform the producer that we consumed the word
  //
  //     endEncountered = std::strcmp( s_word.data, "end" ) == 0;
  //
  //     if (!endEncountered)
  //     {
  //       // Do not insert duplicate words
  //       for ( auto p : s_wordsArray )
  //       {
  //         if (!std::strcmp( p->data, w->data ))
  //         {
  //           ++p->count;
  //           found = true;
  //           break;
  //         }
  //       }
  //
  //       if (!found)
  //         s_wordsArray.push_back( w );
  //     }
  //   }
  // }
};

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords ()
{
  std::atomic_bool endEncountered = false;
  std::string inputWord;
  std::thread * worker = new std::thread( workerThread , std::ref(endEncountered));

  while (!endEncountered) {
    std::cout << "begin input" << std::endl;
    std::cin >> inputWord;
    inputMutex.lock();
    inputWordsQueue.push(inputWord);
    inputMutex.unlock();
    if (inputWord == "end") break;
    std::cout << "unlock input" << std::endl;
  }

  std::cout << "test" << std::endl;
  worker->join();




  // char * linebuf = new char[32];
  //
  // while (!endEncountered)
  // {
  //   if (!std::gets( linebuf )) // EOF?
  //     return;
  //
  //   endEncountered = std::strcmp( linebuf, "end" ) == 0;
  //
  //   // Pass the word to the worker thread
  //   std::strcpy( s_word.data, linebuf );
  //   while (s_word.data[0]); // Wait for the worker thread to consume it
  // }
  //
  // worker->join(); // Wait for the worker to terminate
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords ()
{
  bool found;
  // char * linebuf = new char[32];
  std::string lookupWord{};

  for(;;) {
    std::printf( "\nEnter a word for lookup:" );
    std::cin >> lookupWord;
    if (std::cin.eof()) {
      // NOTE EOF will behave differently depending on if ran with IDE and terminal
      std::cout << "EOF detected" << std::endl;
      return;
    }
    std::printf("\nHere %s", lookupWord.c_str());


    // // Initialize the word to search for
    // Word * w = new Word();
    // std::strcpy( w->data, linebuf );

    // // Search for the word
    // unsigned i;
    // for ( i = 0; i < s_wordsArray.size(); ++i )
    // {
    //   if (std::strcmp( s_wordsArray[i]->data, w->data ) == 0)
    //   {
    //     found = true;
    //     break;
    //   }
    // }
    // Uses a map

  }
  //   if (found)
  //   {
  //     std::printf( "SUCCESS: '%s' was present %d times in the initial word list\n",
  //                  s_wordsArray[i]->data, s_wordsArray[i]->count );
  //     ++s_totalFound;
  //   }
  //   else
  //     std::printf( "'%s' was NOT found in the initial word list\n", w->data );
  // }
}

int main ()
{
  try
  {
    readInputWords();
    
    // Sort the words alphabetically
    // use ordered map
    // std::sort( s_wordsArray.begin(), s_wordsArray.end() );

    // Print the word list
    std::printf( "\n=== Word list:\n" );
    // for ( auto p : s_wordsArray )
    //   std::printf( "%s %d\n", p->data, p->count );

    lookupWords();
    //
    // printf( "\n=== Total words found: %d\n", s_totalFound );
  }
  catch (std::exception & e)
  {
    std::printf( "error %s\n", e.what() );
  }
  
  return 0;
}