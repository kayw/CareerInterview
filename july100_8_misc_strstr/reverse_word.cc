#include "igloo/igloo_alt.h"
using namespace igloo;

#include <algorithm>
// condition: the final word in sentence is punctation
void reverseSentences(std::string& text) {
  std::reverse(text.begin(), text.end() );
  auto wordBegin = text.begin();
  auto wordEnd = text.begin();
  while(wordEnd != text.end() ) {
    while(*wordEnd++ != ' ' && wordEnd != text.end() ); //loop until find whitespace
    auto nextWordBegin = wordEnd;
    //but wordEnd already points to the next word beginning, so decrement
    --wordEnd;
    if (*wordEnd == ' ') { // we don't need decrement when it's at end and not whitspace
      --wordEnd;
    }
    std::reverse(wordBegin, wordEnd);
    wordBegin = nextWordBegin;
    wordEnd = nextWordBegin;
  }
}

Describe(reverse_english_sentence) {
  It(end_with_whitespace) {
    std::string textString = "life isn't that easy ";
    reverseSentences(textString);
    AssertThat(textString, Is().EqualTo(" easy that isn't life") );
  }

};
