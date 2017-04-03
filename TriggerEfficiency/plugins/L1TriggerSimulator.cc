// -*- C++ -*-
//
// Package:    Test
// Class:      L1TriggerSimulator
// 
/**\class L1TriggerSimulator L1TriggerSimulator.cc Test/L1TriggerSimulator/src/L1TriggerSimulator.cc

Description: An analyzer to simulate the L1 trigger based on only gen-level information.

Implementation: To be added.

*/
//
// Original Author:  Paul Lujan
//         Created:  Wed Nov 26 14:16:14 CST 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "TRandom3.h"
#include "TVector2.h"

//
// class declaration
//

const int nDoubleJetCuts = 6;
const int nMETCuts = 5;
const int nRadiusCuts = 5;

const float singleJetCut = 128.0;                                     // L1_SingleJet128
// actual calorimeter radius: ECAL 1.29m-1.79m, HCAL 1.79m-2.95m
const float radiusCuts[nRadiusCuts] = {129, 154, 179, 237, 295};      // in cm!
const float doubleJetCuts[nDoubleJetCuts] = {40, 44, 48, 56, 64, 72}; // L1_DoubleJetC56
const float metCuts[nMETCuts] = {36, 56, 76, 96, 116};                 // L1_ETM36

const float etaCut = 3.0;

class L1TriggerSimulator : public edm::EDAnalyzer {
public:
  explicit L1TriggerSimulator(const edm::ParameterSet&);
  ~L1TriggerSimulator();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------

  edm::InputTag genParticlesTag_;
  edm::InputTag genMETTag_;
  edm::InputTag genJetsTag_;

  // Counters
  // first index: radius cut bin
  // second index: double jet cut bin
  // third index: met cut bin
  int nTotal;
  int nPass[nRadiusCuts][nDoubleJetCuts][nMETCuts];

  void PrintPercentage(int pass, int total);

  TRandom3 *r;
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
L1TriggerSimulator::L1TriggerSimulator(const edm::ParameterSet& iConfig):
  genParticlesTag_( iConfig.getUntrackedParameter<edm::InputTag>("genParticlesTag", edm::InputTag("genParticles")) ),
  genMETTag_( iConfig.getUntrackedParameter<edm::InputTag>("genMETTag", edm::InputTag("genMetTrue"))),
  genJetsTag_( iConfig.getUntrackedParameter<edm::InputTag>("genJetsTag", edm::InputTag("ak5GenJets")))
{
  //now do whatever initialization is needed

  nTotal = 0;
  for (int i=0; i<nRadiusCuts; ++i) {
    for (int j=0; j<nDoubleJetCuts; ++j) {
      for (int k=0; k<nMETCuts; ++k) {
	nPass[i][j][k] = 0;
      }
    }
  }
  r = new TRandom3(73241);
}


L1TriggerSimulator::~L1TriggerSimulator()
{
  // do anything here that needs to be done at destruction time
  // (e.g. close files, deallocate resources etc.)

  std::cout << "Efficiencies  | ";
  for (int k=0; k<nMETCuts; k++)
    std::cout << "MET cut = " << metCuts[k] << "  | ";
  std::cout <<  std::fixed << std::setw(4) << std::setprecision(1) << std::endl;

  for (int i=0; i<nRadiusCuts; i++) {
    std::cout << "R cut = " << radiusCuts[i] << std::endl;
    for (int j=0; j<nDoubleJetCuts; j++) {
      std::cout << "2j cut = " << doubleJetCuts[j] << " | ";

      for (int k=0; k<nMETCuts; k++) {
	PrintPercentage(nPass[i][j][k], nTotal);
	std::cout << "| ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;

  delete r;
}


//
// member functions
//

// Helper function to print out percentages.

void L1TriggerSimulator::PrintPercentage(int pass, int total) {
  if (total == 0)
    std::cout << "no events     ";
  else {
    float pct = (float)pass/total;
    float pcterr = sqrt(pct*(1-pct)/total);
    std::cout << std::fixed << std::setw(4) << std::setprecision(1) << std::left << pct*100
	      << " +/- " << std::setw(4) << std::setprecision(1) << std::left << pcterr*100 << " ";
  }
}

// ------------ method called for each event  ------------
void
L1TriggerSimulator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::GenParticleCollection> genparticles;
  if ( !iEvent.getByLabel(genParticlesTag_, genparticles) || !genparticles.isValid()) {
    std::cerr << "Could not extract gen particles with input tag " 
	      << genParticlesTag_ << std::endl;
    return;
  }

  edm::Handle<reco::GenMETCollection> genmets;
  if ( !iEvent.getByLabel(genMETTag_, genmets) || !genmets.isValid()) {
    std::cerr << "Could not extract gen MET with input tag " << genMETTag_ << std::endl;
    return;
  }

  edm::Handle<reco::GenJetCollection> genjets;
  if (!iEvent.getByLabel(genJetsTag_, genjets) || !genjets.isValid()) {
    std::cerr << "Could not extract gen jets with input tag " 
	      << genJetsTag_ << std::endl;
    return;
  }

  // get beamspot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  const reco::BeamSpot& bs = (*beamSpotHandle);
  
  float ht = 0;
  bool singleJetPassed[nRadiusCuts];
  for (int i=0; i<nRadiusCuts; ++i)
    singleJetPassed[i] = false;
  int nPassingJets[nRadiusCuts][nDoubleJetCuts];
  for (int i=0; i<nRadiusCuts; ++i) {
    for (int j=0; j<nDoubleJetCuts; ++j)
      nPassingJets[i][j] = 0;
  }

  // extract MET
  if (genmets->size() != 1) {
    std::cerr << "found " << genmets->size() << " gen mets, expected 1!" << std::endl;
  }
  float baseMet = genmets->at(0).et();
  TVector2 metVec[nRadiusCuts];
  for (int i=0; i<nRadiusCuts; ++i)
    metVec[i].SetMagPhi(genmets->at(0).et(), genmets->at(0).phi());
  //std::cout << "Bare met = " << baseMet << std::endl;

  //std::cout << "- event " << nTotal << " (" << genjets->size() << " jets)" << std::endl;
  for (unsigned int iJ=0; iJ<genjets->size(); iJ++) {
    reco::GenJetRef jet(genjets, iJ);

    ht += jet->pt();

    if (fabs(jet->eta()) > etaCut) continue;

    // Find jet and calculate the ET to be considered within the radius cut.
    // ET not within the radius can be added to the MET (or not; see below).

    for (int i=0; i<nRadiusCuts; ++i) {

      float totPt = 0;
      float totPtPass = 0;

      std::vector<const reco::GenParticle*> jetTracks = jet->getGenConstituents();

      for (unsigned int iT=0; iT<jetTracks.size(); iT++) {
	const reco::GenParticle &part = *(jetTracks.at(iT));
	const reco::BeamSpot::Point bsPos = bs.position(part.vz());
	double dr = sqrt(part.vx()*part.vx() + part.vy()*part.vy());
	
	totPt += part.pt();
	if (dr < radiusCuts[i])
	  totPtPass += part.pt();
      }
      float passingEt = jet->et()*totPtPass/totPt;
      TVector2 addedMet;
      addedMet.SetMagPhi(jet->et()-passingEt, jet->phi());
      metVec[i] += addedMet;

      if (passingEt > singleJetCut)
	singleJetPassed[i] = true;
      
      for (int j=0; j<nDoubleJetCuts; ++j) {
	if (passingEt > doubleJetCuts[j])
	  nPassingJets[i][j]++;
      } // double jet cut loop

    } // radius cut loop
  } // loop over jets

  // Now see if we pass cuts. Note -- we can use either
  // the base MET or the "corrected" MET here as desired.
  for (int i=0; i<nRadiusCuts; ++i) {
    for (int j=0; j<nDoubleJetCuts; ++j) {
      for (int k=0; k<nMETCuts; ++k) {
	if (singleJetPassed[i] == true ||
	    nPassingJets[i][j] >= 2 ||
	    metVec[i].Mod() > metCuts[k])
	  nPass[i][j][k]++;
      }
    }
  }

  nTotal++;
}


// ------------ method called once each job just before starting event loop  ------------
void 
L1TriggerSimulator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TriggerSimulator::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
L1TriggerSimulator::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
L1TriggerSimulator::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
L1TriggerSimulator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
L1TriggerSimulator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1TriggerSimulator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TriggerSimulator);
