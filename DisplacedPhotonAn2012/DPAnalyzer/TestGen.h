#ifndef TestGen_H
#define TestGen_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <TMath.h>
#include <TF1.h>
#include <TH1.h>
#include <TProfile.h>
#include <TH2.h>
#include <THStack.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TLeaf.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TLorentzVector.h"
#include <Math/VectorUtil.h>
#include "AnaInput.h"

#define MAXPHO 10
#define MAXOBJ 10
#define MAXJET 15
#define MAXVTX 50
#define MAXGEN 20
#define MAXMU 5

#define Kappa  0.193366133727   // Defination of Constant R/2C  From CMS TDR R = 1.29m and C = 299792458 m/s

class TestGen : public TObject {

public:

   TestGen( string datacardfile = "DataCard.txt");     
   ~TestGen();     
   
   void ReadTree( string dataName );
   void Writehists();
   void InitHist();
   void Make_Plots();
   float GetHaloTime( double gEta);  // calculated Halo Time
   bool IsGammaJetEvent(TLorentzVector jp4, TLorentzVector phop4, int jm, int phm );  // GammaJetEven Selection 

  // make Output Root file
//  TFile* f ;
  TDirectory* neut ; 

  // Initialize Histograms:
  // Define a  Struct to Hold all Histograms and Output file
  
struct kin_hist {
   TH1D* h_Time;
   TH1D* h_g1Pt ;
   TH1D* WAveSeedBCphotime; 
   TH1D* AveSCphotime; 
   TH1D* evt_met ;
   TH1D* ph_smin ;
   TH1D* ph_smaj; 
   TH1D* ph_e ;
   TH1D* ph_z ;
   TH1D* ph_eta ;
   TH1D* ph_phi;
   TH1D* jet_eta;
   TH1D* jet_phi;
   TH1D* jp_deta;
   TH1D* jp_dphi;
   TH1D* njets ;
   TH1D* npho ;
   TH1D* j_pt ;
   TH1D* ph_HoverE ;
   TH1D* mettheta ;
   TH1D* phomet_thetadiff;
   TH1D* MassNt;  
   TH1D* pho_angle;
   TH1D* pho_EcalIso;
   TH1D* pho_HcalIso;
//   TH1D* hcal_Iso;
   TH1D* pho_TrkIso;
   TH1D* pu_vtx; 
   TH2D* phoTimeVsEta; 
   TH2D* phoTimeVsE; 
   TH2D* phoTimeVsPhi;
 
   TH2D* metVsPU;
   TH2D* photimeVsPU;
   TH2D* pho_Ecal_IsoVsPU;
   TH2D* pho_Trk_IsoVsPU;
   TH2D* pho_Hcal_IsoVsPU;
   TH2D* Hcal_IsoVsPU;
   TH2D* sMinorVsPU;
   TH1D *phoCSCtime, *pho_CSCdphi, *phonBC, *phonXtal, *phopzOnpt, *phosigmaietaieta, *halo_phodrho,*halo_phodphi, *pho_halodphi, *pho_halodrho;
   TH2D* phoetaVsphi;
   TH2D* kpho_timeVsEta, *kpho_timeVsPhi; 
   TH1D* kpho_time, *pho_num_phoEB, *pho_num_jetEB, *pho_num_phoEE, *pho_num_jetEE;
   TH1D* pho_LN2timeEB, *pho_LN2GP2timeEB,*pho_GP2timeEB;
   TH1D* pho_LN2timeEE, *pho_LN2GP2timeEE,*pho_GP2timeEE;
   TH2D *pho_timeVsCSCdphi;     
   //EB and EE
   TH1D *pho_sigmaEtaEB, *pho_sigmaEtaEE, *pho_sminorEB, *pho_sminorEE, *pho_smajorEB, *pho_smajorEE;
   TH2D *pho_timeVsEtaEB,*pho_timeVsEtaEE, *pho_timeVsPhiEB, *pho_timeVsPhiEE; TH1D *pho_timeEB, *pho_timeEE;
   TH1D *pho_ATG2_smajorEB, *pho_ATG2_smajorEE, *pho_ATG2_sminorEB, *pho_ATG2_sminorEE, *pho_ATG2sminorEB, *pho_ATG2_sigmaEtaEB, *pho_ATG2_sigmaEtaEE;
  // Init Vertices Histograms
  TH1D *py1,*py2,*py3,*py4,*py5,*py6,*py7,*py8, *py9,*py10, *py11, *py12,*py13,*py14,*py15,*py16,*py17,*py18,*py19; 
 // Time Vs NVtx plots
  TH1D *tV1, *tV2, *tV3, *tV4, *tV5, *tV6, *tV7, *tV8, *tV9, *tV10, *tV11, *tV12, *tV13, *tV14, *tV15, *tV16, *tV17, *tV18, *tV19, *tV20, *tV21, *tV22;
  TProfile *HcalIso, *trkIso, *hcalIso, *ecalIso, *sminor;
};

struct Halogamma {
TH2D *halo_etaVsphi, *halo_etaVsStime,*halo_etaVsBCtime, *halo_etaVsSCtime, *halo_phiVsStime, *halo_phiVsBCtime, *halo_phiVsSCtime, *halo_rhoVsphi;

TH1D *halo_pzOnpt, *halo_nBC, *halo_nXtal, *halo_rho, *halo_phi, *halo_sigmaietaieta, *halo_phonBCratio, *halo_phonXtalratio, *halo_TrksSbeta, *halo_nhalosegs,*halo_nOThits, *halo_nhalotrk,*halo_seedTime,*halo_wavBCtime, *halo_wavSCtime, *Rhalo_Time,*halo_smin, *halo_smaj;

// Halo Events with |t| < 2ns EB and EE -with removed ECAL Halo Tagging
TH1D *halo_sigmaEtaEB, *halo_sigmaEtaEE, *halo_sminorEB, *halo_sminorEE, *halo_smajorEB, *halo_smajorEE;
TH2D *khalo_timeVsEta, *khalo_timeVsPhi;
TH1D *khalo_time;
TH1D *halo_timeEB, *halo_timeEE, *halo_num_phoEB, *halo_num_phoEE, *halo_num_jetEB, *halo_num_jetEE;
TH1D *halo_CSCdphi;
TH2D *halo_timeVsCSCdphi;
TH2D *halo_timeVsEtaEB, *halo_timeVsEtaEE, *halo_timeVsPhiEB, *halo_timeVsPhiEE;
TH1D* halo_LN2timeEB, *halo_LN2GP2timeEB,*halo_GP2timeEB;
TH1D* halo_LN2timeEE, *halo_LN2GP2timeEE,*halo_GP2timeEE;
TH1D* halo_ATG2_smajorEB, *halo_ATG2_smajorEE, *halo_ATG2_sminorEB, *halo_ATG2_sminorEE, *halo_ATG2_sigmaEtaEB, *halo_ATG2_sigmaEtaEE;
   
};

// Strange Events 
struct ltimeEvt { 
// Large Time Events
TH1D *ltvtxX, *ltvtxY, *ltvtxZ, *lteta, *ltphi, *ltEvtmet, *ltEvtpt,*ltnjets,*ltnpho,*ltnvtx, *ltphoE ;
};

struct svtxEvt {
// Single vertex events
TH1D *svtxX, *svtxY, *svtxZ, *svtxeta, *svtxphi, *svtxEvtmet, *svtxEvtpt, *svtxnjets, *svtxnpho,*svtxnvtx ;
};

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;

  // For MC Events
   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], phoHoverE[MAXPHO] , timeChi2[MAXPHO], aveTime1[MAXPHO], aveTime[MAXPHO];
   float seedTime[MAXPHO],seedTimeErr[MAXPHO],aveTimeErr[MAXPHO],aveTimeErr1[MAXPHO], phoEta[MAXPHO],phoPhi[MAXPHO];
   float jetPx[MAXJET],jetPy[MAXJET],jetPz[MAXJET], jetE[MAXJET];
 
   float sigmaEta[MAXPHO], sigmaIeta[MAXPHO]; 
   int   nXtals[MAXPHO],nBC[MAXPHO] ;
 
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO]; // HcalIso[MAXPHO];
   float phoTrkIso[MAXPHO], sMinPho[MAXPHO],sMajPho[MAXPHO];
 
   float fSpike[MAXPHO], maxSwissX[MAXPHO], seedSwissX[MAXPHO], dR_TrkPho[MAXPHO] ;
   int   nGen, nPhotons; 
   int   nJets;
   int  nMuons, nElectrons, triggered, nVertices, totalNVtx; 
   int eventId;

   float met;
   float metPx, metPy; 
   float muE[MAXMU];
   float vtxDx[MAXVTX],vtxDy[MAXVTX],vtxDz[MAXVTX];
  
   int   jetCM[MAXJET], jetNDau[MAXJET];
   float jetCEF[MAXJET], jetNHF[MAXJET], jetCHEF[MAXJET], jetEta[MAXJET]; 

     

// Halo infos
    float cscTime[MAXPHO]; 
    float cscdPhi[MAXPHO];
//    int nTrksSmallBeta, nHaloSegs ;

    bool IscscHaloSeg_Tag, IscscHaloTrk_Tag, IsBeamHaloIDTightTag, IscscHaloTight_Tag;

 //   int nOutTimeHits, nHaloTracks ;

    float haloPhi, haloRho;

   float vtxX[MAXVTX],vtxY[MAXVTX],vtxZ[MAXVTX], vtxChi2[MAXVTX],vtxNdof[MAXVTX];

   vector<double> jetCuts ;
   vector <int>   trigCut ;
   vector <double> photonCuts;
   vector <double> metCut; 
   vector <double> HaloCuts; 
   vector <double> photonIso; 
   vector <double> JetIdCuts; 
   //ClassDef(TestGen, 1);


};

//#if !defined(__CINT__)
//    ClassImp(TestGen);
#endif

