#include "Analysis/MVALikelihood/interface/MVALikelihood.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
int main(int argc, char * argv[]) {

  float ptRatio;
  float dcaSig;
  float dPhiMuMet;
  float diMuEta;

  // Creating RooT file for storage of histograms
  TFile * file = new TFile("MVALikelihood.root","recreate");
  file->cd("");

  // histograms
  
  // Z->TauTau sample
  TH1F * diMuPtRatioZTauTauH = new TH1F("diMuPtRatioZTauTauH","",25,0.,1.); // dimuon pt - to scalar sum of muons' pt ratio 
  TH1F * dcaSigZTauTauH = new TH1F("dcaSigZTauTauH","",25,-3,2);
  TH1F * dPhiMuMetZTauTauH = new TH1F("dPhiLepMetZTauTauH","",25,0.,TMath::Pi());
  TH1F * diMuEtaZTauTauH = new TH1F("diMuEtaZTauTauH","",30,-6,6);
  TH1F * likelihoodZTauTauH = new TH1F("likelihoodZTauTauH","",20,0,1);
  
  // Z->MuMu sample
  TH1F * diMuPtRatioZMuMuH = new TH1F("diMuPtRatioZMuMuH","",25,0.,1.); // dimuon pt - to scalar sum of muons' pt ratio 
  TH1F * dcaSigZMuMuH = new TH1F("dcaSigZMuMuH","",25,-3,2);
  TH1F * dPhiMuMetZMuMuH = new TH1F("dPhiLepMetZMuMuH","",25,0.,TMath::Pi());
  TH1F * diMuEtaZMuMuH = new TH1F("diMuEtaZMuMuH","",30,-6,6);
  TH1F * likelihoodZMuMuH = new TH1F("likelihoodZMuMuH","",20,0,1);

  // Initialization of the MVA 
  StringVector classNames;
  classNames.clear();
  classNames.push_back("ZToTauTau");
  classNames.push_back("ZToMuMu");
  
  StringVector variableNames;
  variableNames.clear();
  variableNames.push_back("ptRatio");
  variableNames.push_back("dcaSig");
  variableNames.push_back("diLepEta");
  variableNames.push_back("dPhiPos");
  
  MVALikelihood * mvaLikelihood = new MVALikelihood(classNames,variableNames);


  TFile * fileZTauTau = new TFile("ZToTauTau_Like.root");
  if (fileZTauTau->IsZombie()) {
    std::cout << "File with name ZToTauTau_Like.root does not exist" << std::endl;
    std::cout << "Terminating program" << std::endl;
    exit(-1);
  }
  TTree * tree = (TTree*)fileZTauTau->Get("likeTree");

  tree->SetBranchAddress("DiLepEta",&diMuEta);
  tree->SetBranchAddress("PosMETDPhi",&dPhiMuMet);
  tree->SetBranchAddress("MuonDCASig",&dcaSig);
  tree->SetBranchAddress("DiMuonPtRatio",&ptRatio);

  int nEvt = tree->GetEntries();
  for (int iEvt=0;iEvt<nEvt;++iEvt) {

    tree->GetEntry(iEvt);

    StringDoubleMap variables;
    variables[std::string("ptRatio")] = ptRatio;
    variables[std::string("dcaSig")]  = dcaSig;
    variables[std::string("diLepEta")] = diMuEta;
    variables[std::string("dPhiPos")] = dPhiMuMet;
    
    float likelihood = float(mvaLikelihood->getLikelihood(variables,"ZToTauTau"));

    diMuPtRatioZTauTauH->Fill(ptRatio);
    dcaSigZTauTauH->Fill(dcaSig);
    dPhiMuMetZTauTauH->Fill(dPhiMuMet);
    diMuEtaZTauTauH->Fill(diMuEta);
    likelihoodZTauTauH->Fill(likelihood);    

  }

  TFile * fileZMuMu = new TFile("ZToMuMu_Like.root");
  if (fileZMuMu->IsZombie()) {
    std::cout << "File with name ZToMuMu_Like.root does not exist" << std::endl;
    std::cout << "Terminating program" << std::endl;
    exit(-1);
  }
  tree = (TTree*)fileZMuMu->Get("likeTree");

  tree->SetBranchAddress("DiLepEta",&diMuEta);
  tree->SetBranchAddress("PosMETDPhi",&dPhiMuMet);
  tree->SetBranchAddress("MuonDCASig",&dcaSig);
  tree->SetBranchAddress("DiMuonPtRatio",&ptRatio);

  nEvt = tree->GetEntries();
  for (int iEvt=0;iEvt<nEvt;++iEvt) {

    tree->GetEntry(iEvt);

    StringDoubleMap variables;
    variables[std::string("ptRatio")] = ptRatio;
    variables[std::string("dcaSig")]  = dcaSig;
    variables[std::string("diLepEta")] = diMuEta;
    variables[std::string("dPhiPos")] = dPhiMuMet;
    
    float likelihood = float(mvaLikelihood->getLikelihood(variables,"ZToTauTau"));

    diMuPtRatioZMuMuH->Fill(ptRatio);
    dcaSigZMuMuH->Fill(dcaSig);
    dPhiMuMetZMuMuH->Fill(dPhiMuMet);
    diMuEtaZMuMuH->Fill(diMuEta);
    likelihoodZMuMuH->Fill(likelihood);    

  }

  file->cd("");
  file->Write();
  file->Close();
  delete file;
  delete mvaLikelihood;
  delete fileZMuMu;
  delete fileZTauTau;

}
