#include "word_processing_utils.h"
#include <iostream>

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