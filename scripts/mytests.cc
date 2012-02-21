#include "DataFormats/EcalDetId/interface/EcalScDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DQM/EcalCommon/interface/Numbers.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"
#include <vector>





void GetCCUIdandTimingShiftFromHist(const TProfile2D* myprof,const int iz)
{
  int nxbins = myprof->GetNbinsX();
  int nybins = myprof->GetNbinsY();

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
  
  return;
}
