 #include "BasicHistos.h"
// C++
#include <iostream>
#include <fstream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TCut.h"
#include "dataMCplotMaker.h"
#include "PlotMaker2D.h"
#include "TVector3.h"

#include "stoputils.h"
#include "BasicHistos.h"

#include "CTable.h"
#include "CNumBase.h"

// StopCMS3
#include "StopCMS3.h"

using namespace std;
using namespace stoptas;

void BasicHistos::BookVariable(){
   //* 
  float xlow[6] = {250,350,450,550,650,800};
  data = new TH1F("data","data",5,xlow);
  wjets = new TH1F("wjets","wjets",5,xlow);
  onelep = new TH1F("onelep","onelep",5,xlow);
  znunu = new TH1F("znunu","znunu",5,xlow);
 twolep = new TH1F("twolep","twolep",5,xlow);
/*/
  float xlow[4] = {250,350,450,800};
  data = new TH1F("data","data",3,xlow);
  wjets = new TH1F("wjets","wjets",3,xlow);
  onelep = new TH1F("onelep","onelep",3,xlow);
  znunu = new TH1F("znunu","znunu",3,xlow);
 twolep = new TH1F("twolep","twolep",3,xlow);
/* / 
//  float xlow[3] = {250,325,800};
  float xlow[3] = {250,350,800};
  data = new TH1F("data","data",2,xlow);
  wjets = new TH1F("wjets","wjets",2,xlow);
  onelep = new TH1F("onelep","onelep",2,xlow);
  znunu = new TH1F("znunu","znunu",2,xlow);
 twolep = new TH1F("twolep","twolep",2,xlow);


/*float xlow[3] = {0,1,6};
  data = new TH1F("data","data",2,xlow);
  wjets = new TH1F("wjets","wjets",2,xlow);
  wjets_err=new TH1F("wjets_err","wjets_err",2,xlow);
  onelep = new TH1F("onelep","onelep",2,xlow);
  onelep_err = new TH1F("onelep_err","onelep_err",2,xlow);
  znunu = new TH1F("znunu","znunu",2,xlow);
  znunu_err = new TH1F("znunu_err","znunu_err",2,xlow);
 twolep = new TH1F("twolep","twolep",2,xlow);
 twolep_err = new TH1F("twolep_err","twolep_err",2,xlow);
*/
}
void BasicHistos::BS(string label, float Lumi){
  data->SetBinContent(1,met_data->Integral(0,12));
  data->SetBinContent(2,met_data->Integral(13,16));
  data->SetBinContent(3,met_data->Integral(17,20));
  data->SetBinContent(4,met_data->Integral(21,24));
  data->SetBinContent(5,met_data->Integral(25,25));
cout<<"Data 250-350  "<<met_data->Integral(0,12)<<endl;
cout<<"Data 350-450  "<<met_data->Integral(13,16)<<endl;
cout<<"Data 450-inf  "<<met_data->Integral(17,25)<<endl;
  wjets->SetBinContent(1,met_SingleLep_notfromtop->Integral(0,12));
  wjets->SetBinContent(2,met_SingleLep_notfromtop->Integral(13,16));
  wjets->SetBinContent(3,met_SingleLep_notfromtop->Integral(17,20));
  wjets->SetBinContent(4,met_SingleLep_notfromtop->Integral(21,24));
  wjets->SetBinContent(5,met_SingleLep_notfromtop->Integral(25,25));

  onelep->SetBinContent(1,met_SingleLep_fromtop->Integral(0,12));
  onelep->SetBinContent(2,met_SingleLep_fromtop->Integral(13,16));
  onelep->SetBinContent(3,met_SingleLep_fromtop->Integral(17,20));
  onelep->SetBinContent(4,met_SingleLep_fromtop->Integral(21,24));
  onelep->SetBinContent(5,met_SingleLep_fromtop->Integral(25,25));

  znunu->SetBinContent(1,met_Znunu->Integral(0,12));
  znunu->SetBinContent(2,met_Znunu->Integral(13,16));
  znunu->SetBinContent(3,met_Znunu->Integral(17,20));
  znunu->SetBinContent(4,met_Znunu->Integral(21,24));
  znunu->SetBinContent(5,met_Znunu->Integral(25,25));

  twolep->SetBinContent(1,met_Dilep->Integral(0,12));
  twolep->SetBinContent(2,met_Dilep->Integral(13,16));
  twolep->SetBinContent(3,met_Dilep->Integral(17,20));
  twolep->SetBinContent(4,met_Dilep->Integral(21,24));
  twolep->SetBinContent(5,met_Dilep->Integral(25,25));
//* /
/*  data->SetBinContent(1,nbjets_data->Integral(0,1));
  data->SetBinContent(2,nbjets_data->Integral(2,7));
cout<<"Data 250-350  "<<nbjets_data->Integral(0,1)<<endl;
cout<<"Data 350-450  "<<nbjets_data->Integral(2,2)<<endl;
cout<<"Data 350-450  "<<nbjets_data->Integral(2,3)<<endl;
  wjets->SetBinContent(1,nbjets_SingleLep_notfromtop->Integral(0,1));
  wjets->SetBinContent(2,nbjets_SingleLep_notfromtop->Integral(2,7));

  wjets_err->SetBinContent(1,nbjets_SingleLep_notfromtop->Integral(0,1));
  wjets_err->SetBinContent(2,nbjets_SingleLep_notfromtop->Integral(2,7));
  wjets_err->SetBinError(1,nbjets_SingleLep_notfromtop->Integral(0,1)*0.02);
  wjets_err->SetBinError(2,nbjets_SingleLep_notfromtop->Integral(2,7)*0.16);

  onelep->SetBinContent(1,nbjets_SingleLep_fromtop->Integral(0,1));
  onelep->SetBinContent(2,nbjets_SingleLep_fromtop->Integral(2,7));
  onelep_err->Add(onelep);
  onelep_err->SetBinError(1,nbjets_SingleLep_fromtop->Integral(0,1)*0);
  onelep_err->SetBinError(2,nbjets_SingleLep_fromtop->Integral(2,7)*0);


  znunu->SetBinContent(1,nbjets_Znunu->Integral(0,1));
  znunu->SetBinContent(2,nbjets_Znunu->Integral(2,7));
  znunu->SetBinContent(3,nbjets_Znunu->Integral(3,3));
  znunu->SetBinContent(4,nbjets_Znunu->Integral(4,7));
  znunu_err->Add(znunu);
  znunu_err->SetBinError(1,nbjets_Znunu->Integral(0,1)*0);
  znunu_err->SetBinError(2,nbjets_Znunu->Integral(2,7)*0);

  twolep->SetBinContent(1,nbjets_Dilep->Integral(0,1));
  twolep->SetBinContent(2,nbjets_Dilep->Integral(2,7));
  twolep_err->Add(twolep);
  twolep_err->SetBinError(1,nbjets_Dilep->Integral(0,1)*0);
  twolep_err->SetBinError(2,nbjets_Dilep->Integral(2,7)*0);
*/
  TH1F* null = new TH1F("","",1,0,1);
  std::vector < TH1F* > nullb;
  nullb.push_back(znunu);
  nullb.push_back(onelep);
  nullb.push_back(twolep);
  nullb.push_back(wjets);
  std::vector < string > nullname;
  nullname.push_back("Z#rightarrow#nu#nu");
  nullname.push_back("1lep, from top");
  nullname.push_back(">= 2lep");
  nullname.push_back("WJets(1lep, not from top)");
  pair<TH1F*,TH1F*> znunu_err2 =make_pair(znunu,znunu_err);
  pair<TH1F*,TH1F*> onelep_err2 =make_pair(onelep,onelep_err);
  pair<TH1F*,TH1F*> twolep_err2 =make_pair(twolep,twolep_err);
  pair<TH1F*,TH1F*> wjets_err2 =make_pair(wjets,wjets_err);
  vector < pair<TH1F*,TH1F*> > nullb_err;
  nullb_err.push_back(znunu_err2);
  nullb_err.push_back(onelep_err2);
  nullb_err.push_back(twolep_err2);
  nullb_err.push_back(wjets_err2);

//--setMaximum 28 
  dataMCplotMaker(data, nullb, nullname, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2fb --xAxisLabel MET --isLinear --outputName MET_variable_%s",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors2);
//dataMCplotMaker(data, nullb_err, nullname, "", "", Form("--outOfFrame --isLinear --energy 13 --lumi %1.2fb --png --xAxisLabel Nbtags --outputName Nbtags_variable_%s",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors2);
  wjets->Reset();
  onelep->Reset();
  znunu->Reset();
  twolep->Reset();
  data->Reset();
  

}

void BasicHistos::SaveRootFile(char* name){
  //  TFile f->(_theOutputFile,"recreate");
  //      //f->.cd();
   TFile *f = new TFile(Form("%s.root",name),"recreate");
   f->cd();

   f->Add(MT_data);
   f->Add(MT2W_data);
   f->Add(Topness_data);
   f->Add(Topnessmod_data);
   f->Add(Chi2_data);
   f->Add(MinDPhi_data);
   f->Add(HTratio_data);
   f->Add(DRlepb_data);
   f->Add(leadbpt_data);
   f->Add(met_data);
   //f->Add(metphi_data);
   f->Add(leppt_data);
   f->Add(lepeta_data);
   f->Add(lepphi_data);
   f->Add(HT_data);
   f->Add(njets_data);
   f->Add(nbjets_data);
   f->Add(njets_pt200_nobtags_data);
   f->Add(leadISRjet_pt200_nobtags_data);
   f->Add(METoverSqrtHT_data);
   f->Add(Mlepb_data);
   f->Add(genMlepb_data);
   f->Add(M3b_data);
   f->Add(jetpt_data);
   f->Add(DPhiLepJet_data);
   f->Add(leadjetpt_data);
   f->Add(DPhiWLep_data);
   f->Add(PZeta_TrkLep_data);
   f->Add(PZetaVis_TrkLep_data);
   f->Add(ak4_nef_data);
   f->Add(ak4_cef_data);
   f->Add(ak4_EF_data);

   f->Add(MT_Dilep);
   f->Add(MT2W_Dilep);
   f->Add(Topness_Dilep);
   f->Add(Topnessmod_Dilep);
   f->Add(Chi2_Dilep);
   f->Add(MinDPhi_Dilep);
   f->Add(HTratio_Dilep);
   f->Add(DRlepb_Dilep);
   f->Add(leadbpt_Dilep);
   f->Add(met_Dilep);
   //f->Add(metphi_Dilep);
   f->Add(leppt_Dilep);
   f->Add(lepeta_Dilep);
   f->Add(lepphi_Dilep);
   f->Add(HT_Dilep);
   f->Add(njets_Dilep);
   f->Add(nbjets_Dilep);
   f->Add(njets_pt200_nobtags_Dilep);
   f->Add(leadISRjet_pt200_nobtags_Dilep);
   f->Add(METoverSqrtHT_Dilep);
   f->Add(Mlepb_Dilep);
   f->Add(genMlepb_Dilep);
   f->Add(M3b_Dilep);
   f->Add(jetpt_Dilep);
   f->Add(DPhiLepJet_Dilep);
   f->Add(leadjetpt_Dilep);
   f->Add(DPhiWLep_Dilep);
   f->Add(PZeta_TrkLep_Dilep);
   f->Add(PZetaVis_TrkLep_Dilep);
   f->Add(ak4_nef_Dilep);
   f->Add(ak4_cef_Dilep);
   f->Add(ak4_EF_Dilep);

   f->Add(MT_SingleLep_notfromtop);
   f->Add(MT2W_SingleLep_notfromtop);
   f->Add(Topness_SingleLep_notfromtop);
   f->Add(Topnessmod_SingleLep_notfromtop);
   f->Add(Chi2_SingleLep_notfromtop);
   f->Add(MinDPhi_SingleLep_notfromtop);
   f->Add(HTratio_SingleLep_notfromtop);
   f->Add(DRlepb_SingleLep_notfromtop);
   f->Add(leadbpt_SingleLep_notfromtop);
   f->Add(met_SingleLep_notfromtop);
//   f->Add(metphi_SingleLep_notfromtop);
   f->Add(leppt_SingleLep_notfromtop);
   f->Add(lepeta_SingleLep_notfromtop);
   f->Add(lepphi_SingleLep_notfromtop);
   f->Add(HT_SingleLep_notfromtop);
   f->Add(njets_SingleLep_notfromtop);
   f->Add(nbjets_SingleLep_notfromtop);
   f->Add(njets_pt200_nobtags_SingleLep_notfromtop);
   f->Add(leadISRjet_pt200_nobtags_SingleLep_notfromtop);
   f->Add(METoverSqrtHT_SingleLep_notfromtop);
   f->Add(Mlepb_SingleLep_notfromtop);
   f->Add(genMlepb_SingleLep_notfromtop);
   f->Add(M3b_SingleLep_notfromtop);
   f->Add(jetpt_SingleLep_notfromtop);
   f->Add(DPhiLepJet_SingleLep_notfromtop);
   f->Add(leadjetpt_SingleLep_notfromtop);
   f->Add(DPhiWLep_SingleLep_notfromtop);
   f->Add(PZeta_TrkLep_SingleLep_notfromtop);
   f->Add(PZetaVis_TrkLep_SingleLep_notfromtop);
   f->Add(ak4_nef_SingleLep_notfromtop);
   f->Add(ak4_cef_SingleLep_notfromtop);

  TH1F* null = new TH1F("","",1,0,1);
  std::vector < TH1F* > nullb;
  nullb.push_back(eventswithb_met_notfromtop);
  nullb.push_back(eventswithc_met_notfromtop);
  nullb.push_back(eventswithlf_met_notfromtop);
  std::vector < string > nullname;
  nullname.push_back("Events with b-quarks");
  nullname.push_back("Events with c-quarks");
  nullname.push_back("Events with LF");

  double norm = eventswithb_met_notfromtop->Integral() + eventswithc_met_notfromtop->Integral() + eventswithlf_met_notfromtop->Integral();
  eventswithb_met_notfromtop->Scale(1./norm);
  eventswithc_met_notfromtop->Scale(1./norm);
  eventswithlf_met_notfromtop->Scale(1./norm);

 // eventswithb_met_notfromtop->Scale(1./eventswithb_met_notfromtop->Integral() );
 // eventswithc_met_notfromtop->Scale(1./eventswithc_met_notfromtop->Integral() );
 // eventswithlf_met_notfromtop->Scale(1./eventswithlf_met_notfromtop->Integral());
//--normalize 

  dataMCplotMaker(null, nullb, nullname, "", "",Form("--setMinimum 0.01 --energy 13 --lumi 3.99 fb --png --xAxisLabel MET --yAxisLabel fraction of total events --outputName partoncontent_log_%s",name));
  dataMCplotMaker(null, nullb, nullname, "", "",Form("--isLinear --energy 13 --lumi 3.99 fb --png --xAxisLabel MET --yAxisLabel fraction of total events --outputName partoncontent_%s",name));

   f->Add(ak4_EF_SingleLep_notfromtop);

   f->Add(eventswithb_met_notfromtop);
   f->Add(eventswithc_met_notfromtop);
   f->Add(eventswithlf_met_notfromtop);

   cout<<"Events with bs "<<eventswithb_met_notfromtop->Integral();
   cout<<"Events with cs "<<eventswithc_met_notfromtop->Integral();
   cout<<"Events with LF "<<eventswithlf_met_notfromtop->Integral();

   f->Add(MT_SingleLep_fromtop);
   f->Add(MT2W_SingleLep_fromtop);
   f->Add(Topness_SingleLep_fromtop);
   f->Add(Topnessmod_SingleLep_fromtop);
   f->Add(Chi2_SingleLep_fromtop);
   f->Add(MinDPhi_SingleLep_fromtop);
   f->Add(HTratio_SingleLep_fromtop);
   f->Add(DRlepb_SingleLep_fromtop);
   f->Add(leadbpt_SingleLep_fromtop);
   f->Add(met_SingleLep_fromtop);
  // f->Add(metphi_SingleLep_fromtop);
   f->Add(leppt_SingleLep_fromtop);
   f->Add(lepeta_SingleLep_fromtop);
   f->Add(lepphi_SingleLep_fromtop);
   f->Add(HT_SingleLep_fromtop);
   f->Add(njets_SingleLep_fromtop);
   f->Add(nbjets_SingleLep_fromtop);
   f->Add(njets_pt200_nobtags_SingleLep_fromtop);
   f->Add(leadISRjet_pt200_nobtags_SingleLep_fromtop);
   f->Add(METoverSqrtHT_SingleLep_fromtop);
   f->Add(Mlepb_SingleLep_fromtop);
   f->Add(genMlepb_SingleLep_fromtop);
   f->Add(M3b_SingleLep_fromtop);
   f->Add(jetpt_SingleLep_fromtop);
   f->Add(DPhiLepJet_SingleLep_fromtop);
   f->Add(leadjetpt_SingleLep_fromtop);
   f->Add(DPhiWLep_SingleLep_fromtop);
   f->Add(PZeta_TrkLep_SingleLep_fromtop);
   f->Add(PZetaVis_TrkLep_SingleLep_fromtop);
   f->Add(ak4_nef_SingleLep_fromtop);
   f->Add(ak4_cef_SingleLep_fromtop);
   f->Add(ak4_EF_SingleLep_fromtop);

   f->Add(MT_Znunu);
   f->Add(MT2W_Znunu);
   f->Add(Topness_Znunu);
   f->Add(Topnessmod_Znunu);
   f->Add(Chi2_Znunu);
   f->Add(MinDPhi_Znunu);
   f->Add(HTratio_Znunu);
   f->Add(DRlepb_Znunu);
   f->Add(leadbpt_Znunu);
   f->Add(met_Znunu);
//   f->Add(metphi_Znunu);
   f->Add(leppt_Znunu);
   f->Add(lepeta_Znunu);
   f->Add(lepphi_Znunu);
   f->Add(HT_Znunu);
   f->Add(njets_Znunu);
   f->Add(nbjets_Znunu);
   f->Add(njets_pt200_nobtags_Znunu);
   f->Add(leadISRjet_pt200_nobtags_Znunu);
   f->Add(METoverSqrtHT_Znunu);
   f->Add(Mlepb_Znunu);
   f->Add(genMlepb_Znunu);
   f->Add(M3b_Znunu);
   f->Add(jetpt_Znunu);
   f->Add(DPhiLepJet_Znunu);
   f->Add(leadjetpt_Znunu);
   f->Add(DPhiWLep_Znunu);
   f->Add(PZeta_TrkLep_Znunu);
   f->Add(PZetaVis_TrkLep_Znunu);
   f->Add(ak4_nef_Znunu);
   f->Add(ak4_cef_Znunu);
   f->Add(ak4_EF_Znunu);
  //Write();
  //
  f->Write();
  //delete f;
}

void BasicHistos::BookSRHistos_bg(){
       MT_1lep = new TH1F("MT_1lep","MT_1lep",12,0,600);
       MT2W_1lep = new TH1F("MT2W_1lep","MT2W_1lep",18,50,500);
       Topness_1lep = new TH1F("Topness_1lep","Topness_1lep",18,50,500);
       Topnessmod_1lep = new TH1F("Topnessmod_1lep","Topnessmod_1lep",20,-5,15);
       Chi2_1lep = new TH1F("Chi2_1lep","Chi2_1lep",20,0,20);
       MinDPhi_1lep = new TH1F("MinDPhi_1lep","MinDPhi_1lep",20,0,4);
       HTratio_1lep = new TH1F("HTratio_1lep","HTratio_1lep",20,0,1);
       DRlepb_1lep= new TH1F("DRlepb_1lep","DRlepb_1lep",20,0,5);
       leadbpt_1lep= new TH1F("leadbpt_1lep","leadbpt_1lep",18,30,390);
       met_1lep= new TH1F("met_1lep","met_1lep",24,50,650);
       leppt_1lep= new TH1F("leppt_1lep","leppt_1lep",26,30,680);
       lepeta_1lep= new TH1F("lepeta_1lep","lepeta_1lep",30,-3,3);
       lepphi_1lep= new TH1F("lepphi_1lep","lepphi_1lep",20,-1,1);
       HT_1lep= new TH1F("HT_1lep","HT_1lep",30,0,1500);
       njets_1lep= new TH1F("njets_1lep","njets_1lep",12,0,12);
       nbjets_1lep= new TH1F("nbjets_1lep","nbjets_1lep",6,0,6);
       njets_pt200_nobtags_1lep= new TH1F("njets_pt200_nobtags_1lep","njets_pt200_nobtags_1lep",5,0,5);
       leadISRjet_pt200_nobtags_1lep= new TH1F("leadISRjet_pt200_nobtags_1lep","leadISRjet_pt200_nobtags_1lep",24,0,600);
       METoverSqrtHT_1lep= new TH1F("METoverSqrtHT_1lep","METoverSqrtHT_1lep",20,0,40);
       Mlepb_1lep= new TH1F("Mlepb_1lep","Mlepb_1lep",24,0,600);
       genMlepb_1lep= new TH1F("genMlepb_1lep","genMlepb_1lep",24,0,600);
       M3b_1lep= new TH1F("M3b_1lep","M3b_1lep",10,0,1);
       jetpt_1lep= new TH1F("jetpt_1lep","jetpt_1lep",32,30,480);
       DPhiLepJet_1lep= new TH1F("DPhiLepJet_1lep","DPhiLepJet_1lep",20,0,4);
       leadjetpt_1lep= new TH1F("leadjetpt_1lep","leadjetpt_1lep",32,30,480);
       DPhiWLep_1lep= new TH1F("DPhiWLep_1lep","DPhiWLep_1lep",25,0,5);
       PZeta_TrkLep_1lep = new TH1F("PZeta_TrkLep_1lep","PZeta_TrkLep_1lep",60,-600,600);
       PZetaVis_TrkLep_1lep = new TH1F("PZetaVis_TrkLep_1lep","PZetaVis_TrkLep_1lep",12,0,600);
       ak4_nef_1lep = new TH1F("ak4_nef_1lep", "ak4_nef_1lep",34,30,300);
       ak4_cef_1lep = new TH1F("ak4_cef_1lep", "ak4_cef_1lep",22,30,200);
       ak4_EF_1lep = new TH1F("ak4_EFf_1lep", "ak4_EF_1lep",10,0,1.);
       Wpt_1lep = new TH1F("Wpt_1lep","Wpt_1lep",13,0,650);

       MT_ST = new TH1F("MT_ST","MT_ST",12,0,600);
       MT2W_ST = new TH1F("MT2W_ST","MT2W_ST",18,50,500);
       Topness_ST = new TH1F("Topness_ST","Topness_ST",18,50,500);
       Topnessmod_ST = new TH1F("Topnessmod_ST","Topnessmod_ST",20,-5,15);
       Chi2_ST = new TH1F("Chi2_ST","Chi2_ST",20,0,20);
       MinDPhi_ST = new TH1F("MinDPhi_ST","MinDPhi_ST",20,0,4);
       HTratio_ST = new TH1F("HTratio_ST","HTratio_ST",20,0,1);
       DRlepb_ST= new TH1F("DRlepb_ST","DRlepb_ST",20,0,5);
       leadbpt_ST= new TH1F("leadbpt_ST","leadbpt_ST",18,30,390);
       met_ST= new TH1F("met_ST","met_ST",24,50,650);
       leppt_ST= new TH1F("leppt_ST","leppt_ST",26,30,680);
       lepeta_ST= new TH1F("lepeta_ST","lepeta_ST",30,-3,3);
       lepphi_ST= new TH1F("lepphi_ST","lepphi_ST",20,-1,1);
       HT_ST= new TH1F("HT_ST","HT_ST",30,0,1500);
       njets_ST= new TH1F("njets_ST","njets_ST",12,0,12);
       nbjets_ST= new TH1F("nbjets_ST","nbjets_ST",6,0,6);
       njets_pt200_nobtags_ST= new TH1F("njets_pt200_nobtags_ST","njets_pt200_nobtags_ST",5,0,5);
       leadISRjet_pt200_nobtags_ST= new TH1F("leadISRjet_pt200_nobtags_ST","leadISRjet_pt200_nobtags_ST",24,0,600);
       METoverSqrtHT_ST= new TH1F("METoverSqrtHT_ST","METoverSqrtHT_ST",20,0,40);
       Mlepb_ST= new TH1F("Mlepb_ST","Mlepb_ST",24,0,600);
       genMlepb_ST= new TH1F("genMlepb_ST","genMlepb_ST",24,0,600);
       M3b_ST= new TH1F("M3b_ST","M3b_ST",10,0,1);
       jetpt_ST= new TH1F("jetpt_ST","jetpt_ST",32,30,480);
       DPhiLepJet_ST= new TH1F("DPhiLepJet_ST","DPhiLepJet_ST",20,0,4);
       leadjetpt_ST= new TH1F("leadjetpt_ST","leadjetpt_ST",32,30,480);
       DPhiWLep_ST= new TH1F("DPhiWLep_ST","DPhiWLep_ST",25,0,5);
       PZeta_TrkLep_ST = new TH1F("PZeta_TrkLep_ST","PZeta_TrkLep_ST",60,-600,600);
       PZetaVis_TrkLep_ST = new TH1F("PZetaVis_TrkLep_ST","PZetaVis_TrkLep_ST",12,0,600);
       ak4_nef_ST = new TH1F("ak4_nef_ST", "ak4_nef_ST",34,30,300);
       ak4_cef_ST = new TH1F("ak4_cef_ST", "ak4_cef_ST",22,30,200);
       ak4_EF_ST = new TH1F("ak4_EFf_ST", "ak4_EF_ST",10,0,1.);
       Wpt_ST = new TH1F("Wpt_ST","Wpt_ST",13,0,650);

       MT_2lep = new TH1F("MT_2lep","MT_2lep",12,0,600);
       MT2W_2lep = new TH1F("MT2W_2lep","MT2W_2lep",18,50,500);
       Topness_2lep = new TH1F("Topness_2lep","Topness_2lep",18,50,500);
       Topnessmod_2lep = new TH1F("Topnessmod_2lep","Topnessmod_2lep",20,-5,15);
       Chi2_2lep = new TH1F("Chi2_2lep","Chi2_2lep",20,0,20);
       MinDPhi_2lep = new TH1F("MinDPhi_2lep","MinDPhi_2lep",20,0,4);
       HTratio_2lep = new TH1F("HTratio_2lep","HTratio_2lep",20,0,1);
       DRlepb_2lep= new TH1F("DRlepb_2lep","DRlepb_2lep",20,0,5);
       leadbpt_2lep= new TH1F("leadbpt_2lep","leadbpt_2lep",18,30,390);
       met_2lep= new TH1F("met_2lep","met_2lep",24,50,650);
       leppt_2lep= new TH1F("leppt_2lep","leppt_2lep",26,30,680);
       lepeta_2lep= new TH1F("lepeta_2lep","lepeta_2lep",30,-3,3);
       lepphi_2lep= new TH1F("lepphi_2lep","lepphi_2lep",20,-1,1);
       HT_2lep= new TH1F("HT_2lep","HT_2lep",30,0,1500);
       njets_2lep= new TH1F("njets_2lep","njets_2lep",12,0,12);
       nbjets_2lep= new TH1F("nbjets_2lep","nbjets_2lep",6,0,6);
       njets_pt200_nobtags_2lep= new TH1F("njets_pt200_nobtags_2lep","njets_pt200_nobtags_2lep",5,0,5);
       leadISRjet_pt200_nobtags_2lep= new TH1F("leadISRjet_pt200_nobtags_2lep","leadISRjet_pt200_nobtags_2lep",24,0,600);
       METoverSqrtHT_2lep= new TH1F("METoverSqrtHT_2lep","METoverSqrtHT_2lep",20,0,40);
       Mlepb_2lep= new TH1F("Mlepb_2lep","Mlepb_2lep",24,0,600);
       genMlepb_2lep= new TH1F("genMlepb_2lep","genMlepb_2lep",24,0,600);
       M3b_2lep= new TH1F("M3b_2lep","M3b_2lep",10,0,1);
       jetpt_2lep= new TH1F("jetpt_2lep","jetpt_2lep",32,30,480);
       DPhiLepJet_2lep= new TH1F("DPhiLepJet_2lep","DPhiLepJet_2lep",20,0,4);
       leadjetpt_2lep= new TH1F("leadjetpt_2lep","leadjetpt_2lep",32,30,480);
       DPhiWLep_2lep= new TH1F("DPhiWLep_2lep","DPhiWLep_2lep",25,0,5);
       PZeta_TrkLep_2lep = new TH1F("PZeta_TrkLep_2lep","PZeta_TrkLep_2lep",60,-600,600);
       PZetaVis_TrkLep_2lep = new TH1F("PZetaVis_TrkLep_2lep","PZetaVis_TrkLep_2lep",12,0,600);
       ak4_nef_2lep = new TH1F("ak4_nef_2lep", "ak4_nef_2lep",34,30,300);
       ak4_cef_2lep = new TH1F("ak4_cef_2lep", "ak4_cef_2lep",22,30,200);
       ak4_EF_2lep = new TH1F("ak4_EFf_2lep", "ak4_EF_2lep",10,0,1.);
       Wpt_2lep = new TH1F("Wpt_2lep","Wpt_2lep",13,0,650);

       MT_wjets = new TH1F("MT_wjets","MT_wjets",12,0,600);
       MT2W_wjets = new TH1F("MT2W_wjets","MT2W_wjets",18,50,500);
       Topness_wjets = new TH1F("Topness_wjets","Topness_wjets",18,50,500);
       Topnessmod_wjets = new TH1F("Topnessmod_wjets","Topnessmod_wjets",20,-5,15);
       Chi2_wjets = new TH1F("Chi2_wjets","Chi2_wjets",20,0,20);
       MinDPhi_wjets = new TH1F("MinDPhi_wjets","MinDPhi_wjets",20,0,4);
       HTratio_wjets = new TH1F("HTratio_wjets","HTratio_wjets",20,0,1);
       DRlepb_wjets= new TH1F("DRlepb_wjets","DRlepb_wjets",20,0,5);
       leadbpt_wjets= new TH1F("leadbpt_wjets","leadbpt_wjets",18,30,390);
       met_wjets= new TH1F("met_wjets","met_wjets",24,50,650);
       leppt_wjets= new TH1F("leppt_wjets","leppt_wjets",26,30,680);
       lepeta_wjets= new TH1F("lepeta_wjets","lepeta_wjets",30,-3,3);
       lepphi_wjets= new TH1F("lepphi_wjets","lepphi_wjets",20,-1,1);
       HT_wjets= new TH1F("HT_wjets","HT_wjets",30,0,1500);
       njets_wjets= new TH1F("njets_wjets","njets_wjets",12,0,12);
       nbjets_wjets= new TH1F("nbjets_wjets","nbjets_wjets",6,0,6);
       njets_pt200_nobtags_wjets= new TH1F("njets_pt200_nobtags_wjets","njets_pt200_nobtags_wjets",5,0,5);
       leadISRjet_pt200_nobtags_wjets= new TH1F("leadISRjet_pt200_nobtags_wjets","leadISRjet_pt200_nobtags_wjets",24,0,600);
       METoverSqrtHT_wjets= new TH1F("METoverSqrtHT_wjets","METoverSqrtHT_wjets",20,0,40);
       Mlepb_wjets= new TH1F("Mlepb_wjets","Mlepb_wjets",24,0,600);
       genMlepb_wjets= new TH1F("genMlepb_wjets","genMlepb_wjets",24,0,600);
       M3b_wjets= new TH1F("M3b_wjets","M3b_wjets",10,0,1);
       jetpt_wjets= new TH1F("jetpt_wjets","jetpt_wjets",32,30,480);
       DPhiLepJet_wjets= new TH1F("DPhiLepJet_wjets","DPhiLepJet_wjets",20,0,4);
       leadjetpt_wjets= new TH1F("leadjetpt_wjets","leadjetpt_wjets",32,30,480);
       DPhiWLep_wjets= new TH1F("DPhiWLep_wjets","DPhiWLep_wjets",25,0,5);
       PZeta_TrkLep_wjets = new TH1F("PZeta_TrkLep_wjets","PZeta_TrkLep_wjets",60,-600,600);
       PZetaVis_TrkLep_wjets = new TH1F("PZetaVis_TrkLep_wjets","PZetaVis_TrkLep_wjets",12,0,600);
       ak4_nef_wjets = new TH1F("ak4_nef_wjets", "ak4_nef_wjets",34,30,300);
       ak4_cef_wjets = new TH1F("ak4_cef_wjets", "ak4_cef_wjets",22,30,200);
       ak4_EF_wjets = new TH1F("ak4_EFf_wjets", "ak4_EF_wjets",10,0,1.);
       genHT_wjets= new TH1F("genHT_wjets","genHT_wjets",500,0,2500);
       Wpt_wjets = new TH1F("Wpt_wjets","Wpt_wjets",13,0,650);

       MT_rare = new TH1F("MT_rare","MT_rare",12,0,600);
       MT2W_rare = new TH1F("MT2W_rare","MT2W_rare",18,50,500);
       Topness_rare = new TH1F("Topness_rare","Topness_rare",18,50,500);
       Topnessmod_rare = new TH1F("Topnessmod_rare","Topnessmod_rare",20,-5,15);
       Chi2_rare = new TH1F("Chi2_rare","Chi2_rare",20,0,20);
       MinDPhi_rare = new TH1F("MinDPhi_rare","MinDPhi_rare",20,0,4);
       HTratio_rare = new TH1F("HTratio_rare","HTratio_rare",20,0,1);
       DRlepb_rare= new TH1F("DRlepb_rare","DRlepb_rare",20,0,5);
       leadbpt_rare= new TH1F("leadbpt_rare","leadbpt_rare",18,30,390);
       met_rare= new TH1F("met_rare","met_rare",24,50,650);
       leppt_rare= new TH1F("leppt_rare","leppt_rare",26,30,680);
       lepeta_rare= new TH1F("lepeta_rare","lepeta_rare",30,-3,3);
       lepphi_rare= new TH1F("lepphi_rare","lepphi_rare",20,-1,1);
       HT_rare= new TH1F("HT_rare","HT_rare",30,0,1500);
       njets_rare= new TH1F("njets_rare","njets_rare",12,0,12);
       nbjets_rare= new TH1F("nbjets_rare","nbjets_rare",6,0,6);
       njets_pt200_nobtags_rare= new TH1F("njets_pt200_nobtags_rare","njets_pt200_nobtags_rare",5,0,5);
       leadISRjet_pt200_nobtags_rare= new TH1F("leadISRjet_pt200_nobtags_rare","leadISRjet_pt200_nobtags_rare",24,0,600);
       METoverSqrtHT_rare= new TH1F("METoverSqrtHT_rare","METoverSqrtHT_rare",20,0,40);
       Mlepb_rare= new TH1F("Mlepb_rare","Mlepb_rare",24,0,600);
       genMlepb_rare= new TH1F("genMlepb_rare","genMlepb_rare",24,0,600);
       M3b_rare= new TH1F("M3b_rare","M3b_rare",10,0,1);
       jetpt_rare= new TH1F("jetpt_rare","jetpt_rare",32,30,480);
       DPhiLepJet_rare= new TH1F("DPhiLepJet_rare","DPhiLepJet_rare",20,0,4);
       leadjetpt_rare= new TH1F("leadjetpt_rare","leadjetpt_rare",32,30,480);
       DPhiWLep_rare= new TH1F("DPhiWLep_rare","DPhiWLep_rare",25,0,5);
       PZeta_TrkLep_rare = new TH1F("PZeta_TrkLep_rare","PZeta_TrkLep_rare",60,-600,600);
       PZetaVis_TrkLep_rare = new TH1F("PZetaVis_TrkLep_rare","PZetaVis_TrkLep_rare",12,0,600);
       ak4_nef_rare = new TH1F("ak4_nef_rare", "ak4_nef_rare",34,30,300);
       ak4_cef_rare = new TH1F("ak4_cef_rare", "ak4_cef_rare",22,30,200);
       ak4_EF_rare = new TH1F("ak4_EFf_rare", "ak4_EF_rare",10,0,1.);
       Wpt_rare = new TH1F("Wpt_rare","Wpt_rare",13,0,650);

       MT_data = new TH1F("MT_data","MT_data",12,0,600);
       MT2W_data = new TH1F("MT2W_data","MT2W_data",18,50,500);
       Topness_data = new TH1F("Topness_data","Topness_data",18,50,500);
       Topnessmod_data = new TH1F("Topnessmod_data","Topnessmod_data",20,-5,15);
       Chi2_data = new TH1F("Chi2_data","Chi2_data",20,0,20);
       MinDPhi_data = new TH1F("MinDPhi_data","MinDPhi_data",20,0,4);
       HTratio_data = new TH1F("HTratio_data","HTratio_data",20,0,1);
       DRlepb_data= new TH1F("DRlepb_data","DRlepb_data",20,0,5);
       leadbpt_data= new TH1F("leadbpt_data","leadbpt_data",18,30,390);
       met_data= new TH1F("met_data","met_data",24,50,650);
       leppt_data= new TH1F("leppt_data","leppt_data",26,30,680);
       lepeta_data= new TH1F("lepeta_data","lepeta_data",30,-3,3);
       lepphi_data= new TH1F("lepphi_data","lepphi_data",20,-1,1);
       HT_data= new TH1F("HT_data","HT_data",30,0,1500);
       njets_data= new TH1F("njets_data","njets_data",12,0,12);
       nbjets_data= new TH1F("nbjets_data","nbjets_data",6,0,6);
       njets_pt200_nobtags_data= new TH1F("njets_pt200_nobtags_data","njets_pt200_nobtags_data",5,0,5);
       leadISRjet_pt200_nobtags_data= new TH1F("leadISRjet_pt200_nobtags_data","leadISRjet_pt200_nobtags_data",24,0,600);
       METoverSqrtHT_data= new TH1F("METoverSqrtHT_data","METoverSqrtHT_data",20,0,40);
       Mlepb_data= new TH1F("Mlepb_data","Mlepb_data",24,0,600);
       genMlepb_data= new TH1F("genMlepb_data","genMlepb_data",24,0,600);
       M3b_data= new TH1F("M3b_data","M3b_data",10,0,1);
       jetpt_data= new TH1F("jetpt_data","jetpt_data",32,30,480);
       DPhiLepJet_data= new TH1F("DPhiLepJet_data","DPhiLepJet_data",20,0,4);
       leadjetpt_data= new TH1F("leadjetpt_data","leadjetpt_data",32,30,480);
       DPhiWLep_data= new TH1F("DPhiWLep_data","DPhiWLep_data",25,0,5);
       PZeta_TrkLep_data = new TH1F("PZeta_TrkLep_data","PZeta_TrkLep_data",60,-600,600);
       PZetaVis_TrkLep_data = new TH1F("PZetaVis_TrkLep_data","PZetaVis_TrkLep_data",12,0,600);
       ak4_nef_data = new TH1F("ak4_nef_data", "ak4_nef_data",34,30,300);
       ak4_cef_data = new TH1F("ak4_cef_data", "ak4_cef_data",22,30,200);
       ak4_EF_data = new TH1F("ak4_EFf_data", "ak4_EF_data",10,0,1.);
       Wpt_data = new TH1F("Wpt_data","Wpt_data",13,0,650);

        jetPt2D_2lep = new TH2F("jetPt2D_2lep","jetPt2D_2lep",25,0,500,25,0,500);
        Mlepb2D_2lep = new TH2F("Mlepb2D_2lep","Mlepb2D_2lep",24,0,600,24,0,600);
        genMlepb2D_2lep = new TH2F("genMlepb2D_2lep","genMlepb2D_2lep",24,0,600,24,0,600);

        genHT_recoHT = new TH2F("genHT_recoHT","genHT_recoHT",30,0,1500,30,0,1500);


       MT_Dilep = new TH1F("MT_Dilep","MT_Dilep",12,0,600);
       MT2W_Dilep = new TH1F("MT2W_Dilep","MT2W_Dilep",18,50,500);
       Topness_Dilep = new TH1F("Topness_Dilep","Topness_Dilep",18,50,500);
       Topnessmod_Dilep = new TH1F("Topnessmod_Dilep","Topnessmod_Dilep",20,-5,15);
       Chi2_Dilep = new TH1F("Chi2_Dilep","Chi2_Dilep",20,0,20);
       MinDPhi_Dilep = new TH1F("MinDPhi_Dilep","MinDPhi_Dilep",20,0,4);
       HTratio_Dilep = new TH1F("HTratio_Dilep","HTratio_Dilep",20,0,1);
       DRlepb_Dilep= new TH1F("DRlepb_Dilep","DRlepb_Dilep",20,0,5);
       leadbpt_Dilep= new TH1F("leadbpt_Dilep","leadbpt_Dilep",18,30,390);
       met_Dilep= new TH1F("met_Dilep","met_Dilep",24,50,650);
       leppt_Dilep= new TH1F("leppt_Dilep","leppt_Dilep",26,30,680);
       lepeta_Dilep= new TH1F("lepeta_Dilep","lepeta_Dilep",30,-3,3);
       lepphi_Dilep= new TH1F("lepphi_Dilep","lepphi_Dilep",20,-1,1);
       HT_Dilep= new TH1F("HT_Dilep","HT_Dilep",30,0,1500);
       njets_Dilep= new TH1F("njets_Dilep","njets_Dilep",12,0,12);
       nbjets_Dilep= new TH1F("nbjets_Dilep","nbjets_Dilep",6,0,6);
       njets_pt200_nobtags_Dilep= new TH1F("njets_pt200_nobtags_Dilep","njets_pt200_nobtags_Dilep",5,0,5);
       leadISRjet_pt200_nobtags_Dilep= new TH1F("leadISRjet_pt200_nobtags_Dilep","leadISRjet_pt200_nobtags_Dilep",24,0,600);
       METoverSqrtHT_Dilep= new TH1F("METoverSqrtHT_Dilep","METoverSqrtHT_Dilep",20,0,40);
       Mlepb_Dilep= new TH1F("Mlepb_Dilep","Mlepb_Dilep",24,0,600);
       genMlepb_Dilep= new TH1F("genMlepb_Dilep","genMlepb_Dilep",24,0,600);
       M3b_Dilep= new TH1F("M3b_Dilep","M3b_Dilep",10,0,1);
       jetpt_Dilep= new TH1F("jetpt_Dilep","jetpt_Dilep",32,30,480);
       DPhiLepJet_Dilep= new TH1F("DPhiLepJet_Dilep","DPhiLepJet_Dilep",20,0,4);
       leadjetpt_Dilep= new TH1F("leadjetpt_Dilep","leadjetpt_Dilep",32,30,480);
       DPhiWLep_Dilep= new TH1F("DPhiWLep_Dilep","DPhiWLep_Dilep",25,0,5);
       PZeta_TrkLep_Dilep = new TH1F("PZeta_TrkLep_Dilep","PZeta_TrkLep_Dilep",60,-600,600);
       PZetaVis_TrkLep_Dilep = new TH1F("PZetaVis_TrkLep_Dilep","PZetaVis_TrkLep_Dilep",12,0,600);
       ak4_nef_Dilep = new TH1F("ak4_nef_Dilep", "ak4_nef_Dilep",34,30,300);
       ak4_cef_Dilep = new TH1F("ak4_cef_Dilep", "ak4_cef_Dilep",22,30,200);
       ak4_EF_Dilep = new TH1F("ak4_EFf_Dilep", "ak4_EF_Dilep",10,0,1.);
       Wpt_Dilep = new TH1F("Wpt_Dilep","Wpt_Dilep",13,0,650);

       MT_SingleLep_notfromtop = new TH1F("MT_SingleLep_notfromtop","MT_SingleLep_notfromtop",12,0,600);
       MT2W_SingleLep_notfromtop = new TH1F("MT2W_SingleLep_notfromtop","MT2W_SingleLep_notfromtop",18,50,500);
       Topness_SingleLep_notfromtop = new TH1F("Topness_SingleLep_notfromtop","Topness_SingleLep_notfromtop",18,50,500);
       Topnessmod_SingleLep_notfromtop = new TH1F("Topnessmod_SingleLep_notfromtop","Topnessmod_SingleLep_notfromtop",20,-5,15);
       Chi2_SingleLep_notfromtop = new TH1F("Chi2_SingleLep_notfromtop","Chi2_SingleLep_notfromtop",20,0,20);
       MinDPhi_SingleLep_notfromtop = new TH1F("MinDPhi_SingleLep_notfromtop","MinDPhi_SingleLep_notfromtop",20,0,4);
       HTratio_SingleLep_notfromtop = new TH1F("HTratio_SingleLep_notfromtop","HTratio_SingleLep_notfromtop",20,0,1);
       DRlepb_SingleLep_notfromtop= new TH1F("DRlepb_SingleLep_notfromtop","DRlepb_SingleLep_notfromtop",20,0,5);
       leadbpt_SingleLep_notfromtop= new TH1F("leadbpt_SingleLep_notfromtop","leadbpt_SingleLep_notfromtop",18,30,390);
       met_SingleLep_notfromtop= new TH1F("met_SingleLep_notfromtop","met_SingleLep_notfromtop",24,50,650);
       leppt_SingleLep_notfromtop= new TH1F("leppt_SingleLep_notfromtop","leppt_SingleLep_notfromtop",26,30,680);
       lepeta_SingleLep_notfromtop= new TH1F("lepeta_SingleLep_notfromtop","lepeta_SingleLep_notfromtop",30,-3,3);
       lepphi_SingleLep_notfromtop= new TH1F("lepphi_SingleLep_notfromtop","lepphi_SingleLep_notfromtop",20,-1,1);
       HT_SingleLep_notfromtop= new TH1F("HT_SingleLep_notfromtop","HT_SingleLep_notfromtop",30,0,1500);
       njets_SingleLep_notfromtop= new TH1F("njets_SingleLep_notfromtop","njets_SingleLep_notfromtop",12,0,12);
       nbjets_SingleLep_notfromtop= new TH1F("nbjets_SingleLep_notfromtop","nbjets_SingleLep_notfromtop",6,0,6);
       njets_pt200_nobtags_SingleLep_notfromtop= new TH1F("njets_pt200_nobtags_SingleLep_notfromtop","njets_pt200_nobtags_SingleLep_notfromtop",5,0,5);
       leadISRjet_pt200_nobtags_SingleLep_notfromtop= new TH1F("leadISRjet_pt200_nobtags_SingleLep_notfromtop","leadISRjet_pt200_nobtags_SingleLep_notfromtop",24,0,600);
       METoverSqrtHT_SingleLep_notfromtop= new TH1F("METoverSqrtHT_SingleLep_notfromtop","METoverSqrtHT_SingleLep_notfromtop",20,0,40);
       Mlepb_SingleLep_notfromtop= new TH1F("Mlepb_SingleLep_notfromtop","Mlepb_SingleLep_notfromtop",24,0,600);
       genMlepb_SingleLep_notfromtop= new TH1F("genMlepb_SingleLep_notfromtop","genMlepb_SingleLep_notfromtop",24,0,600);
       M3b_SingleLep_notfromtop= new TH1F("M3b_SingleLep_notfromtop","M3b_SingleLep_notfromtop",10,0,1);
       jetpt_SingleLep_notfromtop= new TH1F("jetpt_SingleLep_notfromtop","jetpt_SingleLep_notfromtop",32,30,480);
       DPhiLepJet_SingleLep_notfromtop= new TH1F("DPhiLepJet_SingleLep_notfromtop","DPhiLepJet_SingleLep_notfromtop",20,0,4);
       leadjetpt_SingleLep_notfromtop= new TH1F("leadjetpt_SingleLep_notfromtop","leadjetpt_SingleLep_notfromtop",32,30,480);
       DPhiWLep_SingleLep_notfromtop= new TH1F("DPhiWLep_SingleLep_notfromtop","DPhiWLep_SingleLep_notfromtop",25,0,5);
       PZeta_TrkLep_SingleLep_notfromtop = new TH1F("PZeta_TrkLep_SingleLep_notfromtop","PZeta_TrkLep_SingleLep_notfromtop",60,-600,600);
       PZetaVis_TrkLep_SingleLep_notfromtop = new TH1F("PZetaVis_TrkLep_SingleLep_notfromtop","PZetaVis_TrkLep_SingleLep_notfromtop",12,0,600);
       ak4_nef_SingleLep_notfromtop = new TH1F("ak4_nef_SingleLep_notfromtop", "ak4_nef_SingleLep_notfromtop",34,30,300);
       ak4_cef_SingleLep_notfromtop = new TH1F("ak4_cef_SingleLep_notfromtop", "ak4_cef_SingleLep_notfromtop",22,30,200);
       ak4_EF_SingleLep_notfromtop = new TH1F("ak4_EFf_SingleLep_notfromtop", "ak4_EF_SingleLep_notfromtop",10,0,1.);
       Wpt_SingleLep_notfromtop = new TH1F("Wpt_SingleLep_notfromtop","Wpt_SingleLep_notfromtop",13,0,650);

       eventswithb_met_notfromtop = new TH1F("eventswithb_met_notfromtop","eventswithb_met_notfromtop",3,250,550);
       eventswithc_met_notfromtop = new TH1F("eventswithc_met_notfromtop","eventswithc_met_notfromtop",3,250,550);
       eventswithlf_met_notfromtop = new TH1F("eventswithlf_met_notfromtop","eventswithlf_met_notfromtop",3,250,550);

       MT_SingleLep_fromtop = new TH1F("MT_SingleLep_fromtop","MT_SingleLep_fromtop",12,0,600);
       MT2W_SingleLep_fromtop = new TH1F("MT2W_SingleLep_fromtop","MT2W_SingleLep_fromtop",18,50,500);
       Topness_SingleLep_fromtop = new TH1F("Topness_SingleLep_fromtop","Topness_SingleLep_fromtop",18,50,500);
       Topnessmod_SingleLep_fromtop = new TH1F("Topnessmod_SingleLep_fromtop","Topnessmod_SingleLep_fromtop",20,-5,15);
       Chi2_SingleLep_fromtop = new TH1F("Chi2_SingleLep_fromtop","Chi2_SingleLep_fromtop",20,0,20);
       MinDPhi_SingleLep_fromtop = new TH1F("MinDPhi_SingleLep_fromtop","MinDPhi_SingleLep_fromtop",20,0,4);
       HTratio_SingleLep_fromtop = new TH1F("HTratio_SingleLep_fromtop","HTratio_SingleLep_fromtop",20,0,1);
       DRlepb_SingleLep_fromtop= new TH1F("DRlepb_SingleLep_fromtop","DRlepb_SingleLep_fromtop",20,0,5);
       leadbpt_SingleLep_fromtop= new TH1F("leadbpt_SingleLep_fromtop","leadbpt_SingleLep_fromtop",18,30,390);
       met_SingleLep_fromtop= new TH1F("met_SingleLep_fromtop","met_SingleLep_fromtop",24,50,650);
       leppt_SingleLep_fromtop= new TH1F("leppt_SingleLep_fromtop","leppt_SingleLep_fromtop",26,30,680);
       lepeta_SingleLep_fromtop= new TH1F("lepeta_SingleLep_fromtop","lepeta_SingleLep_fromtop",30,-3,3);
       lepphi_SingleLep_fromtop= new TH1F("lepphi_SingleLep_fromtop","lepphi_SingleLep_fromtop",20,-1,1);
       HT_SingleLep_fromtop= new TH1F("HT_SingleLep_fromtop","HT_SingleLep_fromtop",30,0,1500);
       njets_SingleLep_fromtop= new TH1F("njets_SingleLep_fromtop","njets_SingleLep_fromtop",12,0,12);
       nbjets_SingleLep_fromtop= new TH1F("nbjets_SingleLep_fromtop","nbjets_SingleLep_fromtop",6,0,6);
       njets_pt200_nobtags_SingleLep_fromtop= new TH1F("njets_pt200_nobtags_SingleLep_fromtop","njets_pt200_nobtags_SingleLep_fromtop",5,0,5);
       leadISRjet_pt200_nobtags_SingleLep_fromtop= new TH1F("leadISRjet_pt200_nobtags_SingleLep_fromtop","leadISRjet_pt200_nobtags_SingleLep_fromtop",24,0,600);
       METoverSqrtHT_SingleLep_fromtop= new TH1F("METoverSqrtHT_SingleLep_fromtop","METoverSqrtHT_SingleLep_fromtop",20,0,40);
       Mlepb_SingleLep_fromtop= new TH1F("Mlepb_SingleLep_fromtop","Mlepb_SingleLep_fromtop",24,0,600);
       genMlepb_SingleLep_fromtop= new TH1F("genMlepb_SingleLep_fromtop","genMlepb_SingleLep_fromtop",24,0,600);
       M3b_SingleLep_fromtop= new TH1F("M3b_SingleLep_fromtop","M3b_SingleLep_fromtop",10,0,1);
       jetpt_SingleLep_fromtop= new TH1F("jetpt_SingleLep_fromtop","jetpt_SingleLep_fromtop",32,30,480);
       DPhiLepJet_SingleLep_fromtop= new TH1F("DPhiLepJet_SingleLep_fromtop","DPhiLepJet_SingleLep_fromtop",20,0,4);
       leadjetpt_SingleLep_fromtop= new TH1F("leadjetpt_SingleLep_fromtop","leadjetpt_SingleLep_fromtop",32,30,480);
       DPhiWLep_SingleLep_fromtop= new TH1F("DPhiWLep_SingleLep_fromtop","DPhiWLep_SingleLep_fromtop",25,0,5);
       PZeta_TrkLep_SingleLep_fromtop = new TH1F("PZeta_TrkLep_SingleLep_fromtop","PZeta_TrkLep_SingleLep_fromtop",60,-600,600);
       PZetaVis_TrkLep_SingleLep_fromtop = new TH1F("PZetaVis_TrkLep_SingleLep_fromtop","PZetaVis_TrkLep_SingleLep_fromtop",12,0,600);
       ak4_nef_SingleLep_fromtop = new TH1F("ak4_nef_SingleLep_fromtop", "ak4_nef_SingleLep_fromtop",34,30,300);
       ak4_cef_SingleLep_fromtop = new TH1F("ak4_cef_SingleLep_fromtop", "ak4_cef_SingleLep_fromtop",22,30,200);
       ak4_EF_SingleLep_fromtop = new TH1F("ak4_EFf_SingleLep_fromtop", "ak4_EF_SingleLep_fromtop",10,0,1.);
       Wpt_SingleLep_fromtop = new TH1F("Wpt_SingleLep_fromtop","Wpt_SingleLep_fromtop",13,0,650);

       MT_Znunu = new TH1F("MT_Znunu","MT_Znunu",12,0,600);
       MT2W_Znunu = new TH1F("MT2W_Znunu","MT2W_Znunu",18,50,500);
       Topness_Znunu = new TH1F("Topness_Znunu","Topness_Znunu",18,50,500);
       Topnessmod_Znunu = new TH1F("Topnessmod_Znunu","Topnessmod_Znunu",20,-5,15);
       Chi2_Znunu = new TH1F("Chi2_Znunu","Chi2_Znunu",20,0,20);
       MinDPhi_Znunu = new TH1F("MinDPhi_Znunu","MinDPhi_Znunu",20,0,4);
       HTratio_Znunu = new TH1F("HTratio_Znunu","HTratio_Znunu",20,0,1);
       DRlepb_Znunu= new TH1F("DRlepb_Znunu","DRlepb_Znunu",20,0,5);
       leadbpt_Znunu= new TH1F("leadbpt_Znunu","leadbpt_Znunu",18,30,390);
       met_Znunu= new TH1F("met_Znunu","met_Znunu",24,50,650);
       leppt_Znunu= new TH1F("leppt_Znunu","leppt_Znunu",26,30,680);
       lepeta_Znunu= new TH1F("lepeta_Znunu","lepeta_Znunu",30,-3,3);
       lepphi_Znunu= new TH1F("lepphi_Znunu","lepphi_Znunu",20,-1,1);
       HT_Znunu= new TH1F("HT_Znunu","HT_Znunu",30,0,1500);
       njets_Znunu= new TH1F("njets_Znunu","njets_Znunu",12,0,12);
       nbjets_Znunu= new TH1F("nbjets_Znunu","nbjets_Znunu",6,0,6);
       njets_pt200_nobtags_Znunu= new TH1F("njets_pt200_nobtags_Znunu","njets_pt200_nobtags_Znunu",5,0,5);
       leadISRjet_pt200_nobtags_Znunu= new TH1F("leadISRjet_pt200_nobtags_Znunu","leadISRjet_pt200_nobtags_Znunu",24,0,600);
       METoverSqrtHT_Znunu= new TH1F("METoverSqrtHT_Znunu","METoverSqrtHT_Znunu",20,0,40);
       Mlepb_Znunu= new TH1F("Mlepb_Znunu","Mlepb_Znunu",24,0,600);
       genMlepb_Znunu= new TH1F("genMlepb_Znunu","genMlepb_Znunu",24,0,600);
       M3b_Znunu= new TH1F("M3b_Znunu","M3b_Znunu",10,0,1);
       jetpt_Znunu= new TH1F("jetpt_Znunu","jetpt_Znunu",32,30,480);
       DPhiLepJet_Znunu= new TH1F("DPhiLepJet_Znunu","DPhiLepJet_Znunu",20,0,4);
       leadjetpt_Znunu= new TH1F("leadjetpt_Znunu","leadjetpt_Znunu",32,30,480);
       DPhiWLep_Znunu= new TH1F("DPhiWLep_Znunu","DPhiWLep_Znunu",25,0,5);
       PZeta_TrkLep_Znunu = new TH1F("PZeta_TrkLep_Znunu","PZeta_TrkLep_Znunu",60,-600,600);
       PZetaVis_TrkLep_Znunu = new TH1F("PZetaVis_TrkLep_Znunu","PZetaVis_TrkLep_Znunu",12,0,600);
       ak4_nef_Znunu = new TH1F("ak4_nef_Znunu", "ak4_nef_Znunu",34,30,300);
       ak4_cef_Znunu = new TH1F("ak4_cef_Znunu", "ak4_cef_Znunu",22,30,200);
       ak4_EF_Znunu = new TH1F("ak4_EFf_Znunu", "ak4_EF_Znunu",10,0,1.);
       Wpt_Znunu = new TH1F("Wpt_Znunu","Wpt_Znunu",13,0,650);





}

void BasicHistos::BookSRHistos_signal(int vIt, string process){

        char* thejetPt2DHistoName = Form("jetPt2D_%s",process.c_str());
        _thejetPt2DHistoMap[vIt] = new TH2F(thejetPt2DHistoName,thejetPt2DHistoName,25,0,500,25,0,500);
        char* theMlepb2DHistoName = Form("Mlepb2D_%s",process.c_str());
        _theMlepb2DHistoMap[vIt] = new TH2F(theMlepb2DHistoName,theMlepb2DHistoName,24,0,600,24,0,600);
        char* thegenMlepb2DHistoName = Form("genMlepb2D_%s",process.c_str());
        _thegenMlepb2DHistoMap[vIt] = new TH2F(thegenMlepb2DHistoName,thegenMlepb2DHistoName,24,0,600,24,0,600);
        char* theMTHistoName = Form("MT_%s",process.c_str());
        _theMTHistoMap[vIt] = new TH1F(theMTHistoName,theMTHistoName,12,0,600);
        char* theMT2WHistoName = Form("MT2W_%s",process.c_str());
        _theMT2WHistoMap[vIt] = new TH1F(theMT2WHistoName,theMT2WHistoName,18,50,500);
        char* theTopnessHistoName = Form("Topness_%s",process.c_str());
        _theTopnessHistoMap[vIt] = new TH1F(theTopnessHistoName,theTopnessHistoName,18,50,500);
        char* theTopnessmodHistoName = Form("Topnessmod_%s",process.c_str());
        _theTopnessmodHistoMap[vIt] = new TH1F(theTopnessmodHistoName,theTopnessmodHistoName,20,-5,15);
        char* theChi2HistoName = Form("Chi2_%s",process.c_str());
        _theChi2HistoMap[vIt] = new TH1F(theChi2HistoName,theChi2HistoName,20,0,20);
        char* theMinDPhiHistoName = Form("MinDPhi_%s",process.c_str());
        _theMinDPhiHistoMap[vIt] = new TH1F(theMinDPhiHistoName,theMinDPhiHistoName,20,0,4);
        char* theHTratioHistoName = Form("HTratio_%s",process.c_str());
        _theHTratioHistoMap[vIt] = new TH1F(theHTratioHistoName,theHTratioHistoName,20,0,1);
        char* theDRlepbHistoName = Form("DRlepb_%s",process.c_str());
        _theDRlepbHistoMap[vIt] = new TH1F(theDRlepbHistoName,theDRlepbHistoName,20,0,5);
        char* theleadbptHistoName = Form("leadbpt_%s",process.c_str());
        _theleadbptHistoMap[vIt] = new TH1F(theleadbptHistoName,theleadbptHistoName,18,30,390);
        char* themetHistoName = Form("met_%s",process.c_str());
        _themetHistoMap[vIt] = new TH1F(themetHistoName,themetHistoName,24,50,650);
        char* thelepptHistoName = Form("leppt_%s",process.c_str());
        _thelepptHistoMap[vIt] = new TH1F(thelepptHistoName,thelepptHistoName,26,30,680);
        char* thelepetaHistoName = Form("lepeta_%s",process.c_str());
        _thelepetaHistoMap[vIt] = new TH1F(thelepetaHistoName,thelepetaHistoName,30,-3,3);
        char* thelepphiHistoName = Form("lepphi_%s",process.c_str());
        _thelepphiHistoMap[vIt] = new TH1F(thelepphiHistoName,thelepphiHistoName,20,-1,1);
        char* theHTHistoName = Form("HT_%s",process.c_str());
        _theHTHistoMap[vIt] = new TH1F(theHTHistoName,theHTHistoName,30,0,1500);
        char* thenjetsHistoName = Form("njets_%s",process.c_str());
        _thenjetsHistoMap[vIt] = new TH1F(thenjetsHistoName,thenjetsHistoName,12,0,12);
        char* thenbjetsHistoName = Form("nbjets_%s",process.c_str());
        _thenbjetsHistoMap[vIt] = new TH1F(thenbjetsHistoName,thenbjetsHistoName,6,0,6);
        char* thenjets_pt200_nobtagsHistoName = Form("njets_pt200_nobtags_%s",process.c_str());
        _thenjets_pt200_nobtagsHistoMap[vIt] = new TH1F(thenjets_pt200_nobtagsHistoName,thenjets_pt200_nobtagsHistoName,5,0,5);
        char* theleadISRjet_pt200_nobtagsHistoName = Form("leadISRjet_pt200_nobtags_%s",process.c_str());
        _theleadISRjet_pt200_nobtagsHistoMap[vIt] = new TH1F(theleadISRjet_pt200_nobtagsHistoName,theleadISRjet_pt200_nobtagsHistoName,24,0,600);
        char* theMEToverSqrtHTHistoName = Form("METoverSqrtHT_%s",process.c_str());
        _theMEToverSqrtHTHistoMap[vIt] = new TH1F(theMEToverSqrtHTHistoName,theMEToverSqrtHTHistoName,20,0,40);
        char* theMlepbHistoName = Form("Mlepb_%s",process.c_str());
        _theMlepbHistoMap[vIt] = new TH1F(theMlepbHistoName,theMlepbHistoName,24,0,600);
        char* thegenMlepbHistoName = Form("genMlepb_%s",process.c_str());
        _thegenMlepbHistoMap[vIt] = new TH1F(thegenMlepbHistoName,thegenMlepbHistoName,24,0,600);
        char* theM3bHistoName = Form("M3b_%s",process.c_str());
        _theM3bHistoMap[vIt] = new TH1F(theM3bHistoName,theM3bHistoName,10,0,1);
        char* thejetptHistoName = Form("jetpt_%s",process.c_str());
        _thejetptHistoMap[vIt] = new TH1F(thejetptHistoName,thejetptHistoName,32,30,480);
        char* theDPhiLepJetHistoName = Form("DPhiLepJet_%s",process.c_str());
        _theDPhiLepJetHistoMap[vIt] = new TH1F(theDPhiLepJetHistoName,theDPhiLepJetHistoName,20,0,4);
        char* theleadjetptHistoName = Form("leadjetpt_%s",process.c_str());
        _theleadjetptHistoMap[vIt] = new TH1F(theleadjetptHistoName,theleadjetptHistoName,32,30,480);

        char* theDPhiWLepHistoName = Form("theDPhiWLep_%s",process.c_str());
        _theDPhiWLepHistoMap[vIt] = new TH1F(theDPhiWLepHistoName,theDPhiWLepHistoName,25,0,5);
        char* thePZeta_TrkLepHistoName = Form("PZeta_TrkLep_%s",process.c_str());
        _thePZeta_TrkLepHistoMap[vIt] = new TH1F(thePZeta_TrkLepHistoName,thePZeta_TrkLepHistoName,60,-600,600);
        char* thePZetaVis_TrkLepHistoName = Form("PZetaVis_TrkLep_%s",process.c_str());
        _thePZetaVis_TrkLepHistoMap[vIt] = new TH1F(thePZetaVis_TrkLepHistoName,thePZetaVis_TrkLepHistoName,12,0,600);
        char* _theak4NEFHistoName = Form("ak4_nef_%s",process.c_str());
        _theak4NEFHistoMap[vIt] = new TH1F(_theak4NEFHistoName,_theak4NEFHistoName,34,30,300);
        char* _theak4CEFHistoName = Form("ak4_cef_%s",process.c_str());
        _theak4CEFHistoMap[vIt] = new TH1F(_theak4CEFHistoName,_theak4CEFHistoName,22,30,200);
        char* _theak4EFHistoName = Form("ak4_EF_%s",process.c_str());
        _theak4EFHistoMap[vIt] = new TH1F(_theak4EFHistoName,_theak4EFHistoName,10,0,1.);
         
        char* theWptHistoName = Form("theWpt_%s",process.c_str());
        _theWptHistoMap[vIt] = new TH1F(theWptHistoName,theWptHistoName,13,0,650);
       
}

void BasicHistos::MakeBasicHistoVectors(int process,string name,float signalscale){
    std::string filestr (name);
    cout<<filestr<<" Integral "<<_theMTHistoMap[process]->Integral()<<endl;
       _mySignalVector.push_back(_theMTHistoMap[process]);
       _mySignalMT2WVector.push_back(_theMT2WHistoMap[process]);
       _mySignalTopnessVector.push_back(_theTopnessHistoMap[process]);
       _mySignalTopnessmodVector.push_back(_theTopnessmodHistoMap[process]);
       _mySignalChi2Vector.push_back(_theChi2HistoMap[process]);
       _mySignalMinDPhiVector.push_back(_theMinDPhiHistoMap[process]);
       _mySignalHTratioVector.push_back(_theHTratioHistoMap[process]);
       _mySignalDRlepbVector.push_back(_theDRlepbHistoMap[process]);
       _mySignalleadbptVector.push_back(_theleadbptHistoMap[process]);
       _mySignalmetVector.push_back(_themetHistoMap[process]);
       _mySignallepptVector.push_back(_thelepptHistoMap[process]);
       _mySignallepetaVector.push_back(_thelepetaHistoMap[process]);
       _mySignallepphiVector.push_back(_thelepphiHistoMap[process]);
       _mySignalHTVector.push_back(_theHTHistoMap[process]);
       _mySignalnjetsVector.push_back(_thenjetsHistoMap[process]);
       _mySignalnbjetsVector.push_back(_thenbjetsHistoMap[process]);
       _mySignalnjets_pt200_nobtagsVector.push_back(_thenjets_pt200_nobtagsHistoMap[process]);
       _mySignalleadISRjet_pt200_nobtagsVector.push_back(_theleadISRjet_pt200_nobtagsHistoMap[process]);
       _mySignalMEToverSqrtHTVector.push_back(_theMEToverSqrtHTHistoMap[process]);
       _mySignalMlepbVector.push_back(_theMlepbHistoMap[process]);
       _mySignalgenMlepbVector.push_back(_thegenMlepbHistoMap[process]);
       _mySignalM3bVector.push_back(_theM3bHistoMap[process]);
       _mySignaljetptVector.push_back(_thejetptHistoMap[process]);
       _mySignalDPhiLepJetVector.push_back(_theDPhiLepJetHistoMap[process]);
       _mySignalleadjetptVector.push_back(_theleadjetptHistoMap[process]);
       _mySignalDPhiWLep.push_back(_theDPhiWLepHistoMap[process]);
       _mySignalPZeta_TrkLep.push_back(_thePZeta_TrkLepHistoMap[process]);
       _mySignalPZetaVis_TrkLep.push_back(_thePZetaVis_TrkLepHistoMap[process]);
       _mySignal_ak4NEFVector.push_back(_theak4NEFHistoMap[process]);
       _mySignal_ak4CEFVector.push_back(_theak4CEFHistoMap[process]);
       _mySignal_ak4EFVector.push_back(_theak4EFHistoMap[process]);
       _mySignalWptVector.push_back(_theWptHistoMap[process]);
        if(filestr.find("T2tt_80_100") != string::npos){
                _mySignalTitles.push_back(Form("T2tt(80,100)x%4.0f",signalscale));
       }
        if(filestr.find("T2tt_60_325") != string::npos){
                _mySignalTitles.push_back(Form("T2tt(60,325)x%4.0f",signalscale));
        }
        if(filestr.find("T2tt_00_325") != string::npos){
                _mySignalTitles.push_back(Form("T2tt(00,325)x%4.0f",signalscale));
        }
        if(filestr.find("T2tt_425_325") != string::npos){
                _mySignalTitles.push_back(Form("T2tt(425,325)x%4.0f",signalscale));
        }
        if(filestr.find("SMS_T2tb_425_230_225") != string::npos){
                _mySignalTitles.push_back(Form("T2bt(425,230,222.5)x%4.0f",signalscale));
        }
        if(filestr.find("SMS_T2tb_650_330_325") != string::npos){
                _mySignalTitles.push_back(Form("T2tb(650,330,325)x%4.0f",signalscale));
        }
        if(filestr.find("SMS_T2tb_850_105_100") != string::npos){
                _mySignalTitles.push_back(Form("T2bt(850,105,100)x%4.0f",signalscale));
        }
        if(filestr.find("SMS_T2tb_850_400_100") != string::npos){
                _mySignalTitles.push_back(Form("T2bt(850,400,300)x%4.0f",signalscale));
        }
        if(filestr.find("SMS_T2tb_700_250_100") != string::npos){
                _mySignalTitles.push_back(Form("T2bt(700,250,100)x%4.0f",signalscale));
        }
}

void BasicHistos::MakeBasicHistoVectors_bckgd2(){
       _myDataVector.push_back(MT_data);
       _myDataMT2WVector.push_back(MT2W_data);
       _myDataTopnessVector.push_back(Topness_data);
       _myDataTopnessmodVector.push_back(Topnessmod_data);
       _myDataChi2Vector.push_back(Chi2_data);
       _myDataMinDPhiVector.push_back(MinDPhi_data);
       _myDataHTratioVector.push_back(HTratio_data);
       _myDataDRlepbVector.push_back(DRlepb_data);
       _myDataleadbptVector.push_back(leadbpt_data);
       _myDatametVector.push_back(met_data);
       _myDatalepptVector.push_back(leppt_data);
       _myDatalepetaVector.push_back(lepeta_data);
       _myDatalepphiVector.push_back(lepphi_data);
       _myDataHTVector.push_back(HT_data);
       _myDatanjetsVector.push_back(njets_data);
       _myDatanbjetsVector.push_back(nbjets_data);
       _myDatanjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_data);
       _myDataleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_data);
       _myDataMEToverSqrtHTVector.push_back(METoverSqrtHT_data);
       _myDataMlepbVector.push_back(Mlepb_data);
       _myDatagenMlepbVector.push_back(genMlepb_data);
       _myDataM3bVector.push_back(M3b_data);
       _myDatajetptVector.push_back(jetpt_data);

       _myDataDPhiLepJetVector.push_back(DPhiLepJet_data);
       _myDataleadjetptVector.push_back(leadjetpt_data);
       _myDataDPhiWLep.push_back(DPhiWLep_data);
       _myDataPZeta_TrkLep.push_back(PZeta_TrkLep_data);
       _myDataPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_data);
       _myDataak4NEFVector.push_back(ak4_nef_data);
       _myDataak4CEFVector.push_back(ak4_cef_data);
       _myDataak4EFVector.push_back(ak4_EF_data);
       _myDataWptVector.push_back(Wpt_data);

       _myTitles2.push_back("Z#nu#nu");
       _myColors2.push_back(kMagenta-5);
       _myVector2.push_back(MT_Znunu);
       _myMT2WVector2.push_back(MT2W_Znunu);
       _myTopnessVector2.push_back(Topness_Znunu);
       _myTopnessmodVector2.push_back(Topnessmod_Znunu);
       _myChi2Vector2.push_back(Chi2_Znunu);
       _myMinDPhiVector2.push_back(MinDPhi_Znunu);
       _myHTratioVector2.push_back(HTratio_Znunu);
       _myDRlepbVector2.push_back(DRlepb_Znunu);
       _myleadbptVector2.push_back(leadbpt_Znunu);
       _mymetVector2.push_back(met_Znunu);
       _mylepptVector2.push_back(leppt_Znunu);
       _mylepetaVector2.push_back(lepeta_Znunu);
       _mylepphiVector2.push_back(lepphi_Znunu);
       _myHTVector2.push_back(HT_Znunu);
       _mynjetsVector2.push_back(njets_Znunu);
       _mynbjetsVector2.push_back(nbjets_Znunu);
       _mynjets_pt200_nobtagsVector2.push_back(njets_pt200_nobtags_Znunu);
       _myleadISRjet_pt200_nobtagsVector2.push_back(leadISRjet_pt200_nobtags_Znunu);
       _myMEToverSqrtHTVector2.push_back(METoverSqrtHT_Znunu);
       _myMlepbVector2.push_back(Mlepb_Znunu);
       _mygenMlepbVector2.push_back(genMlepb_Znunu);
       _myM3bVector2.push_back(M3b_Znunu);
       _myjetptVector2.push_back(jetpt_Znunu);
       _myWptVector2.push_back(Wpt_Znunu);

       _myTitles2.push_back("1lep (from top)");
       _myColors2.push_back(kRed-7);
       _myVector2.push_back(MT_SingleLep_fromtop);
       _myMT2WVector2.push_back(MT2W_SingleLep_fromtop);
       _myTopnessVector2.push_back(Topness_SingleLep_fromtop);
       _myTopnessmodVector2.push_back(Topnessmod_SingleLep_fromtop);
       _myChi2Vector2.push_back(Chi2_SingleLep_fromtop);
       _myMinDPhiVector2.push_back(MinDPhi_SingleLep_fromtop);
       _myHTratioVector2.push_back(HTratio_SingleLep_fromtop);
       _myDRlepbVector2.push_back(DRlepb_SingleLep_fromtop);
       _myleadbptVector2.push_back(leadbpt_SingleLep_fromtop);
       _mymetVector2.push_back(met_SingleLep_fromtop);
       _mylepptVector2.push_back(leppt_SingleLep_fromtop);
       _mylepetaVector2.push_back(lepeta_SingleLep_fromtop);
       _mylepphiVector2.push_back(lepphi_SingleLep_fromtop);
       _myHTVector2.push_back(HT_SingleLep_fromtop);
       _mynjetsVector2.push_back(njets_SingleLep_fromtop);
       _mynbjetsVector2.push_back(nbjets_SingleLep_fromtop);
       _mynjets_pt200_nobtagsVector2.push_back(njets_pt200_nobtags_SingleLep_fromtop);
       _myleadISRjet_pt200_nobtagsVector2.push_back(leadISRjet_pt200_nobtags_SingleLep_fromtop);
       _myMEToverSqrtHTVector2.push_back(METoverSqrtHT_SingleLep_fromtop);
       _myMlepbVector2.push_back(Mlepb_SingleLep_fromtop);
       _mygenMlepbVector2.push_back(genMlepb_SingleLep_fromtop);
       _myM3bVector2.push_back(M3b_SingleLep_fromtop);
       _myjetptVector2.push_back(jetpt_SingleLep_fromtop);
       _myWptVector2.push_back(Wpt_SingleLep_fromtop);

       _myTitles2.push_back("2lep (lost lepton)");
       _myColors2.push_back(kCyan-3);
       _myVector2.push_back(MT_Dilep);
       _myMT2WVector2.push_back(MT2W_Dilep);
       _myTopnessVector2.push_back(Topness_Dilep);
       _myTopnessmodVector2.push_back(Topnessmod_Dilep);
       _myChi2Vector2.push_back(Chi2_Dilep);
       _myMinDPhiVector2.push_back(MinDPhi_Dilep);
       _myHTratioVector2.push_back(HTratio_Dilep);
       _myDRlepbVector2.push_back(DRlepb_Dilep);
       _myleadbptVector2.push_back(leadbpt_Dilep);
       _mymetVector2.push_back(met_Dilep);
       _mylepptVector2.push_back(leppt_Dilep);
       _mylepetaVector2.push_back(lepeta_Dilep);
       _mylepphiVector2.push_back(lepphi_Dilep);
       _myHTVector2.push_back(HT_Dilep);
       _mynjetsVector2.push_back(njets_Dilep);
       _mynbjetsVector2.push_back(nbjets_Dilep);
       _mynjets_pt200_nobtagsVector2.push_back(njets_pt200_nobtags_Dilep);
       _myleadISRjet_pt200_nobtagsVector2.push_back(leadISRjet_pt200_nobtags_Dilep);
       _myMEToverSqrtHTVector2.push_back(METoverSqrtHT_Dilep);
       _myMlepbVector2.push_back(Mlepb_Dilep);
       _mygenMlepbVector2.push_back(genMlepb_Dilep);
       _myM3bVector2.push_back(M3b_Dilep);
       _myjetptVector2.push_back(jetpt_Dilep);
       _myWptVector2.push_back(Wpt_Dilep);

       _myTitles2.push_back("WJets (1lep not from top)");
       _myColors2.push_back(kOrange-2);
       _myVector2.push_back(MT_SingleLep_notfromtop);
       _myMT2WVector2.push_back(MT2W_SingleLep_notfromtop);
       _myTopnessVector2.push_back(Topness_SingleLep_notfromtop);
       _myTopnessmodVector2.push_back(Topnessmod_SingleLep_notfromtop);
       _myChi2Vector2.push_back(Chi2_SingleLep_notfromtop);
       _myMinDPhiVector2.push_back(MinDPhi_SingleLep_notfromtop);
       _myHTratioVector2.push_back(HTratio_SingleLep_notfromtop);
       _myDRlepbVector2.push_back(DRlepb_SingleLep_notfromtop);
       _myleadbptVector2.push_back(leadbpt_SingleLep_notfromtop);
       _mymetVector2.push_back(met_SingleLep_notfromtop);
       _mylepptVector2.push_back(leppt_SingleLep_notfromtop);
       _mylepetaVector2.push_back(lepeta_SingleLep_notfromtop);
       _mylepphiVector2.push_back(lepphi_SingleLep_notfromtop);
       _myHTVector2.push_back(HT_SingleLep_notfromtop);
       _mynjetsVector2.push_back(njets_SingleLep_notfromtop);
       _mynbjetsVector2.push_back(nbjets_SingleLep_notfromtop);
       _mynjets_pt200_nobtagsVector2.push_back(njets_pt200_nobtags_SingleLep_notfromtop);
       _myleadISRjet_pt200_nobtagsVector2.push_back(leadISRjet_pt200_nobtags_SingleLep_notfromtop);
       _myMEToverSqrtHTVector2.push_back(METoverSqrtHT_SingleLep_notfromtop);
       _myMlepbVector2.push_back(Mlepb_SingleLep_notfromtop);
       _mygenMlepbVector2.push_back(genMlepb_SingleLep_notfromtop);
       _myM3bVector2.push_back(M3b_SingleLep_notfromtop);
       _myjetptVector2.push_back(jetpt_SingleLep_notfromtop);
       _myWptVector2.push_back(Wpt_SingleLep_notfromtop);
}

void BasicHistos::MakeBasicHistoVectors_bckgd(){

       _myDataVector.push_back(MT_data);
       _myDataMT2WVector.push_back(MT2W_data);
       _myDataTopnessVector.push_back(Topness_data);
       _myDataTopnessmodVector.push_back(Topnessmod_data);
       _myDataChi2Vector.push_back(Chi2_data);
       _myDataMinDPhiVector.push_back(MinDPhi_data);
       _myDataHTratioVector.push_back(HTratio_data);
       _myDataDRlepbVector.push_back(DRlepb_data);
       _myDataleadbptVector.push_back(leadbpt_data);
       _myDatametVector.push_back(met_data);
       _myDatalepptVector.push_back(leppt_data);
       _myDatalepetaVector.push_back(lepeta_data);
       _myDatalepphiVector.push_back(lepphi_data);
       _myDataHTVector.push_back(HT_data);
       _myDatanjetsVector.push_back(njets_data);
       _myDatanbjetsVector.push_back(nbjets_data);
       _myDatanjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_data);
       _myDataleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_data);
       _myDataMEToverSqrtHTVector.push_back(METoverSqrtHT_data);
       _myDataMlepbVector.push_back(Mlepb_data);
       _myDatagenMlepbVector.push_back(genMlepb_data);
       _myDataM3bVector.push_back(M3b_data);
       _myDatajetptVector.push_back(jetpt_data);

       _myDataDPhiLepJetVector.push_back(DPhiLepJet_data);
       _myDataleadjetptVector.push_back(leadjetpt_data);
       _myDataDPhiWLep.push_back(DPhiWLep_data);
       _myDataPZeta_TrkLep.push_back(PZeta_TrkLep_data);
       _myDataPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_data);
       _myDataak4NEFVector.push_back(ak4_nef_data);
       _myDataak4CEFVector.push_back(ak4_cef_data);
       _myDataak4EFVector.push_back(ak4_EF_data);
       _myDataWptVector.push_back(Wpt_data);
       
       _myTitles.push_back("rare");
       _myColors.push_back(kMagenta-5);
       _myVector.push_back(MT_rare);
       _myMT2WVector.push_back(MT2W_rare);
       _myTopnessVector.push_back(Topness_rare);
       _myTopnessmodVector.push_back(Topnessmod_rare);
       _myChi2Vector.push_back(Chi2_rare);
       _myMinDPhiVector.push_back(MinDPhi_rare);
       _myHTratioVector.push_back(HTratio_rare);
       _myDRlepbVector.push_back(DRlepb_rare);
       _myleadbptVector.push_back(leadbpt_rare);
       _mymetVector.push_back(met_rare);
       _mylepptVector.push_back(leppt_rare);
       _mylepetaVector.push_back(lepeta_rare);
       _mylepphiVector.push_back(lepphi_rare);
       _myHTVector.push_back(HT_rare);
       _mynjetsVector.push_back(njets_rare);
       _mynbjetsVector.push_back(nbjets_rare);
       _mynjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_rare);
       _myleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_rare);
       _myMEToverSqrtHTVector.push_back(METoverSqrtHT_rare);
       _myMlepbVector.push_back(Mlepb_rare);
       _mygenMlepbVector.push_back(genMlepb_rare);
       _myM3bVector.push_back(M3b_rare);
       _myjetptVector.push_back(jetpt_rare);
       _myWptVector.push_back(Wpt_rare);

       _myDPhiLepJetVector.push_back(DPhiLepJet_rare);
       _myleadjetptVector.push_back(leadjetpt_rare);
       _myDPhiWLep.push_back(DPhiWLep_rare);
       _myPZeta_TrkLep.push_back(PZeta_TrkLep_rare);
       _myPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_rare);
       _myak4NEFVector.push_back(ak4_nef_rare);
       _myak4CEFVector.push_back(ak4_cef_rare);
       _myak4EFVector.push_back(ak4_EF_rare);

       _myTitles.push_back("W+Jets");
       _myColors.push_back(kOrange-2);
       _myVector.push_back(MT_wjets);
       _myMT2WVector.push_back(MT2W_wjets);
       _myTopnessVector.push_back(Topness_wjets);
       _myTopnessmodVector.push_back(Topnessmod_wjets);
       _myChi2Vector.push_back(Chi2_wjets);
       _myMinDPhiVector.push_back(MinDPhi_wjets);
       _myHTratioVector.push_back(HTratio_wjets);
       _myDRlepbVector.push_back(DRlepb_wjets);
       _myleadbptVector.push_back(leadbpt_wjets);
       _mymetVector.push_back(met_wjets);
       _mylepptVector.push_back(leppt_wjets);
       _mylepetaVector.push_back(lepeta_wjets);
       _mylepphiVector.push_back(lepphi_wjets);
       _myHTVector.push_back(HT_wjets);
       _mynjetsVector.push_back(njets_wjets);
       _mynbjetsVector.push_back(nbjets_wjets);
       _mynjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_wjets);
       _myleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_wjets);
       _myMEToverSqrtHTVector.push_back(METoverSqrtHT_wjets);
       _myMlepbVector.push_back(Mlepb_wjets);
       _mygenMlepbVector.push_back(genMlepb_wjets);
       _myM3bVector.push_back(M3b_wjets);
       _myjetptVector.push_back(jetpt_wjets);
       _myDPhiLepJetVector.push_back(DPhiLepJet_wjets);
       _myleadjetptVector.push_back(leadjetpt_wjets);
       _myDPhiWLep.push_back(DPhiWLep_wjets);
       _myPZeta_TrkLep.push_back(PZeta_TrkLep_wjets);
       _myPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_wjets);
       _myak4NEFVector.push_back(ak4_nef_wjets);
       _myak4CEFVector.push_back(ak4_cef_wjets);
       _myak4EFVector.push_back(ak4_EF_wjets);
       _myWptVector.push_back(Wpt_wjets);

       _myTitles.push_back("single top");
       _myColors.push_back(kRed-3);
       _myVector.push_back(MT_ST);
       _myMT2WVector.push_back(MT2W_ST);
       _myTopnessVector.push_back(Topness_ST);
       _myTopnessmodVector.push_back(Topnessmod_ST);
       _myChi2Vector.push_back(Chi2_ST);
       _myMinDPhiVector.push_back(MinDPhi_ST);
       _myHTratioVector.push_back(HTratio_ST);
       _myDRlepbVector.push_back(DRlepb_ST);
       _myleadbptVector.push_back(leadbpt_ST);
       _mymetVector.push_back(met_ST);
       _mylepptVector.push_back(leppt_ST);
       _mylepetaVector.push_back(lepeta_ST);
       _mylepphiVector.push_back(lepphi_ST);
       _myHTVector.push_back(HT_ST);
       _mynjetsVector.push_back(njets_ST);
       _mynbjetsVector.push_back(nbjets_ST);
       _mynjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_ST);
       _myleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_ST);
       _myMEToverSqrtHTVector.push_back(METoverSqrtHT_ST);
       _myMlepbVector.push_back(Mlepb_ST);
       _mygenMlepbVector.push_back(genMlepb_ST);
       _myM3bVector.push_back(M3b_ST);
       _myjetptVector.push_back(jetpt_ST);
       _myDPhiLepJetVector.push_back(DPhiLepJet_ST);
       _myleadjetptVector.push_back(leadjetpt_ST);
       _myDPhiWLep.push_back(DPhiWLep_ST);
       _myPZeta_TrkLep.push_back(PZeta_TrkLep_ST);
       _myPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_ST);
       _myak4NEFVector.push_back(ak4_nef_ST);
       _myak4CEFVector.push_back(ak4_cef_ST);
       _myak4EFVector.push_back(ak4_EF_ST);
       _myWptVector.push_back(Wpt_ST);

       _myTitles.push_back("t#bar{t} #rightarrow l+jets");
       _myColors.push_back(kRed-7);
       _myVector.push_back(MT_1lep);
       _myMT2WVector.push_back(MT2W_1lep);
       _myTopnessVector.push_back(Topness_1lep);
       _myTopnessmodVector.push_back(Topnessmod_1lep);
       _myChi2Vector.push_back(Chi2_1lep);
       _myMinDPhiVector.push_back(MinDPhi_1lep);
       _myHTratioVector.push_back(HTratio_1lep);
       _myDRlepbVector.push_back(DRlepb_1lep);
       _myleadbptVector.push_back(leadbpt_1lep);
       _mymetVector.push_back(met_1lep);
       _mylepptVector.push_back(leppt_1lep);
       _mylepetaVector.push_back(lepeta_1lep);
       _mylepphiVector.push_back(lepphi_1lep);
       _myHTVector.push_back(HT_1lep);
       _mynjetsVector.push_back(njets_1lep);
       _mynbjetsVector.push_back(nbjets_1lep);
       _mynjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_1lep);
       _myleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_1lep);
       _myMEToverSqrtHTVector.push_back(METoverSqrtHT_1lep);
       _myMlepbVector.push_back(Mlepb_1lep);
       _mygenMlepbVector.push_back(genMlepb_1lep);
       _myM3bVector.push_back(M3b_1lep);
       _myjetptVector.push_back(jetpt_1lep);
       _myDPhiLepJetVector.push_back(DPhiLepJet_1lep);
       _myleadjetptVector.push_back(leadjetpt_1lep);
       _myDPhiWLep.push_back(DPhiWLep_1lep);
       _myPZeta_TrkLep.push_back(PZeta_TrkLep_1lep);
       _myPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_1lep);
       _myak4NEFVector.push_back(ak4_nef_1lep);
       _myak4CEFVector.push_back(ak4_cef_1lep);
       _myak4EFVector.push_back(ak4_EF_1lep);
       _myWptVector.push_back(Wpt_1lep);

       _myTitles.push_back("t#bar{t} #rightarrow ll");
       _myColors.push_back(kCyan-3);
       _myVector.push_back(MT_2lep);
       _myMT2WVector.push_back(MT2W_2lep);
       _myTopnessVector.push_back(Topness_2lep);
       _myTopnessmodVector.push_back(Topnessmod_2lep);
       _myChi2Vector.push_back(Chi2_2lep);
       _myMinDPhiVector.push_back(MinDPhi_2lep);
       _myHTratioVector.push_back(HTratio_2lep);
       _myDRlepbVector.push_back(DRlepb_2lep);
       _myleadbptVector.push_back(leadbpt_2lep);
       _mymetVector.push_back(met_2lep);
       _mylepptVector.push_back(leppt_2lep);
       _mylepetaVector.push_back(lepeta_2lep);
       _mylepphiVector.push_back(lepphi_2lep);
       _myHTVector.push_back(HT_2lep);
       _mynjetsVector.push_back(njets_2lep);
       _mynbjetsVector.push_back(nbjets_2lep);
       _mynjets_pt200_nobtagsVector.push_back(njets_pt200_nobtags_2lep);
       _myleadISRjet_pt200_nobtagsVector.push_back(leadISRjet_pt200_nobtags_2lep);
       _myMEToverSqrtHTVector.push_back(METoverSqrtHT_2lep);
       _myMlepbVector.push_back(Mlepb_2lep);
       _mygenMlepbVector.push_back(genMlepb_2lep);
       _myM3bVector.push_back(M3b_2lep);
       _myjetptVector.push_back(jetpt_2lep);
       _myDPhiLepJetVector.push_back(DPhiLepJet_2lep);
       _myleadjetptVector.push_back(leadjetpt_2lep);
       _myDPhiWLep.push_back(DPhiWLep_2lep);
       _myPZeta_TrkLep.push_back(PZeta_TrkLep_2lep);
       _myPZetaVis_TrkLep.push_back(PZetaVis_TrkLep_2lep);
       _myak4NEFVector.push_back(ak4_nef_2lep);
       _myak4CEFVector.push_back(ak4_cef_2lep);
       _myak4EFVector.push_back(ak4_EF_2lep);
       _myWptVector.push_back(Wpt_2lep);

       _myColors.push_back(kBlue);
       _myColors.push_back(kTeal+7);
       _myColors.push_back(kRed+3);
       _myColors.push_back(kGreen+3);

}
/*
void BasicHistos::MakeBasicHistoVectors(int process, string name,float signalscale){

    std::string filestr (name);
    cout<<filestr<<" Integral "<<_theMTHistoMap[process]->Integral()<<endl;
    if(filestr.find("T2tt") == string::npos && filestr.find("data") == string::npos){
       _myTitles.push_back(filestr);
       _myVector.push_back(_theMTHistoMap[process]);
       _myMTMHTVector.push_back(_theMTMHTHistoMap[process]);
       _myMTnewmetVector.push_back(_theMTnewmetHistoMap[process]);
       _myMTrawmetVector.push_back(_theMTrawmetHistoMap[process]);
       _mymetVector.push_back(_themetHistoMap[process]);
       _mymetphiVector.push_back(_themetphiHistoMap[process]);
       _myrawmetVector.push_back(_therawmetHistoMap[process]);
       _myrawmetphiVector.push_back(_therawmetphiHistoMap[process]);
       _myjecmetVector.push_back(_thejecmetHistoMap[process]);
       _myjecmetphiVector.push_back(_thejecmetphiHistoMap[process]);
       _myunjecmetVector.push_back(_theunjecmetHistoMap[process]);
       _myunjecmetphiVector.push_back(_theunjecmetphiHistoMap[process]);
       _myjecmetXVector.push_back(_thejecmetXHistoMap[process]);
       _myjecmetYVector.push_back(_thejecmetYHistoMap[process]);
       _mycalometVector.push_back(_thecalometHistoMap[process]);
       _mycalometphiVector.push_back(_thecalometphiHistoMap[process]);
       _mytrkmetVector.push_back(_thetrkmetHistoMap[process]);
       _mytrkmetphiVector.push_back(_thetrkmetphiHistoMap[process]);
       _mylepptVector.push_back(_thelepptHistoMap[process]);
       _myleprelisoVector.push_back(_theleprelisoHistoMap[process]);
       _mylepminirelisoVector.push_back(_thelepminirelisoHistoMap[process]);
       _mylepabsisoVector.push_back(_thelepabsisoHistoMap[process]);
       _mylepminiabsisoVector.push_back(_thelepminiabsisoHistoMap[process]);
       _mylepetaVector.push_back(_thelepetaHistoMap[process]);
       _mylepphiVector.push_back(_thelepphiHistoMap[process]);
       _myHTVector.push_back(_theHTHistoMap[process]);
       _myNGoodVtxVector.push_back(_theNGoodVtxHistoMap[process]);
       _mynjetsVector.push_back(_thenjetsHistoMap[process]);
       _mynhfjetsVector.push_back(_thenhfjetsHistoMap[process]);
       _myjetptVector.push_back(_thejetptHistoMap[process]);
      _myjetetaVector.push_back(_thejetetaHistoMap[process]);
       _myjetphiVector.push_back(_thejetphiHistoMap[process]);
       _myDPhiLepJetVector.push_back(_theDPhiLepJetHistoMap[process]);
       _myleadjetptVector.push_back(_theleadjetptHistoMap[process]);
       _myDPhiWLep.push_back(_theDPhiWLepHistoMap[process]);
       _myWptVector.push_back(_theWptHistoMap[process]);

 /*      if(filestr.find("ttbar") != string::npos){
         cout<<filestr<<" Integral "<<_thelepphiHistoMap_2lep[process]->Integral()<<endl;
         _myTitles.push_back("t#bar{t} #rightarrow ll");
         _myVector.push_back(_theMTHistoMap_2lep[process]);
         _myMT2WVector.push_back(_theMT2WHistoMap_2lep[process]);
         _myChi2Vector.push_back(_theChi2HistoMap_2lep[process]);
         _myMinDPhiVector.push_back(_theMinDPhiHistoMap_2lep[process]);
         _myHTratioVector.push_back(_theHTratioHistoMap_2lep[process]);
         _myDRlepbVector.push_back(_theDRlepbHistoMap_2lep[process]);
         _myleadbptVector.push_back(_theleadbptHistoMap_2lep[process]);
         _mymetVector.push_back(_themetHistoMap_2lep[process]);
         _mymetphiVector.push_back(_themetphiHistoMap_2lep[process]);
         _mylepptVector.push_back(_thelepptHistoMap_2lep[process]);
         _mylepetaVector.push_back(_thelepetaHistoMap_2lep[process]);
         _mylepphiVector.push_back(_thelepphiHistoMap_2lep[process]);
         _myHTVector.push_back(_theHTHistoMap_2lep[process]);
         _mynjetsVector.push_back(_thenjetsHistoMap_2lep[process]);
         _mynbjetsVector.push_back(_thenbjetsHistoMap_2lep[process]);
         _mynjets_pt200_nobtagsVector.push_back(_thenjets_pt200_nobtagsHistoMap_2lep[process]);
         _myleadISRjet_pt200_nobtagsVector.push_back(_theleadISRjet_pt200_nobtagsHistoMap_2lep[process]);
         _myMEToverSqrtHTVector.push_back(_theMEToverSqrtHTHistoMap_2lep[process]);
         _myMlepbVector.push_back(_theMlepbHistoMap_2lep[process]);
         _myM3bVector.push_back(_theM3bHistoMap_2lep[process]);
         _myjetptVector.push_back(_thejetptHistoMap_2lep[process]);
         _myDPhiLepJetVector.push_back(_theDPhiLepJetHistoMap_2lep[process]);
         _myleadjetptVector.push_back(_theleadjetptHistoMap_2lep[process]);
         _myDPhiWLep.push_back(_theDPhiWLepHistoMap_2lep[process]);
         _myWptVector.push_back(_theWptHistoMap_2lep[process]);
         _myPZeta_TrkLep.push_back(_thePZeta_TrkLepHistoMap_2lep[process]);
         _myPZetaVis_TrkLep.push_back(_thePZetaVis_TrkLepHistoMap_2lep[process]);
         _myak4NEFVector.push_back(_theak4NEFHistoMap_2lep[process]);
         _myak4CEFVector.push_back(_theak4CEFHistoMap_2lep[process]);
         _myak4EFVector.push_back(_theak4EFHistoMap_2lep[process]);
      }
i * /
    }else if(filestr.find("data") != string::npos){

       _myDataVector.push_back(_theMTHistoMap[process]);
       _myDataMTMHTVector.push_back(_theMTMHTHistoMap[process]);
       _myDataMTnewmetVector.push_back(_theMTnewmetHistoMap[process]);
       _myDataMTrawmetVector.push_back(_theMTrawmetHistoMap[process]);
       _myDatametVector.push_back(_themetHistoMap[process]);
       _myDatametphiVector.push_back(_themetphiHistoMap[process]);
       _myDatarawmetVector.push_back(_therawmetHistoMap[process]);
       _myDatarawmetphiVector.push_back(_therawmetphiHistoMap[process]);
       _myDatajecmetVector.push_back(_thejecmetHistoMap[process]);
       _myDatajecmetphiVector.push_back(_thejecmetphiHistoMap[process]);
       _myDataunjecmetVector.push_back(_theunjecmetHistoMap[process]);
       _myDataunjecmetphiVector.push_back(_theunjecmetphiHistoMap[process]);
       _myDatajecmetXVector.push_back(_thejecmetXHistoMap[process]);
       _myDatajecmetYVector.push_back(_thejecmetYHistoMap[process]);

       _myDatacalometVector.push_back(_thecalometHistoMap[process]);
       _myDatacalometphiVector.push_back(_thecalometphiHistoMap[process]);
       _myDatatrkmetVector.push_back(_thetrkmetHistoMap[process]);
       _myDatatrkmetphiVector.push_back(_thetrkmetphiHistoMap[process]);

       _myDatalepptVector.push_back(_thelepptHistoMap[process]);
       _myDataleprelisoVector.push_back(_theleprelisoHistoMap[process]);
       _myDatalepminirelisoVector.push_back(_thelepminirelisoHistoMap[process]);
       _myDatalepabsisoVector.push_back(_thelepabsisoHistoMap[process]);
       _myDatalepminiabsisoVector.push_back(_thelepminiabsisoHistoMap[process]);
       _myDatalepetaVector.push_back(_thelepetaHistoMap[process]);
       _myDatalepphiVector.push_back(_thelepphiHistoMap[process]);
       _myDataHTVector.push_back(_theHTHistoMap[process]);
       _myDataNGoodVtxVector.push_back(_theNGoodVtxHistoMap[process]);
       _myDatanjetsVector.push_back(_thenjetsHistoMap[process]);
       _myDatanhfjetsVector.push_back(_thenhfjetsHistoMap[process]);
       _myDatajetptVector.push_back(_thejetptHistoMap[process]);
       _myDatajetphiVector.push_back(_thejetphiHistoMap[process]);
       _myDataDPhiLepJetVector.push_back(_theDPhiLepJetHistoMap[process]);
       _myDataleadjetptVector.push_back(_theleadjetptHistoMap[process]);
       _myDataDPhiWLep.push_back(_theDPhiWLepHistoMap[process]);
       _myDataWptVector.push_back(_theWptHistoMap[process]);
    }else{
       _mySignalVector.push_back(_theMTHistoMap[process]);
       _mySignalmetVector.push_back(_themetHistoMap[process]);
       _mySignalmetphiVector.push_back(_themetphiHistoMap[process]);
       _mySignalrawmetVector.push_back(_therawmetHistoMap[process]);
       _mySignalrawmetphiVector.push_back(_therawmetphiHistoMap[process]);
       _mySignallepptVector.push_back(_thelepptHistoMap[process]);
       _mySignalleprelisoVector.push_back(_theleprelisoHistoMap[process]);
       _mySignallepminirelisoVector.push_back(_thelepminirelisoHistoMap[process]);
       _mySignallepabsisoVector.push_back(_thelepabsisoHistoMap[process]);
       _mySignallepminiabsisoVector.push_back(_thelepminiabsisoHistoMap[process]);
       _mySignallepetaVector.push_back(_thelepetaHistoMap[process]);
       _mySignallepphiVector.push_back(_thelepphiHistoMap[process]);
       _mySignalHTVector.push_back(_theHTHistoMap[process]);
       _mySignalnjetsVector.push_back(_thenjetsHistoMap[process]);
       _mySignalnhfjetsVector.push_back(_thenhfjetsHistoMap[process]);
       _mySignaljetptVector.push_back(_thejetptHistoMap[process]);
       _mySignalDPhiLepJetVector.push_back(_theDPhiLepJetHistoMap[process]);
       _mySignalleadjetptVector.push_back(_theleadjetptHistoMap[process]);
       _mySignalDPhiWLep.push_back(_theDPhiWLepHistoMap[process]);
       _mySignalWptVector.push_back(_theWptHistoMap[process]);

       	if(filestr.find("T2tt(80,100)") != string::npos){
           	_mySignalTitles.push_back(Form("T2tt(80,100)x%4.0f",signalscale));
       }
       	if(filestr.find("T2tt(60,325)") != string::npos){
		_mySignalTitles.push_back(Form("T2tt(60,325)x%4.0f",signalscale));
	}
       	if(filestr.find("T2tt(00,325)") != string::npos){
		_mySignalTitles.push_back(Form("T2tt(00,325)x%4.0f",signalscale));
 	}
       	if(filestr.find("T2tt(425,325)") != string::npos){
		_mySignalTitles.push_back(Form("T2tt(425,325)x%4.0f",signalscale));
	}
    }
}
*/

void BasicHistos::MakeBasicSRPlots2(string label, float Lumi){
  TH1F* null = new TH1F("","",1,0,1);
  std::vector < TH1F* > nullb;
  nullb.push_back(null);
  std::vector < char* > nullname;
  nullname.push_back("");
  dataMCplotMaker(_myDataWptVector.at(0), _myWptVector2, _myTitles2, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --preserveSignalOrder --lumi %1.2f --png --xAxisLabel W p_{T} --outputName WpT_plot_%s",Lumi,label.c_str()),_mySignalWptVector, _mySignalTitles,_myColors2);

  dataMCplotMaker(_myDataWptVector.at(0), _myWptVector2, _myTitles2, "", "", Form("--noXaxisUnit --energy 13 --outOfFrame --preserveSignalOrder --lumi %1.2f --png --xAxisLabel W p_{T} --outputName WpT_plot_%s",Lumi,label.c_str()),_mySignalWptVector, _mySignalTitles,_myColors2);


  dataMCplotMaker(_myDataVector.at(0), _myVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --outputName MT_log_%s",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMT2WVector.at(0), _myMT2WVector2, _myTitles2, "", "", Form("--vLine 200 --xAxisLabel MT2W      --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_log_%s",Lumi,label.c_str()),_mySignalMT2WVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataTopnessVector.at(0), _myTopnessVector2, _myTitles2, "", "", Form(" --xAxisLabel amt2 --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2_lb_b_log_%s",Lumi,label.c_str()),_mySignalTopnessVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataTopnessmodVector.at(0), _myTopnessmodVector2, _myTitles2, "", "", Form(" --xAxisLabel Topnessmod --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topnessmod_log_%s",Lumi,label.c_str()),_mySignalTopnessmodVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataChi2Vector.at(0), _myChi2Vector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel Hadronic top #chi^{2} --outputName Chi2_log_%s",Lumi,label.c_str()),_mySignalChi2Vector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMinDPhiVector.at(0), _myMinDPhiVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel min(#Delta#phi(met, j_{1,2,3})) --outputName MinDPhi_log_%s",Lumi,label.c_str()),_mySignalMinDPhiVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataHTratioVector.at(0), _myHTratioVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel H_{T}(SSM)/H_{T} --outputName HTRatio_log_%s",Lumi,label.c_str()),_mySignalHTratioVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDRlepbVector.at(0), _myDRlepbVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel #DeltaR(lep,b_{lead}) --outputName DRLep1b_log_%s",Lumi,label.c_str()),_mySignalDRlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadbptVector.at(0), _myleadbptVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel b_{lead} p_{T} --outputName leadbpt_log_%s",Lumi,label.c_str()),_mySignalleadbptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatametVector.at(0), _mymetVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel MET --outputName met_log_%s",Lumi,label.c_str()),_mySignalmetVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepptVector.at(0), _mylepptVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Lepton p_{T} --outputName leppt_log_%s",Lumi,label.c_str()),_mySignallepptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepetaVector.at(0), _mylepetaVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel Lepton #eta --outputName lepeta_log_%s",Lumi,label.c_str()),_mySignallepetaVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepphiVector.at(0), _mylepphiVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel #phi(lep,met) --outputName lepphi_log_%s",Lumi,label.c_str()),_mySignallepphiVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataHTVector.at(0), _myHTVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel H_{T} --outputName HT_log_%s",Lumi,label.c_str()),_mySignalHTVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMlepbVector.at(0), _myMlepbVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName Mlepblead_log_%s",Lumi,label.c_str()),_mySignalMlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(null, _mygenMlepbVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName gen Mlepblead_log_%s",Lumi,label.c_str()),_mySignalgenMlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataM3bVector.at(0), _myM3bVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #frac{p_{T}^{leadjet} - p_{T}^{subleadjet}}{p_{T}^{leadjet} +p_{T}^{subleadjet}} --outputName pTassym_log_%s",Lumi,label.c_str()),_mySignalM3bVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatanjetsVector.at(0), _mynjetsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected Jets --outputName njets_log_%s",Lumi,label.c_str()),_mySignalnjetsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatanbjetsVector.at(0), _mynbjetsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected B-tagged Jets --outputName nbjets_log_%s",Lumi,label.c_str()),_mySignalnbjetsVector, _mySignalTitles,_myColors2);

//dataMCplotMaker(_myData.at(0), _mySignalMT2WVector2, _mySignalTitles2, "", "", Form("--vLine 200 --isLinear --setMaximum 0.6 --noStack --vLine 120 --xAxisLabel MT2W --normalize  --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_signal_%s",Lumi,label.c_str()));

  dataMCplotMaker(_myDatanjets_pt200_nobtagsVector.at(0), _mynjets_pt200_nobtagsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected non-btagged Jets with p_{T}>200GeV (Njet> 4) --outputName njets_pt200_nobtags_log_%s",Lumi,label.c_str()),_mySignalnjets_pt200_nobtagsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadISRjet_pt200_nobtagsVector.at(0), _myleadISRjet_pt200_nobtagsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel  p_{T}(leading non-b-jet) (Njet> 4, p_{T}>200GeV) --outputName leadISRjet_pt200_nobtags_log_%s",Lumi,label.c_str()),_mySignalleadISRjet_pt200_nobtagsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMEToverSqrtHTVector.at(0), _myMEToverSqrtHTVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel (H^{miss}_{T}-100)/sqrt(H_{T}) --outputName MHToverSqrtMHT_log_%s",Lumi,label.c_str()),_mySignalMEToverSqrtHTVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatajetptVector.at(0), _myjetptVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet p_{T} --outputName jetpt_log_%s",Lumi,label.c_str()),_mySignaljetptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDPhiLepJetVector.at(0), _myDPhiLepJetVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(lep,jet) --outputName DPhiLepJet_log_%s",Lumi,label.c_str()),_mySignalDPhiLepJetVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadjetptVector.at(0), _myleadjetptVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet_{lead} p_{T} --outputName leadjetpt_log_%s",Lumi,label.c_str()),_mySignalleadjetptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDPhiWLep.at(0), _myDPhiWLepVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(W,Lep) --outputName DPhiWLep_log_%s",Lumi,label.c_str()),_mySignalDPhiWLep, _mySignalTitles,_myColors2);
  PlotMaker2D(genHT_recoHT,"--png --Xaxis gen H_{T}  --Yaxis reco H_{T} --colors --outputName genHT_recoHT_2lep");

}

void BasicHistos::MakeBasicSRPlots(string label, float Lumi){

  TH1F* null = new TH1F("","",1,0,1);
  std::vector < TH1F* > nullb;
  nullb.push_back(null);
  std::vector < char* > nullname;
  nullname.push_back("");
  dataMCplotMaker(_myDataVector.at(0), _myVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --outputName MT_log_%s",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMT2WVector.at(0), _myMT2WVector, _myTitles, "", "", Form("--vLine 200 --xAxisLabel MT2W      --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_log_%s",Lumi,label.c_str()),_mySignalMT2WVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataTopnessVector.at(0), _myTopnessVector, _myTitles, "", "", Form(" --xAxisLabel amt2 --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2_lb_b_log_%s",Lumi,label.c_str()),_mySignalTopnessVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataTopnessmodVector.at(0), _myTopnessmodVector, _myTitles, "", "", Form(" --xAxisLabel Topnessmod --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topnessmod_log_%s",Lumi,label.c_str()),_mySignalTopnessmodVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataChi2Vector.at(0), _myChi2Vector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel Hadronic top #chi^{2} --outputName Chi2_log_%s",Lumi,label.c_str()),_mySignalChi2Vector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMinDPhiVector.at(0), _myMinDPhiVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel min(#Delta#phi(met, j_{1,2,3})) --outputName MinDPhi_log_%s",Lumi,label.c_str()),_mySignalMinDPhiVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataHTratioVector.at(0), _myHTratioVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel H_{T}(SSM)/H_{T} --outputName HTRatio_log_%s",Lumi,label.c_str()),_mySignalHTratioVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDRlepbVector.at(0), _myDRlepbVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel #DeltaR(lep,b_{lead}) --outputName DRLep1b_log_%s",Lumi,label.c_str()),_mySignalDRlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadbptVector.at(0), _myleadbptVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel b_{lead} p_{T} --outputName leadbpt_log_%s",Lumi,label.c_str()),_mySignalleadbptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatametVector.at(0), _mymetVector, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel MET --outputName met_log_%s",Lumi,label.c_str()),_mySignalmetVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepptVector.at(0), _mylepptVector, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Lepton p_{T} --outputName leppt_log_%s",Lumi,label.c_str()),_mySignallepptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepetaVector.at(0), _mylepetaVector, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel Lepton #eta --outputName lepeta_log_%s",Lumi,label.c_str()),_mySignallepetaVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepphiVector.at(0), _mylepphiVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel #phi(lep,met) --outputName lepphi_log_%s",Lumi,label.c_str()),_mySignallepphiVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataHTVector.at(0), _myHTVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel H_{T} --outputName HT_log_%s",Lumi,label.c_str()),_mySignalHTVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMlepbVector.at(0), _myMlepbVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName Mlepblead_log_%s",Lumi,label.c_str()),_mySignalMlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(null, _mygenMlepbVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName gen Mlepblead_log_%s",Lumi,label.c_str()),_mySignalgenMlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataM3bVector.at(0), _myM3bVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #frac{p_{T}^{leadjet} - p_{T}^{subleadjet}}{p_{T}^{leadjet} +p_{T}^{subleadjet}} --outputName pTassym_log_%s",Lumi,label.c_str()),_mySignalM3bVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatanjetsVector.at(0), _mynjetsVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected Jets --outputName njets_log_%s",Lumi,label.c_str()),_mySignalnjetsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatanbjetsVector.at(0), _mynbjetsVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected B-tagged Jets --outputName nbjets_log_%s",Lumi,label.c_str()),_mySignalnbjetsVector, _mySignalTitles,_myColors);

//dataMCplotMaker(_myData.at(0), _mySignalMT2WVector, _mySignalTitles, "", "", Form("--vLine 200 --isLinear --setMaximum 0.6 --noStack --vLine 120 --xAxisLabel MT2W --normalize  --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_signal_%s",Lumi,label.c_str()));

  dataMCplotMaker(_myDatanjets_pt200_nobtagsVector.at(0), _mynjets_pt200_nobtagsVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected non-btagged Jets with p_{T}>200GeV (Njet> 4) --outputName njets_pt200_nobtags_log_%s",Lumi,label.c_str()),_mySignalnjets_pt200_nobtagsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadISRjet_pt200_nobtagsVector.at(0), _myleadISRjet_pt200_nobtagsVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel  p_{T}(leading non-b-jet) (Njet> 4, p_{T}>200GeV) --outputName leadISRjet_pt200_nobtags_log_%s",Lumi,label.c_str()),_mySignalleadISRjet_pt200_nobtagsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMEToverSqrtHTVector.at(0), _myMEToverSqrtHTVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel (H^{miss}_{T}-100)/sqrt(H_{T}) --outputName MHToverSqrtMHT_log_%s",Lumi,label.c_str()),_mySignalMEToverSqrtHTVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatajetptVector.at(0), _myjetptVector, _myTitles, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet p_{T} --outputName jetpt_log_%s",Lumi,label.c_str()),_mySignaljetptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDPhiLepJetVector.at(0), _myDPhiLepJetVector, _myTitles, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(lep,jet) --outputName DPhiLepJet_log_%s",Lumi,label.c_str()),_mySignalDPhiLepJetVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadjetptVector.at(0), _myleadjetptVector, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet_{lead} p_{T} --outputName leadjetpt_log_%s",Lumi,label.c_str()),_mySignalleadjetptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDPhiWLep.at(0), _myDPhiWLep, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(W,Lep) --outputName DPhiWLep_log_%s",Lumi,label.c_str()),_mySignalDPhiWLep, _mySignalTitles,_myColors);
dataMCplotMaker(_myDataPZeta_TrkLep.at(0), _myPZeta_TrkLep, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel CDF P_{#Zeta}(lep,leadJet) --outputName PZeta_LeadJLep_log_%s",Lumi,label.c_str()),_mySignalPZeta_TrkLep, _mySignalTitles,_myColors);
dataMCplotMaker(_myDataPZetaVis_TrkLep.at(0), _myPZetaVis_TrkLep, _myTitles, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel CDF P_{#Zeta}^{Vis}(lep,leadJet) --outputName PZetaVis_LeadJetLep_log_%s",Lumi,label.c_str()),_mySignalPZetaVis_TrkLep, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataVector.at(0), _myVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --outputName MT__%s",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMT2WVector.at(0), _myMT2WVector, _myTitles, "", "", Form("--vLine 200 --xAxisLabel MT2W     --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W__%s",Lumi,label.c_str()),_mySignalMT2WVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataTopnessVector.at(0), _myTopnessVector, _myTitles, "", "", Form("--isLinear --xAxisLabel Topness --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topness__%s",Lumi,label.c_str()),_mySignalTopnessVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataTopnessmodVector.at(0), _myTopnessmodVector, _myTitles, "", "", Form("--isLinear --xAxisLabel Topnessmod --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topnessmod__%s",Lumi,label.c_str()),_mySignalTopnessmodVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataChi2Vector.at(0), _myChi2Vector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel Hadronic top #chi^{2} --outputName Chi2__%s",Lumi,label.c_str()),_mySignalChi2Vector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMinDPhiVector.at(0), _myMinDPhiVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel min(#Delta#phi(met, j_{1,2})) --outputName MinDPhi__%s",Lumi,label.c_str()),_mySignalMinDPhiVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataHTratioVector.at(0), _myHTratioVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel H_{T}(SSM)/H_{T} --outputName HTRatio__%s",Lumi,label.c_str()),_mySignalHTratioVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDRlepbVector.at(0), _myDRlepbVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel #DeltaR(lep,b_{lead}) --outputName DRLep1b__%s",Lumi,label.c_str()),_mySignalDRlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadbptVector.at(0), _myleadbptVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel b_{lead} p_{T} --outputName leadbpt__%s",Lumi,label.c_str()),_mySignalleadbptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatametVector.at(0), _mymetVector, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel MET --outputName met__%s",Lumi,label.c_str()),_mySignalmetVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepptVector.at(0), _mylepptVector, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Lepton p_{T} --outputName leppt__%s",Lumi,label.c_str()),_mySignallepptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepetaVector.at(0), _mylepetaVector, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel Lepton #eta --outputName lepeta__%s",Lumi,label.c_str()),_mySignallepetaVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatalepphiVector.at(0), _mylepphiVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel #phi(lep,met) --outputName lepphi__%s",Lumi,label.c_str()),_mySignallepphiVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataHTVector.at(0), _myHTVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel H_{T} --outputName HT__%s",Lumi,label.c_str()),_mySignalHTVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMlepbVector.at(0), _myMlepbVector, _myTitles, "", "", Form("--isLinear --noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName Mlepblead__%s",Lumi,label.c_str()),_mySignalMlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(null, _mygenMlepbVector, _myTitles, "", "", Form("--isLinear --noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName gen Mlepblead__%s",Lumi,label.c_str()),_mySignalgenMlepbVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataM3bVector.at(0), _myM3bVector, _myTitles, "", "", Form("--isLinear --noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #frac{p_{T}^{leadjet} - p_{T}^{subleadjet}}{p_{T}^{leadjet} +p_{T}^{subleadjet}} --outputName pTassym__%s",Lumi,label.c_str()),_mySignalM3bVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatanjetsVector.at(0), _mynjetsVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected Jets --outputName njets__%s",Lumi,label.c_str()),_mySignalnjetsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatanbjetsVector.at(0), _mynbjetsVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected B-tagged Jets --outputName nbjets__%s",Lumi,label.c_str()),_mySignalnbjetsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatanjets_pt200_nobtagsVector.at(0), _mynjets_pt200_nobtagsVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected non-btagged Jets with p_{T}>200GeV (Njet> 4) --outputName njets_pt200_nobtags__%s",Lumi,label.c_str()),_mySignalnjets_pt200_nobtagsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadISRjet_pt200_nobtagsVector.at(0), _myleadISRjet_pt200_nobtagsVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel  p_{T}(leading non-b-jet) (Njet> 4, p_{T}>200GeV) --outputName leadISRjet_pt200_nobtags__%s",Lumi,label.c_str()),_mySignalleadISRjet_pt200_nobtagsVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataMEToverSqrtHTVector.at(0), _myMEToverSqrtHTVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel (H^{miss}_{T}-100)/sqrt(H_{T}) --outputName MHToverSqrtMHT__%s",Lumi,label.c_str()),_mySignalMEToverSqrtHTVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDatajetptVector.at(0), _myjetptVector, _myTitles, "", "", Form(" --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet p_{T} --outputName jetpt__%s",Lumi,label.c_str()),_mySignaljetptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDPhiLepJetVector.at(0), _myDPhiLepJetVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(lep,jet) --outputName DPhiLepJet__%s",Lumi,label.c_str()),_mySignalDPhiLepJetVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataleadjetptVector.at(0), _myleadjetptVector, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet_{lead} p_{T} --outputName leadjetpt__%s",Lumi,label.c_str()),_mySignalleadjetptVector, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataDPhiWLep.at(0), _myDPhiWLep, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(W,Lep) --outputName DPhiWLep__%s",Lumi,label.c_str()),_mySignalDPhiWLep, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataPZeta_TrkLep.at(0), _myPZeta_TrkLep, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel CDF P_{#Zeta}(lep,leadJet) --outputName PZeta_LeadJetLep__%s",Lumi,label.c_str()),_mySignalPZeta_TrkLep, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataPZetaVis_TrkLep.at(0), _myPZetaVis_TrkLep, _myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel CDF P_{#Zeta}^{Vis}(lep,leadJet) --outputName PZetaVis_LeadJetLep__%s",Lumi,label.c_str()),_mySignalPZetaVis_TrkLep, _mySignalTitles,_myColors);
  dataMCplotMaker(_myDataWptVector.at(0), _myWptVector, _myTitles, "", "", Form("--noXaxisUnit --isLinear  --energy 13 --outOfFrame --preserveSignalOrder --lumi %1.2f  --png --xAxisLabel W p_{T} --outputName WpT_plot_%s",Lumi,label.c_str()),_mySignalWptVector, _mySignalTitles,_myColors);

  dataMCplotMaker(_myDataWptVector.at(0), _myWptVector, _myTitles, "", "", Form("--noXaxisUnit --energy 13 --outOfFrame --preserveSignalOrder --lumi %1.2f  --png --xAxisLabel W p_{T} --outputName WpT_plot_%s",Lumi,label.c_str()),_mySignalWptVector, _mySignalTitles,_myColors);

/*  dataMCplotMaker(_myData.at(0), _myak4NEFVector,_myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jets E_{T}^{3}  --outputName Avi7__%s",Lumi,label.c_str()),_mySignal_ak4NEFVector, _mySignalTitles,_myColors);
 *    dataMCplotMaker(_myData.at(0), _myak4CEFVector,_myTitles, "", "", Form("--isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jets E_{T}^{4} --outputName Avi6__%s",Lumi,label.c_str()),_mySignal_ak4CEFVector, _mySignalTitles,_myColors);
 *      dataMCplotMaker(_myData.at(0), _myak4EFVector,_myTitles, "", "", Form("--setMaximum 120 --isLinear  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel ak4 EF --outputName ak4EF__%s",Lumi,label.c_str()),_mySignal_ak4EFVector, _mySignalTitles,_myColors);
 *      */
//  PlotMaker2D(jetPt2D_2lep,"--png --Xaxis lead-jet p_{T}  --Yaxis sublead-jet p_{T} --colors --outputName jetPt2D_2lep");
/*  dataMCplotMaker(_myDataVector.at(0), _myVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT_log_%s_new",Lumi,label.c_str()),_mySignalVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMT2WVector.at(0), _myMT2WVector2, _myTitles2, "", "", Form("--vLine 200 --xAxisLabel MT2W      --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_log_%s_new",Lumi,label.c_str()),_mySignalMT2WVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataTopnessVector.at(0), _myTopnessVector2, _myTitles2, "", "", Form(" --xAxisLabel Topness --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topness_log_%s_new",Lumi,label.c_str()),_mySignalTopnessVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataTopnessmodVector.at(0), _myTopnessmodVector2, _myTitles2, "", "", Form(" --xAxisLabel Topnessmod --energy 13 --outOfFrame --lumi %1.2f --png --outputName Topnessmod_log_%s_new",Lumi,label.c_str()),_mySignalTopnessmodVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataChi2Vector.at(0), _myChi2Vector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel Hadronic top #chi^{2} --outputName Chi2_log_%s_new",Lumi,label.c_str()),_mySignalChi2Vector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMinDPhiVector.at(0), _myMinDPhiVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel min(#Delta#phi(met, j_{1,2,3})) --outputName MinDPhi_log_%s_new",Lumi,label.c_str()),_mySignalMinDPhiVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataHTratioVector.at(0), _myHTratioVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel H_{T}(SSM)/H_{T} --outputName HTRatio_log_%s_new",Lumi,label.c_str()),_mySignalHTratioVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDRlepbVector.at(0), _myDRlepbVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --noXaxisUnit --png --xAxisLabel #DeltaR(lep,b_{lead}) --outputName DRLep1b_log_%s_new",Lumi,label.c_str()),_mySignalDRlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadbptVector.at(0), _myleadbptVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel b_{lead} p_{T} --outputName leadbpt_log_%s_new",Lumi,label.c_str()),_mySignalleadbptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatametVector.at(0), _mymetVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel MET --outputName met_log_%s_new",Lumi,label.c_str()),_mySignalmetVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepptVector.at(0), _mylepptVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Lepton p_{T} --outputName leppt_log_%s_new",Lumi,label.c_str()),_mySignallepptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepetaVector.at(0), _mylepetaVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel Lepton #eta --outputName lepeta_log_%s_new",Lumi,label.c_str()),_mySignallepetaVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatalepphiVector.at(0), _mylepphiVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --noXaxisUnit --xAxisLabel #phi(lep,met) --outputName lepphi_log_%s_new",Lumi,label.c_str()),_mySignallepphiVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataHTVector.at(0), _myHTVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel H_{T} --outputName HT_log_%s_new",Lumi,label.c_str()),_mySignalHTVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMlepbVector.at(0), _myMlepbVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName Mlepblead_log_%s_new",Lumi,label.c_str()),_mySignalMlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(null, _mygenMlepbVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel M(lep,b_{lead})  --outputName gen Mlepblead_log_%s_new",Lumi,label.c_str()),_mySignalgenMlepbVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataM3bVector.at(0), _myM3bVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #frac{p_{T}^{leadjet} - p_{T}^{subleadjet}}{p_{T}^{leadjet} +p_{T}^{subleadjet}} --outputName pTassym_log_%s_new",Lumi,label.c_str()),_mySignalM3bVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatanjetsVector.at(0), _mynjetsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected Jets --outputName njets_log_%s_new",Lumi,label.c_str()),_mySignalnjetsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatanbjetsVector.at(0), _mynbjetsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected B-tagged Jets --outputName nbjets_log_%s_new",Lumi,label.c_str()),_mySignalnbjetsVector, _mySignalTitles,_myColors2);

//dataMCplotMaker(_myData.at(0), _mySignalMT2WVector2, _mySignalTitles2, "", "", Form("--vLine 200 --isLinear --setMaximum 0.6 --noStack --vLine 120 --xAxisLabel MT2W --normalize  --energy 13 --outOfFrame --lumi %1.2f --png --outputName MT2W_signal_%s",Lumi,label.c_str()));

  dataMCplotMaker(_myDatanjets_pt200_nobtagsVector.at(0), _mynjets_pt200_nobtagsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel Number of Selected non-btagged Jets with p_{T}>200GeV (Njet> 4) --outputName njets_pt200_nobtags_log_%s_new",Lumi,label.c_str()),_mySignalnjets_pt200_nobtagsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadISRjet_pt200_nobtagsVector.at(0), _myleadISRjet_pt200_nobtagsVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel  p_{T}(leading non-b-jet) (Njet> 4, p_{T}>200GeV) --outputName leadISRjet_pt200_nobtags_log_%s_new",Lumi,label.c_str()),_mySignalleadISRjet_pt200_nobtagsVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataMEToverSqrtHTVector.at(0), _myMEToverSqrtHTVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel MET/sqrt(H_{T}) --outputName METoverSqrtHT_log_%s_new",Lumi,label.c_str()),_mySignalMEToverSqrtHTVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDatajetptVector.at(0), _myjetptVector2, _myTitles2, "", "", Form("  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet p_{T} --outputName jetpt_log_%s_new",Lumi,label.c_str()),_mySignaljetptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDPhiLepJetVector.at(0), _myDPhiLepJetVector2, _myTitles2, "", "", Form("--noXaxisUnit  --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(lep,jet) --outputName DPhiLepJet_log_%s_new",Lumi,label.c_str()),_mySignalDPhiLepJetVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataleadjetptVector.at(0), _myleadjetptVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel jet_{lead} p_{T} --outputName leadjetpt_log_%s_new",Lumi,label.c_str()),_mySignalleadjetptVector, _mySignalTitles,_myColors2);
  dataMCplotMaker(_myDataDPhiWLep.at(0), _myDPhiWLepVector2, _myTitles2, "", "", Form(" --energy 13 --outOfFrame --lumi %1.2f --png --xAxisLabel #Delta#phi(W,Lep) --outputName DPhiWLep_log_%s_new",Lumi,label.c_str()),_mySignalDPhiWLep, _mySignalTitles,_myColors2);
  PlotMaker2D(genHT_recoHT,"--png --Xaxis gen H_{T}  --Yaxis reco H_{T} --colors --outputName genHT_recoHT_2lep");
*/
}

void BasicHistos::Make2DMetPlots(int vIt, string label){
//PlotMaker2D(TH2F* plot, std::string options);
//--outputName X: to specify the name of the output PDF.
//--noOverflow: if you don't want underflow/overflow to be put into first/last bin.
//--setTitle X
//--Xaxis X
//--Yaxis X
//--sciNot X: to put your bin contents into scientific notation. X is a printf string (ie --sciNot .2 will give you two decimal places)
//--colors: if you want each bin to be colored proportional to its value
  PlotMaker2D(_thejetPt2DHistoMap[vIt], Form("--png --Xaxis lead-jet p_{T}  --Yaxis sublead-jet p_{T} --colors --outputName jetPt2D_%s",label.c_str()));
  PlotMaker2D(jetPt2D_2lep,                  "--png --Xaxis lead-jet p_{T}  --Yaxis sublead-jet p_{T} --colors --outputName jetPt2D_2lep");
  PlotMaker2D(_theMlepb2DHistoMap[vIt], Form("--png --Xaxis M(lep,b_{lead}) --Yaxis M(lep,b_{sublead}) --colors --outputName Mlepb2D_%s",label.c_str()));
  PlotMaker2D(Mlepb2D_2lep,                  "--png --Xaxis M(lep,b_{lead})  --Yaxis M(lep,b_{sublead})  --colors --outputName Mlepb2D2D_2lep");
  PlotMaker2D(_thegenMlepb2DHistoMap[vIt], Form("--png --Xaxis M(lep,b_{lead}) --Yaxis M(lep,b_{sublead}) --colors --outputName genMlepb2D_%s",label.c_str()));
  PlotMaker2D(genMlepb2D_2lep,                  "--png --Xaxis M(lep,b_{lead})  --Yaxis M(lep,b_{sublead})  --colors --outputName genMlepb2D2D_2lep");
//  PlotMaker2D(jetPt2D_2lep, Form("--png --Xaxis phi --YAxis eta --colors --outputName jetPt2D_2lep_%s",label.c_str()));
}

void BasicHistos::FillSRHistos_Dilep(int process,float scale){
    int n_isr = 0;
           MT_Dilep->Fill(mt_met_lep(),scale);
           MT2W_Dilep->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
//    if(AMT2<= 170.) return false;
           Topness_Dilep->Fill(AMT2,scale);
           Topnessmod_Dilep->Fill(topnessMod(),scale);
           Chi2_Dilep->Fill(hadronic_top_chi2(),scale);
           MinDPhi_Dilep->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_Dilep->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_Dilep->Fill(ak4_htratiom(),scale);
           //DRlepb_Dilep->Fill(dR_lep_leadb(),scale);
           leadbpt_Dilep->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_Dilep->Fill(pfmet(),scale);
           leppt_Dilep->Fill(lep1_p4().pt(),scale);
           lepeta_Dilep->Fill(lep1_p4().eta(),scale);
           lepphi_Dilep->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_Dilep->Fill(ak4_HT(),scale);
           Mlepb_Dilep->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_Dilep->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_Dilep->Fill(ngoodjets(),scale);
           nbjets_Dilep->Fill(ngoodbtags(),scale);
           METoverSqrtHT_Dilep->Fill(getMHTSig(),scale);
           DPhiWLep_Dilep->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
              //  PZeta_TrkLep_Dilep->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
                //PZetaVis_TrkLep_Dilep->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_Dilep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_Dilep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_Dilep->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_Dilep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_Dilep->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_Dilep->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_Dilep->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_Dilep->Fill(n_isr,scale);
           Wpt_Dilep->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_SingleLep_notfromtop(int process,float scale){
    int n_isr = 0;

   const int pdg_c = 4;
   const int pdg_b = 5;
   int nbs=0;
   int ncs=0;
   int nlf=0;
   for(int i=0;i<ak4pfjets_parton_flavor().size();i++){
      if(abs(ak4pfjets_parton_flavor().at(i)) ==pdg_c) ncs++;
      if(abs(ak4pfjets_parton_flavor().at(i)) ==pdg_b) nbs++;
      //if(abs(ak4pfjets_parton_flavor().at(i))<pdg_c) nlf++;
   }

   if(nbs>0) eventswithb_met_notfromtop->Fill(pfmet(),scale);
   else if(ncs>0) eventswithc_met_notfromtop->Fill(pfmet(),scale);
   else if((nbs+ncs)<1) eventswithlf_met_notfromtop->Fill(pfmet(),scale);

           MT_SingleLep_notfromtop->Fill(mt_met_lep(),scale);
           MT2W_SingleLep_notfromtop->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_SingleLep_notfromtop->Fill(AMT2,scale);
           Topnessmod_SingleLep_notfromtop->Fill(topnessMod(),scale);
           Chi2_SingleLep_notfromtop->Fill(hadronic_top_chi2(),scale);
           MinDPhi_SingleLep_notfromtop->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_SingleLep_notfromtop->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_SingleLep_notfromtop->Fill(ak4_htratiom(),scale);
         //  DRlepb_SingleLep_notfromtop->Fill(dR_lep_leadb(),scale);
           leadbpt_SingleLep_notfromtop->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_SingleLep_notfromtop->Fill(pfmet(),scale);
           leppt_SingleLep_notfromtop->Fill(lep1_p4().pt(),scale);
           lepeta_SingleLep_notfromtop->Fill(lep1_p4().eta(),scale);
           lepphi_SingleLep_notfromtop->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_SingleLep_notfromtop->Fill(ak4_HT(),scale);
           Mlepb_SingleLep_notfromtop->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_SingleLep_notfromtop->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_SingleLep_notfromtop->Fill(ngoodjets(),scale);
           nbjets_SingleLep_notfromtop->Fill(ngoodbtags(),scale);
           METoverSqrtHT_SingleLep_notfromtop->Fill(getMHTSig(),scale);
           DPhiWLep_SingleLep_notfromtop->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
                //PZeta_TrkLep_SingleLep_notfromtop->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_SingleLep_notfromtop->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_SingleLep_notfromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_SingleLep_notfromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_SingleLep_notfromtop->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_SingleLep_notfromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_SingleLep_notfromtop->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_SingleLep_notfromtop->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_SingleLep_notfromtop->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_SingleLep_notfromtop->Fill(n_isr,scale);
           Wpt_SingleLep_notfromtop->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}


void BasicHistos::FillSRHistos_SingleLep_fromtop(int process,float scale){
    int n_isr = 0;
           MT_SingleLep_fromtop->Fill(mt_met_lep(),scale);
           MT2W_SingleLep_fromtop->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_SingleLep_fromtop->Fill(AMT2,scale);
           Topnessmod_SingleLep_fromtop->Fill(topnessMod(),scale);
           Chi2_SingleLep_fromtop->Fill(hadronic_top_chi2(),scale);
           MinDPhi_SingleLep_fromtop->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_SingleLep_fromtop->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_SingleLep_fromtop->Fill(ak4_htratiom(),scale);
           //DRlepb_SingleLep_fromtop->Fill(dR_lep_leadb(),scale);
           leadbpt_SingleLep_fromtop->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_SingleLep_fromtop->Fill(pfmet(),scale);
           leppt_SingleLep_fromtop->Fill(lep1_p4().pt(),scale);
           lepeta_SingleLep_fromtop->Fill(lep1_p4().eta(),scale);
           lepphi_SingleLep_fromtop->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_SingleLep_fromtop->Fill(ak4_HT(),scale);
           Mlepb_SingleLep_fromtop->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_SingleLep_fromtop->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_SingleLep_fromtop->Fill(ngoodjets(),scale);
           nbjets_SingleLep_fromtop->Fill(ngoodbtags(),scale);
           METoverSqrtHT_SingleLep_fromtop->Fill(getMHTSig(),scale);
           DPhiWLep_SingleLep_fromtop->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
               // PZeta_TrkLep_SingleLep_fromtop->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
              //  PZetaVis_TrkLep_SingleLep_fromtop->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_SingleLep_fromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_SingleLep_fromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_SingleLep_fromtop->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_SingleLep_fromtop->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_SingleLep_fromtop->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_SingleLep_fromtop->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_SingleLep_fromtop->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_SingleLep_fromtop->Fill(n_isr,scale);
          Wpt_SingleLep_fromtop->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_Znunu(int process,float scale){
    int n_isr = 0;
           MT_Znunu->Fill(mt_met_lep(),scale);
           MT2W_Znunu->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_Znunu->Fill(AMT2,scale);
           Topnessmod_Znunu->Fill(topnessMod(),scale);
           Chi2_Znunu->Fill(hadronic_top_chi2(),scale);
           MinDPhi_Znunu->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_Znunu->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_Znunu->Fill(ak4_htratiom(),scale);
           //DRlepb_Znunu->Fill(dR_lep_leadb(),scale);
           leadbpt_Znunu->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_Znunu->Fill(pfmet(),scale);
           leppt_Znunu->Fill(lep1_p4().pt(),scale);
           lepeta_Znunu->Fill(lep1_p4().eta(),scale);
           lepphi_Znunu->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_Znunu->Fill(ak4_HT(),scale);
           Mlepb_Znunu->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_Znunu->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_Znunu->Fill(ngoodjets(),scale);
           nbjets_Znunu->Fill(ngoodbtags(),scale);
           METoverSqrtHT_Znunu->Fill(getMHTSig(),scale);
           DPhiWLep_Znunu->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
              //  PZeta_TrkLep_Znunu->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
              //  PZetaVis_TrkLep_Znunu->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_Znunu->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_Znunu->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_Znunu->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_Znunu->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_Znunu->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_Znunu->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_Znunu->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_Znunu->Fill(n_isr,scale);
          Wpt_Znunu->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_1lep(int process,float scale){
    int n_isr = 0;
           MT_1lep->Fill(mt_met_lep(),scale);
           MT2W_1lep->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_1lep->Fill(AMT2,scale);
           Topnessmod_1lep->Fill(topnessMod(),scale);
           Chi2_1lep->Fill(hadronic_top_chi2(),scale);
           MinDPhi_1lep->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_1lep->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_1lep->Fill(ak4_htratiom(),scale);
           //DRlepb_1lep->Fill(dR_lep_leadb(),scale);
           leadbpt_1lep->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_1lep->Fill(pfmet(),scale);
           leppt_1lep->Fill(lep1_p4().pt(),scale);
           lepeta_1lep->Fill(lep1_p4().eta(),scale);
           lepphi_1lep->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_1lep->Fill(ak4_HT(),scale);
           Mlepb_1lep->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_1lep->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_1lep->Fill(ngoodjets(),scale);
           nbjets_1lep->Fill(ngoodbtags(),scale);
           METoverSqrtHT_1lep->Fill(getMHTSig(),scale);
           DPhiWLep_1lep->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
               // PZeta_TrkLep_1lep->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_1lep->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_1lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_1lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_1lep->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_1lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_1lep->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_1lep->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_1lep->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_1lep->Fill(n_isr,scale);

           Wpt_1lep->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_data(int process,float scale){
    int n_isr = 0;
           MT_data->Fill(mt_met_lep(),scale);
           MT2W_data->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_data->Fill(AMT2,scale);
           Topnessmod_data->Fill(topnessMod(),scale);
           Chi2_data->Fill(hadronic_top_chi2(),scale);
           MinDPhi_data->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_data->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_data->Fill(ak4_htratiom(),scale);
           //DRlepb_data->Fill(dR_lep_leadb(),scale);
           leadbpt_data->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_data->Fill(pfmet(),scale);
           leppt_data->Fill(lep1_p4().pt(),scale);
           lepeta_data->Fill(lep1_p4().eta(),scale);
           lepphi_data->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_data->Fill(ak4_HT(),scale);
           Mlepb_data->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_data->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_data->Fill(ngoodjets(),scale);
           nbjets_data->Fill(ngoodbtags(),scale);
           METoverSqrtHT_data->Fill(getMHTSig(),scale);
           DPhiWLep_data->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
           //    PZeta_TrkLep_data->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
             //   PZetaVis_TrkLep_data->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_data->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_data->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_data->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_data->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_data->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_data->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_data->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_data->Fill(n_isr,scale);
           Wpt_data->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_2lep(int process,float scale){
    int n_isr = 0;
    int nb = 0;
     if(ngoodjets()>1) jetPt2D_2lep->Fill(ak4pfjets_p4().at(0).pt(),ak4pfjets_p4().at(1).pt());
           MT_2lep->Fill(mt_met_lep(),scale);
           MT2W_2lep->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_2lep->Fill(AMT2,scale);
           Topnessmod_2lep->Fill(topnessMod(),scale);
           Chi2_2lep->Fill(hadronic_top_chi2(),scale);
           MinDPhi_2lep->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_2lep->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_2lep->Fill(ak4_htratiom(),scale);
           //DRlepb_2lep->Fill(dR_lep_leadb(),scale);
           leadbpt_2lep->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_2lep->Fill(pfmet(),scale);
           leppt_2lep->Fill(lep1_p4().pt(),scale);
           lepeta_2lep->Fill(lep1_p4().eta(),scale);
           lepphi_2lep->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_2lep->Fill(ak4_HT(),scale);
           Mlepb_2lep->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_2lep->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_2lep->Fill(ngoodjets(),scale);
           nbjets_2lep->Fill(ngoodbtags(),scale);
           METoverSqrtHT_2lep->Fill(getMHTSig(),scale);
           DPhiWLep_2lep->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
                //PZeta_TrkLep_2lep->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_2lep->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
    int leadb_idx=-999;
    int subleadb_idx=-999;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_2lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_2lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_2lep->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);
             if(ak4pfjets_passMEDbtag().at(iJet)) nb++;
             if(nb==1) leadb_idx = iJet;
             if(nb==2) subleadb_idx = iJet;
             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_2lep->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
if(nb>0){
 Mlepb_2lep->Fill((ak4pfjets_p4().at(leadb_idx)+lep1_p4()).M(),scale);
if(nb>1)  Mlepb2D_2lep->Fill((ak4pfjets_p4().at(leadb_idx)+lep1_p4()).M(),(ak4pfjets_p4().at(subleadb_idx)+lep1_p4()).M());
}
//           ak4_nef_2lep->Fill(ak4pfjets_p4().at(2).E(),scale);
  //         ak4_cef_2lep->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_2lep->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_2lep->Fill(n_isr,scale);

   const int pdg_b = 5;
   const int pdg_t = 6;
   const int pdg_stop1 = 1000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_W = 24;

           int genbfromt_idx=-9999;
           int genbfromstop_idx =-9999;
           int genlepfromtop_idx = -9999;
           int genleadb_idx = -999;
           int gensubleadb_idx = -999;
int genbs = 0;
          // _theak4NEFHistoMap[process]->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  _theak4CEFHistoMap[process]->Fill(ak4pfjets_p4().at(3).E(),scale);
           for(unsigned int igenb=0; igenb<genqs_p4().size();igenb++){
        //        cout<<"genb"<<igenb<<" status "<<genqs_status().at(igenb)<<" mother "<<genqs_motherid().at(igenb)<<endl;
               // if(abs(genqs_motherid().at(igenb)) ==pdg_stop1) cout<<"found genb ("<<igenb<<") from stop"<<endl;
                if(genqs_id().at(igenb)!=pdg_b) continue;
                if(genqs_status().at(igenb)!=23) continue;
                if(!genqs_isfromt().at(igenb)) continue;
                if(abs(genqs_motherid().at(igenb)) ==pdg_stop1) genbfromstop_idx = igenb;
                if(abs(genqs_motherid().at(igenb)) == pdg_t) genbfromt_idx = igenb;
                if(genbs==0) genleadb_idx=igenb;
// cout<<genleadb_idx<<"  "<<igenb<<endl;
                if(genqs_p4().at(genleadb_idx).pt() < genqs_p4().at(igenb).pt()) genleadb_idx=igenb;
                genbs++; 
                //if(abs(genqs_motherid().at(igenb)) == pdg_t)  cout<<"found genb ("<<igenb<<") from top"<<endl;
           }
        if(genleadb_idx!=-999){
           for(unsigned int ilep=0; ilep<genleps_p4().size();ilep++){
              if(ROOT::Math::VectorUtil::DeltaR(genleps_p4().at(ilep), lep1_p4()) > 0.4) continue; 
              if(genleps_isfromt().at(ilep)) genMlepb_2lep->Fill((genqs_p4().at(genleadb_idx)+genleps_p4().at(ilep)).M(),scale);
           }
        }
//cout<<"*************"<<endl;
           Wpt_2lep->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_ST(int process,float scale){
    int n_isr = 0;
if(gen_nfromtnus_() ==2) jetPt2D_2lep->Fill(ak4pfjets_p4().at(0).pt(),ak4pfjets_p4().at(1).pt());
           MT_ST->Fill(mt_met_lep(),scale);
           MT2W_ST->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_ST->Fill(AMT2,scale);
           Topnessmod_ST->Fill(topnessMod(),scale);
           Chi2_ST->Fill(hadronic_top_chi2(),scale);
           MinDPhi_ST->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_ST->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_ST->Fill(ak4_htratiom(),scale);
           //DRlepb_ST->Fill(dR_lep_leadb(),scale);
           leadbpt_ST->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_ST->Fill(pfmet(),scale);
           leppt_ST->Fill(lep1_p4().pt(),scale);
           lepeta_ST->Fill(lep1_p4().eta(),scale);
           lepphi_ST->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_ST->Fill(ak4_HT(),scale);
           Mlepb_ST->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_ST->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_ST->Fill(ngoodjets(),scale);
           nbjets_ST->Fill(ngoodbtags(),scale);
           METoverSqrtHT_ST->Fill(getMHTSig(),scale);
           DPhiWLep_ST->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
                //PZeta_TrkLep_ST->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_ST->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_ST->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_ST->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_ST->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_ST->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
         //  ak4_nef_ST->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_ST->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_ST->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_ST->Fill(n_isr,scale);
           Wpt_ST->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_WJets(int process,float scale){
//genHT_recoHT->Fill(genht(),ak4_HT());
    int n_isr = 0;
           MT_wjets->Fill(mt_met_lep(),scale);
           MT2W_wjets->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_wjets->Fill(AMT2,scale);
           Topnessmod_wjets->Fill(topnessMod(),scale);
           Chi2_wjets->Fill(hadronic_top_chi2(),scale);
           MinDPhi_wjets->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_wjets->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_wjets->Fill(ak4_htratiom(),scale);
           //DRlepb_wjets->Fill(dR_lep_leadb(),scale);
           leadbpt_wjets->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_wjets->Fill(pfmet(),scale);
           leppt_wjets->Fill(lep1_p4().pt(),scale);
           lepeta_wjets->Fill(lep1_p4().eta(),scale);
           lepphi_wjets->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_wjets->Fill(ak4_HT(),scale);
           Mlepb_wjets->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) M3b_wjets->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_wjets->Fill(ngoodjets(),scale);
           nbjets_wjets->Fill(ngoodbtags(),scale);
           METoverSqrtHT_wjets->Fill(getMHTSig(),scale);
           DPhiWLep_wjets->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
                //PZeta_TrkLep_wjets->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_wjets->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_wjets->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_wjets->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_wjets->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_wjets->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
          // ak4_nef_wjets->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  ak4_cef_wjets->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_wjets->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_wjets->Fill(n_isr,scale);
           genHT_wjets->Fill(genht(),scale);
           Wpt_wjets->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_Rare(int process,float scale){
    int n_isr = 0;
           MT_rare->Fill(mt_met_lep(),scale);
           MT2W_rare->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
           Topness_rare->Fill(AMT2,scale);
           Topnessmod_rare->Fill(topnessMod(),scale);
           Chi2_rare->Fill(hadronic_top_chi2(),scale);
           MinDPhi_rare->Fill(mindphi_met_j1_j2(),scale);
           //MinDPhi_rare->Fill(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) ),_theScalesMap[process]);
           HTratio_rare->Fill(ak4_htratiom(),scale);
           //DRlepb_rare->Fill(dR_lep_leadb(),scale);
           leadbpt_rare->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
           met_rare->Fill(pfmet(),scale);
           leppt_rare->Fill(lep1_p4().pt(),scale);
           lepeta_rare->Fill(lep1_p4().eta(),scale);
           lepphi_rare->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
           HT_rare->Fill(ak4_HT(),scale);
           Mlepb_rare->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
           if(ngoodjets()>1) M3b_rare->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
           njets_rare->Fill(ngoodjets(),scale);
           nbjets_rare->Fill(ngoodbtags(),scale);
           METoverSqrtHT_rare->Fill(getMHTSig(),scale);
           DPhiWLep_rare->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
            // for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
                //PZeta_TrkLep_rare->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // PZetaVis_TrkLep_rare->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
            // }
           n_isr = 0;
           for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) leadjetpt_rare->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             jetpt_rare->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             DPhiLepJet_rare->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);

             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                      n_isr++;
                      if(n_isr==1)  leadISRjet_pt200_nobtags_rare->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
        //   ak4_nef_rare->Fill(ak4pfjets_p4().at(2).E(),scale);
          // ak4_cef_rare->Fill(ak4pfjets_p4().at(3).E(),scale);
//           ak4_cef_rare->Fill((ak4pfjets_p4().at(2).E()+ak4pfjets_p4().at(3).E())/(ak4pfjets_p4().at(0).E()+ak4pfjets_p4().at(1).E()),_theScalesMap[process]);
           njets_pt200_nobtags_rare->Fill(n_isr,scale);
           Wpt_rare->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
}

void BasicHistos::FillSRHistos_Signal(int process,float scale){
    int n_isr = 0;
        _theWptHistoMap[process]->Fill(WpT(pfmet(), pfmet_phi(), lep1_p4()),scale);
_thejetPt2DHistoMap[process]->Fill(ak4pfjets_p4().at(0).pt(),ak4pfjets_p4().at(1).pt());
        _theMTHistoMap[process]->Fill(mt_met_lep(),scale);
        _theMT2WHistoMap[process]->Fill(MT2W(),scale);
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
        _theTopnessHistoMap[process]->Fill(AMT2,scale);
        _theTopnessmodHistoMap[process]->Fill(topnessMod(),scale);
        _theChi2HistoMap[process]->Fill(hadronic_top_chi2(),scale);
        _theMinDPhiHistoMap[process]->Fill(mindphi_met_j1_j2(),scale);
        _theHTratioHistoMap[process]->Fill(ak4_htratiom(),scale);
        //_theDRlepbHistoMap[process]->Fill(dR_lep_leadb(),scale);
        _theleadbptHistoMap[process]->Fill(ak4pfjets_leadMEDbjet_p4().pt(),scale);
        _themetHistoMap[process]->Fill(pfmet(),scale);
        _thelepptHistoMap[process]->Fill(lep1_p4().pt(),scale);
        _thelepetaHistoMap[process]->Fill(lep1_p4().eta(),scale);
        _thelepphiHistoMap[process]->Fill(cos(lep1_p4().phi()- pfmet_phi()),scale);
        _theHTHistoMap[process]->Fill(ak4_HT(),scale);
//        _theMlepbHistoMap[process]->Fill((ak4pfjets_leadMEDbjet_p4()+lep1_p4()).M(),scale);
if(ngoodjets()>1) _theM3bHistoMap[process]->Fill((ak4pfjets_p4().at(0).pt() - ak4pfjets_p4().at(1).pt() ) /(ak4pfjets_p4().at(0).pt()+ak4pfjets_p4().at(1).pt()),scale);
        _thenjetsHistoMap[process]->Fill(ngoodjets(),scale);
        _thenbjetsHistoMap[process]->Fill(ngoodbtags(),scale);
        _theMEToverSqrtHTHistoMap[process]->Fill(getMHTSig(),scale);
        _theDPhiWLepHistoMap[process]->Fill(DPhi_W_lep(pfmet(),pfmet_phi(),lep1_p4()),scale);
          //   for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {
               // _thePZeta_TrkLepHistoMap[process]->Fill(CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),ak4pfjets_p4().at(0)),scale);
               // _thePZetaVis_TrkLepHistoMap[process]->Fill(CDF_PZetaVis(lep1_p4(),ak4pfjets_p4().at(0)),scale);
                //cout<<CDF_PZeta(pfmet(),pfmet_phi(),lep1_p4(),isoTracks_p4().at(ipf))<<endl;
            // }
           n_isr = 0;
           int nb = 0;
    int leadb_idx;
    int subleadb_idx; 
          for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
             if( iJet==0) _theleadjetptHistoMap[process]->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             _thejetptHistoMap[process]->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             _theDPhiLepJetHistoMap[process]->Fill(lep1_p4().phi() - ak4pfjets_p4().at(iJet).phi(),scale);
             if(ak4pfjets_passMEDbtag().at(iJet)) nb++;
             if(nb==1) leadb_idx = iJet;
             if(nb==2) subleadb_idx = iJet;
             if( ngoodjets()>2 && ak4pfjets_p4().at(iJet).pt() > 200. && ak4pfjets_CSV().at(iJet) < 0.814 ){
                       n_isr++;
                       if(n_isr==1)  _theleadISRjet_pt200_nobtagsHistoMap[process]->Fill(ak4pfjets_p4().at(iJet).pt(),scale);
             }
           }
           _thenjets_pt200_nobtagsHistoMap[process]->Fill(n_isr,scale);
if(nb>0){
            _theMlepbHistoMap[process]->Fill((ak4pfjets_p4().at(leadb_idx)+lep1_p4()).M(),scale);
  if(nb>1)   _theMlepb2DHistoMap[process]->Fill((ak4pfjets_p4().at(leadb_idx)+lep1_p4()).M(),(ak4pfjets_p4().at(subleadb_idx)+lep1_p4()).M());
}
   const int pdg_b = 5;
   const int pdg_t = 6;
   const int pdg_stop1 = 1000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_W = 24;

           int genbfromt_idx=-9999;
           int genbfromstop_idx =-9999;
           int genlepfromtop_idx = -9999;
           int genleadb_idx = -999;
           int gensubleadb_idx = -999;
int genbs=0;
          // _theak4NEFHistoMap[process]->Fill(ak4pfjets_p4().at(2).E(),scale);
         //  _theak4CEFHistoMap[process]->Fill(ak4pfjets_p4().at(3).E(),scale);
           for(unsigned int igenb=0; igenb<genqs_p4().size();igenb++){
                //cout<<"genb"<<igenb<<" status "<<genqs_status().at(igenb)<<" mother "<<genqs_motherid().at(igenb)<<endl;
               // if(abs(genqs_motherid().at(igenb)) ==pdg_stop1) cout<<"found genb ("<<igenb<<") from stop"<<endl;
                if(genqs_id().at(igenb)!=pdg_b) continue;
                if(genqs_status().at(igenb)!=23) continue;
              //  if(!genqs_isfromt().at(igenb) || abs(genqs_motherid().at(igenb)) !=pdg_stop1) continue;
                if(abs(genqs_motherid().at(igenb)) ==pdg_stop1) genbfromstop_idx = igenb;
                if(abs(genqs_motherid().at(igenb)) == pdg_t) genbfromt_idx = igenb;
                if(genbs==0) genleadb_idx=igenb;
// cout<<genleadb_idx<<"  "<<igenb<<endl;
                if(genqs_p4().at(genleadb_idx).pt() < genqs_p4().at(igenb).pt()) genleadb_idx=igenb;
                genbs++;
                //if(abs(genqs_motherid().at(igenb)) == pdg_t)  cout<<"found genb ("<<igenb<<") from top"<<endl;
           } 
if(genleadb_idx>-1){
           for(unsigned int ilep=0; ilep<genleps_p4().size();ilep++){
               if(genleps_isfromt().at(ilep)) _thegenMlepbHistoMap[process]->Fill((genqs_p4().at(genleadb_idx)+genleps_p4().at(ilep)).M(),scale);
           }
}
 //               cout<<"******************************"<<endl;
   //             cout<<endl;

}

void BasicHistos::ClearHistVectors(){
  _myColors.clear();
  _myTitles.clear();
  _myColors2.clear();
  _myTitles2.clear();
  _myElTitles.clear();
  _mySignalTitles.clear(); 
  
    for(unsigned int pr = 0; pr < _mySignalVector.size(); pr++){
      if(_mySignalVector.size()<1) continue;
       _mySignalVector.at(pr)->Reset();
       _mySignalMT2WVector.at(pr)->Reset();
       _mySignalTopnessVector.at(pr)->Reset(); //_back(_theTopnessHistoMap[process]);
       _mySignalTopnessmodVector.at(pr)->Reset(); //_back(_theTopnessmodHistoMap[process]);
       _mySignalChi2Vector.at(pr)->Reset(); //_back(_theChi2HistoMap[process]);
       _mySignalMinDPhiVector.at(pr)->Reset(); //_back(_theMinDPhiHistoMap[process]);
       _mySignalHTratioVector.at(pr)->Reset(); //_back(_theHTratioHistoMap[process]);
       _mySignalDRlepbVector.at(pr)->Reset(); //_back(_theDRlepbHistoMap[process]);
       _mySignalleadbptVector.at(pr)->Reset(); //_back(_theleadbptHistoMap[process]);
       _mySignalmetVector.at(pr)->Reset(); //_back(_themetHistoMap[process]);
       _mySignallepptVector.at(pr)->Reset(); //_back(_thelepptHistoMap[process]);
       _mySignallepetaVector.at(pr)->Reset(); //_back(_thelepetaHistoMap[process]);
       _mySignallepphiVector.at(pr)->Reset(); //_back(_thelepphiHistoMap[process]);
       _mySignalHTVector.at(pr)->Reset(); //_back(_theHTHistoMap[process]);
       _mySignalnjetsVector.at(pr)->Reset(); //_back(_thenjetsHistoMap[process]);
       _mySignalnbjetsVector.at(pr)->Reset(); //_back(_thenbjetsHistoMap[process]);
       _mySignalnjets_pt200_nobtagsVector.at(pr)->Reset(); //_back(_thenjets_pt200_nobtagsHistoMap[process]);
       _mySignalleadISRjet_pt200_nobtagsVector.at(pr)->Reset(); //_back(_theleadISRjet_pt200_nobtagsHistoMap[process]);
       _mySignalMEToverSqrtHTVector.at(pr)->Reset(); //_back(_theMEToverSqrtHTHistoMap[process]);
       _mySignalMlepbVector.at(pr)->Reset(); //_back(_theMlepbHistoMap[process]);
       _mySignalgenMlepbVector.at(pr)->Reset(); //_back(_thegenMlepbHistoMap[process]);
       _mySignalM3bVector.at(pr)->Reset(); //_back(_theM3bHistoMap[process]);
       _mySignaljetptVector.at(pr)->Reset(); //_back(_thejetptHistoMap[process]);
       _mySignalDPhiLepJetVector.at(pr)->Reset(); //_back(_theDPhiLepJetHistoMap[process]);
       _mySignalleadjetptVector.at(pr)->Reset(); //_back(_theleadjetptHistoMap[process]);
       _mySignalDPhiWLep.at(pr)->Reset(); //_back(_theDPhiWLepHistoMap[process]);
       _mySignalPZeta_TrkLep.at(pr)->Reset(); //_back(_thePZeta_TrkLepHistoMap[process]);
       _mySignalPZetaVis_TrkLep.at(pr)->Reset(); //_back(_thePZetaVis_TrkLepHistoMap[process]);
       _mySignal_ak4NEFVector.at(pr)->Reset(); //_back(_theak4NEFHistoMap[process]);
       _mySignal_ak4CEFVector.at(pr)->Reset(); //_back(_theak4CEFHistoMap[process]);
       _mySignal_ak4EFVector.at(pr)->Reset(); //_back(_theak4EFHistoMap[process]);
       _mySignalWptVector.at(pr)->Reset();
   }

       _mySignalVector.clear();
       _mySignalMT2WVector.clear();
       _mySignalTopnessVector.clear(); //_back(_theTopnessHistoMap[process]);
       _mySignalTopnessmodVector.clear(); //_back(_theTopnessmodHistoMap[process]);
       _mySignalChi2Vector.clear(); //_back(_theChi2HistoMap[process]);
       _mySignalMinDPhiVector.clear(); //_back(_theMinDPhiHistoMap[process]);
       _mySignalHTratioVector.clear(); //_back(_theHTratioHistoMap[process]);
       _mySignalDRlepbVector.clear(); //_back(_theDRlepbHistoMap[process]);
       _mySignalleadbptVector.clear(); //_back(_theleadbptHistoMap[process]);
       _mySignalmetVector.clear(); //_back(_themetHistoMap[process]);
       _mySignallepptVector.clear(); //_back(_thelepptHistoMap[process]);
       _mySignallepetaVector.clear(); //_back(_thelepetaHistoMap[process]);
       _mySignallepphiVector.clear(); //_back(_thelepphiHistoMap[process]);
       _mySignalHTVector.clear(); //_back(_theHTHistoMap[process]);
       _mySignalnjetsVector.clear(); //_back(_thenjetsHistoMap[process]);
       _mySignalnbjetsVector.clear(); //_back(_thenbjetsHistoMap[process]);
       _mySignalnjets_pt200_nobtagsVector.clear(); //_back(_thenjets_pt200_nobtagsHistoMap[process]);
       _mySignalleadISRjet_pt200_nobtagsVector.clear(); //_back(_theleadISRjet_pt200_nobtagsHistoMap[process]);
       _mySignalMEToverSqrtHTVector.clear(); //_back(_theMEToverSqrtHTHistoMap[process]);
       _mySignalMlepbVector.clear(); //_back(_theMlepbHistoMap[process]);
       _mySignalgenMlepbVector.clear(); //_back(_thegenMlepbHistoMap[process]);
       _mySignalM3bVector.clear(); //_back(_theM3bHistoMap[process]);
       _mySignaljetptVector.clear(); //_back(_thejetptHistoMap[process]);
       _mySignalDPhiLepJetVector.clear(); //_back(_theDPhiLepJetHistoMap[process]);
       _mySignalleadjetptVector.clear(); //_back(_theleadjetptHistoMap[process]);
       _mySignalDPhiWLep.clear(); //_back(_theDPhiWLepHistoMap[process]);
       _mySignalPZeta_TrkLep.clear(); //_back(_thePZeta_TrkLepHistoMap[process]);
       _mySignalPZetaVis_TrkLep.clear(); //_back(_thePZetaVis_TrkLepHistoMap[process]);
       _mySignal_ak4NEFVector.clear(); //_back(_theak4NEFHistoMap[process]);
       _mySignal_ak4CEFVector.clear(); //_back(_theak4CEFHistoMap[process]);
       _mySignal_ak4EFVector.clear(); //_back(_theak4EFHistoMap[process]);
       _mySignalWptVector.clear();

   for(unsigned int pr = 0; pr < _myDataVector.size(); pr++){
       _myDataVector.at(pr)->Reset(); //(MT_data);
       _myDataMT2WVector.at(pr)->Reset(); //(MT2W_data);
       _myDataTopnessVector.at(pr)->Reset(); //(Topness_data);
       _myDataTopnessmodVector.at(pr)->Reset(); //(Topnessmod_data);
       _myDataChi2Vector.at(pr)->Reset(); //(Chi2_data);
       _myDataMinDPhiVector.at(pr)->Reset(); //(MinDPhi_data);
       _myDataHTratioVector.at(pr)->Reset(); //(HTratio_data);
       _myDataDRlepbVector.at(pr)->Reset(); //(DRlepb_data);
       _myDataleadbptVector.at(pr)->Reset(); //(leadbpt_data);
       _myDatametVector.at(pr)->Reset(); //(met_data);
       _myDatalepptVector.at(pr)->Reset(); //(leppt_data);
       _myDatalepetaVector.at(pr)->Reset(); //(lepeta_data);
       _myDatalepphiVector.at(pr)->Reset(); //(lepphi_data);
       _myDataHTVector.at(pr)->Reset(); //(HT_data);
       _myDatanjetsVector.at(pr)->Reset(); //(njets_data);
       _myDatanbjetsVector.at(pr)->Reset(); //(nbjets_data);
       _myDatanjets_pt200_nobtagsVector.at(pr)->Reset(); //(njets_pt200_nobtags_data);
       _myDataleadISRjet_pt200_nobtagsVector.at(pr)->Reset(); //(leadISRjet_pt200_nobtags_data);
       _myDataMEToverSqrtHTVector.at(pr)->Reset(); //(METoverSqrtHT_data);
       _myDataMlepbVector.at(pr)->Reset(); //(Mlepb_data);
       _myDatagenMlepbVector.at(pr)->Reset(); //(genMlepb_data);
       _myDataM3bVector.at(pr)->Reset(); //(M3b_data);
       _myDatajetptVector.at(pr)->Reset(); //(jetpt_data);

       _myDataDPhiLepJetVector.at(pr)->Reset(); //(DPhiLepJet_data);
       _myDataleadjetptVector.at(pr)->Reset(); //(leadjetpt_data);
       _myDataDPhiWLep.at(pr)->Reset(); //(DPhiWLep_data);
       _myDataPZeta_TrkLep.at(pr)->Reset(); //(PZeta_TrkLep_data);
       _myDataPZetaVis_TrkLep.at(pr)->Reset(); //(PZetaVis_TrkLep_data);
       _myDataak4NEFVector.at(pr)->Reset(); //(ak4_nef_data);
       _myDataak4CEFVector.at(pr)->Reset(); //(ak4_cef_data);
       _myDataak4EFVector.at(pr)->Reset(); //(ak4_EF_data);
       _myDataWptVector.at(pr)->Reset();

        _myDatadetainVector.clear();
        _myDatadphiinVector.clear();
        _myDatasigmaietaietaVector.clear();
        _myDatahovereVector.clear();
        _myDatadzVector.clear();
        _myDatad0Vector.clear();
        _myDataempVector.clear();
        _myDataminirelisoVector.clear();
        _myDatamissinghitsVector.clear();
        _myDataconversionsvetoVector.clear();
    }

       _myDataVector.clear(); //(MT_data);
       _myDataMT2WVector.clear(); //(MT2W_data);
       _myDataTopnessVector.clear(); //(Topness_data);
       _myDataTopnessmodVector.clear(); //(Topnessmod_data);
       _myDataChi2Vector.clear(); //(Chi2_data);
       _myDataMinDPhiVector.clear(); //(MinDPhi_data);
       _myDataHTratioVector.clear(); //(HTratio_data);
       _myDataDRlepbVector.clear(); //(DRlepb_data);
       _myDataleadbptVector.clear(); //(leadbpt_data);
       _myDatametVector.clear(); //(met_data);
       _myDatalepptVector.clear(); //(leppt_data);
       _myDatalepetaVector.clear(); //(lepeta_data);
       _myDatalepphiVector.clear(); //(lepphi_data);
       _myDataHTVector.clear(); //(HT_data);
       _myDatanjetsVector.clear(); //(njets_data);
       _myDatanbjetsVector.clear(); //(nbjets_data);
       _myDatanjets_pt200_nobtagsVector.clear(); //(njets_pt200_nobtags_data);
       _myDataleadISRjet_pt200_nobtagsVector.clear(); //(leadISRjet_pt200_nobtags_data);
       _myDataMEToverSqrtHTVector.clear(); //(METoverSqrtHT_data);
       _myDataMlepbVector.clear(); //(Mlepb_data);
       _myDatagenMlepbVector.clear(); //(genMlepb_data);
       _myDataM3bVector.clear(); //(M3b_data);
       _myDatajetptVector.clear(); //(jetpt_data);

       _myDataDPhiLepJetVector.clear(); //(DPhiLepJet_data);
       _myDataleadjetptVector.clear(); //(leadjetpt_data);
       _myDataDPhiWLep.clear(); //(DPhiWLep_data);
       _myDataPZeta_TrkLep.clear(); //(PZeta_TrkLep_data);
       _myDataPZetaVis_TrkLep.clear(); //(PZetaVis_TrkLep_data);
       _myDataak4NEFVector.clear(); //(ak4_nef_data);
       _myDataak4CEFVector.clear(); //(ak4_cef_data);
       _myDataak4EFVector.clear(); //(ak4_EF_data);
       _myDataWptVector.clear();
    for(unsigned int pr = 0; pr < _myVector.size(); pr++){
       _myVector.at(pr)->Reset(); //(MT_wjets);
       _myMT2WVector.at(pr)->Reset(); //(MT2W_wjets);
       _myTopnessVector.at(pr)->Reset(); //(Topness_wjets);
       _myTopnessmodVector.at(pr)->Reset(); //(Topnessmod_wjets);
       _myChi2Vector.at(pr)->Reset(); //(Chi2_wjets);
       _myMinDPhiVector.at(pr)->Reset(); //(MinDPhi_wjets);
       _myHTratioVector.at(pr)->Reset(); //(HTratio_wjets);
       _myDRlepbVector.at(pr)->Reset(); //(DRlepb_wjets);
       _myleadbptVector.at(pr)->Reset(); //(leadbpt_wjets);
       _mymetVector.at(pr)->Reset(); //(met_wjets);
       _mylepptVector.at(pr)->Reset(); //(leppt_wjets);
       _mylepetaVector.at(pr)->Reset(); //(lepeta_wjets);
       _mylepphiVector.at(pr)->Reset(); //(lepphi_wjets);
       _myHTVector.at(pr)->Reset(); //(HT_wjets);
       _mynjetsVector.at(pr)->Reset(); //(njets_wjets);
       _mynbjetsVector.at(pr)->Reset(); //(nbjets_wjets);
       _mynjets_pt200_nobtagsVector.at(pr)->Reset(); //(njets_pt200_nobtags_wjets);
       _myleadISRjet_pt200_nobtagsVector.at(pr)->Reset(); //(leadISRjet_pt200_nobtags_wjets);
       _myMEToverSqrtHTVector.at(pr)->Reset(); //(METoverSqrtHT_wjets);
       _myMlepbVector.at(pr)->Reset(); //(Mlepb_wjets);
       _mygenMlepbVector.at(pr)->Reset(); //(genMlepb_wjets);
       _myM3bVector.at(pr)->Reset(); //(M3b_wjets);
       _myjetptVector.at(pr)->Reset(); //(jetpt_wjets);
       _myDPhiLepJetVector.at(pr)->Reset(); //(DPhiLepJet_wjets);
       _myleadjetptVector.at(pr)->Reset(); //(leadjetpt_wjets);
       _myDPhiWLep.at(pr)->Reset(); //(DPhiWLep_wjets);
       _myPZeta_TrkLep.at(pr)->Reset(); //(PZeta_TrkLep_wjets);
       _myPZetaVis_TrkLep.at(pr)->Reset(); //(PZetaVis_TrkLep_wjets);
       _myak4NEFVector.at(pr)->Reset(); //(ak4_nef_wjets);
       _myak4CEFVector.at(pr)->Reset(); //(ak4_cef_wjets);
       _myak4EFVector.at(pr)->Reset(); //(ak4_EF_wjets);
       _myWptVector.at(pr)->Reset();
    }
        _myWptVector.clear();
       _myVector.clear(); //(MT_wjets);
       _myMT2WVector.clear(); //(MT2W_wjets);
       _myTopnessVector.clear(); //(Topness_wjets);
       _myTopnessmodVector.clear(); //(Topnessmod_wjets);
       _myChi2Vector.clear(); //(Chi2_wjets);
       _myMinDPhiVector.clear(); //(MinDPhi_wjets);
       _myHTratioVector.clear(); //(HTratio_wjets);
       _myDRlepbVector.clear(); //(DRlepb_wjets);
       _myleadbptVector.clear(); //(leadbpt_wjets);
       _mymetVector.clear(); //(met_wjets);
       _mylepptVector.clear(); //(leppt_wjets);
       _mylepetaVector.clear(); //(lepeta_wjets);
       _mylepphiVector.clear(); //(lepphi_wjets);
       _myHTVector.clear(); //(HT_wjets);
       _mynjetsVector.clear(); //(njets_wjets);
       _mynbjetsVector.clear(); //(nbjets_wjets);
       _mynjets_pt200_nobtagsVector.clear(); //(njets_pt200_nobtags_wjets);
       _myleadISRjet_pt200_nobtagsVector.clear(); //(leadISRjet_pt200_nobtags_wjets);
       _myMEToverSqrtHTVector.clear(); //(METoverSqrtHT_wjets);
       _myMlepbVector.clear(); //(Mlepb_wjets);
       _mygenMlepbVector.clear(); //(genMlepb_wjets);
       _myM3bVector.clear(); //(M3b_wjets);
       _myjetptVector.clear(); //(jetpt_wjets);
       _myDPhiLepJetVector.clear(); //(DPhiLepJet_wjets);
       _myleadjetptVector.clear(); //(leadjetpt_wjets);
       _myDPhiWLep.clear(); //(DPhiWLep_wjets);
       _myPZeta_TrkLep.clear(); //(PZeta_TrkLep_wjets);
       _myPZetaVis_TrkLep.clear(); //(PZetaVis_TrkLep_wjets);
       _myak4NEFVector.clear(); //(ak4_nef_wjets);
       _myak4CEFVector.clear(); //(ak4_cef_wjets);
       _myak4EFVector.clear(); //(ak4_EF_wjets);
     //   _myDataWptVector.clear();

    for(unsigned int pr = 0; pr < _myVector2.size(); pr++){
       _myVector2.at(pr)->Reset();
       _myMT2WVector2.at(pr)->Reset();
       _myTopnessVector2.at(pr)->Reset(); //(Topness_Znunu);
       _myTopnessmodVector2.at(pr)->Reset(); //(Topnessmod_Znunu);
       _myChi2Vector2.at(pr)->Reset(); //(Chi2_Znunu);
       _myMinDPhiVector2.at(pr)->Reset(); //(MinDPhi_Znunu);
       _myHTratioVector2.at(pr)->Reset(); //(HTratio_Znunu);
       _myDRlepbVector2.at(pr)->Reset(); //(DRlepb_Znunu);
       _myleadbptVector2.at(pr)->Reset(); //(leadbpt_Znunu);
       _mymetVector2.at(pr)->Reset(); //(met_Znunu);
       _mylepptVector2.at(pr)->Reset(); //(leppt_Znunu);
       _mylepetaVector2.at(pr)->Reset(); //(lepeta_Znunu);
       _mylepphiVector2.at(pr)->Reset(); //(lepphi_Znunu);
       _myHTVector2.at(pr)->Reset(); //(HT_Znunu);
       _mynjetsVector2.at(pr)->Reset(); //(njets_Znunu);
       _mynbjetsVector2.at(pr)->Reset(); //(nbjets_Znunu);
       _mynjets_pt200_nobtagsVector2.at(pr)->Reset(); //(njets_pt200_nobtags_Znunu);
       _myleadISRjet_pt200_nobtagsVector2.at(pr)->Reset(); //(leadISRjet_pt200_nobtags_Znunu);
       _myMEToverSqrtHTVector2.at(pr)->Reset(); //(METoverSqrtHT_Znunu);
       _myMlepbVector2.at(pr)->Reset(); //(Mlepb_Znunu);
       _mygenMlepbVector2.at(pr)->Reset(); //(genMlepb_Znunu);
       _myM3bVector2.at(pr)->Reset(); //(M3b_Znunu);
       _myjetptVector2.at(pr)->Reset(); //(jetpt_Znunu);
       _myWptVector2.at(pr)->Reset(); 
   }
       _myWptVector2.clear();
       _myVector2.clear();//MT_Znunu);
       _myMT2WVector2.clear();//MT2W_Znunu);
       _myTopnessVector2.clear(); //(Topness_Znunu);
       _myTopnessmodVector2.clear(); //(Topnessmod_Znunu);
       _myChi2Vector2.clear(); //(Chi2_Znunu);
       _myMinDPhiVector2.clear(); //(MinDPhi_Znunu);
       _myHTratioVector2.clear(); //(HTratio_Znunu);
       _myDRlepbVector2.clear(); //(DRlepb_Znunu);
       _myleadbptVector2.clear(); //(leadbpt_Znunu);
       _mymetVector2.clear(); //(met_Znunu);
       _mylepptVector2.clear(); //(leppt_Znunu);
       _mylepetaVector2.clear(); //(lepeta_Znunu);
       _mylepphiVector2.clear(); //(lepphi_Znunu);
       _myHTVector2.clear(); //(HT_Znunu);
       _mynjetsVector2.clear(); //(njets_Znunu);
       _mynbjetsVector2.clear(); //(nbjets_Znunu);
       _mynjets_pt200_nobtagsVector2.clear(); //(njets_pt200_nobtags_Znunu);
       _myleadISRjet_pt200_nobtagsVector2.clear(); //(leadISRjet_pt200_nobtags_Znunu);
       _myMEToverSqrtHTVector2.clear(); //(METoverSqrtHT_Znunu);
       _myMlepbVector2.clear(); //(Mlepb_Znunu);
       _mygenMlepbVector2.clear(); //(genMlepb_Znunu);
       _myM3bVector2.clear(); //(M3b_Znunu);
       _myjetptVector2.clear(); //(jetpt_Znunu);

   /* for(unsigned int pr = 0; pr < _mydetainVector.size(); pr++){
        _mydetainVector.at(pr)->Reset();
        _mydphiinVector.at(pr)->Reset();
        _mysigmaietaietaVector.at(pr)->Reset();
        _myhovereVector.at(pr)->Reset();
        _mydzVector.at(pr)->Reset();
        _myd0Vector.at(pr)->Reset();
        _myempVector.at(pr)->Reset();
        _myminirelisoVector.at(pr)->Reset();
        _mymissinghitsVector.at(pr)->Reset();
        _myconversionsvetoVector.at(pr)->Reset();
    }*/
        _mydetainVector.clear();
        _mydphiinVector.clear();
        _mysigmaietaietaVector.clear();
        _myhovereVector.clear();
        _mydzVector.clear();
        _myd0Vector.clear();
        _myempVector.clear();
        _myminirelisoVector.clear();
        _mymissinghitsVector.clear();
        _myconversionsvetoVector.clear();
        _myDatadetainVector.clear();
        _myDatadphiinVector.clear();
        _myDatasigmaietaietaVector.clear();
        _myDatahovereVector.clear();
        _myDatadzVector.clear();
        _myDatad0Vector.clear();
        _myDataempVector.clear();
        _myDataminirelisoVector.clear();
        _myDatamissinghitsVector.clear();
        _myDataconversionsvetoVector.clear();
}


void BasicHistos::BookElectronHistos(int vIt, string process){
        char* thedetainHistoName = Form("detain_%s",process.c_str());
        _thedetainHistoMap[vIt] = new TH1F(thedetainHistoName,thedetainHistoName,20,0,0.01);
        char* thedphiinHistoName = Form("dphiin_%s",process.c_str());
        _thedphiinHistoMap[vIt] = new TH1F(thedphiinHistoName,thedphiinHistoName,20,0,0.1);
        char* thesigmaietaietaHistoName = Form("sigmaietaieta_%s",process.c_str());
        _thesigmaietaietaHistoMap[vIt] = new TH1F(thesigmaietaietaHistoName,thesigmaietaietaHistoName,20,0,0.01);
        char* thehovereHistoName = Form("hovere_%s",process.c_str());
        _thehovereHistoMap[vIt] = new TH1F(thehovereHistoName,thehovereHistoName,20,0,0.1);
        char* thedzHistoName = Form("dz_%s",process.c_str());
        _thedzHistoMap[vIt] = new TH1F(thedzHistoName,thedzHistoName,20,0,0.05);
        char* thed0HistoName = Form("d0_%s",process.c_str());
        _thed0HistoMap[vIt] = new TH1F(thed0HistoName,thed0HistoName,20,0,0.05);
        char* theempHistoName = Form("emp_%s",process.c_str());
        _theempHistoMap[vIt] = new TH1F(theempHistoName,theempHistoName,20,0,0.1);
        char* theminirelisoHistoName = Form("minireliso_%s",process.c_str());
        _theminirelisoHistoMap[vIt] = new TH1F(theminirelisoHistoName,theminirelisoHistoName,10,0,0.2);

        char* themissinghitsHistoName = Form("missinghits_%s",process.c_str());
        _themissinghitsHistoMap[vIt] = new TH1F(themissinghitsHistoName,themissinghitsHistoName,5,0,5);
        char* theconversionsvetoHistoName = Form("conversionsveto_%s",process.c_str());
        _theconversionsvetoHistoMap[vIt] = new TH1F(theconversionsvetoHistoName,theconversionsvetoHistoName,3,0,2);
}

void BasicHistos::FillElectronHistoMaps(int process,float scale){

 /* if(lep1_is_lepid_medium_noiso()){
     _theminirelisoHistoMap[process]->Fill(lep1_MiniIso(),scale);
  }


  if(lep1_MiniIso()<0.1){
    if (fabs(lep1_etaSC()) <= 1.479  && (lep1_expectedMissingInnerHits()<=1)  && !(lep1_conversionVeto())){

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) && (fabs(lep1_dz()) < 0.042020)  )  _thedetainHistoMap[process]->Fill(fabs(lep1_dEtaIn()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_d0()) < 0.012235) && (fabs(lep1_dz()) < 0.042020)  )  _thedphiinHistoMap[process]->Fill(fabs(lep1_dPhiIn()),scale);

      if((lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) && (fabs(lep1_dz()) < 0.042020)  )  _thesigmaietaietaHistoMap[process]->Fill(lep1_sigmaIEtaEta_fill5x5(),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) && (fabs(lep1_dz()) < 0.042020)  )  _thehovereHistoMap[process]->Fill(lep1_hOverE(),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) )  _thedzHistoMap[process]->Fill(fabs(lep1_dz()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) &&(fabs(lep1_dz()) < 0.042020)  ) _thed0HistoMap[process]->Fill(fabs(lep1_d0()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) &&(fabs(lep1_dz()) < 0.042020)  )  _theempHistoMap[process]->Fill(lep1_ooEmooP(),scale);

    } else if((fabs(lep1_etaSC()) > 1.479) && (fabs(lep1_etaSC()) < 2.5)  && (lep1_expectedMissingInnerHits()<=1)  && !(lep1_conversionVeto())){

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683) && (lep1_hOverE() < 0.086782) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) && (fabs(lep1_dz()) < 0.138142)  )  _thedetainHistoMap[process]->Fill(fabs(lep1_dEtaIn()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683)  && (lep1_hOverE() < 0.086782) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_d0()) < 0.036719) &&  (fabs(lep1_dz()) < 0.138142) ) _thedphiinHistoMap[process]->Fill(fabs(lep1_dPhiIn()),scale);

      if( (lep1_ooEmooP() < 0.100683)  && (lep1_hOverE() < 0.086782) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) && (fabs(lep1_dz()) < 0.138142)  ) _thesigmaietaietaHistoMap[process]->Fill(lep1_sigmaIEtaEta_fill5x5(),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) && (fabs(lep1_dz()) < 0.138142)  )  _thehovereHistoMap[process]->Fill(lep1_hOverE(),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) )  _thedzHistoMap[process]->Fill(fabs(lep1_dz()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) &&  (fabs(lep1_dz()) < 0.138142)  ) _thed0HistoMap[process]->Fill(fabs(lep1_d0()),scale);

      if((lep1_sigmaIEtaEta_fill5x5() < 0.030135) &&  (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) &&  (fabs(lep1_dz()) < 0.138142)  ) _theempHistoMap[process]->Fill(lep1_ooEmooP(),scale);
    }
  }

  if(lep1_MiniIso()<0.1){
    if (fabs(lep1_etaSC()) <= 1.479 && (lep1_sigmaIEtaEta_fill5x5() < 0.009996) && (lep1_ooEmooP() < 0.091942) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.008925) && (fabs(lep1_dPhiIn()) < 0.035973) && (fabs(lep1_d0()) < 0.012235) &&(fabs(lep1_dz()) < 0.042020) ){
       if(!(lep1_conversionVeto())) _themissinghitsHistoMap[process]->Fill(lep1_expectedMissingInnerHits(),scale);
       if(lep1_expectedMissingInnerHits()<=1) _theconversionsvetoHistoMap[process]->Fill(lep1_conversionVeto(), scale);
    }else if((fabs(lep1_etaSC()) > 1.479) && (fabs(lep1_etaSC()) < 2.5) && (lep1_sigmaIEtaEta_fill5x5() < 0.030135) && (lep1_ooEmooP() < 0.100683) && (lep1_hOverE() < 0.050537) && (fabs(lep1_dEtaIn()) < 0.007429) && (fabs(lep1_dPhiIn()) < 0.067879) && (fabs(lep1_d0()) < 0.036719) &&  (fabs(lep1_dz()) < 0.138142) ){
                 if(!(lep1_conversionVeto())) _themissinghitsHistoMap[process]->Fill(lep1_expectedMissingInnerHits(),scale);
       if(lep1_expectedMissingInnerHits()<=1) _theconversionsvetoHistoMap[process]->Fill(lep1_conversionVeto(), scale);
     }
   }
*/
}

void BasicHistos::MakeElectronHistoVectors(int process, string name,float signalscale){
    std::string filestr (name);
    if(filestr.find("T2tt") == string::npos && filestr.find("data") == string::npos){
        _mydetainVector.push_back(_thedetainHistoMap[process]);
        _mydphiinVector.push_back(_thedphiinHistoMap[process]);
        _mysigmaietaietaVector.push_back(_thesigmaietaietaHistoMap[process]);
        _myhovereVector.push_back(_thehovereHistoMap[process]);
        _mydzVector.push_back(_thedzHistoMap[process]);
        _myd0Vector.push_back(_thed0HistoMap[process]);
        _myempVector.push_back(_theempHistoMap[process]);
        _myminirelisoVector.push_back(_theminirelisoHistoMap[process]);
        _mymissinghitsVector.push_back(_themissinghitsHistoMap[process]);
        _myconversionsvetoVector.push_back(_theconversionsvetoHistoMap[process]);
    }else if(filestr.find("data") != string::npos){
        _myDatadetainVector.push_back(_thedetainHistoMap[process]);
        _myDatadphiinVector.push_back(_thedphiinHistoMap[process]);
        _myDatasigmaietaietaVector.push_back(_thesigmaietaietaHistoMap[process]);
        _myDatahovereVector.push_back(_thehovereHistoMap[process]);
        _myDatadzVector.push_back(_thedzHistoMap[process]);
        _myDatad0Vector.push_back(_thed0HistoMap[process]);
        _myDataempVector.push_back(_theempHistoMap[process]);
        _myDataminirelisoVector.push_back(_theminirelisoHistoMap[process]);
        _myDatamissinghitsVector.push_back(_themissinghitsHistoMap[process]);
        _myDataconversionsvetoVector.push_back(_theconversionsvetoHistoMap[process]);
    }
}

void BasicHistos::MakeElectronPlots(float Lumi, string label){
  TH1F* null = new TH1F("","",1,0,1);
  std::vector < TH1F* > nullb;
  nullb.push_back(null);
  std::vector < char* > nullname;
  nullname.push_back("");
std::string labelstr (label);
_myElTitles.push_back("WJets");
_myElTitles.push_back("TTBar");
_myElTitles.push_back("Rare");

if (labelstr.find("barrel") !=string::npos){
  dataMCplotMaker(_myDatadetainVector.at(0), _mydetainVector, _myElTitles, "", "", Form("--vLine 0.008925  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#eta_{in} --png --outputName electronIDNminus1_detainlogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadphiinVector.at(0), _mydphiinVector, _myElTitles, "", "", Form("--vLine 0.035973  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#phi_{in} --png --outputName electronIDNminus1_dphiinlogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatasigmaietaietaVector.at(0), _mysigmaietaietaVector, _myElTitles, "", "", Form("--hline 0.009996  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #sigma_{i#eta i#eta} --png --outputName electronIDNminus1_sigmaietaietalogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatahovereVector.at(0), _myhovereVector, _myElTitles, "", "", Form("--vLine 0.050537  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{H}{e} --png --outputName electronIDNminus1_hoverelogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadzVector.at(0), _mydzVector, _myElTitles, "", "", Form("--vLine 0.012235 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel dz --png --outputName electronIDNminus1_dzlogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatad0Vector.at(0), _myd0Vector, _myElTitles, "", "", Form("--vLine 0.042020  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel d0 --png --outputName electronIDNminus1_d0logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataempVector.at(0), _myempVector, _myElTitles, "", "", Form("--vLine 0.091942  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{E_{m}}{P} --png --outputName electronIDNminus1_emplogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minirelisologplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatamissinghitsVector.at(0), _mymissinghitsVector, _myElTitles, "", "", Form("--vLine 1 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel misshing hits  --png --outputName electronIsoNminus1_missinghits_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataconversionsvetoVector.at(0), _myconversionsvetoVector, _myElTitles, "", "", Form("--energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel conversions veto  --png --outputName electronIsoNminus1_conversions_logplot_%s",Lumi,label.c_str()));

 dataMCplotMaker(_myDatadetainVector.at(0), _mydetainVector, _myElTitles, "", "", Form("--vLine 0.008925  --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#eta_{in} --png --outputName electronIDNminus1_detainplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadphiinVector.at(0), _mydphiinVector, _myElTitles, "", "", Form("--vLine 0.035973  --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#phi_{in} --png --outputName electronIDNminus1_dphiinplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatasigmaietaietaVector.at(0), _mysigmaietaietaVector, _myElTitles, "", "", Form("--hline 0.009996  --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #sigma_{i#eta i#eta} --png --outputName electronIDNminus1_sigmaietaietaplot_%s",Lumi,label.c_str()));
dataMCplotMaker(_myDatahovereVector.at(0), _myhovereVector, _myElTitles, "", "", Form("--vLine 0.050537  --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{H}{e} --png --outputName electronIDNminus1_hoverelogplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadzVector.at(0), _mydzVector, _myElTitles, "", "", Form("--vLine 0.012235 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel dz --png --outputName electronIDNminus1_dzplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatad0Vector.at(0), _myd0Vector, _myElTitles, "", "", Form("--vLine 0.042020  --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel d0 --png --outputName electronIDNminus1_d0plot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataempVector.at(0), _myempVector, _myElTitles, "", "", Form("--vLine 0.091942  --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{E_{m}}{P} --png --outputName electronIDNminus1_empplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minirelisoplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatamissinghitsVector.at(0), _mymissinghitsVector, _myElTitles, "", "", Form("--vLine 1 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel misshing hits  --png --outputName electronIsoNminus1_missinghits_plot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataconversionsvetoVector.at(0), _myconversionsvetoVector, _myElTitles, "", "", Form(" --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel conversions veto  --png --outputName electronIsoNminus1_conversions_plot_%s",Lumi,label.c_str()));

  }else if(labelstr.find("endcap") !=string::npos){
  dataMCplotMaker(_myDatadetainVector.at(0), _mydetainVector, _myElTitles, "", "", Form("--vLine 0.007429 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#eta_{in} --png --outputName electronIDNminus1_detain_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadphiinVector.at(0), _mydphiinVector, _myElTitles, "", "", Form("--vLine 0.067879 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#phi_{in} --png --outputName electronIDNminus1_dphiin_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatasigmaietaietaVector.at(0), _mysigmaietaietaVector, _myElTitles, "", "", Form("--vLine 0.030135 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #sigma_{i#eta i#eta} --png --outputName electronIDNminus1_sigmaietaieta_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatahovereVector.at(0), _myhovereVector, _myElTitles, "", "", Form("--vLine 0.050537 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{H}{e} --png --outputName electronIDNminus1_hovere_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadzVector.at(0), _mydzVector, _myElTitles, "", "", Form("--vLine 0.138142 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel dz --png --outputName electronIDNminus1_dz_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatad0Vector.at(0), _myd0Vector, _myElTitles, "", "", Form("--vLine 0.036719 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel d0 --png --outputName electronIDNminus1_d0_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataempVector.at(0), _myempVector, _myElTitles, "", "", Form("--vLine 0.100683 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{E_{m}}{P} --png --outputName electronIDNminus1_emp_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minireliso_logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatamissinghitsVector.at(0), _mymissinghitsVector, _myElTitles, "", "", Form("--vLine 1 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel misshing hits  --png --outputName electronIsoNminus1_missinghits__logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataconversionsvetoVector.at(0), _myconversionsvetoVector, _myElTitles, "", "", Form("--energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel conversions veto  --png --outputName conversions__logplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadetainVector.at(0), _mydetainVector, _myElTitles, "", "", Form("--vLine 0.007429 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#eta_{in} --png --outputName electronIDNminus1_detainplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadphiinVector.at(0), _mydphiinVector, _myElTitles, "", "", Form("--vLine 0.067879 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #Delta#phi_{in} --png --outputName electronIDNminus1_dphiinplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatasigmaietaietaVector.at(0), _mysigmaietaietaVector, _myElTitles, "", "", Form("--vLine 0.030135 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel #sigma_{i#eta i#eta} --png --outputName electronIDNminus1_sigmaietaietaplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatahovereVector.at(0), _myhovereVector, _myElTitles, "", "", Form("--vLine 0.050537 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{H}{e} --png --outputName electronIDNminus1_hovereplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatadzVector.at(0), _mydzVector, _myElTitles, "", "", Form("--vLine 0.138142 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel dz --png --outputName electronIDNminus1_dzplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatad0Vector.at(0), _myd0Vector, _myElTitles, "", "", Form("--vLine 0.036719 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel d0 --png --outputName electronIDNminus1_d0plot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataempVector.at(0), _myempVector, _myElTitles, "", "", Form("--vLine 0.100683 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel \frac{E_{m}}{P} --png --outputName electronIDNminus1_empplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minirelisoplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDatamissinghitsVector.at(0), _mymissinghitsVector, _myElTitles, "", "", Form("--vLine 1 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel misshing hits  --png --outputName electronIsoNminus1_missinghits_plot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataconversionsvetoVector.at(0), _myconversionsvetoVector, _myElTitles, "", "", Form("--isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel conversions veto  --png --outputName conversions_plot_%s",Lumi,label.c_str()));
  }else{
   dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --isLinear --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minirelisoplot_%s",Lumi,label.c_str()));
  dataMCplotMaker(_myDataminirelisoVector.at(0), _myminirelisoVector, _myElTitles, "", "", Form("--vLine 0.1 --energy 13 --preserveSignalOrder --lumi %2.0f pb --xAxisLabel mini rel. iso.  --png --outputName electronIsoNminus1_minireliso_logplot_%s",Lumi,label.c_str()));
  }
}
