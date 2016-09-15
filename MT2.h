#include "TLorentzVector.h"
#include <stdlib.h>
#include <stdio.h>
//#include "lester_mt2_bisect.h"

class ComputeMT2 {
 public:
  void listparticles();
  ComputeMT2(TLorentzVector visa, TLorentzVector visb, TVector2 MET, double ma=0., double mb=0.);
  ~ComputeMT2();
  double Compute() ;
  std::pair <double,double> get_solutions();
 private:
  void Init(TLorentzVector visa, TLorentzVector visb, TVector2 MET, double ma, double mb);
  TLorentzVector V1;
  TLorentzVector V2;
  TVector2 ET;
  double Ma;
  double Mb;
  double myMT2;
  double sol1;
  double sol2; 
};
