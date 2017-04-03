// -*- C++ -*-
//
// Package:    TriggerEfficiencyH4b
// Class:      TriggerefficiencyH4b
// 
/**\class TriggerEfficiencyH4b TriggerEfficiencyH4b.cc PUAnalysisTools/TriggerEfficiency/src/TriggerEfficiencyH4b.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Paul Lujan
//
//

const int nbins = 4;
const float genEffMin = 20.0;
const float genEffMax = 80.0;

// system include files
#include <cmath>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "TMath.h"
#include "TFile.h"
#include "TProfile.h"

#include <Math/GenVector/VectorUtil.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/HLTPathStatus.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

//
// class declaration
//

class TriggerEfficiencyH4b : public edm::EDAnalyzer {
public:
  explicit TriggerEfficiencyH4b(const edm::ParameterSet&);
  ~TriggerEfficiencyH4b();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  void fillEffHisto(int iTr, std::vector<float> &lxyVals, std::vector<float> &ctauVals, int pass, bool passL1);
  void printPercentage(int pass, int total);
  static bool sortFunction(const std::pair<std::string, int> &p1,
			   const std::pair<std::string, int> &p2) {
    return (p1.second > p2.second);
  }

  // ----------member data ---------------------------
  L1GtUtils m_l1GtUtils;
  HLTConfigProvider hltConfig_;
  
  // counters for acceptance
  int n_events[nbins];
  std::vector<int> n_trig[nbins];

  bool writeTriggerInfo_;
  std::string hltLabel_;
  bool isMC_;

  edm::InputTag genParticlesTag_;
  edm::InputTag triggerEventTag_;
  edm::InputTag triggerResultsTag_;
  
  std::vector<std::string> targetTrigNames_;
  std::vector<std::string> unprescaledTriggersHLT_;
  std::vector<std::string> unprescaledTriggersL1_;
  std::string outfileName_;
  TFile *outfile_;

  std::vector<TProfile *> trigEffVsLxy1X_;
  std::vector<TProfile *> trigEffVsCtau1X_;
  std::vector<TProfile *> trigEffVsLxy2X_;
  std::vector<TProfile *> trigEffVsCtau2X_;
  std::vector<TProfile *> trigEffVsLxyMinX_;
  std::vector<TProfile *> trigEffVsCtauMinX_;
  std::vector<TProfile *> L1PassTrigEffVsLxy1X_;
  std::vector<TProfile *> L1PassTrigEffVsCtau1X_;
  std::vector<TProfile *> L1PassTrigEffVsLxyMinX_;
  std::vector<TProfile *> L1PassTrigEffVsCtauMinX_;

  TH1F* Lxy1X_;
  TH1F *Ctau1X_;
  TH1F* Lxy2X_;
  TH1F *Ctau2X_;
  TH1F* LxyMinX_;
  TH1F *CtauMinX_;

  bool triggerInfoInitialized_;
  TProfile* allTriggerEfficiency_;
  std::vector<bool> triggerUnprescaled_;
  
  std::vector<std::string> l1TriggerName_;
  std::vector<int> l1TriggerCount_;
  std::vector<bool> l1TriggerIsPrescaled_;

  const double plotLxyMax_;
  const double plotCtauMax_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//


//
// constructors and destructor
//
TriggerEfficiencyH4b::TriggerEfficiencyH4b(const edm::ParameterSet& iConfig) :
  writeTriggerInfo_( iConfig.getUntrackedParameter<bool>("writeTriggerInfo", false)),
  hltLabel_( iConfig.getUntrackedParameter<std::string>("HLTLabel", "HLT") ),
  isMC_( iConfig.getUntrackedParameter<bool>("isMC", true) ),
  genParticlesTag_( iConfig.getUntrackedParameter<edm::InputTag>("genParticlesTag",edm::InputTag("genParticles")) ),
  triggerEventTag_( iConfig.getUntrackedParameter<edm::InputTag>("triggerEventTag",edm::InputTag("triggerSummaryAOD")) ),
  triggerResultsTag_( iConfig.getUntrackedParameter<edm::InputTag>("triggerResultsTag",edm::InputTag("TriggerResults","","HLT")) ),
  outfileName_( iConfig.getUntrackedParameter<std::string>("outfileName", "outfile.root")),
  plotLxyMax_(iConfig.getUntrackedParameter<double>("plotLxyMax", 200)),
  plotCtauMax_(iConfig.getUntrackedParameter<double>("plotCtauMax", 200))
{
  targetTrigNames_ = iConfig.getUntrackedParameter<std::vector<std::string> >("targetTrigNames");
  unprescaledTriggersHLT_ = iConfig.getUntrackedParameter<std::vector<std::string> >("unprescaledTriggersHLT");
  unprescaledTriggersL1_ = iConfig.getUntrackedParameter<std::vector<std::string> >("unprescaledTriggersL1");

  // other initializations (e.g. set counters to 0)

  // Add in some dummy triggers
  targetTrigNames_.push_back("AnyDisplacedTriggerL1");
  targetTrigNames_.push_back("AnyTriggerL1");
  targetTrigNames_.push_back("AnyDisplacedTriggerHLT");
  targetTrigNames_.push_back("AnyTriggerHLT");

  unsigned int nTargetTrigs = targetTrigNames_.size();

  for (int i=0; i<nbins; i++) {
    n_events[i] = 0;
    for (unsigned int j=0; j<nTargetTrigs; j++)
      n_trig[i].push_back(0);
  }

  char buf[512];

  for (unsigned int i=0; i<nTargetTrigs; i++) {
    sprintf(buf, "trigEffVsLxy1X_%s", targetTrigNames_[i].c_str());
    trigEffVsLxy1X_.push_back(new TProfile(buf, "Trigger efficiency vs. L_{xy} of either X", 40, 0, plotLxyMax_));
    sprintf(buf, "trigEffVsCtau1X_%s", targetTrigNames_[i].c_str());
    trigEffVsCtau1X_.push_back(new TProfile(buf, "Trigger efficiency vs. c#tau of either X", 40, 0, plotCtauMax_));

    sprintf(buf, "trigEffVsLxy2X_%s", targetTrigNames_[i].c_str());
    trigEffVsLxy2X_.push_back(new TProfile(buf, "Trigger efficiency vs. L_{xy} of both X", 10, 0, plotLxyMax_));
    sprintf(buf, "trigEffVsCtau2X_%s", targetTrigNames_[i].c_str());
    trigEffVsCtau2X_.push_back(new TProfile(buf, "Trigger efficiency vs. c#tau of both X", 10, 0, plotCtauMax_));

    sprintf(buf, "trigEffVsLxyMinX_%s", targetTrigNames_[i].c_str());
    trigEffVsLxyMinX_.push_back(new TProfile(buf, "Trigger efficiency vs. smaller L_{xy} of Xs", 40, 0, plotLxyMax_));
    sprintf(buf, "trigEffVsCtauMinX_%s", targetTrigNames_[i].c_str());
    trigEffVsCtauMinX_.push_back(new TProfile(buf, "Trigger efficiency vs. smaller c#tau of Xs", 40, 0, plotCtauMax_));

    sprintf(buf, "L1PassTrigEffVsLxy1X_%s", targetTrigNames_[i].c_str());
    L1PassTrigEffVsLxy1X_.push_back(new TProfile(buf, "Trigger efficiency (passing L1) vs. L_{xy} of either X", 40, 0, plotLxyMax_));
    sprintf(buf, "L1PassTrigEffVsCtau1X_%s", targetTrigNames_[i].c_str());
    L1PassTrigEffVsCtau1X_.push_back(new TProfile(buf, "Trigger efficiency (passing L1) vs. c#tau of either X", 40, 0, plotCtauMax_));

    sprintf(buf, "L1PassTrigEffVsLxyMinX_%s", targetTrigNames_[i].c_str());
    L1PassTrigEffVsLxyMinX_.push_back(new TProfile(buf, "Trigger efficiency (passing L1) vs. smaller L_{xy} of Xs", 40, 0, plotLxyMax_));
    sprintf(buf, "L1PassTrigEffVsCtauMinX_%s", targetTrigNames_[i].c_str());
    L1PassTrigEffVsCtauMinX_.push_back(new TProfile(buf, "Trigger efficiency (passing L1) vs. smaller c#tau of Xs", 40, 0, plotCtauMax_));
  }
  // and one for the overall distributions
  Lxy1X_ = new TH1F("Lxy1X", "Distribution of L_{xy} of either X", 40, 0, plotLxyMax_);
  Ctau1X_ = new TH1F("Ctau1X", "Distribution of c#tau of either X", 40, 0, plotCtauMax_);

  Lxy2X_ = new TH1F("Lxy2X", "Distribution of L_{xy} of both X", 40, 0, plotLxyMax_);
  Ctau2X_ = new TH1F("Ctau2X", "Distribution of c#tau of both X", 40, 0, plotCtauMax_);

  LxyMinX_ = new TH1F("LxyMinX", "Distribution of L_{xy} of smaller X", 40, 0, plotLxyMax_);
  CtauMinX_ = new TH1F("CtauMinX", "Distribution of c#tau of smaller X", 40, 0, plotCtauMax_);
  
  triggerInfoInitialized_ = false;
}


TriggerEfficiencyH4b::~TriggerEfficiencyH4b(){}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TriggerEfficiencyH4b::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
   bool useL1EventSetup = true;
   bool useL1GtTriggerMenuLite = true;

   // get L1 trigger info
   m_l1GtUtils.getL1GtRunCache(iEvent, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();

   // Some trigger information
   const std::string processName = hltLabel_;
   bool changed;
   hltConfig_.init(iEvent.getRun(), iSetup, processName, changed);
   if (changed) std::cout << "Trigger info changed: " << changed << std::endl;
   if (writeTriggerInfo_ ) {
     std::cout << "LIST OF TRIGGERS" << std::endl;
     std::cout << "================" << std::endl;

     // look at the L1 trigger info too
     std::cout << "L1 algo triggers: " << std::endl;

     for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo) {
       int iErrorCode;
       int prescale = m_l1GtUtils.prescaleFactor(iEvent, (algo->second).algoName(), iErrorCode);
       if (iErrorCode != 0) std::cout << "Bad prescale factor for " << (algo->second).algoName() << std::endl;
       std::cout << "Name: " << (algo->second).algoName() << " Alias: " << (algo->second).algoAlias()
		 << " prescale: " << prescale << std::endl;
     }

     std::cout << "HLT triggers (process = " << hltLabel_ << ")" << std::endl;
     for( int iN=0; iN<(int)(hltConfig_.triggerNames()).size(); ++iN ){
       trigger::size_type index = hltConfig_.triggerIndex( (hltConfig_.triggerNames())[iN] );
       const int prescaleSet = hltConfig_.prescaleSet(iEvent, iSetup);
       unsigned int prescale = hltConfig_.prescaleValue( iEvent, iSetup, (hltConfig_.triggerNames())[iN] );
       std::cout << "Name: " << (hltConfig_.triggerNames())[iN] << " Index: " << index 
		 << " Prescale: " << prescaleSet << " " << prescale << std::endl;
     }
     writeTriggerInfo_ = false;
   }

   int whichbin = 0;
   // the two below are meaningful only if one goes to electrons and one muons

   // Classify the event by the MC type.
   std::vector<float> lxyVals;
   std::vector<float> ctauVals;

   if( isMC_ ){      
     edm::Handle<reco::GenParticleCollection> genparticles;
     if ( !iEvent.getByLabel(genParticlesTag_,genparticles) ) {
       std::cerr << "Could not extract gen particles with input tag " 
		 << genParticlesTag_ << std::endl;
       return;
     }
     
     if (!genparticles.isValid() ){
       std::cerr << "Input tag " << genParticlesTag_ << " not valid collection" << std::endl;
       return;
     }

     int n1=0;
     int n2=0;
     int n3=0;
     int semilep_b=0;
     
     for (unsigned int i=0; i<genparticles->size(); i++) {
       reco::GenParticleRef part(genparticles, i);

       if (abs(part->pdgId()) == 13) {
	 bool is_semilep = true;
	 for (unsigned int j=0; j<part->numberOfMothers(); j++) {
	   reco::GenParticleRef moth = part->motherRef(j);
	   if (abs(moth->pdgId()) == 6001113 || abs(moth->pdgId()) == 6002113 || abs(moth->pdgId()) == 6003113) {
	     is_semilep = false;
	     break;
	   }
	 }
	 if (is_semilep) semilep_b++;
       }
       
       if (part->pdgId() == 6001112) n1++;
       else if (part->pdgId() == 6002112 || part->pdgId() == 6000112) n2++;
       else if (part->pdgId() == 6003112) n3++;
       else continue;

       // calculate lifetime -- this is determined by the vertex position
       // of the 1st daughter
       if (part->numberOfDaughters() > 0) {
	 reco::GenParticleRef dau0 = part->daughterRef(0);
	 // taken from XtoFFbarFilter:
	 // Unfortunately, duplicate particles can appear in the event record. Handle this as follows:
	 for (unsigned int j = 0; j < dau0->numberOfDaughters(); j++) {
	   reco::GenParticleRef granddau = dau0->daughterRef(j);        
	   if (granddau->pdgId() == dau0->pdgId()) {
	     dau0 = granddau;
	     break;
	   }
	 }
	 // Having found the actual daughter, compute the distance.
	 math::XYZVector dlength = dau0->vertex()-part->vertex();
	 float lxy = dlength.Rho();
	 // Compute ctau too
	 float ctau = dlength.Rho()*part->mass()/part->pt();

	 lxyVals.push_back(lxy);
	 ctauVals.push_back(ctau);
       }
       
       if (n1+n2+n3 == 2) break;
     }
     
     if (n1+n2+n3 != 2) {
       std::cerr << "Error: didn't find two long-lived particles"  << std::endl;
       for (unsigned int i=0; i<50; i++) {
	 reco::GenParticleRef part(genparticles, i);
	 std::cout << part->pdgId() << std::endl;
       }
       return;
     }
     
     if (n1 == 2) whichbin = 1;
     else if (n2 == 2) whichbin = 2;
     else if (n3 == 2) whichbin = 3;
     else {
       std::cerr << "Error: long-lived particle types didn't match" << std::endl;
       return;
     }

   } // is MC
  
   n_events[0]++;
   if (whichbin != 0) n_events[whichbin]++;

   // Now, look for the trigger information.

   edm::Handle<trigger::TriggerEvent> trgEvent;
   iEvent.getByLabel(triggerEventTag_, trgEvent);

   edm::Handle<edm::TriggerResults> trgResults;
   if( !iEvent.getByLabel(triggerResultsTag_,trgResults) ){
      std::cout << "Could not get trigger results with tag " << triggerResultsTag_ << std::endl;
   }
   
   // Store the number of accepted triggers and the type by index
   if( !trgResults.isValid() ) {
     std::cerr << "Error: invalid trigger results" << std::endl;
     return;
   }

   unsigned int nTargetTrigs = targetTrigNames_.size();
   int passAnyTriggersL1 = 0;
   int passAnyTargetTriggersL1 = 0;
   int passAnyTriggersHLT = 0;
   int passAnyTargetTriggersHLT = 0;

   // Set up trigger info, if we haven't.
   if (triggerInfoInitialized_ == false) {
     // Save L1 triggers info.
     for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo) {
       std::string tName = (algo->second).algoName();

       l1TriggerName_.push_back(tName);
       l1TriggerCount_.push_back(0);
       bool isPrescaled = true;
       for (unsigned int iTr=0; iTr<unprescaledTriggersL1_.size(); iTr++) {
	 if (tName == unprescaledTriggersL1_[iTr]) {
	   isPrescaled = false;
	   break;
	 }
       }
       l1TriggerIsPrescaled_.push_back(isPrescaled);
     }

     // And HLT trigger info.
     unsigned int nTrig = hltConfig_.triggerNames().size();
     triggerUnprescaled_.resize(nTrig);
     allTriggerEfficiency_ = new TProfile("allTriggerEfficiency", "Efficiency for all unprescaled triggers",
					  nTrig, -0.5, (float)nTrig-0.5);
     for (unsigned int iN=0; iN<(hltConfig_.triggerNames()).size(); ++iN) {
       std::string tName = (hltConfig_.triggerNames())[iN];
       allTriggerEfficiency_->GetXaxis()->SetBinLabel(iN+1, tName.c_str());

       triggerUnprescaled_[iN] = false;
       // See if this is unprescaled.
       for (unsigned int iTr=0; iTr<unprescaledTriggersHLT_.size(); iTr++) {
	 if (tName == unprescaledTriggersHLT_[iTr]) {
	   triggerUnprescaled_[iN] = true;
	   break;
	 } // was unprescaled
       } // loop over unprescaled triggers
     } // loop over all triggers
     triggerInfoInitialized_ = true;
   } // initialize trigger info



   // Loop over L1 triggers.
   int l1tr = 0;
   for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo, ++l1tr) {
     int iErrorCode;
     std::string tName = (algo->second).algoName();
     bool pass = m_l1GtUtils.decisionAfterMask(iEvent, tName, iErrorCode);
     if (iErrorCode != 0) std::cout << "Bad decision for " << (algo->second).algoName() << std::endl;
     //std::cout << tName << " result: " << pass << " error: " << iErrorCode << std::endl;

     // See if this is an unprescaled trigger, so it counts for passAny.
     if (pass) {
       assert(l1TriggerName_[l1tr] == tName);
       l1TriggerCount_[l1tr]++;
       for (unsigned int iTr=0; iTr<unprescaledTriggersL1_.size(); iTr++) {
	 if (tName == unprescaledTriggersL1_[iTr]) {
	   passAnyTriggersL1 = true;
	   break;
	 }
       }
     }

     for (unsigned int iTr=0; iTr<nTargetTrigs; iTr++) {
       if (tName == targetTrigNames_[iTr]) {

	 if (pass) {
	   n_trig[0][iTr]++;
	   if (whichbin != 0) n_trig[whichbin][iTr]++;
	   passAnyTargetTriggersL1 = true;
	 }
	 	   
	 // Fill efficiency histograms.  Could also require a specific value of whichbin here,
	 // but for now we'll leave it alone.

	 fillEffHisto(iTr, lxyVals, ctauVals, pass, false);

       } // if desired trigger
     } // loop over target triggers
   } // loop over L1 triggers

   for( int iN=0; iN<(int)(hltConfig_.triggerNames()).size(); ++iN ) {
     std::string tName = (hltConfig_.triggerNames())[iN];

     if( tName.find("HLT_") == std::string::npos ) continue;      
     int tIndex = hltConfig_.triggerIndex( (hltConfig_.triggerNames())[iN] );

     if (triggerUnprescaled_[iN]) {
       if (trgResults->accept(tIndex) > 0) {
	 passAnyTriggersHLT = 1;
	 allTriggerEfficiency_->Fill(iN, 1);
       } else {
	 allTriggerEfficiency_->Fill(iN, 0);
       }
     } // was unprescaled

     for (unsigned int iTr=0; iTr<nTargetTrigs; iTr++) {
       if (tName == targetTrigNames_[iTr]) {
	 int pass = 0;
	 if (trgResults->accept(tIndex) > 0) {
	   // std::cout << tName << " passed" << std::endl;
	   n_trig[0][iTr]++;
	   if (whichbin != 0) n_trig[whichbin][iTr]++;
	   pass = 1;
	   passAnyTargetTriggersHLT = 1;
	 } else {
	   // std::cout << tName << " failed" << std::endl;
	 }

	 // Also check to see if we passed L1.
	 	   
	 // Fill efficiency histograms.  Could also require a specific value of whichbin here,
	 // but for now we'll leave it alone.

	 std::string L1Name = targetTrigNames_[iTr-1];
	 // Check to see if passed L1.
	 int iErrorCode;
	 bool passL1 = m_l1GtUtils.decisionBeforeMask(iEvent, L1Name, iErrorCode);

	 fillEffHisto(iTr, lxyVals, ctauVals, pass, passL1);
       }
     } // loop over target triggers
   } // loop over all triggers

   // Fill all-trigger & all-displaced-trigger histos.
   if (passAnyTargetTriggersL1) {
     n_trig[0][nTargetTrigs-4]++;
     if (whichbin != 0) n_trig[whichbin][nTargetTrigs-4]++;
   }
   fillEffHisto(nTargetTrigs-4, lxyVals, ctauVals, passAnyTargetTriggersL1, false);
   if (passAnyTriggersL1) {
     n_trig[0][nTargetTrigs-3]++;
     if (whichbin != 0) n_trig[whichbin][nTargetTrigs-3]++;
   }
   fillEffHisto(nTargetTrigs-3, lxyVals, ctauVals, passAnyTriggersL1, false);

   if (passAnyTargetTriggersHLT) {
     n_trig[0][nTargetTrigs-2]++;
     if (whichbin != 0) n_trig[whichbin][nTargetTrigs-2]++;
   }
   fillEffHisto(nTargetTrigs-2, lxyVals, ctauVals, passAnyTargetTriggersHLT, passAnyTargetTriggersL1);
   if (passAnyTriggersHLT) {
     n_trig[0][nTargetTrigs-1]++;
     if (whichbin != 0) n_trig[whichbin][nTargetTrigs-1]++;
   }
   fillEffHisto(nTargetTrigs-1, lxyVals, ctauVals, passAnyTriggersHLT, passAnyTriggersL1);

   // Store general information.
   Lxy1X_->Fill(lxyVals[0]);
   Lxy1X_->Fill(lxyVals[1]);
   Ctau1X_->Fill(ctauVals[0]);
   Ctau1X_->Fill(ctauVals[1]);

   if (Lxy2X_->FindBin(lxyVals[0]) == Lxy2X_->FindBin(lxyVals[1]))
     Lxy2X_->Fill(lxyVals[0]);
   if (Ctau2X_->FindBin(ctauVals[0]) == Ctau2X_->FindBin(ctauVals[1]))
     Ctau2X_->Fill(ctauVals[0]);

   LxyMinX_->Fill(std::min(lxyVals[0], lxyVals[1]));
   CtauMinX_->Fill(std::min(ctauVals[0], ctauVals[1]));
  
} // end of event loop


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerEfficiencyH4b::beginJob(){}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerEfficiencyH4b::endJob() {
  std::cout << "                                      Trigger Name total  ctau0.1 ctau1.0 ctau10" << std::endl;
  for (unsigned int i=0; i<targetTrigNames_.size(); i++) {
    std::cout << std::setw(50) << targetTrigNames_[i] << " ";
    for (int j=0; j<nbins; j++)
      std::cout << n_trig[j][i] << "/" << n_events[j] << " ";
    std::cout << std::endl;
  }

  std::cout << "                                      Trigger Name total        ctau0.1      ctau1.0      ctau10" << std::endl;
  for (unsigned int i=0; i<targetTrigNames_.size(); i++) {
    std::cout << std::setw(50) << targetTrigNames_[i] << " ";
    for (int j=0; j<nbins; j++) {
      printPercentage(n_trig[j][i], n_events[j]);
    }
    std::cout << std::endl;
  }

  std::cout << "--- Top L1 triggers ---" << std::endl;
  std::vector<std::pair<std::string, int> > l1TrigResults;
  for (unsigned int i=0; i<l1TriggerName_.size(); ++i) {
    if (!l1TriggerIsPrescaled_[i]) {
     l1TrigResults.push_back(std::make_pair(l1TriggerName_[i], l1TriggerCount_[i]));
    }
  }
  std::sort(l1TrigResults.begin(), l1TrigResults.end(), sortFunction);
  for (unsigned int i=0; i<50; ++i) {
    std::cout  << " " << l1TrigResults[i].first << " " ;
    printPercentage(l1TrigResults[i].second, n_events[0]);
    std::cout << std::endl;
  }

  outfile_ = new TFile(outfileName_.c_str(), "RECREATE");
  for (unsigned int i=0; i<targetTrigNames_.size(); i++) {
    trigEffVsLxy1X_[i]->Write();
    trigEffVsCtau1X_[i]->Write();

    trigEffVsLxy2X_[i]->Write();
    trigEffVsCtau2X_[i]->Write();

    trigEffVsLxyMinX_[i]->Write();
    trigEffVsCtauMinX_[i]->Write();

    L1PassTrigEffVsLxy1X_[i]->Write();
    L1PassTrigEffVsCtau1X_[i]->Write();

    L1PassTrigEffVsLxyMinX_[i]->Write();
    L1PassTrigEffVsCtauMinX_[i]->Write();
  }

  Lxy1X_->Write();
  Ctau1X_->Write();
  Lxy2X_->Write();
  Ctau2X_->Write();
  LxyMinX_->Write();
  CtauMinX_->Write();
  if (allTriggerEfficiency_ != NULL)
    allTriggerEfficiency_->Write();
  outfile_->Close();
}

void TriggerEfficiencyH4b::fillEffHisto(int iTr, std::vector<float> &lxyVals, std::vector<float> &ctauVals, int pass, bool passL1) {
  // Versions in which only one X has to be in the given bin (i.e. filled twice per event)
  trigEffVsLxy1X_[iTr]->Fill(lxyVals[0], pass);
  trigEffVsLxy1X_[iTr]->Fill(lxyVals[1], pass);
  trigEffVsCtau1X_[iTr]->Fill(ctauVals[0], pass);
  trigEffVsCtau1X_[iTr]->Fill(ctauVals[1], pass);
  
  // Versions in which both Xes have to be in the given bin. Note -- these don't exist in log versions
  // at the moment
  if (trigEffVsLxy2X_[iTr]->FindBin(lxyVals[0]) == trigEffVsLxy2X_[iTr]->FindBin(lxyVals[1]))
    trigEffVsLxy2X_[iTr]->Fill(lxyVals[0], pass);
  if (trigEffVsCtau2X_[iTr]->FindBin(ctauVals[0]) == trigEffVsCtau2X_[iTr]->FindBin(ctauVals[1]))
    trigEffVsCtau2X_[iTr]->Fill(ctauVals[0], pass);
  
  // Versions that use the smaller lxy or ctau value for the two Xes.
  trigEffVsLxyMinX_[iTr]->Fill(std::min(lxyVals[0], lxyVals[1]), pass);
  trigEffVsCtauMinX_[iTr]->Fill(std::min(ctauVals[0], ctauVals[1]), pass);

  // Also fill in passL1 versions, if the trigger passed L1.
  if (passL1) {
    L1PassTrigEffVsLxy1X_[iTr]->Fill(lxyVals[0], pass);
    L1PassTrigEffVsLxy1X_[iTr]->Fill(lxyVals[1], pass);
    L1PassTrigEffVsCtau1X_[iTr]->Fill(ctauVals[0], pass);
    L1PassTrigEffVsCtau1X_[iTr]->Fill(ctauVals[1], pass);

    L1PassTrigEffVsLxyMinX_[iTr]->Fill(std::min(lxyVals[0], lxyVals[1]), pass);
    L1PassTrigEffVsCtauMinX_[iTr]->Fill(std::min(ctauVals[0], ctauVals[1]), pass);
  }
}

void TriggerEfficiencyH4b::printPercentage(int pass, int total) {
  if (total == 0)
    std::cout << "no events     ";
  else {
    float pct = (float)pass/total;
    float pcterr = sqrt(pct*(1-pct)/total);
    std::cout << std::fixed << std::setw(4) << std::setprecision(1) << std::left << pct*100
	      << " +/- " << std::setw(4) << std::setprecision(1) << std::left << pcterr*100 << " ";
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerEfficiencyH4b);
