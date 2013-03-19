#include "Analysis/MVALikelihood/interface/MVALikelihood.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"

int main(int argc, char * argv[]) {

    double pfmet;
    double ht;
    double dPhi;
    double metTopo;

    // Creating RooT file for storage of histograms
    TFile * file = new TFile("MVALikelihood.root", "recreate");
    file->cd("");

    // histograms

    // Wtaunu
    TH1F * PFMET_Sig = new TH1F("PFMET_Sig", "", 24, 0., 120.); // dimuon pt - to scalar sum of muons' pt ratio
    TH1F * RHT_Sig = new TH1F("RHT_Sig", "", 24, 0, 1.0);
    TH1F * deltaPhi_Sig = new TH1F("deltaPhi_Sig", "", 24, 0, 1.0);
    TH1F * metTopo_Sig = new TH1F("metTopo_Sig", "", 24, 0, 1.0);
    TH1F * likelihoodSignal = new TH1F("likelihoodSignal", "", 20, 0, 1);

    // BG Mainly Data
    TH1F * PFMET_BG = new TH1F("PFMET_BG", "", 24, 0., 120.); // dimuon pt - to scalar sum of muons' pt ratio
    TH1F * RHT_BG = new TH1F("RHT_BG", "", 24, 0, 1.0);
    TH1F * deltaPhi_BG = new TH1F("deltaPhi_BG", "", 24, 0, 1.0);
    TH1F * metTopo_BG = new TH1F("metTopo_BG", "", 24, 0, 1.0);
    TH1F * likelihoodBG = new TH1F("likelihoodBG", "", 20, 0, 1);

    // Initialization of the MVA
    StringVector classNames;
    classNames.clear();
    classNames.push_back("tau_Sig");
    classNames.push_back("tau_BG");

    StringVector variableNames;
    variableNames.clear();
    variableNames.push_back("pfmet");
    variableNames.push_back("ht");
    variableNames.push_back("dPhi");
    variableNames.push_back("metTopo");
    //  variableNames.push_back("dPhiPos");

    MVALikelihood * mvaLikelihood = new MVALikelihood(classNames, variableNames);


    TFile * fileZTauTau = new TFile("Signal.root");
    if (fileZTauTau->IsZombie()) {
        std::cout << "File with name ZToTauTau_Like.root does not exist" << std::endl;
        std::cout << "Terminating program" << std::endl;
        exit(-1);
    }
    TTree * tree = (TTree*) fileZTauTau->Get("mva_Tree");

    //  tree->SetBranchAddress("DiLepEta",&diMuEta);
    //  tree->SetBranchAddress("PosMETDPhi",&dPhiMuMet);
    tree->SetBranchAddress("T_RHT", &ht);
    tree->SetBranchAddress("T_MET", &pfmet);
    tree->SetBranchAddress("T_deltaPhi", &dPhi);
    tree->SetBranchAddress("T_MetTopologyPhi", &metTopo);

    int nEvt = tree->GetEntries();
    for (int iEvt = 0; iEvt < nEvt; ++iEvt) {

        tree->GetEntry(iEvt);

        StringDoubleMap variables;
        variables[std::string("pfmet")] = pfmet;
        variables[std::string("ht")] = ht;
        variables[std::string("dPhi")] = dPhi;
        variables[std::string("metTopo")] = metTopo;
        //    variables[std::string("diLepEta")] = diMuEta;
        //    variables[std::string("dPhiPos")] = dPhiMuMet;

        float likelihood = float(mvaLikelihood->getLikelihood(variables, "tau_Sig"));

        PFMET_Sig->Fill(pfmet);
        RHT_Sig->Fill(ht);
        deltaPhi_Sig->Fill(dPhi);
        metTopo_Sig->Fill(metTopo);
        //    dPhiMuMetZTauTauH->Fill(dPhiMuMet);
        //    diMuEtaZTauTauH->Fill(diMuEta);
        likelihoodSignal->Fill(likelihood);

    }

    TFile * fileZMuMu = new TFile("BG.root");
    if (fileZMuMu->IsZombie()) {
        std::cout << "File with name ZToMuMu_Like.root does not exist" << std::endl;
        std::cout << "Terminating program" << std::endl;
        exit(-1);
    }
    tree = (TTree*) fileZMuMu->Get("mva_Tree");

    //  tree->SetBranchAddress("DiLepEta",&diMuEta);
    //  tree->SetBranchAddress("PosMETDPhi",&dPhiMuMet);
    tree->SetBranchAddress("T_MET", &pfmet);
    tree->SetBranchAddress("T_RHT", &ht);
    tree->SetBranchAddress("T_deltaPhi", &dPhi);
    tree->SetBranchAddress("T_MetTopologyPhi", &metTopo);

    nEvt = tree->GetEntries();
    for (int iEvt = 0; iEvt < nEvt; ++iEvt) {

        tree->GetEntry(iEvt);

        StringDoubleMap variables;
        variables[std::string("pfmet")] = pfmet;
        variables[std::string("ht")] = ht;
        variables[std::string("dPhi")] = dPhi;
        variables[std::string("metTopo")] = metTopo;
        //    variables[std::string("diLepEta")] = diMuEta;
        //    variables[std::string("dPhiPos")] = dPhiMuMet;

        float likelihood = float(mvaLikelihood->getLikelihood(variables, "tau_Sig"));

        PFMET_BG->Fill(pfmet);
        RHT_BG->Fill(ht);
        deltaPhi_BG->Fill(dPhi);
        metTopo_BG->Fill(metTopo);
        //    dPhiMuMetZMuMuH->Fill(dPhiMuMet);
        //    diMuEtaZMuMuH->Fill(diMuEta);
        likelihoodBG->Fill(likelihood);

    }

    file->cd("");
    file->Write();
    file->Close();
    delete file;
    delete mvaLikelihood;
    delete fileZMuMu;
    delete fileZTauTau;

}
