#ifndef DPAnalysis_H
#define DPAnalysis_H
// -*- C++ -*-
//
// Package:    DPAnalysis
// Class:      DPAnalysis
// 
/**\class DPAnalysis DPAnalysis.cc Exotica/DPAnalysis/src/DPAnalysis.h

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shih-Chuan Kao
//         Created:  Thu Sep 29 05:26:22 CDT 2011
// $Id: DPAnalysis.h,v 1.17 2012/09/24 22:43:13 sckao Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/eventsetuprecord_registration_macro.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

// AOD Objects
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"

#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/METReco/interface/BeamHaloSummary.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// L1 Trigger 
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

// for ECAL cluster
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include <algorithm>

// for CSC Segment
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "DataFormats/CSCRecHit/interface/CSCSegment.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"

#include "DataFormats/METReco/interface/CSCHaloData.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/MuonDetId/interface/CSCIndexer.h"

#include "Geometry/CSCGeometryBuilder/plugins/CSCGeometryESModule.h"

#include "Geometry/Records/interface/CSCRecoGeometryRcd.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"


// Calibration services
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalTools.h"
#include "CalibCalorimetry/EcalTiming/interface/timeVsAmpliCorrector.h"

// PU SummeryInfo
//#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 

#include <TMath.h>
#include "TFile.h"
#include "TTree.h"

#include "Ntuple.h"
#include "GenStudy.h"

#include <Math/VectorUtil.h>

using namespace std ;

//
// class declaration
//
typedef std::pair<reco::SuperClusterRef, float> ParticleSC  ;

struct PhoInfo {

  double t    ;
  double dt   ;
  double nchi2  ;
  double fSpike ;
  double maxSX  ;
  int    nxtals ;  
  int    nBC    ;


} ;


class DPAnalysis : public edm::EDAnalyzer {
   public:
      explicit DPAnalysis(const edm::ParameterSet&);
      ~DPAnalysis();

      virtual void analyze(const edm::Event&, const edm::EventSetup&);

      bool EventSelection( const edm::Event& iEvent );

      void CSCHaloCleaning( const edm::Event& iEvent, vector<const reco::Photon*>& selectedPhotons )  ;

      bool L1TriggerSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup ) ;

      void TriggerTagging( edm::Handle<edm::TriggerResults> triggers, const edm::TriggerNames& trgNameList, int RunID, vector<int>& firedTrig ) ;
      bool TriggerSelection( edm::Handle<edm::TriggerResults> triggers, vector<int> firedTrig ) ;
      //bool TriggerSelection( const edm::Event& iEvent, int RunID ) ;
 
      template<typename object>
      bool GetTrgMatchObject( object, const edm::Event& iEvent, edm::InputTag inputProducer_ ) ;

      bool VertexSelection( edm::Handle<reco::VertexCollection> vtx ) ;

      bool PhotonSelection(  edm::Handle<reco::PhotonCollection> photons, edm::Handle<EcalRecHitCollection> recHitsEB, edm::Handle<EcalRecHitCollection> recHitsEE, edm::Handle<reco::TrackCollection> tracks, vector<const reco::Photon*>& selectedPhotons ) ;

      pair<double,double> ClusterTime( reco::SuperClusterRef scRef, edm::Handle<EcalRecHitCollection> recHitsEB, edm::Handle<EcalRecHitCollection> recHitsEE ) ;
      void ClusterTime( reco::SuperClusterRef scRef, edm::Handle<EcalRecHitCollection> recHitsEB, edm::Handle<EcalRecHitCollection> recHitsEE, PhoInfo& phoTmp, bool useAllClusters = false ) ;
      //void ClusterTime( reco::SuperClusterRef scRef, edm::Handle<EcalRecHitCollection> recHitsEB, edm::Handle<EcalRecHitCollection> recHitsEE, double& aveTime, double& aveTimeErr, double& nChi2, bool useAllClusters = false ) ;

      //double HLTMET( edm::Handle<reco::PFJetCollection> jets, vector<const reco::Muon*>& selectedMuons, bool addMuon = false ) ;

      bool JetSelection( edm::Handle<reco::PFJetCollection> jets, vector<const reco::Photon*>& selectedPhotons,
                                                                     vector<const reco::PFJet*>& selectedJets ) ;
      bool ElectronSelection( edm::Handle<reco::GsfElectronCollection> electrons, 
                              vector<const reco::GsfElectron*>& selectedElectrons ) ;
      bool MuonSelection( edm::Handle<reco::MuonCollection> muons, vector<const reco::Muon*>& selectedMuons ) ;
      void PrintTriggers( const edm::Event& iEvent ) ;

      bool sMinorSelection( vector<const reco::Photon*>& selectedPhotons,  edm::Handle<EcalRecHitCollection> recHitsEB,     
                              edm:: Handle<EcalRecHitCollection> recHitsEE ) ;

      bool IsoPhotonSelection( vector<const reco::Photon*>& selectedPhotons ) ; 

      bool GammaJetVeto( vector<const reco::Photon*>& selectedPhotons, vector<const reco::PFJet*>& selectedJets) ;

      bool BeamHaloMatch( edm::Handle<CSCSegmentCollection> cscSeg, vector<const reco::Photon*>& selectedPhotons, const edm::EventSetup& iSetup ) ;

   private:

      Ntuple leaves ;

      TTree *theTree;

      TFile *theFile;
      GenStudy *gen ; 

      // ----------member data ---------------------------
      string rootFileName;
      std::vector<string> triggerPatent ;
      bool isData ;
      bool L1Select ;
      string l1GTSource ;

      edm::InputTag trigSource;
      edm::InputTag trigEvent;
      edm::InputTag pvSource;
      edm::InputTag beamSpotSource;
      edm::InputTag muonSource;
      edm::InputTag electronSource;
      edm::InputTag photonSource;
      edm::InputTag metSource;
      edm::InputTag jetSource;
      edm::InputTag trackSource;

      edm::InputTag EBRecHitCollection;
      edm::InputTag EERecHitCollection;
      edm::InputTag CSCSegmentTag ;
      edm::InputTag cscHaloTag ;
      //edm::InputTag pileupSource ;

      edm::ESHandle<EcalIntercalibConstants> ical;
      edm::ESHandle<EcalADCToGeVConstant> agc;
      edm::ESHandle<EcalLaserDbService> laser;
      edm::ESHandle<CaloGeometry> pGeometry ;
      const CaloGeometry * theGeometry ;

      std::vector<double> muonCuts ;
      std::vector<double> electronCuts ;
      std::vector<double> photonCuts ;
      std::vector<double> photonIso ;
      std::vector<double> metCuts ;
      std::vector<double> jetCuts ; 
      std::vector<double> vtxCuts ; 

      std::vector<const reco::PFJet*> selectedJets ;
      std::vector<const reco::GsfElectron*> selectedElectrons ;
      std::vector<const reco::Muon*> selectedMuons ;
      std::vector<const reco::Photon*> selectedPhotons ;

      bool passEvent ;
      int counter[10] ; 
      float sMin_ ;
      int runID_ ;

      timeCorrector theTimeCorrector_;
      edm::Timestamp eventTime ;

      std::vector<int> firedTrig ;
      int targetTrig ;
      //std::vector<int> firedTrigID ;
      ///string TriggerName ;
      bool passL1 ;
      bool passHLT ;


      bool debugT ; 
};

#endif
