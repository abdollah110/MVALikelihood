#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

void Plot_MVA() {


    TFile *data = new TFile("MVALikelihood.root");
//    TFile *wtaunu = new TFile("tau_Sig.root");
//    TFile *wmunu = new TFile("Wmunu.root");
//    TFile *wenu = new TFile("Wenu.root");
//    TFile *zjet = new TFile("ZJet.root");
//    TFile *qcd = new TFile("myQCD.root");

//    TH1D *Event_Data = (TH1D*) data->Get("IsoId_Cuts");
//    TH1D *Event_Wtaunu = (TH1D*) wtaunu->Get("IsoId_Cuts");
//    TH1D *Event_Wmunu = (TH1D*) wmunu->Get("eventCut");
//    TH1D *Event_Wenu = (TH1D*) wenu->Get("eventCut");
//    TH1D *Event_ZJet = (TH1D*) zjet->Get("eventCut");
//    TH1D *Event_QCD = (TH1D*) qcd->Get("eventCut");

    TH1F *Pt_Data = (TH1F*) data->Get("likelihoodSignal");
    TH1F *Pt_Wtaunu = (TH1F*) data->Get("likelihoodBG");
//    TH1D *Pt_Wmunu = (TH1D*) wmunu->Get("Pt");
//    TH1D *Pt_Wenu = (TH1D*) wenu->Get("Pt");
//    TH1D *Pt_ZJet = (TH1D*) zjet->Get("Pt");
//    TH1D *Pt_Wtaunu = (TH1D*) qcd->Get("pfmet_calomet");


//    TH2D *h1 = new TH2D("h2", "my histogram", 1000, 0, 100, 1000, 0, 100);
//    for (Int_t i = 0; i < 1000; i++) h1->Fill(0.1 * i, 0.1 * i);


//    double Int_Lumi = 12.0;
//
//    double XS_Data = 1;
//    double XS_Wtaunu = 9350;
//    double XS_Wmunu = 6938;
//    double XS_Wenu = 7284;
//    double XS_ZJet = 2400;
//    double XS_QCD = 29544580;


//
//    double w_a = XS_Data; //Data
//    double w_b = (XS_Wtaunu * Int_Lumi / Event_Wtaunu->GetBinContent(1)); //wtaunu
//    double w_c = (XS_Wmunu * Int_Lumi / Event_Wmunu->GetBinContent(1)); //wmunu
//    double w_d = (XS_Wenu * Int_Lumi / Event_Wenu->GetBinContent(1)); //wenu
//    double w_e = (XS_ZJet * Int_Lumi / Event_ZJet->GetBinContent(1)); //ZJet
//    double w_f = (XS_QCD * Int_Lumi / Event_QCD->GetBinContent(1)); //QCD_tauEnriched




    TCanvas *MyC = new TCanvas("MyC", "MyC", 1000, 500);
    //    Pt_Data->SetLineColor(1);
    //    Pt_Data->Scale(1.0);
    //    Pt_Data->Draw();

    //    Pt_QCD->SetLineColor(6);
    //    Pt_QCD->Scale(w_f);
    //    Pt_QCD->Draw("same");
    //
    Pt_Data->SetLineColor(1);
    Pt_Data->SetFillColor(1);
    Pt_Data->SetFillStyle(3);
    Pt_Data->SetMarkerColor(3);
    Pt_Data->SetMarkerSize(0.5);
    Pt_Data->DrawNormalized();
//    Pt_Wtaunu->SetXTitle("pfMET");
    Pt_Wtaunu->SetLineColor(4);
    Pt_Wtaunu->SetFillColor(4);
    Pt_Wtaunu->SetFillStyle(69);
    Pt_Wtaunu->SetMarkerColor(4);
    Pt_Wtaunu->SetMarkerSize(4.5);
    Pt_Wtaunu->DrawNormalized("same");
//    Pt_Wtaunu->SetYTitle("caloMET");



//
//    h1->SetLineColor(2);
//    h1->SetMarkerSize(1);
//    h1->SetMarkerStyle(6);
//    h1->SetMarkerColor(2);
    //    Pt_Wtaunu->Scale(w_b);
//    h1->Draw();
//    h1->Draw();
            //    Pt_ZJet->SetLineColor(5);
            //    Pt_ZJet->Scale(w_e);
            //    Pt_ZJet->Draw("same");
            //
            //
            //
            //    Pt_Wmunu->SetLineColor(3);
            //    Pt_Wmunu->Scale(w_c);
            //    Pt_Wmunu->Draw("same");
            //
            //    Pt_Wenu->SetLineColor(4);
            //    Pt_Wenu->Scale(w_d);
            //    Pt_Wenu->Draw("same");

            //    TLegend *l = new TLegend(0.85, 0.6, 0.95, 0.7);
            //
            //    l->AddEntry(Pt_QCD, "QCD ", "l");
            //    l->AddEntry(Pt_Wtaunu, " Wtaunu", "l");
            //    l->AddEntry(Pt_ZJet, "ZJet ", "l");
            //    l->AddEntry(Pt_Data, " Data", "l");
            //    l->AddEntry(Pt_Wenu, "Wenu ", "l");
            //    l->AddEntry(Pt_Wmunu, "Wmunu ", "l");
            //
            //    l->Draw();

        TLegend *l = new TLegend(0.8, 0.55, 0.95, 0.75);

    l->AddEntry(Pt_Wtaunu, " Wtaunu ", "lpf");
    l->AddEntry(Pt_Data, " Data ", "lpf");

    l->Draw();

}

