// -*- C++ -*-
//
// Package:    NeutralinoLifetimeAnalyzer
// Class:      NeutralinoLifetimeAnalyzer
// 
/**\class NeutralinoLifetimeAnalyzer NeutralinoLifetimeAnalyzer.cc GMSBAnalysis/NeutralinoLifetimeAnalyzer/src/NeutralinoLifetimeAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tambe Ebai Norbert
//         Created:  Tue Apr 10 12:51:31 CDT 2012
// $Id$
//
//


// system include files
#include <memory>
#include <iostream>

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

// user include files Use CMS FrameWork and Parent Analyzer
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

// Will be adding more parameters with time
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//Tres impot
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

// Ooops! now I have to make some Plots
#include "FWCore/ServiceRegistry/interface/Service.h" 
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

//
// class declaration
//

class NeutralinoLifetimeAnalyzer : public edm::EDAnalyzer
{
public:
       //
      explicit NeutralinoLifetimeAnalyzer(const edm::ParameterSet&);
      ~NeutralinoLifetimeAnalyzer();

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

  TH1D*  Ntinopt;
  TH1D*  Ntinobeta;
  TH1D*  Ntinogamma;
  TH1F*  hardphpt;
  TH1F*  softphpt;
  TH1F* dihardphpt;
  TH1F* disoftphpt;
  TH1F* soft_hardphpt;
  
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

using namespace edm;
using namespace std;

NeutralinoLifetimeAnalyzer::NeutralinoLifetimeAnalyzer(const edm::ParameterSet& iConfig):

  
  Ntinopt(0), Ntinobeta(0), Ntinogamma(0), hardphpt(0),softphpt(0), dihardphpt(0), disoftphpt(0), soft_hardphpt(0)

{
   //now do what ever initialization is needed

}


NeutralinoLifetimeAnalyzer::~NeutralinoLifetimeAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NeutralinoLifetimeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
NeutralinoLifetimeAnalyzer::beginJob()
{

  Service<TFileService> fs;

  Ntinopt = fs->make<TH1D>("Ntinopt", " Neutralino Pt(GeV)", 100, 0., 1000000.);
  Ntinobeta = fs->make<TH1D>("Ntinobeta", " Neutralino #Beta ", 100, -100., 100.);
  Ntinogamma = fs->make<TH1D>("Ntinogamma", "Neutralino #gamma", 100, 0., 100.);
  hardphpt   = fs->make<TH1F>("hardphpt", "High Pt Photon ", 100, 0., 1000.);
  softphpt  = fs->make<TH1F>("softphpt", "Soft Pt Photon", 100, 0., 100.);
  dihardphpt = fs->make<TH1F>("dihardphpt", "Di Hard Photon Pt", 100, 0., 1000.);
  disoftphpt = fs->make<TH1F>("disoftphpt", "Di Soft Photon Pt", 100, 0., 100.);
  soft_hardphpt = fs->make<TH1F>("soft_hardphpt", "Soft_Hard Photon pt",  100, 0., 1000);
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NeutralinoLifetimeAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
NeutralinoLifetimeAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
NeutralinoLifetimeAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
NeutralinoLifetimeAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
NeutralinoLifetimeAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NeutralinoLifetimeAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NeutralinoLifetimeAnalyzer);
