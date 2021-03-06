#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TFile.h"

void Fit_Sig() {

    TFile *tau = new TFile("Signal.root"); // the .root file with the distributions
    TFile *fout = new TFile("tau_Sig.root", "recreate");


    TH1F *pfmet = (TH1F*) tau->Get("After_HPSMedium_PFMET");
    pfmet->Smooth(100);
    TF1 * fpfmet = new TF1("pfmet", "gaus", 0, 120);
    fpfmet->SetTitle("");
    pfmet->Fit(fpfmet, "");
    pfmet->Scale(1. / (fpfmet->Integral(0., 120.)));
    pfmet->Fit(fpfmet, "R");
    fout->WriteObject(fpfmet, "pfmet");



//    TH1F *ht = (TH1F*) tau->Get("After_HPSMedium_HT");
//    ht->Smooth(100);
//    TF1 * fht = new TF1("ht", "gaus", 0.75, 1.1);
//    TF1 * fht2 = new TF1("ht2", "gaus", 0, 0.75);
//    TF1 * Total = new TF1("total_fit", "gaus(0) + gaus(3)", 0, 1.1);
//    Total->SetTitle("");
//    ht->Fit(fht, "R");
//    ht->Fit(fht2, "R+");
////    ht->Scale(1. / (fht->Integral(0.75, 1.1) + fht2->Integral(0.0, 0.75) ));
//    ht->Fit(Total, "R+");
//    fout->WriteObject(fht+fht2, "ht");


    TH1F *ht = (TH1F*) tau->Get("After_HPSMedium_HT");
    ht->Smooth(100);
    TF1* fht = new TF1("ht", "gaus", 0.1, 1.1);
    fht->SetTitle("");
    ht->Fit(fht, "");
    ht->Scale(1. / (fht->Integral(0.1, 1.1)));
    ht->Fit(fht, "R");
    fout->WriteObject(fht, "ht");

    fout->Close();


}
