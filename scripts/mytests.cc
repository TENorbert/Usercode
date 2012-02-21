#include "DataFormats/EcalDetId/interface/EcalScDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DQM/EcalCommon/interface/Numbers.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void GetCCUIdandTimingShiftFromHist(const TProfile2D* myprof,const int iz)
{
  int nxbins = myprof->GetNbinsX();
  int nybins = myprof->GetNbinsY();

  ofstream CCUideb, CCUideep, CCUideem;

  CCUideb.open("CCUId_In_EB_And_TimeShift.txt",fstream::in | fstream::out);

  CCUideep.open("CCUId_In_EEPlus_And_TimeShift.txt",fstream::in | fstream::out);

  CCUideem.open("CCUId_In_EEMinus_And_TimeShift.txt",fstream::in | fstream::out);
  

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
  EcalTrigTowerDetId ttid;
  
  //EE 
  EcalScDetId CCUIdP;
  EcalScDetId CCUIdM;
  
  //  EcalScDetId CCUIdEEM = 0;


  if (iz = 0)
	{

 for( int ny =0; ny <= nybins; ny++)
	{
	  for(int nx = 0; nx <= nxbins; nx++)
		{
		  // Get IZ from ix,iy here!
		  //int const iz = 1;
		  
				  if( EcalTrigTowerDetId::validDetId(nx,ny,iz))
					{ 
					  ttid(iz,EcalBarel,nx,ny); 
					}
				 
			 
			 CCUIdVecEB.push_back(ttId);
			 CCUIdTimeEB.push_back(myprof->GetBinContent(nx,ny););
		
		}			 
			
		
	}

	  
	}else if {iz < 0)
	  {

	   for( int ny =0; ny <= nybins; ny++)
    	{
	     for(int nx = 0; nx <= nxbins; nx++)
	     	{
		  // Get IZ from ix,iy here!
		  //int const iz = 1;
		  
				  if( EcalScDetId::validDetId(nx,ny,iz))
					{ 
					  CCUIdM(nx,ny,iz); 
					}
				 
			 
			 CCUIdVecEEM.push_back(CCUIdM);
			 CCUIdTimeEEM.push_back(myprof->GetBinContent(nx,ny););
		
		}			 
			
		
	}

	   
	}else if(iz>0)
	   {
  
  //  Loop over XYbins
        for( int ny =0; ny <= nybins; ny++)
	       {
	        for(int nx = 0; nx <= nxbins; nx++)
	        	{
		  // Get IZ from ix,iy here!
		  //int const iz = 1;
		  
				  if( EcalScDetId::validDetId(nx,ny,iz))
					{ 
					  CCUIdP(nx,ny,iz); 
					}
				 
			 
			 CCUIdVecEEP.push_back(CCUIdP);
			 CCUIdTimeEEP.push_back(myprof->GetBinContent(nx,ny););
		
	        	}			 
				
	      }
	   } // end of EE Plus


  if(CCUideb.is_open()){ cout << "CCUIdEB File is open write in it" <<endl;}
  if(CCUideep.is_open()){ cout << "CCUIdEEP File is open, write" << endl;}
  if(CCUideem.is_open()){cout << " CCUIdEEM File is open, write" << endl;}


  // write EB CCUs
  if(CCUIdVecEB.size()==CCUIdTimeEB.size())
	{
	  for( int ii = 0; ii < CCUIdVecEB.size(); ii++)
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
	  for( int ii = 0; ii < CCUIdVecEEM.size(); ii++)
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
