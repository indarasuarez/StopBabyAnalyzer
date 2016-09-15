#ifndef STOPUTILS_H
#define STOPUTILS_H
#include "TString.h"
#include <vector>
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
#include "TVector3.h"
#include <functional>
#include <list>
#include <algorithm>
#include <utility>
#include <assert.h>
#include "CNumBase.h"


using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
bool _isZnunu();
bool _is1lep();
bool _is1lep_fromTop();
bool _is1lep_notfromTop();
bool _is2lep();
   float calculateMt(const LorentzVector p4, double met, double met_phi);
   double getBinomialUncertainty (double num, double den);
   double getSignificance_SoverSqrtB(int type, double signal, double background, double bkg_unc);
   double getSigUncertainty (double sig, double bg, double sigmabg);
   double calculateZbi(double signal, double bkg, double unc);
//CNumBase<float> calculateZbi(CNumBase<float> signal, CNumBase<float> bkg, double unc);
   float getMinDphi(float metPhi, LorentzVector vec1, LorentzVector vec2,LorentzVector vec3,LorentzVector vec4 );
   float getdphi( float phi1 , float phi2 );
   bool passtrackveto();
   bool passMT2trackveto();
   bool passLepIso(float iso, float pt);
   int GetNGoodJets();
   int GetATLASGoodJets2();
   int GetATLASGoodJets();
   int GetATLASGoodJets3();
   int GetNGoodBJets();
   int HFJets();
   float trackIso(int thisPf, float coneR, float deltaZCut, float pT);
   bool passtrackveto_custom(float conedR, float leppT_thresh, float hadpT_thresh, float isocandpT,float lepisocut, float hadisocut);
   vector<pair <int, LorentzVector>> sort_pt( vector<LorentzVector> p4_, float pt_, float DRmin_lep1obj);
   float CDF_PZeta(float MET, float MET_phi, LorentzVector p4_1, LorentzVector p4_2);
   float CDF_PZetaVis(LorentzVector p4_1, LorentzVector p4_2);
   float DPhi_W_lep(float MET, float MET_Phi, LorentzVector p4);
   float WpT(float MET, float MET_Phi, LorentzVector p4);
   bool EMFracVeto();
   bool passMockMuTrigger();
   bool passMockElTrigger();
   bool isbadEcalEvent();
   int getOverlappingJetIndex(LorentzVector lep_, vector<LorentzVector> jets_, double dR);
   LorentzVector leadingGoodJetp4();
   LorentzVector getMHT(vector<LorentzVector> jets_,float pt, float eta);
   float getMHTSig();
   pair<float,float> newmet();
   int getBkgType();
   int getStopDecayMode();
   bool isT2bt();
   bool isT2tt();
   bool isT2bW();
   float GetHFWeight(float hfweight);
double metSF(bool central,bool up, bool down);
bool PassATLAStauveto();
//double getTTbarSysPtSF(bool ttbar, bool tW);
float getamt2(LorentzVector b1, LorentzVector b2, LorentzVector lep,float met, float metphi);
vector<int> JetIndexCSVsorted(vector<float> btagvalues, vector<LorentzVector > jets);
float getTTbarSysPtSF(string process);
#endif
