#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TFile.h"

void tau_fit() {

    TFile *fout = new TFile("tau.root", "recreate");

    TFile *tau = new TFile("taulike_tot.root"); // the .root file with the distributions

    TH1F *pfmet = (TH1F*) tau->Get("FailMET_DeNum");
    TH1F *ht = (TH1F*) tau->Get("ht");

    pfmet->Smooth(1000);
    TH1F fpfmet = new TF1("pfmet", "pol9", 20, 100);
    fpfmet->SetTitle("");
    pfmet->Fit(fpfmet, "");
    pfmet->Scale(1. / (fpfmet->Integral(20., 100.)));
    pfmet->Fit(fpfmet, "R");
    fout->WriteObject(fpfmet, "pfmet");



    ht->Smooth(100);
    TH1F fht = new TF1("ht", "pol19", 0.05, 0.95);
    fht->SetTitle("");
    ht->Fit(fht, "");
    ht->Scale(1. / (fht->Integral(0.05, 0.95)));
    ht->Fit(fht, "R");
    fout->WriteObject(fht, "ht");

    fout->Close();


}
