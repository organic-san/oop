/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     QueueTest.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Dec 11, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

#include <iostream>
#include <fstream>
#include "AnsiPrint.h"

using namespace std;

/**
 * Print my id 
 */

void
PrintMyID(const char *studId) {

  char *str= new char[strlen(studId)+5];
  sprintf(str,"ID: %s",studId);
  AnsiPrint(str, yellow, red, true, true);
  cout << endl ;
  delete [] str;

}

/**
 * PrintUsage
 */

void
PrintUsage(const char *progName) {

    assert(progName);
	cout << "Usage: " << progName << " intfile [charfile]" << endl;
}

int
main(int argc, char **argv) {

	istream *is1 = &cin, *is2 = &cin;

	if (argc>3) {
		PrintUsage(argv[0]);
		exit(-1);
	} else if (argc>2) {
		is2 = new ifstream(argv[2]);
		if (!(*is2)) {
			cerr << "Can't open file " << argv[2] << endl;
			exit(1);
		}
	} 
	if (argc>1) {
		is1 = new ifstream(argv[1]);
		if (!(*is1)) {
			cerr << "Can't open file " << argv[1] << endl;
			exit(2);
		}
	}

	// You need to provide testing exercises here

	
	PrintMyID("1117030XX");
	return 0;
    
}
