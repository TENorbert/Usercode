// Calculate the Timing Shift from Laser data @laTEN
// Include Ecal Stuff Here!
#include "DQM/EcalCommon/interface/Numbers.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/EcalScDetId.h"

// C++    stuffs
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>

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
#include "CalibCalorimetry/EcalTiming/bin/GetCCUIdAndTimeFromTProfileHist.h"

#define NWL 3 // if you change this, mind to change the Branch declaration of TTree...
#define ETA_NBIN 100
#define ETA_MIN   -3.
#define ETA_MAX   +3.


#define RunB4TS 163291 //163297//163291 //163332 //162765 //161020//161018//160111 //176455 //159218 //175573  //178854 //178731  // 162518 //160147    // 176652  // 160138    // 160133       // 160111 // 159784 //175832  // 175354 //159784 //1611175
#define RunAFTS 163333 //163483 //163333 //163869 //163078//162765 //162764 //160138 //177727 //160006 //177930 //178241


// defineDirectoryname

//GetCCUIdandTimeShift
GetCCUIdAndTimeFromTProfileHist* getCCUId = 0;

const std::string dirname ="LaserTimingShiftRun163297VsRun1634833";

const int numEBFed  = 36;
const int maxNumCCUInFed = 68;
const int mxNumXtalInCCU = 25;
const int numSC = 9;

// Set Max and Min on Each Runs.
const int  binlow = -50.0;
const int  binhigh = 50.0;


// SetMaximum Minimum of Bins on TimeshiftHist
const int lbin = -5.0;
const int hbin =  5.0;


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
  mystyle.SetLegendBorderSize(0.5);
  mystyle.SetStatH(0.2);
  mystyle.SetOptStat(11);
  TCanvas myCanvas;
  myCanvas.cd();
  mytprof->Draw("colztext");
  std::string filename="LaserTimingShiftRun163291VsRun163333/";
  filename += mytprof->GetTitle();
  filename += ".png";
  myCanvas.Print(filename.c_str());
	  
}




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

  TDirectory * TestPlots = savefile->mkdir("LaserTiming");
 
  TestPlots->cd();
 

 
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
FedAvgTimingEB->Draw("colztext");
FedAvgTimingEB->Write();


 
//EE Plus
 FedAvgTimingEEP->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEP->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEP->Draw("colztext");
 FedAvgTimingEEP->Write();

 
 //EE Minus
 FedAvgTimingEEM->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEM->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEM->Draw("colztext");
 FedAvgTimingEEM->Write();

 
 
for( int numfed = 0; numfed < numEBFed; numfed++)
{
// CCUAvgTimingEBplus[j]->Write();
 CCUAvgTimeEB_RunA[numfed]->GetXaxis()->SetTitle("i#phi");
 CCUAvgTimeEB_RunA[numfed]->GetYaxis()->SetTitle("i#eta");
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
 FedAvgTimingEEP_RunB->Draw("colztext");
 FedAvgTimingEEP_RunB->Write();

 
 // run B
  //EE Minus
 FedAvgTimingEEM_RunB->GetXaxis()->SetTitle("ix");
 FedAvgTimingEEM_RunB->GetYaxis()->SetTitle("iy");
 FedAvgTimingEEM_RunB->Draw("colztext");
 FedAvgTimingEEM_RunB->Write();

 //ALL EB SM

 // Run B
FedAvgTimingEB_RunB->GetXaxis()->SetTitle("i#phi");
FedAvgTimingEB_RunB->GetYaxis()->SetTitle("i#eta");
FedAvgTimingEB_RunB->Draw("colztext");
FedAvgTimingEB_RunB->Write();


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




/////////&&&&&& Trial Fxn To calculate TprofSubtract &&&&&&&/////////
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
  TProfile2D *result_hprof =(TProfile2D*)hprof_runA->Clone("MynewCCUMeanTimehprof");

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
		  
		 
		  // Time Diff
		  float timeshift = timeA - timeB;

		   // check here for Empty CCUs in A and B and set Time Extra Large.;
		  if( nentriesA == 0 || nentriesB == 0)
			{
			  result_hprof->SetBinContent(binsA, -9999999); // If No entry Set Etra large Time,Plot shows white. 
			}else
			{
			  
			  result_hprof->SetBinContent(binsA, timeshift);
			  result_hprof->SetBinEntries(binsA, 1);
			}
		  //result_hprof->Fill(ixa, iya, timeshift);
		  
		  //debug if the right thinsg is being done
		  
		  if((timeshift >=5 || timeshift <=-5) && timeA !=0 && timeB !=0)
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




//////&&&&&&&&& Version 1 Funtion to Substract Hists &&&&&&&&&&&&&&&&/////////////////

TProfile2D* SubtractHistProf( TProfile2D* hprof_runA, TProfile2D* hprof_runB)
{
  if(!hprof_runA){cout << "No input histograms was put" << endl;}

  TProfile2D*  clonehprof = (TProfile2D*)hprof_runA->Clone("CCUMeantimeDiff");
  //   TProfile2D*  clonehprof = (TProfile2D*)hprof_runA->Clone(hprof_runA->GetName());

  //subtract Histograms:
    clonehprof->Add(hprof_runB, -1);
	// hprof_runA->Add(hprof_runB, -1);
    moveBinsTProfile2D(clonehprof);
	// moveBinsTProfile2D(hprof_runA);
    clonehprof->SetMinimum(-5);
    clonehprof->SetMaximum(5);
  // hprof_runA->SetMinimum(-5);
  // hprof_runA->SetMaximum(5);

  return clonehprof;
  // return hprof_runA;
} // end of fxn to subtract hists





//  CLass Defining Each Xtal
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


std::string ConvertIntToString(int num)
{
  //  using name space std;
  stringstream mystream;
  mystream  << num;

  return mystream.str();
  
}


/////// ***** Fxn Main Begins *********///////
int main(int argc, char ** argv)
{
    int * wl = NULL, nwl = 0;
    TChain * tx = new TChain("x");

		tx->Add("/hdfs/cms/user/norbert/data/Validlaser/*.root");
		//	tx->Add("/hdfs/cms/user/norbert/data/Laser/*.root"); ///hdfs/cms/user/norbert/data/Validlaser
	   //	  tx->Add("/hdfs/cms/user/norbert/data/NewLaserData/ntuple_example/*.root");
	//	tx->Add("/hdfs/cms/user/norbert/data/NewLaserData/cmsecallaser/srv-ecal-laser-13/disk0/ferriff/tree_data/ntuple_example/*.root");



//We Define  EB Feds
for( int hnum = 0; hnum < numEBFed; hnum++)
  {
	std::string fedhistname = "CCU_Mean_Time_EB";

	if(hnum < 18)
	  {
		//fedhistname +="EB";
		fedhistname += ConvertIntToString(( hnum + 610));
		fedhistname +=ConvertIntToString(-hnum);

	    fedhistname +="_RunA";
        CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1,21,17,1.,86);
		
		// For Run B
		fedhistname +="_RunB";
		CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1,21,17,1.,86);
		
//CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);
		

  }else if (hnum > 17 )
		  {
			//    fedhistname +="EB";
			fedhistname += ConvertIntToString(( hnum + 610));
			fedhistname +=ConvertIntToString(hnum-18);

		    fedhistname +="_RunA";
			CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1,21,17,1,86);
			// For Run B
			fedhistname +="_RunB";
			CCUAvgTimeEB_RunB[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1,21,17,1.,86);

//CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1+(hnum-18)*20,1+((hnum-18)+1)*20,17,1,86);



		  }
  }

 
// Do EE Here!
//	 CCUAvgTimeEEP_RunA[eeSec]
for( int eeMnum = 0; eeMnum < 9; eeMnum++)
  {
	std::string fedhistname = "CCU_Mean_Time_EEMinus";

	//fedhistname +="EB";
	//For Run A EE Minus
		fedhistname += ConvertIntToString(( eeMnum + 601));
		//		fedhistname +=ConvertIntToString(-hnum);
		fedhistname +="_RunA";
        CCUAvgTimeEEM_RunA[eeMnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),20,0.0,100,20,0.,100);
		
		// For Run B
		fedhistname +="_RunB";
		CCUAvgTimeEEM_RunB[eeMnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),20,0.,100,20,0.,100);
		
    //CCUAvgTimeEB_RunA[hnum] = new TProfile2D(fedhistname.c_str(),fedhistname.c_str(),4,1+hnum*20,1+(hnum+1)*20,17,-85,0);

		// EE Plus
		//RunA551

		std::string EESecname = "CCU_Mean_Time_EEPlus";
		EESecname += ConvertIntToString(eeMnum + 646);

			EESecname +="_RunA";
		CCUAvgTimeEEP_RunA[eeMnum] = new TProfile2D(EESecname.c_str(),EESecname.c_str(), 20, 0., 100, 20, 0.,100);

		// For Run B
		EESecname +="_RunB";
		
		CCUAvgTimeEEP_RunB[eeMnum] = new TProfile2D(EESecname.c_str(),EESecname.c_str(), 20, 0., 100, 20, 0.,100); 
  }

 
//  sprintf(hprofnameEB,"EB %d",hnum);
//  bufferTitleEB.erase();
//  bufferTitleEB = std::string(hprofnameEB)+ std::string("CCU Mean Time[ns]");
//  CCUAvgTimeEB_RunA[hnum] = new TProfile2D(hprofnameEB,bufferTitleEB.c_str(),4, 1,21,17,1,86);
 


 // CCUAvgTimingEB[i] = new TProfile2D("CCUAvgTimingEB[i]","CCU Mean Time Distrubution EBP[i]",17, 0,85,4,0,20);

// sprintf(hprofnameEBminus,"EB- %d",hnum);
// bufferTitleEBminus.erase();
// bufferTitleEBminus = std::string(hprofnameEBminus)+std::string(",CCU Mean Time [ns]");
//  CCUAvgTimingEBminus[hnum] = new TProfile2D(hprofnameEBminus,bufferTitleEBminus.c_str(),17, -85,1,4,0,20);
// //CCUAvgTimingEBminus[i] = new TProfile2D("CCUAvgTimingEBminus[i]","CCU Mean Time Distrubution EBM[i]",17, -85,1,4,0,20);
 //   }



//EB All SM
 FedAvgTimingEB = new TProfile2D("FedAvgTimingEB","CCU Mean Time EB", 360, 1., 361, 171, -85,85);

 // run B
FedAvgTimingEB_RunB = new TProfile2D("FedAvgTimingEB_RunB","CCU Mean Time EB", 360, 1., 361, 171, -85,85);

//EE plus
 FedAvgTimingEEP = new TProfile2D("FedAvgTimingEEP","CCU Mean Time EE+", 100, 0., 100., 100, 0, 100);
 //Run B
 FedAvgTimingEEP_RunB = new TProfile2D("FedAvgTimingEEP_RunB","CCU Mean Time EE+", 100, 0., 100., 100, 0, 100);
//FedAvgTimingEEP = new TProfile2D("FedAvgTimingEEP","CCU Mean Time EE+", 100, -50., 50., 100, 0, 100);
 //EE minus
  FedAvgTimingEEM = new TProfile2D("FedAvgTimingEEM","CCU Mean Time EE-", 100, 0., 100., 100, 0, 100);
  // run B
   FedAvgTimingEEM_RunB = new TProfile2D("FedAvgTimingEEM_RunB","CCU Mean Time EE-", 100, 0., 100., 100, 0, 100);

//FedAvgTimingEEM = new TProfile2D("FedAvgTimingEEM","CCU Mean Time EE-", 100, -50., 50., 100, -100, 0);



 // Ssave Out Put Files  here!
    savefile = new TFile("EcalLaserTiming_New_163291Vs163333_March02.root", "recreate");

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


		
// Loop over Crystals Begin Here!  
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
		int ieta = ebdetid.ietaSM();
 		int iphi = ebdetid.iphiSM();

			
//		int ieta = x.ix;
//		int iphi = x.iy+10;
        float crytime = x.tmax[0];
		float Xtaltime = (crytime - 5)*25;
		int  EBXtalFed = x.fed;
		int numfed = EBXtalFed - 610;


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
		 FedAvgTimingEB->Fill(x.iy+10,x.ix,(x.tmax[0]-5)*25);  // making some changes here Now!

		 //   Do EE  here!
 }else{
            wl = eewl;
            nwl = 3;
//            EEDetId eedetid;

        EEDetId eedetid(x.detId);
		int ix = eedetid.ix();
 		int iy = eedetid.iy();

		int EExtalfed = x.fed;
	


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

			
			 FedAvgTimingEEM->Fill(ix,iy,(x.tmax[0]-5)*25);
     	   }else

	      {
			cout << "Plus EE crystals" << endl;

					// For EE Plus
			int eehistprofp = EExtalfed - 646;
			float crytime = (x.tmax[0]-5)*25;
			CCUAvgTimeEEP_RunA[eehistprofp]->Fill(ix, iy, crytime);

              FedAvgTimingEEP->Fill(ix,iy,(x.tmax[0]-5)*25);
	      }
	    
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
		int ieta = ebdetid.ietaSM();
 		int iphi = ebdetid.iphiSM();

			
//		int ieta = x.ix;
//		int iphi = x.iy+10;
        float crytime = x.tmax[0];
		float Xtaltime = (crytime - 5)*25;
		int  EBXtalFed = x.fed;
		int numfed = EBXtalFed - 610;


		if(x.fed ==610)
		  {
			EBM1Dtime_RunB->Fill(Xtaltime);
			cout <<  " the Xtal eta is:" << ieta << " Xtal Phi:" << iphi << " Xtal Time is:" << Xtaltime << endl;
		  }

		if (x.fed == 628)
		  {

			cout << "Crystal time is :" << Xtaltime << endl;
			EBP1Dtime_RunB->Fill(Xtaltime);
			
		  }
		
         CCUAvgTimeEB_RunB[numfed]->Fill(iphi, ieta, Xtaltime); // Fill all EB-FEDs
	

   
		 XtaltimeVsAmpEB_RunB->Fill(x.qmax[0],Xtaltime); // OBX time here!
		//XtaltimeVsTimeEB->Fill( x.time[0],x.tmax[0]);
	    XtaltimeVsLumiEB_RunB->Fill(x.lumi[0],x.tmax[0]);
	    XtaltimeVsFedIDEB_RunB->Fill(x.fed,(x.tmax[0]-5)*25);

		xtaltimeDistEB_RunB->Fill( (x.tmax[0]-5)*25);
		FedAvgTimingEB_RunB->Fill(x.iy+10,x.ix,(x.tmax[0]-5)*25); //  same changes here now!

		 //   Do EE  here!
 }else{
            wl = eewl;
            nwl = 3;
//            EEDetId eedetid;

         EEDetId eedetid(x.detId);
		int ix = eedetid.ix();
 		int iy = eedetid.iy();

		int EExtalfed = x.fed;
          // Loop over number crystals in EE
			xtaltimeDistEE_RunB->Fill( (x.tmax[0]-5)*25);
			XtaltimeVsAmpEE_RunB->Fill(x.qmax[0],(x.tmax[0]-5)*25);
			//	        XtaltimeVsTimeEE_RunB->Fill( x.time[0],(x.tmax[0]-5)*25);

			XtaltimeVsFedIDEE_RunB->Fill(x.fed,(x.tmax[0]-5)*25);

	    if(x.fed >=601 && x.fed <= 609)
		  {

				// For EE Minus
			int eehistprofm = EExtalfed - 601;
			float crytime = (x.tmax[0]-5)*25;
			CCUAvgTimeEEM_RunB[eehistprofm]->Fill(ix, iy, crytime);

			 FedAvgTimingEEM_RunB->Fill(ix,iy,(x.tmax[0]-5)*25);

		  }else

	      {
			cout << "Plus EE crystals" << endl;
					// For EE Plus
			int eehistprofp = EExtalfed - 646;
			float crytime = (x.tmax[0]-5)*25;
			CCUAvgTimeEEP_RunB[eehistprofp]->Fill(ix, iy, crytime);

            FedAvgTimingEEP_RunB->Fill(ix,iy,(x.tmax[0]-5)*25);
	      }
	    
   }


          //Fill generally for all sturff.
          XtaltimeVsEta_RunB->Fill(x.eta, (x.tmax[0]-5)*25);
          XtaltimeVsRun_RunB->Fill( x.run,(x.tmax[0]-5)*25);


numcrys +=numcrys;

if( numcrys > 75838) break; 

  }   // end of choice of run  After TS and Seq


 
}// end of Loop over entries( xtals)


 
////// Calculate CCU Time Shift Here!////////

//First for ALL EB and EE

//EB 
 CrysTimeShiftEB = SubtractTwoTProfile2D(FedAvgTimingEB,  FedAvgTimingEB_RunB);
 CrysTimeShiftEB ->SetMinimum(lbin);
 CrysTimeShiftEB->SetMaximum(hbin);
 SaveCanvasInDir(CrysTimeShiftEB);
 //EEP
 CrysTimeShiftEEP = SubtractTwoTProfile2D(FedAvgTimingEEP, FedAvgTimingEEP_RunB);
 CrysTimeShiftEEP->SetMinimum(lbin);
 CrysTimeShiftEEP->SetMaximum(hbin);
 SaveCanvasInDir(CrysTimeShiftEEP);
	
 //EEM 
 CrysTimeShiftEEM = SubtractTwoTProfile2D(FedAvgTimingEEM, FedAvgTimingEEM_RunB);
 CrysTimeShiftEEM->SetMinimum(lbin);
 CrysTimeShiftEEM->SetMaximum(hbin);
 SaveCanvasInDir(CrysTimeShiftEEM);


 //loop over all FED TProfile2D
 // EB
   for( int nh = 0; nh < numEBFed; nh++)
	 {
	  
	   CCUTimeShiftEB[nh]= SubtractTwoTProfile2D(CCUAvgTimeEB_RunA[nh], CCUAvgTimeEB_RunB[nh]);
	   CCUTimeShiftEB[nh]->SetMinimum(lbin);
	   CCUTimeShiftEB[nh]->SetMaximum(hbin);
	   SaveCanvasInDir( CCUTimeShiftEB[nh]);
	    	// Get CCUId and Time
	   //	   GetCCUIdAndTimeFromTProfileHist::
	   //	 	   getCCUId->GetCCUIdandTimeShift(CCUTimeShiftEB[nh], 0);   
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
	    	SaveCanvasInDir(CCUTimeShiftEEP[eenh]);
//GetCCUId and Time EE+
			//	GetCCUIdAndTimeFromTProfileHist::
			//			getCCUId->GetCCUIdandTimeShift(CCUTimeShiftEEP[eenh], 1); 
	    
	   //EE Minus   
		CCUTimeShiftEEM[eenh]= SubtractTwoTProfile2D(CCUAvgTimeEEM_RunA[eenh], CCUAvgTimeEEM_RunB[eenh]);
		
	    	CCUTimeShiftEEM[eenh]->SetMinimum(lbin);
        	CCUTimeShiftEEM[eenh]->SetMaximum(hbin);
		SaveCanvasInDir(CCUTimeShiftEEM[eenh]);
// Get CCUId and Time EE-
//		GetCCUIdAndTimeFromTProfileHist::
//		getCCUId->GetCCUIdandTimeShift(CCUTimeShiftEEM[eenh], -1); 
	 }

   
    cout << " Write Histograms" << endl;
    writehist();

    savefile->Close();


	// Add function to Map TimeShift to CCUId  Here!


    return 0;

}



