// from: https://twiki.cern.ch/twiki/bin/view/CMS/ECALLaserMonitoringAnalysisWG1
// necessary to access the ntuple of Ferri's making

// numWavelengths is the number of wavelenghts _held_ by the ntuple
 // if you change this, mind to change the Branch declaration of TTree...
#define numWavelengths 3

struct ntu_xtals {
  
//  // constructur just to initialize numWavelengths
// ntu_xtals::ntu_xtals( const int numWavelengthspass)
//    : numWavelengths(numWavelengthspass)
//  {;}
//  const int numWavelengths; 

  int   run;
  int   seq;
  int   fed;
  int   ix;
  int   iy;
  int   iz;
  int   detId;
  int   elecId;
  int   harness;
  int   side;
  float eta;
  float phi;
  float field;
  float alpha;
  int   wl[numWavelengths];
  int   time[numWavelengths];
  int   nevt[numWavelengths];
  int   laser_power[numWavelengths];
  int   vinj[numWavelengths];
  int   nxtal25[numWavelengths];
  int   npn[numWavelengths];
  int   vfe_mode[numWavelengths];
  int   mem_gain[numWavelengths];
  int   numfill[numWavelengths];
  float lumi[numWavelengths];
  float qmax[numWavelengths];
  float qmaxS[numWavelengths];
  float tmax[numWavelengths];
  float apdpnA[numWavelengths];
  float apdpnAS[numWavelengths];
  float apdpnB[numWavelengths];
  float apdpnBS[numWavelengths];
  float apdpnAB[numWavelengths];
  float apdpnABS[numWavelengths];
  float ped[numWavelengths];
  float pedS[numWavelengths];
  float ped_tp[numWavelengths];
  float ped_tpS[numWavelengths];
  float ped_laser[numWavelengths];
  float ped_laserS[numWavelengths];
  float tp[numWavelengths];
  float tpS[numWavelengths];
  float corrwidth[numWavelengths];
  float apdapdA[numWavelengths];
  float apdapdAS[numWavelengths];
  float apdapdB[numWavelengths];
  float apdapdBS[numWavelengths];
  float l_ampli[numWavelengths];
  float l_rise_time[numWavelengths];
  float l_fwhm[numWavelengths];
  float l_width90[numWavelengths];
  float l_width95[numWavelengths];
  float l_prepulse[numWavelengths];
  float l_nphot0[numWavelengths];
  float l_nphot1[numWavelengths];
  float l_nphot2[numWavelengths];
  float l_nphot3[numWavelengths];
  float l_nphot4[numWavelengths];
  float pnA_qmax[numWavelengths];
  float pnA_qmaxS[numWavelengths];
  float pnA_pnpnB[numWavelengths];
  float pnA_pnpnBS[numWavelengths];
  float pnA_corrwidth[numWavelengths];
  float pnA_ped[numWavelengths];
  float pnA_pedS[numWavelengths];
  float pnA_tp_ped[numWavelengths];
  float pnA_tp_pedS[numWavelengths];
  float pnA_l_ped[numWavelengths];
  float pnA_l_pedS[numWavelengths];
  float pnA_tp[numWavelengths];
  float pnA_tpS[numWavelengths];
  float pnB_qmax[numWavelengths];
  float pnB_qmaxS[numWavelengths];
  float pnB_pnpnB[numWavelengths];
  float pnB_pnpnBS[numWavelengths];
  float pnB_corrwidth[numWavelengths];
  float pnB_ped[numWavelengths];
  float pnB_pedS[numWavelengths];
  float pnB_tp_ped[numWavelengths];
  float pnB_tp_pedS[numWavelengths];
  float pnB_l_ped[numWavelengths];
  float pnB_l_pedS[numWavelengths];
  float pnB_tp[numWavelengths];
  float pnB_tpS[numWavelengths];
};
