#define suman_rscan_cxx
// The class definition in suman_rscan.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("suman_rscan.C")
// Root > T->Process("suman_rscan.C","some options")
// Root > T->Process("suman_rscan.C+")
//

#include "suman_rscan.h"
#include <TH2.h>
#include <TStyle.h>
//#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"
#include <TProof.h>
#include "TChain.h"
#include <string>

#include <iostream>
#include <fstream>

//#define PU_UP   
//#define PU_DN

using namespace std;  

using namespace std;

const float pival = acos(-1.);

static const int nalgo = 12 ;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
static const int netarange = 10 ;
const char* JetEta[netarange] = {"|eta|<0.5","0.5<|eta|<1.0","1.0<|eta|<1.5","1.5<|eta|<2.0","2.0<|eta|<2.5","2.5<|eta|<3.0","3.0<|eta|<3.2","3.2<|eta|<3.7","3.7<|eta|<4.2","4.2<|eta|<4.7"} ;
double etarng[netarange+1] ={0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.2, 3.7, 4.2, 4.7};

const int noptbins = 62 ;

double ptbins[noptbins+1] = {74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

const int noptbins1 = 68 ;

double ptbins1[noptbins1+1] = {30, 37, 43, 49, 56, 64, 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

 const int npileupmx = 80;
 const double minPFPt = 20.;    

 const int nHLTmx= 10;
 double leadingPtThreshold[nHLTmx+1]= {74, 97, 133, 196, 272, 330, 395, 468, 548, 592, 5000.0};

 const char* jethlt_name[nHLTmx] = {"HLT_AK8PFJet40_v", "HLT_AK8PFJet60_v",
                                 "HLT_AK8PFJet80_v", "HLT_AK8PFJet140_v", "HLT_AK8PFJet200_v",
                                 "HLT_AK8PFJet260_v", "HLT_AK8PFJet320_v",
                                 "HLT_AK8PFJet400_v", "HLT_AK8PFJet450_v", "HLT_AK8PFJet500_v"} ;

double compres[nHLTmx] = {0};

double compres15[nHLTmx] = {133490.64,17310.168,4567.035,868.165,117.545,11.427,5.46,2.466,1.0002,1.0};
double compresB[nHLTmx] = {642980.,72759.1,22884.3,2235.47,223.757,47.8042,16.9884,5.42371,1.,1.} ;
double compresC[nHLTmx] = {576174.,81695.1,25718.3,2569.92,255.795,53.4,19.0319,6.23305,1.,1.};
double compresD[nHLTmx] = {580101.,81285.6,25916.5,2534.28,252.871,55.5829,18.8895,6.22492,1.,1.};
double compresE[nHLTmx] = {641478.,92969.,29772.8,2904.08,307.486,61.3483,20.9706,6.88494,1.,1.};
double compresF[nHLTmx] = {660909.,111157.,40255.3,3670.99,465.406,69.2093,23.2046,7.78581,1.,1.};
double compresG[nHLTmx] = {774248.665,122319.611,40851.372,4168.971,630.5287,73.69957,24.33146,8.2079,1.,1.};
double compresH[nHLTmx] = {726646.691,131051.757,43288.608,4508.252,680.906,77.707,25.935,8.816,1.,1.} ;

double datpileup[nHLTmx][npileupmx] = {{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                      						 ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}                     	
								                  ,{6.54008e-06,2.29383e-05,6.32223e-05,8.55796e-05,0.000122592,0.000164214,0.000191738,0.000353072,0.000965735,0.00215544,0.00484612,0.00986199,0.0165083,0.0240058,0.032166,0.0407818,0.0481844,0.0532395,0.0561219,0.0575573,0.058412,0.0588587,0.0583078,0.056491,0.0537587,0.0504445,0.0466722,0.0425747,0.0383287,0.0340574,0.0298202,0.0256705,0.0216922,0.0179859,0.0146378,0.011698,0.00917774,0.00705846,0.00530639,0.00388441,0.00275715,0.00189012,0.00124723,0.000790064,0.000479456,0.00027833,0.000154405,8.18145e-05,4.14101e-05,2.00435e-05,9.30691e-06,4.17785e-06,1.84606e-06,8.3504e-07,4.1498e-07,2.45829e-07,1.77914e-07,1.48846e-07,1.33924e-07,1.23839e-07,1.1526e-07,1.07079e-07,9.89863e-08,9.09467e-08,8.30145e-08,7.52676e-08,6.77837e-08,6.06312e-08,5.38664e-08,4.75325e-08,4.16595e-08,3.62653e-08,3.1356e-08,2.69281e-08,2.29691e-08,1.94598e-08,1.63753e-08,1.36867e-08,1.13622e-08,9.36881e-09}
                                                                                 };

double  mcpileup[npileupmx] = {2.82595e-05,6.29473e-05,0.000126337,0.000256885,0.000564631,0.00110702,0.00204067,0.0035458,0.00559555,0.0083368,0.011575,0.0154292,0.01967,0.0241571,0.0285471,0.0326206,0.0364776,0.0397328,0.0421873,0.044275,0.0451668,0.0458842,0.045376,0.0445124,0.043152,0.0411647,0.038777,0.0366233,0.033998,0.0314075,0.0287512,0.0262996,0.0239008,0.0215455,0.0195003,0.0176033,0.015793,0.0141663,0.0128473,0.0115051,0.0103265,0.00926773,0.00834596,0.00750304,0.00666546,0.00597047,0.00529105,0.00466223,0.00413244,0.00362811,0.00318285,0.00273657,0.00239027,0.0020306,0.0017336,0.00146106,0.00122478,0.00100438,0.000834986,0.000668676,0.000550739,0.000455454,0.000343681,0.000275465,0.000227473,0.000165593,0.000133594,0.000107893,7.98589e-05,6.69385e-05,5.60126e-05,4.08681e-05,2.92365e-05,2.53712e-05,1.69478e-05,1.57952e-05,1.38265e-05,9.98148e-06,6.90946e-06,6.66382e-06} ; 



void PileUpGenerator(double datapileup[nHLTmx][npileupmx],double *mcpileup,double rat_pileup[nHLTmx][npileupmx])
{
    double dattot[nHLTmx]={0};
    double mctot=0;
    for (int ij=0; ij<npileupmx; ij++) {
      for (int jk=0; jk<nHLTmx; jk++) {
        dattot[jk] +=datpileup[jk][ij];
      }
      mctot +=mcpileup[ij];
    }
    cout<<"datatot "<<dattot[0]<<endl;

    for (int ij=0; ij<npileupmx; ij++) {
      mcpileup[ij] /=max(1.e-6,mctot);
      for (int jk=0; jk<nHLTmx; jk++) {
        datpileup[jk][ij] /=max(1.e-6,dattot[jk]);

        if(jk==0) { cout<<ij<<" ratio "<<rat_pileup[jk][ij]<<endl;}

                }
    }
///prescale///
//
for(int ij=0; ij<nHLTmx; ij++){
       compres[ij] = compresG[ij];
       }
}

int* dec2bin(int dec)
{
const int length = nHLTmx;
int input = dec;
int istep=0;
int div[length] = {0};
while(input>0){
  input = input/2;
  div[istep] = input%2;
  istep++;
 }

static int binary[nHLTmx];
for(int ij=1; ij<(length+1); ij++){
 binary[ij-1] = div[length-ij];
 }
return binary;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

double PhiInRange(const double& phi) {
  double phiout = phi;

  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;

  return phiout;
}

double delta2R(double eta1, double phi1, double eta2, double phi2) {
  return sqrt(pow(eta1 - eta2,2) +pow(PhiInRange(phi1 - phi2),2));
}
  
unsigned ievt;
  
  static const int njetmx =20; 
  
  double Rho ;
    
  int nvert;
  int nchict;
  int npu_vert;

  double event_weight;
  double weight;
  double weighttrg[nHLTmx];
  double tot_weight = 0;

  int ihlt[nHLTmx];

  int trig_value;

  bool isMC = false;
  float pthat;

  int njets[nalgo] ;
  int pfjetmul[nalgo][njetmx] ;
  float pfjetenr[nalgo][njetmx], pfjetmom[nalgo][njetmx], pfjetpT[nalgo][njetmx], pfjetarea[nalgo][njetmx], pfjetthe[nalgo][njetmx], pfjety[nalgo][njetmx], pfjetphi[nalgo][njetmx],  pfjetpTup[nalgo][njetmx], pfjetpTdn[nalgo][njetmx], pfjetJEC[nalgo][njetmx], pfjetJECL1[nalgo][njetmx], pfjetwidth[nalgo][njetmx];
  bool pfjettightID[nalgo][njetmx], pfjetlooseID[nalgo][njetmx] ;
  double trig_weight[nalgo];
 
  int npfjets01;
  int pfjetmul01[njetmx];
  float pfjetenr01[njetmx], pfjetpT01[njetmx], pfjetarea01[njetmx], pfjety01[njetmx], pfjetphi01[njetmx], pfjetpTup01[njetmx], pfjetpTdn01[njetmx], pfjetJEC01[njetmx], pfjetJECL101[njetmx], pfjetwidth01[njetmx];
  bool pfjettightID01[njetmx],  pfjetlooseID01[njetmx]   ;
  double trig_weight01;  

  int npfjets02;
  int pfjetmul02[njetmx];
  float pfjetenr02[njetmx], pfjetpT02[njetmx], pfjetarea02[njetmx], pfjety02[njetmx], pfjetphi02[njetmx], pfjetpTup02[njetmx], pfjetpTdn02[njetmx], pfjetJEC02[njetmx], pfjetJECL102[njetmx], pfjetwidth02[njetmx];
  bool pfjettightID02[njetmx],  pfjetlooseID02[njetmx]   ;
  double trig_weight02;  

  int npfjets03;
  int pfjetmul03[njetmx];
  float pfjetenr03[njetmx], pfjetpT03[njetmx], pfjetarea03[njetmx], pfjety03[njetmx], pfjetphi03[njetmx], pfjetpTup03[njetmx], pfjetpTdn03[njetmx], pfjetJEC03[njetmx], pfjetJECL103[njetmx], pfjetwidth03[njetmx];
  bool pfjettightID03[njetmx],  pfjetlooseID03[njetmx]   ;
  double trig_weight03;

  int npfjets04;
  int pfjetmul04[njetmx];
  float pfjetenr04[njetmx], pfjetpT04[njetmx], pfjetarea04[njetmx], pfjety04[njetmx], pfjetphi04[njetmx], pfjetpTup04[njetmx], pfjetpTdn04[njetmx], pfjetJEC04[njetmx], pfjetJECL104[njetmx], pfjetwidth04[njetmx];
  bool pfjettightID04[njetmx],  pfjetlooseID04[njetmx]   ;
  double trig_weight04;

  int npfjets05;
  int pfjetmul05[njetmx];
  float pfjetenr05[njetmx], pfjetpT05[njetmx], pfjetarea05[njetmx], pfjety05[njetmx], pfjetphi05[njetmx], pfjetpTup05[njetmx], pfjetpTdn05[njetmx], pfjetJEC05[njetmx], pfjetJECL105[njetmx], pfjetwidth05[njetmx];
  bool pfjettightID05[njetmx],  pfjetlooseID05[njetmx]   ;
  double trig_weight05;

  int npfjets06;
  int pfjetmul06[njetmx];
  float pfjetenr06[njetmx], pfjetpT06[njetmx], pfjetarea06[njetmx], pfjety06[njetmx], pfjetphi06[njetmx], pfjetpTup06[njetmx], pfjetpTdn06[njetmx], pfjetJEC06[njetmx], pfjetJECL106[njetmx], pfjetwidth06[njetmx];
  bool pfjettightID06[njetmx],  pfjetlooseID06[njetmx]   ;
  double trig_weight06;

  int npfjets07;
  int pfjetmul07[njetmx];
  float pfjetenr07[njetmx], pfjetpT07[njetmx], pfjetarea07[njetmx], pfjety07[njetmx], pfjetphi07[njetmx], pfjetpTup07[njetmx], pfjetpTdn07[njetmx], pfjetJEC07[njetmx], pfjetJECL107[njetmx], pfjetwidth07[njetmx];
  bool pfjettightID07[njetmx] ,  pfjetlooseID07[njetmx]  ;
  double trig_weight07;

  int npfjets08;
  int pfjetmul08[njetmx];
  float pfjetenr08[njetmx], pfjetpT08[njetmx], pfjetarea08[njetmx], pfjety08[njetmx], pfjetphi08[njetmx], pfjetpTup08[njetmx], pfjetpTdn08[njetmx], pfjetJEC08[njetmx], pfjetJECL108[njetmx], pfjetwidth08[njetmx];
  bool pfjettightID08[njetmx],  pfjetlooseID08[njetmx]   ;
  double trig_weight08;

  int npfjets09;
  int pfjetmul09[njetmx];
  float pfjetenr09[njetmx], pfjetpT09[njetmx], pfjetarea09[njetmx], pfjety09[njetmx], pfjetphi09[njetmx], pfjetpTup09[njetmx], pfjetpTdn09[njetmx], pfjetJEC09[njetmx], pfjetJECL109[njetmx], pfjetwidth09[njetmx];
  bool pfjettightID09[njetmx],  pfjetlooseID09[njetmx] ;
  double trig_weight09;

  int npfjets10;
  int pfjetmul10[njetmx];
  float pfjetenr10[njetmx], pfjetpT10[njetmx], pfjetarea10[njetmx], pfjety10[njetmx], pfjetphi10[njetmx], pfjetpTup10[njetmx], pfjetpTdn10[njetmx], pfjetJEC10[njetmx], pfjetJECL110[njetmx], pfjetwidth10[njetmx];
  bool pfjettightID10[njetmx],  pfjetlooseID10[njetmx]   ;
  double trig_weight10;

  int npfjets11;
  int pfjetmul11[njetmx];
  float pfjetenr11[njetmx], pfjetpT11[njetmx], pfjetarea11[njetmx], pfjety11[njetmx], pfjetphi11[njetmx], pfjetpTup11[njetmx], pfjetpTdn11[njetmx], pfjetJEC11[njetmx], pfjetJECL111[njetmx], pfjetwidth11[njetmx];
  bool pfjettightID11[njetmx],  pfjetlooseID11[njetmx]   ;
  double trig_weight11;

  int npfjets12;
  int pfjetmul12[njetmx];
  float pfjetenr12[njetmx], pfjetpT12[njetmx], pfjetarea12[njetmx], pfjety12[njetmx], pfjetphi12[njetmx], pfjetpTup12[njetmx], pfjetpTdn12[njetmx], pfjetJEC12[njetmx], pfjetJECL112[njetmx], pfjetwidth12[njetmx];
  bool pfjettightID12[njetmx],  pfjetlooseID12[njetmx]   ;
  double trig_weight12;  

  int npfjets13;
  int pfjetmul13[njetmx];
  float pfjetenr13[njetmx], pfjetpT13[njetmx], pfjetarea13[njetmx], pfjety13[njetmx], pfjetphi13[njetmx], pfjetpz13[njetmx], pfjettightID13[njetmx]  ;
  
  int npfjets14;
  int pfjetmul14[njetmx];
  float pfjetenr14[njetmx], pfjetpT14[njetmx], pfjetarea14[njetmx], pfjety14[njetmx], pfjetphi14[njetmx], pfjetpz14[njetmx], pfjettightID14[njetmx]  ;
  
  int npfjets15;
  int pfjetmul15[njetmx];
  float pfjetenr15[njetmx], pfjetpT15[njetmx], pfjetarea15[njetmx], pfjety15[njetmx], pfjetphi15[njetmx], pfjetpz15[njetmx], pfjettightID15[njetmx]  ;

  
  static const int ngenjetmx =20;

  int ngenjets[nalgo] ;
  int genjetmul[nalgo];
  float genjetenr[nalgo][njetmx], genjetmom[nalgo][njetmx], genjetpT[nalgo][njetmx], genjetpz[nalgo][njetmx], genjetarea[nalgo][njetmx], genjetthe[nalgo][njetmx], genjety[nalgo][njetmx], genjetphi[nalgo][njetmx] ;

  int ngenjets01;
  int genjetmul01[njetmx];
  float genjetenr01[njetmx], genjetpT01[njetmx], genjetarea01[njetmx], genjety01[njetmx], genjetphi01[njetmx];

  int ngenjets02;
  int genjetmul02[njetmx];
  float genjetenr02[njetmx], genjetpT02[njetmx], genjetarea02[njetmx], genjety02[njetmx], genjetphi02[njetmx] ;

  int ngenjets03;
  int genjetmul03[njetmx];
  float genjetenr03[njetmx], genjetpT03[njetmx], genjetarea03[njetmx], genjety03[njetmx], genjetphi03[njetmx] ;

  int ngenjets04;
  int genjetmul04[njetmx];
  float genjetenr04[njetmx], genjetpT04[njetmx], genjetarea04[njetmx], genjety04[njetmx], genjetphi04[njetmx] ;

  int ngenjets05;
  int genjetmul05[njetmx];
  float genjetenr05[njetmx], genjetpT05[njetmx], genjetarea05[njetmx], genjety05[njetmx], genjetphi05[njetmx] ;

  int ngenjets06;
  int genjetmul06[njetmx];
  float genjetenr06[njetmx], genjetpT06[njetmx], genjetarea06[njetmx], genjety06[njetmx], genjetphi06[njetmx] ;
 
  int ngenjets07;
  int genjetmul07[njetmx];
  float genjetenr07[njetmx], genjetpT07[njetmx], genjetarea07[njetmx], genjety07[njetmx], genjetphi07[njetmx] ;

  int ngenjets08;
  int genjetmul08[njetmx];
  float genjetenr08[njetmx], genjetpT08[njetmx], genjetarea08[njetmx], genjety08[njetmx], genjetphi08[njetmx] ;

  int ngenjets09;
  int genjetmul09[njetmx];
  float genjetenr09[njetmx], genjetpT09[njetmx], genjetarea09[njetmx], genjety09[njetmx], genjetphi09[njetmx] ;

  int ngenjets10;
  int genjetmul10[njetmx];
  float genjetenr10[njetmx], genjetpT10[njetmx], genjetarea10[njetmx], genjety10[njetmx], genjetphi10[njetmx] ;

  int ngenjets11;
  int genjetmul11[njetmx];
  float genjetenr11[njetmx], genjetpT11[njetmx], genjetarea11[njetmx], genjety11[njetmx], genjetphi11[njetmx] ;
  
  int ngenjets12;
  int genjetmul12[njetmx];
  float genjetenr12[njetmx], genjetpT12[njetmx], genjetarea12[njetmx], genjety12[njetmx], genjetphi12[njetmx] ;
  
  int ngenjets13;
  int genjetmul13[njetmx];
  float genjetenr13[njetmx], genjetpT13[njetmx], genjetarea13[njetmx], genjety13[njetmx], genjetphi13[njetmx] ;
  
  int ngenjets14;
  int genjetmul14[njetmx];
  float genjetenr14[njetmx], genjetpT14[njetmx], genjetarea14[njetmx], genjety14[njetmx], genjetphi14[njetmx] ;
  
  int ngenjets15;
  int genjetmul15[njetmx];
  float genjetenr15[njetmx], genjetpT15[njetmx], genjetarea15[njetmx], genjety15[njetmx], genjetphi15[njetmx];  
  
  float miset , misphi , sumEt;
  
  int iRecoPTbin[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int iGenPTbin[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  double ex_cor[nalgo][netarange][noptbins1] = {{{1.}}};
 
  bool ihlt01, ihlt02, ihlt03, ihlt04, ihlt05, ihlt06, ihlt07, ihlt08, ihlt09, ihlt10;
  
  void fillarray() {
  
  miset = miset;
  misphi = misphi;
  sumEt = sumEt;
  
  nvert = nvert;
  nchict = nchict;
  event_weight = event_weight;
  tot_weight+=event_weight;
  pthat = pthat;
 
  trig_value = trig_value;

  for(int ht=0; ht<nHLTmx; ht++){

   ihlt[ht] = 0;

   switch(ht){

   case 0:
   ihlt[ht] = ihlt01;
   break;

   case 1:
   ihlt[ht] = ihlt02;
   break;

   case 2:
   ihlt[ht] = ihlt03;
   break;

   case 3:
   ihlt[ht] = ihlt04;
   break;

   case 4:
   ihlt[ht] = ihlt05;
   break;

   case 5:
   ihlt[ht] = ihlt06;
   break;

   case 6:
   ihlt[ht] = ihlt07;
   break;

   case 7:
   ihlt[ht] = ihlt08;
   break;

   case 8:
   ihlt[ht] = ihlt09;
   break;

   case 9:
   ihlt[ht] = ihlt10;
   break;

    }

  }
 
  for(int ix=0; ix<nalgo; ix++){
    njets[ix] = 0;
    ngenjets[ix] = 0;
    
    switch(ix){
      
    case 0:
      
       if(pfjettightID01[0]!=1) break;
       if(isMC){
         if(pfjetpT01[0]>(3.*pthat)) break;
        } 
    
      trig_weight[ix] = trig_weight01;

      for(int jet=0; jet<npfjets01; jet++){
	
//	if(pfjettightID01[jet]!=1) continue;
	if(pfjetpT01[jet]<minPFPt) continue ;
	
	pfjetenr[ix][njets[ix]] = pfjetenr01[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT01[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea01[jet] ;
	pfjety[ix][njets[ix]] = pfjety01[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi01[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID01[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID01[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup01[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn01[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC01[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL101[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth01[jet];

	njets[ix]++;
      }
     

      if(isMC){
      for(int gjet=0; gjet<ngenjets01; gjet++){
	
	if(genjetpT01[gjet]<minPFPt) continue ;	
	
	genjetenr[ix][ngenjets[ix]] = genjetenr01[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT01[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea01[gjet];
	genjety[ix][ngenjets[ix]] = genjety01[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi01[gjet];
	
	ngenjets[ix]++;
      }	
     }  
      break;	
      
    case 1:
      
       if(pfjettightID02[0]!=1) break;
       if(isMC){
         if(pfjetpT02[0]>(3.*pthat)) break;
        }      

      trig_weight[ix] = trig_weight02;

      for(int jet=0; jet<npfjets02; jet++){
	
	if(pfjettightID02[jet]!=1) continue;
	if(pfjetpT02[jet]<minPFPt) continue ;
	
	pfjetenr[ix][njets[ix]] = pfjetenr02[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT02[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea02[jet] ;
	pfjety[ix][njets[ix]] = pfjety02[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi02[jet] ;
        pfjettightID[ix][njets[ix]] = pfjettightID02[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID02[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup02[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn02[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC02[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL102[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth02[jet];
	
	njets[ix]++;
      }
     
     if(isMC){
      for(int gjet=0; gjet<ngenjets02; gjet++){
	
	if(genjetpT02[gjet]<minPFPt) continue ;	
	
	genjetenr[ix][ngenjets[ix]] = genjetenr02[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT02[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea02[gjet];
	genjety[ix][ngenjets[ix]] = genjety02[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi02[gjet];
	
	ngenjets[ix]++;
      }
     }      

      break;	
      
      
    case 2:
      
       if(pfjettightID03[0]!=1) break;
       if(isMC){
         if(pfjetpT03[0]>(3.*pthat)) break;
        }      

      trig_weight[ix] = trig_weight03;

      for(int jet=0; jet<npfjets03; jet++){
	
	if(pfjettightID03[jet]!=1) continue;
	if(pfjetpT03[jet]<minPFPt) continue ;
	
	pfjetenr[ix][njets[ix]] = pfjetenr03[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT03[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea03[jet] ;
	pfjety[ix][njets[ix]] = pfjety03[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi03[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID03[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID03[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup03[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn03[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC03[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL103[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth03[jet];
	
	njets[ix]++;
      }
     
      if(isMC){
      for(int gjet=0; gjet<ngenjets03; gjet++){
	
	if(genjetpT03[gjet]<minPFPt) continue ;	
	
	genjetenr[ix][ngenjets[ix]] = genjetenr03[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT03[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea03[gjet];
	genjety[ix][ngenjets[ix]] = genjety03[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi03[gjet];
	
	ngenjets[ix]++;
      }
    }      

      break;	
      
      
    case 3:
      
       if(pfjettightID04[0]!=1) break;
       if(isMC){
         if(pfjetpT04[0]>(3.*pthat)) break;
        }  
    
      trig_weight[ix] = trig_weight04;

      for(int jet=0; jet<npfjets04; jet++){
	
	if(pfjettightID04[jet]!=1) continue;
	if(pfjetpT04[jet]<minPFPt) continue ;
	
	pfjetenr[ix][njets[ix]] = pfjetenr04[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT04[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea04[jet] ;
	pfjety[ix][njets[ix]] = pfjety04[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi04[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID04[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID04[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup04[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn04[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC04[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL104[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth04[jet];
				
	njets[ix]++;
      }
  
     if(isMC){	
      for(int gjet=0; gjet<ngenjets04; gjet++){
						
	if(genjetpT04[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr04[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT04[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea04[gjet];
	genjety[ix][ngenjets[ix]] = genjety04[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi04[gjet];
				 
	ngenjets[ix]++;
      }
    }				
      break;	
		
		    
    case 4:
     
      if(pfjettightID05[0]!=1) break;
      if(isMC){
         if(pfjetpT05[0]>(3.*pthat)) break;
        }  
   
      trig_weight[ix] = trig_weight05;

      for(int jet=0; jet<npfjets05; jet++){
	
	if(pfjettightID05[jet]!=1) continue;
	if(pfjetpT05[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr05[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT05[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea05[jet] ;
	pfjety[ix][njets[ix]] = pfjety05[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi05[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID05[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID05[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup05[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn05[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC05[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL105[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth05[jet];
				
	njets[ix]++;
      }

    if(isMC){				
      for(int gjet=0; gjet<ngenjets05; gjet++){
						
	if(genjetpT05[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr05[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT05[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea05[gjet];
	genjety[ix][ngenjets[ix]] = genjety05[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi05[gjet];
				 
	ngenjets[ix]++;
      }
     }
      break;		
			
		
    case 5:
      
       if(pfjettightID06[0]!=1) break;
       if(isMC){
         if(pfjetpT06[0]>(3.*pthat)) break;
        } 
     
      trig_weight[ix] = trig_weight06;

      for(int jet=0; jet<npfjets06; jet++){
	
	if(pfjettightID06[jet]!=1) continue;
	if(pfjetpT06[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr06[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT06[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea06[jet] ;
	pfjety[ix][njets[ix]] = pfjety06[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi06[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID06[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID06[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup06[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn06[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC06[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL106[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth06[jet];
				
	njets[ix]++;
      }

     if(isMC){	
      for(int gjet=0; gjet<ngenjets06; gjet++){
						
	if(genjetpT06[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr06[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT06[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea06[gjet];
	genjety[ix][ngenjets[ix]] = genjety06[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi06[gjet];
			 
	ngenjets[ix]++;
      }
     }					
      break;	
			
			
    case 6:
    
      if(pfjettightID07[0]!=1) break;
      if(isMC){
         if(pfjetpT07[0]>(3.*pthat)) break;
        }   
    
      trig_weight[ix] = trig_weight07;

      for(int jet=0; jet<npfjets07; jet++){
				
	if(pfjettightID07[jet]!=1) continue;
	if(pfjetpT07[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr07[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT07[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea07[jet] ;
	pfjety[ix][njets[ix]] = pfjety07[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi07[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID07[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID07[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup07[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn07[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC07[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL107[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth07[jet];
				
	njets[ix]++;
      }

    if(isMC){			
      for(int gjet=0; gjet<ngenjets07; gjet++){
						
	if(genjetpT07[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr07[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT07[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea07[gjet];
	genjety[ix][ngenjets[ix]] = genjety07[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi07[gjet];
				 
	ngenjets[ix]++;
      }
     }				
      break;	
			
			
    case 7:
    
     if(pfjettightID08[0]!=1) break;
     if(isMC){
         if(pfjetpT08[0]>(3.*pthat)) break;
        } 

      trig_weight[ix] = trig_weight08;
   
      for(int jet=0; jet<npfjets08; jet++){
				
	if(pfjettightID08[jet]!=1) continue;
	if(pfjetpT08[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr08[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT08[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea08[jet] ;
	pfjety[ix][njets[ix]] = pfjety08[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi08[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID08[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID08[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup08[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn08[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC08[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL108[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth08[jet];
				
	njets[ix]++;
      }

    if(isMC){	
      for(int gjet=0; gjet<ngenjets08; gjet++){
						
	if(genjetpT08[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr08[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT08[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea08[gjet];
	genjety[ix][ngenjets[ix]] = genjety08[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi08[gjet];
				 
	ngenjets[ix]++;
      }
    }
				 
      break;	
			
			
    case 8:
      
       if(pfjettightID09[0]!=1) break;
       if(isMC){
         if(pfjetpT09[0]>(3.*pthat)) break;
        }   

      trig_weight[ix] = trig_weight09;   

      for(int jet=0; jet<npfjets09; jet++){
	
	if(pfjettightID09[jet]!=1) continue;
	if(pfjetpT09[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr09[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT09[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea09[jet] ;
	pfjety[ix][njets[ix]] = pfjety09[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi09[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID09[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID09[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup09[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn09[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC09[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL109[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth09[jet];
				
	njets[ix]++;
      }

    if(isMC){		
      for(int gjet=0; gjet<ngenjets09; gjet++){
						
	if(genjetpT09[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr09[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT09[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea09[gjet];
	genjety[ix][ngenjets[ix]] = genjety09[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi09[gjet];
				 
	ngenjets[ix]++;
      }
     }
      break;	
			
			
    case 9:
     
      if(pfjettightID10[0]!=1) break;
      if(isMC){
         if(pfjetpT10[0]>(3.*pthat)) break;
        }     

      trig_weight[ix] = trig_weight10;

      for(int jet=0; jet<npfjets10; jet++){
	
	if(pfjettightID10[jet]!=1) continue;
	if(pfjetpT10[jet]<minPFPt) continue ;
		
	pfjetenr[ix][njets[ix]] = pfjetenr10[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT10[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea10[jet] ;
	pfjety[ix][njets[ix]] = pfjety10[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi10[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID10[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID10[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup10[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn10[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC10[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL110[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth10[jet];
				
	njets[ix]++;
      }
      
    if(isMC){
      for(int gjet=0; gjet<ngenjets10; gjet++){
						
	if(genjetpT10[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr10[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT10[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea10[gjet];
	genjety[ix][ngenjets[ix]] = genjety10[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi10[gjet];
				 
	ngenjets[ix]++;
      }
     }
      break;				
			
    case 10:
      
      if(pfjettightID11[0]!=1) break;
      if(isMC){
         if(pfjetpT11[0]>(3.*pthat)) break;
        }   
   
      trig_weight[ix] = trig_weight11;

      for(int jet=0; jet<npfjets11; jet++){
				
	if(pfjettightID11[jet]!=1) continue;
	if(pfjetpT11[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr11[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT11[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea11[jet] ;
	pfjety[ix][njets[ix]] = pfjety11[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi11[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID11[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID11[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup11[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn11[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC11[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL111[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth11[jet];
				
	njets[ix]++;
      }

     if(isMC){	
      for(int gjet=0; gjet<ngenjets11; gjet++){	
					
	if(genjetpT11[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr11[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT11[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea11[gjet];
	genjety[ix][ngenjets[ix]] = genjety11[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi11[gjet];
			 
	ngenjets[ix]++;
      }
     }
      break;				
			
    case 11:
      
      if(pfjettightID12[0]!=1) break;
      if(isMC){
        if(pfjetpT12[0]>(3.*pthat)) break;
        }      

      trig_weight[ix] = trig_weight12;

      for(int jet=0; jet<npfjets12; jet++){
				
	
	if(pfjettightID12[jet]!=1) continue;
	if(pfjetpT12[jet]<minPFPt) continue ;
				
	pfjetenr[ix][njets[ix]] = pfjetenr12[jet] ;
	pfjetpT[ix][njets[ix]] =  pfjetpT12[jet];
	pfjetarea[ix][njets[ix]] = pfjetarea12[jet] ;
	pfjety[ix][njets[ix]] = pfjety12[jet];
	pfjetphi[ix][njets[ix]] = pfjetphi12[jet] ;
	pfjettightID[ix][njets[ix]] = pfjettightID12[jet];
	pfjetlooseID[ix][njets[ix]] = pfjetlooseID12[jet];
	pfjetpTup[ix][njets[ix]] = pfjetpTup12[jet] ;
	pfjetpTdn[ix][njets[ix]] = pfjetpTdn12[jet] ;
	pfjetJEC[ix][njets[ix]] = pfjetJEC12[jet];
	pfjetJECL1[ix][njets[ix]] = pfjetJECL112[jet];
	pfjetwidth[ix][njets[ix]] = pfjetwidth12[jet];
				
	njets[ix]++;
      }

     if(isMC){				
      for(int gjet=0; gjet<ngenjets12; gjet++){
					
	if(genjetpT12[gjet]<minPFPt) continue ;	
					
	genjetenr[ix][ngenjets[ix]] = genjetenr12[gjet];
	genjetpT[ix][ngenjets[ix]] = genjetpT12[gjet];
	genjetarea[ix][ngenjets[ix]] = genjetarea12[gjet];
	genjety[ix][ngenjets[ix]] = genjety12[gjet];;
	genjetphi[ix][ngenjets[ix]] = genjetphi12[gjet];
				 
	ngenjets[ix]++;
      }
     }
      break;	
			
    }//switch(ix)
  }//ix  
}//fillarray


void suman_rscan::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

int nevent_total = 0;


}

void suman_rscan::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

 // TString option = GetOption();
 

  char name[100];
  char title[100];

  hist_pfmet = new TH1F("MET_Value","MET Value",1000,0.0,2000.0) ; 
  hist_SumEt = new TH1F("Sum_Et","Sum_Et",3500,0,3500.);
  hist_METbyET = new TH1F("METbyEt","MET Value by pT Sum",100,0.0,1.0) ; 
  hist_PV_all = new TH1F("nprimall_rewt_trigset","All PV",60, -0.5, 59.5);
  hist_PV_sel = new TH1F("nprimsel_rewt_trigset","Selected PV",60, -0.5, 59.5);
  hist_PU     = new TH1F("pu_vertices","# of PU Vertices",80,-0.5,79.5);

  PU_vs_PV_all = new TH2F("pileup_vs_nprimall","PU vs PV all",80,-0.5,79.5,80,-0.5,79.5);
  PU_vs_PV_sel = new TH2F("pileup_vs_nprimsel","PU vs PV sel",80,-0.5,79.5,80,-0.5,79.5);
  PU_vs_PV_sel_rewt = new TH2F("pileup_vs_nprimsel_reweighted","PU vs PV sel Weighted",80,-0.5,79.5,80,-0.5,79.5);



  for(int ij=0;ij<nalgo;ij++){
    for (int jk=0;jk<netarange;jk++){	
	
      sprintf(name,"NJets_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"NJets for %s %s",JetRad[ij],JetEta[jk]);

      NJets[ij][jk] = new TH1F(name,title,20,0,20);
      NJets[ij][jk]->Sumw2();

      sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s",JetRad[ij],JetEta[jk]);
      
      JetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT[ij][jk]->Sumw2();
      
      sprintf(name,"JetpT_%s_EtaBin%i_JER_up",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s JER Up",JetRad[ij],JetEta[jk]);
      
      JetpT_up[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT_up[ij][jk]->Sumw2();
      
      sprintf(name,"JetpT_%s_EtaBin%i_JER_dn",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s JER Down",JetRad[ij],JetEta[jk]);
      
      JetpT_dn[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT_dn[ij][jk]->Sumw2();
      
      sprintf(name,"Leading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Leading JetpT for %s %s" ,JetRad[ij],JetEta[jk]);
      
      LeadJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      LeadJetpT[ij][jk]->Sumw2();
      
      sprintf(name,"DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
      DiJet_Mass[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      DiJet_Mass[ij][jk]->Sumw2();

      sprintf(name,"NGenJets_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"NJets %s EtaBin %i",JetRad[ij],jk+1) ;
      
      sprintf(name,"Jet_Width_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Jet Width for %s %s",JetRad[ij],JetEta[jk]);

      JetWidth[ij][jk] = new TH1F(name,title,100,0,2.);
      JetWidth[ij][jk]->Sumw2();

      sprintf(name,"JetPt_vs_JEC_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt vs JEC %s EtaBin%i",JetRad[ij],jk+1);
      JetPt_vs_JEC[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JEC[ij][jk]->Sumw2();

      sprintf(name,"JetPt_vs_JECL1_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt vs JEC L1 %s EtaBin%i",JetRad[ij],jk+1);
      JetPt_vs_JECL1[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JECL1[ij][jk]->Sumw2();

      sprintf(name,"Measured_Cov_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Measured Cov %s EtaBin%i",JetRad[ij],jk+1);
      Mes_Cov[ij][jk] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      Mes_Cov[ij][jk]->Sumw2();

      for(int hl=0 ; hl<nHLTmx; hl++){
      sprintf(name,"JetpT_%s_EtaBin%i_HLT%i",JetRad[ij],jk+1,hl+1);
      sprintf(title,"JetpT for %s %s %s",JetRad[ij],JetEta[jk],jethlt_name[hl]);
      Prescale_JetpT[ij][jk][hl] = new TH1F(name,title,noptbins,ptbins);
      Prescale_JetpT[ij][jk][hl]->Sumw2();
      }

     if(isMC){

      NGenJets[ij][jk] = new TH1F(name,title,20,0,20);
      NGenJets[ij][jk]->Sumw2();
      
      sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCJetpT[ij][jk]->Sumw2();
			
      sprintf(name,"Gen_MC_JetpT_Pow_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Gen MC Jet pT Pow %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCJetpT_pow[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCJetpT_pow[ij][jk]->Sumw2();
      
      sprintf(name,"Leading_Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Leading Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCLeadJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCLeadJetpT[ij][jk]->Sumw2();
			
      sprintf(name,"Gen_DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Gen_DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
      Gen_DiJet_Mass[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      Gen_DiJet_Mass[ij][jk]->Sumw2();
			
      sprintf(name,"LeadJetRaio_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Leading Jet Pt Ratio for %s EtaBin%i",JetRad[ij],jk+1);

      LeadJetRatio[ij][jk] = new TH1F(name,title,500,-0.01,5.);
      LeadJetRatio[ij][jk]->Sumw2();
	 
      sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"RecoJetvsGenJet %s EtaBin%i",JetRad[ij],jk+1);
      RecoVsGenJetpT[ij][jk] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      RecoVsGenJetpT[ij][jk]->Sumw2();
	
      RecoVsGenJetpT[ij][jk]->GetXaxis()->SetTitle("RECO Jet pT (in GeV)");
      RecoVsGenJetpT[ij][jk]->GetYaxis()->SetTitle("Gen Jet pT (in GeV)") ;
	
      sprintf(name,"RecoJetvsGenJet_Number_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"RecoJetvsGenJet Number %s EtaBin%i",JetRad[ij],jk+1);
      RecoVsGenJetNo[ij][jk] = new TH2F(name,title,njetmx,-0.5,19.5,njetmx,-0.5,19.5);
      RecoVsGenJetNo[ij][jk]->Sumw2();
	
      sprintf(name,"Pt_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt Ratio %s EtaBin%i",JetRad[ij],jk+1);
      Pt_Ratio[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      Pt_Ratio[ij][jk]->Sumw2();
	
      sprintf(name,"Pt_Ratio_nomatch_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt Ratio nomatch %s EtaBin%i",JetRad[ij],jk+1);
      Pt_Ratio_nomatch[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      Pt_Ratio_nomatch[ij][jk]->Sumw2();
      
      for(int kl=0; kl<noptbins; kl++){
			
	sprintf(name,"Resolution_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"Resolution %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	Resolution[ij][jk][kl] = new TH1F(name,title,200,-2.0,2.0);
	Resolution[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen[ij][jk][kl] = new TH1F(name,title,360,0,3.6);
	DeltaR_RecoGen[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_Matrix_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR Matrix %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen_mat[ij][jk][kl] = new TH1F(name,title,360,0,3.6);
	DeltaR_RecoGen_mat[ij][jk][kl]->Sumw2();
      }//kl
     }//isMC
    }//jk
	
	
    sprintf(name,"Jety_%s",JetRad[ij]);
    sprintf(title,"Jet Rapidity for %s",JetRad[ij]);
    
    Jeteta[ij] = new TH1F(name,title,200,-5.0,5.0);
    Jeteta[ij]->Sumw2();
    
    sprintf(name,"Leading_Jety_%s",JetRad[ij]);
    sprintf(title,"Leading Jet Rapidity for %s",JetRad[ij]);
    
    LeadJeteta[ij] = new TH1F(name,title,100,-5.0,5.0);
    LeadJeteta[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaR_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaR for %s",JetRad[ij]);
    
    Leading2JetsDeltaR[ij] = new TH1F(name,title,100,0,8.0);
    Leading2JetsDeltaR[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaPhi_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaPhi for %s",JetRad[ij]);
    
    Leading2JetsDeltaPhi[ij] = new TH1F(name,title,75,0,2*pival);
    Leading2JetsDeltaPhi[ij]->Sumw2();
	
    if(isMC){
      
      sprintf(name,"GenJety_%s",JetRad[ij]);
      sprintf(title,"GenJet Rapidity for %s",JetRad[ij]);
      
      GenJeteta[ij] = new TH1F(name,title,200,-5.0,5.0);
      GenJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading_GenJety_%s",JetRad[ij]);
      sprintf(title,"Leading GenJet Rapidity for %s",JetRad[ij]);
      
      GenLeadJeteta[ij] = new TH1F(name,title,100,-5.0,5.0);
      GenLeadJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaR_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaR for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaR[ij] = new TH1F(name,title,100,0,8.0);
      GenLeading2JetsDeltaR[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaPhi_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaPhi for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaPhi[ij] = new TH1F(name,title,75,0,2*pival);
      GenLeading2JetsDeltaPhi[ij]->Sumw2();
      
      sprintf(name,"Response_y_%s", JetRad[ij]);
      sprintf(title,"Response Matrix in y for %s Jets",JetRad[ij]);
	  
      Response_y[ij] = new TH2F(name,title,netarange,etarng,netarange,etarng);
      Response_y[ij]->Sumw2();
	  
      sprintf(name,"Resolution_y_%s", JetRad[ij]);
      sprintf(title,"Resolution in y for %s Jets",JetRad[ij]);
	  
      y_Reso[ij] = new TH1F(name,title,100,-10.,10.);
      y_Reso[ij]->Sumw2();
	  
      sprintf(name,"Resolution_phi_%s", JetRad[ij]);
      sprintf(title,"Resolution in phi for %s Jets",JetRad[ij]);
	  
      phi_Reso[ij] = new TH1F(name,title,100,-pival,pival);
      phi_Reso[ij]->Sumw2();
      
      sprintf(name,"Pthat_vs_LeadingJet_Pt_%s",JetRad[ij]);
      sprintf(title,"Pthat vs LeadingJet Pt %s",JetRad[ij]);
      
      Pthat_vs_LeadPt[ij] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      Pthat_vs_LeadPt[ij]->Sumw2();
    }
  }//ij

PileUpGenerator(datpileup,mcpileup,rat_pileup);
}

Bool_t suman_rscan::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either suman_rscan::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fillarray();
       
     weight = 0; //event_weight;
//     weight*=rat_pileup[0][npu_vert];
 
     for (int ij=0; ij<nHLTmx; ij++) {
          weighttrg[ij] = 1.0;
           weighttrg[ij] *=compres[ij];
     }

     int ihlttrg[nHLTmx+1]= {0,0,0,0,0,0,0,0,0,0,0};

     if(trig_value>1){
//     ihlttrg[nHLTmx-int(log2(trig_value))] = 1;
     ihlttrg[nHLTmx] = 1;
//     cout<<"trig_value "<<trig_value<<endl;
     for (int ij=0; ij<nHLTmx; ij++) {
     ihlttrg[ij] = *(dec2bin(trig_value)+ij);
      }
     }      

   if(ihlttrg[nHLTmx] ==0) continue;

    if(getbinid(pfjetpT[7][0],nHLTmx, leadingPtThreshold)>=0){
    weight = weighttrg[getbinid(pfjetpT[7][0],nHLTmx, leadingPtThreshold)];
    }
    else {continue;}

     hist_pfmet->Fill(miset,weight);
     hist_SumEt->Fill(sumEt,weight);
     hist_METbyET->Fill(miset*1./sumEt,weight);

     if(miset*1./sumEt > 0.3) continue;
            
     hist_PV_all->Fill(nvert,weight);     
     hist_PV_sel->Fill(nchict,weight);   
     hist_PU->Fill(npu_vert,weight); 
       
     PU_vs_PV_all->Fill(npu_vert,nvert);
     PU_vs_PV_sel->Fill(npu_vert,nchict);
     PU_vs_PV_sel_rewt->Fill(npu_vert,nchict,weight);
              
     for(int ix=0; ix<nalgo; ix++){
		
       iRecoPTbin[ix] = -1;
       iGenPTbin[ix] = -1;
		
       int njet_count[netarange] = {0};

	int bincount[netarange][noptbins] = {0};
	int bincount2d[netarange][noptbins][noptbins] = {{0}};
 
       for(int jet=0; jet<njets[ix]; jet++){
			  
	  if(jet==0){
          iRecoPTbin[ix] = getbinid(pfjetpT[ix][jet],nHLTmx, leadingPtThreshold);
          if ((iRecoPTbin[ix]<0) || (iRecoPTbin[ix]>=nHLTmx) || (ihlttrg[iRecoPTbin[ix]]==0)) break;
/*
	  if(abs(weighttrg[iRecoPTbin[ix]]-trig_weight[ix])*1./trig_weight[ix] > 1.e-6){	 
	  cout<<"weightrg "<<weighttrg[iRecoPTbin[ix]]<<" trigwt "<<trig_weight[ix]<<" diff "<<abs(weighttrg[iRecoPTbin[ix]]-trig_weight[ix])*1./(trig_weight[ix]*1.)<<" ratio "<<weighttrg[iRecoPTbin[ix]]/trig_weight[ix]<<endl;
		}
*/
	  weight =  weighttrg[iRecoPTbin[ix]]; // trig_weight[ix];
	   }


	 int etatag = getbinid(abs(pfjety[ix][jet]),netarange,etarng);
	 if(etatag>=0) {
	   njet_count[etatag]++;
	   
	   int ptbin_tag = getbinid(pfjetpT[ix][jet],noptbins1,ptbins1);

/*	   if(ptbin_tag>=0){
           if(ex_cor[ix][etatag][ptbin_tag]<1.e-3) { ex_cor[ix][etatag][ptbin_tag] = 1.; }
	   pfjetpT[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
	   pfjetpTup[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
	   pfjetpTdn[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
		}
*/
	   JetpT[ix][etatag]->Fill(pfjetpT[ix][jet],weight);
	   JetpT_up[ix][etatag]->Fill(pfjetpTup[ix][jet],weight);
	   JetpT_dn[ix][etatag]->Fill(pfjetpTdn[ix][jet],weight);

	   JetWidth[ix][etatag]->Fill(pfjetwidth[ix][jet],weight);	

	   if (pfjetpT[ix][jet]>leadingPtThreshold[0]) { Jeteta[ix]->Fill(pfjety[ix][jet],weight); }

          if(jet==0&&isMC) { Pthat_vs_LeadPt[ix]->Fill(pthat,pfjetpT[ix][jet]); }

	   JetPt_vs_JEC[ix][etatag]->Fill(pfjetpT[ix][jet],pfjetJEC[ix][jet],weight);
	   JetPt_vs_JECL1[ix][etatag]->Fill(pfjetpT[ix][jet],pfjetJECL1[ix][jet],weight);
	  
	   int ptbin_tag_cov = getbinid(pfjetpT[ix][jet],noptbins,ptbins);
	   if(ptbin_tag_cov>=0 && etatag>=0) { bincount[etatag][ptbin_tag_cov] += 1; }
 
	   if(jet==0){
	     Prescale_JetpT[ix][etatag][iRecoPTbin[ix]]->Fill(pfjetpT[ix][jet]);
	     LeadJetpT[ix][etatag]->Fill(pfjetpT[ix][jet],weight);
	     if (pfjetpT[ix][jet]>leadingPtThreshold[0]) { LeadJeteta[ix]->Fill(pfjety[ix][jet],weight);}
	   }
	 }
       } //jet
      

       for(int eta=0; eta<netarange; eta++){

	 NJets[ix][eta]->Fill(njet_count[eta],weight) ;
/*
		for(int pti=0; pti<noptbins; pti++){
		   for(int ptj=0; ptj<noptbins; ptj++){
				bincount2d[eta][pti][ptj] = bincount[eta][pti] * bincount[eta][ptj];
				Mes_Cov[ix][eta]->SetBinContent(pti+1,ptj+1,Mes_Cov[ix][eta]->GetBinContent(pti+1,ptj+1) + bincount2d[eta][pti][ptj]);
			}
		}*/
       }

       if(njets[ix]>=2){
	 Leading2JetsDeltaR[ix]->Fill(delta2R(pfjety[ix][0],pfjetphi[ix][0],pfjety[ix][1],pfjetphi[ix][1]),weight);
	 Leading2JetsDeltaPhi[ix]->Fill(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]),weight);

	 if((njets[ix]==2)||((njets[ix]>2)&&(pfjetpT[ix][2]<50.))){
	   double p4[3]={0};
		
	   if(abs(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]))>(2*pival/3.)){
	     for(int jt=0; jt<2; jt++){
	       p4[0]+=pfjetenr[ix][jt];
	       p4[1]+=pfjetpT[ix][jt];
	       p4[2]+=pfjetenr[ix][jt]*tanh(pfjety[ix][jt]);
	     }
				    
	     double refy ;
	     if(abs(pfjety[ix][0])>abs(pfjety[ix][1])){ refy = abs(pfjety[ix][0]);}
	     else { refy = abs(pfjety[ix][1]); }
	     int etatag = getbinid(refy,netarange,etarng)  ; 
			
	     if(etatag>=0) {
	       double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
	       DiJet_Mass[ix][etatag]->Fill(mass,weight);	
	     }
	   }//phi condn
	 }//dijet cond
       }//npfjets[ix]>=2	  
			
       if(isMC) {
				 
	 int ngenjet_count[netarange] = {0};
				
	 for(int jet=0; jet<ngenjets[ix]; jet++){
	   int etatag = getbinid(abs(genjety[ix][jet]),netarange,etarng);
	   if(etatag>=0){
	     ngenjet_count[etatag]++;
	     GenMCJetpT[ix][etatag]->Fill(genjetpT[ix][jet],weight);
	     GenMCJetpT_pow[ix][etatag]->Fill(genjetpT[ix][jet],genjetpT[ix][jet]*weight);
	     if (genjetpT[ix][jet]>leadingPtThreshold[0]) { GenJeteta[ix]->Fill(genjety[ix][jet],weight); }
	     
	     if(jet==0){
	       //	       iGenPTbin[ix] = getbinid(genjetpT[ix][jet],nHLTmx, leadingPtThreshold);
	       GenMCLeadJetpT[ix][etatag]->Fill(genjetpT[ix][jet],weight);
	       if (genjetpT[ix][jet]>leadingPtThreshold[0]) {GenLeadJeteta[ix]->Fill(genjety[ix][jet],weight);}
	     }
	   }
	 }//jet
				  
	 for(int eta=0; eta<netarange; eta++){
	   NGenJets[ix][eta]->Fill(ngenjet_count[eta],weight);
	 }

	 if(ngenjets[ix]>=2){
	   GenLeading2JetsDeltaR[ix]->Fill(delta2R(genjety[ix][0],genjetphi[ix][0],genjety[ix][1],genjetphi[ix][1]),weight);
	   GenLeading2JetsDeltaPhi[ix]->Fill(PhiInRange(genjetphi[ix][0]-genjetphi[ix][1]),weight);
			
	   if((ngenjets[ix]==2)||((ngenjets[ix]>2)&&(genjetpT[ix][2]<50.))){
			
	     double p4[3]={0};
			
	     if(abs(PhiInRange(genjetphi[ix][0]-genjetphi[ix][1]))>(2*pival/3.)) {
	       for(int jt=0; jt<2; jt++){
		 p4[0]+=genjetenr[ix][jt];
		 p4[1]+=genjetpT[ix][jt];
		 p4[2]+=genjetenr[ix][jt]*tanh(genjety[ix][jt]);
	       }
	       double refy ;
	       if(abs(genjety[ix][0])>abs(genjety[ix][1])){ refy = abs(genjety[ix][0]);}
	       else { refy = abs(genjety[ix][1]); }
	       int etatag = getbinid(refy,netarange,etarng)  ; 
			
	       if(etatag>=0){
		 double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
		 Gen_DiJet_Mass[ix][etatag]->Fill(mass,weight);		
	       }
	     }//phi condn
	   }//dijet 
	 }	  
	
			
	 //// ====== Resolution ==============

	 double deltaR_min = 0.05*(ix+1);
 
	 for(int reco = 0; reco<njets[ix]; reco++){
		
	   deltaR_min = 0.05*(ix+1);
		
	   int recoeta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	   if ((recoeta_tag<0)||(recoeta_tag>=netarange)) continue;
	    
	   int recopttag = getbinid(pfjetpT[ix][reco],noptbins,ptbins);
	   //	if(recopttag<0) continue ;
		
	   int match_gen = -1;
	   bool ismatched = false;
		
	   for(int gen = 0; gen<ngenjets[ix]; gen++){
			
	     int geneta_tag = -1;
	     geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	     int genpt_tag = -1;
	     genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);

	     if((recoeta_tag==geneta_tag)&&(recopttag==genpt_tag)&&geneta_tag>=0){ Pt_Ratio_nomatch[ix][geneta_tag]->Fill(genjetpT[ix][gen],pfjetpT[ix][reco]*1./genjetpT[ix][gen],weight);}
			
	     //	if(geneta_tag<0||genpt_tag<0) continue;
			
	     double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
			
	     if((genjetpT[ix][gen]>0.5*(pfjetpT[ix][reco]))&&(genjetpT[ix][gen]<2.*(pfjetpT[ix][reco]))){
	       if((geneta_tag>=0)&&(genpt_tag>=0)){
		 DeltaR_RecoGen[ix][geneta_tag][genpt_tag]->Fill(delR_rg) ;
	       }
	     }
			
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen] ;
			
	     if((delR_rg < deltaR_min)&&((pt_rat>0.25)&&(pt_rat<4.))) { 
	       deltaR_min = delR_rg ; 
	       match_gen = gen;
	       ismatched = true;
	     }
	   }//gen
			
			   
	   if(match_gen>=0){
				
	     int gen = match_gen;
					
	     int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	     int genpt_tag =  getbinid(genjetpT[ix][gen],noptbins,ptbins);	
				
	     int recomin = -1;
	     deltaR_min = 0.05*(ix+1);
				
	     for(int reco2=0; reco2<njets[ix]; reco2++){
	       double delR_rg = delta2R(pfjety[ix][reco2],pfjetphi[ix][reco2],genjety[ix][gen],genjetphi[ix][gen]) ;
	       if(delR_rg < deltaR_min){
		 deltaR_min = delta2R(pfjety[ix][reco2],pfjetphi[ix][reco2],genjety[ix][gen],genjetphi[ix][gen]);
		 recomin = reco2;
	       }
	     }//reco2
					
	     if(recomin==reco) {
				
	       if((geneta_tag>=0)&&(genpt_tag>=0)) {
						
		 double res_pt = 0;
		 res_pt = (pfjetpT[ix][reco] - genjetpT[ix][gen])*1.0/genjetpT[ix][gen]; // (RecopT[ix] - GenpT[ix])*1.0/(GenpT[ix]) ;
		 int nbins = Resolution[ix][geneta_tag][genpt_tag]->GetNbinsX();
		 if(res_pt<(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(1))) {
		   res_pt = (Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(1))+0.0001;
		 }else {
		   if(res_pt>(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1))) {
		     res_pt = Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1) -0.0001;
		   }
		 }
				
		 Resolution[ix][geneta_tag][genpt_tag]->Fill(res_pt) ;
	       } //if((geneta_tag>=0)&&(genpt_tag>=0))
			
	       if(geneta_tag==recoeta_tag){
		 RecoVsGenJetpT[ix][geneta_tag]->Fill(pfjetpT[ix][reco],genjetpT[ix][gen],weight);
		 Pt_Ratio[ix][geneta_tag]->Fill(genjetpT[ix][gen],pfjetpT[ix][reco]*1./genjetpT[ix][gen],weight);
	       } else {
		 if(recoeta_tag>=0){
		   RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
		 }
		 if(geneta_tag>=0){
		   RecoVsGenJetpT[ix][geneta_tag]->Fill(-1,genjetpT[ix][gen],weight);
		 }	
	       }
	     } else { //if(recomin==reco) 
	       RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
	     }
	   }//if(match_gen>=0)
	   else{
	     if(!ismatched){
	       if(recoeta_tag>=0){
		 RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
	       }
	     }
	   }
	 }//reco
	
	 
	 for(int gen = 0; gen<ngenjets[ix]; gen++){
		  
	   int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	   int genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);
	   
	   //	   if(geneta_tag<0||genpt_tag<0) continue ; 
	   
	   deltaR_min = 0.05*(ix+1);
	   
	   bool ismatched =false;
	   for(int reco = 0; reco<njets[ix]; reco++) { 
	     int receta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	     int recpt_tag = getbinid(abs(pfjetpT[ix][reco]),noptbins,ptbins);
	  
	     double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen];
			
	     if((delR_rg < deltaR_min)&&(pt_rat>0.25)&&(pt_rat<4.0)) { 
	      
	       int match_gen = -1;
	       
	       for(int gen2=0; gen2<ngenjets[ix] ; gen2++){
			   if(delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen2],genjetphi[ix][gen2])<deltaR_min){
				   deltaR_min = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen2],genjetphi[ix][gen2]);
				   match_gen = gen2;
				   }
			   }
			   
			   if(gen==match_gen) {
				   ismatched =true; 
				   break;
				   }
	     }	
	   }//reco
	    
	   if (!ismatched) { 
	     if(geneta_tag>=0) {
	       RecoVsGenJetpT[ix][geneta_tag]->Fill(-1, genjetpT[ix][gen],weight) ;
	     }
	   }
	 }//gen
				 
	 //// ====== Resolution End ==========	
			
	 ////======Response Matrix for y ==============
			
	 double y_matrix[njetmx][njetmx] = {{0.}};
			
	 for(int reco = 0; reco<njets[ix]; reco++) { 
	   for(int gen=0; gen<ngenjets[ix]; gen++){
	     y_matrix[reco][gen] =  abs(pfjety[ix][reco]-genjety[ix][gen]) ;
	   }
	 }
			
	 for(int gen=0; gen<ngenjets[ix]; gen++){
	   double miny = 100;
	   int recmin_indx = -1;
	   for(int reco = 0; reco<njets[ix]; reco++){
	     if(y_matrix[reco][gen]<miny){
	       miny = y_matrix[reco][gen];
	       recmin_indx = reco;
	     }
	   }
					
	   if(recmin_indx>=0){
						
	     miny = 100;
	     int genmin_index = -1;
						
	     for(int gen2=0; gen2<ngenjets[ix]; gen2++){
	       if(y_matrix[recmin_indx][gen2]<miny){
		 miny = y_matrix[recmin_indx][gen2];
		 genmin_index = gen2;
	       }
	     }//gen2
							
	     if(genmin_index==gen) {
							
	       double pt_rat = pfjetpT[ix][recmin_indx]*1./genjetpT[ix][gen] ;
							
	       if(((pt_rat>0.5)&&(pt_rat<2.))&&(abs(PhiInRange(pfjetphi[ix][recmin_indx]-genjetphi[ix][gen]))<0.075*(ix+1))){
		 Response_y[ix]->Fill(abs(pfjety[ix][recmin_indx]),abs(genjety[ix][gen]),weight) ;
		 y_Reso[ix]->Fill(pfjety[ix][recmin_indx]-genjety[ix][gen]) ;
	       }
	     }
	     else {continue;}
	   }
	   else {continue;}
	 }//gen
					
	 //============= Response Matrix for y Ends =======================		

	 //======= Resolution in Phi Starts ====================

	 for(int reco = 0; reco<njets[ix]; reco++){
	   for(int gen=0; gen<ngenjets[ix]; gen++){
		
	     double minphi = 100;
	     double pseudo_pfphi = 100;
	     double pseudo_genphi = 100;
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen];
	     double del_y = abs(pfjety[ix][reco]-genjety[ix][gen]) ;
	     bool isMatched = false;
		
	     if(((pt_rat>0.5)&&(pt_rat<2.))&&(del_y<0.05*(ix+1))){
			
	       isMatched = true;
			
	       if(abs(PhiInRange(pfjetphi[ix][reco]-genjetphi[ix][gen])) < minphi){
		 pseudo_pfphi = pfjetphi[ix][reco];
		 pseudo_genphi = genjetphi[ix][gen];
		 minphi = abs(PhiInRange(pfjetphi[ix][reco]-genjetphi[ix][gen]));
	       }
	     }
			
	     if(isMatched){
	       phi_Reso[ix]->Fill(PhiInRange(pseudo_pfphi-pseudo_genphi));
	     }
	   }//gen
	 }//reco

	 //======= Resolution in Phi Ends ====================
				
	 for(int jk=0; jk<netarange; jk++){
	   RecoVsGenJetNo[ix][jk]->Fill(njet_count[jk],ngenjet_count[jk], weight) ;
	 }//jk
					
       } //isMC
     }//ix 
 
  fileOut->cd();
  fileOut->Write();
  fileOut->Close();
 
  fp<<"Total Number of events in "<<fileOut->GetName()<<" is "<<nevent_total<<endl;
  fp<<"Total Weight is "<<tot_weight<<endl;

   return kTRUE;
}

void suman_rscan::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void suman_rscan::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
