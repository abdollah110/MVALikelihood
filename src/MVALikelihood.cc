// ************************************************ 
// software implementation of the likelihood based
// Multi-variate analysis technique
// author: Alexei Raspereza
// e-mail: Alexei.Raspereza@desy.de
// last modified : February 3 2011
// *************************************************

#include "Analysis/MVALikelihood/interface/MVALikelihood.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

MVALikelihood::MVALikelihood(StringVector classNames, StringVector varNames) {

  _numberOfClasses = classNames.size();
  _numberOfVariables = varNames.size();
  
  _classNames.clear();
  if (_numberOfClasses < 2 ) {
    std::cout << "MVALikelihood : Program TERMINATED ---> " << std::endl;
    std::cout << "Number of specified classes < 2 (should be > 2) " << std::endl;
    exit(-1);
  }
  else {
    for (unsigned int i=0;i<_numberOfClasses;++i) {
      _classNames.push_back(classNames.at(i));
      _classTNames.push_back(TString(classNames.at(i)));
    }
  }

  if (_numberOfVariables < 2 ) {
    std::cout << "MVALikelihood : Program TERMINATED ---> " << std::endl;
    std::cout << "Number of specified variables < 2 (should be > 2) " << std::endl;
    exit(-1);
  }
  else {
    for (unsigned int i=0;i<_numberOfVariables;++i)
      _varNames.push_back(varNames.at(i));
  }

  _files.clear();
  _pdfs.clear();
  std::cout << "******************************************************" << std::endl;
  std::cout << "************* L I K E L I H O O D ********************" << std::endl;
  std::cout << "******************************************************" << std::endl;
  
  for (unsigned int iClass = 0; iClass<_numberOfClasses; ++iClass) {
    std::cout << "Event class : " <<_classNames.at(iClass) << std::endl;
    TString fileName(classNames.at(iClass));
    TFile * file = new TFile(fileName+TString(".root"));
    if (file->IsZombie()) {
      std::cout << "MVALikelihood : File with name " << fileName 
		<< ".root does not exist" << std::endl;
      std::cout << "The program is terminated... " << std::endl;
      exit(-1);
    }
    _files.push_back(file);
    IndexMap index;
    index.clear();
    for (unsigned int iV=0; iV<_numberOfVariables; ++iV) {
      TF1 * func = (TF1*)file->Get(TString(_varNames.at(iV)));
      if (func==NULL) {
	std::cout << "MVALikelihood : Function " << _varNames.at(iV) 
		  << " is absent in the RooT file " << fileName << ".root" << std::endl; 
	std::cout << "Program is terminated ..." << std::endl;
	exit(-1);
      }
      TAxis * axis = func->GetXaxis();
      double lowerEdge = axis->GetXmin();
      double upperEdge = axis->GetXmax();
      double integral = func->Integral(lowerEdge,upperEdge);
      double norm = func->GetParameter(0);
      func->SetParameter(0,norm/integral);
      integral = func->Integral(lowerEdge,upperEdge);
      std::cout << "  " << _varNames.at(iV) << "   Integral : " 
		<< integral << std::endl; 
      index[_varNames.at(iV)] = func;
    }
    _pdfs[classNames.at(iClass)] = index;
  }
  
}

MVALikelihood::~MVALikelihood() {

  for (unsigned int iFile=0; iFile<_numberOfClasses; iFile++)
    delete _files.at(iFile);

}

double MVALikelihood::getLikelihood(StringDoubleMap variables,
				    std::string likeClassName) {


  unsigned int nOfVar = variables.size();

  TString TLikeClassName(likeClassName);
  bool isClassExist = false;
  for (unsigned int iCl=0; iCl<_numberOfClasses; ++iCl) {
    if (_classTNames.at(iCl)==TLikeClassName) {
      isClassExist = true;
      break;
    }
  
  }

  if (!isClassExist) {
    std::cout << std::endl;
    std::cout << "MVALikelihood::getLikelihood -> target event class " << TLikeClassName << " is not available in MVA..." << std::endl;
    std::cout << "returning value 0" << std::endl;
    std::cout << std::endl;
    double dummy = 0.0;
    return dummy;
  }

  ProbVector probVector;
  probVector.clear();
  for (unsigned int iClass=0; iClass<_numberOfClasses; ++iClass) {
    DoubleVector classPdfVector;
    classPdfVector.clear();
    std::string mainClassName = _classNames.at(iClass);   
    for (StringDoubleMap::iterator iV=variables.begin(); iV!=variables.end(); ++iV) {
      std::string varName = iV->first;
      double value = iV->second;
      double sum = 0.0;
      for (unsigned int jClass=0; jClass<_numberOfClasses; ++jClass) {
	std::string className = _classNames.at(jClass); 
	IndexMap index = _pdfs[className];
	TF1 * function = index[varName];
	if (function==NULL) {
	  std::cout << std::endl;
	  std::cout << "MVALikelihood::getLikelihood -> pdf with the name " << varName << " is not available in MVA... " << std::endl;
	  std::cout << "returning value 0." << std::endl;
	  std::cout << std::endl;
	  double dummy = 0.;
	  return dummy;
	}
	double pdf = fmax(1e-20,function->Eval(value));
	sum += pdf;
      }
      if (sum<0) 
	sum = 1e-20;
      IndexMap mainIndex = _pdfs[mainClassName];
      TF1 * mainFunction = mainIndex[varName];
      double mainPdf = fmax(1e-20,mainFunction->Eval(value));
      double prob = mainPdf / sum;
      classPdfVector.push_back(prob);
    }
    probVector[mainClassName] = classPdfVector;
  }

  StringDoubleMap probProd;
  probProd.clear();
  double sum = 0;
  for (unsigned int iClass = 0; iClass<_numberOfClasses; iClass++) {
    double prod = 1.0;
    std::string className = _classNames.at(iClass);
    DoubleVector classPdfVector = probVector[className];
    for (unsigned int iV=0;iV<nOfVar;++iV) {
      prod *= classPdfVector.at(iV);
    }
    probProd[className] = prod;
    sum += prod;
  }

  return probProd[likeClassName] / sum;

}

