#include "TestGen.h"


// struct of hists and files
TestGen::kin_hist my;    // Struct holds all Kinematics plots and files

TestGen::ltimeEvt Lt;    // Large time >= 10ns Evts

TestGen::svtxEvt  Sv;    // Single Vertex Evts

TestGen::Halogamma Hg;  // Halo Gamma Gamma Evts

TFile *f = new TFile("TodayPhoton_Eta_Studies_DP_Trig_NoJetID.root","recreate");

TestGen::TestGen( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("JetCuts",       &jetCuts );
  Input->GetParameters("TrigCut",       &trigCut );
  Input->GetParameters("photonCuts",    &photonCuts);
  Input->GetParameters("MetCuts",       &metCut);
  Input->GetParameters("HaloCuts",      &HaloCuts);
  Input->GetParameters("photonIso",      &photonIso);
  Input->GetParameters("JetIdCuts",      &JetIdCuts);
}

TestGen::~TestGen(){

  delete Input ;
  cout<<" done ! "<<endl ;

}

//Function to Initialize Histograms
void TestGen::InitHist() {

    my.h_Time  = new TH1D("my.h_Time", "Photon Time(ns)", 500,  -50.0, 50.0);
    my.h_g1Pt  = new TH1D("my.h_g1Pt", "Leading Photon Pt(GeV) ", 200,  0, 2000);
    my.WAveSeedBCphotime  = new TH1D("my.WAveSeedBCphotime", "Photon (W Ave Seed BC) Time(ns)", 500,  -50.0, 50.0);
    my.AveSCphotime  = new TH1D("my.AveSCphotime", "Photon (W Ave SC) Time(ns)", 500,  -50.0, 50.0);
    my.evt_met = new TH1D("my.evt_met", "Missing Energy(GeV)", 200, 0, 2500);
    my.ph_smin = new TH1D("my.ph_smin", "Shower Width in dxn of Minor Axis of Ecl Cluster", 100, 0,5);
    my.ph_smaj = new TH1D("my.ph_smaj", "Shower Width in dxn of Major Axis of Ecal Cluster", 100,0, 5);
    my.ph_e = new TH1D("my.ph_e","Leading Photon Energy(GeV)", 200, 0, 2000);
    my.ph_z = new TH1D("my.ph_z", "Z Vextex Position of Photon(cm)", 4000, -2000.0, 2000.0);
    my.ph_eta = new TH1D("my.ph_eta","Leading Photon #eta", 100, -3.0, 3.0);
    my.ph_phi = new TH1D("my.ph_phi", "Leading Photon #phi", 100, -3.142, 3.142);
    my.jet_eta = new TH1D("my.jet_eta", "Leading Jet #eta", 100, -3.0, 3.0);
    my.jet_phi = new TH1D("my.jet_phi", "Leading Jet #phi", 100, -3.142, 3.142);
    my.jp_deta = new TH1D("my.jp_deta", " Leading Jet-Photo #Delta#eta", 100, -3.0, 3.0);
    my.jp_dphi = new TH1D("my.jp_dphi", "Leading Jet-Photon #Delta#phi", 100, -10, 10);
    my.njets = new TH1D("my.njets", "Number of Jets in Event", 20, 0, 20);
    my.npho = new TH1D("my.npho", "Number of #gamma s in Event", 10, 0, 10);
    my.pu_vtx = new TH1D("my.pu_vtx", "Number of PVs", 1000, 0, 50);
    my.j_pt = new TH1D("my.j_pt", " Leading Jet Pt(GeV)", 200, 0, 2000);
    my.ph_HoverE = new TH1D("my.ph_HoverE", "Photon Hadronic Energy Over EM Energy Ratio", 5, 0.0, 5.0);
    my.mettheta  =  new TH1D("my.mettheta", " Agular Distribution of supposed Gravitino", 200, -10.0, 10.0);
    my.phomet_thetadiff = new TH1D("my.phomet_thetadiff", "Photon-Met Angular Distrubution", 200, -10.0, 10.0);
    my.MassNt  = new TH1D("my.MassNt", "Neutralino Transverse Mass Distribution(GeV)", 250, 0.0, 2500.0);
    my.pho_angle = new TH1D("my.pho_angle","Photon Angular Distribution(Radians)", 200, -10.0, 10.0);
    my.metVsPU = new TH2D("my.metVsPU","Effect of PU on MET",100, 0, 40, 200, 0,2500);
    my.photimeVsPU = new TH2D("my.photimeVsPU","No. PV Vs Photon Time",100, 0, 400, 500, -50.0, 50.0);
    my.pho_Ecal_IsoVsPU = new TH2D("my.phoEcal_IsoVsPU","EcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.pho_Trk_IsoVsPU = new TH2D("my.phoTrk_IsoVsPU","TrackIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.pho_Hcal_IsoVsPU = new TH2D("my.phoHcal_IsoVsPU","HcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
//    my.Hcal_IsoVsPU = new TH2D("my.Hcal_IsoVsPU","2012 HcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.sMinorVsPU = new TH2D("my.sMinorVsPU","sMinor Vs PU", 100, 0.0, 40.0, 100, 0.0, 1.0); 

    my.phoTimeVsEta = new TH2D("my.phoTimeVsEta","Photon Time Vs Eta",100, -3.0, 3.0, 500, -50.0, 50.0);
    my.phoTimeVsE = new TH2D("my.phoTimeVsE","Photon Time Vs Energy", 400, 0.0, 4000.0, 500, -50.0, 50.0);
    my.phoTimeVsPhi = new TH2D("my.phoTimeVsPhi","Photon Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0); 
// Photon Iso studies    
   my.pho_EcalIso = new TH1D("my.pho_EcalIso","Photon EcalIso", 100, 0.0, 10.0);
   my.pho_HcalIso = new TH1D("my.pho_HcalIso", "Photon HcalIso", 100, 0.0, 10.0);
//   my.hcal_Iso    = new TH1D("my.hcal_Iso", "2012 Photon HcalIso", 100, 0.0, 10.0);
   my.pho_TrkIso  = new TH1D("my.pho_TrkIso","Photon Track Iso", 100, 0.0, 10.0);

// Photon 1D plots   
    my.phoCSCtime = new TH1D("my.phoCSCtime","CSC Photon time(ns)", 1000, -100.0, 100.0); 
    my.phonBC = new TH1D("my.phonBC","Photon No of  Seed Basic Clusters", 100, 0.0, 100.0);
    my.phonXtal = new TH1D("my.phonXtal","Photon No. Of Crys ", 200, 0.0, 100.0);
//    my.phopzOnpt = new TH1D("my.phopzOnpt","Ratio of Photon Pz/Pt ", 100, 0.0, 10000.0);
//    my.phosigmaietaieta = new TH1D("my.phosigmaietaieta","Photon #sigma_{i#eta,i#eta}", 200, 0.0, 100.0);
    my.phoetaVsphi = new TH2D("my.phoetaVsphi","#eta_{#gamma} Vs #phi_{#gamma} ", 100, -3.0, 3.0, 100, -3.50, 3.50);
    
    my.pho_timeVsEtaEB = new TH2D("my.pho_timeVsEtaEB","Photon Time Vs Eta EB",100, -3.0, 3.0, 500, -50.0, 50.0);
    my.pho_timeVsEtaEE = new TH2D("my.pho_timeVsEtaEE","Photon Time Vs Eta EE",100, -3.0, 3.0, 500, -50.0, 50.0);  
    my.pho_timeVsPhiEB = new TH2D("my.pho_timeVsPhiEB","Photon Time Vs Phi EB",100, -3.5, 3.5, 500, -50.0, 50.0); 
    my.pho_timeVsPhiEE = new TH2D("my.pho_timeVsPhiEE","Photon Time Vs Phi EE",100, -3.5, 3.5, 500, -50.0, 50.0); 
    my.pho_timeEB  = new TH1D("my.pho_timeEB", "Photon Time(ns) EB", 500,  -50.0, 50.0);
    my.pho_timeEE  = new TH1D("my.pho_timeEE", "Photon Time(ns) EE", 500,  -50.0, 50.0);
    my.pho_sminorEB = new TH1D("my.pho_sminorEB", "SMinor EB", 100, 0,5);
    my.pho_smajorEB = new TH1D("my.pho_smajorEB", "SMajor EB", 100,0, 5);
    my.pho_sigmaEtaEB = new TH1D("my.pho_sigmaEtaEB", "Photon #sigma_{#eta,#eta} EB", 20,0, 10);
    my.pho_sminorEE = new TH1D("my.pho_sminorEE", "SMinor EE", 20, 0,5);
    my.pho_smajorEE = new TH1D("my.pho_smajorEE", "SMajor EE", 20,0, 5);
    my.pho_sigmaEtaEE = new TH1D("my.pho_sigmaEtaEE", "Photon #sigma_{#eta,#eta} EE", 20,0, 10);
    my.pho_timeVsCSCdphi = new TH2D("my.pho_timeVsCSCdphi","Photon Time Vs CSC |#delta #phi|",700, -3.50, 3.50, 500, -50.0, 50.0); 
    my.pho_CSCdphi = new TH1D("my.pho_CSCdphi","#gamma |#delta #phi|",700, -3.50, 3.50);    
    my.pho_num_jetEB = new TH1D("my.pho_num_jetEB", "Number of EB Jets ", 20, 0, 20);
    my.pho_num_phoEB = new TH1D("my.pho_num_phoEB", "Number of EB #gamma s ", 10, 0, 10);
    my.pho_num_jetEE = new TH1D("my.pho_num_jetEE", "Number of EE Jets ", 20, 0, 20);
    my.pho_num_phoEE = new TH1D("my.pho_num_phoEE", "Number of EE #gamma s ", 10, 0, 10);
    my.pho_LN2timeEB  = new TH1D("my.pho_LN2timeEB", "Photon Time < -2ns EB", 500,  -50.0, 50.0);
    my.pho_LN2timeEE  = new TH1D("my.pho_LN2timeEE", "Photon Time < -2ns EE", 500,  -50.0, 50.0);
    my.pho_LN2GP2timeEB  = new TH1D("my.pho_LN2GP2timeEB", "-2ns < Photon Time < 2ns EB", 500,  -50.0, 50.0);
    my.pho_LN2GP2timeEE  = new TH1D("my.pho_LN2GP2timeEE", "-2ns < Photon Time < 2ns EE", 500,  -50.0, 50.0);
    my.pho_GP2timeEB  = new TH1D("my.pho_GP2timeEB", "Photon Time > 2ns EB", 500,  -50.0, 50.0);
    my.pho_GP2timeEE  = new TH1D("my.pho_GP2timeEE", "Photon Time > 2ns EE", 500,  -50.0, 50.0);
    my.pho_ATG2_smajorEB = new TH1D("my.pho_ATG2_smajorEB", "SMajor EB |Time| > 2ns", 100,0, 5);
    my.pho_ATG2_smajorEE = new TH1D("my.pho_ATG2_smajorEE", "SMajor EE |Time| > 2ns", 100,0, 5);
    my.pho_ATG2_sminorEB = new TH1D("my.pho_ATG2_sminorEB", "SMinor EB |Time| > 2ns", 100, 0,5);
    my.pho_ATG2_sminorEE = new TH1D("my.pho_ATG2_sminorEE", "SMinor EE |Time| > 2ns", 100, 0,5);
    my.pho_ATG2_sigmaEtaEB = new TH1D("my.pho_ATG2_sigmaEtaEB", "#sigma_{#eta,#eta} EB |Time| > 2ns", 20,0, 10);
    my.pho_ATG2_sigmaEtaEE = new TH1D("my.pho_ATG2_sigmaEtaEE", "#sigma_{#eta,#eta} EE |Time| > 2ns", 20,0, 10);
    

    my.halo_phodrho = new TH1D("my.halo_phodrho"," #delta#rho of 0.4 Halo Muon & Photon",100, 0.0, 10.0);
    my.halo_phodphi = new TH1D("my.halo_phodphi"," #delta#phi of 0.4 Muon & Photon",100, -3.50, 3.50);
    my.pho_halodphi = new TH1D("my.pho_halodphi"," #delta#phi of CSC Seg & Photon",100, -3.50, 3.50);
    my.pho_halodrho = new TH1D("my.pho_halodrho"," #delta#rho of CSC Seg & Photon",100, -3.50, 3.50);
// Halo Plots
    Hg.halo_etaVsphi = new TH2D("Hg.halo_etaVsphi","Halo #gamma  #eta Vs #phi",100, -3.0, 3.0, 100, -3.50, 3.50); 
    Hg.halo_phiVsStime = new TH2D("Hg.halo_phiVsStime","Halo Photon Seed Xtal Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_phiVsBCtime = new TH2D("Hg.halo_phiVsBCtime","Halo Photon W.Ave BC Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_phiVsSCtime = new TH2D("Hg.halo_phiVsSCtime","Halo Photon W.Ave SC Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_etaVsStime = new TH2D("Hg.halo_etaVsStime","Halo Photon Eta Vs Seed Xtal Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_etaVsBCtime = new TH2D("Hg.halo_etaVsBCtime","Halo Photon Eta Vs W.Ave BC Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_etaVsSCtime = new TH2D("Hg.halo_etaVsSCtime","Halo Photon Eta Vs W.Ave SC Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_rhoVsphi = new TH2D("Hg.halo_rhoVsphi","Halo Photon #rho Vs #phi",100, 0.0, 5.0, 100, -3.5, 3.5);
  // 1 d plots 
//  Hg.halo_pzOnpt = new TH1D("Hg.halo_pzOnpt","Ratio(Pz/Pt) of Halo Photon ",100, 0.0, 10000.0);
  Hg.halo_nBC = new TH1D("Hg.halo_nBC","No Basic Clusters of Halo Photon",100, 0.0, 100.0);
  Hg.halo_nXtal = new TH1D("Hg.halo_nXtal","No Crys in Halo Photon",100, 0.0, 100.0);
  Hg.halo_rho = new TH1D("Hg.halo_rho","Halo #gamma  #rho",100, 0.0, 10.0);
  Hg.halo_phi = new TH1D("my.halo_phi","Halo #gamma #phi",100, -3.50, 3.50);
//  Hg.halo_sigmaietaieta = new TH1D("Hg.halo_sigmaietaieta","#sigma_{i#eta,i#eta} of Halo Photon",1000, 0.0, 10.0);
 // Hg.halo_phonBCratio = new TH1D("Hg.halo_phonBCratio","Ratio of No. Halo Photon to Photon Basic Clusters",100, 0.0, 10.0);
//  Hg.halo_phonXtalratio = new TH1D("Hg.halo_phonXtalratio","Ratio of Halo Photon to Photon No. Crys",100, 0.0, 10.0);
  
 Hg.halo_seedTime  = new TH1D("Hg.halo_seedTime","Halo #gamma Seed Crys Time",500, -50.0, 50.0);
 Hg.halo_wavBCtime = new TH1D("Hg.halo_wavBCtime","Halo #gamma W.Av BC Time",500, -50.0, 50.0);
 Hg.halo_wavSCtime = new TH1D("Hg.halo_wavSCtime","Halo #gamma W.Av SC Time",500, -50.0, 50.0);    
 Hg.halo_timeVsEtaEB = new TH2D("Hg.halo_timeVsEtaEB","Halo #gamma Time Vs #eta EB",100, -3.0, 3.0, 500, -50.0, 50.0);
 Hg.halo_timeVsEtaEE = new TH2D("Hg.halo_timeVsEtaEE","Halo #gamma Time Vs #eta EE",100, -3.0, 3.0, 500, -50.0, 50.0);  
 Hg.halo_timeVsPhiEB = new TH2D("Hg.halo_timeVsPhiEB","Halo #gamma Time Vs #phi EB",100, -3.5, 3.5, 500, -50.0, 50.0); 
 Hg.halo_timeVsPhiEE = new TH2D("Hg.halo_timeVsPhiEE","Halo #gamma Time Vs #phi EE",100, -3.5, 3.5, 500, -50.0, 50.0); 
 Hg.halo_timeEB  = new TH1D("Hg.halo_timeEB", "Halo #gamma Time(ns) EB", 500,  -50.0, 50.0);
 Hg.halo_timeEE  = new TH1D("Hg.halo_timeEE", "Halo #gamma Time(ns) EE", 500,  -50.0, 50.0);
 Hg.halo_sminorEB = new TH1D("Hg.halo_sminorEB", "Halo #gamma SMinor EB", 100, 0,5);
 Hg.halo_smajorEB = new TH1D("Hg.halo_smajorEB", "Halo #gamma SMajor EB", 100,0, 5);
 Hg.halo_sigmaEtaEB = new TH1D("Hg.halo_sigmaEtaEB", "Halo #gamma #sigma_{#eta,#eta} EB", 20,0, 10);
 Hg.halo_sminorEE = new TH1D("Hg.halo_sminorEE", "Halo #gamma SMinor EE", 20, 0,5);
 Hg.halo_smajorEE = new TH1D("Hg.halo_smajorEE", "Halo #gamma SMajor EE", 20,0, 5);
 Hg.halo_sigmaEtaEE = new TH1D("Hg.halo_sigmaEtaEE", "Halo #gamma #sigma_{#eta,#eta} EB", 20,0, 10);
 Hg.halo_timeVsCSCdphi = new TH2D("Hg.halo_timeVsCSCdphi","Halo #gamma Time Vs CSC |#delta #phi|",100, -3.50, 3.50, 500, -50.0, 50.0); 
 Hg.halo_CSCdphi = new TH1D("Hg.halo_CSCdphi"," Halo #gamma |#delta #phi|",100, -3.50, 3.50);  
 Hg.halo_num_jetEB = new TH1D("Hg.halo_num_jetEB", "Number of EB Jets ", 20, 0, 20);
 Hg.halo_num_phoEB = new TH1D("Hg.halo_num_phoEB", "Number of EB #gamma s ", 10, 0, 10);
 Hg.halo_num_jetEE = new TH1D("Hg.halo_num_jetEE", "Number of EE Jets ", 20, 0, 20);
 Hg.halo_num_phoEE = new TH1D("Hg.halo_num_phoEE", "Number of EE #gamma s ", 10, 0, 10);
 Hg.halo_LN2timeEB  = new TH1D("Hg.halo_LN2timeEB", "Photon Time < -2ns EB", 500,  -50.0, 50.0);
 Hg.halo_LN2timeEE  = new TH1D("Hg.halo_LN2timeEE", "Photon Time < -2ns EE", 500,  -50.0, 50.0);
 Hg.halo_LN2GP2timeEB  = new TH1D("Hg.halo_LN2GP2timeEB", "-2ns < Photon Time < 2ns EB", 500,  -50.0, 50.0);
 Hg.halo_LN2GP2timeEE  = new TH1D("Hg.halo_LN2GP2timeEE", "-2ns < Photon Time < 2ns EE", 500,  -50.0, 50.0);
 Hg.halo_GP2timeEB  = new TH1D("Hg.halo_GP2timeEB", "Photon Time > 2ns EB", 500,  -50.0, 50.0);
 Hg.halo_GP2timeEE  = new TH1D("Hg.halo_GP2timeEE", "Photon Time > 2ns EE", 500,  -50.0, 50.0);
 Hg.halo_ATG2_smajorEB = new TH1D("Hg.halo_ATG2_smajorEB", "SMajor EB |Time| > 2ns", 100,0, 5);
 Hg.halo_ATG2_smajorEE = new TH1D("Hg.halo_ATG2_smajorEE", "SMajor EE |Time| > 2ns", 100,0, 5);
 Hg.halo_ATG2_sminorEB = new TH1D("Hg.halo_ATG2_sminorEB", "SMinor EB |Time| > 2ns", 100, 0,5);
 Hg.halo_ATG2_sminorEE = new TH1D("Hg.halo_ATG2_sminorEE", "SMinor EE |Time| > 2ns", 100, 0,5);
 Hg.halo_ATG2_sigmaEtaEB = new TH1D("Hg.halo_ATG2_sigmaEtaEB", "#sigma_{#eta,#eta} EB |Time| > 2ns", 20,0, 10);
 Hg.halo_ATG2_sigmaEtaEE = new TH1D("Hg.halo_ATG2_sigmaEtaEE", "#sigma_{#eta,#eta} EE |Time| > 2ns", 20,0, 10);
    
 Hg.halo_TrksSbeta = new TH1D("Hg.halo_TrksSbeta","Halo Tracks With Small Beta", 100, 0.0, 100);
 Hg.halo_nhalosegs = new TH1D("Hg.halo_nhalosegs","Number Halo Segments",100, 0.0, 10.0);
 Hg.halo_nOThits = new TH1D("Hg.halo_nOThits","Number of OutOfTime Halo Hits",100, 0.0, 100);
 Hg.halo_nhalotrk = new TH1D("Hg.halo_nhalotrk","Number of Halo Track",100, 0.0, 100);

// Define Large Time Events
  Lt.ltvtxX = new TH1D("Lt.ltvtxX","-10.0 < PhotonTime(ns) < 10.0  X Vertex Distribution", 500, -50.0, 50.0);
  Lt.ltvtxY = new TH1D("Lt.ltvtxY","-10.0 < PhotonTime(ns) < 10.0 Y Vertex Distribution", 500, -50.0, 50.0);
  Lt.ltvtxZ = new TH1D("Lt.ltvtxZ","-10.0 < PhotonTime(ns) < 10.0  Z Vertex Distribution", 500, -50.0, 50.0);
  Lt.ltnjets = new TH1D("Lt.ltnjets","-10.0 < PhotonTime(ns) < 10.0  Number of Jets", 20, 0.0, 20.0);
  Lt.ltnpho = new TH1D("Lt.ltnpho","-10.0 < PhotonTime(ns) < 10.0  Number of #gamma", 10, 0.0, 10.0);
  Lt.ltEvtmet = new TH1D("Lt.ltEvtmet","-10.0 < PhotonTime(ns) < 10.0  MET Distribution", 200, 0.0, 2500.0);
  Lt.ltEvtpt = new TH1D("Lt.ltEvtpt","-10.0 < PhotonTime(ns) < 10.0  Leading #gamma Pt Distribution", 200, 0.0, 2500.0);  
  Lt.ltphoE = new TH1D("Lt.ltphoE","-10.0 < PhotonTime(ns) < 10.0  Leading #gamma Energy Distribution", 400, 0.0, 4000.0);  
  Lt.lteta = new TH1D("Lt.lteta","-10.0 < PhotonTime(ns) < 10.0 Leading #gamma #eta Distribution", 100, -3.0, 3.0);
  Lt.ltphi = new TH1D("Lt.ltphi","-10.0 < PhotonTime(ns) < 10.0 Leading #gamma #phi Distribution", 100, -4.0, 4.0);
  Lt.ltnvtx = new TH1D("Lt.ltnvtx","-10.0 < PhotonTime(ns) < 10.0  Number of Vertices", 50, 0.0, 50.0);
  
        
// Define Single Vertex Events
  Sv.svtxX = new TH1D("Sv.svtxX","X Single Vertex Distribution", 1000, -50.0, 50.0);
  Sv.svtxY = new TH1D("Sv.svtxY","Y Single Vertex Distribution", 1000, -50.0, 50.0);
  Sv.svtxZ = new TH1D("Sv.svtxZ","Z Single Vertex Distribution", 1000, -50.0, 50.0);
  Sv.svtxnjets = new TH1D("Sv.svtxnjets","Number of Jets in Single Vertex Events", 20, 0.0, 20.0);
  Sv.svtxnpho = new TH1D("Sv.svtxnpho","Number of #gamma in Single Vertetx Events", 10, 0.0, 10.0);
  Sv.svtxEvtmet = new TH1D("Sv.svtxEvtmet","MET Distribution in Single Vertex Events", 200, 0.0, 2500.0);
  Sv.svtxEvtpt = new TH1D("Sv.svtxEvtpt","Leading #gamma Pt Distribution in Single Vertex Events", 200, 0.0, 2500.0);  
  Sv.svtxeta = new TH1D("Sv.svtxeta","Leading #gamma #eta Distribution in Single Vertex Events", 100, -3.0, 3.0);
  Sv.svtxphi = new TH1D("Sv.svtxtphi","Leading #gamma #phi Distribution in Single Vertex Events", 100, -4.0, 4.0);
  Sv.svtxnvtx = new TH1D("Sv.svtxnvtx","Number of Vertices ", 50, 0.0, 50.0);

// Seed Time Vs nVtx dists
  my.tV1 = new TH1D("my.tV1", "0<= nVtx< 5 Photon ( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
  my.tV2 = new TH1D("my.tV2", "5< nVtx <= 10 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
  my.tV3 = new TH1D("my.tV3", "10 < nVtx <=15 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
  my.tV4 = new TH1D("my.tV4", "15 < nVtx <= 20 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
  my.tV5 = new TH1D("my.tV5", "20< nVtx <=25 Photon(Seed Xtal) Timing(Seed Xtal) Dist", 500, -25.0, 25.0);
  my.tV6 = new TH1D("my.tV6", "25 < nVtx <=30 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
  my.tV7 = new TH1D("my.tV7", "30 < nVtx <= 35 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
//  my.tV8 = new TH1D("my.tV8", "35 < nVtx<= 40 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
//  my.tV9 = new TH1D("my.tV9", "40 < nVtx <= 45 Photon(Sedd Xtal) Timing Dist", 500, -25.0, 25.0);
//  my.tV10 = new TH1D("my.tV10", "45 < nVtx <=50 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
//  my.tV11 = new TH1D("my.tV11", "50 < nVtx <=55  Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);


// W. AVe SC
  my.tV12 = new TH1D("my.tV12", "0<= nVtx <= 5 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
  my.tV13 = new TH1D("my.tV13", "5 < nVtx<=10 Photon(W.Ave SC) Timing Dist", 500, -25.0, 25.0);
  my.tV14 = new TH1D("my.tV14", "10 < nVtx<= 15 Photon(W. AVe SC) Timing Dist", 500, -25.0, 25.0);
  my.tV15 = new TH1D("my.tV15", "15 < nVtx <= 20 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
  my.tV16 = new TH1D("my.tV16", "20 < nVtx <= 25 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
  my.tV17 = new TH1D("my.tV17", "25 < nVtx <= 30 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
  my.tV18 = new TH1D("my.tV18", "30 < nVtx <= 35 Photon(W. AVe SC) Timing Dist", 500, -25.0, 25.0);
//  my.tV19 = new TH1D("my.tV19", "35 < nVtx <= 40 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
//  my.tV20 = new TH1D("my.tV20", "40 < nVtx <= 45 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
//  my.tV21 = new TH1D("my.tV21", "45 < nVtx <= 50 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
//  my.tV22 = new TH1D("my.tV22", "50 < nVtx <= 55 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);

// W AVe Seed BC
  my.py13 = new TH1D("my.py13", "45 < nVtx <= 55 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py14 = new TH1D("my.py14", "35 < nVtx <= 45  Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py15 = new TH1D("my.py15", "24 < nVtx <= 35 Photon(W. Ave  Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py16 = new TH1D("my.py16", "18 < nVtx <= 24 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py17 = new TH1D("my.py17", "12 < nVtx <= 18 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py18 = new TH1D("my.py18", "6 < nVtx <= 12 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
  my.py19 = new TH1D("my.py19", "0 <= nVtx <= 6 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);

} // End of Init Hist fuction


// Fxn 2 Write Hist
void TestGen::Writehists(){

f->cd();

neut = f->mkdir("NeutKin");
neut->cd();

my.h_g1Pt->GetXaxis()->SetTitle("Photon Pt(GeV)");
my.h_g1Pt->GetYaxis()->SetTitle("Event Number");
my.h_g1Pt->Draw();
my.h_g1Pt->Write();

my.h_Time->GetXaxis()->SetTitle("Photon Time(ns)");
my.h_Time->GetYaxis()->SetTitle("Event Number");
my.h_Time->Draw();
my.h_Time->Write();

my.WAveSeedBCphotime->GetXaxis()->SetTitle("Photon(W AVe Seed BC) Time(ns)");
my.WAveSeedBCphotime->GetYaxis()->SetTitle("Event Number");
my.WAveSeedBCphotime->Draw();
my.WAveSeedBCphotime->Write();

my.AveSCphotime->GetXaxis()->SetTitle("Photon (W Ave SC) Time(ns)");
my.AveSCphotime->GetYaxis()->SetTitle("Event Number");
my.AveSCphotime->Draw();
my.AveSCphotime->Write();


my.evt_met->GetXaxis()->SetTitle("Event MET(GeV)");
my.evt_met->GetYaxis()->SetTitle("Event Number");
my.evt_met->Draw();
my.evt_met->Write();

my.ph_smin->GetXaxis()->SetTitle("SMinor");
my.ph_smin->GetYaxis()->SetTitle("Event Number");
my.ph_smin->Draw();
my.ph_smin->Write();

my.ph_smaj->GetXaxis()->SetTitle("SMajor");
my.ph_smaj->GetYaxis()->SetTitle("Event Number");
my.ph_smaj->Draw();
my.ph_smaj->Write();

my.ph_e->GetXaxis()->SetTitle("Photon Energy(GeV)");
my.ph_e->GetYaxis()->SetTitle("Event Number");
my.ph_e->Draw();
my.ph_e->Write();

my.njets->GetXaxis()->SetTitle("Number of Jets");
my.njets->GetYaxis()->SetTitle("Event Number");
my.njets->Draw() ;
my.njets->Write();

my.pu_vtx->GetXaxis()->SetTitle("nVertices");
my.pu_vtx->GetYaxis()->SetTitle("Event Number");
my.pu_vtx->Draw() ;
my.pu_vtx->Write();

my.npho->GetXaxis()->SetTitle("Number of #gammas");
my.npho->GetYaxis()->SetTitle("Event Number");
my.npho->Draw();
my.npho->Write();

my.j_pt->GetXaxis()->SetTitle("JetPt(GeV)");
my.j_pt->GetYaxis()->SetTitle("Event Number");
my.j_pt->Draw();
my.j_pt->Write();

	
my.photimeVsPU->GetXaxis()->SetTitle("Number of Vertices");
my.photimeVsPU->GetYaxis()->SetTitle("Photon Time(ns)");
my.photimeVsPU->Draw("colz") ;
my.photimeVsPU->Write();

// Photon Iso Variables
my.pho_EcalIso->GetXaxis()->SetTitle("#gamma EcalIso");
my.pho_EcalIso->GetYaxis()->SetTitle("Event Number");
my.pho_EcalIso->Draw();
my.pho_EcalIso->Write();

my.pho_HcalIso->GetXaxis()->SetTitle("#gamma HcalIso");
my.pho_HcalIso->GetYaxis()->SetTitle("Event Number");
my.pho_HcalIso->Draw();
my.pho_HcalIso->Write();

my.pho_TrkIso->GetXaxis()->SetTitle("#gamma TrackIso");
my.pho_TrkIso->GetYaxis()->SetTitle("Event Number");
my.pho_TrkIso->Draw();
my.pho_TrkIso->Write();

//my.hcal_Iso->GetXaxis()->SetTitle("#gamma 2012 HCALIso");
//my.hcal_Iso->GetYaxis()->SetTitle("Event Number");
//my.hcal_Iso->Draw();
//my.hcal_Iso->Write();



// PU ? Plots
my.py1 = my.photimeVsPU->ProjectionY("my.py1", 0, 10);
my.py1->SetTitle("1 Vertex ");
my.py1->Draw();
my.py1->Write();

my.py2 = my.photimeVsPU->ProjectionY("my.py2", 11, 21);
my.py2->SetTitle("2 Vertices");
my.py2->Draw();
my.py2->Write();


my.py3 = my.photimeVsPU->ProjectionY("my.py3", 22, 32);
my.py3->SetTitle("3 Vertices");
my.py3->Draw();
my.py3->Write();

my.py4 = my.photimeVsPU->ProjectionY("my.py4", 33, 43);
my.py4->SetTitle("4 Vertices");
my.py4->Draw();
my.py4->Write();


my.py5 = my.photimeVsPU->ProjectionY("my.py5", 44, 54);
my.py5->SetTitle("5 Vertices");
my.py5->Draw();
my.py5->Write();


my.py6 = my.photimeVsPU->ProjectionY("my.py6", 55, 65);
my.py6->SetTitle("6 Vertices");
my.py6->Draw();
my.py6->Write();


my.py7 = my.photimeVsPU->ProjectionY("my.py7", 66, 76);
my.py7->SetTitle("7 Vertices");
my.py7->Draw();
my.py7->Write();


my.py8 = my.photimeVsPU->ProjectionY("my.py8", 77, 87);
my.py8->SetTitle("8 Vertices");
my.py8->Draw();
my.py8->Write();


my.py9 = my.photimeVsPU->ProjectionY("my.py9", 88, 98);
my.py9->SetTitle("9 Vertices");
my.py9->Draw();
my.py9->Write();

my.py10 = my.photimeVsPU->ProjectionY("my.py10", 99, 101);
my.py10->SetTitle("10 Vertices");
my.py10->Draw();
my.py10->Write();

my.py11 = my.photimeVsPU->ProjectionY("my.py11", 102, 112);
my.py11->SetTitle("11 Vertices");
my.py11->Draw();
my.py11->Write();


my.py12 = my.photimeVsPU->ProjectionY("my.py12", 113, 123);
my.py12->SetTitle("12Vertices");
my.py12->Draw();
my.py12->Write();


my.py13->GetXaxis()->SetTitle("45 < nVtx <= 55");
my.py13->GetYaxis()->SetTitle("Event Number");
my.py13->SetTitle("45< nVtx <= 55 Photon Time(ns)");
my.py13->Draw();
my.py13->Write();

my.py14->GetXaxis()->SetTitle("35 < nVtx <= 45");
my.py14->GetYaxis()->SetTitle("Event Number");
my.py14->SetTitle("35< nVtx <=45  Photon Time(ns)");
my.py14->Draw();
my.py14->Write();


my.py15->GetXaxis()->SetTitle("24 < nVtx <= 35");
my.py15->GetYaxis()->SetTitle("Event Number");
my.py15->SetTitle("24< nVtx <= 35 Photon Time(ns)");
my.py15->Draw();
my.py15->Write();


my.py16->GetXaxis()->SetTitle("18 < nVtx <= 24");
my.py16->GetYaxis()->SetTitle("Event Number");
my.py16->SetTitle("18< nVtx <= 24 Photon Time(ns)");
my.py16->Draw();
my.py16->Write();


my.py17->GetXaxis()->SetTitle("12 < nVtx <= 18");
my.py17->GetYaxis()->SetTitle("Event Number");
my.py17->SetTitle("12 < nVtx <= 18 Photon Time(ns)");
my.py17->Draw();
my.py17->Write();

my.py18->GetXaxis()->SetTitle("6 < nVtx <= 12");
my.py18->GetYaxis()->SetTitle("Event Number");
my.py18->SetTitle("6< nVtx <= 12 Photon Time(ns)");
my.py18->Draw();
my.py18->Write();

my.py19->GetXaxis()->SetTitle("0 <= nVtx <= 6");
my.py19->GetYaxis()->SetTitle("Event Number");
my.py19->SetTitle("0<= nVtx <= 6 Photon Time(ns)");
my.py19->Draw();
my.py19->Write();

// Real Distribution of Photon Time Vs Vertices
my.tV1->GetXaxis()->SetTitle("0-7 Vtx");
my.tV1->GetYaxis()->SetTitle("No. Events");
my.tV1->Draw();
my.tV1->Write();

my.tV2->GetXaxis()->SetTitle("7-14 Vtx");
my.tV2->GetYaxis()->SetTitle("No. Events");
my.tV2->Draw();
my.tV2->Write();

my.tV3->GetXaxis()->SetTitle("14-21 Vtx");
my.tV3->GetYaxis()->SetTitle("No. Events");
my.tV3->Draw();
my.tV3->Write();

my.tV4->GetXaxis()->SetTitle("21-28 Vtx");
my.tV4->GetYaxis()->SetTitle("No. Events");
my.tV4->Draw();
my.tV4->Write();

my.tV5->GetXaxis()->SetTitle("28-35 Vtx");
my.tV5->GetYaxis()->SetTitle("No. Events");
my.tV5->Draw();
my.tV5->Write();

my.tV6->GetXaxis()->SetTitle("35-42 Vtx");
my.tV6->GetYaxis()->SetTitle("No. Events");
my.tV6->Draw();
my.tV6->Write();

my.tV7->GetXaxis()->SetTitle("42-49 Vtx");
my.tV7->GetYaxis()->SetTitle("No. Events");
my.tV7->Draw();
my.tV7->Write();

my.tV12->GetXaxis()->SetTitle("0-7 Vtx");
my.tV12->GetYaxis()->SetTitle("No. Events");
my.tV12->Draw();
my.tV12->Write();

my.tV13->GetXaxis()->SetTitle("7-14 Vtx");
my.tV13->GetYaxis()->SetTitle("No. Events");
my.tV13->Draw();
my.tV13->Write();

my.tV14->GetXaxis()->SetTitle("14-21 Vtx");
my.tV14->GetYaxis()->SetTitle("No. Events");
my.tV14->Draw();
my.tV14->Write();

my.tV15->GetXaxis()->SetTitle("21-28 Vtx");
my.tV15->GetYaxis()->SetTitle("No. Events");
my.tV15->Draw();
my.tV15->Write();

my.tV16->GetXaxis()->SetTitle("28-35 Vtx");
my.tV16->GetYaxis()->SetTitle("No. Events");
my.tV16->Draw();
my.tV16->Write();

my.tV17->GetXaxis()->SetTitle("35-42 Vtx");
my.tV17->GetYaxis()->SetTitle("No. Events");
my.tV17->Draw();
my.tV17->Write();

my.tV18->GetXaxis()->SetTitle("42-49 Vtx");
my.tV18->GetYaxis()->SetTitle("No. Events");
my.tV18->Draw();
my.tV18->Write();


my.metVsPU->GetXaxis()->SetTitle("Number of Vertices");
my.metVsPU->GetYaxis()->SetTitle("Event MET(GeV)");
my.metVsPU->Draw("colz");
my.metVsPU->Write();

my.pho_Ecal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Ecal_IsoVsPU->GetYaxis()->SetTitle("EcalIso");
my.pho_Ecal_IsoVsPU->Draw("colz");
my.pho_Ecal_IsoVsPU->Write();

my.ecalIso = my.pho_Ecal_IsoVsPU->ProfileX("my.ecalIso", 1, -1);
my.ecalIso->SetTitle("EcalIso Vs PU");
my.ecalIso->GetYaxis()->SetTitle("EcalIso");
my.ecalIso->GetXaxis()->SetTitle("nVtx");
my.ecalIso->Draw();
my.ecalIso->Write();

my.pho_Hcal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Hcal_IsoVsPU->GetYaxis()->SetTitle("HcalIso");
my.pho_Hcal_IsoVsPU->Draw("colz");
my.pho_Hcal_IsoVsPU->Write();

my.hcalIso = my.pho_Hcal_IsoVsPU->ProfileX("my.hcalIso", 1, -1);
my.hcalIso->SetTitle("HcalIso Vs PU");
my.hcalIso->GetYaxis()->SetTitle("HcalIso");
my.hcalIso->GetXaxis()->SetTitle("nVtx");
my.hcalIso->Draw();
my.hcalIso->Write();

my.pho_Trk_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Trk_IsoVsPU->GetYaxis()->SetTitle("TrkIso");
my.pho_Trk_IsoVsPU->Draw("colz");
my.pho_Trk_IsoVsPU->Write();

my.trkIso = my.pho_Trk_IsoVsPU->ProfileX("my.trkIso", 1, -1);
my.trkIso->SetTitle("TrackIso Vs PU");
my.trkIso->GetYaxis()->SetTitle("TrackIso");
my.trkIso->GetXaxis()->SetTitle("nVtx");
my.trkIso->Draw();
my.trkIso->Write();


//my.Hcal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
//my.Hcal_IsoVsPU->GetYaxis()->SetTitle("2012 HcalIso");
//my.Hcal_IsoVsPU->Draw("colz");
//my.Hcal_IsoVsPU->Write();

//my.HcalIso = my.Hcal_IsoVsPU->ProfileX("my.HcalIso", 1, -1);
//my.HcalIso->SetTitle("2012 HcalIso Vs PU");
//my.HcalIso->GetYaxis()->SetTitle("2012 HcalIso");
//my.HcalIso->GetXaxis()->SetTitle("nVtx");
//my.HcalIso->Draw();
//my.HcalIso->Write();

my.sMinorVsPU->GetXaxis()->SetTitle("nVtx");
my.sMinorVsPU->GetYaxis()->SetTitle("sMinor");
my.sMinorVsPU->Draw("colz");
my.sMinorVsPU->Write();

my.sminor = my.sMinorVsPU->ProfileX("my.sminor", 1, -1);
my.sminor->SetTitle("sMinor Vs PU");
my.sminor->GetYaxis()->SetTitle("sMinor");
my.sminor->GetXaxis()->SetTitle("nVtx");
my.sminor->Draw();
my.sminor->Write();

my.phoTimeVsEta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.phoTimeVsEta->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.phoTimeVsEta->Draw("colz");
my.phoTimeVsEta->Write();

my.phoTimeVsE->GetXaxis()->SetTitle("Photon Energy(GeV)");
my.phoTimeVsE->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.phoTimeVsE->Draw("colz");
my.phoTimeVsE->Write();

my.phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.phoTimeVsPhi->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.phoTimeVsPhi->Draw("colz");
my.phoTimeVsPhi->Write();


my.phoCSCtime->GetYaxis()->SetTitle("No. Events");
my.phoCSCtime->GetXaxis()->SetTitle("CSC Photon Time(ns)");
my.phoCSCtime->Draw();
my.phoCSCtime->Write();

my.phonBC->GetXaxis()->SetTitle("No. Of Basic Clusters");
my.phonBC->GetYaxis()->SetTitle("No. Events");
my.phonBC->Draw();
my.phonBC->Write();

my.phonXtal->GetXaxis()->SetTitle("No. Of Crys in SC");
my.phonXtal->GetYaxis()->SetTitle("No. Events");
my.phonXtal->Draw();
my.phonXtal->Write();
// EB and EE Stuff

my.pho_num_phoEB->GetXaxis()->SetTitle("Number of #gamma s");
my.pho_num_phoEB->GetYaxis()->SetTitle("Event Number");
my.pho_num_phoEB->Draw() ;
my.pho_num_phoEB->Write();

my.pho_num_phoEE->GetXaxis()->SetTitle("Number of #gamma s");
my.pho_num_phoEE->GetYaxis()->SetTitle("Event Number");
my.pho_num_phoEE->Draw() ;
my.pho_num_phoEE->Write();

my.pho_num_jetEB->GetXaxis()->SetTitle("Number of jets");
my.pho_num_jetEB->GetYaxis()->SetTitle("Event Number");
my.pho_num_jetEB->Draw() ;
my.pho_num_jetEB->Write();

my.pho_num_jetEE->GetXaxis()->SetTitle("Number of jets");
my.pho_num_jetEE->GetYaxis()->SetTitle("Event Number");
my.pho_num_jetEE->Draw() ;
my.pho_num_jetEE->Write();

my.pho_timeVsEtaEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.pho_timeVsEtaEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.pho_timeVsEtaEB->Draw("colz");
my.pho_timeVsEtaEB->Write();

my.pho_timeVsEtaEE->GetXaxis()->SetTitle("#eta_{#gamma}");
my.pho_timeVsEtaEE->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.pho_timeVsEtaEE->Draw("colz");
my.pho_timeVsEtaEE->Write();

my.pho_timeVsPhiEB->GetXaxis()->SetTitle("#phi_{#gamma}");
my.pho_timeVsPhiEB->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.pho_timeVsPhiEB->Draw("colz");
my.pho_timeVsPhiEB->Write();

my.pho_timeVsPhiEE->GetXaxis()->SetTitle("#phi_{#gamma}");
my.pho_timeVsPhiEE->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.pho_timeVsPhiEE->Draw("colz");
my.pho_timeVsPhiEE->Write();

my.pho_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
my.pho_sigmaEtaEB->Draw();
my.pho_sigmaEtaEB->Write();

my.pho_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
my.pho_sigmaEtaEE->Draw();
my.pho_sigmaEtaEE->Write();

my.pho_sminorEB->GetXaxis()->SetTitle("SMinor");
my.pho_sminorEB->GetYaxis()->SetTitle("Event Number");
my.pho_sminorEB->Draw();
my.pho_sminorEB->Write();

my.pho_smajorEB->GetXaxis()->SetTitle("SMajor");
my.pho_smajorEB->GetYaxis()->SetTitle("Event Number");
my.pho_smajorEB->Draw();
my.pho_smajorEB->Write();

my.pho_sminorEE->GetXaxis()->SetTitle("SMinor");
my.pho_sminorEE->GetYaxis()->SetTitle("Event Number");
my.pho_sminorEE->Draw();
my.pho_sminorEE->Write();

my.pho_smajorEE->GetXaxis()->SetTitle("SMajor");
my.pho_smajorEE->GetYaxis()->SetTitle("Event Number");
my.pho_smajorEE->Draw();
my.pho_smajorEE->Write();

my.pho_timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_timeEB->Draw();
my.pho_timeEB->Write();

my.pho_timeEE->GetXaxis()->SetTitle("Photon(seed Crys) Time(ns)");
my.pho_timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_timeEE->Draw();
my.pho_timeEE->Write();

my.pho_timeVsCSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
my.pho_timeVsCSCdphi->GetYaxis()->SetTitle("seed Crys Time (ns)");
my.pho_timeVsCSCdphi->Draw();
my.pho_timeVsCSCdphi->Write();

my.pho_CSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
my.pho_CSCdphi->GetYaxis()->SetTitle("No. Events");
my.pho_CSCdphi->Draw();
my.pho_CSCdphi->Write();

my.pho_LN2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_LN2timeEB->Draw();
my.pho_LN2timeEB->Write();

my.pho_LN2GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2GP2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_LN2GP2timeEB->Draw();
my.pho_LN2GP2timeEB->Write();

my.pho_GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_GP2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_GP2timeEB->Draw();
my.pho_GP2timeEB->Write();


my.pho_LN2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_LN2timeEE->Draw();
my.pho_LN2timeEE->Write();

my.pho_LN2GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2GP2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_LN2GP2timeEE->Draw();
my.pho_LN2GP2timeEE->Write();

my.pho_GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_GP2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_GP2timeEE->Draw();
my.pho_GP2timeEE->Write();

my.pho_ATG2_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_ATG2_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
my.pho_ATG2_sigmaEtaEB->Draw();
my.pho_ATG2_sigmaEtaEB->Write();

my.pho_ATG2_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_ATG2_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
my.pho_ATG2_sigmaEtaEE->Draw();
my.pho_ATG2_sigmaEtaEE->Write();

my.pho_ATG2_sminorEB->GetXaxis()->SetTitle("SMinor");
my.pho_ATG2_sminorEB->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_sminorEB->Draw();
my.pho_ATG2_sminorEB->Write();

my.pho_ATG2_smajorEB->GetXaxis()->SetTitle("SMajor");
my.pho_ATG2_smajorEB->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_smajorEB->Draw();
my.pho_ATG2_smajorEB->Write();

my.pho_ATG2_sminorEE->GetXaxis()->SetTitle("SMinor");
my.pho_ATG2_sminorEE->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_sminorEE->Draw();
my.pho_ATG2_sminorEE->Write();

my.pho_ATG2_smajorEE->GetXaxis()->SetTitle("SMajor");
my.pho_ATG2_smajorEE->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_smajorEE->Draw();
my.pho_ATG2_smajorEE->Write();


//my.phopzOnpt->GetXaxis()->SetTitle("Ratio (Pz/Pt)_{#gamma}");
//my.phopzOnpt->GetYaxis()->SetTitle("No. Events");
//my.phopzOnpt->Draw();
//my.phopzOnpt->Write();

//my.phosigmaietaieta->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
//my.phosigmaietaieta->GetYaxis()->SetTitle("No. Events");
//my.phosigmaietaieta->Draw();
//my.phosigmaietaieta->Write();

my.phoetaVsphi->GetXaxis()->SetTitle("#eta_{#gamma}");
my.phoetaVsphi->GetYaxis()->SetTitle("#phi_{gamma}");
my.phoetaVsphi->Draw();
my.phoetaVsphi->Write();

my.halo_phodrho->GetXaxis()->SetTitle("#delta#rho_{halo #gamma}");
my.halo_phodrho->GetYaxis()->SetTitle("No. Events");
my.halo_phodrho->Draw();
my.halo_phodrho->Write();

my.halo_phodphi->GetXaxis()->SetTitle("#delta#phi_{halo #gamma}");
my.halo_phodphi->GetYaxis()->SetTitle("No. Events");
my.halo_phodphi->Draw();
my.halo_phodphi->Write();

Hg.halo_etaVsphi->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsphi->GetYaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_etaVsphi->Draw();
Hg.halo_etaVsphi->Write();

Hg.halo_phiVsStime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsStime->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_phiVsStime->Draw();
Hg.halo_phiVsStime->Write();

Hg.halo_phiVsBCtime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsBCtime->GetYaxis()->SetTitle("W.Av Seed BC Time(ns)");
Hg.halo_phiVsBCtime->Draw();
Hg.halo_phiVsBCtime->Write();

Hg.halo_phiVsSCtime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsSCtime->GetYaxis()->SetTitle("W.Av SC Time(ns)");
Hg.halo_phiVsSCtime->Draw();
Hg.halo_phiVsSCtime->Write();

Hg.halo_etaVsStime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsStime->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_etaVsStime->Draw();
Hg.halo_etaVsStime->Write();

Hg.halo_etaVsBCtime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsBCtime->GetYaxis()->SetTitle("W.Av Seed BC Time(ns)");
Hg.halo_etaVsBCtime->Draw();
Hg.halo_etaVsBCtime->Write();

Hg.halo_etaVsSCtime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsSCtime->GetYaxis()->SetTitle("W.Av SC Time(ns)");
Hg.halo_etaVsSCtime->Draw();
Hg.halo_etaVsSCtime->Write();

Hg.halo_rhoVsphi->GetXaxis()->SetTitle("#rho_{Halo #gamma}");
Hg.halo_rhoVsphi->GetYaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_rhoVsphi->Draw();
Hg.halo_rhoVsphi->Write();

//Hg.halo_pzOnpt->GetXaxis()->SetTitle("Ratio(Pz/Pt)_{Halo #gamma}");
//Hg.halo_pzOnpt->GetYaxis()->SetTitle("No. Events");
//Hg.halo_pzOnpt->Draw();
//Hg.halo_pzOnpt->Write();

Hg.halo_nBC->GetXaxis()->SetTitle("No. BC_{Halo #gamma}");
Hg.halo_nBC->GetYaxis()->SetTitle("No. Events");
Hg.halo_nBC->Draw();
Hg.halo_nBC->Write();

Hg.halo_nXtal->GetXaxis()->SetTitle("No. Crys_{Halo #gamma}");
Hg.halo_nXtal->GetYaxis()->SetTitle("No. Events");
Hg.halo_nXtal->Draw();
Hg.halo_nXtal->Write();

Hg.halo_rho->GetXaxis()->SetTitle("#rho_{Halo #gamma}");
Hg.halo_rho->GetYaxis()->SetTitle("No. Events");
Hg.halo_rho->Draw();
Hg.halo_rho->Write();

Hg.halo_phi->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phi->GetYaxis()->SetTitle("No. Events");
Hg.halo_phi->Draw();
Hg.halo_phi->Write();

//Hg.halo_sigmaietaieta->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}^{Halo #gamma}");
//Hg.halo_sigmaietaieta->GetYaxis()->SetTitle("No. Events");
//Hg.halo_sigmaietaieta->Draw();
//Hg.halo_sigmaietaieta->Write();

//Hg.halo_phonBCratio->GetXaxis()->SetTitle("Ratio(No.BC_{#gamma}/No.BC_{Halo #gamma})");
//Hg.halo_phonBCratio->GetYaxis()->SetTitle("No. Events");
//Hg.halo_phonBCratio->Draw();
//Hg.halo_phonBCratio->Write();

//Hg.halo_phonXtalratio->GetXaxis()->SetTitle("Ratio(No.Crys_{#gamma}/No.Crys_{Halo #gamma})");
//Hg.halo_phonXtalratio->GetYaxis()->SetTitle("No. Events");
//Hg.halo_phonXtalratio->Draw();
//Hg.halo_phonXtalratio->Write();

//Hg.halo_TrksSbeta->GetXaxis()->SetTitle("No. Halo Trks Beta Small");
//Hg.halo_TrksSbeta->GetYaxis()->SetTitle("No. Events");
//Hg.halo_TrksSbeta->Draw();
//Hg.halo_TrksSbeta->Write();

//Hg.halo_nhalosegs->GetXaxis()->SetTitle("No.Of Halo Segments");
//Hg.halo_nhalosegs->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nhalosegs->Draw();
//Hg.halo_nhalosegs->Write();

//Hg.halo_nOThits->GetXaxis()->SetTitle("No.Of OutOfTime Halo Hits");
//Hg.halo_nOThits->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nOThits->Draw();
//Hg.halo_nOThits->Write();

//Hg.halo_nhalotrk->GetXaxis()->SetTitle("No.Of Halo Tracks");
//Hg.halo_nhalotrk->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nhalotrk->Draw();
//Hg.halo_nhalotrk->Write();

Hg.halo_seedTime->GetXaxis()->SetTitle("Seed Crys Time_{Halo #gamma}(ns)");
Hg.halo_seedTime->GetYaxis()->SetTitle("No. Events");
Hg.halo_seedTime->Draw();
Hg.halo_seedTime->Write();

Hg.halo_wavBCtime->GetXaxis()->SetTitle("W.Ave BC Time_{Halo #gamma}(ns)");
Hg.halo_wavBCtime->GetYaxis()->SetTitle("No. Events");
Hg.halo_wavBCtime->Draw();
Hg.halo_wavBCtime->Write();

Hg.halo_wavSCtime->GetXaxis()->SetTitle("W.Av BC Time_{Halo #gamma}(ns)");
Hg.halo_wavSCtime->GetYaxis()->SetTitle("No. Events");
Hg.halo_wavSCtime->Draw();
Hg.halo_wavSCtime->Write();

// EB and EE Stuff
Hg.halo_timeVsEtaEB->GetXaxis()->SetTitle("#eta_{#gamma}");
Hg.halo_timeVsEtaEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
Hg.halo_timeVsEtaEB->Draw("colz");
Hg.halo_timeVsEtaEB->Write();

Hg.halo_timeVsEtaEE->GetXaxis()->SetTitle("#eta_{#gamma}");
Hg.halo_timeVsEtaEE->GetYaxis()->SetTitle("Seed crys Time(ns)");
Hg.halo_timeVsEtaEE->Draw("colz");
Hg.halo_timeVsEtaEE->Write();

Hg.halo_timeVsPhiEB->GetXaxis()->SetTitle("#phi_{#gamma}");
Hg.halo_timeVsPhiEB->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_timeVsPhiEB->Draw("colz");
Hg.halo_timeVsPhiEB->Write();

Hg.halo_timeVsPhiEE->GetXaxis()->SetTitle("#phi_{#gamma}");
Hg.halo_timeVsPhiEE->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_timeVsPhiEE->Draw("colz");
Hg.halo_timeVsPhiEE->Write();

Hg.halo_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_sigmaEtaEB->Draw();
Hg.halo_sigmaEtaEB->Write();

Hg.halo_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
Hg.halo_sigmaEtaEE->Draw();
Hg.halo_sigmaEtaEE->Write();

Hg.halo_sminorEB->GetXaxis()->SetTitle("SMinor");
Hg.halo_sminorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_sminorEB->Draw();
Hg.halo_sminorEB->Write();

Hg.halo_smajorEB->GetXaxis()->SetTitle("SMajor");
Hg.halo_smajorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_smajorEB->Draw();
Hg.halo_smajorEB->Write();

Hg.halo_sminorEE->GetXaxis()->SetTitle("SMinor");
Hg.halo_sminorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_sminorEE->Draw();
Hg.halo_sminorEE->Write();

Hg.halo_smajorEE->GetXaxis()->SetTitle("SMajor");
Hg.halo_smajorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_smajorEE->Draw();
Hg.halo_smajorEE->Write();

Hg.halo_timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_timeEB->Draw();
Hg.halo_timeEB->Write();

Hg.halo_timeEE->GetXaxis()->SetTitle("Photon(seed Crys) Time(ns)");
Hg.halo_timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_timeEE->Draw();
Hg.halo_timeEE->Write();

Hg.halo_timeVsCSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
Hg.halo_timeVsCSCdphi->GetYaxis()->SetTitle("seed Crys Time (ns)");
Hg.halo_timeVsCSCdphi->Draw();
Hg.halo_timeVsCSCdphi->Write();

Hg.halo_CSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
Hg.halo_CSCdphi->GetYaxis()->SetTitle("No. Events");
Hg.halo_CSCdphi->Draw();
Hg.halo_CSCdphi->Write();

Hg.halo_LN2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2timeEB->Draw();
Hg.halo_LN2timeEB->Write();

Hg.halo_LN2GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2GP2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2GP2timeEB->Draw();
Hg.halo_LN2GP2timeEB->Write();

Hg.halo_GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_GP2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_GP2timeEB->Draw();
Hg.halo_GP2timeEB->Write();


Hg.halo_LN2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2timeEE->Draw();
Hg.halo_LN2timeEE->Write();

Hg.halo_LN2GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2GP2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2GP2timeEE->Draw();
Hg.halo_LN2GP2timeEE->Write();

Hg.halo_GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_GP2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_GP2timeEE->Draw();
Hg.halo_GP2timeEE->Write();

Hg.halo_ATG2_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_ATG2_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_ATG2_sigmaEtaEB->Draw();
Hg.halo_ATG2_sigmaEtaEB->Write();

Hg.halo_ATG2_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_ATG2_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
Hg.halo_ATG2_sigmaEtaEE->Draw();
Hg.halo_ATG2_sigmaEtaEE->Write();

Hg.halo_ATG2_sminorEB->GetXaxis()->SetTitle("SMinor");
Hg.halo_ATG2_sminorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_sminorEB->Draw();
Hg.halo_ATG2_sminorEB->Write();

Hg.halo_ATG2_smajorEB->GetXaxis()->SetTitle("SMajor");
Hg.halo_ATG2_smajorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_smajorEB->Draw();
Hg.halo_ATG2_smajorEB->Write();

Hg.halo_ATG2_sminorEE->GetXaxis()->SetTitle("SMinor");
Hg.halo_ATG2_sminorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_sminorEE->Draw();
Hg.halo_ATG2_sminorEE->Write();

Hg.halo_ATG2_smajorEE->GetXaxis()->SetTitle("SMajor");
Hg.halo_ATG2_smajorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_smajorEE->Draw();
Hg.halo_ATG2_smajorEE->Write();

Hg.halo_num_phoEB->GetXaxis()->SetTitle("No.of Halo #gamma s");
Hg.halo_num_phoEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_phoEB->Draw() ;
Hg.halo_num_phoEB->Write();

Hg.halo_num_phoEE->GetXaxis()->SetTitle("No.of Halo #gamma s");
Hg.halo_num_phoEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_phoEE->Draw() ;
Hg.halo_num_phoEE->Write();

Hg.halo_num_jetEB->GetXaxis()->SetTitle("Number of jets");
Hg.halo_num_jetEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_jetEB->Draw() ;
Hg.halo_num_jetEB->Write();

Hg.halo_num_jetEE->GetXaxis()->SetTitle("Number of jets");
Hg.halo_num_jetEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_jetEE->Draw() ;
Hg.halo_num_jetEE->Write();

//Strange time Event Plots 
Lt.ltvtxX->GetXaxis()->SetTitle("X Vertex(cm)");
Lt.ltvtxX->Draw();
Lt.ltvtxX->Write();
Lt.ltvtxY->GetXaxis()->SetTitle("Y Vertex(cm)");
Lt.ltvtxY->Draw();
Lt.ltvtxY->Write();
Lt.ltvtxZ->GetXaxis()->SetTitle("Z Vertex(cm)");
Lt.ltvtxZ->Draw();
Lt.ltvtxZ->Write();
Lt.lteta->GetXaxis()->SetTitle("#eta");
Lt.lteta->Draw();
Lt.lteta->Write();
Lt.ltphi->GetXaxis()->SetTitle("#phi");
Lt.ltphi->Draw();
Lt.ltphi->Write();
Lt.ltEvtmet->GetXaxis()->SetTitle("MET(GeV)");
Lt.ltEvtmet->Draw();
Lt.ltEvtmet->Write();
Lt.ltEvtpt->GetXaxis()->SetTitle("#gamma Pt (GeV/c)");
Lt.ltEvtpt->Draw();
Lt.ltEvtpt->Write();

Lt.ltphoE->GetXaxis()->SetTitle("#gamma Energy (GeV)");
Lt.ltphoE->Draw();
Lt.ltphoE->Write();

Lt.ltnjets->GetXaxis()->SetTitle("Number of Jets");
Lt.ltnjets->Draw();
Lt.ltnjets->Write();
Lt.ltnpho->GetXaxis()->SetTitle("Number of #gamma s");
Lt.ltnpho->Draw();
Lt.ltnpho->Write();
Lt.ltnvtx->GetXaxis()->SetTitle("Number of Primary Vertices");
Lt.ltnvtx->Draw();
Lt.ltnvtx->Write();



//Single Vertex Event Plots 
Sv.svtxX->GetXaxis()->SetTitle("X Vertex(cm)");
Sv.svtxX->Draw();
Sv.svtxX->Write();
Sv.svtxY->GetXaxis()->SetTitle("Y Vertex(cm)");
Sv.svtxY->Draw();
Sv.svtxY->Write();
Sv.svtxZ->GetXaxis()->SetTitle("Z Vertex(cm)");
Sv.svtxZ->Draw();
Sv.svtxZ->Write();
Sv.svtxeta->GetXaxis()->SetTitle("#eta");
Sv.svtxeta->Draw();
Sv.svtxeta->Write();
Sv.svtxphi->GetXaxis()->SetTitle("#phi");
Sv.svtxphi->Draw();
Sv.svtxphi->Write();
Sv.svtxEvtmet->GetXaxis()->SetTitle("MET(GeV)");
Sv.svtxEvtmet->Draw();
Sv.svtxEvtmet->Write();
Sv.svtxEvtpt->GetXaxis()->SetTitle("#gamma Pt (GeV/c)");
Sv.svtxEvtpt->Draw();
Sv.svtxEvtpt->Write();
Sv.svtxnjets->GetXaxis()->SetTitle("Number of Jets");
Sv.svtxnjets->Draw();
Sv.svtxnjets->Write();
Sv.svtxnpho->GetXaxis()->SetTitle("Number of #gamma s");
Sv.svtxnpho->Draw();
Sv.svtxnpho->Write();
Sv.svtxnvtx->GetXaxis()->SetTitle("Number of Primary Vertices");
Sv.svtxnvtx->Draw();
Sv.svtxnvtx->Write();

} // End of Fxn Write hist

//Fxn to Make Plots
void TestGen::Make_Plots(){
// Now Make Plots
   TCanvas*  c1 = new TCanvas("c1","", 800, 600);
   c1->SetFillColor(10);
   c1->SetFillColor(10);
   gStyle->SetOptStat("emriou");
   //c1->SetLogy();

   // Photon Pt distribution
   c1->cd();
   c1->SetLogy();
   gStyle->SetStatY(0.95);
   gStyle->SetStatTextColor(1);
   my.h_g1Pt->SetLineColor(1) ;
   my.h_g1Pt->GetXaxis()->SetTitle("Photon Pt(GeV)");
   my.h_g1Pt->GetYaxis()->SetTitle("Event Number");

   my.h_g1Pt->Draw() ;
   c1->Update();

   TString plotname1 = hfolder + "PhotonPt." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(1);

   // Photon Time
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.h_Time->GetXaxis()->SetTitle("Photon Time(ns)");
   my.h_Time->GetYaxis()->SetTitle("Event Number");
   my.h_Time->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonTime." + plotType ;
   c1->Print( plotname1 );

   // Photon W Ave Seed BC Time
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.WAveSeedBCphotime->GetXaxis()->SetTitle("Photon ( W Ave Seed BC) Time(ns)");
   my.WAveSeedBCphotime->GetYaxis()->SetTitle("Event Number");
   my.WAveSeedBCphotime->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonSeedBCWAveTime." + plotType ;
   c1->Print( plotname1 );

   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.AveSCphotime->GetXaxis()->SetTitle("Photon( W Ave SC) Time(ns)");
   my.AveSCphotime->GetYaxis()->SetTitle("Event Number");
   my.AveSCphotime->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonWAveSCTime." + plotType ;
   c1->Print( plotname1 );


// Event Met
   c1->cd() ;
   gStyle->SetStatY(0.95);
   c1->SetLogy(1);
my.evt_met->GetXaxis()->SetTitle("Event MET(GeV)");
my.evt_met->GetYaxis()->SetTitle("Event Number");

   my.evt_met->Draw() ;
   c1->Update();
   plotname1 = hfolder + "EventMet." + plotType ;
 //  c1->SetLogy(1)
   c1->Print( plotname1 );

// Photon sMinor
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_smin->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonsMinor." + plotType ;
   c1->Print( plotname1 );

// Photon EcalIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_EcalIso->GetXaxis()->SetTitle("#gamma EcalIso");
   my.pho_EcalIso->GetYaxis()->SetTitle("Event Number");
   my.pho_EcalIso->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEcalIso." + plotType ;
   c1->Print( plotname1 );


// Photon HcallIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_HcalIso->GetXaxis()->SetTitle("#gamm Hcal Iso");
   my.pho_HcalIso->GetYaxis()->SetTitle("Event Number");
   my.pho_HcalIso->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonHcalIso." + plotType ;
   c1->Print( plotname1 );


// Photon TrackIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_TrkIso->Draw() ;
   my.pho_TrkIso->GetXaxis()->SetTitle("#gamma TrackIso");
   my.pho_TrkIso->GetYaxis()->SetTitle("Event Number");
   c1->Update();
   plotname1 = hfolder + "PhotonTrkIso." + plotType ;
   c1->Print( plotname1 );


// Photon  2012 HCAL Iso
//   c1->cd() ;
//   gStyle->SetStatY(0.95);
//   my.hcal_Iso->GetXaxis()->SetTitle("#gamma 2012 HcalIso");
//   my.hcal_Iso->GetYaxis()->SetTitle("Event Number");

 //  my.hcal_Iso->Draw() ;
 //  c1->Update();
 //  plotname1 = hfolder + "Photon_2012_HcalIso." + plotType ;
 //  c1->Print( plotname1 );

// Photon sMajor
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_smaj->GetXaxis()->SetTitle("#gamma SMajor");
   my.ph_smaj->GetYaxis()->SetTitle("Event Number");

   my.ph_smaj->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonsMajor." + plotType ;
   c1->Print( plotname1 );

// Photon Energy dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_e->GetXaxis()->SetTitle("Photon Energy(GeV)");
   my.ph_e->GetYaxis()->SetTitle("Event Number");

   my.ph_e->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEnergy." + plotType ;
   c1->Print( plotname1 );

// Photon Z Position
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_z->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonZ." + plotType ;
   c1->Print( plotname1 );


// PU or Nvertices
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pu_vtx->GetXaxis()->SetTitle("nVtx");
   my.pu_vtx->GetYaxis()->SetTitle("Event Number");
   my.pu_vtx->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PUStudy." + plotType ;
   c1->Print( plotname1 );

// Photon Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_eta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEta." + plotType ;
   c1->Print( plotname1 );

// Photon Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_phi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonPhi." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jet_eta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetEta." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jet_phi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPhi." + plotType ;
   c1->Print( plotname1 );

// Photon - Jet Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jp_deta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPhtonDEta." + plotType ;
   c1->Print( plotname1 );

// Photon -Jet Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jp_dphi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonJetDPhi." + plotType ;
   c1->Print( plotname1 );

// Number of Jet Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
 my.njets->GetXaxis()->SetTitle("Number of Jets");
 my.njets->GetYaxis()->SetTitle("Event Number");

   my.njets->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NumberOfJets." + plotType ;
   c1->Print( plotname1 );

// Number of Photon Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.npho->GetXaxis()->SetTitle("Number of #gammas");
   my.npho->GetYaxis()->SetTitle("Event Number");

   my.npho->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NumberOfPhotons." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Pt dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
  my.j_pt->GetXaxis()->SetTitle("JetPt(GeV)");
  my.j_pt->GetYaxis()->SetTitle("Event Number");
   my.j_pt->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPt." + plotType ;
   c1->Print( plotname1 );

	// Met Direction	
	c1->cd() ;
	gStyle->SetStatY(0.95);
	my.mettheta->Draw();
	c1->Update();
	plotname1 = hfolder + "MetTheta." + plotType ;
	c1->Print(plotname1);

	//Met-Photon Direction
   c1->cd() ;
   gStyle->SetStatY(0.95);

   my.phomet_thetadiff->GetXaxis()->SetTitle("Photon-Gravitino Angle Difference(radians)");
   my.phomet_thetadiff->GetYaxis()->SetTitle("Event Number");
   my.phomet_thetadiff->Draw() ;
   c1->Update();
   plotname1 = hfolder + "Met_PhotonThetaDiff." + plotType ;
   c1->Print( plotname1 );

    //Photon Hadronic Energy over Total Energy Ratio
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_HoverE->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonHadOverE." + plotType ;
   c1->Print( plotname1 );

   // Transverse Mass of Neutralino
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.MassNt->GetXaxis()->SetTitle("M_{NLSP}(GeV)");
   my.MassNt->GetYaxis()->SetTitle("Event Number");
   my.MassNt->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NeutTMass." + plotType ;
   c1->Print( plotname1 );

   // Photon Angular Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_angle->GetXaxis()->SetTitle("Photon Angle(radians)");
   my.pho_angle->GetYaxis()->SetTitle("Event Number");
   my.pho_angle->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonAngle." + plotType ;
   c1->Print( plotname1 );

   
   c1->cd() ; 
   gStyle->SetStatY(0.95);
   my.photimeVsPU->GetXaxis()->SetTitle("Number of Vertices");
   my.photimeVsPU->GetYaxis()->SetTitle("Photon Time(ns)");
   my.photimeVsPU->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsPU." + plotType ;
   c1->Print( plotname1 );

   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.metVsPU->GetXaxis()->SetTitle("Number of Vertices");
   my.metVsPU->GetYaxis()->SetTitle("Event MET(GeV)");
   my.metVsPU->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "METVsPU." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsEta->GetXaxis()->SetTitle("#eta_{#gamma}");
   my.phoTimeVsEta->GetYaxis()->SetTitle("Photon Time(ns)");
   my.phoTimeVsEta->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsEtaDist." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs Energy
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsE->GetXaxis()->SetTitle("Photon Energy(GeV)");
   my.phoTimeVsE->GetYaxis()->SetTitle("Photon Time(ns)");
   my.phoTimeVsE->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsEnergy." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs  Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
   my.phoTimeVsPhi->GetYaxis()->SetTitle("Photon Time(ns)");
   my.phoTimeVsPhi->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsPhiDist." + plotType ;
   c1->Print( plotname1 );

} // EoF Make_Plots



//***********/ Fuction Doing Analyzing /*********//
// analysis template
void TestGen::ReadTree( string dataName ) { 

   TTree* tr = Input->TreeMap( dataName );

    tr->SetBranchAddress("nPhotons",    &nPhotons);
    tr->SetBranchAddress("nJets",       &nJets);
    tr->SetBranchAddress("triggered",   &triggered);
    tr->SetBranchAddress("nMuons",      &nMuons);
    tr->SetBranchAddress("nElectrons",  &nElectrons);
    tr->SetBranchAddress("nVertices",   &nVertices);
    tr->SetBranchAddress("totalNVtx",   &totalNVtx);
  
    tr->SetBranchAddress("eventId",     &eventId);
//   tr->SetBranchAddress("nOutTimeHits", &nOutTimeHits) ;
//   tr->SetBranchAddress("nHaloTracks",   &nHaloTracks ) ;
   tr->SetBranchAddress("haloPhi",      &haloPhi ) ;
   tr->SetBranchAddress("haloRho",      &haloRho ) ;

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("phoHoverE",   phoHoverE);
   tr->SetBranchAddress("phoEcalIso",   phoEcalIso);
   tr->SetBranchAddress("phoHcalIso",   phoHcalIso);
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso);
   
   tr->SetBranchAddress("jetCM",   jetCM);
   tr->SetBranchAddress("jetNDau",   jetNDau);
   tr->SetBranchAddress("jetCEF",    jetCEF);
   tr->SetBranchAddress("jetNHF",   jetNHF);
//   tr->SetBranchAddress("jetCHEF",  jetCHEF);
//   tr->SetBranchAddress("jetEta",  jetEta);



 //  tr->SetBranchAddress("HcalIso",    HcalIso);


 //  tr->SetBranchAddress("phoEta",        phoEta );
 // tr->SetBranchAddress("phoPhi",        phoPhi );
   tr->SetBranchAddress("sMinPho",       sMinPho );
   tr->SetBranchAddress("sMajPho",       sMajPho );
   tr->SetBranchAddress("jetE",           jetE );
   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );
   tr->SetBranchAddress("jetPz",       jetPz );
   
   tr->SetBranchAddress("vtxDx",         vtxDx );
   tr->SetBranchAddress("vtxDy",         vtxDy );
   tr->SetBranchAddress("vtxDz",         vtxDz );

   tr->SetBranchAddress("vtxX",         vtxX );
   tr->SetBranchAddress("vtxY",         vtxY );
   tr->SetBranchAddress("vtxZ",         vtxZ );

   tr->SetBranchAddress("met",            &met);
   tr->SetBranchAddress("metPx",        &metPx);
   tr->SetBranchAddress("metPy",        &metPy);
   tr->SetBranchAddress("muE",         muE );
   
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("seedTimeErr", seedTimeErr );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("aveTimeErr",  aveTimeErr );
   tr->SetBranchAddress("aveTimeErr1", aveTimeErr1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );
   tr->SetBranchAddress("sigmaEta",    sigmaEta );
  // tr->SetBranchAddress("sigmaIeta",   sigmaIeta ); 
   
   tr->SetBranchAddress("fSpike",      fSpike );
   tr->SetBranchAddress("nXtals",     nXtals);
   tr->SetBranchAddress("nBC",     nBC );

   tr->SetBranchAddress("cscTime",     cscTime);
   tr->SetBranchAddress("cscdPhi",     cscdPhi); 
//   tr->SetBranchAddress("nTrksSmallBeta",   &nTrksSmallBeta); 
//   tr->SetBranchAddress("nHaloSegs",     &nHaloSegs ); 
   tr->SetBranchAddress("haloPhi",     &haloPhi);
   tr->SetBranchAddress("haloRho",     &haloRho );
   tr->SetBranchAddress("IscscHaloSeg_Tag",     &IscscHaloSeg_Tag);
   tr->SetBranchAddress("IscscHaloTrk_Tag",     &IscscHaloTrk_Tag);
   tr->SetBranchAddress("IsBeamHaloIDTightTag",     &IsBeamHaloIDTightTag);
   tr->SetBranchAddress("IscscHaloTight_Tag",     &IscscHaloTight_Tag);
// MC Infos
   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genM",        genM );
   tr->SetBranchAddress("genVx",       genVx );
   tr->SetBranchAddress("genVy",       genVy );
   tr->SetBranchAddress("genVz",       genVz );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );

// Initialise Histograms
 InitHist();

// Get Events
int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

int nEvt = 0 ;

cout << "Event processing Starts" << endl;
// Loop  over events Now
for ( int i=0; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
         
           tr->GetEntry( i );
 

// Select only DisplacedPhO Triggered Events
bool passTrig = false  ;
for ( size_t j = 0 ; j< trigCut.size(); j++ ) {
    if ( triggered == trigCut[j]) passTrig = true ;
}
if ( !passTrig ) continue ; 

// if (nJets != jetCuts[1]) continue ; 

// Apply MET Selection
if (met < metCut[0]) continue ;


// Reject Halo Photons Right Away
// if(IscscHaloSeg_Tag || IscscHaloTrk_Tag || IsBeamHaloIDTightTag || IscscHaloTight_Tag ) continue;
     
nEvt++;
double metratio = (metPy ? metPx/metPy : 0);
//   if(metPx == 0){ metratio = 0;} else { metratio = metPy ? metPx/metPy : 0 ;} 
double thetamet = TMath::ATan(metratio); // Gravitino direction for MET Vector!
double thetapho = 0;  // Photon angle
double phoeta = 0;    // Photon eta
double pho_gravtheta = 0; // dxn of Grav wrt to photon
float  massNt = 0;  // Neutralino  transverse Mass 

TLorentzVector g1P4(0,0,0,0),  j1p4(0,0,0,0), gHP4(0,0,0,0);  // Halo Photon
double max_gPt  = 0 ;
int kmax = -1 ;
int n_pho = 0; 

// Loop and select Max Pt Photon
for ( int k=0; k< nPhotons; k++) {
     TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
     if ( gP4_.Pt() < photonCuts[0] ) continue ;
     if ( fabs(gP4_.Eta()) > photonCuts[1] ) continue ;
     // Include PhotonIso here!

     //  Halo Tagging 
       
     n_pho++ ;
     //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
     if ( gP4_.Pt() > max_gPt ) {
         max_gPt = gP4_.Pt() ;
         kmax = k ;
         g1P4 = gP4_ ;
     
        } 
           
    }  // End of Nphoton Loops
// Aply  cut on sMin on max Pt Photon
//if( sMinPho[kmax] < photonCuts[4]  ||  sMinPho[kmax] > photonCuts[5] ) continue ;

if ( max_gPt < photonCuts[1] ) continue ;
//if ( n_pho > photonCuts[6] ) continue ;

// Get Leading Jet Kinematics 
double max_jPt = 0;
int    n_jets = 0 ;
for ( int j = 0; j < nJets; j++){
     TLorentzVector jp4_ = TLorentzVector(jetPx[j], jetPy[j], jetPz[j], jetE[j] ); 
     if( jp4_.Pt() < jetCuts[0] ) continue ; 
     // JetID Cuts
 
     n_jets++ ;
     // apply Jet Pt cuts
     if (jp4_.Pt() > max_jPt) {
         max_jPt = jp4_.Pt();
         j1p4    = jp4_;
        }       

   } // End of Loop Over Njets                     
cout << " Number of Jets " << n_jets << endl;
if ( ( n_jets < jetCuts[1] ) ||  ( n_jets > jetCuts[2] ) ) continue ;
          
//Reject Halos here!

// if (( sMajPho[kmax] > HaloCuts[0]) && ( cscdPhi[kmax] < HaloCuts[1] )) continue;
// Debugging 
if( n_jets == 0) { cout << "0-Jets Events have  Photon variables " << g1P4.Pt() << " Eta " << g1P4.Eta() 
<< " Phi " << g1P4.Phi() << " Energy " << g1P4.E() << " Numb of Photons = " << n_pho <<  endl; }
            

// have to take care of pseudorapidity V.Eta() == 0 cases!
my.photimeVsPU->Fill(totalNVtx,seedTime[kmax]);
my.h_Time->Fill( seedTime[kmax] );
my.WAveSeedBCphotime->Fill( aveTime1[kmax] );
my.AveSCphotime->Fill( aveTime[kmax] );
my.ph_smin->Fill(sMinPho[kmax] );
my.ph_smaj ->Fill(sMajPho[kmax] );
my.ph_HoverE ->Fill(phoHoverE[kmax]);
//Eta Dependence studies
my.phoTimeVsEta->Fill( g1P4.Eta(),seedTime[kmax] );  
my.phoTimeVsE->Fill ( g1P4.E(), seedTime[kmax] ) ;
my.phoTimeVsPhi->Fill( g1P4.Phi(), seedTime[kmax] ) ; 

my.phoetaVsphi->Fill(g1P4.Eta(), g1P4.Phi());  // gamma eta vs phi
 
//   my.phopzOnpt->Fill( (g1P4.Pt() ? g1P4.Pz()/g1P4.Pt() : 0 ) );  // Ratio of pz/pt 

my.h_g1Pt->Fill( max_gPt );
my.ph_e ->Fill( g1P4.E() );
my.ph_z ->Fill( g1P4.Z());
phoeta = g1P4.Eta();
my.ph_eta->Fill(g1P4.Eta());
my.ph_phi->Fill(g1P4.Phi());
thetapho = 2*TMath::ATan(TMath::Exp(-phoeta));  // Photon Angle
pho_gravtheta = thetapho - thetamet;
my.phomet_thetadiff->Fill(g1P4.Eta() - (-TMath::Log(TMath::Tan(thetamet/2)))); 
massNt = TMath::Sqrt(2*max_gPt*met*(1 - TMath::Cos(pho_gravtheta)) );
my.phomet_thetadiff->Fill(pho_gravtheta);
my.npho ->Fill(n_pho); 
my.pho_angle ->Fill(thetapho);
my.pu_vtx->Fill(totalNVtx);
// Isolation Variabs          
my.pho_EcalIso->Fill(phoEcalIso[kmax]);
my.pho_HcalIso->Fill(phoHcalIso[kmax]);
// my.hcal_Iso->Fill(HcalIso[kmax]);
my.pho_TrkIso->Fill(phoTrkIso[kmax]);

my.pho_Ecal_IsoVsPU->Fill(totalNVtx,phoEcalIso[kmax]);
my.pho_Trk_IsoVsPU->Fill(totalNVtx,phoTrkIso[kmax]);
my.pho_Hcal_IsoVsPU->Fill(totalNVtx, phoHcalIso[kmax]);
// my.Hcal_IsoVsPU->Fill(totalNVtx,HcalIso[kmax]);
my.sMinorVsPU->Fill(totalNVtx,sMinPho[kmax]);

// Fill Photon CSC related Infors
my.phoCSCtime->Fill(cscTime[kmax]);
my.pho_CSCdphi->Fill(cscdPhi[kmax]);
my.phonBC->Fill(nBC[kmax]);
my.phonXtal->Fill(nXtals[kmax]);
//my.phosigmaietaieta->Fill(sigmaEta[kmax]);

my.pho_timeVsCSCdphi->Fill(cscdPhi[kmax], seedTime[kmax]);
//EB and EE plots
if( fabs(g1P4.Eta()) < 1.479 ) {
my.pho_timeVsEtaEB->Fill(g1P4.Eta(), seedTime[kmax]);
my.pho_timeVsPhiEB->Fill(g1P4.Phi(), seedTime[kmax]);
my.pho_sminorEB->Fill(sMinPho[kmax]);
my.pho_smajorEB->Fill(sMajPho[kmax]);
my.pho_sigmaEtaEB->Fill(sigmaEta[kmax]);
my.pho_timeEB->Fill(seedTime[kmax]);
my.pho_num_phoEB->Fill(n_pho);
my.pho_num_jetEB->Fill(n_jets);
// Treating - & + time Seperately)
if( seedTime[kmax] < -2 ) {
my.pho_LN2timeEB->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > -2 ) && (seedTime[kmax] < 2) ) {
my.pho_LN2GP2timeEB->Fill(seedTime[kmax]);
}else {
my.pho_GP2timeEB->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > 2 ) { 
my.pho_ATG2_sigmaEtaEB->Fill(sigmaEta[kmax]);
my.pho_ATG2_sminorEB->Fill(sMinPho[kmax]);
my.pho_ATG2_smajorEB->Fill(sMajPho[kmax]);
 }

}else{
my.pho_timeVsEtaEE->Fill(g1P4.Eta(), seedTime[kmax]);
my.pho_timeVsPhiEE->Fill(g1P4.Phi(), seedTime[kmax]);
my.pho_sminorEE->Fill(sMinPho[kmax]);
my.pho_smajorEE->Fill(sMajPho[kmax]);
my.pho_sigmaEtaEE->Fill(sigmaEta[kmax]);
my.pho_timeEE->Fill(seedTime[kmax]);
my.pho_num_phoEE->Fill(n_pho);
my.pho_num_jetEE->Fill(n_jets);
// Treating - & + time Seperately)
if( seedTime[kmax] < -2 ) {
my.pho_LN2timeEE->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > -2 ) && (seedTime[kmax] < 2) ) {
my.pho_LN2GP2timeEE->Fill(seedTime[kmax]);
}else {
my.pho_GP2timeEE->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > 2 ) { 
my.pho_ATG2_sigmaEtaEE->Fill(sigmaEta[kmax]);
my.pho_ATG2_sminorEE->Fill(sMinPho[kmax]);
my.pho_ATG2_smajorEE->Fill(sMajPho[kmax]);
 }

}

// For Leading Jets
my.j_pt->Fill(max_jPt); // Jet With Largest Pt
my.jet_eta->Fill(j1p4.Eta() );
my.jet_phi->Fill(j1p4.Phi() );
my.evt_met->Fill(met);
my.metVsPU->Fill(totalNVtx, met); // PU effect?
my.mettheta->Fill(thetamet);
my.MassNt->Fill(massNt); 
my.njets->Fill(n_jets);
my.jp_deta->Fill( j1p4.Eta() - g1P4.Eta() );
my.jp_dphi->Fill ( j1p4.Phi() - g1P4.Phi() ) ;


// Halo Related Issues
float hphodphi = fabs (haloPhi - g1P4.Phi());
float hphodrho = fabs (haloRho - g1P4.Rho());

my.pho_halodphi->Fill(hphodphi);
my.pho_halodrho->Fill(hphodrho);

hphodphi = (hphodphi > 3.1416 ) ? 6.2832 - hphodphi : hphodphi ;
float dphi = 0; 
float drho = 0;
//float nhaloBC = 0;
//float nhaloXtal = 0;
// My Criteria for anything Halo-like
//if(IscscHaloSeg_Tag || IscscHaloTrk_Tag || IsBeamHaloIDTightTag || IscscHaloTight_Tag ) {

if (( sMajPho[kmax] > HaloCuts[0]) && ( cscdPhi[kmax] < HaloCuts[1] )) { // Our Refined Tight Halo Criteria
gHP4 = g1P4 ; 
dphi = fabs( haloPhi - g1P4.Phi() ); 
drho = fabs ( haloRho - g1P4.Rho() ) ; 
//nhaloBC = nBC[kmax];
//nhaloXtal = nXtals[kmax];
my.halo_phodrho->Fill( drho);
my.halo_phodphi->Fill(dphi); 

Hg.halo_etaVsphi->Fill(gHP4.Eta(),gHP4.Phi()); 
Hg.halo_phiVsStime->Fill(gHP4.Phi(),seedTime[kmax]);
Hg.halo_phiVsBCtime->Fill(gHP4.Phi(),aveTime1[kmax]); 
Hg.halo_phiVsSCtime->Fill(gHP4.Phi(),aveTime[kmax]); 
Hg.halo_etaVsStime->Fill(gHP4.Eta(),seedTime[kmax]);
Hg.halo_etaVsBCtime->Fill(gHP4.Eta(),aveTime1[kmax]); 
Hg.halo_etaVsSCtime->Fill(gHP4.Eta(),aveTime[kmax]); 
Hg.halo_rhoVsphi->Fill(haloRho, haloPhi); 
Hg.halo_seedTime->Fill(seedTime[kmax]);
Hg.halo_wavBCtime->Fill(aveTime1[kmax]);
Hg.halo_wavSCtime->Fill(aveTime[kmax]);
//1 d plots
//Hg.halo_pzOnpt->Fill(gHP4.Pz()/gHP4.Pt()); 
Hg.halo_nBC->Fill(nBC[kmax]);
Hg.halo_nXtal->Fill(nXtals[kmax]);
Hg.halo_rho->Fill(haloRho);
Hg.halo_phi->Fill(gHP4.Phi());
//Hg.halo_sigmaietaieta->Fill(sigmaEta[kmax]);

Hg.halo_CSCdphi->Fill(cscdPhi[kmax]);
Hg.halo_timeVsCSCdphi->Fill(cscdPhi[kmax], seedTime[kmax]);
//EB and EE plots
if( fabs(g1P4.Eta()) < 1.479 ) {
Hg.halo_timeVsEtaEB->Fill(g1P4.Eta(), seedTime[kmax]);
Hg.halo_timeVsPhiEB->Fill(g1P4.Phi(), seedTime[kmax]);
Hg.halo_sminorEB->Fill(sMinPho[kmax]);
Hg.halo_smajorEB->Fill(sMajPho[kmax]);
Hg.halo_sigmaEtaEB->Fill(sigmaEta[kmax]);
Hg.halo_timeEB->Fill(seedTime[kmax]);
Hg.halo_num_phoEB->Fill(n_pho);
Hg.halo_num_jetEB->Fill(n_jets);
//treating -&+ time
if( seedTime[kmax] < -2 ) {
Hg.halo_LN2timeEB->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > -2 ) && (seedTime[kmax] < 2) ) {
Hg.halo_LN2GP2timeEB->Fill(seedTime[kmax]);
}else {
Hg.halo_GP2timeEB->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > 2 ) { 
Hg.halo_ATG2_sigmaEtaEB->Fill(sigmaEta[kmax]);
Hg.halo_ATG2_sminorEB->Fill(sMinPho[kmax]);
Hg.halo_ATG2_smajorEB->Fill(sMajPho[kmax]);
 }

}else{
Hg.halo_timeVsEtaEE->Fill(g1P4.Eta(), seedTime[kmax]);
Hg.halo_timeVsPhiEE->Fill(g1P4.Phi(), seedTime[kmax]);
Hg.halo_sminorEE->Fill(sMinPho[kmax]);
Hg.halo_smajorEE->Fill(sMajPho[kmax]);
Hg.halo_sigmaEtaEE->Fill(sigmaEta[kmax]);
Hg.halo_timeEE->Fill(seedTime[kmax]);
Hg.halo_num_phoEE->Fill(n_pho);
Hg.halo_num_jetEE->Fill(n_jets);
//treating -&+ time
if( seedTime[kmax] < -2 ) {
Hg.halo_LN2timeEE->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > -2 ) && (seedTime[kmax] < 2) ) {
Hg.halo_LN2GP2timeEE->Fill(seedTime[kmax]);
}else {
Hg.halo_GP2timeEE->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > 2 ) { 
Hg.halo_ATG2_sigmaEtaEE->Fill(sigmaEta[kmax]);
Hg.halo_ATG2_sminorEE->Fill(sMinPho[kmax]);
Hg.halo_ATG2_smajorEE->Fill(sMajPho[kmax]);
 }

}


 } // End of halo tagging

//if(nhaloBC   !=0)
//Hg.halo_phonBCratio->Fill( nhaloBC/nBC[kmax] );
//if(nhaloXtal !=0) 
//Hg.halo_phonXtalratio->Fill( nhaloXtal/nXtals[kmax] );

// Halo Tracks and segments

//Hg.halo_TrksSbeta->Fill(nTrksSmallBeta);
//Hg.halo_nhalosegs->Fill(nHaloSegs);
//Hg.halo_nhalotrk->Fill(nHaloTracks);
//Hg.halo_nOThits->Fill(nOutTimeHits);



// Plot Photon  Seed time Vs PU  
if( totalNVtx >= 0 && totalNVtx <= 7) my.tV1->Fill(seedTime[kmax]);
if( totalNVtx >  7 && totalNVtx <= 14) my.tV2->Fill(seedTime[kmax]);
if( totalNVtx > 14 && totalNVtx <= 21) my.tV3->Fill(seedTime[kmax]);
if( totalNVtx > 21 && totalNVtx <= 28) my.tV4->Fill(seedTime[kmax]);
if( totalNVtx > 28 && totalNVtx <= 35) my.tV5->Fill(seedTime[kmax]);
if( totalNVtx > 35 && totalNVtx <= 42) my.tV6->Fill(seedTime[kmax]);
if( totalNVtx > 42 && totalNVtx <= 49) my.tV7->Fill(seedTime[kmax]);
 

//if( totalNVtx > 35 && totalNVtx <= 40) my.tV8->Fill(seedTime[kmax]);
//if( totalNVtx > 40 && totalNVtx <= 45) my.tV9->Fill(seedTime[kmax]);
//if( totalNVtx > 45 && totalNVtx <= 50) my.tV10->Fill(seedTime[kmax]);
//if( totalNVtx > 50 && totalNVtx <= 55) my.tV11->Fill(seedTime[kmax]);

//Ave SC Time Vs PU
if( totalNVtx >= 0 && totalNVtx <= 7) my.tV12->Fill(aveTime[kmax]);
if( totalNVtx >  7 && totalNVtx <= 14) my.tV13->Fill(aveTime[kmax]);
if( totalNVtx > 14 && totalNVtx <= 21) my.tV14->Fill(aveTime[kmax]);
if( totalNVtx > 21 && totalNVtx <= 28) my.tV15->Fill(aveTime[kmax]);
if( totalNVtx > 28 && totalNVtx <= 35) my.tV16->Fill(aveTime[kmax]);
if( totalNVtx > 35 && totalNVtx <= 42) my.tV17->Fill(aveTime[kmax]);
if( totalNVtx > 42 && totalNVtx <= 49) my.tV18->Fill(aveTime[kmax]);

//if( totalNVtx > 35 && totalNVtx <= 40) my.tV19->Fill(aveTime[kmax]);
//if( totalNVtx > 40 && totalNVtx <= 45) my.tV20->Fill(aveTime[kmax]);
//if( totalNVtx > 45 && totalNVtx <= 50) my.tV21->Fill(aveTime[kmax]);
//if( totalNVtx > 50 && totalNVtx <= 55) my.tV22->Fill(aveTime[kmax]);

// Timing  Ave Seed BC Time PU Dependence
if( totalNVtx >= 0  &&  totalNVtx <= 6 ) my.py19->Fill(aveTime1[kmax]);
if( totalNVtx >  6  &&  totalNVtx <= 12) my.py18->Fill(aveTime1[kmax]);
if( totalNVtx > 12  &&  totalNVtx <= 18) my.py17->Fill(aveTime1[kmax]);
if( totalNVtx > 18  &&  totalNVtx <= 24) my.py16->Fill(aveTime1[kmax]);
if( totalNVtx > 24  &&  totalNVtx <= 35) my.py15->Fill(aveTime1[kmax]);
if( totalNVtx > 35  &&  totalNVtx <= 45) my.py14->Fill(aveTime1[kmax]);
if( totalNVtx > 45  &&  totalNVtx <= 55) my.py13->Fill(aveTime1[kmax]);



          
// Check weird Photon Time
// if(seedTime[kmax] >= 10){ hasweirdtime = true;};
//if( (seedTime[kmax] < -5.0) || (seedTime[kmax] > 10.0)   ){


//          Lt.ltnjets->Fill(nJets);
//          Lt.ltnpho->Fill(nPhotons);  // The Number of Photons in Event with Large Leading Photon weird time
//          Lt.ltEvtpt->Fill(max_gPt);
//          Lt.ltEvtmet->Fill(met);
//          Lt.lteta->Fill(g1P4.Eta());
//          Lt.ltphoE->Fill(g1P4.E());
//          Lt.ltphi->Fill(g1P4.Phi());
//          Lt.ltnvtx->Fill(totalNVtx);

//          cout << "Has NJets= " << nJets  << "\t" << " Has NPhotons= " << nPhotons << "\n";
//                          cout << "Photon Has Pt=  " << max_gPt << " GeV/c" << "\t"  << "Missing Energy= " << met << " GeV \n";
//                          cout << "Number of vertices= " << totalNVtx << endl;

// // Loop over its number of vertices and print out Vertext position
// for(int nv =0; nv <  totalNVtx; nv++) {
//                                          Lt.ltvtxX->Fill(vtxX[nv]);
//                                          Lt.ltvtxY->Fill(vtxY[nv]);
//                                          Lt.ltvtxZ->Fill(vtxZ[nv]);
//                                          cout << "Strange Ev't with PV from Origin : (X, Y, Z)= \t" << "(" << vtxX[nv] <<", " <<
//                                          vtxY[nv] << ", " << vtxZ[nv]  << ")" <<  endl;
//                                        }
// }  


// check for 1 Vertex events
//TLorentzVector p1P4(0,0,0,0); //,j1p4(0,0,0,0)  ; // If I need Leading JetPt too!
//double max_pPt  = 0 ; // Max Photon Pt

// single vertex events
//if (totalNVtx == 1){

//Sv.svtxnjets->Fill(nJets);
//Sv.svtxEvtmet->Fill(met); 
//Sv.svtxnpho->Fill(nPhotons);
// Loop over all the Photons in 1 vertex Event and Get Leading Pt Photon
//for ( int k=0; k< nPhotons; k++) {
//TLorentzVector pP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
//if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
// if ( pP4_.Pt() > max_pPt ) {
//      max_pPt = pP4_.Pt() ;
//      p1P4 = pP4_ ;
//      }  
//Sv.svtxEvtpt->Fill(max_pPt);
// Sv.svtxeta->Fill(p1P4.Eta());
// Sv.svtxphi->Fill(p1P4.Phi());
// Sv.svtxnvtx->Fill(totalNVtx); // Making sure NVertices is 1 --debug
// Sv.svtxX->Fill(vtxX[0]);     // Single vertex is 1st elem of Array?                                 
// Sv.svtxY->Fill(vtxY[0]);                           
// Sv.svtxZ->Fill(vtxZ[0]);
// cout <<"1 Vtx Event Has\n" << " Number of Jets=: " 
// << nJets << " ," << " With Number of Photons:= " << nPhotons  << "\t" << " Missing Energy:= " << met << endl;
// cout << "single vertex position at : (X, Y, Z) =  " << "(" << vtxX[0] <<", " << vtxZ[0] << ", " << vtxZ[0] << ")"<<  endl;
 //   }

//  } // End of Loop over Nvtx = 1 Events 

int evtId = eventId ; 
int Entry  = i ;          
printf("\nEvent Now has Event ID: %d \n",  evtId);
printf("\n Entry Now is Entry :  %d \n", Entry );


} // end of event looping

  
Make_Plots();

Writehists();


cout << "I just finished Writing my Histograms!" << endl;

f->Close();
 

} // End of ReadTree()
