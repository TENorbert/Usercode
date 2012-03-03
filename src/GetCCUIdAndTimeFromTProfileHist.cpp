// File Graps CCUId and its corresponding Time shift from TProfile2D.@la TEN


// Gets CCUId and TimingSHift from TProfile2D hist.


#include "DataFormats/EcalDetId/interface/EcalScDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DQM/EcalCommon/interface/Numbers.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "TProfile2D.h"

#include "CalibCalorimetry/EcalTiming/bin/GetCCUIdAndTimeFromTProfileHist.h"
using namespace std;

//fxn def
// Give TProfile2D and EB or EEP or EEM

// struct GetCCUIdAndTimeFromTProfileHist
// {
// public:
//   void GetCCUIdandTimeShift(TProfile2D *myprof, int iz);
// };

void GetCCUIdAndTimeFromTProfileHist::GetCCUIdandTimeShift( TProfile2D* myprof,  int iz)
{
  //Get number bins in XY
  int nxbins = myprof->GetNbinsX();
  int nybins = myprof->GetNbinsY();

  ofstream CCUIdeb, CCUIdeep, CCUIdeem;

  CCUIdeb.open("CCUId_In_EB_And_TimeShift.txt",fstream::in | fstream::out);

  CCUIdeep.open("CCUId_In_EEPlus_And_TimeShift.txt",fstream::in | fstream::out);

  CCUIdeem.open("CCUId_In_EEMinus_And_TimeShift.txt",fstream::in | fstream::out);
  

  //EB    In EB CCU == Trigger Tower
  std::vector<EcalTrigTowerDetId> CCUIdVecEB;
  std::vector<float> CCUIdTimeEB;

  // EE Plus  // CCU seen as SuperCrystal in EE..Not as Trigger Tower As Normally done!
  std::vector<EcalScDetId> CCUIdVecEEP;
  std::vector<float> CCUIdTimeEEP;
  //EE Minus
  std::vector<EcalScDetId> CCUIdVecEEM;
  std::vector<float> CCUIdTimeEEM;
  

  //EB
  //  EcalTrigTowerDetId ttId;
  EBDetId ebdetId;
  
  
  //EE
  EEDetId eedetIdm;
  EEDetId eedetIdp;  
  //EE SC
  EcalScDetId CCUIdM;
  EcalScDetId CCUIdP;
  

  // Read CCU Id and Timeshift into file 
  if (iz == 0) 
	{

	  for( int ny =0; ny <= nybins; ny++)
		{
		  for(int nx = 0; nx <= nxbins; nx++)
			{
			  int bin = myprof->GetBin(ny,nx);

 			  int nentries = myprof->GetBinEntries(bin);

			  int tshift = 0; // initialise the time to zero

			  // Set timing shift for CCUs with no entries == 0
			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};

			  // Hopefully these are Phi and eta Values
			  int ieta = myprof->GetBinLowEdge(nx);
			  int iphi = myprof->GetBinLowEdge(ny);

		
			  // if(EcalTrigTowerDetId::validDetId(iz,eb,nx,ny))
			  
			  //  ttId = EcalTrigTowerDetId(iz,eb,nx,ny);
			  //	  EcalTrigTowerDetId ttId(0,1,ieta,iphi,0);  //subdet ==1 and mode ==0 for EcalBarel

			  // Create DetId
			  EBDetId ebdetId(ieta,iphi);
			  // Use DetId to Get Electronics ID
			  const EcalElectronicsId eid = Numbers::map->getElectronicsId(ebdetId);
			  // From electronics Id Get CCUId
			  int  CCUId = eid.towerId();

// 			  // Make TT Id
// 			  EcalTrigTowerDetId ttId(CCUId);

// 			  //Get SM from TTId
// 			  unsigned iSM = Numbers::SM(ttId)


				//Check if ebdetId is valid. But I really have to check if CCUId is Valid though. sighhhh!
				if(ebdetId.valid(ieta,iphi))
				  {				 
					//			  if(ttId.validDetId(0,1,ieta,iphi))
					//				{
					//					CCUIdVecEB.push_back(ttId);
					CCUIdVecEB.push_back(CCUId);	
					CCUIdTimeEB.push_back(tshift);
				  }
			}			 
		  
		  
		}
	  
	  
	}else if (iz == -1)
	{
	  
	  for( int ny =0; ny <= nybins; ny++)
    	{
		  for(int nx = 0; nx <= nxbins; nx++)
	     	{
			  
			  int bin = myprof->GetBin(ny,nx);
			  
			  int nentries = myprof->GetBinEntries(bin);

			  int tshift = 0; // initialise the time to zero

			  // Set timing shift for CCUs with no entries == 0
			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};
			  int ix = myprof->GetBinLowEdge(nx);
			  int iy = myprof->GetBinLowEdge(ny);

			  // Make EEDetID
			  EEDetId eedetIdm(ix,iy);
			   // if(EcalScDetId::validDetId(nx,ny,iz))
			   // CCUIdM = EcalScDetId(nx,ee,ny,iz);
			  
			  // Get Super Cryst Id
			  EcalScDetId CCUIdM = Numbers::getEcalScDetId(eedetIdm );
			  
			  //Get SM Id
			  unsigned eeSM =  Numbers::iSM(CCUIdM);
			  
			  // Now check if SC Id is valid
			  if(Numbers::validEESc(eeSM,ix, iy))
				{
				  //	   EcalScDetId	 CCUIdM(ieta,iphi,iz); 
				  //			   if(CCUIdM.validDetId(ieta,iphi,iz))
				  //				 {
				  CCUIdVecEEM.push_back(CCUIdM);
				  CCUIdTimeEEM.push_back(tshift);
				  
				}			 
			}
		 
		}
	   
	   
	}else if(iz == 1)
	{
  
	  //  Loop over XYbins
	  for( int ny =0; ny <= nybins; ny++)
		{
		  for(int nx = 0; nx <= nxbins; nx++)
			{
			  int bin = myprof->GetBin(ny,nx);
			  //float timeshift = myprof->GetBinContent(bin);

			  
			  int nentries = myprof->GetBinEntries(bin);

			  int tshift = 0; // initialise the time to zero

			  // Set timing shift for CCUs with no entries == 0
			  if( nentries == 0){ tshift = 0;} else { tshift = myprof->GetBinContent(bin);};
			  int ix = myprof->GetBinLowEdge(nx);
			  int iy = myprof->GetBinLowEdge(ny);

			  	  // Make EEDetID
			  EEDetId eedetIdp(ix,iy);
			   // if(EcalScDetId::validDetId(nx,ny,iz))
			   // CCUIdM = EcalScDetId(nx,ee,ny,iz);
			  
			  // Get Super Cryst Id
			  EcalScDetId CCUIdP = Numbers::getEcalScDetId(eedetIdp);
			  
			  //Get SM Id
			  unsigned eeSM =  Numbers::iSM(CCUIdP);
			  
			  // Now check if SC Id is valid
			  if(Numbers::validEESc( eeSM,ix,iy))
				{
		
				  CCUIdVecEEP.push_back(CCUIdP);
				  CCUIdTimeEEP.push_back(tshift); // fill CCU Timing shift.
				}
			}			 
		  
		}
	} // end of EE Plus
  

  if(CCUIdeb.is_open()){ cout << "CCUIdEB File is open write in it" <<endl;}
  if(CCUIdeep.is_open()){ cout << "CCUIdEEP File is open, write" << endl;}
  if(CCUIdeem.is_open()){cout << " CCUIdEEM File is open, write" << endl;}


  // write EB CCUs
  if(CCUIdVecEB.size()==CCUIdTimeEB.size())
	{
	  for( int ii = 0; ii <= CCUIdVecEB.size(); ii++)
		{
		  CCUIdeb << CCUIdVecEB[ii] << "Has TimeShiftOf" << CCUIdTimeEB[ii] <<"(ns)"<< "\n";
		}
	}

  //Write EEP CCUs
  
  if(CCUIdVecEEP.size()==CCUIdTimeEEP.size())
	{
	  for( int ii = 0; ii < CCUIdVecEEP.size(); ii++)
		{
		  CCUIdeep << CCUIdVecEEP[ii] << "Has TimeShiftOf" << CCUIdTimeEEP[ii] <<"(ns)"<< "\n";
		}
	}

  //EEMinus
  if(CCUIdVecEEM.size()==CCUIdTimeEEM.size())
	{
	  for( int ii = 0; ii <= CCUIdVecEEM.size(); ii++)
		{
		  CCUIdeem << CCUIdVecEEM[ii] << "Has TimeShiftOf" << CCUIdTimeEEM[ii] <<"(ns)"<< "\n";
		}
	}


  cout << " CLose all files now" << endl;

  CCUIdeb.close();
  CCUIdeep.close();
  CCUIdeem.close();
  return;


}
