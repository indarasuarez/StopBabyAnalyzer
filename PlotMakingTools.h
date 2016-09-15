#ifndef MAKEPLOTTOOLS_H
#define MAKEPLOTTOOLS_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"
#include "TChain.h"
#include "TCut.h"
#include "TROOT.h"
#include "TColor.h"

//Parse Parameters from options input string
std::vector <std::string> GetParms(std::string blah);

//Turn parsed argument from string into const char*.  Remove leading and trailing whitespace
std::string getString(std::string initial, std::string result);

#endif
