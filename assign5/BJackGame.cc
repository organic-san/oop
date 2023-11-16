/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackGame.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

using namespace std;
#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackGame.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.

BJackGame::BJackGame(BJackPlayer &bjp, BJackDealer &bjd) : menu(sizeof(menuItems)/sizeof(char *),menuItems), bjplayer(bjp), bjdealer(bjd) {
  
  over=true;
  playerCredit=dealerCredit=initCredit;
  
}

// one run of the game
// take and process a use action

bool
BJackGame::oneRun() {
  
  int choice=0;

  // main menu processing
  menu.print();
  choice=menu.getAnswer();
  switch(choice) {
  case o_more:
    moreCard();
    break;
  case o_enough:
    enough();
    break;
  case o_restart:
    restart();
    break;
  case o_quit:
    return false;
  default:
    break;
  }
  // print the cards at hand at the end of each process loop
  bjplayer.showCards();
  if (over) 
      bjdealer.openFirstCard();
  bjdealer.showCards();

  return true;

}

// give the player one more card
// check if we can do that first

void 
BJackGame::moreCard() {

  // check if it is legal to do this
  if (over) {
    cout << "Game Over" << endl;
    return;
  }

  int points=bjplayer.totalPoints(); 
  if (points<=0) {
    // the game may not have started yet
    cout << "You need to start a new game first" << endl;
  } else if (points <= 21) {
    // legal, take actions
    bjplayer.addCard(bjdealer.giveCard());
  } else {
    // you are asking too much
    cout << "You are over 21 already" << endl;
  }
}

// give the dealer enough cards to try to win the player
// determine who win the game at the end

void 
BJackGame::enough() {

  // check legality: game might be over
  if (over) {
    cout << "Game Over" << endl;
    return;
  }

  if (bjplayer.totalPoints() > 0) { 
    int total=bjplayer.totalPoints();
    // add as many cards as needed
    bjdealer.addCards(total);
    // determine who win
    switch (bjdealer.judge(total)) {
    case win:
	playerCredit += betCredit;
	dealerCredit -= betCredit;
	cout << "You win. Good job.";
	break;
    case lose:
	playerCredit -= betCredit;
	dealerCredit += betCredit;
	cout << "I win. Try again.";
	break;
    case tie: 
	cout << "It's a Tie.";
	break;
    default:
	break;
    }
    cout << "(You have " << playerCredit << " points, ";
    cout << "I have " << dealerCredit << " points.)";
    cout << endl;
    over=true;
  } else {
    // we don't have a valid game yet.
    cout << "You need to start a new game first" << endl;
  }

}

// restart the game by giving each player two new cards
void 
BJackGame::restart() {

  if (!over) {
    cout << "Game is not over yet. Choose 'enough' to end a game" << endl;
    return;
  }
  // restart the game if both sides have positive credits
    if ((playerCredit <=0) || (dealerCredit <=0)) {
	cout << "Sorry. Game over. No loan here." << endl;
	return;
    }
  // since the dealer needs to check for enough cards,
  // the start() function for the dealer class needs to be called 
  // before the player class
  bjdealer.start();
  bjplayer.start();
  // first run
  bjplayer.addCard(bjdealer.giveCard());
  bjdealer.addCard();
  // second run
  bjplayer.addCard(bjdealer.giveCard());
  bjdealer.addCard();
  // view the first card
  bjplayer.openFirstCard();
  over=false;

}

