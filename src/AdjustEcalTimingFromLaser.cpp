
// Calculate the Timing Shift from Laser data
// and stores the shift with CCUId in textfiles
// @laTEN Feb 2012


// Include Ecal Stuff Here!
#include "DQM/EcalCommon/interface/Numbers.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/EcalScDetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "Geometry/EcalMapping/interface/EcalElectronicsMapping.h"
#include "DataFormats/EcalDetId/interface/EcalElectronicsId.h"

// C++    stuffs
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TChain.h"
#include "TFile.h"
#include "TProfile2D.h"
#include "TCanvas.h"
#include "TStyle.h"

// Get CCU Timing.
//#include "CalibCalorimetry/EcalTiming/bin/GetCCUIdAndTimeFromTProfileHist.h"

#define NWL 3 // if you change this, mind to change the Branch declaration of TTree...
#define ETA_NBIN 100
#define ETA_MIN   -3.
#define ETA_MAX   +3.


#define RunB4TS  163291 //163297//163291 //163332 //162765 //161020//161018//160111 //176455 //159218 //175573  //178854 //178731  // 162518 //160147    // 176652  // 160138    // 160133       // 160111 // 159784 //175832  // 175354 //159784 //1611175
#define RunAFTS  163333 //163483 //163333 //163869 //163078//162765 //162764 //160138 //177727 //160006 //177930 //178241


// defineDirectoryname

//GetCCUIdandTimeShift
//GetCCUIdAndTimeFromTProfileHist getCCUId;

//const std::string dir ="LaserTimingShiftRun1632901VsRun163333/";

const int numEBFed  = 36;
const int maxNumCCUInFed = 68;
const int maxNumXtalInCCU = 25;
const int numSC = 9;
//  Want to do CCU Id timing.
const  int EBMaxSM  = 36;
//const  int maxNumCCUInFed  = EcalTrigTowerDetId::kEBTowersPerSM+2;
const   int maxEEsm = 18;
const  int maxXtalInCCU = 25;

// Set Max and Min on Each Runs.
const int  binlow = -50.0;
const int  binhigh = 50.0;


// SetMaximum Minimum of Bins on TimeshiftHist
const int lbin = -5.0;
const int hbin =  5.0;


// EB runA
//float CCUInFedTimesEB_runA[EBMaxSM][70][maxXtalInCCU];
float CCUInFedTimesEB_runA[EBMaxSM][maxNumCCUInFed];
int  CCUInFedNumEntriesEB_runA[EBMaxSM][maxNumCCUInFed];

//EB  Run B		  
//float CCUInFedTimesEB_runB[EBMaxSM][70][maxXtalInCCU];
float CCUInFedTimesEB_runB[EBMaxSM][maxNumCCUInFed];
int  CCUInFedNumEntriesEB_runB[EBMaxSM][maxNumCCUInFed];

// EEP RunA
//float CCUInFedTimesEE[maxEEsm][maxNumCCUInFed][maxXtalInCCU];
float CCUInFedTimesEEP_runA[numSC][maxNumCCUInFed];		
int  CCUInFedNumEntriesEEP_runA[numSC][maxNumCCUInFed];

// EEP run B
float CCUInFedTimesEEP_runB[numSC][maxNumCCUInFed];		
int  CCUInFedNumEntriesEEP_runB[numSC][maxNumCCUInFed];


// EEM RunA
//float CCUInFedTimesEE[maxEEsm][maxNumCCUInFed][maxXtalInCCU];
float CCUInFedTimesEEM_runA[numSC][maxNumCCUInFed];		
int  CCUInFedNumEntriesEEM_runA[numSC][maxNumCCUInFed];

// EEM run B
float CCUInFedTimesEEM_runB[numSC][maxNumCCUInFed];		
int  CCUInFedNumEntriesEEM_runB[numSC][maxNumCCUInFed];



// EB Histos
TProfile2D*   CCUAvgTimeEB_RunA[numEBFed];

TProfile2D*   CCUAvgTimeEB_RunB[numEBFed];

// EE histos
TProfile2D* CCUAvgTimeEEP_RunA[9];
TProfile2D* CCUAvgTimeEEM_RunA[9];

TProfile2D* CCUAvgTimeEEP_RunB[9];
TProfile2D* CCUAvgTimeEEM_RunB[9];


// Create Array of Hprof
TProfile2D* CCUTimeShiftEB[numEBFed];

TProfile2D* CCUTimeShiftEEP[numSC];

TProfile2D* CCUTimeShiftEEM[numSC];

TProfile2D* CrysTimeShiftEB;
TProfile2D* CrysTimeShiftEEP;
TProfile2D* CrysTimeShiftEEM;
// NewHist for 5by5 binning
//runA
TProfile2D* ccutimeEBrunA;
TProfile2D* ccutimeEEPrunA;
TProfile2D* ccutimeEEMrunA;
//runB
TProfile2D* ccutimeEBrunB;
TProfile2D* ccutimeEEPrunB;
TProfile2D* ccutimeEEMrunB;

// Timeshift
TProfile2D* ccutshiftEB;
TProfile2D* ccutshiftEEP;
TProfile2D* ccutshiftEEM;


///// 1D ccu timing here!

// Now Fill CCU histograms:
// TH1F* ccuInFedEBtimeRunA[EBMaxSM][maxNumCCUInFed];
// TH1F* ccuInFedEBtimeRunB[EBMaxSM][maxNumCCUInFed];
// TH1F* ccuInFedEBtimeshift[EBMaxSM][maxNumCCUInFed];


// EB
TH1F* ccuInFedEBtimeRunA[EBMaxSM];
TH1F* ccuInFedEBtimeRunB[EBMaxSM];
TH1F* ccuInFedEBtimeshift[EBMaxSM];

TH1F* ebccutimedistrunA;
TH1F* ebccutimedistrunB;
TH1F* ebccutimedistshift;

// For EE Plus
TH1F* ccuInFedEEPtimeRunA[numSC];
TH1F* ccuInFedEEPtimeRunB[numSC];
TH1F* ccuInFedEEPtimeshift[numSC];

// For EE  Minus
TH1F* ccuInFedEEMtimeRunA[numSC];
TH1F* ccuInFedEEMtimeRunB[numSC];
TH1F* ccuInFedEEMtimeshift[numSC];

TH1F* eepccutimedistrunA;
TH1F* eepccutimedistrunB;
TH1F* eepccutimedistshift;

TH1F* eemccutimedistrunA;
TH1F* eemccutimedistrunB;
TH1F* eemccutimedistshift;


using namespace std;

TFile *savefile; 

struct ntu_xtals {
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
    int   wl[NWL];
    int   time[NWL];
    int   nevt[NWL];
    int   laser_power[NWL];
    int   vinj[NWL];
    int   nxtal25[NWL];
    int   npn[NWL];
    int   vfe_mode[NWL];
    int   mem_gain[NWL];
    int   numfill[NWL];
    float lumi[NWL];
    float qmax[NWL];
    float qmaxS[NWL];
    float tmax[NWL];
    float apdpnA[NWL];
    float apdpnAS[NWL];
    float apdpnB[NWL];
    float apdpnBS[NWL];
    float apdpnAB[NWL];
    float apdpnABS[NWL];
    float ped[NWL];
    float pedS[NWL];
    float ped_tp[NWL];
    float ped_tpS[NWL];
    float ped_laser[NWL];
    float ped_laserS[NWL];
    float tp[NWL];
    float tpS[NWL];
    float corrwidth[NWL];
    float apdapdA[NWL];
    float apdapdAS[NWL];
    float apdapdB[NWL];
    float apdapdBS[NWL];
    float l_ampli[NWL];
    float l_rise_time[NWL];
    float l_fwhm[NWL];
    float l_width90[NWL];
    float l_width95[NWL];
    float l_prepulse[NWL];
    float l_nphot0[NWL];
    float l_nphot1[NWL];
    float l_nphot2[NWL];
    float l_nphot3[NWL];
    float l_nphot4[NWL];
    float pnA_qmax[NWL];
    float pnA_qmaxS[NWL];
    float pnA_pnpnB[NWL];
    float pnA_pnpnBS[NWL];
    float pnA_corrwidth[NWL];
    float pnA_ped[NWL];
    float pnA_pedS[NWL];
    float pnA_tp_ped[NWL];
    float pnA_tp_pedS[NWL];
    float pnA_l_ped[NWL];
    float pnA_l_pedS[NWL];
    float pnA_tp[NWL];
    float pnA_tpS[NWL];
    float pnB_qmax[NWL];
    float pnB_qmaxS[NWL];
    float pnB_pnpnB[NWL];
    float pnB_pnpnBS[NWL];
    float pnB_corrwidth[NWL];
    float pnB_ped[NWL];
    float pnB_pedS[NWL];
    float pnB_tp_ped[NWL];
    float pnB_tp_pedS[NWL];
    float pnB_l_ped[NWL];
    float pnB_l_pedS[NWL];
    float pnB_tp[NWL];
    float pnB_tpS[NWL];
};

// TProfile2D* CCUAvgTimingEBplus[18];   //= {610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627};
// TProfile2D* CCUAvgTimingEBminus[18];   //= {628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645};

TProfile2D* FedAvgTimingEB;
TProfile2D* FedAvgTimingEEP;
TProfile2D* FedAvgTimingEEM;
// Run B
TProfile2D* FedAvgTimingEB_RunB;
TProfile2D* FedAvgTimingEEP_RunB;
TProfile2D* FedAvgTimingEEM_RunB;


// TH1F* CCUTimeDiffPlot = new TH1F("CCUTimeDiffPlot","Time Shift Of CCU in EB FED",100, -2.5 , 2.5);
// TH1F* CCUTimeB4TS = new TH1F("CCUTimeB4TS","CCU Time  in EB FED Before TS", 100, -2.5, 2.5);
// TH1F* CCUTimeAFTS = new  TH1F("CCUTimeAFTS","CCU Time in EB FED After TS", 100, -2.5, 2.5);


// Xatl time Vs Amplitude EB and EE
TH2F*   XtaltimeVsAmpEB = new TH2F("XtaltimeVsAmpEB", "Crystal In EB Time Vs Amplitude",  100, 0, 4000,100, binlow, binhigh );
TH2F*   XtaltimeVsAmpEE = new TH2F("XtaltimeVsAmpEE", "Crystal In EE Time Vs Amplitude",  100, 0, 4000,100, binlow, binhigh );
//  Time of 1d
TH1F*  xtaltimeDistEB = new TH1F("xtaltimeEB","Crystal Time Distrubution",100, binlow, binhigh);
TH1F*  xtaltimeDistEE = new TH1F("xtaltimeEE","Crystal Time Distrubution",100, binlow, binhigh);


// Xtal time Vs Time Measured EB and EE
//TH2F*   XtaltimeVsTimeEB = new TH2F("XtaltimeVsTimeEB", "Crystal  In EB Time  Vs Time Measured", 100, 0, 10000000, 100, -25, 25 ); 
//TH2F*   XtaltimeVsTimeEE = new TH2F("XtaltimeVsTimeEE", "Crystal  In EE Time  Vs Time Measured", 100, 0, 10000000,100, -25, 25 );
// Xtal time Vs FedId
TH2F*   XtaltimeVsFedIDEB = new TH2F("XtaltimeVsFedIDEB", "Crystal Time[ns] Vs FedId In EB only", 54, 601, 655, 100, binlow, binhigh );
TH2F*   XtaltimeVsFedIDEE = new TH2F("XtaltimeVsFedIDEE","Crystal Time[ns] Vs FedId In EE Only",  54,  601,  655, 100, binlow, binhigh); 
//Xtal Time Vs Lumi
TH2F*   XtaltimeVsLumiEB = new TH2F("XtaltimeVsLumiEB", "Crystal  In EB Time  Vs Lumi", 100, 0, 4000,100, binlow, binhigh );
// xtak Time Vs Eta EB   
TH2F*   XtaltimeVsEta = new TH2F("XtaltimeVsEta", "Crystal  In EB Time  Vs Eta", 10, -3, 3,100, binlow, binhigh );
//xtal Time Vs Run Number
TH2F*   XtaltimeVsRun = new TH2F("XtaltimeVsRun", "Crystal  In EB Time  Vs Run Number", 100, 150000, 190000, 100, binlow, binhigh);


TH1F* EBP1Dtime =  new TH1F("EBP1Dtime","EB-1 Timing [ns]", 100, binlow, binhigh);
TH1F* EBM1Dtime =  new TH1F("EBM1Dtime","EB+1 Timing [ns]", 100, binlow, binhigh);

// Run Bs
// Xatl time Vs Amplitude EB and EE
TH2F*   XtaltimeVsAmpEB_RunB = new TH2F("XtaltimeVsAmpEB_RunB", "Crystal In EB Time Vs Amplitude",  100, 0, 4000,100, binlow, binhigh );
TH2F*   XtaltimeVsAmpEE_RunB = new TH2F("XtaltimeVsAmpEE_RunB", "Crystal In EE Time Vs Amplitude",  100, 0, 4000,100, binlow, binhigh );
//  Time of 1d
TH1F*  xtaltimeDistEB_RunB = new TH1F("xtaltimeEB_RunB","Crystal Time Distrubution",100, binlow, binhigh);
TH1F*  xtaltimeDistEE_RunB = new TH1F("xtaltimeEE_RunB","Crystal Time Distrubution",100, binlow, binhigh);


// Xtal time Vs Time Measured EB and EE
//TH2F*   XtaltimeVsTimeEB = new TH2F("XtaltimeVsTimeEB", "Crystal  In EB Time  Vs Time Measured", 100, 0, 10000000, 100, -25, 25 ); 
//TH2F*   XtaltimeVsTimeEE = new TH2F("XtaltimeVsTimeEE", "Crystal  In EE Time  Vs Time Measured", 100, 0, 10000000,100, -25, 25 );
// Xtal time Vs FedId
TH2F*   XtaltimeVsFedIDEB_RunB = new TH2F("XtaltimeVsFedIDEB_RunB", "Crystal Time[ns] Vs FedId In EB only", 54, 601, 655, 100, binlow, binhigh );
TH2F*   XtaltimeVsFedIDEE_RunB = new TH2F("XtaltimeVsFedIDEE_RunB","Crystal Time[ns] Vs FedId In EE Only",  54,  601,  655, 100, binlow, binhigh); 
//Xtal Time Vs Lumi
TH2F*   XtaltimeVsLumiEB_RunB = new TH2F("XtaltimeVsLumiEB_RunB", "Crystal  In EB Time  Vs Lumi", 100, 0, 4000,100, binlow, binhigh );
// xtak Time Vs Eta EB   
TH2F*   XtaltimeVsEta_RunB = new TH2F("XtaltimeVsEta_RunB", "Crystal  In EB Time  Vs Eta", 10, -3, 3,100, binlow, binhigh );
//xtal Time Vs Run Number
TH2F*   XtaltimeVsRun_RunB = new TH2F("XtaltimeVsRun_RunB", "Crystal  In EB Time  Vs Run Number", 100, 150000, 190000, 100, binlow, binhigh);


TH1F* EBP1Dtime_RunB =  new TH1F("EBP1Dtime_RunB","EB-1 Timing [ns]", 100, binlow, binhigh);


TH1F* EBM1Dtime_RunB =  new TH1F("EBM1Dtime_RunB","EB+1 Timing [ns]", 100, binlow, binhigh);





//////////// Fxn To Save Canvas In Directory ///////////////

void SaveCanvasInDir( TProfile2D* mytprof)
{

  TStyle mystyle;

  mystyle.SetPalette(1,0);
  mystyle.SetLabelColor(kBlack,"xyz");
  mystyle.SetTitleColor(kBlack);
  mystyle.SetLegendBorderSize(0.2);
  mystyle.SetStatH(0.2);
  mystyle.SetOptStat(111111);
// Sets Histogram Title at Center
//  mystyle.SetTitleX(0.5);
 // mystyle.SetTitleAlign(23);
  TCanvas myCanvas;
  myCanvas.cd();

// make Empty Bins appear white.
//int nxbins = mytprof->GetNbinsX();
//int nybins = mytprof->GetNbinsY();

// Loop over bins and set empty bins to show white.
//for(int ii=0; ii<= nybins; ii++)
//{
//  for( int jj=0; jj <= nxbins; jj++)
 //    {
 //      int bin = mytprof->GetBin(ii,jj);
 //      int nentry = mytprof->GetBinEntries(bin);
//if(nentry == 0){ mytprof->SetBinContent(bin, -999999);};
 //     }
  //}

  mytprof->GetXaxis()->SetTitle("i#phi");
  mytprof->GetYaxis()->SetTitle("i#eta");
  mytprof->Draw("colz"); // Where text happens.
  std::string filename="LaserTimingShiftRun163291VsRun163333/";
  filename += mytprof->GetTitle();
  filename += ".png";
  myCanvas.Print(filename.c_str());
  
} // end of fxn to save canvas.


// New Function To Save  1 Dist Hist
void Savehist(TH1F* myhist)
{

   TStyle mystyle;

  mystyle.SetPalette(1,0);
  mystyle.SetLabelColor(kBlack,"xyz");
  mystyle.SetTitleColor(kBlack);
  mystyle.SetLegendBorderSize(0.2);
  mystyle.SetStatH(0.2);
  mystyle.SetOptStat(111111);

  TCanvas myc;
  myc.cd();
  myhist->GetXaxis()->SetRangeUser(lbin,hbin);
  myhist->GetXaxis()->SetTitle("Time Shift[ns]");
  myhist->GetYaxis()->SetTitle("Number of CCUs");  
  myhist->Draw(); // Where text happens.
  std::string filename="LaserTimingShiftRun163291VsRun163333/";
  filename += myhist->GetTitle();
  filename += ".png";
  myc.Print(filename.c_str());
  
}



//********* Fxn to Get CCUId and TimeShift*********/////

void GetCCUIdandTimeshiftTProfileHist(TProfile2D* myprof,  int iz)
{
  //Get number bins in XY
  int nxbins = myprof->GetNbinsX();
  int nybins = myprof->GetNbinsY();

  ofstream CCUIdeb, CCUIdeep, CCUIdeem;

  CCUIdeb.open("CCUId_In_EB_And_TimeShift.txt",fstream::in | fstream::out);

  CCUIdeep.open("CCUId_In_EEPlus_And_TimeShift.txt",fstream::in | fstream::out);

  CCUIdeem.open("CCUId_In_EEMinus_And_TimeShift.txt",fstream::in | fstream::out);
  

  //EB    In EB CCU == Trigger Tower
//  std::vector<EcalTrigTowerDetId> CCUIdVecEB;
  std::vector<int> CCUIdVecEB;
  std::vector<float> CCUIdTimeEB;

  // EE Plus  // CCU seen as SuperCrystal in EE..Not as Trigger Tower As Normally done!
//  std::vector<EcalScDetId> CCUIdVecEEP;
  std::vector<int> CCUIdVecEEP;
  std::vector<float> CCUIdTimeEEP;
  //EE Minus
//  std::vector<EcalScDetId> CCUIdVecEEM;
  std::vector<int> CCUIdVecEEM;
  std::vector<float> CCUIdTimeEEM;
  

  //EB
  //  EcalTrigTowerDetId ttId;
  EBDetId ebdetId;
  
  
  //EE
  EEDetId eedetIdm;
 // EEDetId eedetIdp;  
  //EE SC
//  EcalScDetId 

 int CCUIdEB = 0; // initialise Variables for safety
 int CCUIdEE = 0;
//  EcalScDetId CCUIdP;

// create Electronics Mapping object
// EcalElectronicsMapping  elecIdmapping;
  

  // Read CCU Id and Timeshift into file 
  if (iz == 0) 
	{

	  for( int nx = 1; nx < nxbins+1; nx++)   // iphi bin
		{
		  for(int ny = 1; ny <  nybins+1; ny++)  // ieta bin
			{
			  int bin = myprof->GetBin(nx,ny);

 			  int nentries = myprof->GetBinEntries(bin);

			  int tshift = 0; // initialise the time to zero

			  // Set timing shift for CCUs with no entries == 0
			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};

			  // Hopefully these are Phi and eta Values


		// 	  // @ la SIC
// 			  int ietaAbs = (ny < 18) ? 18 - ny : ny - 17;
// 			  int iPhi    = nx;
// 			  int zside   = (ny < 18)? -1 : 1;
// 			  int Ieta    = zside*(ietaAbs*5 -2);
// 			  int Iphi    =  iPhi*5 - 2;
			  
			  int ieta = myprof->GetYaxis()->GetBinLowEdge(ny);  // Need to do some work here!
			 
			  //  int Ieta = ieta; //   zside*ieta;
			  int iphi = myprof->GetXaxis()->GetBinLowEdge(nx);
		

		cout << "Gloobal Bin " << bin << " has entries " << nentries << " and bin number nx, ny = " << nx << ", " << ny << "\t and ieta, iphi = " << ieta << ", " << iphi << endl;
			  // if(EcalTrigTowerDetId::validDetId(iz,eb,nx,ny))
			  
			  //  ttId = EcalTrigTowerDetId(iz,eb,nx,ny);
			  //  EcalTrigTowerDetId ttId(0,1,ieta,iphi,0);  //subdet ==1 and mode ==0 for EcalBarel

// skip Bad Ieta nd Iphi Values:
if(iphi < 1 || iphi > 360 || ieta < -85 || ieta > 85 ) continue;
			 
// check for negative phi bins
//if(iphi < 1 || iphi > 360 || ieta < -85 || ieta > 85 ) { cout << "arrrh! Bad Bin with wong iphi has iphi = " << iphi << "and  ieta = " << ieta << ", Its bin is nx, ny = " << nx << ", " << ny << " and Bin is = " << bin << " from hist " << myprof->GetTitle() << endl; }
                    // first check if DetId is valid and skip if invalid

  //                   EBDetId::validDetId(ieta,iphi);
 if( !EBDetId::validDetId(ieta,iphi) ) { std::cout << "invalid EBdetID ieta: " << ieta << "\t iphi: " << iphi << std::endl;  continue; }
 else{ std::cout << "VALID EBdetID ieta: " << ieta << "\t iphi: " << iphi << std::endl; }

 // if ((ieta== 1 || iphi==1)){std::cout << " why?  ieta ==1 and iph ==1 is messed up" << std::endl;continue;}
 //  else {


 std::cout << " I am Happy up till here!" << std::endl;
 
 // Create DetId
  EBDetId ebdetId(ieta,iphi);
  // EBDetId ebdetId;
 // int iz =0;
 // check valid TTId
 // if(EcalTrigTowerDetId::validDetId(iz,1,ieta, iphi))

  std::cout << " I am might be happy here " << std:: endl;
  
 if(EBDetId::validDetId(ieta, iphi))
   {

	 std :: cout << " I can  create  DetId but ... " << std::endl;
	 //	 CCUIdEB =  EcalTrigTowerDetId(iz, 1, ieta, iphi, 0);
	 	 CCUIdEB =  EcalTrigTowerDetId(ebdetId);

     std :: cout << " I Did not create any CCUId  " << std::endl;
		 
   } else {  std::cout << "VALID ECalTTdetID ieta: " << ieta << "\t iphi: " << iphi << std::endl; continue; // skip bad TTdetIds
          }

					  //      }
                        // remove ieta=iphi=0 xtal
                       //   if(ebdetId.ieta()==0 && ebdetId.iphi()==0) continue;
                          // remove ieta > 85 or ieta < -85
                       //   if(ebdetId.ieta() < -85 || ebdetId.ieta() > 85) continue;  
                          // remove iphi > 0 or iphi < 361
                       //   if(ebdetId.iphi()  < 1 || ebdetId.iphi() > 360 ) continue;       

                           // Debuggin issues
	//		  int eta = ebdetId.ietaSM();
	//		  int phi = ebdetId.iphiSM();

			  // Check if EBDetId is Valid
//			  if(ebdetId.validDetId(Ieta, Iphi)){
	//			cout << " The EBDetID is " << ebdetId <<" has eta: "<< eta << " and Has Phi: "<< phi << endl;};
			  // Use DetId to Get Electronics ID
//			  const EcalElectronicsId eid = elecIdmapping.getElectronicsId(ebdetId);
			  //Numbers::map->getElectronicsId(ebdetId);
			  // From electronics Id Get CCUId
//			  int  CCUId = eid.towerId();


					      // Get SM?
					  //	      int  iSM = ebdetId.ism();
						  //     int iSM = Numbers::iSM(ebdetId);
                         // which TT/SC?
					  //    CCUIdEB = Numbers::iSC(iSM,EcalBarrel,ebdetId.ietaSM(),ebdetId.iphiSM());

					
					  
						 


// 			  // Make TT Id
// 			  EcalTrigTowerDetId ttId(CCUId);

// 			  //Get SM from TTId
// 			  unsigned iSM = Numbers::SM(ttId)
             
				//Check if ebdetId is valid. But I really have to check if CCUId is Valid though. sighhhh!
//				if(ebdetId.validDetId(Ieta,Iphi))
//				  {				 
					//			  if(ttId.validDetId(0,1,ieta,iphi))
					//				{
					//					CCUIdVecEB.push_back(ttId);
					CCUIdVecEB.push_back(CCUIdEB);	
					CCUIdTimeEB.push_back(tshift);
//				  } else continue; // continue on Invalid detId
			}			 
		  
		  
		}
	  
	  
	}else if (fabs(iz) == 1)
	{
	  
	  for( int ny =1; ny < nybins+1; ny++)
    	      {
		  for(int nx = 1; nx < nxbins+1; nx++)
	     	       {
			  
			  int bin = myprof->GetBin(ny,nx);
			  
			  int nentries = myprof->GetBinEntries(bin);

			  int tshift = 0; // initialise the time to zero

			  // Set timing shift for CCUs with no entries == 0
			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};
			  int ix = myprof->GetXaxis()->GetBinLowEdge(nx);
			  int iy = myprof->GetYaxis()->GetBinLowEdge(ny);


// skip Bad ix and iy values:
if(ix < 1 || ix > 100 || iy < 1 || iy > 100) continue;
// check for negative ix and iy bins
//if(ix < 1 || ix > 100 || iy < 1 || iy > 100) { cout << "arrrh! Bad Bin with wrong ix has iy = " << iy << "and  ix = " << ix << ", Its bin is nx, ny = " << nx << ", " << ny << " and Bin is = " << bin << " from hist " << myprof->GetTitle() << endl;}


                            //   EEDetId.validDetId(ix,iy,iz);
if( !EEDetId::validDetId(ix,iy,iz) ) { std::cout << "invalid EEdetID ix: " << ix << "\t iy: " << iy << std::endl;  continue; }
 else{ std::cout << "VALID EEdetID ix: " << ix << "\t iy: " << iy << std::endl; }



// Make EEDetID
//
// EEDetId eedetIdm(ix,iy,iz,0);
 if(EcalScDetId::validDetId(ix,iy,iz))
   {
	 CCUIdEE = EcalScDetId(ix,iy,iz);
	 
   } else {  std::cout << "VALID ECalSCdetID ix: " << ix << "\t iy: " << iy << std::endl; continue; // skip bad TTdetIds
          }
 
 //                   }
			  //Continue on bad DetId
//		  if(!eedetIdm.validDetId(ix,iy,iz)) continue;
                   // skip crys with ix=iy=0
 //                 if(eedetIdm.ix()==0 && eedetIdm.iy()==0) continue;
			   // if(EcalScDetId::validDetId(nx,ny,iz))
			   // CCUIdM = EcalScDetId(nx,ee,ny,iz);
			  
			  // Construct Super Cryst Id from detId
//			  EcalScDetId CCUIdM(eedetIdm); 

        // which SM?
			  //        int iSMee = Numbers::iSM(eedetIdm);
        // which TT/SC?
			  //			  CCUIdEE = Numbers::iSC(iSMee,EcalEndcap,eedetIdm.ix(),eedetIdm.iy());
			

//  = Numbers::getEcalScDetId(eedetIdm );
			  
			  //Get SM Id
		//	  unsigned eeSM =  Numbers::iSM(CCUIdM);
			  
			  // Now check if SC Id is valid
//			  if(Numbers::validEESc(eeSM,ix, iy))
//			  if(eedetIdm.validDetId(ix,iy,iz))
//				{
				  //	   EcalScDetId	 CCUIdM(ieta,iphi,iz); 
				  //			   if(CCUIdM.validDetId(ieta,iphi,iz))
				  //				 {
			  
			  if ( iz == -1){
				CCUIdVecEEM.push_back(CCUIdEE);
				CCUIdTimeEEM.push_back(tshift);
			  } else {
				CCUIdVecEEP.push_back(CCUIdEE);
				CCUIdTimeEEP.push_back(tshift); // fill CCU Timing shift.
				
			  }		  
 //				}else continue; // skip Invalid DetId		 
			} 
		 
		}
	   
	   
} // end of filling vecs

// kill this part b/c its repetition
//else if(iz == 1)
//	{
  	  //  Loop over XYbins
//	  for( int ny =0; ny <= nybins; ny++)
//		{
//		  for(int nx = 0; nx <= nxbins; nx++)
//			{
//			  int bin = myprof->GetBin(ny,nx);
//			  //float timeshift = myprof->GetBinContent(bin);
//
//			  
//			  int nentries = myprof->GetBinEntries(bin);
//
//			  int tshift = 0; // initialise the time to zero
//
//			  // Set timing shift for CCUs with no entries == 0
//			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};
//			  int ix = myprof->GetBinLowEdge(nx);
//			  int iy = myprof->GetBinLowEdge(ny);
//
//			  	  // Make EEDetID
//			  EEDetId eedetIdp(ix,iy,1,0);
//			   // if(EcalScDetId::validDetId(nx,ny,iz))
//			   // CCUIdM = EcalScDetId(nx,ee,ny,iz);
//
//			  	  //Continue on bad DetId
//			  if(!eedetIdp.validDetId(ix,iy,1)) continue;
//
//			  
//			  // Construc Super Cryst Id from detId
//			  EcalScDetId CCUIdP(eedetIdp); 
//			  // Numbers::getEcalScDetId(eedetIdp);
//			  
//			  //Get SM Id
//		//	  unsigned eeSM =  Numbers::iSM(CCUIdP);
//			  
//			  // Now check if SC Id is valid
//			  if(Numbers::validEESc( eeSM,ix,iy))
//			  if(eedetIdp.validDetId(ix,iy,1))
//				{		
//				  CCUIdVecEEP.push_back(CCUIdP);
//				  CCUIdTimeEEP.push_back(tshift); // fill CCU Timing shift.
//				}else continue ; // continue of Invalid detId
//			}			 
		  
//		}
//	} // end of EE Plus
  

  if(CCUIdeb.is_open()){ cout << "CCUIdEB File is open write in it" <<endl;}
  if(CCUIdeep.is_open()){ cout << "CCUIdEEP File is open, write" << endl;}
  if(CCUIdeem.is_open()){cout << " CCUIdEEM File is open, write" << endl;}


  // write EB CCUs
  if(CCUIdVecEB.size()==CCUIdTimeEB.size())
	{
	  for( unsigned ii = 0; ii <= CCUIdVecEB.size(); ii++)
		{
		  CCUIdeb << CCUIdVecEB[ii] << "Has TimeShiftOf " << CCUIdTimeEB[ii] <<"(ns)"<< "\n";
		}
	}

  //Write EEP CCUs
  
  if(CCUIdVecEEP.size()==CCUIdTimeEEP.size())
	{
	  for( unsigned ii = 0; ii < CCUIdVecEEP.size(); ii++)
		{
		  CCUIdeep << CCUIdVecEEP[ii] << "Has TimeShiftOf" << CCUIdTimeEEP[ii] <<"(ns)"<< "\n";
		}
	}

  //EEMinus
  if(CCUIdVecEEM.size()==CCUIdTimeEEM.size())
	{
	  for( unsigned ii = 0; ii <= CCUIdVecEEM.size(); ii++)
		{
		  CCUIdeem << CCUIdVecEEM[ii] << "Has TimeShift Of " << CCUIdTimeEEM[ii] <<"(ns)"<< "\n";
		}
	}

  cout << " CLose all files now" << endl;

  CCUIdeb.close();
  CCUIdeep.close();
  CCUIdeem.close();
  return;

} // end of fxn to GetCCUId and TimeShift.



//******** Function to Write Hists*************//
void writehist()
{
  savefile -> cd();

  // Timing Shift for EB
 TDirectory* TimingShiftEB = savefile->mkdir("TimingShiftFromLaserEB");
 TimingShiftEB->cd();
 for( int m = 0; m < numEBFed; m++)
   {
	 CCUTimeShiftEB[m]->GetXaxis()->SetTitle("i#phi");
	 CCUTimeShiftEB[m]->GetYaxis()->SetTitle("i#eta");
	 CCUTimeShiftEB[m]->Draw("colztext");
	 CCUTimeShiftEB[m]->Write();
   }
  CrysTimeShiftEB->GetXaxis()->SetTitle("i#phi");
  CrysTimeShiftEB->GetYaxis()->SetTitle("i#eta");
  CrysTimeShiftEB->Draw("colz");
  CrysTimeShiftEB->Write();


  //5by5 Timing shift hist
  ccutshiftEB->GetXaxis()->SetTitle("i#phi");
  ccutshiftEB->GetYaxis()->SetTitle("i#eta");
  ccutshiftEB->Draw("colz");
  ccutshiftEB->Write();

  
  
 //Timing Shift for EE plus
TDirectory* TimingShiftEEP = savefile->mkdir("TimingShiftFromLaserEEP");
 TimingShiftEEP->cd();
 for( int m = 0; m < numSC; m++)
   {
	 CCUTimeShiftEEP[m]->GetXaxis()->SetTitle("ix");
	 CCUTimeShiftEEP[m]->GetYaxis()->SetTitle("iy");
	 CCUTimeShiftEEP[m]->Draw("colztext");
	 CCUTimeShiftEEP[m]->Write();
   }
  CrysTimeShiftEEP->GetXaxis()->SetTitle("ix");
  CrysTimeShiftEEP->GetYaxis()->SetTitle("iy");
  CrysTimeShiftEEP->Draw("colz");
  CrysTimeShiftEEP->Write();
  //5by5 Timing shift hist
  ccutshiftEEP->GetXaxis()->SetTitle("ix");
  ccutshiftEEP->GetYaxis()->SetTitle("iy");
  ccutshiftEEP->Draw("colz");
  ccutshiftEEP->Write();
  
 // Timing Shift for EE Minus
TDirectory* TimingShiftEEM = savefile->mkdir("TimingShiftFromLaserEEM");
 TimingShiftEEM->cd();
 for( int m = 0; m < numSC; m++)
   {
	 CCUTimeShiftEEM[m]->GetXaxis()->SetTitle("ix");
	 CCUTimeShiftEEM[m]->GetYaxis()->SetTitle("iy");
	 CCUTimeShiftEEM[m]->Draw("colztext");
	 CCUTimeShiftEEM[m]->Write();
   }
 
  CrysTimeShiftEEM->GetXaxis()->SetTitle("ix");
  CrysTimeShiftEEM->GetYaxis()->SetTitle("iy");
  CrysTimeShiftEEM->Draw("colz");
  CrysTimeShiftEEM->Write();
  //5by5 Timing shift hist
  ccutshiftEEM->GetXaxis()->SetTitle("ix");
  ccutshiftEEM->GetYaxis()->SetTitle("iy");
  ccutshiftEEM->Draw("colz");
  ccutshiftEEM->Write();


  //  1D ccu timing shift distribution.
  TDirectory * TestPlots = savefile->mkdir("1D_CCUEBLaserTimingShift");
  
  TestPlots->cd();

  // Now write difference in CCU Time shift
  
  for( int ii = 0; ii < EBMaxSM; ii++)
	{
	  //	  for( int jj = 0; jj < maxNumCCUInFed; jj++)
	  //	{
// 		  ccuInFedEBtimeshift[ii][jj]-> GetXaxis()->SetTitle("Time Shift[ns]");
// 		  ccuInFedEBtimeshift[ii][jj]-> GetYaxis()->SetTitle("# of CCUs In Fed");
// 		  ccuInFedEBtimeshift[ii][jj]-> Draw();
// 		  ccuInFedEBtimeshift[ii][jj]-> Write();
// 		  //	
//	}
 ccuInFedEBtimeshift[ii]-> GetXaxis()->SetTitle("Time Shift[ns]");
 ccuInFedEBtimeshift[ii]-> GetYaxis()->SetTitle("# of CCUs In Fed");
 ccuInFedEBtimeshift[ii]-> Draw();
 ccuInFedEBtimeshift[ii]-> Write();
		 
		  
	}
  ///// Make Corresponding 1D dist for all CCUs in EB Here!
  ebccutimedistshift->GetXaxis()->SetTitle("Time Shift[ns]");
  ebccutimedistshift->GetYaxis()->SetTitle("# CCUs in EB");
  ebccutimedistshift->Draw();
  ebccutimedistshift->Write();
  
  //****** ID ccu timning Dist Run A *******//////
  TDirectory * ccuInEB_RunA = savefile->mkdir("1D_CCUInEBTiming_RunA");
  
  ccuInEB_RunA->cd();
  
  
  // Run A
  for( int ii = 0; ii < EBMaxSM; ii++)
	{
	  //  for( int jj = 0; jj < maxNumCCUInFed; jj++)
// 		{
// 		  ccuInFedEBtimeRunA[ii][jj]-> GetXaxis()->SetTitle("Time[ns]");
// 		  ccuInFedEBtimeRunA[ii][jj]-> GetYaxis()->SetTitle("# of CCUs In Fed");
// 		  ccuInFedEBtimeRunA[ii][jj]-> Draw();
// 		  ccuInFedEBtimeRunA[ii][jj]-> Write();
// 		}
	  ccuInFedEBtimeRunA[ii]-> GetXaxis()->SetTitle("Time[ns]");
	  ccuInFedEBtimeRunA[ii]-> GetYaxis()->SetTitle("# of CCUs In Fed");
	  ccuInFedEBtimeRunA[ii]-> Draw();
	  ccuInFedEBtimeRunA[ii]-> Write();

	}
  
///// Make Corresponding 1D dist for all CCUs in EB Here! run A
  ebccutimedistrunA->GetXaxis()->SetTitle("Time[ns]");
  ebccutimedistrunA->GetYaxis()->SetTitle("# CCUs in EB");
  ebccutimedistrunA->Draw();
  ebccutimedistrunA->Write();


  // ********** 1D ccu timing dist run B ****/////////

TDirectory * ccuInEB_RunB = savefile->mkdir("1D_CCUInEBTiming_RunB");
  
 ccuInEB_RunB->cd();
 
 // for run B
 for( int ii = 0; ii < EBMaxSM; ii++)
   {
// 	 for( int jj = 0; jj < maxNumCCUInFed; jj++)
// 	   {
// 		 ccuInFedEBtimeRunB[ii][jj]-> GetXaxis()->SetTitle("Time[ns]");
// 		 ccuInFedEBtimeRunB[ii][jj]-> GetYaxis()->SetTitle("# of CCUs In Fed");
// 		 ccuInFedEBtimeRunB[ii][jj]-> Draw();
// 		 ccuInFedEBtimeRunB[ii][jj]-> Write();
// 	   }

	 ccuInFedEBtimeRunB[ii]-> GetXaxis()->SetTitle("Time[ns]");
	 ccuInFedEBtimeRunB[ii]-> GetYaxis()->SetTitle("# of CCUs In Fed");
	 ccuInFedEBtimeRunB[ii]-> Draw();
	 ccuInFedEBtimeRunB[ii]-> Write();
	 
   }
  
 ///// Make Corresponding 1D dist for all CCUs in EB Here! run B
 ebccutimedistrunB->GetXaxis()->SetTitle("Time[ns]");
 ebccutimedistrunB->GetYaxis()->SetTitle("# CCUs in EB");
 ebccutimedistrunB->Draw();
 ebccutimedistrunB->Write();

 ///////// Directories To Hold EE 1D plots////////
 TDirectory* ccuInEE_RunA = savefile->mkdir("1DCCUInEETime_RunA");

 ccuInEE_RunA->cd();

 // For EE
 // Run A
 for( int sc = 0; sc < numSC;  sc++)
   {
	 //EEM
	 ccuInFedEEMtimeRunA[sc]->GetXaxis()->SetTitle("Time[ns]");
	 ccuInFedEEMtimeRunA[sc]->GetYaxis()->SetTitle("# of CCUs In EE- FED");
	 ccuInFedEEMtimeRunA[sc]->Draw();
	 ccuInFedEEMtimeRunA[sc]->Write();

	 // EEP
	 ccuInFedEEPtimeRunA[sc]->GetXaxis()->SetTitle("Time[ns]");
	 ccuInFedEEPtimeRunA[sc]->GetYaxis()->SetTitle("# of CCUs In EE+ FED");
	 ccuInFedEEPtimeRunA[sc]->Draw();
	 ccuInFedEEPtimeRunA[sc]->Write();
	 
   }

 // CCUs in EE 1D Time dist
 // EEM
 eemccutimedistrunA->GetXaxis()->SetTitle("Time[ns]");
 eemccutimedistrunA->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eemccutimedistrunA->Draw();
 eemccutimedistrunA->Write();
 // EEP
 eepccutimedistrunA->GetXaxis()->SetTitle("Time[ns]");
 eepccutimedistrunA->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eepccutimedistrunA->Draw();
 eepccutimedistrunA->Write();

 

 // For Run B
 TDirectory * ccuInEE_RunB = savefile->mkdir("1DCCUInEETime_RunB");

 ccuInEE_RunB->cd();
 
 // Run B
 for( int sc = 0; sc < numSC;  sc++)
   {
 	 //EEM
	 ccuInFedEEMtimeRunB[sc]->GetXaxis()->SetTitle("Time[ns]");
	 ccuInFedEEMtimeRunB[sc]->GetYaxis()->SetTitle("# of CCUs In EE- FED");
	 ccuInFedEEMtimeRunB[sc]->Draw();
	 ccuInFedEEMtimeRunB[sc]->Write();

	 // EEP
	 ccuInFedEEPtimeRunB[sc]->GetXaxis()->SetTitle("Time[ns]");
	 ccuInFedEEPtimeRunB[sc]->GetYaxis()->SetTitle("# of CCUs In EE+ FED");
	 ccuInFedEEPtimeRunB[sc]->Draw();
	 ccuInFedEEPtimeRunB[sc]->Write();

   }
 // CCUs in EE 1D Time dist
 // EEM
 eemccutimedistrunB->GetXaxis()->SetTitle("Time[ns]");
 eemccutimedistrunB->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eemccutimedistrunB->Draw();
 eemccutimedistrunB->Write();
 // EEP
 eepccutimedistrunB->GetXaxis()->SetTitle("Time[ns]");
 eepccutimedistrunB->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eepccutimedistrunB->Draw();
 eepccutimedistrunB->Write();
 

 TDirectory* ccutimeshiftEE = savefile->mkdir("1DCCUInEETimeShift");
 ccutimeshiftEE->cd(); 
 // For 1D CCU EE Time shift
 for( int sc = 0; sc < numSC;  sc++)
   {
 	 //EEM
	  ccuInFedEEMtimeshift[sc]->GetXaxis()->SetTitle("Time[ns]");
	  ccuInFedEEMtimeshift[sc]->GetYaxis()->SetTitle("# of CCUs In EE- FED");
	  ccuInFedEEMtimeshift[sc]->Draw();
	  ccuInFedEEMtimeshift[sc]->Write();

	 // EEP
	  ccuInFedEEPtimeshift[sc]->GetXaxis()->SetTitle("Time[ns]");
	  ccuInFedEEPtimeshift[sc]->GetYaxis()->SetTitle("# of CCUs In EE+ FED");
	  ccuInFedEEPtimeshift[sc]->Draw();
	  ccuInFedEEPtimeshift[sc]->Write();

   }

 // CCUs in EEP and EEM 1D time shifts

 // CCUs in EE 1D Time dist
 // EEM
 eemccutimedistshift->GetXaxis()->SetTitle("Time Shift[ns]");
 eemccutimedistshift->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eemccutimedistshift->Draw();
 eemccutimedistshift->Write();
 // EEP
 eepccutimedistshift->GetXaxis()->SetTitle("Time Shift[ns]");
 eepccutimedistshift->GetYaxis()->SetTitle("# of CCUs In EE- FED");
 eepccutimedistshift->Draw();
 eepccutimedistshift->Write();

 
 
   
 //****** New Folder to Fill EB CCUs For RunA ******/// 
TDirectory * CCUInEB_RunA = savefile->mkdir("CCUInEBFedsTime_RunA");

 CCUInEB_RunA->cd();


 XtaltimeVsAmpEB->Write();
 XtaltimeVsAmpEE->Write();
 //  XtaltimeVsTimeEB->Write();
 //  XtaltimeVsTimeEE->Write();
 XtaltimeVsFedIDEB->Write();
 XtaltimeVsFedIDEE->Write();
 
 XtaltimeVsLumiEB->Write();
 XtaltimeVsEta->Write();
 XtaltimeVsRun->Write();
  
 // 1 D timing dist
 xtaltimeDistEB->Write();
 xtaltimeDistEE->Write();


 // EB 1D tests
 EBP1Dtime->Write();
 EBM1Dtime->Write();
 
 // EB All SM
 FedAvgTimingEB->GetXaxis()->SetTitle("i#phi");
 FedAvgTimingEB->GetYaxis()->SetTitle("i#eta");
 FedAvgTimingEB->Draw("colz");
 FedAvgTimingEB->Write();
 
 
 
//EE Plus
 FedAvgTimingEEP->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEP->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEP->Draw("colz");
 FedAvgTimingEEP->Write();

 
 //EE Minus
 FedAvgTimingEEM->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEM->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEM->Draw("colz");
 FedAvgTimingEEM->Write();

 
// 5by5 binning hist runB:
//EB
ccutimeEBrunA->GetXaxis()->SetTitle("i#phi");
ccutimeEBrunA->GetYaxis()->SetTitle("i#eta");
ccutimeEBrunA->Draw("colz");
ccutimeEBrunA->Write();
//EEP
 // 5by5 binning hist runB:
ccutimeEEPrunA->GetXaxis()->SetTitle("ix");
ccutimeEEPrunA->GetYaxis()->SetTitle("iy");
ccutimeEEPrunA->Draw("colz");
ccutimeEEPrunA->Write();
//EEM
  // 5by5 binning hist runB:
ccutimeEEMrunA->GetXaxis()->SetTitle("ix");
ccutimeEEMrunA->GetYaxis()->SetTitle("iy");
ccutimeEEMrunA->Draw("colz");
ccutimeEEMrunA->Write();
 
 
for( int numfed = 0; numfed < numEBFed; numfed++)
{
// CCUAvgTimingEBplus[j]->Write();
 CCUAvgTimeEB_RunA[numfed]->GetXaxis()->SetTitle("i#phi");
 CCUAvgTimeEB_RunA[numfed]->GetYaxis()->SetTitle("i#eta");
 //  CCUAvgTimeEB_RunA[numfed]->SetTitle("CCU Mean Time Shift[ns]EB"); 
 CCUAvgTimeEB_RunA[numfed]->SetMinimum(-50);
 CCUAvgTimeEB_RunA[numfed]->SetMaximum(50); 
 CCUAvgTimeEB_RunA[numfed]->Draw("colztext");
 CCUAvgTimeEB_RunA[numfed]->Write(); 
 }


// DO EE   Here!
 for( int eeSec= 0; eeSec < 9; eeSec++)
   {
	 // for EE Plus
	 CCUAvgTimeEEP_RunA[eeSec]->GetXaxis()->SetTitle("ix");
	 CCUAvgTimeEEP_RunA[eeSec]->GetXaxis()->SetTitle("iy");
     CCUAvgTimeEEP_RunA[eeSec]->SetMinimum(-50); 	 
     CCUAvgTimeEEP_RunA[eeSec]->SetMaximum(50); 
	 CCUAvgTimeEEP_RunA[eeSec]->Draw("colztext");
	 CCUAvgTimeEEP_RunA[eeSec]->Write();

	 // for EE Minus	 
	 CCUAvgTimeEEM_RunA[eeSec]->GetXaxis()->SetTitle("ix");
	 CCUAvgTimeEEM_RunA[eeSec]->GetXaxis()->SetTitle("iy");
     CCUAvgTimeEEM_RunA[eeSec]->SetMinimum(-50); 	 
     CCUAvgTimeEEM_RunA[eeSec]->SetMaximum(50);  
	 CCUAvgTimeEEM_RunA[eeSec]->Draw("colztext");
	 CCUAvgTimeEEM_RunA[eeSec]->Write();
	 
   }


 
TDirectory* CCUInEB_RunB = savefile->mkdir("CCUInEBFedsTime_RunB");

 CCUInEB_RunB->cd();

 for( int fednum = 0; fednum < numEBFed; fednum++)
  {
	//	 CCUAvgTimeEB_RunB
	CCUAvgTimeEB_RunB[fednum]->GetXaxis()->SetTitle("i#phi");
	CCUAvgTimeEB_RunB[fednum]->GetYaxis()->SetTitle("i#eta");
	CCUAvgTimeEB_RunB[fednum]->SetMinimum(-50);
    CCUAvgTimeEB_RunB[fednum]->SetMaximum(50);
    CCUAvgTimeEB_RunB[fednum]->Draw("colztext");
    CCUAvgTimeEB_RunB[fednum]->Write(); 
	 
  }
 
// DO EE   Here!
 for( int eeSec= 0; eeSec < 9; eeSec++)
   {
	 // for EE Plus
	 CCUAvgTimeEEP_RunB[eeSec]->GetXaxis()->SetTitle("ix");
	 CCUAvgTimeEEP_RunB[eeSec]->GetXaxis()->SetTitle("iy");
     CCUAvgTimeEEP_RunB[eeSec]->SetMinimum(-50); 	 
     CCUAvgTimeEEP_RunB[eeSec]->SetMaximum(50); 
	 
	 CCUAvgTimeEEP_RunB[eeSec]->Draw("colztext");
	 CCUAvgTimeEEP_RunB[eeSec]->Write();
	 

	 // for EE Minus	 
	 CCUAvgTimeEEM_RunB[eeSec]->GetXaxis()->SetTitle("ix");
	 CCUAvgTimeEEM_RunB[eeSec]->GetXaxis()->SetTitle("iy");
	 CCUAvgTimeEEM_RunB[eeSec]->SetMinimum(-50); 	 
     CCUAvgTimeEEM_RunB[eeSec]->SetMaximum(50); 
	 CCUAvgTimeEEM_RunB[eeSec]->Draw("colztext");
	 CCUAvgTimeEEM_RunB[eeSec]->Write();	 
   }
  
 // EB Plus
  // Run B
 FedAvgTimingEEP_RunB->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEP_RunB->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEP_RunB->Draw("colz");
 FedAvgTimingEEP_RunB->Write();

 
 // run B
  //EE Minus
 FedAvgTimingEEM_RunB->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEM_RunB->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEM_RunB->Draw("colz");
 FedAvgTimingEEM_RunB->Write();

 //ALL EB SM

 // Run B
FedAvgTimingEB_RunB->GetXaxis()->SetTitle("i#phi");
FedAvgTimingEB_RunB->GetYaxis()->SetTitle("i#eta");
FedAvgTimingEB_RunB->Draw("colz");
FedAvgTimingEB_RunB->Write();
 
// 5by5 binning hist runB:
//EB
ccutimeEBrunB->GetXaxis()->SetTitle("i#phi");
ccutimeEBrunB->GetYaxis()->SetTitle("i#eta");
ccutimeEBrunB->Draw("colz");
ccutimeEBrunB->Write();
//EEP
 // 5by5 binning hist runB:
ccutimeEEPrunB->GetXaxis()->SetTitle("ix");
ccutimeEEPrunB->GetYaxis()->SetTitle("iy");
ccutimeEEPrunB->Draw("colz");
ccutimeEEPrunB->Write();
//EEM
  // 5by5 binning hist runB:
ccutimeEEMrunB->GetXaxis()->SetTitle("ix");
ccutimeEEMrunB->GetYaxis()->SetTitle("iy");
ccutimeEEMrunB->Draw("colz");
ccutimeEEMrunB->Write();


	// Run B
    EBP1Dtime_RunB->Write();
	EBM1Dtime_RunB->Write();
	
  // Run B
  xtaltimeDistEB_RunB->Write();
  xtaltimeDistEE_RunB->Write();


   // Run B  
  XtaltimeVsAmpEB_RunB->Write();
  XtaltimeVsAmpEE_RunB->Write();
  //  XtaltimeVsTimeEB->Write();
  //  XtaltimeVsTimeEE->Write();
  XtaltimeVsFedIDEB_RunB->Write();
  XtaltimeVsFedIDEE_RunB->Write();

  XtaltimeVsLumiEB_RunB->Write();
  XtaltimeVsEta_RunB->Write();
  XtaltimeVsRun_RunB->Write();

 
} //  end of fxn Writehist


////### Fxn To make bins empty bins show as white on Canvas ////////

void moveBinsTProfile2D(TProfile2D* myprof)
{
  int nxbins = myprof->GetNbinsX();
  int nybins = myprof->GetNbinsY();

  for(int i=0; i<=(nxbins+2)*(nybins+2); i++ )
  {
    Double_t binents = myprof->GetBinEntries(i);
    if(binents == 0)
    {
      myprof->SetBinEntries(i,1);
      myprof->SetBinContent(i,-1000);
    }
  }
  return;
} // End of fxn to Move bins




/////////&&&&&& Fxn To calculate TprofSubtract &&&&&&&/////////
TProfile2D* SubtractTwoTProfile2D( TProfile2D* hprof_runA, TProfile2D* hprof_runB)
{
  if(!hprof_runA){cout << "No input histograms was put" << endl;}

  // TProfile2D*  clonehprof = (TProfile2D*)hprof_runA->Clone("CCUMeantimeDiff");

  int nxbinsA = hprof_runA->GetNbinsX();
  int nybinsA = hprof_runA->GetNbinsY();

  int nxbinsB = hprof_runB->GetNbinsX();
  int nybinsB = hprof_runB->GetNbinsY();  
  //  cout <<" Number of Xbins in Run A = " << nxbinsA << " And Number of YBins in Run A = " << nybinsA << endl;
  //  cout <<" Number of Xbins in Run B = " << nxbinsB << " And Number of YBins in Run B = " << nybinsB << endl;
  
  // Define New Histogram to hold CCU Time Shift
  TProfile2D *result_hprof =(TProfile2D*)hprof_runA->Clone("CCUMeanTimeShifthprof");

  result_hprof->Reset();
  
  // loop over bins of both hists:
  if( nxbinsA == nxbinsB && nybinsA == nybinsB)
	{
	  for( int ixa = 1; ixa <= nxbinsA; ixa++)
		{
		  for( int iya = 1; iya <= nybinsA; iya++)
			{
			  int binsA = hprof_runA->GetBin(ixa, iya);
			  int binsB = hprof_runB->GetBin(ixa, iya);
			  // Get CCU time for A and B
			  float timeA = hprof_runA->GetBinContent(binsA);
			  float timeB = hprof_runB->GetBinContent(binsB);
			  
			  // get number entries in Each 2D First.
			  int nentriesA =  hprof_runA->GetBinEntries(binsA);
			  int nentriesB =  hprof_runB->GetBinEntries(binsB);
			  
			  
			  // skip CCU without reading  at either runs
			  if((timeA == 0 && timeB !=0) || (timeA != 0 && timeB ==0)) continue;
			  // Time Diff
			  float timeshift = timeA - timeB;
			  
			  // check here for Empty CCUs in A and B and set Time Extra Large.;
			  if( nentriesA == 0 && nentriesB == 0)
				{
				  if(timeA == 0 || timeB == 0)
					{
					  result_hprof->SetBinContent(binsA, -9999999); // If No entry Set Etra large Time,Plot shows white.
					}else{ cout <<" This Bin is crazy! No entry! No Time! how come reading?" << endl;}
				}else
				{			  
				  result_hprof->SetBinContent(binsA, timeshift);
				  result_hprof->SetBinEntries(binsA, 1);
				}
			  //result_hprof->Fill(ixa, iya, timeshift);
			  
			  //debug for CCUs with either runs have zero time.
			  if((timeshift >=5 || timeshift <=-5) && (timeA !=0 && timeB !=0))
				{
				  cout <<" CCU With Huge TimeShift Has Bins = " << "[" << ixa << "," << iya << "]" <<" and has "<< " timeA = " << timeA << " and timeB = " << timeB << " with time Difference = " << timeshift << endl;
				}
			}
		}
	}
  
  result_hprof->SetMinimum(binlow);
  result_hprof->SetMaximum(binhigh);
  
  return result_hprof;
  
} // end of  Trial Subtract


//////&&&&&&&&& Funtion to Substract  1D Hists &&&&&&&&&&&&&&&&/////////////////

TH1F* subtracthist( TH1F* hprof_runA, TH1F* hprof_runB)
{
  if(!hprof_runA){cout << "No input histograms was put" << endl;}

  //  TH1F*  clonehprof = (TH1F*)hprof_runA->Clone("ccu_timing_shift_dist");
  //   TProfile2D*  clonehprof = (TProfile2D*)hprof_runA->Clone(hprof_runA->GetName());
  
  //subtract Histograms:
  int nXbinsA = hprof_runA->GetNbinsX();
  int nXbinsB = hprof_runB->GetNbinsX();
  TH1F* myhist = (TH1F*)hprof_runA->Clone("ccuInFed_time_shift_dist");
  //TH1F* myhist = (TH1F*)(hprof_runA->Clone(hprof_runA->GetName());
  myhist->Reset();
  if( nXbinsA == nXbinsB)
	{
	  for( Int_t xx = 0; xx < nXbinsA +1; xx++)
		{
		  
		  int bin = hprof_runA->GetBin(xx);
		  // ask # entries to skip empty bins
		  //		  int Nentry = hprof_runA->GetBinEntries(bin);
		  
		  float timeA = hprof_runA->GetBinContent(bin);
		  float timeB = hprof_runB->GetBinContent(bin);

		  //		  if(Nentry == 0) continue;
		  // skip CCU without reading  at either runs
		  if((timeA == 0 && timeB !=0) || (timeA != 0 && timeB ==0)) continue;
		  // Time Diff
		  float timeshift = timeA - timeB;
		  
		  myhist->Fill(timeshift);
		  //   myhist->SetBinEntries(bin, 1);
		}
	}
  
  myhist->GetXaxis()->SetRangeUser(lbin,hbin);
  
  return myhist;
  
} // end of fxn to subtract hists







//////****  CLass Defining Each Xtal *****////////
struct ntu_xtals x;


////////////////////////////////////// Funtion to Initialised DataObjects####**********************////////
void init_ttree(TTree * t, struct ntu_xtals * x)
{
    t->SetBranchAddress("run", &x->run);
    t->SetBranchAddress("seq", &x->seq);
    t->SetBranchAddress("fed", &x->fed);
    t->SetBranchAddress("ix", &x->ix);
    t->SetBranchAddress("iy", &x->iy);
    t->SetBranchAddress("iz", &x->iz);
    t->SetBranchAddress("detId", &x->detId);
    t->SetBranchAddress("elecId", &x->elecId);
    t->SetBranchAddress("harness", &x->harness);
    t->SetBranchAddress("side", &x->side);
    t->SetBranchAddress("eta", &x->eta);
    t->SetBranchAddress("phi", &x->phi);
    t->SetBranchAddress("field", &x->field);
    t->SetBranchAddress("alpha", &x->alpha);
    t->SetBranchAddress("wl", &x->wl);
    t->SetBranchAddress("time", &x->time);
    t->SetBranchAddress("nevt", &x->nevt);
    t->SetBranchAddress("laser_power", &x->laser_power);
    t->SetBranchAddress("vinj", &x->vinj);
    t->SetBranchAddress("nxtal25", &x->nxtal25);
    t->SetBranchAddress("npn", &x->npn);
    t->SetBranchAddress("vfe_mode", &x->vfe_mode);
    t->SetBranchAddress("mem_gain", &x->mem_gain);
    t->SetBranchAddress("numfill", &x->numfill);
    t->SetBranchAddress("lumi", &x->lumi);
    t->SetBranchAddress("qmax", &x->qmax);
    t->SetBranchAddress("qmaxS", &x->qmaxS);
    t->SetBranchAddress("tmax", &x->tmax);
    t->SetBranchAddress("apdpnA", &x->apdpnA);
    t->SetBranchAddress("apdpnAS", &x->apdpnAS);
    t->SetBranchAddress("apdpnB", &x->apdpnB);
    t->SetBranchAddress("apdpnBS", &x->apdpnBS);
    t->SetBranchAddress("apdpnAB", &x->apdpnAB);
    t->SetBranchAddress("apdpnABS", &x->apdpnABS);
    t->SetBranchAddress("ped", &x->ped);
    t->SetBranchAddress("pedS", &x->pedS);
    t->SetBranchAddress("ped_tp", &x->ped_tp);
    t->SetBranchAddress("ped_tpS", &x->ped_tpS);
    t->SetBranchAddress("ped_laser", &x->ped_laser);
    t->SetBranchAddress("ped_laserS", &x->ped_laserS);
    t->SetBranchAddress("tp", &x->tp);
    t->SetBranchAddress("tpS", &x->tpS);
    t->SetBranchAddress("corrwidth", &x->corrwidth);
    t->SetBranchAddress("apdapdA", &x->apdapdA);
    t->SetBranchAddress("apdapdAS", &x->apdapdAS);
    t->SetBranchAddress("apdapdB", &x->apdapdB);
    t->SetBranchAddress("apdapdBS", &x->apdapdBS);
    t->SetBranchAddress("l_ampli", &x->l_ampli);
    t->SetBranchAddress("l_rise_time", &x->l_rise_time);
    t->SetBranchAddress("l_fwhm", &x->l_fwhm);
    t->SetBranchAddress("l_width90", &x->l_width90);
    t->SetBranchAddress("l_width95", &x->l_width95);
    t->SetBranchAddress("l_prepulse", &x->l_prepulse);
    t->SetBranchAddress("l_nphot0", &x->l_nphot0);
    t->SetBranchAddress("l_nphot1", &x->l_nphot1);
    t->SetBranchAddress("l_nphot2", &x->l_nphot2);
    t->SetBranchAddress("l_nphot3", &x->l_nphot3);
    t->SetBranchAddress("l_nphot4", &x->l_nphot4);
    t->SetBranchAddress("pnA_qmax", &x->pnA_qmax);
    t->SetBranchAddress("pnA_qmaxS", &x->pnA_qmaxS);
    t->SetBranchAddress("pnA_pnpnB", &x->pnA_pnpnB);
    t->SetBranchAddress("pnA_pnpnBS", &x->pnA_pnpnBS);
    t->SetBranchAddress("pnA_corrwidth", &x->pnA_corrwidth);
    t->SetBranchAddress("pnA_ped", &x->pnA_ped);
    t->SetBranchAddress("pnA_pedS", &x->pnA_pedS);
    t->SetBranchAddress("pnA_tp_ped", &x->pnA_tp_ped);
    t->SetBranchAddress("pnA_tp_pedS", &x->pnA_tp_pedS);
    t->SetBranchAddress("pnA_l_ped", &x->pnA_l_ped);
    t->SetBranchAddress("pnA_l_pedS", &x->pnA_l_pedS);
    t->SetBranchAddress("pnA_tp", &x->pnA_tp);
    t->SetBranchAddress("pnA_tpS", &x->pnA_tpS);
    t->SetBranchAddress("pnB_qmax", &x->pnB_qmax);
    t->SetBranchAddress("pnB_qmaxS", &x->pnB_qmaxS);
    t->SetBranchAddress("pnB_pnpnB", &x->pnB_pnpnB);
    t->SetBranchAddress("pnB_pnpnBS", &x->pnB_pnpnBS);
    t->SetBranchAddress("pnB_corrwidth", &x->pnB_corrwidth);
    t->SetBranchAddress("pnB_ped", &x->pnB_ped);
    t->SetBranchAddress("pnB_pedS", &x->pnB_pedS);
    t->SetBranchAddress("pnB_tp_ped", &x->pnB_tp_ped);
    t->SetBranchAddress("pnB_tp_pedS", &x->pnB_tp_pedS);
    t->SetBranchAddress("pnB_l_ped", &x->pnB_l_ped);
    t->SetBranchAddress("pnB_l_pedS", &x->pnB_l_pedS);
    t->SetBranchAddress("pnB_tp", &x->pnB_tp);
    t->SetBranchAddress("pnB_tpS", &x->pnB_tpS);
}

int ebwl[] = { 440, 800 };
int eewl[] = { 440, 455, 617 };



////////////&&&&&&&&& Function To Check IF Xtal is in EB or EE &&&&&&&&&&&&&&//////////////////
int isEB(int ifed)
{
    return (ifed >= 610 && ifed <= 645);
}

///*****FxN 2 convert Int to string ********/////////
std::string ConvertIntToString(int num)
{
  //  using name space std;
  stringstream mystream;
  mystream  << num;
  return mystream.str();
  
}

//*************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************///
/////// ***** Fxn Main Begins *********///////
int main(int argc, char ** argv)
{
  int * wl = NULL, nwl = 0;
  TChain * tx = new TChain("x");
  
  tx->Add("/hdfs/cms/user/norbert/data/Validlaser/*.root");
  //tx->Add("/hdfs/cms/user/norbert/data/Laser/*.root"); ///hdfs/cms/user/norbert/data/Validlaser
  //tx->Add("/hdfs/cms/user/norbert/data/NewLaserData/ntuple_example/*.root");
  //	tx->Add("/hdfs/cms/user/norbert/data/NewLaserData/cmsecallaser/srv-ecal-laser-13/disk0/ferriff/tree_data/ntuple_example/*.root");
  
  // define 1D ccu timing hists here!
  
  // Run A
  for( int ii = 0; ii < EBMaxSM; ii++)
	{
	  //	  for( int jj = 0; jj < maxNumCCUInFed; jj++)
	  //	{
		  std::string ccuname = "CCU_In_Fed_Time_shift_ Dist_[ns]";
		  ccuname += ConvertIntToString(ii + 610);
		  //		  ccuname += " CCU_";
		  //		  ccuname += ConvertIntToString(jj);
		  ccuname += "_RunA_";
		  //		  ccuInFedEBtimeRunA[ii][jj] = new TH1F(ccuname.c_str(), ccuname.c_str(), 200, -100.0, 100.0);
		  ccuInFedEBtimeRunA[ii] = new TH1F(ccuname.c_str(), ccuname.c_str(), 100, binlow, binhigh);
		  //	}
	}
  
  
  // Run B
  for( int ii = 0; ii < EBMaxSM; ii++)
	{
	  //  for( int jj = 0; jj < maxNumCCUInFed; jj++)
	  //		{
		  std::string ccuname = "CCU_In_Fed_Time Dist_";
		  ccuname += ConvertIntToString(ii + 610);
		  //		  ccuname += " CCU_";
		  //		  ccuname += ConvertIntToString(jj);
		  ccuname += "_RunB_";
		  //  ccuInFedEBtimeRunB[ii][jj] = new TH1F(ccuname.c_str(), ccuname.c_str(), 200, -100.0, 100.0);
		  //		}
		    ccuInFedEBtimeRunB[ii] = new TH1F(ccuname.c_str(), ccuname.c_str(), 100, binlow, binhigh);
		
	}
  



  // for ccu 1D Time shift:
  
    for( int ii = 0; ii < EBMaxSM; ii++)
	{
	  //	  for( int jj = 0; jj < maxNumCCUInFed; jj++)
	  //		{
		  std::string ccuname = "CCU_In_Fed_Time Shitf_[ns] Dist_EB_";
		  ccuname += ConvertIntToString(ii + 610);
		  //		  ccuname += "_CCU_";
		  //		  ccuname += ConvertIntToString(jj);
		  //		  ccuInFedEBtimeshift[ii][jj] = new TH1F(ccuname.c_str(), ccuname.c_str(), 100, -25.0, 25.0);
		   ccuInFedEBtimeshift[ii] = new TH1F(ccuname.c_str(), ccuname.c_str(), 100, -25.0, 25.0);
		  //	}
	}
  

	///// Define  Corresponding 1D dist for all Feds in EB Here! run A
 ebccutimedistrunA = new TH1F("ebccutimedistrunA","EB CCU Mean Time [ns] Dist RunA", 100, binlow, binhigh);
 ebccutimedistrunB = new TH1F("ebccutimedistrunB","EB CCU Mean Time [ns] Dist RunB", 100, binlow, binhigh);
 ebccutimedistshift = new TH1F("ebccutimedistshift","EB CCU Mean Time Shift[ns] Dist",100, lbin, hbin);



 // For EE
 // Run A
 for( int sc = 0; sc < numSC;  sc++)
   {
	 //EEM
	 std::string eemscname = "CCU Time Dist[ns] Fed_";
 	 eemscname  += ConvertIntToString(sc + 601);
	 eemscname  +="RunA";
	 ccuInFedEEMtimeRunA[sc] = new TH1F(eemscname.c_str(),eemscname.c_str(), 100, binlow, binhigh);

	 // EEP
	 std::string eepscname ="CCU Time Dist[ns] Fed_";
	 eepscname  += ConvertIntToString(sc + 646);
	 eepscname  +="RunA";
	 ccuInFedEEPtimeRunA[sc] = new TH1F(eepscname.c_str(),eepscname.c_str(), 100, binlow, binhigh);
	 
   }

 ///// Define  Corresponding 1D dist for all Feds in EEP and EEM Here! run A
 // EEP
 eepccutimedistrunA = new TH1F("eepccutimedistrunA","EE+ CCU Mean Time [ns] Dist RunA", 100, binlow, binhigh);
 eepccutimedistrunB = new TH1F("eepccutimedistrunB","EE+ CCU Mean Time [ns] Dist RunB", 100, binlow, binhigh);
 eepccutimedistshift = new TH1F("eepccutimedistshift","EE+ CCU Mean Time Shift [ns] Dist ", 100, binlow, binhigh);
// EEM
 eemccutimedistrunA = new TH1F("eemccutimedistrunA","EE- CCU Mean Time [ns] Dist RunA", 100, binlow, binhigh);
 eemccutimedistrunB = new TH1F("eemccutimedistrunB","EE- CCU Mean Time [ns] Dist RunB", 100, binlow, binhigh);
 eemccutimedistshift = new TH1F("eemccutimedistshift","EE- CCU Mean Time Shift [ns] Dist ", 100, binlow, binhigh);
 

 
 // Run B
 for( int sc = 0; sc < numSC;  sc++)
   {
	 //EEM
	 std::string eemscname = "CCU Time Dist[ns]EE- Fed_";
 	 eemscname  += ConvertIntToString(sc + 601);
	 eemscname  +="RunB";
	 ccuInFedEEMtimeRunB[sc] = new TH1F(eemscname.c_str(),eemscname.c_str(), 100, binlow, binhigh);

	 // EEP
	 std::string eepscname ="CCU Time Dist[ns]EE+ Fed_";
	 eepscname  += ConvertIntToString(sc + 646);
	 eepscname  +="RunB";
	 ccuInFedEEPtimeRunB[sc] = new TH1F(eepscname.c_str(),eepscname.c_str(), 100, binlow, binhigh);
 
   }

 // For 1D CCU EE Time shift
 for( int sc = 0; sc < numSC;  sc++)
   {
	 //EEM
	 std::string eemscname = "CCU Time Shift Dist[ns]EE";
 	 eemscname  +="-" + ConvertIntToString( Numbers::iEE(sc+1));
	 eemscname  +="_Fed";
	 eemscname  += ConvertIntToString(sc + 601);
	 ccuInFedEEMtimeshift[sc] = new TH1F(eemscname.c_str(),eemscname.c_str(), 100, binlow, binhigh);
	 
	 // EEP
	 std::string eepscname ="CCU Time Shift Dist[ns]EE";
	 eepscname  +="+" + ConvertIntToString( Numbers::iEE(sc+10));
	 eepscname  +="_Fed ";
	 eepscname  += ConvertIntToString(sc + 646);
	 ccuInFedEEPtimeshift[sc] = new TH1F(eepscname.c_str(),eepscname.c_str(), 100, binlow, binhigh);
	 
   }


 // Corresponding 1D for all CCUs in EEP and EEM
 


 
  
  
  //We Define  EB Feds
  for( int hnum = 0; hnum < numEBFed; hnum++)
	{
	  std::string fedhistname1 = "CCU_Mean_Time_EB_Fed";
	  std::string fedhistname2 = "CCU_Mean_Time_EB_Fed";
	  std::string fedhisttitle = "CCU Mean Time Shift[ns]EB";  // setting title like dis b/c diff uses name.
	  
	  if(hnum < 18)
		{
		  //fedhistname +="EB";

		 
		 
		  fedhistname1 += ConvertIntToString(( hnum + 610));
		  fedhistname2 += ConvertIntToString(( hnum + 610));
		  fedhisttitle += "-" + ConvertIntToString(( hnum + 1)); // Fed hist title.
		  fedhisttitle += "_Fed_"; 
		  fedhisttitle += ConvertIntToString(( hnum + 610)); // Fed hist title.
		  fedhistname1 += ConvertIntToString(-hnum);
		  fedhistname2 += ConvertIntToString(-hnum);
		  
		  fedhistname1 +="_RunA";
		  //		  CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname1.c_str(),fedhisttitle.c_str(),4,1,21,17,1.,86);
		  CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname1.c_str(),fedhisttitle.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);
		
		  // For Run B
		  fedhistname2 +="_RunB";
		  //		  CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname2.c_str(),fedhistname2.c_str(),4,1,21,17,1.,86);
		  CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname2.c_str(),fedhistname2.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);
		  
		  //CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhisttitle.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);
		

		}else if (hnum > 17 )
		{
		  //    fedhistname +="EB";
		  fedhistname1 += ConvertIntToString(( hnum + 610));
		  fedhistname1 +=ConvertIntToString(hnum-18);

		  fedhistname2 += ConvertIntToString(( hnum + 610));
		  fedhistname2 += ConvertIntToString(hnum-18);
          fedhisttitle += "+" + ConvertIntToString(( hnum - 17)); // Fed hist title.
		  fedhisttitle += "_Fed_"; 
		  fedhisttitle += ConvertIntToString(( hnum + 610)); // Fed Hist Title.

		  //for RunA
		  fedhistname1 +="_RunA";
		  //	  CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname1.c_str(),fedhisttitle.c_str(),4,1,21,17,1,86);
		  CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname1.c_str(),fedhisttitle.c_str(),4,1+(hnum-18)*20,1+((hnum-18)+1)*20,17,1,86);
		  // For Run B
		  
		  fedhistname2 +="_RunB";
		  //		  CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname2.c_str(),fedhistname2.c_str(),4,1,21,17,1.,86);
		  CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname2.c_str(),fedhistname2.c_str(),4,1+(hnum-18)*20,1+((hnum-18)+1)*20,17,1,86);

		  //CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1+(hnum-18)*20,1+((hnum-18)+1)*20,17,1,86);
		  
		  
		  
		}
	}
  
  
  // For EE !
  //	 CCUAvgTimeEEP_RunA[eeSec]
  for( int eeMnum = 0; eeMnum < 9; eeMnum++)
  {
	std::string fedhistname1 = "CCU_Mean_Time_EE-Fed";
	std::string fedhistname2 = "CCU_Mean_Time_EE-Fed";
	std::string fedhtitle = "CCU Mean Time Shift[ns]EE";  // setting title like dis b/c diff uses name.
	//fedhistname +="EB";
	//For Run A EE Minus
	fedhistname1 += ConvertIntToString(( eeMnum + 601));
	fedhistname2 += ConvertIntToString(( eeMnum + 601));

	fedhtitle += ConvertIntToString(Numbers::iEE(eeMnum +1) );
	fedhtitle += "_Fed_";
	fedhtitle += ConvertIntToString(( eeMnum + 601));
	//fedhistname +=ConvertIntToString(-hnum);
	//For Run A
	fedhistname1 += "_RunA";
	CCUAvgTimeEEM_RunA[eeMnum] = new TProfile2D(fedhistname1.c_str(),fedhtitle.c_str(),20,0.0,100,20,0.,100);
	//CCUAvgTimeEEM_RunA[eeMnum] = new TProfile2D(fedhistname1.c_str(),fedhtitle.c_str(),20,0.0,100,20,0.,100);
	
	// For Run B
	fedhistname2 += "_RunB";
	CCUAvgTimeEEM_RunB[eeMnum] = new TProfile2D(fedhistname2.c_str(),fedhistname2.c_str(),20,0.,100,20,0.,100);
	
    //CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname1.c_str(),fedhistname1.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);

	// EE Plus
	//RunA
	std::string EESecname1 = "CCU_Mean_Time_EE+Fed";
	std::string EESecname2 = "CCU_Mean_Time_EE+Fed";
	std::string fedtitle = "CCU Mean Time Shift[ns]EE";  // setting title like dis b/c diff uses name.
	
	EESecname1 += ConvertIntToString(eeMnum + 646);
	EESecname2 += ConvertIntToString(eeMnum + 646);

	fedtitle +="+" + ConvertIntToString(Numbers::iEE(eeMnum +10) );
	fedtitle += "_Fed_";
	fedtitle   += ConvertIntToString(eeMnum + 646);
	// For Run A
	EESecname1 +="_RunA";
	CCUAvgTimeEEP_RunA[eeMnum] = new TProfile2D(EESecname1.c_str(),fedtitle.c_str(), 20, 0., 100, 20, 0.,100);
	// For Run B
	EESecname2 +="_RunB";
	CCUAvgTimeEEP_RunB[eeMnum] = new TProfile2D(EESecname2.c_str(),EESecname2.c_str(), 20, 0., 100, 20, 0.,100); 
		
  }


  
  //EB All SM
  //Run A
  FedAvgTimingEB = new TProfile2D("FedAvgTimingEB","Crystal Time Shift[ns] EB", 360, 1., 361, 171, -85,85);
  ccutimeEBrunA = new TProfile2D("ccutimeEBrunA","CCU Mean Time Shift[ns] EB", 72,1., 361, 34, -85,85);
  // run B
  FedAvgTimingEB_RunB = new TProfile2D("FedAvgTimingEB_RunB","Crystal Time EB RunB", 360, 1., 361, 171, -85,85);
  ccutimeEBrunB = new TProfile2D("ccutimeEBrunB","CCU Mean Time Shift[ns] EB RunB", 72,1., 361, 34,-85,85);
  //EE plus
  //Run A
  FedAvgTimingEEP = new TProfile2D("FedAvgTimingEEP","Crystal Time EE+", 100, 0., 100., 100, 0, 100);
  ccutimeEEPrunA = new TProfile2D("ccutimeEEPrunA","CCU Mean Time Shift[ns] EE+", 20,0., 100, 20, 0,100);
  //Run B
  FedAvgTimingEEP_RunB = new TProfile2D("FedAvgTimingEEP_RunB","Crystal Time EE+ RunB", 100, 0., 100., 100, 0, 100);
  ccutimeEEPrunB = new TProfile2D("ccutimeEEPrunB","CCU Mean Time Shift[ns] EE+ RunB", 20,0., 100, 20, 0,100);
  //FedAvgTimingEEP = new TProfile2D("FedAvgTimingEEP","CCU Mean Time EE+", 100, -50., 50., 100, 0, 100);
  //EE minus
  //  Run A
  FedAvgTimingEEM = new TProfile2D("FedAvgTimingEEM","Crystal Time EE-", 100, 0., 100., 100, 0, 100);
  ccutimeEEMrunA = new TProfile2D("ccutimeEEMrunA","CCU Mean Time Shift[ns] EE-", 20,0., 100, 20, 0,100);
  // run B
  FedAvgTimingEEM_RunB = new TProfile2D("FedAvgTimingEEM_RunB","Crystal Time EE- RunB", 100, 0., 100., 100, 0, 100);
  ccutimeEEMrunB = new TProfile2D("ccutimeEEMrunB","CCU Mean Time Shift[ns] EE- RunB", 20,0., 100, 20, 0,100);
//FedAvgTimingEEM = new TProfile2D("FedAvgTimingEEM","CCU Mean Time EE-", 100, -50., 50., 100, -100, 0);





  

 // Ssave Out Put Files  here!
    savefile = new TFile("March14_LaserTiming_163291Vs163333_March14.root", "recreate");

    init_ttree(tx, &x);
    tx->SetBranchStatus("*",0); //disable all branches
    // only read needed branches
    tx->SetBranchStatus("run",1);
    tx->SetBranchStatus("fed",1);
    tx->SetBranchStatus("seq",1);
    tx->SetBranchStatus("detId",1);
    tx->SetBranchStatus("apdpnAB",1);
    tx->SetBranchStatus("time",1);
    tx->SetBranchStatus("eta",1);
    tx->SetBranchStatus("detId",1);
    tx->SetBranchStatus("elecId",1);
    tx->SetBranchStatus("ix",1);
    tx->SetBranchStatus("iy",1);
    tx->SetBranchStatus("phi",1);
    tx->SetBranchStatus("lumi",1);
    tx->SetBranchStatus("field", 1);
    tx->SetBranchStatus("wl",1);
    tx->SetBranchStatus("qmax",1);
    tx->SetBranchStatus("tmax",1);

	

    int nbytes = -1;
    int ientry = 0;
    int numcrys = 0;
	
	EBDetId ebdetid;
	EEDetId eedetid;



	// initialized ccu arrays:

		// initialise all the CCUs
		// for EB
		for( int i = 0; i<EBMaxSM; i++)
		  {
		  for(int j = 0; j< maxNumCCUInFed; j++)
			{
			  //			  for( int k = 0; k < maxXtalInCCU; k++)
			  //	{
			  //			  CCUInFedTimesEB_runA[i][j][k] = 0;
			   CCUInFedTimesEB_runA[i][j] = 0;
			   //			   CCUInFedTimesEB_runB[i][j][k] = 0;
			   CCUInFedTimesEB_runB[i][j] = 0;
				  //		}
     		  CCUInFedNumEntriesEB_runA[i][j] = 0;
		   	  CCUInFedNumEntriesEB_runB[i][j] = 0;
				
			}
		  }

		// for EE
	    for( int i = 0; i<numSC; i++) // ii from 0 to 8 for each Dee
		  {
		  for(int j = 0; j<maxNumCCUInFed; j++)
			{
			  //			  for( int k = 0; k < maxXtalInCCU; k++)
			  //				{
			  //			  CCUInFedTimesEE[i][j][k] = 0;
			  // EEP  run A
			  CCUInFedTimesEEP_runA[i][j]  = 0;
			  //		}
			  CCUInFedNumEntriesEEP_runA[i][j] = 0;

			  // run B
			  CCUInFedTimesEEP_runB[i][j]  = 0;
			  //		}
			  CCUInFedNumEntriesEEP_runB[i][j] = 0;
			  // EEM run A
			  CCUInFedTimesEEM_runA[i][j]  = 0;
			  //		}
			  CCUInFedNumEntriesEEM_runA[i][j] = 0;

			  // run B
			  CCUInFedTimesEEM_runB[i][j]  = 0;
			  //		}
			  CCUInFedNumEntriesEEM_runB[i][j] = 0;

			  
			}
		  
		  }


	

		
////// Loop over Crystals Begin Here!  
	while ((nbytes = tx->GetEntry(ientry++)) != 0)
	  {
		
		///////****** select run before TS RUN A******///////
		if(x.run == RunB4TS && x.seq == 0)
		  {
			
			
			
			// for Barrel FEDs or SumperModules
			
			if (isEB(x.fed)) 
			  {
				
				wl = ebwl;
				nwl = 2;
				//         EBDetId ebdetid;
				EBDetId ebdetid(x.detId);
				//	int ieta = ebdetid.ietaSM();
				//	int iphi = ebdetid.iphiSM();
				int ieta = ebdetid.ieta();
				int iphi = ebdetid.iphi();
				
				
				//		int ieta = x.ix;
				//		int iphi = x.iy+10;
				float crytime = x.tmax[0];
				float Xtaltime = (crytime - 5)*25;
				int  EBXtalFed = x.fed;
				int numfed = EBXtalFed - 610;


				// 1D ccu timing dist stuff
				// run A
				
				//EBdetId  detid(x.detId);
				
				const EcalElectronicsId eid = x.elecId;
				int IdCCU = eid.towerId();
				//						int VFEid = eid.stripId();
				//						int xtalInVFE = eid.xtalId();
				//						int xtalWithinCCUid = 5*( VFEid-1) + xtalInVFE -1; // TEN expects [0,24]
				//				int m = x.fed - 610;	
				int ccuid = IdCCU;
				//	  EcalTrigTowerDetId(ebdetid);
				//
				//				int nxtal =  ebdetid.ic();  // include Crystal Number
				std::cout << "Crystal with Id \t" << eid << " Has CCUid \t" << IdCCU  << std::endl;
				//				if(m < EBMaxSM && ccuid < maxNumCCUInFed)
				//			  {
				CCUInFedTimesEB_runA[numfed][ccuid-1] += (x.tmax[0]- 5)*25;
				//					CCUInFedTimesEB_runA[m][ccuid-1][xtalWithinCCUid] = (x.tmax[0]- 5)*25;
				//					CCUInFedTimesEB_runA[m][ccuid-1][nxtal -1] = (x.tmax[0]- 5)*25;
				CCUInFedNumEntriesEB_runA[numfed][ccuid-1] ++;

					//				  }
				
				// now fill 1D hists
				// Run A
				  
				//			   ccuInFedEBtimeRunA[m][ccuid -1]->Fill( CCUInFedTimesEB_runA[m][ccuid-1][xtalWithinCCUid] );
				  

				// debugging				
				if(x.fed ==610)
				  {
					EBM1Dtime->Fill(Xtaltime);
					cout <<  " the Xtal eta is:" << ieta << " Xtal Phi:" << iphi << " Xtal Time is:" << Xtaltime << endl;
				  }
				
				if (x.fed == 628)
				  {
					
					cout << "Crystal time is :" << Xtaltime << endl;
					EBP1Dtime->Fill(Xtaltime);
					
				  }
				
				CCUAvgTimeEB_RunA[numfed]->Fill(iphi, ieta, Xtaltime); // Fill all EB-FEDs
				
				
				XtaltimeVsAmpEB->Fill(x.qmax[0],Xtaltime); // Here still has raw time. hmm!
				//    XtaltimeVsTimeEB->Fill( x.time[0],x.tmax[0]);
				XtaltimeVsLumiEB->Fill(x.lumi[0],x.tmax[0]);
				XtaltimeVsFedIDEB->Fill(x.fed,(x.tmax[0]-5)*25);
				
				xtaltimeDistEB->Fill( (x.tmax[0]-5)*25);
				FedAvgTimingEB->Fill(iphi,ieta,(x.tmax[0]-5)*25);  //  ALL EB
				ccutimeEBrunA->Fill(iphi,ieta,(x.tmax[0]-5)*25);  // ccutime 5by5 bining!
				
				//   Do EE  here!
			  }else{
			  wl = eewl;
			  nwl = 3;
			  //            EEDetId eedetid;
			  
			  EEDetId eedetid(x.detId);
			  int ix = eedetid.ix();
			  int iy = eedetid.iy(); 
			  int EExtalfed = x.fed;
			  const EcalElectronicsId eid = x.elecId;
			  int SCId = eid.towerId(); // SC Id
			  //						int VFEid = eid.stripId();
			  //						int xtalInVFE = eid.xtalId();
			  //						int xtalWithinCCUid = 5*( VFEid-1) + xtalInVFE -1; // TEN expects [0,24]
			  
			  // Loop over number crystals in EE
			  xtaltimeDistEE->Fill( (x.tmax[0]-5)*25);
			  XtaltimeVsAmpEE->Fill(x.qmax[0],(x.tmax[0]-5)*25);
			  // XtaltimeVsTimeEE->Fill( x.time[0],(x.tmax[0]-5)*25);
			  XtaltimeVsFedIDEE->Fill(x.fed,(x.tmax[0]-5)*25);
			  
			  if(x.fed >=601 && x.fed <= 609)
				{
				  // For EE Minus
				  int eehistprofm = EExtalfed - 601;
				  float crytime = (x.tmax[0]-5)*25;
				  CCUAvgTimeEEM_RunA[eehistprofm]->Fill(ix, iy, crytime);
				  FedAvgTimingEEM->Fill(ix,iy,(x.tmax[0]-5)*25); // Crystal in EEM check with data
				  ccutimeEEMrunA->Fill(ix,iy,(x.tmax[0]-5)*25); // CCU 5by5 bining in EEM check with data

				  // Fill Arrays for EEM
				  CCUInFedTimesEEM_runA[eehistprofm][SCId -1]  += crytime;
				  CCUInFedNumEntriesEEM_runA[eehistprofm][SCId -1] ++;
			
				}else
				{
				  //cout << "Plus EE crystals" << endl;
				  
				  // For EE Plus
				  int eehistprofp = EExtalfed - 646;
				  float crytime = (x.tmax[0]-5)*25;
				  CCUAvgTimeEEP_RunA[eehistprofp]->Fill(ix, iy, crytime);
				  
				  FedAvgTimingEEP->Fill(ix,iy,(x.tmax[0]-5)*25);
				  ccutimeEEPrunA->Fill(ix,iy,(x.tmax[0]-5)*25); // CCU 5by5 bining in EEP check with data

				  // Fill Array for EEP
				  CCUInFedTimesEEP_runA[eehistprofp][SCId -1]  += crytime;
				  CCUInFedNumEntriesEEP_runA[eehistprofp][SCId -1] ++;				  
				}
			  //  CCUInFedTimesEE_runA[i][j]  = ;
			  //    CCUInFedTimesEE[i][j]
			  
			}
			
			//Fill generally for all sturff.
			XtaltimeVsEta->Fill(x.eta, (x.tmax[0]-5)*25);
			XtaltimeVsRun->Fill( x.run,(x.tmax[0]-5)*25);
			
			
			//         for (int i = 0; i < nwl; ++i) 
			//         {
			//           printf("reading WL %d for channel %d in FED %d: APD/PN_AB = %f at time %d\n", x.wl[i], x.detId, x.fed,  x.apdpnAB[i], x.time[i]);
			//         }
			
			numcrys +=numcrys;
			
			if( numcrys > 75838) break; 
			
			
		  }else // end of choice of run Before TS  and Seq


		  
		  ///////****** select run After TS, RUN B******///////
		  if(x.run == RunAFTS && x.seq == 0)
			{
			  
			  // for Barrel FEDs or SumperModules
			  if (isEB(x.fed)) 
				{
				  
				  wl = ebwl;
				  nwl = 2;
				  //         EBDetId ebdetid;
				  
				  
				  EBDetId ebdetid(x.detId);
				  //				  int ieta = ebdetid.ietaSM();
				  //				  int iphi = ebdetid.iphiSM();
				  int ieta = ebdetid.ieta();
				  int iphi = ebdetid.iphi();
				
				  
				  //int ieta = x.ix;
				  //		int iphi = x.iy+10;
				  float crytime = x.tmax[0];
				  float Xtaltime = (crytime - 5)*25;
				  int  EBXtalFed = x.fed;
				  int  numfed = EBXtalFed - 610;
				  

			// run B
		//  Put ccu 1D timing in arrays
		//EBdetId  detid(x.detId);
		
	    const EcalElectronicsId eid = x.elecId;
	    int IdCCU = eid.towerId();
		// 		int VFEid = eid.stripId();
		//		int xtalInVFE = eid.xtalId();
		//		int xtalWithinCCUid = 5*( VFEid-1) + xtalInVFE -1; // TEN  expects [0,24]
		//		int m = x.fed - 610;
        int ccuid =IdCCU;
		  //  EcalTrigTowerDetId(ebdetid);
		//		int nxtal =  ebdetid.ic();

		//		if(m < EBMaxSM && ccuid < maxNumCCUInFed)
		//		  {
			CCUInFedTimesEB_runB[numfed][ccuid-1] += (x.tmax[0]-5)*25;
			//						CCUInFedTimesEB_runB[m][ccuid-1][xtalWithinCCUid] = (x.tmax[0]-5)*25;
			//		CCUInFedTimesEB_runB[m][ccuid-1][nxtal -1] = (x.tmax[0]-5)*25;
		    CCUInFedNumEntriesEB_runB[numfed][ccuid-1] ++;   // Not really used! Just for check!
			//	  }
				  
		//  Fill ccu 1D timing  dist for Run B

		//	     ccuInFedEBtimeRunB[m][ccuid -1]->Fill( CCUInFedTimesEB_runB[m][ccuid-1][xtalWithinCCUid] );

		
		
		// debugging feds stuff
				  if(x.fed ==610)
					{
					  EBM1Dtime_RunB->Fill(Xtaltime);
					  //		  cout <<  " the Xtal eta is:" << ieta << " Xtal Phi:" << iphi << " Xtal Time is:" << Xtaltime << endl;
					}
				  
				  if (x.fed == 628)
					{  
					  //	 cout << "Crystal time is :" << Xtaltime << endl;
					  EBP1Dtime_RunB->Fill(Xtaltime); 
					}
		
				  CCUAvgTimeEB_RunB[numfed]->Fill(iphi, ieta, Xtaltime); // Fill all EB-FEDs

				  
   
				  XtaltimeVsAmpEB_RunB->Fill(x.qmax[0],Xtaltime); 
				  //XtaltimeVsTimeEB->Fill( x.time[0],x.tmax[0]);
				  XtaltimeVsLumiEB_RunB->Fill(x.lumi[0],x.tmax[0]);
				  XtaltimeVsFedIDEB_RunB->Fill(x.fed,(x.tmax[0]-5)*25);
				  
				  xtaltimeDistEB_RunB->Fill( (x.tmax[0]-5)*25);
				  FedAvgTimingEB_RunB->Fill(iphi,ieta,(x.tmax[0]-5)*25); //  ns time!
				  ccutimeEBrunB->Fill(iphi,ieta,(x.tmax[0]-5)*25); // CCU 5by5 bining in EB Run B check with data

				  
				  //   Do EE  here!
				}else{
				wl = eewl;
				nwl = 3;
				//            EEDetId eedetid;
				
				EEDetId eedetid(x.detId);
				int ix = eedetid.ix();
				int iy = eedetid.iy();
				int EExtalfed = x.fed;
				
				const EcalElectronicsId eid = x.elecId;
				int SCId = eid.towerId(); // SC Id
				//						int VFEid = eid.stripId();
				//						int xtalInVFE = eid.xtalId();
				//						int xtalWithinCCUid = 5*( VFEid-1) + xtalInVFE -1; // TEN expects [0,24]
				
				// Loop over number crystals in EE
				xtaltimeDistEE_RunB->Fill( (x.tmax[0]-5)*25);
				XtaltimeVsAmpEE_RunB->Fill(x.qmax[0],(x.tmax[0]-5)*25);
				// XtaltimeVsTimeEE_RunB->Fill( x.time[0],(x.tmax[0]-5)*25);
				
				XtaltimeVsFedIDEE_RunB->Fill(x.fed,(x.tmax[0]-5)*25);
				
				if(x.fed >=601 && x.fed <= 609)
				  {
					
					// For EE Minus
					int eehistprofm = EExtalfed - 601;
					float crytime = (x.tmax[0]-5)*25;
					CCUAvgTimeEEM_RunB[eehistprofm]->Fill(ix, iy, crytime);
					
					FedAvgTimingEEM_RunB->Fill(ix,iy,(x.tmax[0]-5)*25);
					ccutimeEEMrunB->Fill(ix,iy,(x.tmax[0]-5)*25); // CCU 5by5 bining in EEM  runB check with data
					
					// Fill Arrays for EEM
					CCUInFedTimesEEM_runB[eehistprofm][SCId -1]  += crytime;
					CCUInFedNumEntriesEEM_runB[eehistprofm][SCId -1] ++;      //  Just to check still has lots to do here!
					
				  }else
				  
				  {
					cout << "Plus EE crystals" << endl;
					// For EE Plus
					int eehistprofp = EExtalfed - 646;
					float crytime = (x.tmax[0]-5)*25;
					CCUAvgTimeEEP_RunB[eehistprofp]->Fill(ix, iy, crytime);
					FedAvgTimingEEP_RunB->Fill(ix,iy,(x.tmax[0]-5)*25);
					ccutimeEEPrunB->Fill(ix,iy,(x.tmax[0]-5)*25); // CCU 5by5 bining in EEP  runB check with data
					
					// Fill Arrays for EEP
					CCUInFedTimesEEP_runB[eehistprofp][SCId -1]  += crytime;
					CCUInFedNumEntriesEEP_runB[eehistprofp][SCId -1] ++;
					
				  }
				
			  }
			  
			  
			  //Fill generally for all sturff.
			  XtaltimeVsEta_RunB->Fill(x.eta, (x.tmax[0]-5)*25);
			  XtaltimeVsRun_RunB->Fill( x.run,(x.tmax[0]-5)*25);
			  
			  
			  numcrys +=numcrys;
			  
			  if( numcrys > 75838) break; 
			  
			}   // end of choice of run  After TS and Seq
		
		
		
	  }// end of Loop over entries( xtals)



	

	// Fill 1D histograms for EB Run A
	
		for( int ii = 0; ii < EBMaxSM; ii++)
		  {
			for( int jj = 0; jj < maxNumCCUInFed; jj++)
			  {
				//				for( int k = 0; k < maxXtalInCCU; k++)
				  //				  {
				//				ccuInFedEBtimeRunA[ii][jj]->Fill( CCUInFedTimesEB_runA[ii][jj]/ CCUInFedNumEntriesEB_runA[ii][jj] );
				ccuInFedEBtimeRunA[ii]->Fill(CCUInFedTimesEB_runA[ii][jj]/ maxXtalInCCU); //CCUInFedNumEntriesEB_runA[ii][jj] );
				//  }
				ebccutimedistrunA->Fill(CCUInFedTimesEB_runA[ii][jj]/ maxXtalInCCU);				
			  }
		  }

		
		// Fill 1D histograms for EB Run B
		
		for( int ii = 0; ii < EBMaxSM; ii++)
		  {
			for( int jj = 0; jj < maxNumCCUInFed; jj++)
			  {
				//				for( int k = 0; k < maxXtalInCCU; k++)
				//				  {
				//				ccuInFedEBtimeRunB[ii][jj]->Fill( CCUInFedTimesEB_runB[ii][jj]/ CCUInFedNumEntriesEB_runB[ii][jj] );
				ccuInFedEBtimeRunB[ii]->Fill( CCUInFedTimesEB_runB[ii][jj]/maxXtalInCCU); // CCUInFedNumEntriesEB_runB[ii][jj] );
				//  }
				ebccutimedistrunB->Fill(CCUInFedTimesEB_runB[ii][jj]/ maxXtalInCCU);
			  }
		  }		

	// subtract 1D ccu in EB timing  shift  here!
	
	for( int ii = 0; ii < EBMaxSM; ii++)
	  {
		for( int jj = 0; jj < maxNumCCUInFed; jj++)
		  {
			//			for ( int crys = 0; crys < maxXtalInCCU; crys++)
			//			  {
				
			//			ccuInFedEBtimeshift[ii][jj]->Fill( (CCUInFedTimesEB_runA[ii][jj]/ CCUInFedNumEntriesEB_runA[ii][jj]) - (CCUInFedTimesEB_runB[ii][jj]/ CCUInFedNumEntriesEB_runB[ii][jj]) );
			//			ccuInFedEBtimeshift[ii]->Fill( (CCUInFedTimesEB_runA[ii][jj]/ CCUInFedNumEntriesEB_runA[ii][jj]) - (CCUInFedTimesEB_runB[ii][jj]/ CCUInFedNumEntriesEB_runB[ii][jj]) );
				ccuInFedEBtimeshift[ii]->Fill( (CCUInFedTimesEB_runA[ii][jj]/maxXtalInCCU ) - (CCUInFedTimesEB_runB[ii][jj]/maxXtalInCCU ) );
				//ccuInFedEBtimeshift[ii][jj] = subtracthist(ccuInFedEBtimeRunA[ii][jj],ccuInFedEBtimeRunB[ii][jj] );
				//			  }
				
				ebccutimedistshift->Fill( (CCUInFedTimesEB_runA[ii][jj]/maxXtalInCCU ) - (CCUInFedTimesEB_runB[ii][jj]/maxXtalInCCU ));
		  }
		Savehist(ccuInFedEBtimeshift[ii]);
	  }

	Savehist(ebccutimedistshift); // 1D dist of all CCUs in EB
 

	// Fill 1D hist for EEP and EEM

	// For RunA
	for( int sm = 0; sm < numSC; sm++)
	  {
		for( int ccu = 0; ccu < maxNumCCUInFed; ccu++)
		  {
            // For EEM
			ccuInFedEEMtimeRunA[sm]->Fill( CCUInFedTimesEEM_runA[sm][ccu]/maxXtalInCCU);     // Still   has work to do here!
			eemccutimedistrunA->Fill(CCUInFedTimesEEM_runA[sm][ccu]/maxXtalInCCU);
			// for EEP
			ccuInFedEEPtimeRunA[sm]->Fill( CCUInFedTimesEEP_runA[sm][ccu]/maxXtalInCCU);     // Still   has work to do here!
			eepccutimedistrunA->Fill(CCUInFedTimesEEP_runA[sm][ccu]/maxXtalInCCU);
						
		  }
	  }


	//For run B

	
	// For RunA
	for( int sm = 0; sm < numSC; sm++)
	  {
		for( int ccu = 0; ccu < maxNumCCUInFed; ccu++)
		  {
            // For EEM
			ccuInFedEEMtimeRunB[sm]->Fill( CCUInFedTimesEEM_runB[sm][ccu]/maxXtalInCCU);     // Still   has work to do here!
			eemccutimedistrunB->Fill(CCUInFedTimesEEM_runB[sm][ccu]/maxXtalInCCU);  // for all ccus in EEM
			// for EEP
			ccuInFedEEPtimeRunB[sm]->Fill( CCUInFedTimesEEP_runB[sm][ccu]/maxXtalInCCU);     // Still   has work to do here!
			eepccutimedistrunB->Fill(CCUInFedTimesEEP_runB[sm][ccu]/maxXtalInCCU); // for all CCUs in EEP
		  }
		
	  }

	// For Timing Shift		
	// For RunA
	for( int sm = 0; sm < numSC; sm++)
	  {
		for( int ccu = 0; ccu < maxNumCCUInFed; ccu++)
		  {
            // For EEM
			ccuInFedEEMtimeshift[sm]->Fill((CCUInFedTimesEEM_runA[sm][ccu]/maxXtalInCCU) - (CCUInFedTimesEEM_runB[sm][ccu]/maxXtalInCCU));     // Still   has work to do here!
			eemccutimedistshift->Fill((CCUInFedTimesEEM_runA[sm][ccu]/maxXtalInCCU) - (CCUInFedTimesEEM_runB[sm][ccu]/maxXtalInCCU)); // all ccus in EEM time shift
			// for EEP
			ccuInFedEEPtimeshift[sm]->Fill((CCUInFedTimesEEP_runA[sm][ccu]/maxXtalInCCU) - (CCUInFedTimesEEP_runB[sm][ccu]/maxXtalInCCU));     // Still   has work to do here!
			eepccutimedistshift->Fill((CCUInFedTimesEEP_runA[sm][ccu]/maxXtalInCCU) - (CCUInFedTimesEEP_runB[sm][ccu]/maxXtalInCCU)); // all ccus in EEP time shift
		  }
     		Savehist(ccuInFedEEMtimeshift[sm]);
		Savehist(ccuInFedEEPtimeshift[sm]);
	  }

	// 1D  dist of all CCUs in EEP and EEM
	Savehist(eemccutimedistshift);
	Savehist(eepccutimedistshift);	






	
	////// Calculate CCU Time Shift Here!////////
	
	
	//First for ALL EB and EE
	
	//EB 
	CrysTimeShiftEB = SubtractTwoTProfile2D(FedAvgTimingEB,  FedAvgTimingEB_RunB);
	CrysTimeShiftEB ->SetMinimum(lbin);
	CrysTimeShiftEB->SetMaximum(hbin);
	SaveCanvasInDir(CrysTimeShiftEB);    // don't save for now!
	// 5by5 bining
	ccutshiftEB = SubtractTwoTProfile2D(ccutimeEBrunA, ccutimeEBrunB);
	ccutshiftEB ->SetMinimum(lbin);
	ccutshiftEB->SetMaximum(hbin);
	SaveCanvasInDir(ccutshiftEB);          // don't save for now!

	//EEP
	CrysTimeShiftEEP = SubtractTwoTProfile2D(FedAvgTimingEEP, FedAvgTimingEEP_RunB);
	CrysTimeShiftEEP->SetMinimum(lbin);
	CrysTimeShiftEEP->SetMaximum(hbin);
	SaveCanvasInDir(CrysTimeShiftEEP);         // don't save for now!
	// 5by5 bining
	ccutshiftEEP = SubtractTwoTProfile2D(ccutimeEEPrunA, ccutimeEEPrunB);
	ccutshiftEEP ->SetMinimum(lbin);
	ccutshiftEEP->SetMaximum(hbin);
	SaveCanvasInDir(ccutshiftEEP);         // don't save  for now
	
	//EEM 
	CrysTimeShiftEEM = SubtractTwoTProfile2D(FedAvgTimingEEM, FedAvgTimingEEM_RunB);
	CrysTimeShiftEEM->SetMinimum(lbin);
	CrysTimeShiftEEM->SetMaximum(hbin);
	//	SaveCanvasInDir(CrysTimeShiftEEM);    // don't save for now
	
 	// 5by5 bining
	ccutshiftEEM = SubtractTwoTProfile2D(ccutimeEEMrunA, ccutimeEEMrunB);
	ccutshiftEEM ->SetMinimum(lbin);
	ccutshiftEEM->SetMaximum(hbin);
	SaveCanvasInDir(ccutshiftEEM);           //  don't save for now!
	
	
	//loop over all FED TProfile2D
	// EB
	for( int nh = 0; nh < numEBFed; nh++)
	  {
		
		CCUTimeShiftEB[nh]= SubtractTwoTProfile2D(CCUAvgTimeEB_RunA[nh], CCUAvgTimeEB_RunB[nh]);
		CCUTimeShiftEB[nh]->SetMinimum(lbin);
		CCUTimeShiftEB[nh]->SetMaximum(hbin);
		// Get CCUId and Time
		//		  GetCCUIdandTimeshiftTProfileHist(CCUTimeShiftEB[nh], 0);
		// GetCCUIdandTimeshiftTProfileHist(ccutshiftEB, 0);
		//	   GetCCUIdAndTimeFromTProfileHist::
		//	   getCCUId(GetCCUIdandTimeShift(CCUTimeShiftEB[nh], 0));
		
			SaveCanvasInDir( CCUTimeShiftEB[nh]);               // Don't  save for now!
	  }
	
	//Debug issues
	//        int binA = CCUAvgTimeEB_RunA[0]->GetBin(4,17);
	//        float binvalueA = CCUAvgTimeEB_RunA[0]->GetBinContent(binA);
	// 	   int  binEntryA =  CCUAvgTimeEB_RunA[0]->GetBinEntries(binA);
	
	// 	   int binB = CCUAvgTimeEB_RunB[0]->GetBin(4,17);
	// 	   float binvalueB = CCUAvgTimeEB_RunB[0]->GetBinContent(binB);
	// 	   int  binEntryB =  CCUAvgTimeEB_RunB[0]->GetBinEntries(binB);
	
	// 	   int bind = CCUTimeShiftEB[0]->GetBin(4,17);
	// 	   float binvalue = CCUTimeShiftEB[0]->GetBinContent(bind);
	// 	   int  binEntry   =  CCUTimeShiftEB[0]->GetBinEntries(bind);
	
	
	
	//    cout << "RunA has Entries=" << binEntryA << " With Time=" <<  binvalueA << endl;
	//    cout << "RunB has Entries=" << binEntryB << " With Time=" <<  binvalueB << endl;
	
	
	//    cout << "Diff In Run  has Entries=" << binEntry << " With Time=" <<  binvalue << endl;
	
	
	
	//EE
	for ( int eenh = 0; eenh < numSC; eenh++)
	  {
		//EE plus
		CCUTimeShiftEEP[eenh]= SubtractTwoTProfile2D(CCUAvgTimeEEP_RunA[eenh], CCUAvgTimeEEP_RunB[eenh]);
		CCUTimeShiftEEP[eenh]->SetMinimum(lbin);
		CCUTimeShiftEEP[eenh]->SetMaximum(hbin);
		//GetCCUId and Time EE+
		//	   GetCCUIdandTimeshiftTProfileHist(CCUTimeShiftEEP[eenh], 1);
    		//	GetCCUIdAndTimeFromTProfileHist::
		// getCCUId(GetCCUIdandTimeShift(CCUTimeShiftEEP[eenh], 1)); 
		SaveCanvasInDir(CCUTimeShiftEEP[eenh]);	            // don't save now!
		//EE Minus   
		CCUTimeShiftEEM[eenh]= SubtractTwoTProfile2D(CCUAvgTimeEEM_RunA[eenh], CCUAvgTimeEEM_RunB[eenh]);
		
		CCUTimeShiftEEM[eenh]->SetMinimum(lbin);
		CCUTimeShiftEEM[eenh]->SetMaximum(hbin);
		
		// Get CCUId and Time EE-  //	   getCCUId.
		//	GetCCUIdandTimeshiftTProfileHist(CCUTimeShiftEEM[eenh], -1);
		 //		 getCCUId.GetCCUIdandTimeShift(CCUTimeShiftEEM[eenh], -1);
		SaveCanvasInDir(CCUTimeShiftEEM[eenh]);   // dont save for now
	  }
	
	
// Add function to Map TimeShift to CCUId  Here!
//GetCCUIdandTimeshiftTProfileHist(ccutshiftEB, 0);
//GetCCUIdandTimeshiftTProfileHist(ccutshiftEEP, 1);
//GetCCUIdandTimeshiftTProfileHist(ccutshiftEEM, -1);

    cout << " Write Histograms" << endl;
    writehist();
	
    savefile->Close();
	
	
	

	
    return 0;
	
}



