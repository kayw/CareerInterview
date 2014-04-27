#include "igloo/igloo_alt.h"
using namespace igloo;

#include <algorithm>
// condition: the final word in sentence is punctation
void reverseSentences(std::string& text) {
  std::reverse(text.begin(), text.end() );
  auto wordEnd = text.begin();
  while(wordEnd != text.end() ) {
    // new method copy from july100_interview
    while(*wordEnd == ' ' && wordEnd != text.end() ) {//check the whitspaces
      ++wordEnd;
    }
    auto wordBegin = wordEnd;// new word beginning
    while(*wordEnd != ' ' && wordEnd != text.end() ) {//loop through the whole word
      ++wordEnd;
    }
    std::reverse(wordBegin, wordEnd);// reverse second argument means the iterator past the word end
  }
}

Describe(reverse_english_sentence) {
  It(end_with_whitespace) {
    std::string textString = "life isn't that easy ";
    reverseSentences(textString);
    AssertThat(textString, Is().EqualTo(" easy that isn't life") );
  }
  It(separated_with_one_more_whitespace) {
    std::string textString = "where should I    find another better result";
    reverseSentences(textString);
    AssertThat(textString, Is().EqualTo("result better another find    I should where") );
  }
};
