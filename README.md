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

