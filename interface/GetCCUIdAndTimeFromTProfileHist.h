// Header File to Get CCUIdandTimeFromTProfileHist

#ifndef GETCCUIDANDTIMEFROMTPROFILEHISTC_H_
#define GETCCUIDANDTIMEFROMTPROFILEHISTC_H_


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


// fxn prototype

struct GetCCUIdAndTimeFromTProfileHist
{
public:

  void GetCCUIdandTimeShift(TProfile2D* myprof,  int iz);
  
};

#endif //GETCCUIDANFTIMEFROMTPROFILEHISTC_H_
