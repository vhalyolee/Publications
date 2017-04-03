// -*- C++ -*-
//
// Package:    Test
// Class:      TriggerSimulator
// 
/**\class TriggerSimulator TriggerSimulator.cc Test/TriggerSimulator/src/TriggerSimulator.cc

Description: An analyzer to simulate the HLT trigger based on only gen-level information.

Implementation: To be added.

*/
//
// Original Author:  Paul Lujan
//         Created:  Fri Feb  7 09:51:14 CST 2014
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
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "TRandom3.h"

//
// class declaration
//

const int nHtCuts = 5;
const int nPtCuts = 5;
const int nDispCuts = 5;

const float htCuts[nHtCuts] = {0, 200, 250, 300, 350}; // Andrzej cut: >= 300 GeV
const float ptCuts[nPtCuts] = {60, 70, 80, 100, 120}; // standard cut: >= 60 GeV
const float dispCuts[nDispCuts] = {0.01, 0.02, 0.03, 0.04, 0.05}; // Andrzej cut: 300um (0.03 cm)

const int nTrackCut = 8;

class TriggerSimulator : public edm::EDAnalyzer {
public:
  explicit TriggerSimulator(const edm::ParameterSet&);
  ~TriggerSimulator();

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
  edm::InputTag genJetsTag_;

  // Cuts
  double eleLeadingEtCut_;
  double eleSecondEtCut_;
  double muPtCut_;
  double etaCut_;
  double lxyCut_;

  // Counters
  // first index: ht cut bin
  // second index: ntracks cut bin
  // third index: track lxy cut bin
  int nTotal;
  int nPass[nHtCuts][nPtCuts][nDispCuts];

  void PrintPercentage(int pass, int total);

  double l1eff_;
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
TriggerSimulator::TriggerSimulator(const edm::ParameterSet& iConfig):
  genParticlesTag_( iConfig.getUntrackedParameter<edm::InputTag>("genParticlesTag", edm::InputTag("genParticles")) ),
  genJetsTag_( iConfig.getUntrackedParameter<edm::InputTag>("genJetsTag", edm::InputTag("ak5GenJets"))),
  l1eff_( iConfig.getUntrackedParameter<double>("l1Eff"))
{
  //now do whatever initialization is needed

  nTotal = 0;
  for (int i=0; i<nHtCuts; i++) {
    for (int j=0; j<nPtCuts; j++) {
      for (int k=0; k<nDispCuts; k++) {
	nPass[i][j][k] = 0;
      }
    }
  }
  r = new TRandom3(73241);
}


TriggerSimulator::~TriggerSimulator()
{
  // do anything here that needs to be done at destruction time
  // (e.g. close files, deallocate resources etc.)

  std::cout << "Efficiencies" << std::endl;
  for (int i=0; i<nHtCuts; i++) {
    std::cout << "ht cut value " << i << std::endl;
    for (int j=0; j<nPtCuts; j++) {
      std::cout << "pt cut value " << j << " | ";

      for (int k=0; k<nDispCuts; k++) {
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

void TriggerSimulator::PrintPercentage(int pass, int total) {
  if (total == 0)
    std::cout << "no events     ";
  else {
    float pct = (float)pass/total;
    float pcterr = sqrt(pct*(1-pct)/total);
    //pct *= l1eff_/100;
    //pcterr *= l1eff_/100;
    std::cout << std::fixed << std::setw(4) << std::setprecision(1) << std::left << pct*100
	      << " +/- " << std::setw(4) << std::setprecision(1) << std::left << pcterr*100 << " ";
  }
}

// ------------ method called for each event  ------------
void
TriggerSimulator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::GenParticleCollection> genparticles;
  if ( !iEvent.getByLabel(genParticlesTag_, genparticles) || !genparticles.isValid()) {
    std::cerr << "Could not extract gen particles with input tag " 
	      << genParticlesTag_ << std::endl;
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
  int nPassingJets[nPtCuts][nDispCuts];
  for (int i=0; i<nPtCuts; i++) {
    for (int j=0; j<nDispCuts; j++) {
      nPassingJets[i][j] = 0;
    }
  }

  //std::cout << "- event " << nTotal << " (" << genjets->size() << " jets)" << std::endl;
  for (unsigned int iJ=0; iJ<genjets->size(); iJ++) {
    reco::GenJetRef jet(genjets, iJ);

    int nPromptTracks[nDispCuts];
    float displacedTrackPt[nDispCuts];
    for (int i=0; i<nDispCuts; i++) {
      displacedTrackPt[i] = 0;
      nPromptTracks[i] = 0;
    }

    std::vector<const reco::GenParticle*> jetTracks = jet->getGenConstituents();
    // std::cout << "-- jet " << iJ << " (" << jetTracks.size() << " tracks)" << std::endl;

    reco::Candidate::Vector jetMomPassing;

    for (unsigned int iT=0; iT<jetTracks.size(); iT++) {
      const reco::GenParticle &part = *(jetTracks.at(iT));
      const reco::BeamSpot::Point bsPos = bs.position(part.vz());
      double dxy = (-(part.vx()-bsPos.x()) * part.py() + (part.vy()-bsPos.y()) * part.px())/part.pt();
      double dz = (part.vz()-bsPos.z()) - (part.pz()/part.pt())*((part.vx()-bsPos.x())*part.px() + (part.vy()-bsPos.y())*part.py())/part.pt();
      dxy = fabs(dxy); // since we only care about magnitude
      dz = fabs(dz);

      double dr = sqrt(part.vx()*part.vx() + part.vy()*part.vy());
      
      // exclude tracks that start outside the tracker
      float trackEff = 1;
      if (dr > 110) trackEff = 0;
      if (fabs(part.vz()) > 280) trackEff = 0; // TOB goes out to |z|=109, TEC to 280

      // apply efficiency as function of dxy
      if (dxy < 20)
	trackEff *= 0.95 - 0.35*(dxy/20);
      else if (dxy < 32)
 	trackEff *= 0.60 - 0.60*(dxy-20)/12;
      
      // and dz -- this doesn't seem to work, so is commented out for now
//       if (dz > 15 && dz < 40)
// 	trackEff *= (0.95 - 0.35*(dz-15)/25)/0.95;
//       else if (dz < 50)
// 	trackEff *= (0.6 - 0.6*(dz-40)/10)/0.95;
//       else if (dz > 50)
// 	trackEff = 0;

      // std::cout << "--- track " << iT << " dxy=" << dxy << " dz=" << dz;
      // std::cout << "    vx=" << part.vx() << " vy=" << part.vy() << " vz=" << part.vz();
      // std::cout << "   trackEff = " << trackEff << std::endl;

      // see if it passes, add it to the jet if so
      if (r->Rndm() < trackEff) {
	jetMomPassing += part.momentum();

	for (int iC=0; iC<nDispCuts; iC++) {
	  if (dxy >= dispCuts[iC]) {
	    displacedTrackPt[iC] += part.pt();
	  } else { 
	    nPromptTracks[iC]++;
	  }
	} // loop over cuts
      } // if track is "reconstructed"

    }

    ht += jetMomPassing.Rho();
    // Check to see if it passes.

    for (int i=0; i<nPtCuts; i++) {
      for (int j=0; j<nDispCuts; j++) {
	if (displacedTrackPt[j] >= ptCuts[i] && nPromptTracks[j] < nTrackCut) nPassingJets[i][j]++;
      }
    }

  } // loop over jets

  // Now see if we pass cuts.
  for (int i=0; i<nHtCuts; i++) {
    if (ht < htCuts[i]) continue;
    
    for (int j=0; j<nPtCuts; j++) {
      for (int k=0; k<nDispCuts; k++) {
	if (nPassingJets[j][k] >= 2) nPass[i][j][k]++;
      }
    }

  }
  nTotal++;
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerSimulator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerSimulator::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TriggerSimulator::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TriggerSimulator::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TriggerSimulator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TriggerSimulator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriggerSimulator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerSimulator);
