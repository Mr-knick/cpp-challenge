//
// Created by brent on 12/28/24.
//
#include "word_processing_utils.h"
#include <iostream>
#include <cassert>

int main() {
    try {
        std::atomic_bool endEncountered = false;
        workerThread(endEncountered);
        // inputMutex.lock();
        std::cout << "t1" << std::endl;
        inputWordsQueue.push("apple");
        inputWordsQueue.push("banana");
        inputWordsQueue.push("apple");
        inputWordsQueue.push("orange");
        std::cout << "t2" << std::endl;
        inputWordsQueue.push("end");
        std::cout << "t3" << std::endl;
        // inputMutex.unlock();



        assert(words["apple"] == 2);
        assert(words["banana"] == 1);
        assert(words["orange"] == 1);

        totalFound = 0;
        lookupWords();

        assert(totalFound == 3);

        std::cout << "All tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}