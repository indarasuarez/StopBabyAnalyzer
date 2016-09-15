#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h> 

#include "badEventFilter.h"

void eventFilter::loadBadEventList( std::string listname )
{

  std::ifstream filterFile;
  filterFile.open(listname.c_str());
  unsigned long int run = 0;
  unsigned long int lumi = 0;
  unsigned long int event = 0;

  while( filterFile.good() )
	{
	  // this works with space-separated files
//	  filterFile>>run>>lumi>>event;
//	  eventList[run][lumi].insert(event);
	  

	  // a bit more complicated for : separated files
	  std::string line;
	  filterFile>>line;

	  std::istringstream linestream( line );
	  std::string w;
	  getline( linestream, w, ':');
	  run = strtoul (w.c_str(), NULL, 0);
	  getline( linestream, w, ':');
	  lumi = strtoul (w.c_str(), NULL, 0);
	  getline( linestream, w, ':');
	  event = strtoul (w.c_str(), NULL, 0);
	  //cout<<run<<" "<<lumi<<" "<<event<<endl;
	  eventList[run][lumi].insert(event);

	}

  filterFile.close();
}

bool eventFilter::eventFails( unsigned long int run, unsigned long int lumi, unsigned long int event )
{

  if( eventList.count(run) > 0 ){
	if( eventList[run].count(lumi) > 0 ){
	  if( eventList[run][lumi].count(event) > 0){
		return true;
	  }
	}
  }
  return false;

}

//Test Implemetation
void badEventFilter()
{

  eventFilter test;
  test.loadBadEventList("filterLists/muonEG.txt");
  if( test.eventFails( 208686, 97, 94333976 ) )
	std::cout<<"fail5"<<std::endl; //should not print
  if( test.eventFails( 256630, 7, 5436788 ) )
	std::cout<<"fail6"<<std::endl; //should print

}
