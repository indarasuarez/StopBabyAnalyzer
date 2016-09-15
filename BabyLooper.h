#ifndef BABYLOOPER_H
#define BABYLOOPER_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "TString.h"
#include "TH1F.h"
#include <TROOT.h>
#include <TChain.h>
#include "Math/VectorUtil.h"
#include <TFile.h>
#include "badEventFilter.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2.h"
#include "CTable.h"
#include "CNumBase.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

class BTagCalibration;
class BTagCalibrationReader;

class BabyLooper {
  public :

  BabyLooper(){
  
  };

  virtual ~BabyLooper(){}

   TTree          *fChain;   //!pofloater to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   int Looper();
// TChain* chain, bool fast = true, float nEvents = -1, string skimFilePrefix = "test");
//bool fast, float nEvents, string skimFilePrefix); 

   void SetRebinFactor(int);
   void SetLumi(float);
   void SetLumiErr(float);
   void SetSignalScale(float);
   void SetSignalMassXsection(float, float);
   void SetTreeName(string);
   void SetOutputFileName(const char*);
   void SetInputFileName(const char*);
   void SetPlotStringName(char*); 
   void SetminMTCut(float theminMTCut);
   void SetmaxMTCut(float themaxMTCut);
   void SetminMT2WCut(float theminMT2WCut);
   void SetmaxMT2WCut(float themaxMT2WCut);
   void SetminModTopness(float minModTopness);
   void SetmaxMETCut(float themaxMETCut);
   void SetmaxNJetsCut(int themaxNJetsCut);
   void SetmaxNBJetsCut(int themaxNBJetsCut);
   void SetmaxNLepsCut(int themaxNLepsCut);

   void SetminMETCut(float theminMETCut);
   void SetminNJetsCut(int theminNJetsCut);
   void SetminNBJetsCut(int theminNBJetsCut);
   void SetminNLepsCut(int theminNLepsCut);

   void SetRecoLepVeto(bool therecolepveto);
   void SetIsoTrackVeto(bool theisotrackveto);
   void SetTauVeto(bool thetauveto);

   void SetCustomTCut(string CustomTCut);
   void SetLep1PtCut(float theLep1PtCut);
   void SetLep1MinEtaCut(float theLep1MinEtaCut);
   void SetLep1MaxEtaCut(float theLep1MaxEtaCut);
   void SetLep2PtCut(float theLep2PtCut);
   void SetLep2EtaCut(float theLep2EtaCut);
   void SetLep1isElectron(bool theLep1isElectron);
   void SetLep1isMuon(bool theLep1isMuon);
   void SetISRPt(float theISRPt);
   void SetChi2Cut(float theChi2Cut);
   void SetMinDPhiCut(float theMinDPhiCut);
   void SetAbsIsoCut(float theAbsIsoCut);
   void SetRelIsoCut(float theRelIsoCut);
   void SetMiniRelIsoCut(float theMiniRelIsoCut);
   void SetMETSig(float theMETSig);
   void SetDPhiWLep(float theDPhiWLep);

   void SetBtagTFSel(bool theBtagTFSel);
   void SetWJetsSelections(bool theWJetsSel);
   void SetZllSelections(bool theZllSel);
   void SetMTSelections(bool theMTSel);
   void Set0bSelections(bool the0bSel);
   void SetT2ttSelections(bool theT2ttSel);
   void SetT2btSelections(bool theT2btSel);
   void SetT2bWSelections(bool theT2bWSel);

   void FillTables(int opt,std::map< int, CNumBase<float> > tableMap,std::map< int, CNumBase<float> > tableMap_2lep,std::map< int, CNumBase<float> > tableMap_1lepfromtop,std::map< int, CNumBase<float> > tableMap_1lepnotfromtop,std::map< int, CNumBase<float> > tableMap_znunu,int ri);

   std::vector < string > _myTitles;
   std::vector < string > _myTitles_2lep;
   std::vector < string > _mySignalTitles;
   std::vector < Color_t > _myColors;
   std::vector < string > _mySigColors;

 /* Float_t         weight_btagsf;
  Float_t         weight_btagsf_heavy_UP;
  Float_t         weight_btagsf_light_UP;
  Float_t         weight_btagsf_heavy_DN;
  Float_t         weight_btagsf_light_DN;
  Float_t weight_btagsf_UP;
  Float_t weight_btagsf_DN;
*/
//  float getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim = false);
   private:
 // float getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim = false);
    eventFilter metFilterTxt;
    CTable table;
    CTable table2;

    vector<CTable> _table;
    vector<CTable> _table2;

    vector <CNumBase<float> > wjetssrmc;
    vector <CNumBase<float> > wjetscrmc;
    vector< CNumBase<float> > NCR_1l;
    vector< CNumBase<float> > Cont_1l;

    vector <CNumBase<float> > dilepsrmc;
    vector <CNumBase<float> > dilepcrmc;
    vector <CNumBase<float> > NCR_dilep;
    vector <CNumBase<float> > TotalBGmc;

    CTable table3;
    CTable table4;
    CTable table5;
    CTable table6;
     int _theRebinFactor;
     float _theLumi;
     float _theLumiErr;
     float _theMass;
     float _theXSection;
     string _theBabytree;
     const char* _theOutputFile;
     const char* _theInputFile;
     char* _thePlotStringName;
     float _theSignalScale;   
     float _theminMTCut;
     float _themaxMTCut;
     float _minModTopness;

     float _theminMETCut;
     int _theminNJetsCut;
     int _theminNBJetsCut;
     int _theminNLepsCut;

     float _themaxMETCut;
     int _themaxNJetsCut;
     int _themaxNBJetsCut;
     int _themaxNLepsCut;

     bool _therecolepveto;
     bool _theisotrackveto;
     bool _thetauveto;

     string _theCustomTCut;
     float _theLep1PtCut;
     float _theLep1MinEtaCut;
     float _theLep1MaxEtaCut;
     float _theLep2PtCut;
     float _theLep2EtaCut;
     bool _theLep1isElectron;
     bool _theLep1isMuon;
     float _theISRPt;
     float _theMinDPhiCut;
     float _theChi2Cut;
     float _theAbsIsoCut;
     float _theRelIsoCut;
     float _theMiniRelIsoCut;
     float _theminMT2WCut;
     float _themaxMT2WCut;
     float _theMETSig;
     float _theDPhiWLep;
  
     bool _theBtagTFSel;
     bool _theZllSelec;
     bool _theWJetsSelec;
     bool _theMTSelec;
     bool _the0bSelec;
     bool _theT2ttSelec;
     bool _theT2btSelec;
     bool _theT2bWSelec;
 
     std::map<float, string> _theNameMap;            
     std::map<float, float> _theScalesMap;

     std::map<float, std::vector<string>> _theCutsVectorMap;
     std::map<float, std::vector<float>> _theCutFlowVectorMap;
     std::map<float, std::vector<float>> _theCutFlowVectorMap_2lep;
std::map<float, std::vector<float>> _theCutFlowVectorMap_Dilep;
std::map<float, std::vector<float>> _theCutFlowVectorMap_SingleLep_notfromtop ;
std::map<float, std::vector<float>> _theCutFlowVectorMap_SingleLep_fromtop ;
std::map<float, std::vector<float>> _theCutFlowVectorMap_Znunu ;

     std::vector<std::string> _theRootFiles;

     void GetTheFiles();
     void clearEventCounters();
     void GetCutFlowTable(int process);
     void ClearCutFlowVectors(int process);
     void Syncing();    

     bool passSelections(int process);
     bool passATLASSelections_bC2xDiag(int process);
     bool passATLASSelections_lowDM(int process);
     bool passATLASSelections_SR1(int process);
     bool passZSelections(int process);
     bool pass0bSelections(int process);
     bool passMTSelections(int process);
     bool passT2ttSelections(int process);
     bool passT2ttSelections_bu(int process);
     bool passT2btSelections(int process);
     bool passT2bWSelections(int process);
     bool passPreSelections(int process);
     bool pass0bCRSelections();
     bool passDilepSelections();
     bool passSRSelections(int process);
 
  ofstream myfile;

  int rare;

    int count_wjets;
    int count_st;
    int count_ttbar_1lep;
    int count_ttbar_2lep;
    int count_ttbar;
    int count_rare;
    int count_data;

  float nEventsTotal;
  float nEventsPass;
  float nEventsPass_1b;
  float nEventsTotal_2lep;
  float nEventsPass_2lep;
  float nEventsPass_2lep_1b;
  float nEvents_MT2W;
  float nEvents_MT2W_2lep;
  float nEvents_MinDPhi;
  float nEvents_MinDPhi_2lep;
  float nEvents_Chi2;
  float nEvents_Chi2_2lep;
  float nEvents_TauVeto_2lep;
  float nEvents_TauVeto;
  float nEvents_RecoLepVeto;
  float nEvents_RecoLepVeto_2lep;
  float nEvents_TrackVeto_2lep;
  float nEvents_TrackVeto;
  float nEvents_NBtags_2lep;
  float nEvents_NBtags;
  float nEvents_NJets_2lep;
  float nEvents_NJets;
  float nEvents_MT_2lep;
  float nEvents_MT;
  float nEvents_Met_2lep;
  float nEvents_Met;
  float nEvents_LepIso_2lep;
  float nEvents_LepIso;
  float nEvents_LepID_2lep;
  float nEvents_LepID;
  float nEvents_LepPt_2lep;
  float nEvents_LepPt;
  float nEvents_LepEta_2lep;
  float nEvents_LepEta;
  float nEvents_NGoodLep_2lep;
  float nEvents_NGoodLep;
  float nEvents_vtx_2lep;
  float nEvents_vtx;
  float nEvents_ExactlyNGoodLep_2lep;
  float nEvents_ExactlyNGoodLep;
  float nEvents_LepType_2lep;
  float nEvents_LepType;

  float nEventsTriggers;
  float nEventsFilters;
  float nEventsTriggers_2lep;
  float nEventsFilters_2lep;

  float nEvents_METSig;
  float nEvents_METSig_2lep;
  float nEvents_DPhiWLep;
  float nEvents_DPhiWLep_2lep;

  float nEventsPass_Znunu_SR;
  float nEventsPass_2lep_SR;
  float nEventsPass_1lepfromtop_SR;
  float nEventsPass_1lepnotfromtop_SR;

  float nEventsPass_Znunu_0bCR;
  float nEventsPass_2lep_0bCR;
  float nEventsPass_1lepfromtop_0bCR;
  float nEventsPass_1lepnotfromtop_0bCR;

  float nEventsPass_Znunu_2lCR;
  float nEventsPass_2lep_2lCR;
  float nEventsPass_1lepfromtop_2lCR;
  float nEventsPass_1lepnotfromtop_2lCR;

  float nEventsPass_2lCR;
  float nEventsPass_0bCR;
  float nEventsPass_SR;

  float nEventsTotal_Znunu;
  float nEventsPass_Znunu;
  float nEventsPass_Znunu_1b;
  float nEvents_MT2W_Znunu;
  float nEvents_MinDPhi_Znunu;
  float nEvents_Chi2_Znunu;
  float nEvents_TauVeto_Znunu;
  float nEvents_RecoLepVeto_Znunu;
  float nEvents_TrackVeto_Znunu;
  float nEvents_NBtags_Znunu;
  float nEvents_NJets_Znunu;
  float nEvents_MT_Znunu;
  float nEvents_Met_Znunu;
  float nEvents_LepIso_Znunu;
  float nEvents_LepID_Znunu;
  float nEvents_LepPt_Znunu;
  float nEvents_LepEta_Znunu;
  float nEvents_NGoodLep_Znunu;
  float nEvents_vtx_Znunu;
  float nEvents_ExactlyNGoodLep_Znunu;
  float nEvents_LepType_Znunu;
  float nEvents_METSig_Znunu;
  float nEvents_DPhiWLep_Znunu;
  float nEventsTriggers_Znunu;
  float nEventsFilters_Znunu;

  float nEventsTotal_1lepfromtop;
  float nEventsPass_1lepfromtop;
  float nEventsPass_1lepfromtop_1b;
  float nEvents_MT2W_1lepfromtop;
  float nEvents_MinDPhi_1lepfromtop;
  float nEvents_Chi2_1lepfromtop;
  float nEvents_TauVeto_1lepfromtop;
  float nEvents_RecoLepVeto_1lepfromtop;
  float nEvents_TrackVeto_1lepfromtop;
  float nEvents_NBtags_1lepfromtop;
  float nEvents_NJets_1lepfromtop;
  float nEvents_MT_1lepfromtop;
  float nEvents_Met_1lepfromtop;
  float nEvents_LepIso_1lepfromtop;
  float nEvents_LepID_1lepfromtop;
  float nEvents_LepPt_1lepfromtop;
  float nEvents_LepEta_1lepfromtop;
  float nEvents_NGoodLep_1lepfromtop;
  float nEvents_vtx_1lepfromtop;
  float nEvents_ExactlyNGoodLep_1lepfromtop;
  float nEvents_LepType_1lepfromtop;
  float nEvents_METSig_1lepfromtop;
  float nEvents_DPhiWLep_1lepfromtop;
  float nEventsTriggers_1lepfromtop;
  float nEventsFilters_1lepfromtop;

  float nEventsTotal_1lepnotfromtop;
  float nEventsPass_1lepnotfromtop;
  float nEventsPass_1lepnotfromtop_1b;
  float nEvents_MT2W_1lepnotfromtop;
  float nEvents_MinDPhi_1lepnotfromtop;
  float nEvents_Chi2_1lepnotfromtop;
  float nEvents_TauVeto_1lepnotfromtop;
  float nEvents_RecoLepVeto_1lepnotfromtop;
  float nEvents_TrackVeto_1lepnotfromtop;
  float nEvents_NBtags_1lepnotfromtop;
  float nEvents_NJets_1lepnotfromtop;
  float nEvents_MT_1lepnotfromtop;
  float nEvents_Met_1lepnotfromtop;
  float nEvents_LepIso_1lepnotfromtop;
  float nEvents_LepID_1lepnotfromtop;
  float nEvents_LepPt_1lepnotfromtop;
  float nEvents_LepEta_1lepnotfromtop;
  float nEvents_NGoodLep_1lepnotfromtop;
  float nEvents_vtx_1lepnotfromtop;
  float nEvents_ExactlyNGoodLep_1lepnotfromtop;
  float nEvents_LepType_1lepnotfromtop;
  float nEvents_METSig_1lepnotfromtop;
  float nEvents_DPhiWLep_1lepnotfromtop;
  float nEventsTriggers_1lepnotfromtop;
  float nEventsFilters_1lepnotfromtop;

  int lep2_nels;
  int lep2_nmus;
  int lep2_nleptauels;
  int lep2_nleptaumus;
  int lep2_nth_1prong;
  int lep2_nth_3prong;

  int lep2_nels_cracks;
  int lep2_nmus_cracks;
  int lep2_nleptauels_cracks;
  int lep2_nleptaumus_cracks; 
 int lep2_nth_1prong_cracks;
  int lep2_nth_3prong_cracks;

  // for btag SFs
  BTagCalibration* calib;
  BTagCalibrationReader* reader_heavy;
  BTagCalibrationReader* reader_heavy_UP;
  BTagCalibrationReader* reader_heavy_DN;
  BTagCalibrationReader* reader_light;
  BTagCalibrationReader* reader_light_UP;
  BTagCalibrationReader* reader_light_DN;

  TH2D* h_btag_eff_b;
  TH2D* h_btag_eff_c;
  TH2D* h_btag_eff_udsg;

  TH2D* h_btag_eff_b_fastsim;
  TH2D* h_btag_eff_c_fastsim;
  TH2D* h_btag_eff_udsg_fastsim;
  float getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim = false);

};

#endif
