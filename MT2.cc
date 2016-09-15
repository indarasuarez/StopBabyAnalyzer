#include "MT2.h"
#include <iostream>
#include "lester_mt2_bisect.h"

using namespace std;

ComputeMT2::ComputeMT2(TLorentzVector visa, TLorentzVector visb, TVector2 MET, double ma, double mb) {
  
  Init(visa, visb, MET, ma, mb);

}

void ComputeMT2::Init(TLorentzVector visa, TLorentzVector visb, TVector2 MET, double ma, double mb) {
  
  if (V1.M() < 0 || V2.M() < 0){
    cout << "MT2 Error: Your input particles have negative mass" << endl;
    exit(1);
  }

  V1 = visa;
  V2 = visb;
  ET = MET;
  Ma = ma;
  Mb = mb;
  myMT2 = -1;
  sol1 = -1;
  sol2 = -1;

}

ComputeMT2::~ComputeMT2() {
}

double ComputeMT2::Compute()  {

    myMT2 = asymm_mt2_lester_bisect::get_mT2(V1.M(),V1.Px(),V1.Py(),V2.M(),V2.Px(),V2.Py(),ET.Px(),ET.Py(),Ma,Mb);
    sol1 = 0;
    sol2 = 0;
    return myMT2;

}
