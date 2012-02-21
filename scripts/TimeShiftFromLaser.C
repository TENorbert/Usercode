// Macro to Compute the timing Shift from Laser
// It takes two CCUsInEB and Do a bin by bin subtraction
// Cheers @ TEN


#include "string.h"
#include "TChain.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TMath.h"
#include"Riostream.h"

#include "TProfile2D.h"



using namespace std;



TFile *CCU_Mean_Time_Diff;

//  Fxn to move Bins

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
}




void TimeShiftFromLaser(char *fileA)
{

  std::cout << " File Read is:" << fileA << "for Laser Run A" << std::endl;
  //  std::cout << "File Read is:" << fileB << "for Laser Run B " << std::endl;
  TFile* fA =new TFile(fileA);

  //  TFile* fB = new TFile(fileB);



  
 //  Hist To calculate  Timing Diff!

  // Run A
  //EB Minus
  TProfile2D* CCUMeanTimeRunA1 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6100");
  TProfile2D* CCUMeanTimeRunA2 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB611-1");
  TProfile2D* CCUMeanTimeRunA3 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB612-2");
  TProfile2D* CCUMeanTimeRunA4 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB613-3");
  TProfile2D* CCUMeanTimeRunA5 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB614-4");

  TProfile2D* CCUMeanTimeRunA6 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB615-5");
  TProfile2D* CCUMeanTimeRunA7 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB616-6");
  TProfile2D* CCUMeanTimeRunA8 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB617-7");
  TProfile2D* CCUMeanTimeRunA9 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB618-8");
  TProfile2D* CCUMeanTimeRunA10 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB619-9");
  TProfile2D* CCUMeanTimeRunA11 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB620-10");
  TProfile2D* CCUMeanTimeRunA12 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB621-11");
  TProfile2D* CCUMeanTimeRunA13 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB622-12");
  TProfile2D* CCUMeanTimeRunA14 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB623-13");
  TProfile2D* CCUMeanTimeRunA15 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB624-14");
  TProfile2D* CCUMeanTimeRunA16 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB625-15");
  TProfile2D* CCUMeanTimeRunA17 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB626-16");
  TProfile2D* CCUMeanTimeRunA18 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB627-17");

  //EB plus
  TProfile2D* CCUMeanTimeRunAP0 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6280");
  TProfile2D* CCUMeanTimeRunAP1 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6291");
  TProfile2D* CCUMeanTimeRunAP2 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6302");
  TProfile2D* CCUMeanTimeRunAP3 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6313");
  TProfile2D* CCUMeanTimeRunAP4 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6324");
  TProfile2D* CCUMeanTimeRunAP5 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6335");
  TProfile2D* CCUMeanTimeRunAP6 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6346");
  TProfile2D* CCUMeanTimeRunAP7 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6357");
  TProfile2D* CCUMeanTimeRunAP8 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6368");
  TProfile2D* CCUMeanTimeRunAP9 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB6379");
  TProfile2D* CCUMeanTimeRunAP10 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB63810");
  TProfile2D* CCUMeanTimeRunAP11 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB63911");
  TProfile2D* CCUMeanTimeRunAP12 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64012");
  TProfile2D* CCUMeanTimeRunAP13 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64113");
  TProfile2D* CCUMeanTimeRunAP14 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64214");
  TProfile2D* CCUMeanTimeRunAP15 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64315");
  TProfile2D* CCUMeanTimeRunAP16 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64416");
  TProfile2D* CCUMeanTimeRunAP17 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunA/CCU_Mean_Time_EB64517");


  //ALL EB/EE
  TProfile2D* EBMeanTimeDiffRunA = (TProfile2D*)fA->Get("LaserTiming/FedAvgTimingEB");
  TProfile2D* EEPMeanTimeDiffRunA = (TProfile2D*)fA->Get("LaserTiming/FedAvgTimingEEP");
  TProfile2D* EEMMeanTimeDiffRunA = (TProfile2D*)fA->Get("LaserTiming/FedAvgTimingEEM");
  
  
 // TProfile2D *CrysMeanTimeDistEEPlusRunA = (TProfile2D*)f11->Get("");
 // TProfile2D *CrysMeanTimeDistEEMinusRunA = (TProfile2D*)f11->Get("");


  
 //Run B
  //EB Minus
  TProfile2D* CCUMeanTimeRunB1 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6100_RunB");
  TProfile2D* CCUMeanTimeRunB2 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB611-1_RunB");
  TProfile2D* CCUMeanTimeRunB3 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB612-2_RunB");
  TProfile2D* CCUMeanTimeRunB4 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB613-3_RunB");
  TProfile2D* CCUMeanTimeRunB5 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB614-4_RunB");

  TProfile2D* CCUMeanTimeRunB6 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB615-5_RunB");
  TProfile2D* CCUMeanTimeRunB7 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB616-6_RunB");
  TProfile2D* CCUMeanTimeRunB8 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB617-7_RunB");
  TProfile2D* CCUMeanTimeRunB9 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB618-8_RunB");
  TProfile2D* CCUMeanTimeRunB10 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB619-9_RunB");
  TProfile2D* CCUMeanTimeRunB11 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB620-10_RunB");
  TProfile2D* CCUMeanTimeRunB12 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB621-11_RunB");
  TProfile2D* CCUMeanTimeRunB13 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB622-12_RunB");
  TProfile2D* CCUMeanTimeRunB14 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB623-13_RunB");
  TProfile2D* CCUMeanTimeRunB15 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB624-14_RunB");
  TProfile2D* CCUMeanTimeRunB16 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB625-15_RunB");
  TProfile2D* CCUMeanTimeRunB17 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB626-16_RunB");
  TProfile2D* CCUMeanTimeRunB18 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB627-17_RunB");

  //EB plus
  TProfile2D* CCUMeanTimeRunBP0 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6280_RunB");
  TProfile2D* CCUMeanTimeRunBP1 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6291_RunB");
  TProfile2D* CCUMeanTimeRunBP2 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6302_RunB");
  TProfile2D* CCUMeanTimeRunBP3 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6313_RunB");
  TProfile2D* CCUMeanTimeRunBP4 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6324_RunB");
  TProfile2D* CCUMeanTimeRunBP5 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6335_RunB");
  TProfile2D* CCUMeanTimeRunBP6 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6346_RunB");
  TProfile2D* CCUMeanTimeRunBP7 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6357_RunB");
  TProfile2D* CCUMeanTimeRunBP8 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6368_RunB");
  TProfile2D* CCUMeanTimeRunBP9 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB6379_RunB");
  TProfile2D* CCUMeanTimeRunBP10 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB63810_RunB");
  TProfile2D* CCUMeanTimeRunBP11 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB63911_RunB");
  TProfile2D* CCUMeanTimeRunBP12 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64012_RunB");
  TProfile2D* CCUMeanTimeRunBP13 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64113_RunB");
  TProfile2D* CCUMeanTimeRunBP14 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64214_RunB");
  TProfile2D* CCUMeanTimeRunBP15 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64315_RunB");
  TProfile2D* CCUMeanTimeRunBP16 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64416_RunB");
  TProfile2D* CCUMeanTimeRunBP17 = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/CCU_Mean_Time_EB64517_RunB");
  


  //ALL EB/EE
  TProfile2D* EBMeanTimeDiffRunB = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/FedAvgTimingEB_RunB");
  TProfile2D* EEPMeanTimeDiffRunB = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/FedAvgTimingEEP_RunB");
  TProfile2D* EEMMeanTimeDiffRunB = (TProfile2D*)fA->Get("CCUInEBFedsTime_RunB/FedAvgTimingEEM_RunB");
  



  
//   TProfile2D* CCUMeanTimeRunB1 = (TProfile2D*)fB->Get("CCUInEBFedsTiming/CCU_Mean_Time_EB6100");
//   TProfile2D* CCUMeanTimeRunB2 = (TProfile2D*)fB->Get("CCUInEBFedsTiming/CCU_Mean_Time_EB611-1");
//   TProfile2D* CCUMeanTimeRunB3 = (TProfile2D*)fB->Get("CCUInEBFedsTiming/CCU_Mean_Time_EB612-2");
//   TProfile2D* CCUMeanTimeRunB4 = (TProfile2D*)fB->Get("CCUInEBFedsTiming/CCU_Mean_Time_EB613-3");
//   TProfile2D* CCUMeanTimeRunB5 = (TProfile2D*)fB->Get("CCUInEBFedsTiming/CCU_Mean_Time_EB614-4");


 // TProfile2D *CrysMeanTimeDistEEPlusRunB = (TProfile2D*)f10->Get("");
 // TProfile2D *CrysMeanTimeDistEEMinusRunB = (TProfile2D*)f10->Get("");


        
 std::cout << "CCUMeanTimeRunA  is:" 
          << CCUMeanTimeRunA1->GetName() << " and has " 
          << CCUMeanTimeRunA1 ->GetEntries() << " entries;" 
          << std::endl;
std::cout << "CCUMeanTimeRunB  is: " 
          << CCUMeanTimeRunB1 ->GetName() << " and has " 
          << CCUMeanTimeRunB1->GetEntries() << " entries;" 
          << std::endl;


//  Make Clones of Hists
// EB Minus Clones
 TProfile2D* CCUDiffInMeanTimeClone1 = (TProfile2D*)CCUMeanTimeRunA1->Clone("CrysMeanTimeDiffEBM1");
 TProfile2D* CCUDiffInMeanTimeClone2 = (TProfile2D*)CCUMeanTimeRunA2->Clone("CrysMeanTimeDiffEBM2");
 TProfile2D* CCUDiffInMeanTimeClone3 = (TProfile2D*)CCUMeanTimeRunA3->Clone("CrysMeanTimeDiffEBM3");
 TProfile2D* CCUDiffInMeanTimeClone4 = (TProfile2D*)CCUMeanTimeRunA4->Clone("CrysMeanTimeDiffEBM4");
 TProfile2D* CCUDiffInMeanTimeClone5 = (TProfile2D*)CCUMeanTimeRunA5->Clone("CrysMeanTimeDiffEBM5");


 TProfile2D* CCUDiffInMeanTimeClone6 = (TProfile2D*)CCUMeanTimeRunA6->Clone("CrysMeanTimeDiffEBM6");
 TProfile2D* CCUDiffInMeanTimeClone7 = (TProfile2D*)CCUMeanTimeRunA7->Clone("CrysMeanTimeDiffEBM7");
 TProfile2D* CCUDiffInMeanTimeClone8 = (TProfile2D*)CCUMeanTimeRunA8->Clone("CrysMeanTimeDiffEBM8");
 TProfile2D* CCUDiffInMeanTimeClone9 = (TProfile2D*)CCUMeanTimeRunA9->Clone("CrysMeanTimeDiffEBM9");
 TProfile2D* CCUDiffInMeanTimeClone10 = (TProfile2D*)CCUMeanTimeRunA10->Clone("CrysMeanTimeDiffEBM10");
 TProfile2D* CCUDiffInMeanTimeClone11 = (TProfile2D*)CCUMeanTimeRunA11->Clone("CrysMeanTimeDiffEBM11");
 TProfile2D* CCUDiffInMeanTimeClone12 = (TProfile2D*)CCUMeanTimeRunA12->Clone("CrysMeanTimeDiffEBM12");
 TProfile2D* CCUDiffInMeanTimeClone13 = (TProfile2D*)CCUMeanTimeRunA13->Clone("CrysMeanTimeDiffEBM13");
 TProfile2D* CCUDiffInMeanTimeClone14 = (TProfile2D*)CCUMeanTimeRunA14->Clone("CrysMeanTimeDiffEBM14");
 TProfile2D* CCUDiffInMeanTimeClone15 = (TProfile2D*)CCUMeanTimeRunA15->Clone("CrysMeanTimeDiffEBM15");
 TProfile2D* CCUDiffInMeanTimeClone16 = (TProfile2D*)CCUMeanTimeRunA16->Clone("CrysMeanTimeDiffEBM16");
 TProfile2D* CCUDiffInMeanTimeClone17 = (TProfile2D*)CCUMeanTimeRunA17->Clone("CrysMeanTimeDiffEBRM17");
 TProfile2D* CCUDiffInMeanTimeClone18 = (TProfile2D*)CCUMeanTimeRunA18->Clone("CrysMeanTimeDiffEBM18");

 // EB plus Clones
 TProfile2D* CCUDiffInMeanTimeCloneP0 = (TProfile2D*)CCUMeanTimeRunAP0->Clone("CrysMeanTimeDiffEBP1");
 TProfile2D* CCUDiffInMeanTimeCloneP1 = (TProfile2D*)CCUMeanTimeRunAP1->Clone("CrysMeanTimeDiffEBP2");
 TProfile2D* CCUDiffInMeanTimeCloneP2 = (TProfile2D*)CCUMeanTimeRunAP2->Clone("CrysMeanTimeDiffEBP3");
 TProfile2D* CCUDiffInMeanTimeCloneP3 = (TProfile2D*)CCUMeanTimeRunAP3->Clone("CrysMeanTimeDiffEBP4");
 TProfile2D* CCUDiffInMeanTimeCloneP4 = (TProfile2D*)CCUMeanTimeRunAP4->Clone("CrysMeanTimeDiffEBP5");
 TProfile2D* CCUDiffInMeanTimeCloneP5 = (TProfile2D*)CCUMeanTimeRunAP5->Clone("CrysMeanTimeDiffEBP6");
 TProfile2D* CCUDiffInMeanTimeCloneP6 = (TProfile2D*)CCUMeanTimeRunAP6->Clone("CrysMeanTimeDiffEBP7");
 TProfile2D* CCUDiffInMeanTimeCloneP7 = (TProfile2D*)CCUMeanTimeRunAP7->Clone("CrysMeanTimeDiffEBP8");
 TProfile2D* CCUDiffInMeanTimeCloneP8 = (TProfile2D*)CCUMeanTimeRunAP8->Clone("CrysMeanTimeDiffEBP9");
 TProfile2D* CCUDiffInMeanTimeCloneP9 = (TProfile2D*)CCUMeanTimeRunAP9->Clone("CrysMeanTimeDiffEBP10");
 TProfile2D* CCUDiffInMeanTimeCloneP10 = (TProfile2D*)CCUMeanTimeRunAP10->Clone("CrysMeanTimeDiffEBP11");
 TProfile2D* CCUDiffInMeanTimeCloneP11 = (TProfile2D*)CCUMeanTimeRunAP11->Clone("CrysMeanTimeDiffEBP12");
 TProfile2D* CCUDiffInMeanTimeCloneP12 = (TProfile2D*)CCUMeanTimeRunAP12->Clone("CrysMeanTimeDiffEBP13");
 TProfile2D* CCUDiffInMeanTimeCloneP13 = (TProfile2D*)CCUMeanTimeRunAP13->Clone("CrysMeanTimeDiffEBP14");
 TProfile2D* CCUDiffInMeanTimeCloneP14 = (TProfile2D*)CCUMeanTimeRunAP14->Clone("CrysMeanTimeDiffEBP15");
 TProfile2D* CCUDiffInMeanTimeCloneP15 = (TProfile2D*)CCUMeanTimeRunAP15->Clone("CrysMeanTimeDiffEBP16");
 TProfile2D* CCUDiffInMeanTimeCloneP16 = (TProfile2D*)CCUMeanTimeRunAP16->Clone("CrysMeanTimeDiffEBP17");
 TProfile2D* CCUDiffInMeanTimeCloneP17 = (TProfile2D*)CCUMeanTimeRunAP17->Clone("CrysMeanTimeDiffEBP18");


 //All EB/EE

 TProfile2D* EBMeanTimeFDiffClone = (TProfile2D*)EBMeanTimeDiffRunA->Clone("CrysInEB_MeanTimeDiff");
 TProfile2D* EEPMeanTimeFDiffClone = (TProfile2D*)EEPMeanTimeDiffRunA->Clone("CrysInEEP_MeanTimeDiff");
 TProfile2D* EEMMeanTimeFDiffClone = (TProfile2D*)EEMMeanTimeDiffRunA->Clone("CrysInEEM_MeanTimeDiff");
 
 
 
 
 // TProfile2D* CrysmeanDiffEEplusRunAClone = (TProfile2D*)CrysMeanTimeDistEEPlusRunA->Clone("CrysMeanTimeDiffEEPlusRun1");
 //TProfile2D* CrysmeanDiffEEMinusRunAClone = (TProfile2D*)CrysMeanTimeDistEEMinusRunA->Clone("CrysMeanTimeDiffEEMinusRun1");

 //subtract bin-by-bin
 //   EB Minus
  CCUDiffInMeanTimeClone1->Add(CCUMeanTimeRunB1, -1);
  CCUDiffInMeanTimeClone2->Add(CCUMeanTimeRunB2, -1);
  CCUDiffInMeanTimeClone3->Add(CCUMeanTimeRunB3, -1);
  CCUDiffInMeanTimeClone4->Add(CCUMeanTimeRunB4, -1);
  CCUDiffInMeanTimeClone5->Add(CCUMeanTimeRunB5, -1);

  CCUDiffInMeanTimeClone6->Add(CCUMeanTimeRunB6, -1);
  CCUDiffInMeanTimeClone7->Add(CCUMeanTimeRunB7, -1);
  CCUDiffInMeanTimeClone8->Add(CCUMeanTimeRunB8, -1);
  CCUDiffInMeanTimeClone9->Add(CCUMeanTimeRunB9, -1);
  CCUDiffInMeanTimeClone10->Add(CCUMeanTimeRunB10, -1);
  CCUDiffInMeanTimeClone11->Add(CCUMeanTimeRunB11, -1);
  CCUDiffInMeanTimeClone12->Add(CCUMeanTimeRunB12, -1);
  CCUDiffInMeanTimeClone13->Add(CCUMeanTimeRunB13, -1);
  CCUDiffInMeanTimeClone14->Add(CCUMeanTimeRunB14, -1);
  CCUDiffInMeanTimeClone15->Add(CCUMeanTimeRunB15, -1);
  CCUDiffInMeanTimeClone16->Add(CCUMeanTimeRunB16, -1);
  CCUDiffInMeanTimeClone17->Add(CCUMeanTimeRunB17, -1);
  CCUDiffInMeanTimeClone18->Add(CCUMeanTimeRunB18, -1);

  //EB Plus
  CCUDiffInMeanTimeCloneP0->Add(CCUMeanTimeRunBP0, -1);
  CCUDiffInMeanTimeCloneP1->Add(CCUMeanTimeRunBP1, -1);
  CCUDiffInMeanTimeCloneP2->Add(CCUMeanTimeRunBP2, -1);
  CCUDiffInMeanTimeCloneP3->Add(CCUMeanTimeRunBP3, -1);
  CCUDiffInMeanTimeCloneP4->Add(CCUMeanTimeRunBP4, -1);
  CCUDiffInMeanTimeCloneP5->Add(CCUMeanTimeRunBP5, -1);
  CCUDiffInMeanTimeCloneP6->Add(CCUMeanTimeRunBP6, -1);
  CCUDiffInMeanTimeCloneP7->Add(CCUMeanTimeRunBP7, -1);
  CCUDiffInMeanTimeCloneP8->Add(CCUMeanTimeRunBP8, -1);
  CCUDiffInMeanTimeCloneP9->Add(CCUMeanTimeRunBP9, -1);
  CCUDiffInMeanTimeCloneP10->Add(CCUMeanTimeRunBP10, -1);
  CCUDiffInMeanTimeCloneP11->Add(CCUMeanTimeRunBP11, -1);
  CCUDiffInMeanTimeCloneP12->Add(CCUMeanTimeRunBP12, -1);
  CCUDiffInMeanTimeCloneP13->Add(CCUMeanTimeRunBP13, -1);
  CCUDiffInMeanTimeCloneP14->Add(CCUMeanTimeRunBP14, -1);
  CCUDiffInMeanTimeCloneP15->Add(CCUMeanTimeRunBP15, -1);
  CCUDiffInMeanTimeCloneP16->Add(CCUMeanTimeRunBP16, -1);
  CCUDiffInMeanTimeCloneP17->Add(CCUMeanTimeRunBP17, -1);
  
  //ALL EB/EE
  EBMeanTimeFDiffClone->Add(EBMeanTimeDiffRunB ,-1);
  EEPMeanTimeFDiffClone->Add(EEPMeanTimeDiffRunB ,-1);
  EEMMeanTimeFDiffClone->Add(EEMMeanTimeDiffRunB ,-1);
  

  
 // CrysmeanDiffEEplusRunAClone ->Add(CrysMeanTimeDistEEPlusRunB, -1);
 // CrysmeanDiffEEMinusRunAClone->Add(CrysMeanTimeDistEEMinusRunB, -1);


 // Histogram to Hold Diffs
 // TProfile2D* XtalMeanTimeShiftEB = new TProfile2D("XtalMeanTimeShiftEB","Crystal Mean Time Shift EB [BX]", 360, -10.0, 350.0, 171, -85, 85);
//  XtalMeanTimeShiftEB->GetYaxis()->SetTitle("i#eta");
//  XtalMeanTimeShiftEB->GetXaxis()->SetTitle("i#phi");



 // // What us the size of the Hist Holding the difference?
//  int numBinsEBX = CCUMeanTimeRunA->GetNbinsX();
//  int numBinsEBY = CCUMeanTimeRunA->GetNbinsY();
// int numBinsEBZ = CCUMeanTimeRunA->GetNbinsZ();
//  cout << " Number X bins EB =" << numBinsEBX << "Number  Y Bins EB =" << numBinsEBY  << " Number EB Z bins ="<<numBinsEBZ << endl;

//  for(int ii = 1; ii <=(numBinsEBX+2)*(numBinsEBY*2); ii++)
//    {   
            
// 	 XtalMeanTimeShiftEB->Fill(CCUDiffInMeanTimeClone->GetBinContent(ii));

// 	     cout << "Filling The Bins"<< endl;
	   
//    }


  //EB Minus
 moveBinsTProfile2D(CCUDiffInMeanTimeClone1);
 CCUDiffInMeanTimeClone1->SetMinimum(-5);
 CCUDiffInMeanTimeClone1->SetMaximum(5);
 CCUDiffInMeanTimeClone1->SetTitle("CCU Mean Time Shift EB-1 [ns]");
 CCUDiffInMeanTimeClone1->Draw("colztext");
 
 moveBinsTProfile2D(CCUDiffInMeanTimeClone2);
 CCUDiffInMeanTimeClone2->SetMinimum(-5);
 CCUDiffInMeanTimeClone2->SetMaximum(5);
 CCUDiffInMeanTimeClone2->Draw("colztext");
 CCUDiffInMeanTimeClone2->SetTitle("CCU Mean Time Shift EB-2 [ns]");

 
 moveBinsTProfile2D(CCUDiffInMeanTimeClone3);
 CCUDiffInMeanTimeClone3->SetMinimum(-5);
 CCUDiffInMeanTimeClone3->SetMaximum(5);
 CCUDiffInMeanTimeClone3->SetTitle("CCU Mean Time Shift EB-3 [ns]");
 CCUDiffInMeanTimeClone3->Draw("colztext");
 

 moveBinsTProfile2D(CCUDiffInMeanTimeClone4);
 CCUDiffInMeanTimeClone4->SetMinimum(-5);
 CCUDiffInMeanTimeClone4->SetMaximum(5);
 CCUDiffInMeanTimeClone4->SetTitle("CCU Mean Time Shift EB-4 [ns]");
 CCUDiffInMeanTimeClone4->Draw("colztext");

 
 moveBinsTProfile2D(CCUDiffInMeanTimeClone5);
 CCUDiffInMeanTimeClone5->SetMinimum(-5);
 CCUDiffInMeanTimeClone5->SetMaximum(5);
 CCUDiffInMeanTimeClone5->SetTitle("CCU Mean Time Shift EB-5 [ns]");
 CCUDiffInMeanTimeClone5->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone6);
 CCUDiffInMeanTimeClone6->SetMinimum(-5);
 CCUDiffInMeanTimeClone6->SetMaximum(5);
 CCUDiffInMeanTimeClone6->SetTitle("CCU Mean Time Shift EB-6 [ns]");
 CCUDiffInMeanTimeClone6->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone7);
 CCUDiffInMeanTimeClone7->SetMinimum(-5);
 CCUDiffInMeanTimeClone7->SetMaximum(5);
 CCUDiffInMeanTimeClone7->SetTitle("CCU Mean Time Shift EB-7 [ns]");
 CCUDiffInMeanTimeClone7->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone8);
 CCUDiffInMeanTimeClone8->SetMinimum(-5);
 CCUDiffInMeanTimeClone8->SetMaximum(5);
 CCUDiffInMeanTimeClone8->SetTitle("CCU Mean Time Shift EB-8 [ns]");
 CCUDiffInMeanTimeClone8->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone9);
 CCUDiffInMeanTimeClone9->SetMinimum(-5);
 CCUDiffInMeanTimeClone9->SetMaximum(5);
 CCUDiffInMeanTimeClone9->SetTitle("CCU Mean Time Shift EB-9 [ns]");
 CCUDiffInMeanTimeClone9->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone10);
 CCUDiffInMeanTimeClone10->SetMinimum(-5);
 CCUDiffInMeanTimeClone10->SetMaximum(5);
 CCUDiffInMeanTimeClone10->SetTitle("CCU Mean Time Shift EB-10 [ns]");
 CCUDiffInMeanTimeClone10->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone11);
 CCUDiffInMeanTimeClone11->SetMinimum(-5);
 CCUDiffInMeanTimeClone11->SetMaximum(5);
 CCUDiffInMeanTimeClone11->SetTitle("CCU Mean Time Shift EB-11 [ns]");
 CCUDiffInMeanTimeClone11->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone12);
 CCUDiffInMeanTimeClone12->SetMinimum(-5);
 CCUDiffInMeanTimeClone12->SetMaximum(5);
 CCUDiffInMeanTimeClone12->SetTitle("CCU Mean Time Shift EB-12 [ns]");
 CCUDiffInMeanTimeClone12->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone13);
 CCUDiffInMeanTimeClone13->SetMinimum(-5);
 CCUDiffInMeanTimeClone13->SetMaximum(5);
 CCUDiffInMeanTimeClone13->SetTitle("CCU Mean Time Shift EB-13 [ns]");
 CCUDiffInMeanTimeClone13->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone14);
 CCUDiffInMeanTimeClone14->SetMinimum(-5);
 CCUDiffInMeanTimeClone14->SetMaximum(5);
 CCUDiffInMeanTimeClone14->SetTitle("CCU Mean Time Shift EB-14 [ns]");
 CCUDiffInMeanTimeClone14->Draw("colztext");

  moveBinsTProfile2D(CCUDiffInMeanTimeClone15);
 CCUDiffInMeanTimeClone15->SetMinimum(-5);
 CCUDiffInMeanTimeClone15->SetMaximum(5);
 CCUDiffInMeanTimeClone15->SetTitle("CCU Mean Time Shift EB-15 [ns]");
 CCUDiffInMeanTimeClone15->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone16);
 CCUDiffInMeanTimeClone16->SetMinimum(-5);
 CCUDiffInMeanTimeClone16->SetMaximum(5);
 CCUDiffInMeanTimeClone16->SetTitle("CCU Mean Time Shift EB-16 [ns]");
 CCUDiffInMeanTimeClone16->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone17);
 CCUDiffInMeanTimeClone17->SetMinimum(-5);
 CCUDiffInMeanTimeClone17->SetMaximum(5);
 CCUDiffInMeanTimeClone17->SetTitle("CCU Mean Time Shift EB-17 [ns]");
 CCUDiffInMeanTimeClone17->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeClone18);
 CCUDiffInMeanTimeClone18->SetMinimum(-5);
 CCUDiffInMeanTimeClone18->SetMaximum(5);
 CCUDiffInMeanTimeClone18->SetTitle("CCU Mean Time Shift EB-18 [ns]");
 CCUDiffInMeanTimeClone18->Draw("colztext");
 
 // EB  Plus
 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP0);
 CCUDiffInMeanTimeCloneP0->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP0->SetMaximum(5);
 CCUDiffInMeanTimeCloneP0->SetTitle("CCU Mean Time Shift EB+1 [ns]");
 CCUDiffInMeanTimeCloneP0->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP1);
 CCUDiffInMeanTimeCloneP1->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP1->SetMaximum(5);
 CCUDiffInMeanTimeCloneP1->SetTitle("CCU Mean Time Shift EB+2 [ns]");
 CCUDiffInMeanTimeCloneP1->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP2);
 CCUDiffInMeanTimeCloneP2->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP2->SetMaximum(5);
 CCUDiffInMeanTimeCloneP2->SetTitle("CCU Mean Time Shift EB+3 [ns]");
 CCUDiffInMeanTimeCloneP2->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP3);
 CCUDiffInMeanTimeCloneP3->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP3->SetMaximum(5);
 CCUDiffInMeanTimeCloneP3->SetTitle("CCU Mean Time Shift EB+4 [ns]");
 CCUDiffInMeanTimeCloneP3->Draw("colztext");

moveBinsTProfile2D(CCUDiffInMeanTimeCloneP4);
 CCUDiffInMeanTimeCloneP4->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP4->SetMaximum(5);
 CCUDiffInMeanTimeCloneP4->SetTitle("CCU Mean Time Shift EB+5 [ns]");
 CCUDiffInMeanTimeCloneP4->Draw("colztext");


moveBinsTProfile2D(CCUDiffInMeanTimeCloneP5);
 CCUDiffInMeanTimeCloneP5->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP5->SetMaximum(5);
 CCUDiffInMeanTimeCloneP5->SetTitle("CCU Mean Time Shift EB+6 [ns]");
 CCUDiffInMeanTimeCloneP5->Draw("colztext");
 
 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP6);
 CCUDiffInMeanTimeCloneP6->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP6->SetMaximum(5);
 CCUDiffInMeanTimeCloneP6->SetTitle("CCU Mean Time Shift EB+7 [ns]");
 CCUDiffInMeanTimeCloneP6->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP7);
 CCUDiffInMeanTimeCloneP7->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP7->SetMaximum(5);
 CCUDiffInMeanTimeCloneP7->SetTitle("CCU Mean Time Shift EB+8 [ns]");
 CCUDiffInMeanTimeCloneP7->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP8);
 CCUDiffInMeanTimeCloneP8->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP8->SetMaximum(5);
 CCUDiffInMeanTimeCloneP8->SetTitle("CCU Mean Time Shift EB+9 [ns]");
 CCUDiffInMeanTimeCloneP8->Draw("colztext");


  moveBinsTProfile2D(CCUDiffInMeanTimeCloneP9);
 CCUDiffInMeanTimeCloneP9->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP9->SetMaximum(5);
 CCUDiffInMeanTimeCloneP9->SetTitle("CCU Mean Time Shift EB+10 [ns]");
 CCUDiffInMeanTimeCloneP9->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP10);
 CCUDiffInMeanTimeCloneP10->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP10->SetMaximum(5);
 CCUDiffInMeanTimeCloneP10->SetTitle("CCU Mean Time Shift EB+11 [ns]");
 CCUDiffInMeanTimeCloneP10->Draw("colztext");

  moveBinsTProfile2D(CCUDiffInMeanTimeCloneP11);
 CCUDiffInMeanTimeCloneP11->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP11->SetMaximum(5);
 CCUDiffInMeanTimeCloneP11->SetTitle("CCU Mean Time Shift EB+12 [ns]");
 CCUDiffInMeanTimeCloneP11->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP12);
 CCUDiffInMeanTimeCloneP12->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP12->SetMaximum(5);
 CCUDiffInMeanTimeCloneP12->SetTitle("CCU Mean Time Shift EB+13 [ns]");
 CCUDiffInMeanTimeCloneP12->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP13);
 CCUDiffInMeanTimeCloneP13->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP13->SetMaximum(5);
 CCUDiffInMeanTimeCloneP13->SetTitle("CCU Mean Time Shift EB+14 [ns]");
 CCUDiffInMeanTimeCloneP13->Draw("colztext");
 
 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP14);
 CCUDiffInMeanTimeCloneP14->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP14->SetMaximum(5);
 CCUDiffInMeanTimeCloneP14->SetTitle("CCU Mean Time Shift EB+15 [ns]");
 CCUDiffInMeanTimeCloneP14->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP15);
 CCUDiffInMeanTimeCloneP15->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP15->SetMaximum(5);
 CCUDiffInMeanTimeCloneP15->SetTitle("CCU Mean Time Shift EB+16 [ns]");
 CCUDiffInMeanTimeCloneP15->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP16);
 CCUDiffInMeanTimeCloneP16->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP16->SetMaximum(5);
 CCUDiffInMeanTimeCloneP16->SetTitle("CCU Mean Time Shift EB+17 [ns]");
 CCUDiffInMeanTimeCloneP16->Draw("colztext");

 moveBinsTProfile2D(CCUDiffInMeanTimeCloneP17);
 CCUDiffInMeanTimeCloneP17->SetMinimum(-5);
 CCUDiffInMeanTimeCloneP17->SetMaximum(5);
 CCUDiffInMeanTimeCloneP17->SetTitle("CCU Mean Time Shift EB+18 [ns]");
 CCUDiffInMeanTimeCloneP17->Draw("colztext");

 // ALL EB/EE

   moveBinsTProfile2D(EBMeanTimeFDiffClone);
   EBMeanTimeFDiffClone->SetMinimum(-5);
   EBMeanTimeFDiffClone->SetMaximum(5);
   EBMeanTimeFDiffClone->SetTitle("Crystal Time Shift EB[ns]");
   EBMeanTimeFDiffClone->Draw("colztext");
 

  moveBinsTProfile2D(EEPMeanTimeFDiffClone);
   EEPMeanTimeFDiffClone->SetMinimum(-5);
   EEPMeanTimeFDiffClone->SetMaximum(5);
   EEPMeanTimeFDiffClone->SetTitle("Crystal Time Shift EE+[ns]");
   EEPMeanTimeFDiffClone->Draw("colztext");

   moveBinsTProfile2D(EEMMeanTimeFDiffClone);
   EEMMeanTimeFDiffClone->SetMinimum(-5);
   EEMMeanTimeFDiffClone->SetMaximum(5);
   EEMMeanTimeFDiffClone->SetTitle("Crystal Time Shift EE-[ns]");
   EEMMeanTimeFDiffClone->Draw("colztext");
 
   
 // // Now Draw Hists
//  TCanvas* EBCanvasA = new TCanvas("EBCanvasA","EBCanvasA");
//  EBCanvasA->cd();CCUMeanTimeRunA1->Draw("colz");
//  TCanvas* EBCanvasB = new TCanvas("EBCanvasB","EBCanvasB");
//  EBCanvasB->cd(); CCUMeanTimeRunB1->Draw("colz");
//  TCanvas* EBDiffCanvas1 = new TCanvas("EBDiffCanvas1","EBDiffCanvas1");
//  EBDiffCanvas1->cd(); CCUDiffInMeanTimeClone1->SetTitle("CCU Mean Time Shift EB+17 [ns]"); CCUDiffInMeanTimeClone1->Draw("colztext");

//   TCanvas* EBDiffCanvas2 = new TCanvas("EBDiffCanvas2","EBDiffCanvas2");
//   EBDiffCanvas2->cd(); CCUDiffInMeanTimeClone2->SetTitle("CCU Mean Time Shift EB+16 [ns]"); CCUDiffInMeanTimeClone2->Draw("colztext");

//    TCanvas* EBDiffCanvas3 = new TCanvas("EBDiffCanvas3","EBDiffCanvas3");
//    EBDiffCanvas3->cd(); CCUDiffInMeanTimeClone3->SetTitle("CCU Mean Time Shift EB+15 [ns]"); CCUDiffInMeanTimeClone3->Draw("colztext");

//  TCanvas* EBDiffCanvas4 = new TCanvas("EBDiffCanvas4","EBDiffCanvas4");
//  EBDiffCanvas4->cd(); CCUDiffInMeanTimeClone4->SetTitle("CCU Mean Time Shift EB+14 [ns]"); CCUDiffInMeanTimeClone4->Draw("colztext");


//   TCanvas* EBDiffCanvas5 = new TCanvas("EBDiffCanvas5","EBDiffCanvas5");
//  EBDiffCanvas5->cd(); CCUDiffInMeanTimeClone5->SetTitle("CCU Mean Time Shift EB+13 [ns]"); CCUDiffInMeanTimeClone5->Draw("colztext");



 // TCanvas* EBTimeShift = new TCanvas("EBTimeShift","EBTimingShift");
//  EBTimeShift->cd();   XtalMeanTimeShiftEB->Draw("colz");



 
//Write Histograms
 
 CCU_Mean_Time_Diff = new TFile("CCUTimeShiftFromLaser.root", "RECREATE");

 CCU_Mean_Time_Diff->cd();

 //EB minus
 CCUDiffInMeanTimeClone1->Write();
 CCUDiffInMeanTimeClone2->Write();
 CCUDiffInMeanTimeClone3->Write();
 CCUDiffInMeanTimeClone4->Write();
 CCUDiffInMeanTimeClone5->Write();
 CCUDiffInMeanTimeClone6->Write();
 CCUDiffInMeanTimeClone7->Write();
 CCUDiffInMeanTimeClone8->Write();
 CCUDiffInMeanTimeClone9->Write();
 CCUDiffInMeanTimeClone10->Write();
 CCUDiffInMeanTimeClone11->Write();
 CCUDiffInMeanTimeClone12->Write();
 CCUDiffInMeanTimeClone13->Write();
 CCUDiffInMeanTimeClone14->Write();
 CCUDiffInMeanTimeClone15->Write();
 CCUDiffInMeanTimeClone16->Write();
 CCUDiffInMeanTimeClone17->Write();
 CCUDiffInMeanTimeClone18->Write();

 //EB Plus
  CCUDiffInMeanTimeCloneP0->Write();
 CCUDiffInMeanTimeCloneP1->Write();
 CCUDiffInMeanTimeCloneP2->Write();
 CCUDiffInMeanTimeCloneP3->Write();
 CCUDiffInMeanTimeCloneP4->Write();
 CCUDiffInMeanTimeCloneP5->Write();
 CCUDiffInMeanTimeCloneP6->Write();
 CCUDiffInMeanTimeCloneP7->Write();
 CCUDiffInMeanTimeCloneP8->Write();
 CCUDiffInMeanTimeCloneP9->Write();
 CCUDiffInMeanTimeCloneP10->Write();
 CCUDiffInMeanTimeCloneP11->Write();
 CCUDiffInMeanTimeCloneP12->Write();
 CCUDiffInMeanTimeCloneP13->Write();
 CCUDiffInMeanTimeCloneP14->Write();
 CCUDiffInMeanTimeCloneP15->Write();
 CCUDiffInMeanTimeCloneP16->Write();
 CCUDiffInMeanTimeCloneP17->Write();
 
 // ALL EB/EE

 EBMeanTimeFDiffClone->Write();
 EEMMeanTimeFDiffClone->Write();
 EEPMeanTimeFDiffClone->Write();
 

 CCU_Mean_Time_Diff->Close();
 
}
