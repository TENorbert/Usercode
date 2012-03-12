// auxiliary functions that support AdjustEcalTimingFromLaser

#include "TProfile2D.h"
using namespace std;

////////////&&&&&&&&& Function To Check IF Xtal is in EB or EE &&&&&&&&&&&&&&//////////////////
int isEB(int ifed)
{
    return (ifed >= 610 && ifed <= 645);
}


///*****FxN 2 convert Int to string ********/////////
std::string ConvertIntToString(int num)
{
  //  using name space std;
  std::stringstream mystream;
  mystream  << num;
  return mystream.str();
}
