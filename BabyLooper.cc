#include "BabyLooper.h"
// C++
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TCut.h"
#include "dataMCplotMaker.h"
#include "TVector3.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TH2.h"
#include "TH2D.h"

#include "stoputils.h"
#include "BasicHistos.h"

#include "Tools/btagsf/BTagCalibrationStandalone.h"
#include "BTagSFUtil_tprime.h"
#include "stop_variables/chi2.cc"

// StopCMS3
#include "StopCMS3.h"
#include "dorky.h"

using namespace std;
using namespace stoptas;
using namespace duplicate_removal;

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2)
  {
        return v1.second.pt() > v2.second.pt();
  }
};

int BabyLooper::Looper(){
    GetTheFiles();
  // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

////////////////////////////////
  TFile f1(_theOutputFile,"recreate");
  myfile.open (Form("%s_pt%2.0f_MET%2.0f_IncJets.txt",_thePlotStringName,_theLep1PtCut,_theminMETCut));
  bool applyBtagSFs=false;

  int ntables=3;
  for(int i =0; i<ntables;i++){
    CTable dummy;
    dummy.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    dummy.setPrecision(2);
    dummy.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");
    _table.push_back(dummy);
    _table2.push_back(dummy);
/*
    _table.at(i).setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    _table.at(i).setPrecision(3);
    _table.at(i).setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    _table2.at(i).setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    _table2.at(i).setPrecision(3);
    _table2.at(i).setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");
*/
  }
    BasicHistos h1s;
    BasicHistos h0bCR;
    BasicHistos h2lCR;

    table.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table.setPrecision(3);
    table.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    table2.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table2.setPrecision(3);
    table2.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    table3.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table3.setPrecision(3);
    table3.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    table4.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table4.setPrecision(3);
    table4.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    table5.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table5.setPrecision(3);
    table5.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

    table6.setTitle(Form("Events @ %1.2f  fb^{-1}",_theLumi));
    table6.setPrecision(3);
    table6.setTable() ("250 $<$ MET $<$ 350","350 $<$ MET $<$ 450", "MET $>$ 400", "MET $>$ 350");

vector<CNumBase<float> > TFbtags;
vector<CNumBase<float> > TFmets;
vector<CNumBase<float> > Estimates;

vector<CNumBase<float> > TF_dilep;
vector<CNumBase<float> > TFmets_dilep;
vector<CNumBase<float> > Estimates_dilep;


    //loop over baby files
    //opt loop open
    h1s.BookSRHistos_bg();
    h1s.BookVariable();
    h0bCR.BookSRHistos_bg();
    h0bCR.BookVariable();
    h2lCR.BookSRHistos_bg();
    h2lCR.BookVariable();
    count_wjets = 0;
    count_st = 0;
    count_ttbar_1lep = 0;
    count_ttbar_2lep = 0;
    count_ttbar = 0;
    count_rare = 0;
    count_data = 0;
    bool electronplot = false;
    int vIt_fun = 0;
    for(unsigned int vIt = 0; vIt < _theRootFiles.size(); vIt++){
        std::string filestr (_theNameMap[vIt]);
        if(filestr.find("SMS") != string::npos) h1s.BookSRHistos_signal(vIt, filestr);
        if(filestr.find("SMS") != string::npos) h0bCR.BookSRHistos_signal(vIt, filestr);
        if(filestr.find("SMS") != string::npos) h2lCR.BookSRHistos_signal(vIt, filestr);
        else if(filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos) count_wjets++;
        else if(filestr.find("WJetsToLNu_") != string::npos || filestr.find("WJetsToLNu_Inc") != string::npos) count_wjets++;
        else if(filestr.find("ST") != string::npos) count_st++;
        else if(filestr.find("ttbar_1lep") != string::npos) count_ttbar_1lep++;
        else if(filestr.find("ttbar_2lep") != string::npos) count_ttbar_2lep++;
        else if(filestr.find("ttbar_inc") != string::npos) count_ttbar++;
        else if(filestr.find("data") != string::npos) count_data++;
        else count_rare++;

        if((filestr.find("WJetsToLNu_") != string::npos || filestr.find("WJetsToLNu_Inc") != string::npos) && count_wjets == 1) vIt_fun=0;
        else if((filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos) && count_wjets == 1) vIt_fun=0;
        else if((filestr.find("ST") != string::npos) && count_st==1) vIt_fun=6;
        else if((filestr.find("ttbar_inc") != string::npos) && count_ttbar==1) vIt_fun=1;
        else if((filestr.find("ttbar_1lep") != string::npos) && count_ttbar_1lep==1) vIt_fun=4;
        else if((filestr.find("ttbar_2lep") != string::npos) && count_ttbar_2lep==1) vIt_fun=5;
        else if((filestr.find("data") != string::npos) && count_data==1) vIt_fun=3;
        else if(count_rare==1) vIt_fun=2;
    }

    std::string plotstring(_thePlotStringName);
    int nsteps = 0;
    float step_size = 0;
    float value0 =0;
    if(plotstring.find("allhighDM") != string::npos){
      nsteps =4;
      step_size = 100;
      value0 =250;
    }else if(plotstring.find("alllowDM") != string::npos){
            nsteps = 2;
    }else if(plotstring.find("0bCR2") != string::npos){
      nsteps = 2;
//      step_size = 100;
  //    value0 =250;
    }else if(plotstring.find("2JetsInc") != string::npos){
      nsteps = 1;
          _theminNJetsCut =2;
    }else if(plotstring.find("2JetsExc") != string::npos){
      nsteps = 3;
      step_size = 1;
      value0 =2;
//            
    }else{

    //  if(_theminNJetsCut ==4) nsteps = 4;
//      else 
nsteps =1;
      step_size = 100;
      value0 =230;
    }
   TFile *fNumbers = new TFile(Form("%s_Numbers.root",_thePlotStringName),"recreate");
//fNumbers->SetDirectory(0);
TH1D* hEstimate = new TH1D("hEstimate","hEstimate",nsteps+1,0, nsteps);
TH1D* hTFMet = new TH1D("hTFMet","hTFMet",nsteps+1,0, nsteps);
TH1D* hTFBtag = new TH1D("hTFBtag","hTFBtag",nsteps+1,0, nsteps);
TH1D* hNCR = new TH1D("hNCR","hNCR",nsteps+1,0, nsteps);
TH1D* hCont = new TH1D("hCont","hCont",nsteps+1,0, nsteps);

TH1D* hEstimate_dilep = new TH1D("hEstimate_dilep","hEstimate_dilep",nsteps+1,0, nsteps);
TH1D* hTFMet_dilep = new TH1D("hTFMet_dilep","hTFMet_dilep",nsteps+1,0, nsteps);
TH1D* hTFBtag_dilep = new TH1D("hTFBtag_dilep","hTFBtag_dilep",nsteps+1,0, nsteps);
TH1D* hNCR_dilep = new TH1D("hNCR_dilep","hNCR_dilep",nsteps+1,0, nsteps);

/*fNumbers.Add(hTFMet);

fNumbers.Add(hTFBtag);
fNumbers.Add(hEstimate);
fNumbers.Write();
*/
int nsys = 1;
    for(unsigned int nsys2 = 0; nsys2<nsys;++nsys2){
        wjetssrmc.clear();
        wjetscrmc.clear();
        dilepsrmc.clear();
        dilepcrmc.clear();
        NCR_1l.clear();
        Cont_1l.clear();
        NCR_dilep.clear();
        TotalBGmc.clear();
        if(nsys2 == 13) SetInputFileName("babyfiles_CR3NJets2_JECup.dat");
        if(nsys2 == 14) SetInputFileName("babyfiles_CR3NJets2_JECdown.dat");
        //else SetInputFileName("babyfiles_CR3NJets2.dat");
        if(nsys2==13 || nsys2==14){
           _theRootFiles.clear();
           GetTheFiles();
        }


    for(unsigned int opt_idx = 0; opt_idx<nsteps; ++opt_idx){
       /* _theminMETCut = value0 + (opt_idx)*step_size;
        _themaxMETCut = _theminMETCut + step_size;
        if(opt_idx==nsteps-1) _themaxMETCut =9999.;
       */
     for(unsigned int vIt = 0; vIt < _theRootFiles.size(); vIt++){
        TFile *file = new TFile(_theRootFiles.at(vIt).c_str(),"read");
        if ( file->IsOpen() ) printf("File %s opened successfully\n", _theRootFiles.at(vIt).c_str());
        //sanity check
        cout<<"Looking at Events with MET CUT = "<<_theminMETCut<<"  -  "<<_themaxMETCut<<endl;
        TTree *tree = (TTree*)file->Get("t");
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        stopcms3.Init(tree);

        // Loop over Events in current file
        unsigned int nEventsTree = tree->GetEntriesFast();

        clearEventCounters();
        ClearCutFlowVectors(vIt);

        std::string filestr (_theNameMap[vIt]);
        //h1s.BookBasicHistos(vIt, filestr);
         TH1D* h_counter;
         if(filestr.find("data") == string::npos || filestr.find("ttbar")==string::npos)    h_counter = (TH1D*) file->Get("h_counter");
        for( unsigned int event = 0; event < nEventsTree; ++event) {    
//        for( unsigned int event = 0; event < 10000; ++event) { 
          tree->LoadTree(event);
          stopcms3.GetEntry(event);
if(is_data()) myfile<<run()<<" "<<ls()<<endl;
          float scale_vary=1.;
          float MCscale_HF=1.;
          float MCscale_met = 1.;
          float MCscaling = (weight_lepSF()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(28));
//(weight_btagsf()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(14))*(weight_lepSF()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(28));
        //  MCscaling = MCscaling*(weight_vetoLepSF()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(31));
          float MCscale_btageff=1.;
          bool apply_HFweight_up =false;
          if(nsys2==1) apply_HFweight_up = true;
          if(apply_HFweight_up) MCscale_HF = GetHFWeight(1.5);
          bool apply_HFweight_down = false;
          if(nsys2==2) apply_HFweight_down =true;
          if(apply_HFweight_down) MCscale_HF = GetHFWeight(0.5);
          bool apply_btagSF_central = true;
          if(apply_btagSF_central) MCscale_btageff = (weight_btagsf()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(14));//*lep_sf();  //weight_btagsf;//SF_Bnjets = ngoodbtags();
          bool apply_btagHF_up = false;
          if(nsys2==3) apply_btagHF_up=true;
         if(apply_btagHF_up) MCscale_btageff =weight_btagsf_heavy_UP()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(15);
          bool apply_btagHF_down = false;
          if(nsys2==4) apply_btagHF_down=true;
          if(apply_btagHF_down) MCscale_btageff = weight_btagsf_heavy_DN()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(17);
          bool apply_btagLF_up = false;
          if(nsys2==5) apply_btagLF_up=true;
         if(apply_btagLF_up) MCscale_btageff =weight_btagsf_light_UP()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(16);
          bool apply_btagLF_down = false;
          if(nsys2==6) apply_btagLF_down=true;
          if(apply_btagLF_down) MCscale_btageff = weight_btagsf_light_DN()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(18);

          if(filestr.find("ttbar") != string::npos || filestr.find("WJetsToLNu_")!= string::npos){
             MCscale_met = metSF(true,false,false);
             if(nsys2==7) MCscale_met = metSF(false,true,false);
             if(nsys2==8) MCscale_met = metSF(false,false,true);
          }

         if(genweights().size()>4){ // continue;
          bool apply_q2_up = false;
         if(nsys2==9) apply_q2_up = true;
          if(apply_q2_up) scale_vary = genweights().at(4)/genweights().at(0);
          bool apply_q2_down = false;
         if(nsys2==10) apply_q2_down = true;
          if(apply_q2_down) scale_vary = genweights().at(8)/genweights().at(0);
          bool apply_pdf_up = false;
         if(nsys2==11) apply_pdf_up = true;
          if(apply_pdf_up) scale_vary = pdf_up_weight()/genweights().at(0);
          bool apply_pdf_down =false;
         if(nsys2==12) apply_pdf_down = true;
          if(apply_pdf_down) scale_vary = pdf_down_weight()/genweights().at(0);
         }

          MCscaling = MCscaling*MCscale_btageff*MCscale_met*scale_vary*getTTbarSysPtSF(filestr);
//if(filestr.find("ttbar") != string::npos) cout<<getTTbarSysPtSF(filestr)<<endl;
//if(filestr.find("ST_t_tbarW") != string::npos || filestr.find(" ST_t_tW") != string::npos)  cout<<getTTbarSysPtSF(filestr)<<endl;
//          MCscaling = (weight_btagsf()*h_counter->GetBinContent(22)/ h_counter->GetBinContent(14));
          if(filestr.find("data") != string::npos) _theScalesMap[vIt] =1.;
        /*  else if(filestr.find("WJetsToLNu_1") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.238;
          else if(filestr.find("WJetsToLNu_2") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.231;
          else if(filestr.find("WJetsToLNu_3") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.231;
          else if(filestr.find("WJetsToLNu_4") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.144;
          else if(filestr.find("WJetsToLNu_nupt200_1") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.115;
          else if(filestr.find("WJetsToLNu_nupt200_2") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.330;
          else if(filestr.find("WJetsToLNu_nupt200_3") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*1.524;
          else if(filestr.find("WJetsToLNu_nupt200_4") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*26.524;
*/
          else if(filestr.find("ttbar") != string::npos) _theScalesMap[vIt] = _theLumi*MCscaling*scale1fb();//*getTTbarSysPtSF(true,false);
          else if(filestr.find("ST_t_tbarW") != string::npos || filestr.find(" ST_t_tW") != string::npos) _theScalesMap[vIt] = _theLumi*MCscaling*scale1fb();//*getTTbarSysPtSF(false,true);
          else if(filestr.find("WJetsToLNu_") != string::npos) _theScalesMap[vIt] = _theLumi*scale1fb()*MCscaling*MCscale_HF;
          else _theScalesMap[vIt] = _theLumi*MCscaling*scale1fb();
//if(filestr.find("WJetsToLNu") != string::npos) _theScalesMap[vIt] =_theScalesMap[vIt] *0.5;
//_theScalesMap[vIt] = _theScalesMap[vIt]/fabs(scale1fb()*_theLumi);
/*          if( filestr.find("WJetsToLNu_Inc") != string::npos) {
            if((genht() >100)) continue;
          }
  */
        ///
          
          if( filestr.find("WJetsToLNu_1") != string::npos || filestr.find("WJetsToLNu_2") != string::npos ||  filestr.find("WJetsToLNu_3") != string::npos  ||  filestr.find("WJetsToLNu_4") != string::npos ){
            if(genmet()>200) continue;
          }
          if( filestr.find("WJetsToLNu_nupt200") != string::npos ){
    //        if(genmet()<200) continue;
          }  
          // 

          if(filestr.find("ttbar_inc") != string::npos){
            if(is1lep())  nEventsTotal=nEventsTotal+_theScalesMap[vIt];
     //       if(is2lep())  nEventsTotal_2lep=nEventsTotal_2lep+_theScalesMap[vIt];
          }else nEventsTotal=nEventsTotal+_theScalesMap[vIt]; 

         if(!is_data() && filestr.find("SMS") == string::npos){
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && _isZnunu())  nEventsTotal_Znunu = nEventsTotal_Znunu+_theScalesMap[vIt];
           else{
             if(_is2lep()) nEventsTotal_2lep = nEventsTotal_2lep+_theScalesMap[vIt];
             if(_is1lep() && _is1lep_fromTop()) nEventsTotal_1lepfromtop = nEventsTotal_1lepfromtop+_theScalesMap[vIt];
             if(_is1lep() && _is1lep_notfromTop()) nEventsTotal_1lepnotfromtop = nEventsTotal_1lepnotfromtop+_theScalesMap[vIt];
//             if(filestr.find("WZTo3LNu") != string::npos || filestr.find("ZZTo4L") != string::npos) nEventsTotal_2lep = nEventsTotal_2lep+_theScalesMap[vIt];
           }   
         }

     //  if(!passT2ttSelections(vIt)) continue;
       if(!passPreSelections(vIt)) continue;
//        if(!passSRSelections()) continue;
     if(plotstring.find("ATLAS_bC2xDiag") != string::npos && !passATLASSelections_bC2xDiag(vIt)) continue;
     if(plotstring.find("ATLAS_lowDM") != string::npos && !passATLASSelections_lowDM(vIt)) continue;
     if(plotstring.find("ATLAS_SR1") != string::npos && !passATLASSelections_SR1(vIt)) continue;

     if(_theBtagTFSel){
//       if(ngoodbtags() >0){
       if(passSRSelections(vIt)){
         if(!is_data() && filestr.find("SMS") == string::npos){
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu()) nEventsPass_Znunu_SR = nEventsPass_Znunu_SR+_theScalesMap[vIt];
           else{
              if(is2lep()) nEventsPass_2lep_SR = nEventsPass_2lep_SR+_theScalesMap[vIt];
              if(is1lepFromTop()) nEventsPass_1lepfromtop_SR = nEventsPass_1lepfromtop_SR+_theScalesMap[vIt];
              if(is1lepFromW()) nEventsPass_1lepnotfromtop_SR = nEventsPass_1lepnotfromtop_SR+_theScalesMap[vIt];
           }
           }
           if(filestr.find("ttbar_inc") != string::npos){
            if(is1lep())  nEventsPass_SR=nEventsPass_SR+_theScalesMap[vIt];
           }else nEventsPass_SR=nEventsPass_SR+_theScalesMap[vIt];

        }else if(pass0bCRSelections()){
         if(!is_data() && filestr.find("SMS") == string::npos){
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu()) nEventsPass_Znunu_0bCR = nEventsPass_Znunu_0bCR+_theScalesMap[vIt];
         else{
           if(is2lep()) nEventsPass_2lep_0bCR = nEventsPass_2lep_0bCR+_theScalesMap[vIt];
           if(is1lepFromTop()) nEventsPass_1lepfromtop_0bCR = nEventsPass_1lepfromtop_0bCR+_theScalesMap[vIt];
           if(is1lepFromW()) nEventsPass_1lepnotfromtop_0bCR = nEventsPass_1lepnotfromtop_0bCR+_theScalesMap[vIt];
         }
         }
           if(filestr.find("ttbar_inc") != string::npos){
            if(is1lep())  nEventsPass_0bCR=nEventsPass_0bCR+_theScalesMap[vIt];
           }else nEventsPass_0bCR=nEventsPass_0bCR+_theScalesMap[vIt];

           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu())  h0bCR.FillSRHistos_Znunu(vIt,_theScalesMap[vIt]);
           else{
             if(is2lep()) h0bCR.FillSRHistos_Dilep(vIt,_theScalesMap[vIt]);
             if(is1lepFromTop()) h0bCR.FillSRHistos_SingleLep_fromtop(vIt,_theScalesMap[vIt]);
             if(is1lepFromW()) h0bCR.FillSRHistos_SingleLep_notfromtop(vIt,_theScalesMap[vIt]);
           }
        if(filestr.find("SMS") != string::npos) h0bCR.FillSRHistos_Signal(vIt,_theScalesMap[vIt]*_theSignalScale);
        else if(filestr.find("ttbar_inc") != string::npos){
          if((is1lep())) h0bCR.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
          if((is2lep())) h0bCR.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        }else if(filestr.find("WJetsToLNu_Inc") != string::npos) h0bCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos) h0bCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("WJetsToLNu") != string::npos) h0bCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_2lep") != string::npos) h0bCR.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_1lep") != string::npos) h0bCR.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ST") != string::npos) h0bCR.FillSRHistos_ST(vIt,_theScalesMap[vIt]);
        else if(filestr.find("data") != string::npos) h0bCR.FillSRHistos_data(vIt,_theScalesMap[vIt]);
        else h0bCR.FillSRHistos_Rare(vIt,_theScalesMap[vIt]);         
         continue;
        }else if(passDilepSelections()){       
          if(!is_data() && filestr.find("SMS") == string::npos){
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu()) nEventsPass_Znunu_2lCR = nEventsPass_Znunu_2lCR+_theScalesMap[vIt];
         else{
           if(is2lep()) nEventsPass_2lep_2lCR = nEventsPass_2lep_2lCR+_theScalesMap[vIt];
           if(is1lepFromTop()) nEventsPass_1lepfromtop_2lCR = nEventsPass_1lepfromtop_2lCR+_theScalesMap[vIt];         
           if(is1lepFromW()) nEventsPass_1lepnotfromtop_2lCR = nEventsPass_1lepnotfromtop_2lCR+_theScalesMap[vIt];      
         }
         }
           if(filestr.find("ttbar_inc") != string::npos){
            if(is1lep())  nEventsPass_2lCR=nEventsPass_2lCR+_theScalesMap[vIt];
           }else nEventsPass_2lCR=nEventsPass_2lCR+_theScalesMap[vIt];

           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu())  h2lCR.FillSRHistos_Znunu(vIt,_theScalesMap[vIt]);
           else{
             if(is2lep()) h2lCR.FillSRHistos_Dilep(vIt,_theScalesMap[vIt]);
             if(is1lepFromTop()) h2lCR.FillSRHistos_SingleLep_fromtop(vIt,_theScalesMap[vIt]);
             if(is1lepFromW()) h2lCR.FillSRHistos_SingleLep_notfromtop(vIt,_theScalesMap[vIt]);
           }
        if(filestr.find("SMS") != string::npos) h2lCR.FillSRHistos_Signal(vIt,_theScalesMap[vIt]*_theSignalScale);
        else if(filestr.find("ttbar_inc") != string::npos){
          if((is1lep())) h2lCR.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
          if((is2lep())) h2lCR.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        }else if(filestr.find("WJetsToLNu_Inc") != string::npos) h2lCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos) h2lCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("WJetsToLNu") != string::npos) h2lCR.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_2lep") != string::npos) h2lCR.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_1lep") != string::npos) h2lCR.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ST") != string::npos) h2lCR.FillSRHistos_ST(vIt,_theScalesMap[vIt]);
        else if(filestr.find("data") != string::npos) h2lCR.FillSRHistos_data(vIt,_theScalesMap[vIt]);
        else h2lCR.FillSRHistos_Rare(vIt,_theScalesMap[vIt]);
         continue;
        }else continue;
      }

         if(filestr.find("ttbar_inc") != string::npos){
            if(is1lep())  nEventsPass=nEventsPass+_theScalesMap[vIt];
         }else nEventsPass=nEventsPass+_theScalesMap[vIt];

         if(!is_data() && filestr.find("SMS") == string::npos){
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu()) nEventsPass_Znunu = nEventsPass_Znunu+_theScalesMap[vIt];
           else{
              if(is2lep()) nEventsPass_2lep = nEventsPass_2lep+_theScalesMap[vIt];
              if(is1lepFromTop()) nEventsPass_1lepfromtop = nEventsPass_1lepfromtop+_theScalesMap[vIt];
              if(is1lepFromW()) nEventsPass_1lepnotfromtop = nEventsPass_1lepnotfromtop+_theScalesMap[vIt];
           }
           if(filestr.find("ZZTo2L2Nu")!= string::npos || (filestr.find("WZTo1L3Nu") != string::npos) || (filestr.find("tZq_nunu") != string::npos || filestr.find("TTZToLLNuNu") != string::npos || filestr.find("ZZTo2Q2Nu")!= string::npos) && isZtoNuNu())  h1s.FillSRHistos_Znunu(vIt,_theScalesMap[vIt]);
           else{
             if(is2lep()) h1s.FillSRHistos_Dilep(vIt,_theScalesMap[vIt]*(12.921/24.363));
             if(is1lepFromTop()) h1s.FillSRHistos_SingleLep_fromtop(vIt,_theScalesMap[vIt]*(3.846/5.892));
             if(is1lepFromW()) h1s.FillSRHistos_SingleLep_notfromtop(vIt,_theScalesMap[vIt]);
           }
        }

        if(filestr.find("SMS") != string::npos) h1s.FillSRHistos_Signal(vIt,_theScalesMap[vIt]*_theSignalScale);
        else if(filestr.find("ttbar_inc") != string::npos){
          if((is1lep())) h1s.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
          if((is2lep())) h1s.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        }else if(filestr.find("WJetsToLNu_Inc") != string::npos) h1s.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos) h1s.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("WJetsToLNu") != string::npos) h1s.FillSRHistos_WJets(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_2lep") != string::npos) h1s.FillSRHistos_2lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ttbar_1lep") != string::npos) h1s.FillSRHistos_1lep(vIt,_theScalesMap[vIt]);
        else if(filestr.find("ST") != string::npos) h1s.FillSRHistos_ST(vIt,_theScalesMap[vIt]);
        else if(filestr.find("data") != string::npos) h1s.FillSRHistos_data(vIt,_theScalesMap[vIt]);
        else h1s.FillSRHistos_Rare(vIt,_theScalesMap[vIt]);

          //FillGenHistos_lep2(vIt);
      } 
      
      GetCutFlowTable(vIt);
      int cuts =_theCutFlowVectorMap[vIt].size();
      cout<<"Counter "<<_theCutFlowVectorMap[vIt].at(cuts-1)<<" scale 1fb "<< scale1fb()<<endl;
      if(filestr.find("SMS") != string::npos){
         h1s.MakeBasicHistoVectors(vIt,_theNameMap[vIt],_theSignalScale);
         h0bCR.MakeBasicHistoVectors(vIt,_theNameMap[vIt],_theSignalScale);
         h2lCR.MakeBasicHistoVectors(vIt,_theNameMap[vIt],_theSignalScale);
      }
      delete tree;
      file->Close();
      delete file;
    }

    h1s.MakeBasicHistoVectors_bckgd();
  //  h1s.MakeBasicSRPlots(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
  //  h1s.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h1s.MakeBasicHistoVectors_bckgd2();
    h1s.MakeBasicSRPlots2(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h1s.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h1s.SaveRootFile(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    //h1s.MakeGenHisto_Plots(Form("IncJets",_theNJetsCut));
    if(electronplot) h1s.MakeElectronPlots(_theLumi,Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    h1s.ClearHistVectors();

    h0bCR.MakeBasicHistoVectors_bckgd();
  //  h0bCR.MakeBasicSRPlots(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
  //  h0bCR.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h0bCR.MakeBasicHistoVectors_bckgd2();
    h0bCR.MakeBasicSRPlots2(Form("%s_pt%2.0f_MET%2.0f_%dJets_0bCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h0bCR.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets_0bCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h0bCR.SaveRootFile(Form("%s_pt%2.0f_MET%2.0f_%dJets_0bCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    //h0bCR.MakeGenHisto_Plots(Form("IncJets",_theNJetsCut));
    if(electronplot) h0bCR.MakeElectronPlots(_theLumi,Form("%s_pt%2.0f_MET%2.0f_%dJets_0bCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    h0bCR.ClearHistVectors();

    h2lCR.MakeBasicHistoVectors_bckgd();
  //  h2lCR.MakeBasicSRPlots(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
  //  h2lCR.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h2lCR.MakeBasicHistoVectors_bckgd2();
    h2lCR.MakeBasicSRPlots2(Form("%s_pt%2.0f_MET%2.0f_%dJets_2lCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h2lCR.BS(Form("%s_pt%2.0f_MET%2.0f_%dJets_2lCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut),_theLumi);
    h2lCR.SaveRootFile(Form("%s_pt%2.0f_MET%2.0f_%dJets_2lCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    //h2lCR.MakeGenHisto_Plots(Form("IncJets",_theNJetsCut));
    if(electronplot) h2lCR.MakeElectronPlots(_theLumi,Form("%s_pt%2.0f_MET%2.0f_%dJets_2lCR",_thePlotStringName,_theLep1PtCut,_theminMETCut,_theminNJetsCut));
    h2lCR.ClearHistVectors();

    //MakeNormalizedPlots();
    //MakeGenHisto_lep2Plots();
    float totalbg = 0;

//  for(unsigned int ri = 1; ri < 5; ri++){
  std::map< int, CNumBase<float> > _tableMap;  
  std::map< int, CNumBase<float> > _tableMap_2lep;
  std::map< int, CNumBase<float> > _tableMap_1lepfromtop;
  std::map< int, CNumBase<float> > _tableMap_1lepnotfromtop;
  std::map< int, CNumBase<float> > _tableMap_znunu;

  std::map< int, CNumBase<float> > _tableMap_0bCR;
  std::map< int, CNumBase<float> > _tableMap_0bCR_2lep;
  std::map< int, CNumBase<float> > _tableMap_0bCR_1lepfromtop;
  std::map< int, CNumBase<float> > _tableMap_0bCR_1lepnotfromtop;
  std::map< int, CNumBase<float> > _tableMap_0bCR_znunu;

  std::map< int, CNumBase<float> > _tableMap_2lCR;
  std::map< int, CNumBase<float> > _tableMap_2lCR_2lep;
  std::map< int, CNumBase<float> > _tableMap_2lCR_1lepfromtop;
  std::map< int, CNumBase<float> > _tableMap_2lCR_1lepnotfromtop;
  std::map< int, CNumBase<float> > _tableMap_2lCR_znunu;

  for(unsigned int vIt = 0; vIt < _theRootFiles.size(); vIt++){
        std::string filestr (_theNameMap[vIt]);
        int cuts =_theCutFlowVectorMap[vIt].size();
     //  cout<<filestr<<" "<<_theCutFlowVectorMap[vIt].at(cuts-1)<<endl;
        if(filestr.find("SMS") == string::npos){
                 if(_theCutFlowVectorMap[vIt].at(cuts-1)>0)  _tableMap[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap[vIt].at(cuts-1)==0) _tableMap[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-1),0);
                 if(_theCutFlowVectorMap[vIt].at(cuts-1)<0) _tableMap[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)>0)  _tableMap_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Dilep[vIt].at(cuts-1));
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)==0) _tableMap_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1),0,0);
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)<0) _tableMap_2lep[vIt] = CNumBase<float>(0,0,0);
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)>0) totalbg=totalbg+_theCutFlowVectorMap_Dilep[vIt].at(cuts-1);

                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1)>0)  _tableMap_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//0.5*_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1));
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1)==0) _tableMap_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1),0,0);
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1)<0) _tableMap_1lepfromtop[vIt] = CNumBase<float>(0,0,0);
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-1)>0) totalbg=totalbg+_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-1);

                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1)>0)  _tableMap_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1)==0) _tableMap_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1),0);
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1)<0) _tableMap_1lepnotfromtop[vIt] = CNumBase<float>(0,0,0);
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1)>0) totalbg = totalbg+_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-1);

                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1)>0)  _tableMap_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Znunu[vIt].at(cuts-1));
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1)==0) _tableMap_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1),0,0);
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1)<0) _tableMap_znunu[vIt] = CNumBase<float>(0,0,0);
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-1)>0) totalbg = totalbg+_theCutFlowVectorMap_Znunu[vIt].at(cuts-1);
              
          }else{
             if(_theCutFlowVectorMap[vIt].at(cuts-1)>0)  _tableMap[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-1),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-1)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
             if(_theCutFlowVectorMap[vIt].at(cuts-1)==0) _tableMap[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-1),0);
             if(_theCutFlowVectorMap[vIt].at(cuts-1)<0) _tableMap[vIt] = CNumBase<float>(0,0,0);
                  cout<<filestr<<"  "<<_theCutFlowVectorMap[vIt].at(cuts-1)<<endl;
          }

     //  cout<<filestr<<" "<<_theCutFlowVectorMap[vIt].at(cuts-2)<<endl;
        if(filestr.find("SMS") == string::npos){
                 if(_theCutFlowVectorMap[vIt].at(cuts-2)>0)  _tableMap_2lCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap[vIt].at(cuts-2)==0) _tableMap_2lCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-2),0);
                 if(_theCutFlowVectorMap[vIt].at(cuts-2)<0) _tableMap_2lCR[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2)>0)  _tableMap_2lCR_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Dilep[vIt].at(cuts-2));
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2)==0) _tableMap_2lCR_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2),0,0);
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-2)<0) _tableMap_2lCR_2lep[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2)>0)  _tableMap_2lCR_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//0.5*_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2));
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2)==0) _tableMap_2lCR_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2),0,0);
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-2)<0) _tableMap_2lCR_1lepfromtop[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2)>0)  _tableMap_2lCR_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2)==0) _tableMap_2lCR_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2),0);
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-2)<0) _tableMap_2lCR_1lepnotfromtop[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2)>0)  _tableMap_2lCR_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Znunu[vIt].at(cuts-2));
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2)==0) _tableMap_2lCR_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2),0,0);
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-2)<0) _tableMap_2lCR_znunu[vIt] = CNumBase<float>(0,0,0);

          }else{
             if(_theCutFlowVectorMap[vIt].at(cuts-2)>0)  _tableMap_2lCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-2),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-2)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
             if(_theCutFlowVectorMap[vIt].at(cuts-2)==0) _tableMap_2lCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-2),0);
             if(_theCutFlowVectorMap[vIt].at(cuts-2)<0) _tableMap_2lCR[vIt] = CNumBase<float>(0,0,0);
                  cout<<filestr<<"  "<<_theCutFlowVectorMap[vIt].at(cuts-2)<<endl;
          }

     //  cout<<filestr<<" "<<_theCutFlowVectorMap[vIt].at(cuts-3)<<endl;
        if(filestr.find("SMS") == string::npos){
                 if(_theCutFlowVectorMap[vIt].at(cuts-3)>0)  _tableMap_0bCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap[vIt].at(cuts-3)==0) _tableMap_0bCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-3),0);
                 if(_theCutFlowVectorMap[vIt].at(cuts-3)<0) _tableMap_0bCR[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3)>0)  _tableMap_0bCR_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Dilep[vIt].at(cuts-3));
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3)==0) _tableMap_0bCR_2lep[vIt] = CNumBase<float>(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3),0,0);
                 if(_theCutFlowVectorMap_Dilep[vIt].at(cuts-3)<0) _tableMap_0bCR_2lep[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3)>0)  _tableMap_0bCR_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//0.5*_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3));
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3)==0) _tableMap_0bCR_1lepfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3),0,0);
                 if(_theCutFlowVectorMap_SingleLep_fromtop[vIt].at(cuts-3)<0) _tableMap_0bCR_1lepfromtop[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3)>0)  _tableMap_0bCR_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3)==0) _tableMap_0bCR_1lepnotfromtop[vIt] = CNumBase<float>(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3),0);
                 if(_theCutFlowVectorMap_SingleLep_notfromtop[vIt].at(cuts-3)<0) _tableMap_0bCR_1lepnotfromtop[vIt] = CNumBase<float>(0,0,0);

                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3)>0)  _tableMap_0bCR_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));//,0.5*_theCutFlowVectorMap_Znunu[vIt].at(cuts-3));
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3)==0) _tableMap_0bCR_znunu[vIt] = CNumBase<float>(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3),0,0);
                 if(_theCutFlowVectorMap_Znunu[vIt].at(cuts-3)<0) _tableMap_0bCR_znunu[vIt] = CNumBase<float>(0,0,0);

          }else{
             if(_theCutFlowVectorMap[vIt].at(cuts-3)>0)  _tableMap_0bCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-3),TMath::Sqrt(_theCutFlowVectorMap[vIt].at(cuts-3)/fabs(_theScalesMap[vIt]))*fabs(_theScalesMap[vIt]));
             if(_theCutFlowVectorMap[vIt].at(cuts-3)==0) _tableMap_0bCR[vIt] = CNumBase<float>(_theCutFlowVectorMap[vIt].at(cuts-3),0);
             if(_theCutFlowVectorMap[vIt].at(cuts-3)<0) _tableMap_0bCR[vIt] = CNumBase<float>(0,0,0);
                  cout<<filestr<<"  "<<_theCutFlowVectorMap[vIt].at(cuts-3)<<endl;
          }
     }

//fill table
  FillTables(opt_idx,_tableMap,_tableMap_2lep,_tableMap_1lepfromtop,_tableMap_1lepnotfromtop,_tableMap_znunu,0);
  FillTables(opt_idx,_tableMap_0bCR,_tableMap_0bCR_2lep,_tableMap_0bCR_1lepfromtop,_tableMap_0bCR_1lepnotfromtop,_tableMap_0bCR_znunu,1);
  FillTables(opt_idx,_tableMap_2lCR,_tableMap_2lCR_2lep,_tableMap_2lCR_1lepfromtop,_tableMap_2lCR_1lepnotfromtop,_tableMap_2lCR_znunu,2);

  float contsys = ((wjetssrmc.at(opt_idx)/wjetscrmc.at(opt_idx))*0.5*Cont_1l.at(opt_idx)).data();
  _table2.at(0).setRowLabel("1l (not from top), Data-driven Estimate",19);
  CNumBase<float> WJetsEst = NCR_1l.at(opt_idx)*(wjetssrmc.at(opt_idx)/wjetscrmc.at(opt_idx));
  WJetsEst.setSyst(contsys);
//  _table2.at(0).setCell(NCR_1l.at(opt_idx)*(wjetssrmc.at(opt_idx)/wjetscrmc.at(opt_idx)),19,opt_idx);
  _table2.at(0).setCell(WJetsEst,19,opt_idx);
  _table2.at(0).setRowLabel("lost lepton, Data-driven Estimate",20);
  _table2.at(0).setCell(NCR_dilep.at(opt_idx)*(dilepsrmc.at(opt_idx)/dilepcrmc.at(opt_idx)),20,opt_idx);
  _table2.at(0).setRowLabel("Total BGs",21);
  _table2.at(0).setCell(TotalBGmc.at(opt_idx) + WJetsEst + NCR_dilep.at(opt_idx)*(dilepsrmc.at(opt_idx)/dilepcrmc.at(opt_idx)),21,opt_idx);
      for(unsigned int vIt = 0; vIt < _theRootFiles.size(); vIt++){
          ClearCutFlowVectors(vIt);
      }
     clear_list();

    }
    for(int i =0; i<ntables;i++){
      _table2.at(i).print();
    }
  }                                                                                                                                                                                                                                                                 
    //table3.push_back(table);
    //table4.push_back(table);
//table2.print() ;

  //    table.saveTex("MTStudies_IncJets.tex");
    for(int i =0; i<ntables;i++){
      _table.at(i).saveTex(Form("%s_leppt%2.0f_MET%2.0f_R%d.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut,i));
      _table2.at(i).saveTex(Form("%s_leppt%2.0f_MET%2.0f_new_R%d.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut,i));
    }
/*
  table3.saveTex(Form("%s_leppt%2.0f_MET%2.0f_0bCR.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut));
  table4.saveTex(Form("%s_leppt%2.0f_MET%2.0f_0bCR.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut));

  table5.saveTex(Form("%s_leppt%2.0f_MET%2.0f_2lCR.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut));
  table6.saveTex(Form("%s_leppt%2.0f_MET%2.0f_new_2lCR.tex",_thePlotStringName,_theLep1PtCut,_theminMETCut));
*/
  /*
     f1.cd();
     f1.Write();
     f1.Close();
  */
  myfile.close();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;

  delete bmark;
  return 0;
}

void BabyLooper::FillTables(int opt,
  std::map< int, CNumBase<float> > tableMap,
  std::map< int, CNumBase<float> > tableMap_2lep,
  std::map< int, CNumBase<float> > tableMap_1lepfromtop,
  std::map< int, CNumBase<float> > tableMap_1lepnotfromtop,
  std::map< int, CNumBase<float> > tableMap_znunu, int ri){

            CNumBase<float> SingleTop;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
            CNumBase<float> Rare;
            CNumBase<float> Total;
            CNumBase<float> WJetsHT;
            CNumBase<float> DYJets;
            CNumBase<float> Data;
            CNumBase<float> TTBar;
            CNumBase<float> TTBar_1lep;
        int singleT = 0;
        int rare = 0;
        int sig =0;
        int wjetsHT = 0;
        int dyjets = 0;
        int data = 0;
int ttbar1lep=0;
int ttbar2lep=0;
CNumBase<float> SingleLep_notfromtop;
CNumBase<float> SingleLep_fromtop;
CNumBase<float> Znunu;
CNumBase<float> Dilep;
CNumBase<float> Total2;


int row=0;
     for(unsigned int vIt = 0; vIt < _theRootFiles.size(); vIt++){
           SingleLep_notfromtop = SingleLep_notfromtop+ tableMap_1lepnotfromtop[vIt];
           SingleLep_fromtop = SingleLep_fromtop + tableMap_1lepfromtop[vIt];
           Znunu = Znunu + tableMap_znunu[vIt];
           Dilep = Dilep + tableMap_2lep[vIt];
           Total2 = Total2+tableMap_1lepnotfromtop[vIt]+tableMap_1lepfromtop[vIt]+tableMap_znunu[vIt]+tableMap_2lep[vIt];

           std::string filestr (_theNameMap[vIt]);
            int cuts =_theCutFlowVectorMap[vIt].size();
           if(filestr.find("ttbar_1lep") != string::npos){
                ttbar1lep++;
                TTBar_1lep = TTBar_1lep+tableMap[vIt];
               if(ttbar1lep==count_ttbar_1lep){
                  _table.at(ri).setRowLabel("ttbar #rightarrow l+jets", 1);
                  _table.at(ri).setCell(TTBar_1lep, 1, opt);
                   row++;
                }
                Total = Total+tableMap[vIt]; //+tableMap_2lep[vIt];
               // TTBar = (tableMap_2lep[vIt]) + tableMap[vIt];
           }else if(filestr.find("ttbar_inc")!= string::npos){
                if(count_ttbar_2lep == 0){
                  _table.at(ri).setRowLabel("ttbar #rightarrow 2lep", 0);
                  _table.at(ri).setCell(tableMap_2lep[vIt], 0, opt);
                  row++;
                }
                _table.at(ri).setRowLabel("ttbar #rightarrow l+jets", 1);
                _table.at(ri).setCell(tableMap[vIt], 1, opt);
                row++;
                Total = Total+tableMap[vIt]+tableMap_2lep[vIt];
           }else if(filestr.find("ttbar_2lep") != string::npos){
                ttbar2lep++;
                TTBar = TTBar+tableMap[vIt];
                if(ttbar2lep==count_ttbar_2lep){
                  _table.at(ri).setRowLabel("ttbar #rightarrow 2lep", 0);
                  _table.at(ri).setCell(TTBar, 0, opt);
                  row++;
                }
                Total = Total+tableMap[vIt];
           }else if(filestr.find("WJetsToLNu_") != string::npos || filestr.find("WJetsToLNu_Inc")!= string::npos){
                WJetsHT = WJetsHT +tableMap[vIt];
                Total = Total+tableMap[vIt];
                wjetsHT++;
                if(wjetsHT==count_wjets){
                  _table.at(ri).setRowLabel("WJets", 3);
                  _table.at(ri).setCell(WJetsHT, 3, opt);
                  row++;
                }

          }else if(filestr.find("W1Jets") != string::npos || filestr.find("W2Jets") != string::npos || filestr.find("W3Jets") != string::npos || filestr.find("W4Jets") != string::npos){
                WJetsHT = WJetsHT +tableMap[vIt];
                Total = Total+tableMap[vIt];
                wjetsHT++;
                if(wjetsHT==count_wjets){
                  _table.at(ri).setRowLabel("WJets", 3);
                  _table.at(ri).setCell(WJetsHT, 3, opt);
                  row++;
                }
           }else if(filestr.find("ST") != string::npos){
                SingleTop = SingleTop + tableMap[vIt];
                Total = Total+tableMap[vIt];
                singleT++;
                if(singleT==count_st){
                  _table.at(ri).setRowLabel("Single Top", 2);
                  _table.at(ri).setCell(SingleTop, 2, opt);
                  row++;
                }
           }else if(filestr.find("SMS") != string::npos){
                sig++;
                _table.at(ri).setRowLabel(_theNameMap[vIt], row+sig);
                _table.at(ri).setCell(tableMap[vIt], row+sig, opt*2);
//                _table.at(ri).setCell(CNumBase<float>(calculateZbi(_theCutFlowVectorMap[vIt].at(cuts-1)*_theLumi, totalbg,0.3)),row+sig, opt*2+1);
//                _table.at(ri).setCell(calculateZbi(_theCutFlowVectorMap[vIt].at(cuts-1)*_theLumi, totalbg,0.3),row+sig, opt*2+1);
          }else if(filestr.find("data") != string::npos){
                Data = Data + tableMap[vIt];
                data++;
                if(data==count_data){
                  _table.at(ri).setRowLabel("Data", 6);
                  _table.at(ri).setCell(Data, 6, opt);
                  row++;
                }
           }else{
                Rare = Rare + tableMap[vIt];
                Total = Total+tableMap[vIt];
                rare++;
                if(rare==count_rare){
                  _table.at(ri).setRowLabel("Rare", 4);
                  _table.at(ri).setCell(Rare, 4, opt);
                  row++;
                }
           }
    }


    _table.at(ri).setRowLabel("Total BGs",row);
    _table.at(ri).setCell(Total,row,opt);

      _table2.at(ri).setRowLabel("W+jets (1lep not from top)",1);
      _table2.at(ri).setCell(SingleLep_notfromtop,1,opt);
      _table2.at(ri).setRowLabel("1lep (from top)",2);
      _table2.at(ri).setCell(SingleLep_fromtop,2,opt);
      _table2.at(ri).setRowLabel("ge 2lep (lost lep)",3);
      _table2.at(ri).setCell(Dilep,3,opt);
      _table2.at(ri).setRowLabel("Zrightarrow nu nu$",4);
      _table2.at(ri).setCell(Znunu,4,opt);
      _table2.at(ri).setRowLabel("Total BGs",5);
      _table2.at(ri).setCell(Total2,5,opt);
      _table2.at(ri).setRowLabel("Data", 6);
      _table2.at(ri).setCell(Data, 6, opt);
      _table2.at(ri).setRowLabel("Data/MC",7);
      _table2.at(ri).setCell(Data/Total2,7,opt);
      _table2.at(ri).setRowLabel("WJets purity",8);
CNumBase<float> purity = CNumBase<float>((SingleLep_notfromtop/Total2).data(),(SingleLep_notfromtop/Total2).stat(),(1.-((SingleLep_notfromtop/Total2)).data())/2.);
      _table2.at(ri).setCell(purity,8,opt);

      _table2.at(ri).setRowLabel("N$^{MC,nonWJets}$",13);
      _table2.at(ri).setCell(Dilep+Znunu+SingleLep_fromtop,13,opt);
      _table2.at(ri).setRowLabel("N$_{0-bjet}^{data, WJets}$",9);
      _table2.at(ri).setCell(Data*SingleLep_notfromtop/Total2,9,opt);
//OLD way      _table2.at(ri).setCell(Data-Dilep-Znunu-SingleLep_fromtop,9,opt);
      _table2.at(ri).setRowLabel("N$_{\ge-bjet}^{MC, WJets}$",10);
     // _table2.at(ri).setCell(SingleLep_notfromtop_1b,10,opt);
      _table2.at(ri).setRowLabel("TF",11);
     // _table2.at(ri).setCell(SingleLep_notfromtop_1b/SingleLep_notfromtop,11,opt);
      _table2.at(ri).setRowLabel("WJets in SR",12);
    //  _table2.at(ri).setCell((Data*SingleLep_notfromtop/Total2)*(SingleLep_notfromtop_1b/SingleLep_notfromtop),12,opt);
//OLD      _table2.at(ri).setCell((Data-Dilep-Znunu-SingleLep_fromtop)*(SingleLep_notfromtop_1b/SingleLep_notfromtop),12,opt);

//vectors for TFMET
CNumBase<float> tfmet;
  _table2.at(ri).setRowLabel("TFMet",14);
  _table2.at(ri).setCell(tfmet,14,opt);
//vectors for btagTF
CNumBase<float> tfbtag;
  _table2.at(ri).setRowLabel("TFTag",15);
  _table2.at(ri).setCell(tfbtag,15,opt);
CNumBase<float> NCR;
  NCR = (Data*SingleLep_notfromtop/Total2);

 if(ri ==0) {
   wjetssrmc.push_back(SingleLep_notfromtop);
   dilepsrmc.push_back(Dilep);
   TotalBGmc.push_back(Znunu+SingleLep_fromtop);
 }
 if(ri ==1) {
   wjetscrmc.push_back(SingleLep_notfromtop);
   NCR_1l.push_back(NCR);
   Cont_1l.push_back(Data*((Dilep+Znunu+SingleLep_fromtop)/Total2));
}
 if(ri ==2) {
   dilepcrmc.push_back(Dilep);
   NCR_dilep.push_back(Data);
 }

  _table2.at(ri).setRowLabel("NCR",16);
  _table2.at(ri).setCell(NCR,16,opt);
  _table2.at(ri).setRowLabel("WJets Estimate",17);
  _table2.at(ri).setCell(tfbtag*NCR,17,opt);
  _table2.at(ri).setRowLabel("Contamination Sys",18);
  _table2.at(ri).setCell(tfbtag*0.5*Data*((Dilep+Znunu+SingleLep_fromtop)/Total2),18,opt);

}

void BabyLooper::ClearCutFlowVectors(int process){
  std::string filestr (_theRootFiles.at(process).c_str());
  _theCutsVectorMap[process].clear();
  _theCutFlowVectorMap[process].clear();
  _theCutFlowVectorMap_2lep[process].clear();
  _theCutFlowVectorMap_Dilep[process].clear();
  _theCutFlowVectorMap_SingleLep_fromtop[process].clear();
  _theCutFlowVectorMap_SingleLep_notfromtop[process].clear();
  _theCutFlowVectorMap_Znunu[process].clear();

}

void BabyLooper::Syncing(){
  //Print out run:lumi:event:lepton_pt:lepton_pdgid:MET:mT:NJets:NBJets:HT
  printf("%d %d %d %4.2f %d %4.2f %4.2f %d %d %4.2f \n",run(),ls(),evt(), lep1_p4().pt(),lep1_pdgid(),pfmet(),mt_met_lep(),ngoodjets(),ngoodbtags(),ak4_HT()); 
  myfile<<run()<<" "<<ls()<<" "<<evt()<<" "<< lep1_p4().pt()<<" "<<lep1_pdgid()<<" "<<pfmet()<<" "<<mt_met_lep()<<" "<<ngoodjets()<<" "<<ngoodbtags()<<" "<<ak4_HT()<<endl;
}

void BabyLooper::GetCutFlowTable(int process){
    //let's make life simple
    std::string filestr (_theRootFiles.at(process).c_str());

    _theCutsVectorMap[process].push_back("N Events Total");
    _theCutsVectorMap[process].push_back("NGoodVertex");
    _theCutsVectorMap[process].push_back("> 1 Good Leptons");
    _theCutsVectorMap[process].push_back("Exactly 1 Good Leptons");
    _theCutsVectorMap[process].push_back("Lepton Type");
    _theCutsVectorMap[process].push_back("Lepton Eta");
    _theCutsVectorMap[process].push_back("Lepton pT");
    _theCutsVectorMap[process].push_back("Lepton ID");
    _theCutsVectorMap[process].push_back("Lepton Iso");
    _theCutsVectorMap[process].push_back("2nd (reco)Lepton Veto");
    _theCutsVectorMap[process].push_back("TrackVeto");
    _theCutsVectorMap[process].push_back("TauVeto");
    _theCutsVectorMap[process].push_back("NJets");
    _theCutsVectorMap[process].push_back("NBtags");
    _theCutsVectorMap[process].push_back("MET");
    _theCutsVectorMap[process].push_back("MT");
    _theCutsVectorMap[process].push_back("lead-b pT>200");
    _theCutsVectorMap[process].push_back("DPhi(W,Lep)");
    _theCutsVectorMap[process].push_back("MinDphi");
    _theCutsVectorMap[process].push_back("hadronic-chi^2");
    _theCutsVectorMap[process].push_back("MT2W");
    _theCutsVectorMap[process].push_back("Triggers");
    _theCutsVectorMap[process].push_back("Filters");
    _theCutsVectorMap[process].push_back("N Events Passed SR");
    _theCutsVectorMap[process].push_back("N Events Passed 0bCR");
    _theCutsVectorMap[process].push_back("N Events Passed 2lCR");
    _theCutsVectorMap[process].push_back("N Events Passed");

    _theCutFlowVectorMap[process].push_back(nEventsTotal);
    _theCutFlowVectorMap[process].push_back(nEvents_vtx);
    _theCutFlowVectorMap[process].push_back(nEvents_NGoodLep);
    _theCutFlowVectorMap[process].push_back(nEvents_ExactlyNGoodLep);
    _theCutFlowVectorMap[process].push_back(nEvents_LepType);
    _theCutFlowVectorMap[process].push_back(nEvents_LepEta);
    _theCutFlowVectorMap[process].push_back(nEvents_LepPt);
    _theCutFlowVectorMap[process].push_back(nEvents_LepID);
    _theCutFlowVectorMap[process].push_back(nEvents_LepIso);
    _theCutFlowVectorMap[process].push_back(nEvents_RecoLepVeto);
    _theCutFlowVectorMap[process].push_back(nEvents_TrackVeto);
    _theCutFlowVectorMap[process].push_back(nEvents_TauVeto);
    _theCutFlowVectorMap[process].push_back(nEvents_NJets);
    _theCutFlowVectorMap[process].push_back(nEvents_NBtags);
    _theCutFlowVectorMap[process].push_back(nEvents_Met);
    _theCutFlowVectorMap[process].push_back(nEvents_MT);
    _theCutFlowVectorMap[process].push_back(nEvents_METSig);
    _theCutFlowVectorMap[process].push_back(nEvents_DPhiWLep);
    _theCutFlowVectorMap[process].push_back(nEvents_MinDPhi);
    _theCutFlowVectorMap[process].push_back(nEvents_Chi2);
    _theCutFlowVectorMap[process].push_back(nEvents_MT2W);
    _theCutFlowVectorMap[process].push_back(nEventsTriggers);
    _theCutFlowVectorMap[process].push_back(nEventsFilters);
    _theCutFlowVectorMap[process].push_back(nEventsPass_SR);
    _theCutFlowVectorMap[process].push_back(nEventsPass_0bCR);
    _theCutFlowVectorMap[process].push_back(nEventsPass_2lCR);
    _theCutFlowVectorMap[process].push_back(nEventsPass);

      _theCutFlowVectorMap_Dilep[process].push_back(nEventsTotal_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_vtx_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_NGoodLep_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_ExactlyNGoodLep_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_LepType_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_LepEta_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_LepPt_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_LepID_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_LepIso_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_RecoLepVeto_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_TrackVeto_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_TauVeto_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_NJets_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_NBtags_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_Met_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_MT_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_METSig_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_DPhiWLep_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_MinDPhi_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_Chi2_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEvents_MT2W_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsTriggers_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsFilters_2lep);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsPass_2lep_SR);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsPass_2lep_0bCR);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsPass_2lep_2lCR);
      _theCutFlowVectorMap_Dilep[process].push_back(nEventsPass_2lep);

      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsTotal_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_vtx_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_NGoodLep_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_ExactlyNGoodLep_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_LepType_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_LepEta_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_LepPt_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_LepID_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_LepIso_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_RecoLepVeto_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_TrackVeto_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_TauVeto_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_NJets_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_NBtags_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_Met_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_MT_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_METSig_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_DPhiWLep_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_MinDPhi_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_Chi2_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEvents_MT2W_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsTriggers_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsFilters_1lepnotfromtop);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsPass_1lepnotfromtop_SR);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsPass_1lepnotfromtop_0bCR);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsPass_1lepnotfromtop_2lCR);
      _theCutFlowVectorMap_SingleLep_notfromtop[process].push_back(nEventsPass_1lepnotfromtop);

      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsTotal_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_vtx_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_NGoodLep_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_ExactlyNGoodLep_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_LepType_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_LepEta_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_LepPt_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_LepID_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_LepIso_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_RecoLepVeto_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_TrackVeto_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_TauVeto_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_NJets_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_NBtags_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_Met_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_MT_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_METSig_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_DPhiWLep_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_MinDPhi_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_Chi2_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEvents_MT2W_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsTriggers_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsFilters_1lepfromtop);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsPass_1lepfromtop_SR);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsPass_1lepfromtop_0bCR);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsPass_1lepfromtop_2lCR);
      _theCutFlowVectorMap_SingleLep_fromtop[process].push_back(nEventsPass_1lepfromtop);

      _theCutFlowVectorMap_Znunu[process].push_back(nEventsTotal_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_vtx_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_NGoodLep_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_ExactlyNGoodLep_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_LepType_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_LepEta_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_LepPt_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_LepID_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_LepIso_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_RecoLepVeto_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_TrackVeto_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_TauVeto_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_NJets_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_NBtags_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_Met_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_MT_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_METSig_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_DPhiWLep_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_MinDPhi_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_Chi2_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEvents_MT2W_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsTriggers_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsFilters_Znunu);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsPass_Znunu_SR);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsPass_Znunu_0bCR);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsPass_Znunu_2lCR);
      _theCutFlowVectorMap_Znunu[process].push_back(nEventsPass_Znunu);

    cout<< _theNameMap[process]<<":  ";
    cout<<"Scale1fb "<<scale1fb()<<" Lumi "<<_theLumi<<" Scale "<<_theScalesMap[process]<<endl;
    cout<<"Total Events = "<<nEventsTotal<<"  Events Passing Cuts = "<<nEventsPass<<"  Total Effiency ="<<(double)nEventsPass/(double)nEventsTotal<<" +/- "<<getBinomialUncertainty(nEventsPass,nEventsTotal)<<endl;
    cout<<"*****************************************************************************************************************************************"<<endl;
    cout<<"Cut \t\t Events\t\t Efficiency \t\t Eff. Unc."<<endl;
      cout<< _theCutsVectorMap[process].at(0)<<" & "<<_theCutFlowVectorMap[process].at(0)<<endl;
    for(unsigned int icut = 3; icut < _theCutFlowVectorMap[process].size(); icut++){
      cout<< _theCutsVectorMap[process].at(icut)<<" & "<<_theCutFlowVectorMap[process].at(icut)<<" & "<<(double)_theCutFlowVectorMap[process].at(icut)/(double)_theCutFlowVectorMap[process].at(icut-1)<<" & "<<getBinomialUncertainty(_theCutFlowVectorMap[process].at(icut),_theCutFlowVectorMap[process].at(icut-1))<<endl;
    }
if(!is_data()){
//    if(filestr.find("ttbar") != string::npos){
      cout<<_theNameMap[process]<<"_Dilep:  ";
      //cout<<"Total Events = "<<nEventsTotal_2lep<<"  Events Passing Cuts = "<<nEventsPass_2lep<<"  Total Effiency ="<<(double)nEventsPass_2lep/(double)nEventsTotal_2lep<<" +/- "<<getBinomialUncertainty(nEventsPass_2lep,nEventsTotal_2lep)<<endl;
     // cout<<"*****************************************************************************************************************************************"<<endl;
     // cout<<"Cut \t\t Events\t\t Efficiency \t\t Eff. Unc."<<endl;
      cout<< _theCutsVectorMap[process].at(0)<<" \t\t "<<_theCutFlowVectorMap_Dilep[process].at(0)<<endl;
      for(unsigned int icut = _theCutFlowVectorMap_Dilep[process].size()-1; icut < _theCutFlowVectorMap_Dilep[process].size(); icut++){
        cout<< _theCutsVectorMap[process].at(icut)<<" \t\t "<<_theCutFlowVectorMap_Dilep[process].at(icut)<<" \t\t "<<(double)_theCutFlowVectorMap_Dilep[process].at(icut)/(double)_theCutFlowVectorMap_Dilep[process].at(icut-1)<<" \t\t "<<getBinomialUncertainty(_theCutFlowVectorMap_Dilep[process].at(icut),_theCutFlowVectorMap_Dilep[process].at(icut-1))<<endl;
      }
      cout<<_theNameMap[process]<<"_1lepfromtop:  ";
     // cout<<"Total Events = "<<nEventsTotal_1lepfromtop<<"  Events Passing Cuts = "<<nEventsPass_1lepfromtop<<"  Total Effiency ="<<(double)nEventsPass_1lepfromtop/(double)nEventsTotal_1lepfromtop<<" +/- "<<getBinomialUncertainty(nEventsPass_1lepfromtop,nEventsTotal_1lepfromtop)<<endl;
     // cout<<"*****************************************************************************************************************************************"<<endl;
     // cout<<"Cut \t\t Events\t\t Efficiency \t\t Eff. Unc."<<endl;
      cout<< _theCutsVectorMap[process].at(0)<<" \t\t "<<_theCutFlowVectorMap_SingleLep_fromtop[process].at(0)<<endl;
      for(unsigned int icut = _theCutFlowVectorMap_SingleLep_fromtop[process].size()-1; icut < _theCutFlowVectorMap_SingleLep_fromtop[process].size(); icut++){
        cout<< _theCutsVectorMap[process].at(icut)<<" \t\t "<<_theCutFlowVectorMap_SingleLep_fromtop[process].at(icut)<<" \t\t "<<(double)_theCutFlowVectorMap_SingleLep_fromtop[process].at(icut)/(double)_theCutFlowVectorMap_SingleLep_fromtop[process].at(icut-1)<<" \t\t "<<getBinomialUncertainty(_theCutFlowVectorMap_SingleLep_fromtop[process].at(icut),_theCutFlowVectorMap_SingleLep_fromtop[process].at(icut-1))<<endl;
      }

      cout<<_theNameMap[process]<<"_1lepnotfromtop:  ";
     // cout<<"Total Events = "<<nEventsTotal_1lepnotfromtop<<"  Events Passing Cuts = "<<nEventsPass_1lepnotfromtop<<"  Total Effiency ="<<(double)nEventsPass_1lepnotfromtop/(double)nEventsTotal_1lepnotfromtop<<" +/- "<<getBinomialUncertainty(nEventsPass_1lepnotfromtop,nEventsTotal_1lepnotfromtop)<<endl;
     // cout<<"*****************************************************************************************************************************************"<<endl;
    //  cout<<"Cut \t\t Events\t\t Efficiency \t\t Eff. Unc."<<endl;
      cout<< _theCutsVectorMap[process].at(0)<<" \t\t "<<_theCutFlowVectorMap_SingleLep_notfromtop[process].at(0)<<endl;
      for(unsigned int icut = _theCutFlowVectorMap_SingleLep_notfromtop[process].size()-1; icut < _theCutFlowVectorMap_SingleLep_notfromtop[process].size(); icut++){
        cout<< _theCutsVectorMap[process].at(icut)<<" \t\t "<<_theCutFlowVectorMap_SingleLep_notfromtop[process].at(icut)<<" \t\t "<<(double)_theCutFlowVectorMap_SingleLep_notfromtop[process].at(icut)/(double)_theCutFlowVectorMap_SingleLep_notfromtop[process].at(icut-1)<<" \t\t "<<getBinomialUncertainty(_theCutFlowVectorMap_SingleLep_notfromtop[process].at(icut),_theCutFlowVectorMap_SingleLep_notfromtop[process].at(icut-1))<<endl;
      }
      cout<<_theNameMap[process]<<"_Znunu:  ";
     // cout<<"Total Events = "<<nEventsTotal_Znunu<<"  Events Passing Cuts = "<<nEventsPass_Znunu<<"  Total Effiency ="<<(double)nEventsPass_Znunu/(double)nEventsTotal_Znunu<<" +/- "<<getBinomialUncertainty(nEventsPass_Znunu,nEventsTotal_Znunu)<<endl;
      //cout<<"*****************************************************************************************************************************************"<<endl;
     // cout<<"Cut \t\t Events\t\t Efficiency \t\t Eff. Unc."<<endl;
      cout<< _theCutsVectorMap[process].at(0)<<" \t\t "<<_theCutFlowVectorMap[process].at(0)<<endl;
      for(unsigned int icut = _theCutFlowVectorMap[process].size()-1; icut < _theCutFlowVectorMap[process].size(); icut++){
        cout<< _theCutsVectorMap[process].at(icut)<<" \t\t "<<_theCutFlowVectorMap_Znunu[process].at(icut)<<" \t\t "<<(double)_theCutFlowVectorMap_Znunu[process].at(icut)/(double)_theCutFlowVectorMap_Znunu[process].at(icut-1)<<" \t\t "<<getBinomialUncertainty(_theCutFlowVectorMap_Znunu[process].at(icut),_theCutFlowVectorMap_Znunu[process].at(icut-1))<<endl;
      }
}
  //  }

}

void BabyLooper::SetRebinFactor(int theRebinFactor){
  _theRebinFactor = theRebinFactor;
}

void BabyLooper::SetBtagTFSel(bool theBtagTFSel){
  _theBtagTFSel = theBtagTFSel;
}

void BabyLooper::SetZllSelections(bool theZllSel){
  _theZllSelec = theZllSel;
}

void BabyLooper::SetWJetsSelections(bool theWJetsSel){
  _theWJetsSelec = theWJetsSel;
}

void BabyLooper::SetMTSelections(bool theMTSel){
  _theMTSelec = theMTSel;
}

void BabyLooper::Set0bSelections(bool the0bSel){
  _the0bSelec = the0bSel;
}

void BabyLooper::SetT2ttSelections(bool theT2ttSel){
  _theT2ttSelec = theT2ttSel;
}

void BabyLooper::SetT2btSelections(bool theT2btSel){
  _theT2btSelec = theT2btSel;
}

void BabyLooper::SetT2bWSelections(bool theT2bWSel){
  _theT2bWSelec = theT2bWSel;
}

void BabyLooper::SetSignalScale(float theSignalScale){
  _theSignalScale = theSignalScale;
}

void BabyLooper::SetLumi(float theLumi){
  _theLumi = theLumi;
}

void BabyLooper::SetLumiErr(float theLumiErr){
  _theLumiErr = theLumiErr;
}

void BabyLooper::SetTreeName(string babytree){
  _theBabytree = babytree;
}

void BabyLooper::SetOutputFileName(const char* output){
  _theOutputFile = output;
}

void BabyLooper::SetInputFileName(const char* input){
  _theInputFile = input;
}

void BabyLooper::SetPlotStringName(char* filestring){
  _thePlotStringName = filestring;
}

void BabyLooper::SetSignalMassXsection(float theMass, float theXSection){
  _theMass = theMass;
  _theXSection = theXSection;
}

void BabyLooper::SetmaxMTCut(float themaxMTCut){
  _themaxMTCut = themaxMTCut;
}

void BabyLooper::SetminMTCut(float theminMTCut){
  _theminMTCut = theminMTCut;
}

void BabyLooper::SetminMT2WCut(float theminMT2WCut){
  _theminMT2WCut = theminMT2WCut;
}
void BabyLooper::SetmaxMT2WCut(float themaxMT2WCut){
  _themaxMT2WCut = themaxMT2WCut;
}

void BabyLooper::SetminMETCut(float theminMETCut){
  _theminMETCut = theminMETCut;
}
void BabyLooper::SetmaxMETCut(float themaxMETCut){
  _themaxMETCut = themaxMETCut;
}

void BabyLooper::SetminNJetsCut(int theminNJetsCut){
  _theminNJetsCut = theminNJetsCut;
}
void BabyLooper::SetmaxNJetsCut(int themaxNJetsCut){
  _themaxNJetsCut = themaxNJetsCut;
}

void BabyLooper::SetminNBJetsCut(int theminNBJetsCut){
  _theminNBJetsCut = theminNBJetsCut;
}
void BabyLooper::SetmaxNBJetsCut(int themaxNBJetsCut){
  _themaxNBJetsCut = themaxNBJetsCut;
}

void BabyLooper::SetminNLepsCut(int theminNLepsCut){
  _theminNLepsCut = theminNLepsCut;
}
void BabyLooper::SetmaxNLepsCut(int themaxNLepsCut){
  _themaxNLepsCut = themaxNLepsCut;
}

void BabyLooper::SetRecoLepVeto(bool therecolepveto){
  _therecolepveto = therecolepveto;
}
void BabyLooper::SetIsoTrackVeto(bool theisotrackveto){
  _theisotrackveto = theisotrackveto;
}
void BabyLooper::SetTauVeto(bool thetauveto){
  _thetauveto = thetauveto;
}

void BabyLooper::SetminModTopness(float minModTopness){
  _minModTopness = minModTopness;
}

void BabyLooper::SetCustomTCut(string CustomTCut){
  _theCustomTCut = CustomTCut;
}

void BabyLooper::SetLep1PtCut(float theLep1PtCut){
  _theLep1PtCut = theLep1PtCut;
}

void BabyLooper::SetLep1MinEtaCut(float theLep1MinEtaCut){
  _theLep1MinEtaCut = theLep1MinEtaCut;
}

void BabyLooper::SetLep1MaxEtaCut(float theLep1MaxEtaCut){
  _theLep1MaxEtaCut = theLep1MaxEtaCut;
}

void BabyLooper::SetLep2PtCut(float theLep2PtCut){
  _theLep2PtCut = theLep2PtCut;
}
void BabyLooper::SetLep2EtaCut(float theLep2EtaCut){
  _theLep2EtaCut = theLep2EtaCut;
}

void BabyLooper::SetMinDPhiCut(float theMinDPhiCut){
  _theMinDPhiCut = theMinDPhiCut;
}

void BabyLooper::SetChi2Cut(float theChi2Cut){
  _theChi2Cut = theChi2Cut;
}

void BabyLooper::SetAbsIsoCut(float theAbsIsoCut){
  _theAbsIsoCut = theAbsIsoCut;
}

void BabyLooper::SetRelIsoCut(float theRelIsoCut){
  _theRelIsoCut = theRelIsoCut;
}

void BabyLooper::SetMiniRelIsoCut(float theMiniRelIsoCut){
  _theMiniRelIsoCut = theMiniRelIsoCut;
}

void BabyLooper::SetLep1isElectron(bool theLep1isElectron){
  _theLep1isElectron = theLep1isElectron;
}

void BabyLooper::SetLep1isMuon(bool theLep1isMuon){
  _theLep1isMuon = theLep1isMuon;
}

void BabyLooper::SetISRPt(float theISRPt){
  _theISRPt = theISRPt;
}

void BabyLooper::SetMETSig(float theMETSig){
  _theMETSig = theMETSig;
}

void BabyLooper::SetDPhiWLep(float theDPhiWLep){
  _theDPhiWLep = theDPhiWLep;
}

void BabyLooper::GetTheFiles(){
  vector<TString> output;
  char buffer[500];
  char StringValue[1000];
  int i = 0;

  ifstream IN(_theInputFile);
  while( IN.getline(buffer, 500, '\n') ){
    // ok = false;
    if (buffer[0] == '#') {
      continue; // Skip lines commented with '#'
    }
    if( !strcmp(buffer, "SAMPLE")){     
      bool add = false;
      IN.getline(buffer, 500, '\n');
      sscanf(buffer, "Name\t%s", StringValue);
      _theNameMap[i] = string(StringValue);
      i++; 
      IN.getline(buffer, 500, '\n');
      sscanf(buffer, "Path\t%s", StringValue);

      _theRootFiles.push_back(StringValue);
    }
  }
}

bool BabyLooper::passATLASSelections_bC2xDiag(int process){
  if(GetATLASGoodJets()<4) return false;
  if(getdphi(pfmet_phi(), ak4pfjets_p4().at(0).phi())  <= 1.2) return false;
  if(getdphi(pfmet_phi(), ak4pfjets_p4().at(1).phi())  <= 0.8) return false;
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi()); 
//  if(MT2_lb_b() <= 170.) return false;
  if(AMT2<= 170.) return false;
  return true;
}

bool BabyLooper::passATLASSelections_lowDM(int process){
  if(GetATLASGoodJets2()<4) return false;
  if(getdphi(pfmet_phi(), lep1_p4().phi())  <= 0.8) return false;
  if(getMinDphi(pfmet_phi(), ak4pfjets_p4().at(0), ak4pfjets_p4().at(1), ak4pfjets_p4().at(2), ak4pfjets_p4().at(3)) <=1.4) return false;
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  //if(getMHTSig() <=14.) return false;
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
  if(AMT2<= 140.) return false;
  return true;
}

bool BabyLooper::passATLASSelections_SR1(int process){
  if(GetATLASGoodJets3()<4) return false;
  vector<int> jetIndexSortedCSV;
  jetIndexSortedCSV =  JetIndexCSVsorted(ak4pfjets_CSV(), ak4pfjets_p4());
  //if(getMHTSig() <=14.) return false;
  float AMT2 = getamt2(ak4pfjets_p4().at(jetIndexSortedCSV.at(0)), ak4pfjets_p4().at(jetIndexSortedCSV.at(1)),lep1_p4(),pfmet(), pfmet_phi());
  if(AMT2<= 175.) return false;
  if(topness()<6.5) return false;
  vector<float> dummy_sigma; dummy_sigma.clear(); //move outside of if-clause to be able to copy for photon selection
  for (size_t idx = 0; idx < ak4pfjets_p4().size(); ++idx){
    dummy_sigma.push_back(0.1);
  } 
  LorentzVector lep = lep1_p4();
  if(!getMTopChi2(ak4pfjets_p4(),dummy_sigma,ak4pfjets_passMEDbtag(),lep)) return false;
  return true;
}


bool BabyLooper::passPreSelections(int process){
     std::string filestr2 (_theNameMap[process]);

  //   if(filestr2.find("SMS_T2tb") != string::npos && !isT2bt()) return false;
     if(nvtxs()<1) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_vtx = _theScalesMap[process] + nEvents_vtx;
         if(is2lep())  nEvents_vtx_2lep = _theScalesMap[process] + nEvents_vtx_2lep;
       }else nEvents_vtx = _theScalesMap[process] + nEvents_vtx;
     if(ngoodleps() < _theminNLepsCut) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_NGoodLep = _theScalesMap[process] + nEvents_NGoodLep;
         if(is2lep())  nEvents_NGoodLep_2lep = _theScalesMap[process] + nEvents_NGoodLep_2lep;
       }else nEvents_NGoodLep = _theScalesMap[process] + nEvents_NGoodLep;

     if(_theLep1isElectron && !_theLep1isMuon && abs(lep1_pdgid()) !=11) return false;
     else if(_theLep1isMuon && !_theLep1isElectron && abs(lep1_pdgid()) !=13) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_LepType = _theScalesMap[process] + nEvents_LepType;
         if(is2lep())  nEvents_LepType_2lep = _theScalesMap[process] + nEvents_LepType_2lep;
       }else   nEvents_LepType = _theScalesMap[process] + nEvents_LepType;

     if(_theLep1isElectron && _theLep1isMuon){

         if(abs(lep1_pdgid())==11){
         //   if(fabs( lep1_p4().eta()) < _theLep1MinEtaCut) return false;
        //    if(fabs( lep1_p4().eta()) > _theLep1MaxEtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

            if( lep1_p4().pt() < _theLep1PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
         }else if(abs(lep1_pdgid())==13){
         //   if(fabs( lep1_p4().eta()) > _theLep2EtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

            if( lep1_p4().pt() < _theLep2PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
         }

     }else{
        // if(fabs( lep1_p4().eta()) < _theLep1MinEtaCut) return false;
        // if(fabs( lep1_p4().eta()) > _theLep1MaxEtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

         if( lep1_p4().pt() < _theLep1PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;

     }
     if(abs(lep1_pdgid())==11){
//         if(!lep1_passMediumID()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
             if(is2lep())  nEvents_LepID_2lep = _theScalesMap[process] + nEvents_LepID_2lep;
           }else nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
     }
     if(abs(lep1_pdgid())==13){
         //  if(fabs(lep1_d0())>0.02) return false;
         //  if(fabs(lep1_dz())>0.1) return false;
//           if(!lep1_passMediumID()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
             if(is2lep())  nEvents_LepID_2lep = _theScalesMap[process] + nEvents_LepID_2lep;
           }else nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
     }

     if(lep1_MiniIso()>_theMiniRelIsoCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepIso = _theScalesMap[process] + nEvents_LepIso;
             if(is2lep())  nEvents_LepIso_2lep = _theScalesMap[process] + nEvents_LepIso_2lep;
           }else nEvents_LepIso = _theScalesMap[process] + nEvents_LepIso;

     if(ngoodjets() < _theminNJetsCut) return false;
     if(ngoodjets() > _themaxNJetsCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_NJets = _theScalesMap[process] + nEvents_NJets;
             if(is2lep())  nEvents_NJets_2lep = _theScalesMap[process] + nEvents_NJets_2lep;
           }else nEvents_NJets = _theScalesMap[process] + nEvents_NJets;

     if(pfmet() < _theminMETCut) return false;
     if(pfmet() > _themaxMETCut) return false;
        if(filestr2.find("ttbar_all") != string::npos){
          if(is1lep())  nEvents_Met = _theScalesMap[process] + nEvents_Met;
          if(is2lep())  nEvents_Met_2lep = _theScalesMap[process] + nEvents_Met_2lep;
        }else nEvents_Met = _theScalesMap[process] + nEvents_Met;

     if(mt_met_lep() < _theminMTCut) return false;
     if(mt_met_lep() > _themaxMTCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MT = _theScalesMap[process] + nEvents_MT;
             if(is2lep())  nEvents_MT_2lep = _theScalesMap[process] + nEvents_MT_2lep;
           }else nEvents_MT = _theScalesMap[process] + nEvents_MT;

      if(topnessMod()< _minModTopness) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_METSig = _theScalesMap[process] + nEvents_METSig;
             if(is2lep())  nEvents_METSig_2lep = _theScalesMap[process] + nEvents_METSig_2lep;
           }else nEvents_METSig = _theScalesMap[process] + nEvents_METSig;

     //if(DPhi_W_lep(pfmet(), pfmet_phi(), lep1_p4()) < _theDPhiWLep) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_DPhiWLep = _theScalesMap[process] + nEvents_DPhiWLep;
             if(is2lep())  nEvents_DPhiWLep_2lep = _theScalesMap[process] + nEvents_DPhiWLep_2lep;
           }else nEvents_DPhiWLep = _theScalesMap[process] + nEvents_DPhiWLep;

     if(_theMinDPhiCut!=0 && mindphi_met_j1_j2() < _theMinDPhiCut) return false;
    //   if(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) )< _theMinDPhiCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MinDPhi = _theScalesMap[process] + nEvents_MinDPhi;
             if(is2lep())  nEvents_MinDPhi_2lep = _theScalesMap[process] + nEvents_MinDPhi_2lep;
           }else nEvents_MinDPhi = _theScalesMap[process] + nEvents_MinDPhi;

     if(_theChi2Cut != 0 && hadronic_top_chi2() > _theChi2Cut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_Chi2 = _theScalesMap[process] + nEvents_Chi2;
             if(is2lep())  nEvents_Chi2_2lep = _theScalesMap[process] + nEvents_Chi2_2lep;
           }else nEvents_Chi2 = _theScalesMap[process] + nEvents_Chi2;

     if(MT2W() < _theminMT2WCut) return false;
     if(MT2W() >= _themaxMT2WCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MT2W = _theScalesMap[process] + nEvents_MT2W;
             if(is2lep())  nEvents_MT2W_2lep = _theScalesMap[process] + nEvents_MT2W_2lep;
           }else nEvents_MT2W = _theScalesMap[process] + nEvents_MT2W;

     bool SingleLep = true;
     bool MET = true;
     if(is_data()){
       if(SingleLep && MET){
          if((_theLep1isElectron && abs(lep1_pdgid())==11 && !(HLT_MET() || HLT_SingleEl() || HLT_MET100_MHT100()))) return false;
          else if((_theLep1isMuon && abs(lep1_pdgid())==13 && !(HLT_MET() || HLT_SingleMu() || HLT_MET100_MHT100()))) return false;
         //if(!(HLT_SingleEl() || HLT_MET() ||HLT_SingleMu()) ) return false;
          else nEventsTriggers = _theScalesMap[process] + nEventsTriggers;
       }else if(SingleLep && !MET){
          if((_theLep1isElectron && !( HLT_SingleEl() ))) return false;
          if((_theLep1isMuon && !( HLT_SingleMu() )))  return false;
          nEventsTriggers = _theScalesMap[process] + nEventsTriggers;
       }
     }
    if(is_data()){
  //    bool badevents = !(metFilterTxt.eventFails(run(), ls(), evt()));
      if(!filt_met()) return false;
      if(!filt_badChargedCandidateFilter()) return false;
      if(!filt_badMuonFilter()) return false;
    //  if(!filt_badevents()) return false;
      DorkyEventIdentifier id(run(), evt(), ls());
      if (is_duplicate(id) ) return false;

    }
    nEventsFilters = _theScalesMap[process] + nEventsFilters;
    return true;
}

bool BabyLooper::passSRSelections(int process){
     std::string filestr2 (_theNameMap[process]);

     if(ngoodleps() > _themaxNLepsCut) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_ExactlyNGoodLep = _theScalesMap[process] + nEvents_ExactlyNGoodLep;
         if(is2lep())  nEvents_ExactlyNGoodLep_2lep = _theScalesMap[process] + nEvents_ExactlyNGoodLep_2lep;
       }else nEvents_ExactlyNGoodLep = _theScalesMap[process] + nEvents_ExactlyNGoodLep;

       if(_therecolepveto && nvetoleps()!=1) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep()) nEvents_RecoLepVeto = _theScalesMap[process] + nEvents_RecoLepVeto;
             if(is2lep()) nEvents_RecoLepVeto_2lep = _theScalesMap[process] + nEvents_RecoLepVeto_2lep;
           }else nEvents_RecoLepVeto = _theScalesMap[process] + nEvents_RecoLepVeto;

     if(_theisotrackveto && !PassTrackVeto()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_TrackVeto = _theScalesMap[process] + nEvents_TrackVeto;
             if(is2lep())  nEvents_TrackVeto_2lep = _theScalesMap[process] + nEvents_TrackVeto_2lep;
           }else nEvents_TrackVeto = _theScalesMap[process] + nEvents_TrackVeto;

     if(_thetauveto && !PassTauVeto()) return false;
     if(!PassATLAStauveto()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_TauVeto = _theScalesMap[process] + nEvents_TauVeto;
             if(is2lep())  nEvents_TauVeto_2lep = _theScalesMap[process] + nEvents_TauVeto_2lep;
           }else nEvents_TauVeto = _theScalesMap[process] + nEvents_TauVeto;

     if(ngoodbtags() < _theminNBJetsCut) return false;
     if(ngoodbtags() > _themaxNBJetsCut) return false;
         if(filestr2.find("ttbar_all") != string::npos){
           if(is1lep())  nEvents_NBtags = _theScalesMap[process] + nEvents_NBtags;
           if(is2lep())  nEvents_NBtags_2lep = _theScalesMap[process] + nEvents_NBtags_2lep;
         }else nEvents_NBtags = _theScalesMap[process] + nEvents_NBtags;

  return true;
}

bool BabyLooper::pass0bCRSelections(){
  if(ngoodleps() > _themaxNLepsCut) return false;
  if(!PassATLAStauveto()) return false;
  if(_therecolepveto && nvetoleps()!=1) return false;
  if(_theisotrackveto && !PassTrackVeto()) return false;
 // if(_thetauveto && !PassTauVeto()) return false;
  if(ngoodbtags() >0) return false;
  return true;
}

bool BabyLooper::passDilepSelections(){
  bool is_dilep = false;
  if(ngoodleps() >= 2) {
    is_dilep = true;
  }else if(!PassATLAStauveto() && ngoodleps() == 1) is_dilep = true;
  else if(_therecolepveto && (ngoodleps() == 1 && nvetoleps() >= 2 && lep2_p4().Pt()>10)) is_dilep = true;
//else if (ngoodleps() == 1 && !PassTauVeto()) is_dilep = true;
  if(!is_dilep) return false;

//else if (ngoodleps() == 1 && nvetoleps() >= 2 && lep2_p4().Pt()>10) is_dilep = true;
//  else  if(ngoodleps() == 1 && !PassTrackVeto()) is_dilep = true;
  //else if (ngoodleps() == 1 && !PassTauVeto()) is_dilep = true;
  //if(!is_dilep) return false;
 
  if(ngoodbtags() < _theminNBJetsCut) return false;
  if(ngoodbtags() > _themaxNBJetsCut) return false;

  return true;
}

bool BabyLooper::passT2ttSelections(int process){
     std::string filestr2 (_theNameMap[process]);

     if(filestr2.find("SMS_T2tb") != string::npos && !isT2bt()) return false;
     if(nvtxs()<1) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_vtx = _theScalesMap[process] + nEvents_vtx;
         if(is2lep())  nEvents_vtx_2lep = _theScalesMap[process] + nEvents_vtx_2lep;
       }else nEvents_vtx = _theScalesMap[process] + nEvents_vtx;
     if(ngoodleps() < _theminNLepsCut) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_NGoodLep = _theScalesMap[process] + nEvents_NGoodLep;
         if(is2lep())  nEvents_NGoodLep_2lep = _theScalesMap[process] + nEvents_NGoodLep_2lep;
       }else nEvents_NGoodLep = _theScalesMap[process] + nEvents_NGoodLep;

     if(ngoodleps() > _themaxNLepsCut) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_ExactlyNGoodLep = _theScalesMap[process] + nEvents_ExactlyNGoodLep;
         if(is2lep())  nEvents_ExactlyNGoodLep_2lep = _theScalesMap[process] + nEvents_ExactlyNGoodLep_2lep;
       }else nEvents_ExactlyNGoodLep = _theScalesMap[process] + nEvents_ExactlyNGoodLep;

     if(_theLep1isElectron && !_theLep1isMuon && abs(lep1_pdgid()) !=11) return false;
     else if(_theLep1isMuon && !_theLep1isElectron && abs(lep1_pdgid()) !=13) return false;
       if(filestr2.find("ttbar_all") != string::npos){
         if(is1lep())  nEvents_LepType = _theScalesMap[process] + nEvents_LepType;
         if(is2lep())  nEvents_LepType_2lep = _theScalesMap[process] + nEvents_LepType_2lep;
       }else   nEvents_LepType = _theScalesMap[process] + nEvents_LepType;

     if(_theLep1isElectron && _theLep1isMuon){

         if(abs(lep1_pdgid())==11){
         //   if(fabs( lep1_p4().eta()) < _theLep1MinEtaCut) return false;
        //    if(fabs( lep1_p4().eta()) > _theLep1MaxEtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

            if( lep1_p4().pt() < _theLep1PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
         }else if(abs(lep1_pdgid())==13){
         //   if(fabs( lep1_p4().eta()) > _theLep2EtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

            if( lep1_p4().pt() < _theLep2PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
         }

     }else{
        // if(fabs( lep1_p4().eta()) < _theLep1MinEtaCut) return false;
        // if(fabs( lep1_p4().eta()) > _theLep1MaxEtaCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;
              if(is2lep())  nEvents_LepEta_2lep = _theScalesMap[process] + nEvents_LepEta_2lep;
            }else nEvents_LepEta = _theScalesMap[process] + nEvents_LepEta;

         if( lep1_p4().pt() < _theLep1PtCut) return false;
            if(filestr2.find("ttbar_all") != string::npos){
              if(is1lep())  nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;
              if(is2lep())  nEvents_LepPt_2lep = _theScalesMap[process] + nEvents_LepPt_2lep;
            }else nEvents_LepPt = _theScalesMap[process] + nEvents_LepPt;

     }
     if(abs(lep1_pdgid())==11){
//         if(!lep1_passMediumID()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
             if(is2lep())  nEvents_LepID_2lep = _theScalesMap[process] + nEvents_LepID_2lep;
           }else nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
     }
     if(abs(lep1_pdgid())==13){
         //  if(fabs(lep1_d0())>0.02) return false;
         //  if(fabs(lep1_dz())>0.1) return false;
//           if(!lep1_passMediumID()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
             if(is2lep())  nEvents_LepID_2lep = _theScalesMap[process] + nEvents_LepID_2lep;
           }else nEvents_LepID = _theScalesMap[process] + nEvents_LepID;
     }

     if(lep1_MiniIso()>_theMiniRelIsoCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_LepIso = _theScalesMap[process] + nEvents_LepIso;
             if(is2lep())  nEvents_LepIso_2lep = _theScalesMap[process] + nEvents_LepIso_2lep;
           }else nEvents_LepIso = _theScalesMap[process] + nEvents_LepIso;

     if(_therecolepveto && nvetoleps()!=1) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep()) nEvents_RecoLepVeto = _theScalesMap[process] + nEvents_RecoLepVeto;
             if(is2lep()) nEvents_RecoLepVeto_2lep = _theScalesMap[process] + nEvents_RecoLepVeto_2lep;
           }else nEvents_RecoLepVeto = _theScalesMap[process] + nEvents_RecoLepVeto;

     if(_theisotrackveto && !PassTrackVeto()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_TrackVeto = _theScalesMap[process] + nEvents_TrackVeto;
             if(is2lep())  nEvents_TrackVeto_2lep = _theScalesMap[process] + nEvents_TrackVeto_2lep;
           }else nEvents_TrackVeto = _theScalesMap[process] + nEvents_TrackVeto;

     if(_thetauveto && !PassTauVeto()) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_TauVeto = _theScalesMap[process] + nEvents_TauVeto;
             if(is2lep())  nEvents_TauVeto_2lep = _theScalesMap[process] + nEvents_TauVeto_2lep;
           }else nEvents_TauVeto = _theScalesMap[process] + nEvents_TauVeto;

     if(ngoodjets() < _theminNJetsCut) return false;
     if(ngoodjets() > _themaxNJetsCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_NJets = _theScalesMap[process] + nEvents_NJets;
             if(is2lep())  nEvents_NJets_2lep = _theScalesMap[process] + nEvents_NJets_2lep;
           }else nEvents_NJets = _theScalesMap[process] + nEvents_NJets;

     if(ngoodbtags() < _theminNBJetsCut) return false;
     if(ngoodbtags() > _themaxNBJetsCut) return false;
     //  if(GetNGoodBJets() < _theminNBJetsCut) return false;
      // if(GetNGoodBJets() > _themaxNBJetsCut) return false;
         if(filestr2.find("ttbar_all") != string::npos){
           if(is1lep())  nEvents_NBtags = _theScalesMap[process] + nEvents_NBtags;
           if(is2lep())  nEvents_NBtags_2lep = _theScalesMap[process] + nEvents_NBtags_2lep;
         }else nEvents_NBtags = _theScalesMap[process] + nEvents_NBtags;

     if(pfmet() < _theminMETCut) return false;
     if(pfmet() > _themaxMETCut) return false;
        if(filestr2.find("ttbar_all") != string::npos){
          if(is1lep())  nEvents_Met = _theScalesMap[process] + nEvents_Met;
          if(is2lep())  nEvents_Met_2lep = _theScalesMap[process] + nEvents_Met_2lep;
        }else nEvents_Met = _theScalesMap[process] + nEvents_Met;

     if(mt_met_lep() < _theminMTCut) return false;
     if(mt_met_lep() > _themaxMTCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MT = _theScalesMap[process] + nEvents_MT;
             if(is2lep())  nEvents_MT_2lep = _theScalesMap[process] + nEvents_MT_2lep;
           }else nEvents_MT = _theScalesMap[process] + nEvents_MT;
//cout<<"postmt "<<ngoodjets()<<endl;
//     if(pfmet()/TMath::Sqrt(ak4_HT()) < _theMETSig) return false;
      if(topnessMod()< _minModTopness) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_METSig = _theScalesMap[process] + nEvents_METSig;
             if(is2lep())  nEvents_METSig_2lep = _theScalesMap[process] + nEvents_METSig_2lep;
           }else nEvents_METSig = _theScalesMap[process] + nEvents_METSig;


     //if(DPhi_W_lep(pfmet(), pfmet_phi(), lep1_p4()) < _theDPhiWLep) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_DPhiWLep = _theScalesMap[process] + nEvents_DPhiWLep;
             if(is2lep())  nEvents_DPhiWLep_2lep = _theScalesMap[process] + nEvents_DPhiWLep_2lep;
           }else nEvents_DPhiWLep = _theScalesMap[process] + nEvents_DPhiWLep;

     if(_theMinDPhiCut!=0 && mindphi_met_j1_j2() < _theMinDPhiCut) return false;

    //   if(getMinDphi(pfmet_phi(),ak4pfjets_p4().at(0), ak4pfjets_p4().at(1),ak4pfjets_p4().at(2) )< _theMinDPhiCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MinDPhi = _theScalesMap[process] + nEvents_MinDPhi;
             if(is2lep())  nEvents_MinDPhi_2lep = _theScalesMap[process] + nEvents_MinDPhi_2lep;
           }else nEvents_MinDPhi = _theScalesMap[process] + nEvents_MinDPhi;

     if(_theChi2Cut != 0 && hadronic_top_chi2() > _theChi2Cut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_Chi2 = _theScalesMap[process] + nEvents_Chi2;
             if(is2lep())  nEvents_Chi2_2lep = _theScalesMap[process] + nEvents_Chi2_2lep;
           }else nEvents_Chi2 = _theScalesMap[process] + nEvents_Chi2;
//cout<<"postnothing "<<ngoodjets()<<endl;
     if(MT2W() < _theminMT2WCut) return false;
     if(MT2W() >= _themaxMT2WCut) return false;
           if(filestr2.find("ttbar_all") != string::npos){
             if(is1lep())  nEvents_MT2W = _theScalesMap[process] + nEvents_MT2W;
             if(is2lep())  nEvents_MT2W_2lep = _theScalesMap[process] + nEvents_MT2W_2lep;
           }else nEvents_MT2W = _theScalesMap[process] + nEvents_MT2W;
//cout<<"pre trigger"<<ngoodjets()<<endl;
     bool SingleLep = true;
     bool MET = true;
     if(is_data()){
       if(SingleLep && MET){
          if((_theLep1isElectron && abs(lep1_pdgid())==11 && !(HLT_MET() || HLT_SingleEl() || HLT_MET100_MHT100()))) return false;
          else if((_theLep1isMuon && abs(lep1_pdgid())==13 && !(HLT_MET() || HLT_SingleMu() || HLT_MET100_MHT100()))) return false;
         //if(!(HLT_SingleEl() || HLT_MET() ||HLT_SingleMu()) ) return false;
          else nEventsTriggers = _theScalesMap[process] + nEventsTriggers;
       }else if(SingleLep && !MET){
          if((_theLep1isElectron && !( HLT_SingleEl() ))) return false;
          if((_theLep1isMuon && !( HLT_SingleMu() )))  return false;
          nEventsTriggers = _theScalesMap[process] + nEventsTriggers;
       }
     }
    // nEventsTriggers = _theScalesMap[process] + nEventsTriggers;
//cout<<"post trigger"<<ngoodjets()<<endl;
    if(is_data()){
  //    bool badevents = !(metFilterTxt.eventFails(run(), ls(), evt()));
      if(!filt_met()) return false;
      if(!filt_badChargedCandidateFilter()) return false;
      if(!filt_badMuonFilter()) return false;
    //  if(!filt_badevents()) return false;
      DorkyEventIdentifier id(run(), evt(), ls());
      if (is_duplicate(id) ) return false;

    }
    nEventsFilters = _theScalesMap[process] + nEventsFilters;
//cout<<"post event filters "<<endl;

     return true;
}


void BabyLooper::clearEventCounters(){
    nEventsTotal = 0.;
    nEventsPass = 0.;
    nEventsPass_1b = 0.;
    nEventsTriggers = 0;
    nEventsFilters = 0.;
    nEvents_MT2W = 0.;
    nEvents_MT2W_2lep = 0.;
    nEvents_MinDPhi = 0.;
    nEvents_MinDPhi_2lep = 0.;
    nEvents_Chi2 = 0.;
    nEvents_Chi2_2lep = 0.;
    nEvents_TauVeto_2lep = 0.;
    nEvents_TauVeto = 0.;
    nEvents_TrackVeto_2lep = 0.;
    nEvents_TrackVeto = 0.;
    nEvents_RecoLepVeto = 0.;
    nEvents_RecoLepVeto_2lep =0.;
    nEvents_NBtags_2lep = 0.;
    nEvents_NBtags = 0.;
    nEvents_NJets_2lep = 0.;
    nEvents_NJets = 0.;
    nEvents_MT_2lep = 0.;
    nEvents_MT = 0.;
    nEvents_Met_2lep = 0.;
    nEvents_Met = 0.;
    nEvents_LepIso_2lep = 0.;
    nEvents_LepIso = 0.;
    nEvents_LepID_2lep = 0.;
    nEvents_LepID = 0.;
    nEvents_LepPt_2lep = 0.;
    nEvents_LepPt = 0.;
    nEvents_LepEta_2lep = 0.;
    nEvents_LepEta = 0.;
    nEvents_NGoodLep_2lep = 0.;
    nEvents_NGoodLep = 0.;
    nEvents_vtx = 0.;
    nEvents_vtx_2lep = 0.;
    nEvents_ExactlyNGoodLep_2lep = 0.;
    nEvents_ExactlyNGoodLep = 0.;
    nEvents_LepType_2lep = 0.;
    nEvents_LepType = 0.;

    nEventsTriggers_2lep = 0;
    nEventsFilters_2lep = 0.;

   nEventsTotal_2lep = 0.;
   nEventsPass_2lep = 0.;
   nEventsPass_2lep_1b = 0.;

   nEvents_METSig = 0.;
   nEvents_METSig_2lep = 0.;
   nEvents_DPhiWLep = 0.;
   nEvents_DPhiWLep_2lep = 0.;

   nEventsTotal_Znunu=0.;
   nEventsPass_Znunu=0.;
   nEventsPass_Znunu_1b = 0.;
   nEvents_MT2W_Znunu=0.;
   nEvents_MinDPhi_Znunu=0.;
   nEvents_Chi2_Znunu=0.;
   nEvents_TauVeto_Znunu=0.;
   nEvents_RecoLepVeto_Znunu=0.;
   nEvents_TrackVeto_Znunu=0.;
   nEvents_TrackVeto=0.;
   nEvents_NBtags_Znunu=0.;
   nEvents_NBtags=0.;
   nEvents_NJets_Znunu=0.;
   nEvents_MT_Znunu=0.;
   nEvents_Met_Znunu=0.;
   nEvents_LepIso_Znunu=0.;
   nEvents_LepID_Znunu=0.;
   nEvents_LepPt_Znunu=0.;
   nEvents_LepEta_Znunu=0.;
   nEvents_NGoodLep_Znunu=0.;
   nEvents_vtx_Znunu=0.;
   nEvents_ExactlyNGoodLep_Znunu=0.;
   nEvents_LepType_Znunu=0.;
   nEvents_METSig_Znunu=0.;
    nEventsTriggers_Znunu = 0;
    nEventsFilters_Znunu = 0.;

   nEventsTotal_1lepfromtop=0.;
   nEventsPass_1lepfromtop=0.;
   nEventsPass_1lepfromtop_1b = 0.;
   nEvents_MT2W_1lepfromtop=0.;
   nEvents_MinDPhi_1lepfromtop=0.;
   nEvents_Chi2_1lepfromtop=0.;
   nEvents_TauVeto_1lepfromtop=0.;
   nEvents_RecoLepVeto_1lepfromtop=0.;
   nEvents_TrackVeto_1lepfromtop=0.;
   nEvents_TrackVeto=0.;
   nEvents_NBtags_1lepfromtop=0.;
   nEvents_NBtags=0.;
   nEvents_NJets_1lepfromtop=0.;
   nEvents_MT_1lepfromtop=0.;
   nEvents_Met_1lepfromtop=0.;
   nEvents_LepIso_1lepfromtop=0.;
   nEvents_LepID_1lepfromtop=0.;
   nEvents_LepPt_1lepfromtop=0.;
   nEvents_LepEta_1lepfromtop=0.;
   nEvents_NGoodLep_1lepfromtop=0.;
   nEvents_vtx_1lepfromtop=0.;
   nEvents_ExactlyNGoodLep_1lepfromtop=0.;
   nEvents_LepType_1lepfromtop=0.;
   nEvents_METSig_1lepfromtop=0.;
   nEvents_DPhiWLep_1lepfromtop=0.;
    nEventsTriggers_1lepfromtop = 0;
    nEventsFilters_1lepfromtop = 0.;

   nEventsTotal_1lepnotfromtop=0.;
   nEventsPass_1lepnotfromtop=0.;
   nEventsPass_1lepnotfromtop_1b=0.;
   nEvents_MT2W_1lepnotfromtop=0.;
   nEvents_MinDPhi_1lepnotfromtop=0.;
   nEvents_Chi2_1lepnotfromtop=0.;
   nEvents_TauVeto_1lepnotfromtop=0.;
   nEvents_RecoLepVeto_1lepnotfromtop=0.;
   nEvents_TrackVeto_1lepnotfromtop=0.;
   nEvents_TrackVeto=0.;
   nEvents_NBtags_1lepnotfromtop=0.;
   nEvents_NBtags=0.;
   nEvents_NJets_1lepnotfromtop=0.;
   nEvents_MT_1lepnotfromtop=0.;
   nEvents_Met_1lepnotfromtop=0.;
   nEvents_LepIso_1lepnotfromtop=0.;
   nEvents_LepID_1lepnotfromtop=0.;
   nEvents_LepPt_1lepnotfromtop=0.;
   nEvents_LepEta_1lepnotfromtop=0.;
   nEvents_NGoodLep_1lepnotfromtop=0.;
   nEvents_vtx_1lepnotfromtop=0.;
   nEvents_ExactlyNGoodLep_1lepnotfromtop=0.;
   nEvents_LepType_1lepnotfromtop=0.;
   nEvents_METSig_1lepnotfromtop=0.;
   nEvents_DPhiWLep_1lepnotfromtop=0.;
    nEventsTriggers_1lepnotfromtop = 0;
    nEventsFilters_1lepnotfromtop = 0.;

   lep2_nels = 0;
   lep2_nmus=0;
   lep2_nleptauels = 0;
   lep2_nleptaumus=0;
   lep2_nth_1prong=0;
   lep2_nth_3prong=0;

   lep2_nels_cracks = 0;
   lep2_nmus_cracks =0;
   lep2_nleptauels_cracks = 0;
   lep2_nleptaumus_cracks =0;
   lep2_nth_1prong_cracks =0;
   lep2_nth_3prong_cracks =0;

   nEventsPass_SR = 0;
   nEventsPass_0bCR = 0;
   nEventsPass_2lCR = 0;

   nEventsPass_Znunu_SR = 0;
   nEventsPass_2lep_SR = 0;
   nEventsPass_1lepfromtop_SR = 0;
   nEventsPass_1lepnotfromtop_SR = 0;

   nEventsPass_Znunu_0bCR = 0;
   nEventsPass_2lep_0bCR = 0;
   nEventsPass_1lepfromtop_0bCR = 0;
   nEventsPass_1lepnotfromtop_0bCR = 0;

   nEventsPass_Znunu_2lCR = 0;
   nEventsPass_2lep_2lCR = 0;
   nEventsPass_1lepfromtop_2lCR = 0;
   nEventsPass_1lepnotfromtop_2lCR = 0;
}

float BabyLooper::getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim){
    if(!h_btag_eff_b || !h_btag_eff_c || !h_btag_eff_udsg) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
      return 1.;
    }

    if(isFastsim && (!h_btag_eff_b_fastsim || !h_btag_eff_c_fastsim || !h_btag_eff_udsg_fastsim)) {
      std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
      return 1.;
    }

    // only use pt bins up to 400 GeV for charm and udsg
    float pt_cutoff = std::max(20.,std::min(399.,double(pt)));
    TH2D* h(0);

    if (abs(mcFlavour) == 5) {
      h = isFastsim ? h_btag_eff_b_fastsim : h_btag_eff_b;
      // use pt bins up to 600 GeV for b
      pt_cutoff = std::max(20.,std::min(599.,double(pt)));
    }
    else if (abs(mcFlavour) == 4) {
      h = isFastsim ? h_btag_eff_c_fastsim : h_btag_eff_c;
    }
    else {
      h = isFastsim ? h_btag_eff_udsg_fastsim : h_btag_eff_udsg;
    }

 //   cout<<h_btag_eff_udsg->Integral()<<"  ";
  //  cout<<h_btag_eff_udsg->GetBinContent(0,0)<<endl;    
    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    int biny = h->GetYaxis()->FindBin(fabs(eta));
    return h->GetBinContent(binx,biny);
}
