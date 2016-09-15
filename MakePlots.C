#include "iostream"
#include <string> 
#include "TChain.h"

#include "BabyLooper.h"  

using namespace std;

int main(int argc, char **argv){

  char *channel = argv[1];
  char *etaregion = argv[2];
  char *metType = argv[3];
//  char *njets = argv[4];
  char *CR = argv[4];

  BabyLooper babylooper;

//file with baby paths
  babylooper.SetInputFileName("babyfiles_ATLAS.dat");

//general settings
  babylooper.SetOutputFileName("Plots.root");
  babylooper.SetSignalScale(10);
  babylooper.SetRebinFactor(1);
  babylooper.SetLumi(12.9); //191.169 (/nb)

//baseline
  babylooper.SetminMTCut(170.);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250.);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminMT2WCut(200.);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(999999);
  babylooper.SetminNBJetsCut(1);
  babylooper.SetmaxNBJetsCut(99999);
  babylooper.SetminNLepsCut(1);
  babylooper.SetmaxNLepsCut(1);
  babylooper.SetMinDPhiCut(0.8);
  babylooper.SetMiniRelIsoCut(0.1);
  babylooper.SetRecoLepVeto(true);
  babylooper.SetIsoTrackVeto(true);
  babylooper.SetTauVeto(true);
  babylooper.SetBtagTFSel(true);
//othercuts
  babylooper.SetminModTopness(-99999);
  babylooper.SetMETSig(0.);
  babylooper.SetDPhiWLep(0.);
  babylooper.SetCustomTCut("");
  babylooper.SetISRPt(200.);
  babylooper.SetChi2Cut(0.);
  babylooper.SetAbsIsoCut(9999.);
  babylooper.SetRelIsoCut(9999.);

  if(strcmp (CR,"ATLAS_bC2xDiag") == 0) {
//baseline
  babylooper.SetminMTCut(170.);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(230.);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminMT2WCut(0.);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(999999);
  babylooper.SetminNBJetsCut(2);
  babylooper.SetmaxNBJetsCut(99999);
  babylooper.SetminNLepsCut(1);
  babylooper.SetmaxNLepsCut(1);
  babylooper.SetMinDPhiCut(0.4);
  babylooper.SetMiniRelIsoCut(0.1);
  babylooper.SetRecoLepVeto(true);
  babylooper.SetIsoTrackVeto(false);
  babylooper.SetTauVeto(true);
  babylooper.SetBtagTFSel(true);
//othercuts
  babylooper.SetminModTopness(-99999);
  }

  if(strcmp (CR,"ATLAS_lowDM") == 0) {
//baseline
  babylooper.SetminMTCut(120.);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(300.);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminMT2WCut(0.);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(999999);
  babylooper.SetminNBJetsCut(1);
  babylooper.SetmaxNBJetsCut(99999);
  babylooper.SetminNLepsCut(1);
  babylooper.SetmaxNLepsCut(1);
  babylooper.SetMinDPhiCut(0.4);
  babylooper.SetMiniRelIsoCut(0.1);
  babylooper.SetRecoLepVeto(false);
  babylooper.SetIsoTrackVeto(false);
  babylooper.SetTauVeto(true);
  babylooper.SetBtagTFSel(true);
//othercuts
  babylooper.SetminModTopness(-99999);
  }

  if(strcmp (CR,"ATLAS_SR1") == 0) {
//baseline
  babylooper.SetminMTCut(170.);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(260.);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminMT2WCut(0.);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(999999);
  babylooper.SetminNBJetsCut(1);
  babylooper.SetmaxNBJetsCut(99999);
  babylooper.SetminNLepsCut(1);
  babylooper.SetmaxNLepsCut(1);
  babylooper.SetMinDPhiCut(0.4);
  babylooper.SetMiniRelIsoCut(0.1);
  babylooper.SetRecoLepVeto(true);
  babylooper.SetIsoTrackVeto(false);
  babylooper.SetTauVeto(true);
  babylooper.SetBtagTFSel(true);
//othercuts
  babylooper.SetminModTopness(-99999);
  }

  if(strcmp (CR,"CR5_2jets") == 0) {
  babylooper.SetminMTCut(150);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(150);
  babylooper.SetmaxMETCut(250);
  babylooper.SetminNJetsCut(2);
  babylooper.SetmaxNJetsCut(2);
  babylooper.SetminMT2WCut(0);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(6.4);
  }

  if(strcmp (CR,"CR1_2jets") == 0) {
  babylooper.SetminMTCut(150);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(2);
  babylooper.SetmaxNJetsCut(2);
  babylooper.SetminMT2WCut(0);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(6.4);
  }
  if(strcmp (CR,"CR1_3jets") == 0) {
  babylooper.SetminMTCut(150);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(3);
  babylooper.SetmaxNJetsCut(3);
  babylooper.SetminMT2WCut(200);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(-9999999.);
  }
  if(strcmp (CR,"CR1_4jets") == 0) {
  babylooper.SetminMTCut(150);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(9999999);
  babylooper.SetminMT2WCut(200);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(-9999999.);
  }

  if(strcmp (CR,"CR2_2jets") == 0) {
  babylooper.SetminMTCut(0);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(2);
  babylooper.SetmaxNJetsCut(2);
  babylooper.SetminMT2WCut(0);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(6.4);
  }
  if(strcmp (CR,"CR2_3jets") == 0) {
  babylooper.SetminMTCut(0);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(3);
  babylooper.SetmaxNJetsCut(3);
  babylooper.SetminMT2WCut(200);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(-9999999.);
  }

  if(strcmp (CR,"CR2_4jets") == 0) {
  babylooper.SetminMTCut(0);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(9999999);
  babylooper.SetminMT2WCut(200);
  babylooper.SetmaxMT2WCut(99999);
  babylooper.SetminModTopness(-9999999.);
  }

  if(strcmp (CR,"SR_low_4jets") == 0) {
  babylooper.SetminMTCut(150);
  babylooper.SetmaxMTCut(99999);
  babylooper.SetminMETCut(250);
  babylooper.SetmaxMETCut(99999);
  babylooper.SetminNJetsCut(4);
  babylooper.SetmaxNJetsCut(9999999);
  babylooper.SetminMT2WCut(0);
  babylooper.SetmaxMT2WCut(200);
  babylooper.SetminModTopness(-9999999.);
  babylooper.SetminNBJetsCut(1);
  babylooper.SetmaxNBJetsCut(9999999);
  babylooper.SetBtagTFSel(false);
  }

//lepton selections
  if(strcmp (channel,"muon") == 0){
    babylooper.SetLep1isMuon(true);
    babylooper.SetLep1PtCut(35.);
    babylooper.SetLep1isElectron(false);
    babylooper.SetRelIsoCut(9999.);
    babylooper.SetMiniRelIsoCut(0.1);
  }else if(strcmp (channel,"electron") == 0){
    babylooper.SetLep1isElectron(true);
    babylooper.SetLep1PtCut(35.);
    babylooper.SetLep1isMuon(false);
    babylooper.SetRelIsoCut(9999.);
    babylooper.SetMiniRelIsoCut(0.1);
  }else{
    babylooper.SetLep1isElectron(true);
    babylooper.SetLep1isMuon(true);
    babylooper.SetLep1PtCut(20.);
    babylooper.SetLep2PtCut(20.);
  }

//lepton eta selections
  if(strcmp (etaregion,"barrel") == 0){
    babylooper.SetLep1MinEtaCut(0);
    babylooper.SetLep1MaxEtaCut(1.442);
  }else if(strcmp (etaregion,"endcap") == 0){
    babylooper.SetLep1MinEtaCut(1.556);
    babylooper.SetLep1MaxEtaCut(2.1);
//    babylooper.SetMiniRelIsoCut(0.05);
  //    babylooper.SetAbsIsoCut(4.);
  }else{
    babylooper.SetLep1MinEtaCut(0);
    babylooper.SetLep1MaxEtaCut(1.4442);
   //babylooper.SetLep1MaxEtaCut(2.1);
    babylooper.SetLep2EtaCut(2.1);
  }

  std::string RegionCuts(CR);
 //special CR selections
  if(strcmp (CR,"Zll") == 0) {
        babylooper.SetminNLepsCut(2);
        babylooper.SetmaxNLepsCut(2);
        babylooper.SetMiniRelIsoCut(0.1);
        babylooper.SetLep1PtCut(20.);
        babylooper.SetLep2PtCut(20.);
        babylooper.SetminMETCut(0);
        babylooper.SetminNBJetsCut(0);
        babylooper.SetmaxNBJetsCut(0);
        babylooper.SetRecoLepVeto(false);
        babylooper.SetIsoTrackVeto(false);
        babylooper.SetTauVeto(false);
  }

  if(strcmp (CR,"WJets") == 0){
        babylooper.SetMinDPhiCut(0);
        babylooper.SetminNJetsCut(2);
        babylooper.SetminMTCut(0.);
        babylooper.SetmaxMTCut(999999);
        babylooper.SetminMETCut(250.);
        babylooper.SetminMT2WCut(0);
        babylooper.SetminNBJetsCut(0);
        babylooper.SetmaxNBJetsCut(0);
  }

  char *plotstring = strcat(channel,etaregion);
  char *plotstring2 = strcat(plotstring,metType);

  babylooper.SetPlotStringName(strcat(plotstring2,CR));

  babylooper.Looper();

 // std::vector < TH1F* > Backgrounds, std::vector < char* > Titles,
  

  return 0;
}
