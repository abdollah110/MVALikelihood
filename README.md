MVALikelihood
=============

Doing MVA analysis for ZHtautau analysis

First step to use the MVA analysis is to find some varaibles to discriminate signal from BG.

One need to check the correlation between these variablesm using TMVA package: 

https://twiki.cern.ch/twiki/bin/view/TMVA/WebHome#BuildTMVA

http://tmva.sourceforge.net/docu/TMVAUsersGuide.pdf

http://tmva.sourceforge.net/

After that one need to fit those distributions with a model (trail and error)

Next step is run the executables (fitted files and tree files are needed). The output would be the MVA output.


############################################################

To use the current MVA code one need to create a CMSSW, i.e:

cmsrel CMSSW_5_3_8 (or any other version)

cd CMSSW_5_3_8/src

mkdir Analysis

git clone https://github.com/abdollah110/MVALikelihood.git

cd Analysis/MVALikelihood

cmsenv (this create an executable MVALikelihood which is located in the bin directory)

to run it just run:   MVALikelihood


############################################################
############################################################
How TMVA works:

// --- Create the Reader object

    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
    
// Create a set of variables and declare them to the reader
// - the variable names MUST corresponds in name and type to those given in the weight file(s) used

    Float_t N3_Pt, N4_Pt, N_MET;
    Float_t N3_IsoT, N4_IsoT;
    reader->AddVariable("N3_Pt", &N3_Pt);
    reader->AddVariable("N4_Pt", &N4_Pt);
    reader->AddVariable("N3_IsoT", &N3_IsoT);
    reader->AddVariable("N4_IsoT", &N4_IsoT);
    reader->AddVariable("N_MET", &N_MET);
    
// --- Book the MVA methods

    reader->BookMVA(methodName, weightfile);
    
// Book output histogramm

    TH1F * histBdt = new TH1F("MVA_BDT", "MVA_BDT", nbin, -0.8, 0.8);    

// Prepare input tree (this must be replaced by your data source)
    
    TFile * input(0);
    TString fname = "./mvaRed.root";
    input = TFile::Open(fname); // check if file in local directory exists

// Prepare the event tree
  
    TTree* theTree = (TTree*) input->Get("MVATree");
  
    theTree->SetBranchAddress("N3_Pt", &N3_Pt);
    theTree->SetBranchAddress("N4_Pt", &N4_Pt);
    theTree->SetBranchAddress("N3_IsoT", &N3_IsoT);
    theTree->SetBranchAddress("N4_IsoT", &N4_IsoT);
    theTree->SetBranchAddress("N_MET", &N_MET);
    
//Run Over the Tree

    for (Long64_t ievt = 0; ievt < theTree->GetEntries(); ievt++) {

        theTree->GetEntry(ievt);
                    histBdt ->Fill(reader->EvaluateMVA("BDT method"));
    }    
