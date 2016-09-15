{

  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("t"); 
  ch->Add("/home/users/isuarez/stop/babies_16Feb2015/stop.root");
  ScanChain(ch); 
}