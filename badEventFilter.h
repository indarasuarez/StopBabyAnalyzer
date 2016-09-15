#include <map>
#include <set>
#include <iostream>
#include <fstream>

#ifndef BADEVENTFILTER_H
#define BADEVENTFILTER_H

class eventFilter{

private:

  std::map <unsigned long int, std::map<unsigned long int, std::set<unsigned long int> > > eventList;

public:

  void loadBadEventList( std::string listname );
  bool eventFails( unsigned long int run, unsigned long int lumi, unsigned long int event );

};

#endif
