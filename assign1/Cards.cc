/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     Cards.cc
   NOTE
     You are asked to design this module.
     You need to draw the given number of cards and print them out.
     Assume that you are given a deck of 52 cards. The cards do not reappear.
     That is, you do not put a card back into the deck after it is drawn.
***************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include "Cards.h"
#include "AnsiPrint.h"
using namespace std;

//vector operator<< debug tool
template<typename T> ostream& operator<<(ostream& os, const vector<T>& vec) {
  os << "[";
  for(typename vector<T>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter) {
    if (iter != vec.begin()) os << ", ";
    os << *iter;
  }
  os << "]";
  return os;
}

//pair operator<< debug tool
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& iter) {
  os << "(" << iter.first << ", " << iter.second << ")";
  return os;
}

template<typename item> item getRandItem(vector<item> &v) {
    int index = rand() % v.size();
    auto iter = v.begin() + index;
    item temp = *iter;
    v.erase(iter);
    return temp;
}

color fontColor(const char L) {
  return (L == 'D' || L == 'H') ? red : black;
}

void printLine(const int lineNum, const int cardNum, const char replaceLetter) {
  if (lineNum >= kCardHeight) {
    throw "err: lineNum bigger than " + to_string(kCardHeight) + ".";
  } else if(cardNum >= kNPip) {
    throw "err: cardNum bigger than " + to_string(kNPip) + ".";
  }

  //replace "x" to specific suit
  string t = card[cardNum][lineNum];
  for (int i = 0; i < kCardWidth; i++) {
    if (t[i] == 'x') t[i] = replaceLetter;
  }
  
  AnsiPrint(t.c_str(), fontColor(replaceLetter), white);
}

void printCard(const int cardAmount) {
  vector<pair<char, int>> cardArr, deckArr;

  // initial card list
  char suits[kNSuit] = {'C', 'D', 'H', 'S'};
  for(int i = 0; i < kNSuit; i++) {
    for(int j = 0; j < kNPip; j++) {
      cardArr.emplace_back(make_pair(suits[i], j));
    }
  }

  // get random card from card list and put into deck
  for(int i = 0; i < cardAmount; i++) {
    deckArr.push_back(getRandItem(cardArr));
  }

  //print cards in deck
  for(int i = 0; i < (int(deckArr.size()) / MaxCardInOneLine + 1); i++) {
    for(int j = 0; j < kCardHeight; j++) {
      for(int k = 0; 
          k < min(MaxCardInOneLine, int(deckArr.size() - i * MaxCardInOneLine)); 
          k++) {
        printLine(j, 
                  deckArr[i * MaxCardInOneLine + k].second, 
                  deckArr[i * MaxCardInOneLine + k].first);
        cout << " ";
      }
      cout << endl;
    }
  }
}