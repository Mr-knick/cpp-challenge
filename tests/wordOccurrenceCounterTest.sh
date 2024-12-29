#!/bin/bash

# ctest is a little wonky with cin and didn't want to make all the function public so wrote up a batch

echo -e "=== No input test"
output=$(echo "end" | ./wordOccurrenceCounter 2>&1)

wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 0" ]]; then
#if  [[ $(echo /"$last_line" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]') == $(echo "$expected_line" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]') ]]; then
  echo "Test passed: Last line matches expected output"
else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 0"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Search for good word test"
output=$(echo -e "this\nis\na\n\nend\nthis" | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 1" ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 1"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Search for bad word test"
output=$(echo -e "this\nis\na\n\nend\nnot" | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 0" ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 0"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Search for good word with extra whitespace test"
output=$(echo -e "this\nis\nis\n    a  \n\nend\na\na" | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 2" ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 2"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Search for good word with extra whitespace in search test"
output=$(echo -e "this\nis\nis\n    a  \n\nend\na\n  a  " | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 2" ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 2"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Search for good word with tabs search test"
output=$(echo -e "this\nis\nis\n\ta\t\n\nend\na\na" | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail -1)

if [[ $wordsFound == "=== Total words found: 2" ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: === Total words found: 2"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Double bad entry test"
output=$(echo -e "this this this\nis\nis\n\ta\t\n\nend\nthis" | ./wordOccurrenceCounter 2>&1)
#echo $output
wordsFound=$(echo "$output" | tail)

if [[ $wordsFound == *"SUCCESS: this was present 1 times"* ]]; then
  echo "Test passed: Last line matches expected output"

else
  echo "Test failed: Words Found does not match expected output"
  echo "Expected: SUCCESS: this was present 1 times"
  echo "Actual:   $wordsFound"
fi

##############################################################################

echo -e "\n=== Valgrind memory test"
echo -e "this\nis\nis\n\ta\t\n\nend\na\na" | sudo valgrind --leak-check=full --show-leak-kinds=all ./wordOccurrenceCounter