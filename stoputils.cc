#include "stoputils.h"
// C++
 #include <iostream>
 #include <fstream>
 #include <vector>

 // StopCMS3
 #include "StopCMS3.h"
 #include "MT2.h"

using namespace std;
using namespace stoptas;
/*
double getTTbarSysPtSF(bool ttbar, bool tW){

  double  weight_ttbarSysPt    = 1.0;
  double weight_ttbarSysPt_up = 1.0;
  double weight_ttbarSysPt_dn = 1.0;

  double sf_val = 1.0;
  double sf_err = 0.0;

  if( !is2lep() ) return weight_ttbarSysPt;


  // Get ttbar/tW system pT
  LorentzVector system_LV(0.0,0.0,0.0,0.0);

  // Grab top quarks
  for(int iGen=0; iGen<(int)genqs_p4().size(); iGen++){
    if( abs(genqs_id().at(iGen))==6 &&
	genqs_isLastCopy().at(iGen) ){
      system_LV += genqs_p4().at(iGen);
    }
  }

  // If tW grab the W
  if(tW){
    for(int iGen=0; iGen<(int)genbosons_p4().size(); iGen++){
      if( abs(genbosons_id().at(iGen))==24 &&
	  genbosons_isHardProcess().at(iGen) &&
	  genbosons_isLastCopy().at(iGen) ){
	system_LV += genbosons_p4().at(iGen);
      }
    }
  }
   
  double system_pt = system_LV.Pt();


  // Get Scale Factor
  if( system_pt>=100.0 && system_pt<150.0 ){
    sf_val = 1.02;
    sf_err = 0.02;
  }

  if( system_pt>=150.0 && system_pt<200.0 ){
    sf_val = 0.98;
    sf_err = 0.02;
  }

  if( system_pt>=200.0 && system_pt<250.0 ){
    sf_val = 0.99;
    sf_err = 0.03;
  }

  if( system_pt>=250.0 && system_pt<350.0 ){
    sf_val = 0.97;
    sf_err = 0.03;
  }

  if( system_pt>=350.0 && system_pt<450.0 ){
    sf_val = 0.98;
    sf_err = 0.05;
  }

  if( system_pt>=450.0 ){
    sf_val = 1.08;
    sf_err = 0.07;
  }


  // true=sf, false=uncertainty only
  //if(!apply_ttbarSysPt_sf) sf_val = 1.0;

  weight_ttbarSysPt    = sf_val;
  weight_ttbarSysPt_up = (sf_val + sf_err );
  weight_ttbarSysPt_dn = (sf_val - sf_err );

  return weight_ttbarSysPt;
}
*/
double metSF(bool central,bool up, bool down){

double sf_val=1.;
double sf_err=0.;

    if( ngoodjets()==2 ){

    if( pfmet()>=250.0 && pfmet()<350.0 ){
      sf_val = 1.048;
      sf_err = 0.007;
    }

    if( pfmet()>=350.0 && pfmet()<450.0 ){
      sf_val = 0.910;
      sf_err = 0.014;
    }

    if( pfmet()>=450.0 ){
      sf_val = 0.776;
      sf_err = 0.020;
    }

  } // end if nJets==2

  if( ngoodjets()==3 ){

    if( pfmet()>=250.0 && pfmet()<350.0 ){
      sf_val = 1.076;
      sf_err = 0.010;
    }

    if( pfmet()>=350.0 && pfmet()<450.0 ){
      sf_val = 0.928;
      sf_err = 0.020;
    }

    if( pfmet()>=450.0 && pfmet()<550.0 ){
      sf_val = 0.808;
      sf_err = 0.030;
    }

    if( pfmet()>=550.0 ){
      sf_val = 0.658;
      sf_err = 0.031;
    }

  } // end if nJets==3



   if( ngoodjets()>=4 ){

    if( MT2W()<200.0 ){

      if( pfmet()>=250.0 && pfmet()<350.0 ){
        sf_val = 1.076;
        sf_err = 0.020;
      }

      if( pfmet()>=350.0 && pfmet()<450.0  ){
        sf_val = 0.939;
        sf_err = 0.023;
      }

      if( pfmet()>=450.0 ){
        sf_val = 0.740;
        sf_err = 0.026;
      }

    } // end if MT2W<200.0

    if( MT2W()>=200.0 ){

      if( pfmet()>=250.0 && pfmet()<350.0 ){
        sf_val = 1.076;
        sf_err = 0.020;
      }

      if( pfmet()>=350.0 && pfmet()<450.0  ){
        sf_val = 0.939;
        sf_err = 0.023;
      }

      if( pfmet()>=450.0 && pfmet()<550.0  ){
        sf_val = 0.873;
        sf_err = 0.037;
      }

      if( pfmet()>=550.0 && pfmet()<650.0  ){
        sf_val = 0.747;
        sf_err = 0.055;
      }

      if( pfmet()>=650.0 ){
        sf_val = 0.564;
        sf_err = 0.047;
      }

    } // end if MT2W>=200.0


  } // end if nJets>=4

  if(central) return sf_val;
  else if(up) return sf_err+sf_val;
  else return sf_val-sf_err;
}

float GetHFWeight(float hfweight){
   const int pdg_c = 4;
   const int pdg_b = 5;
   int nheavy=0;
  
   for(int i=0;i<ak4pfjets_parton_flavor().size();i++){
      //if(!ak4pfjets_passMEDbtag().at(i)) continue;
      //if(abs(ak4pfjets_parton_flavor().at(i)) ==pdg_c) nheavy++;
      if(abs(ak4pfjets_parton_flavor().at(i)) ==pdg_b) nheavy++;
   }

   if(nheavy>0) return hfweight;
   return 1.;
}

int getBkgType(){

    int ngenlep = 0;
    for(unsigned int i=0; i<genleps_id().size(); i++){
        if(genleps_isfromt()[i] || abs(genleps_motherid()[i])==24){
            ngenlep++;
        }
    }

    if(ngenlep==0)
        return 0;
    else if(ngenlep==1)
        return 1;
    else if (ngenlep==2)
        return 2;
    else
        return 3;


}

bool _is1lep(){
    bool _1lep = false;
      int nGenPromptLep = 0;
      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
       if( genleps_isLastCopy().at(iGen) && genleps_fromHardProcessFinalState().at(iGen) ) ++nGenPromptLep; //cout<<"genel  "<<genels_motherid().at(iGen)<<" "<<genels_simplemotherid().at(iGen)<<" "<<genels_status().at(iGen)<<endl; }
        if(abs(genleps_id().at(iGen)) == 15 && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessDecayed().at(iGen) ) ++nGenPromptLep;
      }
      if(nGenPromptLep==1) _1lep = true;
      return nGenPromptLep;
}

bool _is1lep_fromTop(){
      if(!_is1lep()) return false;
      if(_is2lep()) return false;
      bool _1lep = false;
      int nGenPromptLep = 0;
      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
        if(genleps_isfromt().at(iGen) && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessFinalState().at(iGen) ) ++nGenPromptLep; //cout<<"genel  "<<genels_motherid().at(iGen)<<" "<<genels_simplemotherid().at(iGen)<<" "<<genels_status().at(iGen)<<endl; }
        if(genleps_isfromt().at(iGen) && abs(genleps_id().at(iGen)) == 15 && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessDecayed().at(iGen) ) ++nGenPromptLep;
      }

      if(nGenPromptLep==1) _1lep = true;
      return _1lep;
}

bool _is1lep_notfromTop(){
    if(!_is1lep()) return false;
    if(_is2lep()) return false;
    if(_isZnunu()) return false;
      bool _1lep = false;
      int nGenPromptLep = 0;
      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
        if(!genleps_isfromt().at(iGen) && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessFinalState().at(iGen) ) ++nGenPromptLep; //cout<<"genel  "<<genels_motherid().at(iGen)<<" "<<genels_simplemotherid().at(iGen)<<" "<<genels_status().at(iGen)<<endl; }
        if(!genleps_isfromt().at(iGen) && abs(genleps_id().at(iGen)) == 15 && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessDecayed().at(iGen) ) ++nGenPromptLep;

      }

      if(nGenPromptLep==1) _1lep = true;
      return _1lep;
}


bool _is2lep(){
    bool _2lep = false;
    if(_isZnunu()) return false;
      int nGenPromptLep = 0;
      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
        if( genleps_isLastCopy().at(iGen) && genleps_fromHardProcessFinalState().at(iGen) ) ++nGenPromptLep; //cout<<"genel  "<<genels_motherid().at(iGen)<<" "<<genels_simplemotherid().at(iGen)<<" "<<genels_status().at(iGen)<<endl; }
        if(abs(genleps_id().at(iGen)) == 15 && genleps_isLastCopy().at(iGen) && genleps_fromHardProcessDecayed().at(iGen) ) ++nGenPromptLep;
      }
// cout<<nGenPromptLep<<endl;
      if(nGenPromptLep>1) _2lep = true;
      return _2lep;
}

bool _isZnunu(){
   //if(is2lep()) return false;
   bool Znunu = false;
      for(int iGen=0; iGen<(int)gennus_p4().size(); iGen++){
        if(Znunu) break;
        //cout<<gennus_isLastCopy().at(iGen)<<" "<<gennus_fromHardProcessFinalState().at(iGen)<<" "<<gennus_motherid().at(iGen)<<endl;
        if( gennus_isLastCopy().at(iGen) && gennus_fromHardProcessFinalState().at(iGen) && gennus_motherid().at(iGen)==23 ) Znunu = true;
      }
   return Znunu;
}

int getStopDecayMode() {

    int pos_mid = 0, neg_mid = 0;
    for(unsigned int i=0; i<gensusy_motherid().size() ; i++){
        int mid = gensusy_motherid()[i];
        if(mid < 0){
            if(neg_mid!=0 && neg_mid!=abs(mid))
                cout << "WARNING!!! strange decay pattern" << endl;
            neg_mid = abs(mid);
        }else{
            if(pos_mid!=0 && pos_mid!=abs(mid))
                cout << "WARNING!!! strange decay pattern" << endl;
            pos_mid = abs(mid);
        }
    }

    if(neg_mid + pos_mid == 1000006+1000006)
        return 0;
    else if(neg_mid + pos_mid == 1000006+1000024)
        return 1;
    else if(neg_mid + pos_mid == 1000024+1000024)
        return 2;
    else
        return 3;
}

bool isT2bt(){
   const int pdg_stop1 = 1000006;
   const int pdg_stop2 = 2000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_2neutral = 1000023;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_chi_3neutral = 1000025;
   const int pdg_chi_4neutral = 1000035;
   const int pdg_chi_2plus1 = 1000037;

  int T2tt = 0;
  int T2bW = 0;

    for(unsigned int i=0; i<gensusy_motherid().size() ; i++){
      if(gensusy_isLastCopy().at(i) ==1 && abs(gensusy_id().at(i)) == pdg_chi_1neutral && abs(gensusy_motherid().at(i)) == pdg_stop1){
    //     cout<<"T2tt status"<<gensusy_status().at(i)<<endl;
         T2tt++;
      } //else cout<<"T2bW status"<<gensusy_status().at(i)<<"  "<<abs(gensusy_id().at(i))<<"  "<<abs(gensusy_motherid().at(i))<<endl;
//      if(gensusy_isLastCopy().at(i) == 1 && abs(gensusy_id().at(i)) == pdg_chi_1neutral &&  abs(gensusy_motherid().at(i)) == pdg_chi_1plus1){
      if(gensusy_isLastCopy().at(i) && abs(gensusy_id().at(i)) == pdg_chi_1plus1){
      //   cout<<"T2bW status"<<abs(gensusy_motherid().at(i))<<endl;
         T2bW++;
      }
    }
    //if(T2bW==2) cout<<"T2tt "<<T2tt<<" T2bW "<<T2bW<<endl;
    if(T2tt==1 && T2bW==1) return true;
    else return false;
}

bool isT2tt(){
   const int pdg_stop1 = 1000006;
   const int pdg_stop2 = 2000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_2neutral = 1000023;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_chi_3neutral = 1000025;
   const int pdg_chi_4neutral = 1000035;
   const int pdg_chi_2plus1 = 1000037;

  int T2tt = 0;
  int T2bW = 0;

    for(unsigned int i=0; i<gensusy_motherid().size() ; i++){
      if(gensusy_status().at(i) ==1 && abs(gensusy_id().at(i)) == pdg_chi_1neutral && abs(gensusy_motherid().at(i)) == pdg_stop1) T2tt++;
    }
    if(T2tt==2) return true;
    return false;
}

bool isT2bW(){
   const int pdg_stop1 = 1000006;
   const int pdg_stop2 = 2000006;
   const int pdg_chi_1neutral = 1000022;
   const int pdg_chi_2neutral = 1000023;
   const int pdg_chi_1plus1 = 1000024;
   const int pdg_chi_3neutral = 1000025;
   const int pdg_chi_4neutral = 1000035;
   const int pdg_chi_2plus1 = 1000037;

  int T2tt = 0;
  int T2bW = 0;

    for(unsigned int i=0; i<gensusy_motherid().size() ; i++){
      if(gensusy_status().at(i) == 1 && abs(gensusy_id().at(i)) == pdg_chi_1neutral &&  abs(gensusy_motherid().at(i)) == pdg_chi_1plus1) T2bW++;
    }
    if(T2bW==2) return true;
    return false;
}

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2)
  {
        return v1.second.pt() > v2.second.pt();
  }
};

float CDF_PZeta(float MET, float MET_Phi, LorentzVector p4_1, LorentzVector p4_2){
  double zeta_x = TMath::Cos(p4_1.phi()) + TMath::Cos(p4_2.phi());
  double zeta_y = TMath::Sin(p4_1.phi()) + TMath::Sin(p4_2.phi());
  double zeta_R = TMath::Sqrt(zeta_x*zeta_x + zeta_y*zeta_y);
  if ( zeta_R > 0. ) { 
    zeta_x /= zeta_R; 
    zeta_y /= zeta_R; 
  }
  
  double px = (p4_1.Px() + p4_2.Px()) + MET*TMath::Cos(MET_Phi);
  double py = (p4_1.Py() + p4_2.Py()) + MET*TMath::Sin(MET_Phi);

  return zeta_x*px + zeta_y*py;
}

float CDF_PZetaVis(LorentzVector p4_1, LorentzVector p4_2){
  double zeta_x = TMath::Cos(p4_1.phi()) + TMath::Cos(p4_2.phi());
  double zeta_y = TMath::Sin(p4_1.phi()) + TMath::Sin(p4_2.phi());
  double zeta_R = TMath::Sqrt(zeta_x*zeta_x + zeta_y*zeta_y);
  if ( zeta_R > 0. ) { 
     zeta_x /= zeta_R; 
     zeta_y /= zeta_R; 
  }

  double px_vis = (p4_1.Px() + p4_2.Px());
  double py_vis = (p4_1.Py() + p4_2.Py()) ;

  return zeta_x*px_vis + zeta_y*py_vis;

}

float DPhi_W_lep(float MET, float MET_Phi, LorentzVector p4){
  const TVector3 lep(p4.x(), p4.y(), p4.z());
  const TVector3 met(MET*cos(MET_Phi),MET*sin(MET_Phi),0);
  const TVector3 w = lep+met;
  double dphi = fabs(w.DeltaPhi(lep));
  return dphi;
}

float WpT(float MET, float MET_Phi, LorentzVector p4){
  const TVector3 lep(p4.x(), p4.y(), p4.z());
  const TVector3 met(MET*cos(MET_Phi),MET*sin(MET_Phi),0);
  const TVector3 w = lep+met;
  double wpt = w.Pt();
  return wpt;
}

bool EMFracVeto(){
  int n_ooavetojets;
/*  for(unsigned int iJet=0; iJet< OutOfAccak4pfjets_p4().size(); iJet++){
     if(OutOfAccak4pfjets_p4().at(iJet).eta()< 2.4 || OutOfAccak4pfjets_p4().at(iJet).eta()>5.) continue;
     if(!OutOfAccak4pfjets_loose_pfid().at(iJet)) continue;
     if(OutOfAccak4pfjets_nef().at(iJet)/OutOfAccak4pfjets_p4().at(iJet).E() + OutOfAccak4pfjets_cef().at(iJet)/OutOfAccak4pfjets_p4().at(iJet).E()  > 0.9) continue;
     n_ooavetojets++;
  }*/
  if(n_ooavetojets<1) return true;
  else return false;
}

/*bool passtrackveto(){
   int chargedtracks = 0;
       for (unsigned int idx = 0; idx < isoTracks_p4().size(); idx++){
             if(ROOT::Math::VectorUtil::DeltaR(isoTracks_p4().at(idx), lep1_p4()) < 0.4) continue;
             if(fabs(isoTracks_dz().at(idx)) > 0.1) continue;
             if(abs(isoTracks_pdgId().at(idx))!=11 && abs(isoTracks_pdgId().at(idx))!=13){
                if(isoTracks_p4().at(idx).pt() < 10.) continue;
                if(isoTracks_absIso().at(idx)/isoTracks_p4().at(idx).pt() >0.1) continue;
                if(isoTracks_charge().at(idx) * lep1_charge() > 0) continue;
             }else{
                if(isoTracks_p4().at(idx).pt() < 5.) continue;
                if(isoTracks_absIso().at(idx)/isoTracks_p4().at(idx).pt() >0.2) continue;
             }
             chargedtracks++;
      }
      if(chargedtracks<1) return true;
      else return false;
}*/


vector<pair <int, LorentzVector>> sort_pt( vector<LorentzVector> p4_, float pt_, float DRmin_lep1obj){
  vector<pair <int, LorentzVector>> sorted_;
  for(unsigned int iObj=0; iObj<p4_.size(); iObj++){
   if(p4_.at(iObj).pt()<pt_) continue;
   if(ROOT::Math::VectorUtil::DeltaR(p4_.at(iObj), lep1_p4()) < DRmin_lep1obj) continue;
   sorted_.push_back(make_pair(iObj,p4_.at(iObj)));
  }
  sort(sorted_.begin(),sorted_.end(),sortbypt());
  return sorted_;
}

LorentzVector leadingGoodJetp4(){
      vector<pair <int, LorentzVector>> sorted_;
        int overlep;
           overlep= 0;//getOverlappingJetIndex(lep1_p4(), ak4pfjets_p4(), 0.4);
for (int ijet = 0; ijet < ak4pfjets_p4().size(); ijet++) { 
      if (ijet == overlep) continue;
      // if(fabs(ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(ijet), lep1_p4()))< 0.4) continue;
       if(!ak4pfjets_loose_pfid().at(ijet)) continue;
       if(fabs(ak4pfjets_p4().at(ijet).pt())<30.) continue;
       if(fabs(ak4pfjets_p4().at(ijet).eta()) > 2.4) continue;
       sorted_.push_back(make_pair(ijet,ak4pfjets_p4().at(ijet)));
      }
  sort(sorted_.begin(),sorted_.end(),sortbypt());
  return sorted_.at(0).second;

}
/*
bool passtrackveto_custom(float conedR, float leppT_thresh, float hadpT_thresh, float isocandpT, float lepisocut, float hadisocut){
   int chargedtracks = 0;
       for (unsigned int idx = 0; idx < isoTracks_p4().size(); idx++){
             if(ROOT::Math::VectorUtil::DeltaR(isoTracks_p4().at(idx), lep1_p4()) < 0.4) continue;
             if(fabs(isoTracks_dz().at(idx)) > 0.1) continue;
             if(abs(isoTracks_pdgId().at(idx))!=11 && abs(isoTracks_pdgId().at(idx))!=13){
                if(isoTracks_p4().at(idx).pt() < hadpT_thresh) continue;
                if(trackIso(idx, conedR, 0.1, isocandpT)/isoTracks_p4().at(idx).pt() >hadisocut) continue;
                if(isoTracks_charge().at(idx) * lep1_charge() > 0) continue;
             }else{
                if(isoTracks_p4().at(idx).pt() < leppT_thresh) continue;
                if(isoTracks_absIso().at(idx)/isoTracks_p4().at(idx).pt() >lepisocut) continue;
             }
             chargedtracks++;
      }
      if(chargedtracks<1) return true;
      else return false;
}

float trackIso(int thisPf, float coneR, float deltaZCut, float pT){

  float absIso = 0.0;

  for (int ipf = 0; ipf < isoTracks_p4().size(); ipf++) {

    if( ipf == thisPf ) continue; // skip this PFCandidate
    if(isoTracks_p4().at(ipf).pt()<pT) continue;
    double dr=ROOT::Math::VectorUtil::DeltaR( isoTracks_p4().at(ipf) , isoTracks_p4().at(thisPf) );
    if( dr > coneR ) continue; // skip pfcands outside the cone                                     
    if( isoTracks_p4().at(ipf).pt()>=0.0 && fabs(isoTracks_dz().at(ipf)) <= deltaZCut) absIso += isoTracks_p4().at(ipf).pt();

  }
  return absIso;
}
*/
double calculateZbi(double signal=1.1, double bkg=5.5, double unc=0.3){
  double n_on = signal+bkg;
  double mu_b_hat=bkg;
  double sigma_b=unc*bkg;
  double tau = mu_b_hat/(sigma_b*sigma_b);
  double n_off = tau*mu_b_hat;
  double P_Bi = TMath::BetaIncomplete(1./(1.+tau),n_on,n_off+1);
  double Z_Bi = sqrt(2)*TMath::ErfInverse(1 - 2*P_Bi);
  return Z_Bi;
  //  std::cout<<"The calculated Zbi for a signal of "<<signal<<" events and background of "<<bkg<<" events with a systematic uncertainty of "<<unc*100<<"% is "<<Z_Bi<<std::endl;                                                           
}

/*
CNumBase<float> calculateZbi(CNumBase<float> signal, CNumBase<float> bkg, double unc){
  CNumBase<float> n_on = CNumBase<float>(signal+bkg);
  CNumBase<float> mu_b_hat = CNumBase<float>(bkg);
  CNumBase<float> sigma_b = CNumBase<float>(unc*bkg);
  CNumBase<float> tau = CNumBase<float>(mu_b_hat/(sigma_b*sigma_b));
  CNumBase<float> n_off = CNumBase<float>(tau*mu_b_hat);
  CNumBase<float> P_Bi = CNumBase<float>(TMath::BetaIncomplete(1./(1.+tau),n_on,n_off+1));
  CNumBase<float> Z_Bi = CNumBase<float>(sqrt(2)*TMath::ErfInverse(1 - 2*P_Bi));
  return Z_Bi;
}
*/
int GetNGoodJets(){
  int njets =0;
        int overlep;
           overlep=0; getOverlappingJetIndex(lep1_p4(), ak4pfjets_p4(), 0.4);

  for (int ijet = 0; ijet < ak4pfjets_p4().size(); ijet++) {
     if (ijet == overlep) continue;
    // if(fabs(ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(ijet), lep1_p4()))< 0.4) continue;
     if(!ak4pfjets_loose_pfid().at(ijet)) continue;
     if(fabs(ak4pfjets_p4().at(ijet).pt())<30.) continue;
     if(fabs(ak4pfjets_p4().at(ijet).eta()) > 2.4) continue;
     njets++; // && ak4pfjets_p4().at(ijet).pt()>30. && ak4pfjets_loose_puid().at(ijet) > 0) njets++; 
  }
  return njets;
}

int GetATLASGoodJets(){
  int jetpt70=0;
  int jetpt60=0;
  int jetpt55=0;
  int jetpt25=0;
  int njets=0;

     if(fabs(ak4pfjets_p4().at(0).pt())>70.) jetpt70++;
     if(fabs(ak4pfjets_p4().at(1).pt())>60.) jetpt60++;
     if(fabs(ak4pfjets_p4().at(2).pt())>55.) jetpt55++;
     if(fabs(ak4pfjets_p4().at(3).pt())>25.) jetpt25++;
//  if(jetpt60<1 || jetpt70<1 || jetpt55<1 || jetpt25<1) njets =0;
  //else 
  njets = jetpt70 + jetpt60 + jetpt55 +jetpt25;
  return njets;
}

int GetATLASGoodJets2(){
  int jetpt60=0;
  int jetpt40=0;
  int jetpt25=0;
  int njets=0;

     if(fabs(ak4pfjets_p4().at(0).pt())>60.) jetpt60++;
     if(fabs(ak4pfjets_p4().at(1).pt())>60.) jetpt60++;
     if(fabs(ak4pfjets_p4().at(2).pt())>40.) jetpt40++;
     if(fabs(ak4pfjets_p4().at(3).pt())>25.) jetpt25++;
 // if(jetpt60<2 || jetpt40<1 || jetpt25<1) njets =0;
//  else 
  njets = jetpt60 + jetpt40 +jetpt25;
  return njets;
}

int GetATLASGoodJets3(){
  int jetpt60=0;
  int jetpt40=0;
  int jetpt25=0;
  int njets=0;

     if(fabs(ak4pfjets_p4().at(0).pt())>80.) jetpt60++;
     if(fabs(ak4pfjets_p4().at(1).pt())>50.) jetpt60++;
     if(fabs(ak4pfjets_p4().at(2).pt())>40.) jetpt40++;
     if(fabs(ak4pfjets_p4().at(3).pt())>40.) jetpt25++;
 // if(jetpt60<2 || jetpt40<1 || jetpt25<1) njets =0;
  //else 
  njets = jetpt60 + jetpt40 +jetpt25;
  return njets;
}

int GetNGoodBJets(){
  int njets =0;
  //      int overlep;
    //       overlep=0;// getOverlappingJetIndex(lep1_p4(), ak4pfjets_p4(), 0.4);
  for (int ijet = 0; ijet < ak4pfjets_p4().size(); ijet++) {
    // if(fabs(ROOT::Math::VectorUtil::DeltaR(ak4pfjets_p4().at(ijet), lep1_p4()))< 0.4) continue;
 //    if (ijet == overlep) continue;
 //    if(!ak4pfjets_loose_pfid().at(ijet)) continue;
//     if(!ak4pfjets_passMEDbtag().at(ijet)) continue;
     if(ak4pfjets_CSV().at(ijet) < 0.46) continue;
//     if(fabs(ak4pfjets_p4().at(ijet).pt())<30.) continue;
  //   if(fabs(ak4pfjets_p4().at(ijet).eta()) > 2.4) continue;
    njets++; // && ak4pfjets_p4().at(ijet).pt()>30. && ak4pfjets_loose_puid().at(ijet) > 0) njets++; 
  }
  return njets;
}

int HFJets(){
  int hfjets=0;
  for (int ijet = 0; ijet < ak4pfjets_p4().size(); ijet++) {
     if(fabs(ak4pfjets_p4().at(ijet).pt())<30.) continue;
     if(fabs(ak4pfjets_p4().at(ijet).eta()) <3.0) continue;
     hfjets++;
  }
  return hfjets;
}

float dRbetweenVectors(LorentzVector& vec1,LorentzVector& vec2 ){
  float dphi = std::min(::fabs(vec1.Phi() - vec2.Phi()), 2 * M_PI - fabs(vec1.Phi() - vec2.Phi()));
  float deta = vec1.Eta() - vec2.Eta();

  return sqrt(dphi*dphi + deta*deta);
}

float calculateMt(const LorentzVector p4, double met, double met_phi){
  float phi1 = p4.Phi();
  float phi2 = met_phi;
  float Et1  = p4.Et();
  float Et2  = met;

  return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
}

float getMinDphi(float metPhi, LorentzVector vec1, LorentzVector vec2,LorentzVector vec3, LorentzVector vec4) {
  float dphimj1_    = getdphi(metPhi, vec1.phi() );
  float dphimj2_    = getdphi(metPhi, vec2.phi() );
  float dphimj3_    = getdphi(metPhi, vec3.phi() );
  float dphimj4_    = getdphi(metPhi, vec4.phi() );
  float dphimjmin_12  = TMath::Min( dphimj1_ , dphimj2_ );
  float dphimjmin_34 = TMath::Min( dphimj3_ , dphimj4_ );
  float dphimjmin_  = TMath::Min( dphimjmin_12 , dphimjmin_34 );
  return dphimjmin_;

}

float getdphi( float phi1 , float phi2 ){
  float dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = TMath::TwoPi() - dphi;
  return dphi;
}

double getBinomialUncertainty (double num, double den)
{
   double eff = num/den;
   double unc = sqrt( eff * (1-eff) / den);
   return unc;
}

double getSigUncertainty (double sig, double bg, double sigmabg)
{
   double bprime = bg + (bg*sigmabg)*(bg*sigmabg);
   double sigma_bprime = sqrt(bg) + 2*(bg*sigmabg)*(sigmabg*sqrt(bg));
   double f1 = sqrt(sig)/sig;
   double f2 = (0.5*sigma_bprime)/bprime;
   double f3 = (sqrt(sig)*sigma_bprime)/(sig*bprime);
   double unc = getSignificance_SoverSqrtB(1,sig,bg,sigmabg) * sqrt(f1*f1 + f2*f2 - f3);
   if(bg==0) return 0.;
   return unc;
}

double getSignificance_SoverSqrtB(int type, double signal, double background, double bkg_unc){
  double sig;
  if(type == 0) sig = signal / sqrt(background) ;
  if(type == 1) sig = signal / sqrt(background + (bkg_unc*background)*(bkg_unc*background));
  if(background ==0) return 0.;
  return sig;
}

/*bool passMockMuTrigger(){
  if (fabs(lep1_p4().eta()) <= 1.479){
    if(lep1_chiso()/lep1_p4().pt() > 0.09) return false;
    if(lep1_nhiso()/lep1_p4().pt() > 0.21) return false;
    if(lep1_emiso()/lep1_p4().pt() > 0.11) return false;
  }else if((fabs(lep1_p4().eta()) > 1.479) && (fabs(lep1_p4().eta()) < 2.5)){
    if(lep1_chiso()/lep1_p4().pt() > 0.09) return false;
    if(lep1_nhiso()/lep1_p4().pt() > 0.22) return false;
    if(lep1_emiso()/lep1_p4().pt() > 0.08) return false;
  }else return false;
  return true;
}

bool passMockElTrigger(){
  if (fabs(lep1_etaSC()) <= 1.479){
    if (lep1_sigmaIEtaEta_fill5x5() >= 0.011) return false;
    if (lep1_ooEmooP() >= 0.012) return false;
    if (lep1_hOverE() >= 0.06) return false;
    if (fabs(lep1_dEtaIn()) >= 0.004) return false;
    if (fabs(lep1_dPhiIn()) >= 0.02) return false;
    if(lep1_chiso()/lep1_p4().pt() > 0.08) return false;
    if(lep1_nhiso()/lep1_p4().pt() > 0.15) return false;
    if(lep1_emiso()/lep1_p4().pt() > 0.15) return false;
  }
  else if((fabs(lep1_etaSC()) > 1.479) && (fabs(lep1_etaSC()) < 2.5)){
    if (lep1_sigmaIEtaEta_fill5x5() >= 0.032) return false;
    if (lep1_ooEmooP() >= 0.065) return false;
    if (lep1_hOverE() >= 0.065) return false;
    if (fabs(lep1_dEtaIn()) >= 0.007) return false;
    if (fabs(lep1_dPhiIn()) >= 0.02) return false;
    if(lep1_chiso()/lep1_p4().pt() > 0.08) return false;
    if(lep1_nhiso()/lep1_p4().pt() > 0.16) return false;
    if(lep1_emiso()/lep1_p4().pt() > 0.15) return false;
    if(lep1_expectedMissingInnerHits()>2) return false;
    if(lep1_ChiSqr()>=2.8) return false;
  }
  else return false;
  return true;
}
*/
int getOverlappingJetIndex(LorentzVector lep_, vector<LorentzVector> jets_, double dR){
  float DR_lep_jet1 = 0.;
  float DR_lep_jet2 = 0.;
  int closestjet_idx = 0;

  if(jets_.size()==0) return -999;

        for(unsigned int iJet=1; iJet<jets_.size(); iJet++){
          DR_lep_jet1 = ROOT::Math::VectorUtil::DeltaR(jets_.at(closestjet_idx), lep_);
          DR_lep_jet2 = ROOT::Math::VectorUtil::DeltaR(jets_.at(iJet), lep_);
          if(DR_lep_jet1 > DR_lep_jet2) closestjet_idx = iJet;
        }


        if(ROOT::Math::VectorUtil::DeltaR(jets_.at(closestjet_idx), lep_) > dR){
       //   cout<<"No overlapping jet found"<<endl;
          return -9999;
        }else return closestjet_idx;
}

bool isbadEcalEvent(){

  if(run()==251251 && ls()==70 && evt()==42778380) return true;
  if(run()==251244 && ls()==213 && evt()==122972241) return true;
  if(run()==251561 && ls()==71 && evt()==63948430) return true;
  if(run()==251251 && ls()==64 && evt()==39089589) return true;
  if(run()==251561 && ls()==54 &&evt()==47865098) return true;
  if(run()==251562){
    if(ls() == 107 && evt() ==97817286) return true;
    if(ls() == 520 && evt() ==457785193) return true;
    if(ls() == 160 && evt() ==145319957) return true;
    if(ls() == 70 && evt() ==63977928) return true;
    if(ls() == 285 && evt() ==256157943) return true;
    if(ls() == 284 && evt() ==255147436) return true;
  }else if(run()==251643){
    if(ls() == 44 && evt() == 46151562) return true;
    if(ls() == 509 && evt() == 532770934) return true;
    if(ls() == 167 && evt() == 180185712) return true;
    if(ls() == 490 && evt() == 513915800) return true;
    if(ls() == 394 && evt() == 416725747) return true;
    if(ls() == 150 && evt() == 161351770) return true;
  }else return false; 
}

LorentzVector getMHT(vector<LorentzVector> jets_,float pt, float eta){

LorentzVector MHT = LorentzVector(0,0,0,0);
if(jets_.size()==0) return LorentzVector(0,0,0,0);
int overlep=0;// getOverlappingJetIndex(lep1_p4(), ak4pfjets_p4(), 0.4);
    for(unsigned int iJet=0; iJet<jets_.size(); iJet++){
      if(iJet==overlep) continue;
      if(jets_.at(iJet).pt()<pt) continue;
      if(jets_.at(iJet).eta()>eta) continue;
       MHT -= jets_.at(iJet);
    }
    MHT-=lep1_p4();
    return MHT; 

}

float getMHTSig(){
  float MHTsig = 0;
  LorentzVector MHT = LorentzVector(0,0,0,0);
  for(unsigned int iJet=0; iJet<ak4pfjets_p4().size(); iJet++){
    MHT -= ak4pfjets_p4().at(iJet);
  }
  MHT-=lep1_p4();
  
//  if(MHT.pt()<5) return 0.;
  MHTsig = (MHT.pt() - 100.)/sqrt(ak4_HT());
  if(MHTsig<0) MHTsig=0;
  return MHTsig;

}

pair<float,float> newmet(){
  //float metx = nupfmet_trk_pt()*cos(nupfmet_trk_phi()) + chpfmet_trk_pt()*cos(chpfmet_trk_phi());
  //float mety = nupfmet_trk_pt()*sin(nupfmet_trk_phi()) + chpfmet_trk_pt()*sin(chpfmet_trk_phi());
  //float metx = chphpfmet_trk_pt()*cos(chphpfmet_trk_phi());
 // float mety = chphpfmet_trk_pt()*sin(chphpfmet_trk_phi());
  float metx=0;
  float mety = 0;
  const TVector3 newmet(metx,mety,0);
  pair<float,float> met = make_pair(newmet.Mag(), newmet.Phi());
  return met;
}

bool PassATLAStauveto(){
  bool passtauveto = true;
  ComputeMT2* mycalc;
  const TVector2 EtMissVec(pfmet()*cos(pfmet_phi()),pfmet()*sin(pfmet_phi()));

  LorentzVector b2 = lep1_p4();
  TLorentzVector b2v;
  b2v.SetPtEtaPhiE(b2.pt(), b2.eta(), b2.phi(), b2.E());

  for(unsigned int tau = 0; tau < tau_p4().size() ; tau++){
    if(!tau_isVetoTau().at(tau)) continue;
    LorentzVector b1 = tau_p4().at(tau);
    TLorentzVector b1v;
    b1v.SetPtEtaPhiE(b1.pt(), b1.eta(), b1.phi(), b1.E());
    mycalc = new ComputeMT2(b1v,b2v,EtMissVec,0.,0.);
    double tmp1 = mycalc->Compute();
    //if(tmp1 < 80.)  cout<<"mt2_tau = "<<tmp1<<" < 80."<<endl;
    if(tmp1 < 80.) passtauveto = false;
  }
  
  return passtauveto;
}

float getamt2(LorentzVector b1, LorentzVector b2, LorentzVector lep,float met, float metphi){

  ComputeMT2* mycalc;
  const TVector2 EtMissVec(met*cos(metphi),met*sin(metphi));

  TLorentzVector b1v;
  b1v.SetPtEtaPhiE(b1.pt(), b1.eta(), b1.phi(), b1.E());
  TLorentzVector b2v;
  b2v.SetPtEtaPhiE(b2.pt(), b2.eta(), b2.phi(), b2.E()); 
  TLorentzVector lepton;
  lepton.SetPtEtaPhiE(lep.pt(), lep.eta(), lep.phi(), lep.E());
 
  TLorentzVector lepb1 = b1v + lepton;
  TLorentzVector lepb2 = b2v + lepton;
  float amt2=0;
      mycalc = new ComputeMT2(lepb1,b2v,EtMissVec,0,80.4);
      double tmp1 = mycalc->Compute();
      mycalc = new ComputeMT2(lepb2,b1v,EtMissVec,0,80.4);
      double tmp2 = mycalc->Compute();
      amt2 = min(tmp1,tmp2);
      delete mycalc;
  return amt2;
 
}

vector<int> JetIndexCSVsorted(vector<float> btagvalues, vector<LorentzVector > jets){

    vector<int> b;
    if(btagvalues.size()!=jets.size()) return b;
    vector<int>::iterator it;
    for(unsigned int n = 0; n<jets.size(); ++n){
      it = b.begin(); bool inloop = false;
      for(unsigned int k = 0; k<b.size();++k){
        if(btagvalues.at(n)>btagvalues.at(b.at(k)) ) { b.insert(it+k,n); inloop = true; break;}
      }
      if(inloop==false) b.push_back(n);
    }
    return b;
}

float getTTbarSysPtSF(string process){
  float weight_ttbarSysPt    = 1.0;
  double sf_val = 1.0;
  double sf_err = 0.0;

  if( is_data() ) return weight_ttbarSysPt;

  std::string filestr2 (process);
  if(filestr2.find("ttbar") == string::npos && filestr2.find("tW") == string::npos && filestr2.find("tbarW") == string::npos) return weight_ttbarSysPt;

  if( !is2lep() ) return weight_ttbarSysPt;


  // Get ttbar/tW system pT
  LorentzVector system_LV(0.0,0.0,0.0,0.0);

  // Grab top quarks
  for(int iGen=0; iGen<(int)genqs_p4().size(); iGen++){
    if( abs(genqs_id().at(iGen))==6 &&
	genqs_isLastCopy().at(iGen) ){
      system_LV += genqs_p4().at(iGen);
    }
  }

  // If tW grab the W
  if(filestr2.find("tW") != string::npos || filestr2.find("tbarW") != string::npos){
    for(int iGen=0; iGen<(int)genbosons_p4().size(); iGen++){
      if( abs(genbosons_id().at(iGen))==24 &&
	  genbosons_isHardProcess().at(iGen) &&
	  genbosons_isLastCopy().at(iGen) ){
	system_LV += genbosons_p4().at(iGen);
      }
    }
  }
   
  double system_pt = system_LV.Pt();
//if(system_pt>=100.0 ) cout<<"should not be 1."<<endl;
//cout<<system_pt<<endl;
  // Get Scale Factor
  if( system_pt>=100.0 && system_pt<150.0 ){
    sf_val = 1.02;
    sf_err = 0.02;
  }

  if( system_pt>=150.0 && system_pt<200.0 ){
    sf_val = 0.98;
    sf_err = 0.02;
  }

  if( system_pt>=200.0 && system_pt<250.0 ){
    sf_val = 0.99;
    sf_err = 0.03;
  }

  if( system_pt>=250.0 && system_pt<350.0 ){
    sf_val = 0.97;
    sf_err = 0.03;
  }

  if( system_pt>=350.0 && system_pt<450.0 ){
    sf_val = 0.98;
    sf_err = 0.05;
  }

  if( system_pt>=450.0 ){
    sf_val = 1.08;
    sf_err = 0.07;
  }


  // true=sf, false=uncertainty only

  weight_ttbarSysPt    = sf_val;

  return weight_ttbarSysPt;
}
