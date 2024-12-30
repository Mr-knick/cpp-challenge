#include "word_processing.h"
#include <iostream>
#include <memory>

int main ()
{
  try {
    std::cout << "Input words into word list" << std::endl;
    std::shared_ptr<WordProcessor> wp = std::make_shared<WordProcessor>();
    wp->readInputWords();
    wp->printWordList();
    wp->lookupWords();
  }
  catch (std::exception & e) {
    std::cout << "error " << e.what() << std::endl;
  }

  return 0;
}
