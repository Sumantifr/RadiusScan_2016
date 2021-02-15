
/*
23/10/2012 : Add ho digi informations
/home/gobinda/cms/anal/CMSSW_5_3_2/src/
/afs/cern.ch/user/m/majumder/scratch0/simulation/CMSSW_5_2_3/src/
qpll :
cvs co -r CMSSW_5_3_2 RecoJets/JetProducers
cvs co -r CMSSW_5_3_2 RecoMET/Configuration
cvs co -r CMSSW_5_3_2 RecoMET/METProducers
cvs co -r CMSSW_5_3_2 DataFormats/HcalCalibObjects
cvs co -r CMSSW_5_3_2 RecoLocalCalo/CaloTowersCreator
cvs co -r CMSSW_5_3_2 RecoLocalCalo/Configuration
cvs co -r CMSSW_5_3_2 RecoLocalCalo/HcalRecProducers
cvs co -r CMSSW_5_3_2 RecoParticleFlow/Configuration
cvs co -r CMSSW_5_3_2 RecoParticleFlow/PFClusterProducer
cvs co -r CMSSW_5_3_2 RecoParticleFlow/PFProducer
*/
// Original Author:  Gobinda Majumder,22 1-031,+41227679681,
//         Created:  Thu Dec  1 13:09:13 CET 2011
// $Id$
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TAxis.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

#include "GeneratorInterface/Pythia8Interface/plugins/ReweightUserHooks.h"

#include <string>

#include <iostream>
#include <fstream>

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
//#include "CalibFormats/HcalObjects/interface/HcalCalibrationWidths.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
//#include "CondFormats/HcalObjects/interface/HcalQIECoder.h"
//#include "CondFormats/HcalObjects/interface/HcalPedestal.h"
//#include "CondFormats/HcalObjects/interface/HcalPedestalWidth.h"
//#include "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "FWCore/Utilities/interface/typelookup.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include  "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReportEntry.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReport.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/Framework/interface/ESHandle.h>
//#include "CondFormats/DataRecord/interface/JetResolutionRcd.h"
//#include "CondFormats/DataRecord/interface/JetResolutionScaleFactorRcd.h"
#include "FWCore/Utilities/interface/typelookup.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#define JETRESO                      // on for MC
////#define JETEnergyScale                   // on for data
////#define LHAPDF                      // on for MC
////#define GenPDF
////#define Data2015
#define Data2016

using namespace std;
using namespace edm;
using namespace reco;  
using namespace CLHEP;
using namespace trigger;
using namespace math;

const float mu_mass = 0.105658;
const float el_mass = 0.000511;
const float pival = acos(-1.);

static const int nalgo = 1;
const char* JetRad[nalgo] = {/*"ak1","ak2","ak3",*/"ak4"/*,"ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"*/};
static const int netarange = 10 ;
const char* JetEta[netarange] = {"|eta|<0.5","0.5<|eta|<1.0","1.0<|eta|<1.5","1.5<|eta|<2.0","2.0<|eta|<2.5","2.5<|eta|<3.0","3.0<|eta|<3.2","3.2<|eta|<3.7","3.7<|eta|<4.2","4.2<|eta|<4.7"} ;
double etarng[netarange+1] ={0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.2, 3.7, 4.2, 4.7};

static const int nsrc = 26;
const char* srcnames[nsrc] =
  {"AbsoluteStat", "AbsoluteScale", "AbsoluteFlavMap", "AbsoluteMPFBias", "Fragmentation", "SinglePionHCAL", "SinglePionECAL", "FlavorQCD", "TimePt", "TimeEta", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativeFSR", "RelativePtBB", "RelativePtEC1", "RelativePtEC2","RelativePtHF", "RelativeStatEC", "RelativeStatHF", "PileUpDataMC", "PileUpPtRef", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF"};

//const int njecmcmx = 1;

#ifdef JETRESO

const int njecmcmx = 3 ;

#elif defined(JETEnergyScale)

const int njecmcmx = 2*nsrc + 1 ;

#else

const int njecmcmx =  1 ;

#endif

const int noptbins = 67 ;
  
double ptbins[noptbins+1] = {37, 43, 49, 56, 64, 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;


#ifdef Data2015
const int npileupmx = 50;

#elif defined(Data2016)

const int npileupmx = 80;

#else
const int npileupmx = 50;

#endif



const int nHLTmx= 10; 

double compres[nHLTmx] = {0};

double compres15[nHLTmx] = {133490.64,17310.168,4567.035,868.165,117.545,11.427,5.46,2.466,1.0002,1.0};
double compresBC[nHLTmx] = {1728726.3799,82725.478,26255.7187,2572.276,261.405,55.0338,19.0746,6.229,1.,1.} ;
double compresDE[nHLTmx] = {917909.4373,82725.478,26255.7187,2572.276,261.405,55.0338,19.0746,6.229,1.,1.} ;
//double compresFG[nHLTmx] = {768152.62,122459.002,42357.61,4196.961,632.538,73.5695,24.368,8.2197,1.,1.} ;
double compresF[nHLTmx] = {755389.069,124562.8843,49923.0858,4353.415,648.5377,74.02,24.821,8.3699,1.,1.};
double compresG[nHLTmx] = {774248.665,122319.611,40851.372,4168.971,630.5287,73.69957,24.33146,8.2079,1.,1.};
double compresH[nHLTmx] =  {724247.565,130247.636,43019.847,4479.516,676.36,77.278,25.779,8.7586,1.,1.} ;

double rat_pileup[nHLTmx][npileupmx]={{0}};

//double leadingPtThreshold[nHLTmx+1]={70, 90, 109, 172, 239, 317, 374, 476, 525, 573, 5000.0}; //For AK4 PFJET Trigger turn on points

#ifdef Data2015
double leadingPtThreshold[nHLTmx+1] ={74, 97, 114, 174, 245, 330, 395, 507, 548, 592, 5000.0}; 

#elif defined(Data2016)
//double leadingPtThreshold[nHLTmx+1]= {74, 114, 196, 272, 330, 395, 468, 548, 5000.0} ; //Engin used
//double leadingPtThreshold[nHLTmx+1]= {74, 84, 114, 196, 272, 330, 395, 468, 548, 592, 5000.0}; 
double leadingPtThreshold[nHLTmx+1]= {37, 97, 133, 196, 272, 330, 395, 468, 548, 592, 5000.0};
#endif

const int nopbins = nHLTmx+1;

#ifdef Data2015
double pbins[nopbins+1] ={0, 70, 97, 114, 174, 245, 330, 395, 507, 548, 592, 5000.0}; 

#elif defined(Data2016)
double pbins[nopbins+1]={0, 74, 84, 114, 196, 272, 330, 395, 468, 548, 614, 5000.0};

#endif

double jethlt_thr[nHLTmx]={40, 60, 80,140,200,260,320,400,450,500};

#ifdef Data2015
const char* jethlt_name[nHLTmx] = {"HLT_PFJet40_v", "HLT_PFJet60_v", 
				 "HLT_PFJet80_v", "HLT_PFJet140_v", "HLT_PFJet200_v", 
				 "HLT_PFJet260_v", "HLT_PFJet320_v",
                                 "HLT_PFJet400_v", "HLT_PFJet450_v", "HLT_PFJet500_v"} ;

#elif defined (Data2016)
const char* jethlt_name[nHLTmx] = {"HLT_AK8PFJet40_v", "HLT_AK8PFJet60_v", 
				 "HLT_AK8PFJet80_v", "HLT_AK8PFJet140_v", "HLT_AK8PFJet200_v", 
				 "HLT_AK8PFJet260_v", "HLT_AK8PFJet320_v",
                                 "HLT_AK8PFJet400_v", "HLT_AK8PFJet450_v", "HLT_AK8PFJet500_v"} ;
#endif                                 


const char* jetak4hlt_name[nHLTmx]={"HLT_PFJet40_v", "HLT_PFJet60_v", 
				 "HLT_PFJet80_v", "HLT_PFJet140_v", "HLT_PFJet200_v", 
				 "HLT_PFJet260_v", "HLT_PFJet320_v",
                                 "HLT_PFJet400_v", "HLT_PFJet450_v", "HLT_PFJet500_v"} ;

const char* jetak8hlt_name[nHLTmx]={"HLT_AK8PFJet40_v", "HLT_AK8PFJet60_v", 
				 "HLT_AK8PFJet80_v", "HLT_AK8PFJet140_v", "HLT_AK8PFJet200_v", 
				 "HLT_AK8PFJet260_v", "HLT_AK8PFJet320_v",
                                 "HLT_AK8PFJet400_v", "HLT_AK8PFJet450_v", "HLT_AK8PFJet500_v"};


#ifdef Data2015

double mcpileup[npileupmx] ={0.00131219,0.00227916,0.00349035,0.0047818,0.00639651,0.0084178,0.0108138,0.0135592,0.0168034,0.0202878,0.0241942,0.0283229,0.0324728,0.0366731,0.0405802,0.044219,0.0474083,0.0497308,0.0511615,0.0518103,0.0515588,0.0504813,0.048436,0.0459626,0.0426073,0.0393155,0.0354159,0.031734,0.0278365,0.0242604,0.0208056,0.0176024,0.0147037,0.0120456,0.00980611,0.00791486,0.00622525,0.00483572,0.00373834,0.00284041,0.00209753,0.00153859,0.00112982,0.000804123,0.000562228,0.000388887,0.000265317,0.000180903,0.000116251,7.48986e-05}; 
//for 2015D 50 bins

//double mcpileup[npileupmx] = {0.00133138,0.00226617,0.00347697,0.00486957,0.00645179,0.00838397,0.0106977,0.0136185,0.0167816,0.0203971,0.0243055,0.028234,0.0323196,0.0366867,0.0405619,0.0441906,0.0473917,0.0495344,0.0511588,0.0519609,0.0516455,0.0503343,0.0483928,0.0458181,0.0427218,0.0391649,0.0355506,0.0317789,0.0278581,0.0241927,0.0207236,0.0177046,0.0147733,0.0121751,0.00986079,0.00785912,0.00625986,0.00483505,0.00374285,0.0028349,0.00208376,0.00155246,0.00112104,0.000808986,0.000567656,0.000390148,0.00026327,0.000170757,0.000118441/*,7.76308e-05*/}; //2016 Spring MC
#elif defined (Data2016)

double  mcpileup[npileupmx] = {2.82595e-05,6.29473e-05,0.000126337,0.000256885,0.000564631,0.00110702,0.00204067,0.0035458,0.00559555,0.0083368,0.011575,0.0154292,0.01967,0.0241571,0.0285471,0.0326206,0.0364776,0.0397328,0.0421873,0.044275,0.0451668,0.0458842,0.045376,0.0445124,0.043152,0.0411647,0.038777,0.0366233,0.033998,0.0314075,0.0287512,0.0262996,0.0239008,0.0215455,0.0195003,0.0176033,0.015793,0.0141663,0.0128473,0.0115051,0.0103265,0.00926773,0.00834596,0.00750304,0.00666546,0.00597047,0.00529105,0.00466223,0.00413244,0.00362811,0.00318285,0.00273657,0.00239027,0.0020306,0.0017336,0.00146106,0.00122478,0.00100438,0.000834986,0.000668676,0.000550739,0.000455454,0.000343681,0.000275465,0.000227473,0.000165593,0.000133594,0.000107893,7.98589e-05,6.69385e-05,5.60126e-05,4.08681e-05,2.92365e-05,2.53712e-05,1.69478e-05,1.57952e-05,1.38265e-05,9.98148e-06,6.90946e-06,6.66382e-06} ; //For 2016 Summer MC

#endif
//double mcpileup[npileupmx] ={0.00095,0.00245,0.0034,0.00545,0.0053,0.0073,0.0103,0.0129,0.01455,0.02175,0.0246,0.02965,0.03265,0.03565,0.04195,0.04545,0.04635,0.0492,0.0524,0.0493,0.0495,0.05245,0.04855,0.04535,0.04415,0.03965,0.03475,0.03145,0.03005,0.0245,0.02065,0.0167,0.01545,0.0118,0.0095,0.0068,0.006,0.0058,0.0049,0.0028,0.0026,0.00165,0.0009,0.00095,0.00065,0.0003,0.0001,0.0002,0.0001,0.0001,5e-05,5e-05,0,0,0,0,0,0,0}

#ifdef Data2015

double datpileup[nHLTmx][npileupmx] ={ {5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}*/
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								       ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}
								     ,{5.59005e-05,0.000268082,0.00038114,0.000548791,0.000967954,0.00227247,0.00708089,0.0272594,0.0754117,0.129253,0.168217,0.181735,0.162694,0.117907,0.0687553,0.0327985,0.0135528,0.00561249,0.00274113,0.00145598,0.00068176,0.000253159,7.38419e-05,1.79722e-05,4.21013e-06,1.12697e-06,3.60827e-07,1.29128e-07,4.85584e-08,1.84662e-08,6.91112e-09,2.49941e-09,8.64236e-10,2.84148e-10,8.86003e-11,2.61695e-11,7.3183e-12,1.93727e-12,4.85407e-13,1.15118e-13,2.58407e-14,5.49017e-15,1.10406e-15,2.10149e-16,3.78622e-17,6.45404e-18,1.04508e-18,1.56733e-19,2.84959e-20,0}*/
                                    }; // for 2015 data 50 bins
		 

#elif defined(Data2016)

double datpileup[nHLTmx][npileupmx] =  	{{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										,{6.52792e-06,2.25873e-05,6.30179e-05,8.48678e-05,0.000121822,0.000163186,0.00019044,0.000344208,0.000942541,0.00210257,0.00471626,0.00963608,0.0162032,0.0236351,0.0317173,0.040292,0.0477459,0.0528886,0.0558519,0.0573331,0.0582012,0.0586839,0.0582154,0.0564851,0.0538176,0.0505587,0.0468387,0.0427834,0.038568,0.0343206,0.0301031,0.0259666,0.0219912,0.0182764,0.0149097,0.0119448,0.00939622,0.00724809,0.00546795,0.00401908,0.00286629,0.00197552,0.00131137,0.000836089,0.000510923,0.000298789,0.00016704,8.92227e-05,4.55329e-05,2.22214e-05,1.03993e-05,4.69849e-06,2.08208e-06,9.37062e-07,4.57241e-07,2.62816e-07,1.84761e-07,1.51844e-07,1.3556e-07,1.25048e-07,1.16374e-07,1.08206e-07,1.00151e-07,9.21457e-08,8.42338e-08,7.64909e-08,6.89947e-08,6.1815e-08,5.50097e-08,4.86243e-08,4.26909e-08,3.72294e-08,3.22484e-08,2.7746e-08,2.37118e-08,2.0128e-08,1.69711e-08,1.42132e-08,1.18236e-08}
										}; //for 2016 data 80 bins
#endif


struct triggervar{
  HepLorentzVector trg4v;
  bool		       both;
  bool            level1;
  bool            highl;
  int             ihlt;
  int             prescl;
};

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
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


//class declaration
//
class MCJetsMINIAOD_SingleRad : public edm::EDAnalyzer {
   public:
      explicit MCJetsMINIAOD_SingleRad(const edm::ParameterSet&);
      ~MCJetsMINIAOD_SingleRad();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void fillmetarray();
      // ----------member data ---------------------------
  int Nevt;
  bool isMC;
  bool Data2016B,Data2016C,Data2016D,Data2016E,Data2016F,Data2016G,Data2016H;
  bool isReconstruct ;
  bool isHistFill;
  std::string theRootFileName;
  std::string theHLTTag;
  int iTag;
  int iTagMET;
  double jtptthr;
  double minPFPt;

  int trig_tag = 0;
  bool two_tag = false;

//  edm::EDGetTokenT<reco::BeamSpot> tok_beamspot_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

  edm::EDGetTokenT<double> tok_Rho_;
  edm::EDGetTokenT<reco::VertexCollection> tok_primaryVertices_;
  //edm::EDGetTokenT<reco::GenParticleCollection>tok_genparticles_;
  edm::EDGetTokenT<pat::METCollection>tok_mets_ ;
  
  edm::EDGetTokenT<edm::View<pat::Jet>/*reco::PFJetCollection*/>tok_pfjets_[nalgo] ;
  
 
  edm::EDGetTokenT<reco::GenJetCollection>tok_genjets_[nalgo];
  
  edm::EDGetTokenT<HepMCProduct> tok_HepMC ;
  edm::EDGetTokenT<GenEventInfoProduct> tok_wt_;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileup_;
  
  edm::EDGetTokenT<LHEEventProduct> lheEventProductToken_;
  edm::EDGetTokenT<GenEventInfoProduct> GenEventProductToken_;

  TFile* theFile;

  TTree* T1;
  
  TH1F* hist_pfmet ;
  TH1F* hist_SumEt;
  TH1F* hist_METbyET ;
  TH1F* hist_weight;
  
  #if defined(JETEnergyScale) || defined(JETRESO)
  TH1F * RecoJetpT[nalgo][netarange][njecmcmx] ;
  #endif 
  
  #ifdef  LHAPDF
		static const int nnmx=101;
        double pdfwt[nnmx];
  #elif defined(GenPDF)
        static const int nnmx=101;
        double pdfwt[nnmx];
  #else	
		static const int nnmx=1;
		double pdfwt[nnmx] =  {1.0};
	
 #endif 
 
  TH1F* scale_factor[nalgo];
 
  TH1F* JetpT[nalgo][netarange];
  TH1F* LeadJetpT[nalgo][netarange];
  TH1F* DiJet_Mass[nalgo][netarange];
  TH1F* Jeteta[nalgo];
  TH1F* LeadJeteta[nalgo];
  TH1F* Leading2JetsDeltaR[nalgo];
  TH1F* Leading2JetsDeltaPhi[nalgo] ;
  TH1F* Prescale_JetpT[nalgo][netarange][nHLTmx] ;
  TH1F* Prescale_JetpT_all[nalgo][netarange][nHLTmx] ;  

  TH1F* LeadJetRatio[nalgo][netarange];

  TH1F* CHF_hiss[nalgo];
  TH1F* CEMF_hiss[nalgo];
  TH1F* NHF_hiss[nalgo];
  TH1F* NEMF_hiss[nalgo];
  TH1F* MUF_hiss[nalgo];
  TH1F* PHF_hiss[nalgo];
  TH1F* cem_mul_hiss[nalgo];
  TH1F* ch_mul_hiss[nalgo];
  TH1F* neu_em_mul_hiss[nalgo];
  TH1F* neu_had_mul_hiss[nalgo];
  TH1F* muon_mul_hiss[nalgo];
  TH1F* phtn_mul_hiss[nalgo];
  TH1F* neu_tot_mul_hiss[nalgo];
  
  TH1F* CHF_clean_hiss[nalgo];
  TH1F* CEMF_clean_hiss[nalgo];
  TH1F* NHF_clean_hiss[nalgo];
  TH1F* NEMF_clean_hiss[nalgo];
  TH1F* MUF_clean_hiss[nalgo];
  TH1F* PHF_clean_hiss[nalgo];
  TH1F* cem_mul_clean_hiss[nalgo];
  TH1F* ch_mul_clean_hiss[nalgo];
  TH1F* neu_em_mul_clean_hiss[nalgo];
  TH1F* neu_had_mul_clean_hiss[nalgo];
  TH1F* muon_mul_clean_hiss[nalgo];
  TH1F* phtn_mul_clean_hiss[nalgo];
  
  
  TH1F* CHF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* CEMF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* NHF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* NEMF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* MUF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* PHF_hiss_binned[nalgo][netarange][nopbins];
  TH1F* cem_mul_hiss_binned[nalgo][netarange][nopbins];
  TH1F* ch_mul_hiss_binned[nalgo][netarange][nopbins];
  TH1F* neu_em_mul_hiss_binned[nalgo][netarange][nopbins];
  TH1F* neu_had_mul_hiss_binned[nalgo][netarange][nopbins];
  TH1F* muon_mul_hiss_binned[nalgo][netarange][nopbins];
  TH1F* phtn_mul_hiss_binned[nalgo][netarange][nopbins];
  
  TH1F* CHF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* CEMF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* NHF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* NEMF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* MUF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* PHF_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* cem_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* ch_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* neu_em_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* neu_had_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* muon_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  TH1F* phtn_mul_clean_hiss_binned[nalgo][netarange][nopbins];
  
  TH2F* CHF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* CEMF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* NHF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* NEMF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* MUF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* PHF_clean_2dhiss_binned[nalgo][netarange];
  TH2F* cem_mul_clean_2dhiss_binned[nalgo][netarange];
  TH2F* ch_mul_clean_2dhiss_binned[nalgo][netarange];
  TH2F* neu_em_mul_clean_2dhiss_binned[nalgo][netarange];
  TH2F* neu_had_mul_clean_2dhiss_binned[nalgo][netarange];
  TH2F* muon_mul_clean_2dhiss_binned[nalgo][netarange];
  TH2F* phtn_mul_clean_2dhiss_binned[nalgo][netarange];


  TH1F* GenJetpT[nalgo][netarange][nnmx];
  TH1F* GenLeadJetpT[nalgo][netarange][nnmx];
  TH1F* GenMCJetpT[nalgo][netarange];
  TH1F* GenMCJetpT_pow[nalgo][netarange];
  TH1F* GenMCLeadJetpT[nalgo][netarange];
  TH1F* Gen_DiJet_Mass[nalgo][netarange];
  TH1F* GenJeteta[nalgo];
  TH1F* GenLeadJeteta[nalgo];
  TH1F* GenLeading2JetsDeltaR[nalgo];
  TH1F* GenLeading2JetsDeltaPhi[nalgo] ;
  TH1F* DeltaR_RecoGen[nalgo][netarange][noptbins] ;
  TH1F* DeltaR_RecoGen_mat[nalgo][netarange][noptbins] ;
  TH1F* Resolution[nalgo][netarange][noptbins];

  TH2F* RecoVsGenJetpT[nalgo][netarange] ;
  TH2F* JEC_fac[nalgo][netarange] ;
  TH2F* Response_y[nalgo];

  TH1F* PileupVertices[nHLTmx] ;
 
  
  //Trigger Normal case
  TH1F* trgjet_angle[nalgo][nHLTmx][netarange][2];
  TH2F* trgjet_2dangle[nalgo][nHLTmx][netarange][2];
  TH1F* trgjet_pt[nalgo][nHLTmx][netarange][2];
  TH1F* trgjet_eta[nalgo][nHLTmx][netarange][2];
  TH1F* trgjet_phi[nalgo][nHLTmx][netarange][2];
  TH1F* prbjet_pt[nalgo][nHLTmx][netarange][2];
  TH1F* prbjet_eta[nalgo][nHLTmx][netarange][2];
  TH1F* prbjet_phi[nalgo][nHLTmx][netarange][2];

  TH1F* prim_hist[nHLTmx+1];
  TH1F* prim_sel[nHLTmx+1];

  TH1F* prim_hist_rewt[nHLTmx+1];
  TH1F* prim_sel_rewt[nHLTmx+1];
  
  int irunold;
  int irun, ilumi, ifltr, nprim, ibrnch;
  double event_weight;
  
  unsigned ievt;
  
  static const int njetmx =20; 
  
  double Rho ;
    

  int npfjets[nalgo] ;
  int pfjetmul[nalgo][njetmx] ;
  float pfjetenr[nalgo][njetmx], pfjetmom[nalgo][njetmx], pfjetpT[nalgo][njetmx], pfjetpz[nalgo][njetmx], pfjetarea[nalgo][njetmx], pfjetthe[nalgo][njetmx], pfjety[nalgo][njetmx], pfjetphi[nalgo][njetmx] ;
 
  int npfjets01;
  int pfjetmul01[njetmx];
  float pfjetenr01[njetmx], pfjetpT01[njetmx], pfjetarea01[njetmx], pfjety01[njetmx], pfjetphi01[njetmx] ;
  
  int npfjets02;
  int pfjetmul02[njetmx];
  float pfjetenr02[njetmx], pfjetpT02[njetmx], pfjetarea02[njetmx], pfjety02[njetmx], pfjetphi02[njetmx] ;
  
  int npfjets03;
  int pfjetmul03[njetmx];
  float pfjetenr03[njetmx], pfjetpT03[njetmx], pfjetarea03[njetmx], pfjety03[njetmx], pfjetphi03[njetmx] ;

  int npfjets04;
  int pfjetmul04[njetmx];
  float pfjetenr04[njetmx], pfjetpT04[njetmx], pfjetarea04[njetmx], pfjety04[njetmx], pfjetphi04[njetmx] ;

  int npfjets05;
  int pfjetmul05[njetmx];
  float pfjetenr05[njetmx], pfjetpT05[njetmx], pfjetarea05[njetmx], pfjety05[njetmx], pfjetphi05[njetmx] ;

  int npfjets06;
  int pfjetmul06[njetmx];
  float pfjetenr06[njetmx], pfjetpT06[njetmx], pfjetarea06[njetmx], pfjety06[njetmx], pfjetphi06[njetmx] ;

  int npfjets07;
  int pfjetmul07[njetmx];
  float pfjetenr07[njetmx], pfjetpT07[njetmx], pfjetarea07[njetmx], pfjety07[njetmx], pfjetphi07[njetmx] ;

  int npfjets08;
  int pfjetmul08[njetmx];
  float pfjetenr08[njetmx], pfjetpT08[njetmx], pfjetarea08[njetmx], pfjety08[njetmx], pfjetphi08[njetmx] ;

  int npfjets09;
  int pfjetmul09[njetmx];
  float pfjetenr09[njetmx], pfjetpT09[njetmx], pfjetarea09[njetmx], pfjety09[njetmx], pfjetphi09[njetmx] ;

  int npfjets10;
  int pfjetmul10[njetmx];
  float pfjetenr10[njetmx], pfjetpT10[njetmx], pfjetarea10[njetmx], pfjety10[njetmx], pfjetphi10[njetmx] ;

  int npfjets11;
  int pfjetmul11[njetmx];
  float pfjetenr11[njetmx], pfjetpT11[njetmx], pfjetarea11[njetmx], pfjety11[njetmx], pfjetphi11[njetmx] ;

  int npfjets12;
  int pfjetmul12[njetmx];
  float pfjetenr12[njetmx], pfjetpT12[njetmx], pfjetarea12[njetmx], pfjety12[njetmx], pfjetphi12[njetmx] ;
  
  int npfjets13;
  int pfjetmul13[njetmx];
  float pfjetenr13[njetmx], pfjetpT13[njetmx], pfjetarea13[njetmx], pfjety13[njetmx], pfjetphi13[njetmx] ;
  
  int npfjets14;
  int pfjetmul14[njetmx];
  float pfjetenr14[njetmx], pfjetpT14[njetmx], pfjetarea14[njetmx], pfjety14[njetmx], pfjetphi14[njetmx] ;
  
  int npfjets15;
  int pfjetmul15[njetmx];
  float pfjetenr15[njetmx], pfjetpT15[njetmx], pfjetarea15[njetmx], pfjety15[njetmx], pfjetphi15[njetmx] ;

  
  static const int ngenjetmx =20;

  int ngenjets[nalgo] ;
  int genjetmul[nalgo];
  float genjetenr[nalgo][njetmx], genjetmom[nalgo][njetmx], genjetpT[nalgo][njetmx], genjetpz[nalgo][njetmx], genjetarea[nalgo][njetmx], genjetthe[nalgo][njetmx], genjety[nalgo][njetmx], genjetphi[nalgo][njetmx] ;

  int ngenjets01;
  int genjetmul01[njetmx];
  float genjetenr01[njetmx], genjetpT01[njetmx], genjetarea01[njetmx], genjety01[njetmx], genjetphi01[njetmx] ;

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
  float genjetenr15[njetmx], genjetpT15[njetmx], genjetarea15[njetmx], genjety15[njetmx], genjetphi15[njetmx] ;
  
  
  float miset , misphi , sumEt;
  
  int isReco[nalgo] = {-1} ;
  float RecopT[nalgo] = {-1} ;
  int  iRecoPTbin[nalgo] = {-1} ;

  int isGen[nalgo] = {-1} ;
  float GenpT/*[njecmcmx]*/[nalgo] = {-1} ;// {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}} ;
  int  iGenPTbin[nalgo] = {-1} ;

  unsigned int mypow_2[32];

  int irunhlt, l1pres[nHLTmx], hltpres[nHLTmx];
  /*
  #ifdef Data2015
  double compres[nHLTmx] = {133490.64,17310.168,4567.035,868.165,117.545,11.427,5.46,2.466,1.0002,1.0}; 
 
  #elif defined(Data2016)
// double compres[nHLTmx] = {672386.,101981.,33293.6,3309.27,389.811,64.5779,21.9379,7.2873,1.0,1.0};  //all versions of trigger
   double compres[nHLTmx] = {768152.62,122459.002,42357.61,4196.961,632.538,73.5695,24.368,8.2197,1.,1.} ;
   
   if(Data2016B||Data2016C){
	   compres[nHLTmx] = {1728726.3799,82725.478,26255.7187,2572.276,261.405,55.0338,19.0746,6.229,1.,1.} ;
	   }
   if(Data2016D||Data2016E){
	   compres[nHLTmx] = {917909.4373,82725.478,26255.7187,2572.276,261.405,55.0338,19.0746,6.229,1.,1.} ;
	   } 	   
   if(Data2016F||Data2016G){
	   compres[nHLTmx] = {768152.62,122459.002,42357.61,4196.961,632.538,73.5695,24.368,8.2197,1.,1.} ;
		}
	if(Data2016H){
	   compres[nHLTmx] = {724247.565,130247.636,43019.847,4479.516,676.36,77.278,25.779,8.7586,1.,1.} ;
		}
 
 #endif
 * */
/* for 2015D*/
//  double compres[nHLTmx]={/*1000000,*/ 672386,101981,33294,3309.3,390,64.6,21.9,7.3,1.0,1.0};
/* for 2016*/  

  //HLTConfigProvider hltConfig_;
  HLTPrescaleProvider hltPrescaleProvider_;

  float qscale;
  float wtfact , weight2 = 1.0;
  float pthat ;
  float weighttrg[nHLTmx]; // = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}; //MC : eventinfo->weight(); data : hltpres[ihltfill]*l1pres[ihltfill];
  int procid, npilup1, npilup2; //1:-5 to -1, 2:0 to 3
  
  int idall;
  float xfrac1, xfrac2, xpdf1, xpdf2;  
  
   // ---- Jet Corrector Parameter ---- //
    JetCorrectorParameters *L1FastAK4, *L2RelativeAK4, *L3AbsoluteAK4, *L2L3ResidualAK4;
    vector<JetCorrectorParameters> vecL1FastAK4, vecL2RelativeAK4, vecL3AbsoluteAK4, vecL2L3ResidualAK4;
    FactorizedJetCorrector *jecL1FastAK4, *jecL2RelativeAK4, *jecL3AbsoluteAK4, *jecL2L3ResidualAK4;
 
    JetCorrectorParameters *L1FastAK8, *L2RelativeAK8, *L3AbsoluteAK8, *L2L3ResidualAK8;
    vector<JetCorrectorParameters> vecL1FastAK8, vecL2RelativeAK8, vecL3AbsoluteAK8, vecL2L3ResidualAK8;
    FactorizedJetCorrector *jecL1FastAK8, *jecL2RelativeAK8, *jecL3AbsoluteAK8, *jecL2L3ResidualAK8;
 

   // std::string mFileName,mPuFileName,mPuTrigName;
    std::string mJECL1FastFileAK4, mJECL2RelativeFileAK4, mJECL3AbsoluteFileAK4, mJECL2L3ResidualFileAK4, mJECL1FastFileAK8, mJECL2RelativeFileAK8, mJECL3AbsoluteFileAK8, mJECL2L3ResidualFileAK8;
  
  // ---- Jet Corrector Parameter End---- //
  
  std::vector<JetCorrectionUncertainty*> vsrc ;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MCJetsMINIAOD_SingleRad::MCJetsMINIAOD_SingleRad(const edm::ParameterSet& pset) :
triggerBits_(consumes<edm::TriggerResults>(pset.getParameter<edm::InputTag>("bits"))),
triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(pset.getParameter<edm::InputTag>("objects"))),
triggerPrescales_(consumes<pat::PackedTriggerPrescales>(pset.getParameter<edm::InputTag>("prescales"))),
hltPrescaleProvider_(pset, consumesCollector(), *this)
{
   //now do what ever initialization is needed
  
  edm::Service<TFileService> fs;
  
  isMC      = pset.getUntrackedParameter<bool>("MonteCarlo", false);
  Data2016B = pset.getUntrackedParameter<bool>("Data2016B", false);
  Data2016C = pset.getUntrackedParameter<bool>("Data2016C", false);
  Data2016D = pset.getUntrackedParameter<bool>("Data2016D", false);
  Data2016E = pset.getUntrackedParameter<bool>("Data2016E", false);
  Data2016F = pset.getUntrackedParameter<bool>("Data2016F", false);
  Data2016G = pset.getUntrackedParameter<bool>("Data2016G", false);
  Data2016H = pset.getUntrackedParameter<bool>("Data2016H", false);
  isHistFill = pset.getUntrackedParameter<bool>("HistFill", true); 
  jtptthr = pset.getUntrackedParameter<double>("Ptcut", 51.0);
  weight2 = pset.getUntrackedParameter<double>("HistWeight", 1.0);
  minPFPt =  pset.getUntrackedParameter<double>("minPFPt", 30.0);
  isReconstruct = pset.getUntrackedParameter<bool>("isRECO", true);
  theRootFileName = pset.getUntrackedParameter<string>("RootFileName");
  theHLTTag = pset.getUntrackedParameter<string>("HLTTag", "HLT");
  
  //  tok_beamspot_ = consumes<reco::BeamSpot> (pset.getParameter<edm::InputTag>("Beamspot"));
  tok_primaryVertices_ =consumes<reco::VertexCollection>( pset.getParameter<edm::InputTag>("PrimaryVertices"));

  
  tok_Rho_ = consumes<double>(pset.getParameter<edm::InputTag>("PFRho"));
 /* triggerBits_ = consumes<edm::TriggerResults>(pset.getParameter<edm::InputTag>("bits"));
  triggerObjects_ = consumes<pat::TriggerObjectStandAloneCollection>(pset.getParameter<edm::InputTag>("objects"));
  triggerPrescales_ = consumes<pat::PackedTriggerPrescales>(pset.getParameter<edm::InputTag>("prescales"));*/
   
  tok_mets_= consumes<pat::METCollection> ( pset.getParameter<edm::InputTag>("PFMet"));
 
  mJECL1FastFileAK4         = pset.getParameter<std::string>               ("jecL1FastFileAK4");
  mJECL1FastFileAK8         = pset.getParameter<std::string>               ("jecL1FastFileAK8");
  mJECL2RelativeFileAK4     = pset.getParameter<std::string>               ("jecL2RelativeFileAK4");
  mJECL2RelativeFileAK8     = pset.getParameter<std::string>               ("jecL2RelativeFileAK8");
  mJECL3AbsoluteFileAK4     = pset.getParameter<std::string>               ("jecL3AbsoluteFileAK4");
  mJECL3AbsoluteFileAK8     = pset.getParameter<std::string>               ("jecL3AbsoluteFileAK8");
  mJECL2L3ResidualFileAK4   = pset.getParameter<std::string>               ("jecL2L3ResidualFileAK4");
  mJECL2L3ResidualFileAK8   = pset.getParameter<std::string>               ("jecL2L3ResidualFileAK8");
 
  for(int ij=0; ij<nalgo; ++ij){
    char jettag[100] ;
    
     sprintf(jettag,"PFJets%i",ij+1) ;
     
 //    cout<<"jettag  "<<jettag<<endl ;
    
    tok_pfjets_[ij]= consumes<edm::View<pat::Jet>/*reco::PFJetCollection*/>( pset.getParameter<edm::InputTag>(jettag));
   
    if(isMC){
      
      sprintf(jettag,"GenJets%i",ij+1);
      
      tok_genjets_[ij]= consumes<reco::GenJetCollection>( pset.getParameter<edm::InputTag>(jettag));
    }
  }
  
  
  
  if(isMC){    
    tok_HepMC= consumes<HepMCProduct>(pset.getParameter<edm::InputTag>("Generator"));
    tok_wt_ = consumes<GenEventInfoProduct>(pset.getParameter<edm::InputTag>("Generator")) ;
    pileup_ = consumes<std::vector<PileupSummaryInfo> >(pset.getParameter<edm::InputTag>("slimmedAddPileupInfo"));   
    
    lheEventProductToken_ = consumes<LHEEventProduct>(pset.getParameter<edm::InputTag>("LHEEventProductInputTag")) ;
    GenEventProductToken_  = consumes<GenEventInfoProduct>(pset.getParameter<edm::InputTag>("GenEventProductInputTag")) ;
  } 
 
  char name[100];
  char title[100];
 
  theFile = new TFile(theRootFileName.c_str(), "RECREATE");
  theFile->cd();
 
  //  T1 = fs->make<TTree>("T1","PFandGenJets") ;
  T1 = new TTree("T1", "PFandGenJets");

  T1->Branch("irun", &irun, "irun/I");  
  T1->Branch("ilumi", &ilumi, "ilumi/I");  
  
  T1->Branch("ievt", &ievt, "ievt/i");
  T1->Branch("nprim", &nprim, "nprim/I");
  
  T1->Branch("Rho", &Rho, "Rho/D") ;
  
  T1->Branch("event_weight", &event_weight, "event_weight/D") ;

  T1->Branch("PFMET",&miset,"miset/F") ;
  T1->Branch("PFMETPhi",&misphi,"misphi/F") ;

  T1->Branch("npfjets01",&npfjets01, "npfjets01/I"); 
  T1->Branch("pfjetpT01",pfjetpT01,"pfjetpT01[npfjets01]/F");
  T1->Branch("pfjetarea01",pfjetarea01,"pfjetarea01[npfjets01]/F");
  T1->Branch("pfjety01",pfjety01,"pfjety01[npfjets01]/F"); 
  T1->Branch("pfjetphi01",pfjetphi01,"pfjetphi01[npfjets01]/F") ;

  T1->Branch("npfjets02", &npfjets02, "npfjets02/I"); 
  T1->Branch("pfjetpT02",pfjetpT02,"pfjetpT02[npfjets02]/F");
  T1->Branch("pfjetarea02",pfjetarea02,"pfjetarea02[npfjets02]/F");
  T1->Branch("pfjety02",pfjety02,"pfjety02[npfjets02]/F"); 
  T1->Branch("pfjetphi02",pfjetphi02,"pfjetphi02[npfjets02]/F") ;

  T1->Branch("npfjets03", &npfjets03, "npfjets03/I");
  T1->Branch("pfjetpT03",pfjetpT03,"pfjetpT03[npfjets03]/F");
  T1->Branch("pfjetarea03",pfjetarea03,"pfjetarea03[npfjets03]/F");
  T1->Branch("pfjety03",pfjety03,"pfjety03[npfjets03]/F");
  T1->Branch("pfjetphi03",pfjetphi03,"pfjetphi03[npfjets03]/F") ;
 
  T1->Branch("npfjets04", &npfjets04, "npfjets04/I");
  T1->Branch("pfjetpT04",pfjetpT04,"pfjetpT04[npfjets04]/F");
  T1->Branch("pfjetarea04",pfjetarea04,"pfjetarea04[npfjets04]/F");
  T1->Branch("pfjety04",pfjety04,"pfjety04[npfjets04]/F");
  T1->Branch("pfjetphi04",pfjetphi04,"pfjetphi04[npfjets04]/F") ;

  T1->Branch("npfjets05", &npfjets05, "npfjets05/I");
  T1->Branch("pfjetpT05",pfjetpT05,"pfjetpT05[npfjets05]/F");
  T1->Branch("pfjetarea05",pfjetarea05,"pfjetarea05[npfjets05]/F");
  T1->Branch("pfjety05",pfjety05,"pfjety05[npfjets05]/F");
  T1->Branch("pfjetphi05",pfjetphi05,"pfjetphi05[npfjets05]/F") ;

  T1->Branch("npfjets06", &npfjets06, "npfjets06/I");
  T1->Branch("pfjetpT06",pfjetpT06,"pfjetpT06[npfjets06]/F");
  T1->Branch("pfjetarea06",pfjetarea06,"pfjetarea06[npfjets06]/F");
  T1->Branch("pfjety06",pfjety06,"pfjety06[npfjets06]/F");
  T1->Branch("pfjetphi06",pfjetphi06,"pfjetphi06[npfjets06]/F") ;

  T1->Branch("npfjets07", &npfjets07, "npfjets07/I");
  T1->Branch("pfjetpT07",pfjetpT07,"pfjetpT07[npfjets07]/F");
  T1->Branch("pfjetarea07",pfjetarea07,"pfjetarea07[npfjets07]/F");
  T1->Branch("pfjety07",pfjety07,"pfjety07[npfjets07]/F");
  T1->Branch("pfjetphi07",pfjetphi07,"pfjetphi07[npfjets07]/F") ; 

  T1->Branch("npfjets08", &npfjets08, "npfjets08/I");
  T1->Branch("pfjetpT08",pfjetpT08,"pfjetpT08[npfjets08]/F");
  T1->Branch("pfjetarea08",pfjetarea08,"pfjetarea08[npfjets08]/F");
  T1->Branch("pfjety08",pfjety08,"pfjety08[npfjets08]/F");
  T1->Branch("pfjetphi08",pfjetphi08,"pfjetphi08[npfjets08]/F") ;

  T1->Branch("npfjets09", &npfjets09, "npfjets09/I");
  T1->Branch("pfjetpT09",pfjetpT09,"pfjetpT09[npfjets09]/F");
  T1->Branch("pfjetarea09",pfjetarea09,"pfjetarea09[npfjets09]/F");
  T1->Branch("pfjety09",pfjety09,"pfjety09[npfjets09]/F");
  T1->Branch("pfjetphi09",pfjetphi09,"pfjetphi09[npfjets09]/F") ;
 
  T1->Branch("npfjets10", &npfjets10, "npfjets10/I");
  T1->Branch("pfjetpT10",pfjetpT10,"pfjetpT10[npfjets10]/F");
  T1->Branch("pfjetarea10",pfjetarea10,"pfjetarea10[npfjets10]/F");
  T1->Branch("pfjety10",pfjety10,"pfjety10[npfjets10]/F");
  T1->Branch("pfjetphi10",pfjetphi10,"pfjetphi10[npfjets10]/F") ;

  T1->Branch("npfjets11", &npfjets11, "npfjets11/I");
  T1->Branch("pfjetpT11",pfjetpT11,"pfjetpT11[npfjets11]/F");
  T1->Branch("pfjetarea11",pfjetarea11,"pfjetarea11[npfjets11]/F");
  T1->Branch("pfjety11",pfjety11,"pfjety11[npfjets11]/F");
  T1->Branch("pfjetphi11",pfjetphi11,"pfjetphi11[npfjets11]/F") ; 
  
  T1->Branch("npfjets12", &npfjets12, "npfjets12/I");
  T1->Branch("pfjetpT12",pfjetpT12,"pfjetpT12[npfjets12]/F");
  T1->Branch("pfjetarea12",pfjetarea12,"pfjetarea12[npfjets12]/F");
  T1->Branch("pfjety12",pfjety12,"pfjety12[npfjets12]/F");
  T1->Branch("pfjetphi12",pfjetphi12,"pfjetphi12[npfjets12]/F") ; 
  

  if(isMC){
 
    T1->Branch("ngenjets01", &ngenjets01, "ngenjets01/I");
    T1->Branch("genjetpT01",genjetpT01,"genjetpT01[ngenjets01]/F");
    T1->Branch("genjetarea01",genjetarea01,"genjetarea01[ngenjets01]/F");
    T1->Branch("genjety01",genjety01,"genjety01[ngenjets01]/F");
    T1->Branch("genjetphi01",genjetphi01,"genjetphi01[ngenjets01]/F") ;
 
    T1->Branch("ngenjets02", &ngenjets02, "ngenjets02/I");
    T1->Branch("genjetpT02",genjetpT02,"genjetpT02[ngenjets02]/F");
    T1->Branch("genjetarea02",genjetarea02,"genjetarea02[ngenjets02]/F");
    T1->Branch("genjety02",genjety02,"genjety02[ngenjets02]/F");
    T1->Branch("genjetphi02",genjetphi02,"genjetphi02[ngenjets02]/F") ;
    
    T1->Branch("ngenjets03", &ngenjets03, "ngenjets03/I");
    T1->Branch("genjetpT03",genjetpT03,"genjetpT03[ngenjets03]/F");
    T1->Branch("genjetarea03",genjetarea03,"genjetarea03[ngenjets03]/F");
    T1->Branch("genjety03",genjety03,"genjety03[ngenjets03]/F");
    T1->Branch("genjetphi03",genjetphi03,"genjetphi03[ngenjets03]/F") ;
    
    T1->Branch("ngenjets04", &ngenjets04, "ngenjets04/I");
    T1->Branch("genjetpT04",genjetpT04,"genjetpT04[ngenjets04]/F");
    T1->Branch("genjetarea04",genjetarea04,"genjetarea04[ngenjets04]/F");
    T1->Branch("genjety04",genjety04,"genjety04[ngenjets04]/F");
    T1->Branch("genjetphi04",genjetphi04,"genjetphi04[ngenjets04]/F") ;
    
    T1->Branch("ngenjets05", &ngenjets05, "ngenjets05/I");
    T1->Branch("genjetpT05",genjetpT05,"genjetpT05[ngenjets05]/F");
    T1->Branch("genjetarea05",genjetarea05,"genjetarea05[ngenjets05]/F");
    T1->Branch("genjety05",genjety05,"genjety05[ngenjets05]/F");
    T1->Branch("genjetphi05",genjetphi05,"genjetphi05[ngenjets05]/F") ;
    
    T1->Branch("ngenjets06", &ngenjets06, "ngenjets06/I");
    T1->Branch("genjetpT06",genjetpT06,"genjetpT06[ngenjets06]/F");
    T1->Branch("genjetarea06",genjetarea06,"genjetarea06[ngenjets06]/F");
    T1->Branch("genjety06",genjety06,"genjety06[ngenjets06]/F");
    T1->Branch("genjetphi06",genjetphi06,"genjetphi06[ngenjets06]/F") ;
    
    T1->Branch("ngenjets07", &ngenjets07, "ngenjets07/I");
    T1->Branch("genjetpT07",genjetpT07,"genjetpT07[ngenjets07]/F");
    T1->Branch("genjetarea07",genjetarea07,"genjetarea07[ngenjets07]/F");
    T1->Branch("genjety07",genjety07,"genjety07[ngenjets07]/F");
    T1->Branch("genjetphi07",genjetphi07,"genjetphi07[ngenjets07]/F") ;
    
    T1->Branch("ngenjets08", &ngenjets08, "ngenjets08/I");
    T1->Branch("genjetpT08",genjetpT08,"genjetpT08[ngenjets08]/F");
    T1->Branch("genjetarea08",genjetarea08,"genjetarea08[ngenjets08]/F");
    T1->Branch("genjety08",genjety08,"genjety08[ngenjets08]/F");
    T1->Branch("genjetphi08",genjetphi08,"genjetphi08[ngenjets08]/F") ;
    
    T1->Branch("ngenjets09", &ngenjets09, "ngenjets09/I");
    T1->Branch("genjetpT09",genjetpT09,"genjetpT09[ngenjets09]/F");
    T1->Branch("genjetarea09",genjetarea09,"genjetarea09[ngenjets09]/F");
    T1->Branch("genjety09",genjety09,"genjety09[ngenjets09]/F");
    T1->Branch("genjetphi09",genjetphi09,"genjetphi09[ngenjets09]/F") ;
    
    T1->Branch("ngenjets10", &ngenjets10, "ngenjets10/I");
    T1->Branch("genjetpT10",genjetpT10,"genjetpT10[ngenjets10]/F");
    T1->Branch("genjetarea10",genjetarea10,"genjetarea10[ngenjets10]/F");
    T1->Branch("genjety10",genjety10,"genjety10[ngenjets10]/F");
    T1->Branch("genjetphi10",genjetphi10,"genjetphi10[ngenjets10]/F") ;
    
    T1->Branch("ngenjets11", &ngenjets11, "ngenjets11/I");
    T1->Branch("genjetpT11",genjetpT11,"genjetpT11[ngenjets11]/F");
    T1->Branch("genjetarea11",genjetarea11,"genjetarea11[ngenjets11]/F");
    T1->Branch("genjety11",genjety11,"genjety11[ngenjets11]/F");
    T1->Branch("genjetphi11",genjetphi11,"genjetphi11[ngenjets11]/F") ;
    
    T1->Branch("ngenjets12", &ngenjets12, "ngenjets12/I");
    T1->Branch("genjetpT12",genjetpT12,"genjetpT12[ngenjets12]/F");
    T1->Branch("genjetarea12",genjetarea12,"genjetarea12[ngenjets12]/F");
    T1->Branch("genjety12",genjety12,"genjety12[ngenjets12]/F");
    T1->Branch("genjetphi12",genjetphi12,"genjetphi12[ngenjets12]/F") ;
    
    
    for (int ij=0; ij<nHLTmx; ij++) { 
      sprintf(name, "Pileup_Vertices_%i",ij);
      sprintf(title, "Pileup Vertices (%s)", jethlt_name[ij]);
      PileupVertices[ij] = fs->make<TH1F>(name, title, 80, -0.5, 79.5);
    }
 
  } //isMC
  
      
       hist_pfmet = fs->make<TH1F>("MET_Value","MET Value",1000,0.0,2000.0) ; 
       hist_SumEt = fs->make<TH1F>("Sum_Et","Sum_Et",3500,0,3500.);
       hist_METbyET = fs->make<TH1F>("METbyEt","MET Value by pT Sum",100,0.0,1.0) ; 
       hist_weight = fs->make<TH1F>("weight_rec","Weight Record",100,-0.01,99.99);
  
  for(int ij=0;ij<nalgo;ij++){
    
    sprintf(name,"Scale_Factor_%s",JetRad[ij]);
    
    scale_factor[ij] = fs->make<TH1F>(name,title,1000000,0,10000);
    
    for (int jk=0;jk<netarange;jk++){	
	
		for (int rs=0; rs<njecmcmx; rs++){
			
			#ifdef JETEnergyScale	
			
			sprintf(name,"JetpT_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,rs);
			sprintf(title,"JetpT for %s %s JES %i",JetRad[ij],JetEta[jk],rs);
			
			#elif defined(JETRESO)
			
			sprintf(name,"JetpT_%s_EtaBin%i_JER%i",JetRad[ij],jk+1,rs);
			sprintf(title,"JetpT for %s %s JER %i",JetRad[ij],JetEta[jk],rs);
      
			#endif
      
			RecoJetpT[ij][jk][rs] = fs->make<TH1F>(name,title,noptbins,ptbins);
			RecoJetpT[ij][jk][rs]->Sumw2();
			}
			
      
      sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s",JetRad[ij],JetEta[jk]);
      
      JetpT[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
      JetpT[ij][jk]->Sumw2();
      
      sprintf(name,"Leading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Leading JetpT for %s %s" ,JetRad[ij],JetEta[jk]);
      
      LeadJetpT[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
      LeadJetpT[ij][jk]->Sumw2();
      
      sprintf(name,"DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
      DiJet_Mass[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
      DiJet_Mass[ij][jk]->Sumw2();
      
     
      for(int hl=0 ; hl<nHLTmx; hl++){
		  sprintf(name,"JetpT_%s_EtaBin%i_HLT%i",JetRad[ij],jk+1,hl+1);
		  sprintf(title,"JetpT for %s %s %s",JetRad[ij],JetEta[jk],jethlt_name[hl]);
		  
		  Prescale_JetpT[ij][jk][hl] = fs->make<TH1F>(name,title,noptbins,ptbins);
		  Prescale_JetpT[ij][jk][hl]->Sumw2();
		  
		  sprintf(name,"JetpT_%s_EtaBin%i_HLT%i_alljets",JetRad[ij],jk+1,hl+1);
		  sprintf(title,"JetpT for %s %s %s Alljets",JetRad[ij],JetEta[jk],jethlt_name[hl]);
		  
		  Prescale_JetpT_all[ij][jk][hl] = fs->make<TH1F>(name,title,noptbins,ptbins);
		  Prescale_JetpT_all[ij][jk][hl]->Sumw2();
		  
		  
		  }
      
      
      if(isMC){
		  
			sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
			sprintf(title,"Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
			GenMCJetpT[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
			GenMCJetpT[ij][jk]->Sumw2();
			
			sprintf(name,"Gen_MC_JetpT_Pow_%s_EtaBin%i",JetRad[ij],jk+1) ;
			sprintf(title,"Gen MC Jet pT Pow %s for %s",JetRad[ij],JetEta[jk]) ;
      
			GenMCJetpT_pow[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
			GenMCJetpT_pow[ij][jk]->Sumw2();
      
			sprintf(name,"Leading_Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
			sprintf(title,"Leading Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
			GenMCLeadJetpT[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
			GenMCLeadJetpT[ij][jk]->Sumw2();
			
			sprintf(name,"Gen_DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
			sprintf(title,"Gen_DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
			Gen_DiJet_Mass[ij][jk] = fs->make<TH1F>(name,title,noptbins,ptbins);
			Gen_DiJet_Mass[ij][jk]->Sumw2();
		  
		  if(isMC){
		    sprintf(name,"LeadJetRaio_%s_EtaBin%i",JetRad[ij],jk+1);
			sprintf(title,"Leading Jet Pt Ratio for %s EtaBin%i",JetRad[ij],jk+1);

			LeadJetRatio[ij][jk] = fs->make<TH1F>(name,title,500,-0.01,5.);
			LeadJetRatio[ij][jk]->Sumw2();
				}
		  
		  
		  for(int ip=0; ip<nnmx; ip++){
	 
	sprintf(name,"GenJetpT_%s_EtaBin%i_PDF%i",JetRad[ij],jk+1,ip);
	sprintf(title,"GenJetpT for %s %s PDF %i",JetRad[ij],JetEta[jk],ip);
	
	GenJetpT[ij][jk][ip] = fs->make<TH1F>(name,title,noptbins,ptbins);
	GenJetpT[ij][jk][ip]->Sumw2();
	
	sprintf(name,"Leading_GenJetpT_%s_EtaBin%i_PDF%i",JetRad[ij],jk+1,ip);
	sprintf(title,"Leading GenJetpT for %s %s PDF %i" ,JetRad[ij],JetEta[jk],ip);
	
	GenLeadJetpT[ij][jk][ip] = fs->make<TH1F>(name,title,noptbins,ptbins);
	GenLeadJetpT[ij][jk][ip]->Sumw2();
  }
	sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[ij],jk+1);
	sprintf(title,"RecoJetvsGenJet %s EtaBin%i ",JetRad[ij],jk+1);
	RecoVsGenJetpT[ij][jk] = fs->make<TH2F>(name,title,noptbins,ptbins,noptbins,ptbins);
	RecoVsGenJetpT[ij][jk]->Sumw2();
	
	RecoVsGenJetpT[ij][jk]->GetXaxis()->SetTitle("RECO Jet pT (in GeV)");
	RecoVsGenJetpT[ij][jk]->GetYaxis()->SetTitle("Gen Jet pT (in GeV)") ;
	
    for(int kl=0; kl<noptbins; kl++){
			
	sprintf(name,"Resolution_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"Resolution %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	Resolution[ij][jk][kl] = fs->make<TH1F>(name,title,150,-1.0,2.0);
	Resolution[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen[ij][jk][kl] = fs->make<TH1F>(name,title,360,0,3.6);
	DeltaR_RecoGen[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_Matrix_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR Matrix %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen_mat[ij][jk][kl] = fs->make<TH1F>(name,title,360,0,3.6);
	DeltaR_RecoGen_mat[ij][jk][kl]->Sumw2();
	 }
    }

	sprintf(name,"JEC_facor_%s_EtaBin%i",JetRad[ij],jk+1);
        printf(title,"JEC facor %s EtaBin %i",JetRad[ij],jk+1);
        JEC_fac[ij][jk] = fs->make<TH2F>(name,title,noptbins,ptbins,3000,0,3.);
        JEC_fac[ij][jk]->Sumw2();


   }//loop over jk (eta)
   
 /* 
        sprintf(name,"JEC_facor_%s",JetRad[ij]);
        printf(title,"JEC facor %s",JetRad[ij]);
        JEC_fac[ij] = fs->make<TH2F>(name,title,noptbins,ptbins,3000,0,3.);
        JEC_fac[ij]->Sumw2();
 */
   
    sprintf(name,"Jety_%s",JetRad[ij]);
    sprintf(title,"Jet Rapidity for %s",JetRad[ij]);
    
    Jeteta[ij] = fs->make<TH1F>(name,title,200,-5.0,5.0);
    Jeteta[ij]->Sumw2();
    
    sprintf(name,"Leading_Jety_%s",JetRad[ij]);
    sprintf(title,"Leading Jet Rapidity for %s",JetRad[ij]);
    
    LeadJeteta[ij] = fs->make<TH1F>(name,title,100,-5.0,5.0);
    LeadJeteta[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaR_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaR for %s",JetRad[ij]);
    
    Leading2JetsDeltaR[ij] = fs->make<TH1F>(name,title,100,0,8.0);
    Leading2JetsDeltaR[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaPhi_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaPhi for %s",JetRad[ij]);
    
    Leading2JetsDeltaPhi[ij] = fs->make<TH1F>(name,title,75,0,2*M_PI);
    Leading2JetsDeltaPhi[ij]->Sumw2();
    
    
    if(isMC){
      
      sprintf(name,"GenJety_%s",JetRad[ij]);
      sprintf(title,"GenJet Rapidity for %s",JetRad[ij]);
      
      GenJeteta[ij] = fs->make<TH1F>(name,title,200,-5.0,5.0);
      GenJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading_GenJety_%s",JetRad[ij]);
      sprintf(title,"Leading GenJet Rapidity for %s",JetRad[ij]);
      
      GenLeadJeteta[ij] = fs->make<TH1F>(name,title,100,-5.0,5.0);
      GenLeadJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaR_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaR for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaR[ij] = fs->make<TH1F>(name,title,100,0,8.0);
      GenLeading2JetsDeltaR[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaPhi_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaPhi for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaPhi[ij] = fs->make<TH1F>(name,title,75,0,2*M_PI);
      GenLeading2JetsDeltaPhi[ij]->Sumw2();
      
      sprintf(name,"Response_y_%s", JetRad[ij]);
	  sprintf(title,"Response Matrix in y for %s Jets",JetRad[ij]);
	  
	  Response_y[ij] = fs->make<TH2F>(name,title,100,0.,5.0,100,0.,5.0);
	  Response_y[ij]->Sumw2();
    }
  }
  

  for (int ij=0; ij<=nHLTmx; ij++) { 
	 
    sprintf(name, "nprimall_%i_trigset", ij);
    sprintf(title, "# of primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_hist[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_hist[ij]->Sumw2();

    sprintf(name, "nprimsel_%i_trigset", ij);
    sprintf(title, "Selected # of primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_sel[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_sel[ij]->Sumw2();

    sprintf(name, "nprimall_rewt_%i_trigset", ij);
    sprintf(title, "# of rewighted primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_hist_rewt[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_hist_rewt[ij]->Sumw2();

    sprintf(name, "nprimsel_rewt_%i_trigset", ij);
    sprintf(title, "Selected # of reweighted primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_sel_rewt[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_sel_rewt[ij]->Sumw2();
  }

  Nevt=0;
  irunold = -1;
  
  for (int ix=0; ix<32; ix++) { mypow_2[ix] = pow(2,ix);}
  
}


MCJetsMINIAOD_SingleRad::~MCJetsMINIAOD_SingleRad()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MCJetsMINIAOD_SingleRad::analyze(const edm::Event& iEvent, const edm::EventSetup& pset) {

  using namespace edm;
  Nevt++;

  irun = iEvent.id().run();
  ilumi = iEvent.luminosityBlock();
  
  ievt = iEvent.id().event();
  
  if (isMC) {
	  
	bool lhe_pdf = false;
	  
	#ifdef LHAPDF
    edm::Handle<LHEEventProduct> EvtHandle ;
    iEvent.getByToken( lheEventProductToken_ , EvtHandle ) ;
		
		if(EvtHandle.isValid()){
			lhe_pdf = true;
			if(lhe_pdf){
		for ( unsigned int weightIndex = 0; weightIndex < EvtHandle->weights().size(); ++weightIndex ) {
			if (weightIndex>=9 && weightIndex<=109) {
				pdfwt[weightIndex-9] = EvtHandle->weights()[weightIndex].wgt/EvtHandle->originalXWGTUP(); 
			//	std::cout<<"lhe index "<<weightIndex-9<<"   "<<pdfwt[weightIndex-9]<<endl ;
				}
			}
		}
			
	}
	
	#elif defined(GenPDF)

		 if(!(lhe_pdf)){	 
			 edm::Handle<GenEventInfoProduct> GenHandle;
			 iEvent.getByToken(GenEventProductToken_,GenHandle);
			 if(GenHandle.isValid()){
				 const std::vector<double>& genweights = GenHandle->weights();
				 for ( unsigned int weightIndex = 0; weightIndex < GenHandle->weights().size(); ++weightIndex ) {
						if (weightIndex>=10 && weightIndex<=110) {
						pdfwt[weightIndex-10] = genweights[weightIndex]*1./genweights[10]; 
						//std::cout<<"lhe index "<<weightIndex-10<<"   "<<pdfwt[weightIndex-10]<<endl ;
					}
				 }
			 }
		}
	
	#endif
	  	  
	wtfact = 1. ;

    edm::Handle<GenEventInfoProduct>eventinfo ;
    
    iEvent.getByToken(tok_wt_,eventinfo) ;
    
    if (eventinfo.isValid()){
   
      hist_weight->Fill(1.,eventinfo->weight());
     // cout<<"event weight "<<eventinfo->weight()<<endl ;
      wtfact = weight2*eventinfo->weight();
      event_weight = eventinfo->weight();
   //  cout<<" event weight "<<wtfact<<endl ;
     hist_weight->Fill(2,wtfact);
     pthat = eventinfo->qScale();
    } 
  } //isMC 

  for (int ij=0; ij<nHLTmx; ij++) { 
	  weighttrg[ij] = 1.0;
	  }

  
/*  if (Nevt%1000==1)*/ cout <<"HOinPFAlgo::analyze "<< Nevt<<" "<<iEvent.id().run()<<" "<<iEvent.id().event()<<" "<<iTag<<" "<<jtptthr<<endl;
   
 
  Handle<double> Rho_PF;
  
  iEvent.getByToken(tok_Rho_,Rho_PF);
  Rho = *Rho_PF;
 
  const char* variab1;
   
  edm::Handle<edm::TriggerResults> trigRes;
  iEvent.getByToken(triggerBits_, trigRes);
  
  const edm::TriggerNames &names = iEvent.triggerNames(*trigRes);

  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  iEvent.getByToken(triggerObjects_, triggerObjects);
  
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
  iEvent.getByToken(triggerPrescales_, triggerPrescales);
  
  //Calcualte Trigger Efficiency;
  
  int ihlttrg[nHLTmx+1]= {0,0,0,0,0,0,0,0,0,0,0};

  for (int jk=0; jk<nHLTmx; jk++) {
    for(unsigned ij = 0; ij<trigRes->size(); ++ij) {
      std::string name = names.triggerName(ij);
      variab1 = name.c_str(); 
      
       if (strstr(variab1,jethlt_name[jk]) && ((strlen(variab1)-strlen(jethlt_name[jk]))<5))
        {
		if ((trigRes->accept(ij))||(isMC)) {
			ihlttrg[jk] = ihlttrg[nHLTmx] = 1;
			}
        }
     }//ij 
    }//jk

  if (!isMC) {
    if (ihlttrg[nHLTmx]>0){
			wtfact = 1.0;///compres[ihlt];
		  } else { return ; } 
		}
   
   hist_weight->Fill(4.,wtfact);
  
   for (int ij=0; ij<nHLTmx; ij++) {
    weighttrg[ij] = wtfact;
    if (!isMC) { weighttrg[ij] *=compres[ij];
		         hist_weight->Fill(5.,compres[ij]);
		       }
   //  cout<<"trig "<<jethlt_name[ij]<<" wt "<<weighttrg[ij]<<endl;
		}//ij

  if (isMC) { 
	  
    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
    iEvent.getByToken(pileup_, PupInfo);
    int npu = -1;
    if (PupInfo.isValid()) {
      std::vector<PileupSummaryInfo>::const_iterator PVI;
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
		if (PVI->getBunchCrossing()==0) {
			npu = PVI->getPU_NumInteractions();
			break;
		}
      }
    }

    for (int ij=0; ij<nHLTmx; ij++) {
      if (ihlttrg[ij]>0) {
	PileupVertices[ij]->Fill(npu);
	
	if (npu<npileupmx) {
	//	cout<<"npu "<<npu<<" rat pileup "<<rat_pileup[ij][npu]<<endl;
	  weighttrg[ij] *=rat_pileup[ij][npu]; //[irecoht]
	  hist_weight->Fill(6.,rat_pileup[ij][npu]);
	} else {
			weighttrg[ij] *=rat_pileup[ij][npileupmx-1];
			hist_weight->Fill(6.,rat_pileup[ij][npileupmx-1]);
			}
		}
	   }//ij
    }//isMC
   else {  if(ihlttrg[nHLTmx]==0) { return; } }
   
 
  Handle<VertexCollection> primaryVertices;
  
  iEvent.getByToken(tok_primaryVertices_, primaryVertices); 

  if (primaryVertices.isValid()) {
    int ndofct=0;
    int nchict=0;
    int nvert = 0;
    for (reco::VertexCollection::const_iterator vert=primaryVertices->begin(); vert<primaryVertices->end(); vert++) {
      nvert++;
      if (vert->isValid() && !vert->isFake()) {
	if (vert->ndof()>7) { 
	  ndofct++;
	  if (vert->normalizedChi2()<5) nchict++;
		}
      }
    }
    nprim = min(99,nvert) + 100*min(99,ndofct) + 10000*min(99,nchict);
    
    for (int ij=0; ij<=nHLTmx; ij++) {
      if (ihlttrg[ij]>0) { 
	prim_hist[ij]->Fill(nvert, wtfact);
	prim_sel[ij]->Fill(nchict, wtfact);
	
	prim_hist_rewt[ij]->Fill(nvert, weighttrg[ij]);
	prim_sel_rewt[ij]->Fill(nchict, weighttrg[ij]);
      }
	}	
  } else { nprim = 0;}


  edm::Handle<edm::View<pat::Jet>/*reco::PFJetCollection*/> PFJets[nalgo];
  edm::Handle<reco::GenJetCollection> GenJets[nalgo];

  vector<double> recojetptx[nalgo][njecmcmx];
  vector<double> recojetscl[nalgo][njecmcmx];
  vector<int> recojetindx[nalgo][njecmcmx];

	for(int ix=0; ix<nalgo; ix++){
	
	iEvent.getByToken(tok_pfjets_[ix], PFJets[ix]);
	
	for (unsigned jet = 0; jet<PFJets[ix]->size(); jet++) {
	  
	  HepLorentzVector pfjet4v((*PFJets[ix])[jet].px(),(*PFJets[ix])[jet].py(),(*PFJets[ix])[jet].pz(), (*PFJets[ix])[jet].energy());
	  
	  double tmprecpt = pfjet4v.perp();
	  double tmpreceta = pfjet4v.eta();
	  double tmprecarea = (*PFJets[ix])[jet].jetArea();
	 
	  double total_cor = 1. ;
	  
	  if(ix<=5){
	  
	  jecL1FastAK4->setJetPt(tmprecpt); 
	  jecL1FastAK4->setJetA(tmprecarea);
      jecL1FastAK4->setRho(*Rho_PF);
      jecL1FastAK4->setJetEta(tmpreceta);
      
      double corFactorL1Fast = jecL1FastAK4->getCorrection();
      total_cor*= corFactorL1Fast;
      tmprecpt = tmprecpt * corFactorL1Fast;
      //cout<<"L1 "<<corFactorL1Fast<<endl;
      
      jecL2RelativeAK4->setJetPt(tmprecpt);
      jecL2RelativeAK4->setJetEta(tmpreceta);
      
      double corFactorL2Relative = jecL2RelativeAK4->getCorrection();
      total_cor*= corFactorL2Relative ;
      tmprecpt = tmprecpt * corFactorL2Relative;
      //cout<<" L2 "<<corFactorL2Relative<<endl;
      
      jecL3AbsoluteAK4->setJetPt(tmprecpt); 
	  jecL3AbsoluteAK4->setJetEta(tmpreceta);
	  
	  double corFactorL3Absolute = jecL3AbsoluteAK4->getCorrection();
	  total_cor*= corFactorL3Absolute ;
	  tmprecpt = tmprecpt * corFactorL3Absolute;
	//  cout<<" L3 "<<corFactorL3Absolute<<endl;
	  
	  if(!isMC){
		  double corFactorL2L3Residual;
		  
		  jecL2L3ResidualAK4->setJetPt(tmprecpt);
		  jecL2L3ResidualAK4->setJetEta(tmpreceta);
    
		  corFactorL2L3Residual = jecL2L3ResidualAK4->getCorrection();
		  total_cor*= corFactorL2L3Residual;
          tmprecpt *=corFactorL2L3Residual;
          //cout<<" L2L3 "<<corFactorL2L3Residual<<endl;
		  }
	  	}//ix<=5
	  	else{
			    jecL1FastAK8->setJetPt(tmprecpt); 
				jecL1FastAK8->setJetA(tmprecarea);
				jecL1FastAK8->setRho(*Rho_PF);
				jecL1FastAK8->setJetEta(tmpreceta);
      
				double corFactorL1Fast = jecL1FastAK8->getCorrection();
				total_cor*= corFactorL1Fast;
				tmprecpt = tmprecpt * corFactorL1Fast;
			//	cout<<"L1 "<<corFactorL1Fast<<endl;
      
				jecL2RelativeAK8->setJetPt(tmprecpt);
				jecL2RelativeAK8->setJetEta(tmpreceta);
      
				double corFactorL2Relative = jecL2RelativeAK8->getCorrection();
				total_cor*= corFactorL2Relative ;
				tmprecpt = tmprecpt * corFactorL2Relative;
			//	cout<<" L2 "<<corFactorL2Relative<<endl;
      
				jecL3AbsoluteAK8->setJetPt(tmprecpt); 
				jecL3AbsoluteAK8->setJetEta(tmpreceta);
	  
				double corFactorL3Absolute = jecL3AbsoluteAK8->getCorrection();
				total_cor*= corFactorL3Absolute ;
				tmprecpt = tmprecpt * corFactorL3Absolute;
			//	cout<<" L3 "<<corFactorL3Absolute<<endl;
	  
				if(!isMC){
				double corFactorL2L3Residual;
		  
				jecL2L3ResidualAK8->setJetPt(tmprecpt);
				jecL2L3ResidualAK8->setJetEta(tmpreceta);
    
				corFactorL2L3Residual = jecL2L3ResidualAK8->getCorrection();
				total_cor*= corFactorL2L3Residual;
				tmprecpt *=corFactorL2L3Residual;
			//	cout<<" L2L3 "<<corFactorL2L3Residual<<endl;
				}
			}//else  
	  	  
	  	  
	 // 	  cout<<"algo"<<ix+1<<" jet "<<jet+1<<" correction factor "<<total_cor<<endl;
	  	  
	  	  
	  for(int isrc =0 ; isrc<njecmcmx; isrc++){
		  
		  double sup = 1.0 ;
		  
		  #ifdef JETEnergyScale
		  
		  if((isrc>0)&&(isrc<=nsrc)){
				JetCorrectionUncertainty *jecUnc = vsrc[isrc-1];
				jecUnc->setJetEta(tmpreceta);
				jecUnc->setJetPt(tmprecpt);
	
				sup += jecUnc->getUncertainty(true);
			}
			else if(isrc>nsrc){
				JetCorrectionUncertainty *jecUnc = vsrc[isrc-1-nsrc];
				jecUnc->setJetEta(tmpreceta);
				jecUnc->setJetPt(tmprecpt);
	
				sup -= jecUnc->getUncertainty(false);
				}
		 
		 #elif defined(JETRESO)	

			JME::JetResolution resolution;
			if(ix<=5){	resolution = JME::JetResolution("Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt"); }  // resolution file 
				else  { resolution = JME::JetResolution("Spring16_25nsV6_MC_PtResolution_AK8PFchs.txt"); }
	  
				JME::JetResolutionScaleFactor res_sf;
			if(ix<=5){	 res_sf = JME::JetResolutionScaleFactor("Spring16_25nsV6_MC_SF_AK4PFchs.txt"); }    //scale factor file
				else  {  res_sf = JME::JetResolutionScaleFactor("Spring16_25nsV6_MC_SF_AK8PFchs.txt");}
      
				double reso = 1 ;
		 
				JME::JetParameters parameters_5 = {{JME::Binning::JetPt, tmprecpt}, {JME::Binning::JetEta, tmpreceta}, {JME::Binning::Rho, *Rho_PF}};
				double rp = resolution.getResolution(parameters_5);
				double sf = res_sf.getScaleFactor({{JME::Binning::JetEta, tmpreceta}}, Variation::NOMINAL);
				double sf_up= res_sf.getScaleFactor({{JME::Binning::JetEta, tmpreceta}}, Variation::UP);
				double sf_dn= res_sf.getScaleFactor({{JME::Binning::JetEta, tmpreceta}}, Variation::DOWN);
		 
				if(isrc==0) { reso = sqrt(max(0.,(sf*sf-1))*rp);}
				else if(isrc==1) {reso = sqrt(max(0.,(sf_up*sf_up-1))*rp);}
				else if(isrc==2) {reso = sqrt(max(0.,(sf_dn*sf_dn-1))*rp);}	
			
				sup = gRandom->Gaus(1.0, reso);	
				
		 	    #endif
				
				if((total_cor<1.e-7)||(total_cor>1.e3)){total_cor = 1.;}
				
				recojetptx[ix][isrc].push_back(sup*tmprecpt);
				recojetscl[ix][isrc].push_back(sup*total_cor);
				recojetindx[ix][isrc].push_back(jet);
		  
			} // loop over isrc
		} // loop over jet no
	} // loop over ix
	
	// now shuffle 
	
	for(int ix=0 ; ix<nalgo; ix++) { 
	    for (int isrc = 0; isrc < njecmcmx; isrc++) {
	 	if(recojetptx[ix][isrc].size()>1) { 
		for (unsigned int ij=0; ij<recojetptx[ix][isrc].size()-1; ij++) {
			for (unsigned int jk=ij+1; jk<recojetptx[ix][isrc].size(); jk++) {
				
				if (recojetptx[ix][isrc][jk]>recojetptx[ix][isrc][ij]) {
					
					double tmppt = recojetptx[ix][isrc][ij];
					double tmpscl = recojetscl[ix][isrc][ij];
					int tmpindx = recojetindx[ix][isrc][ij];

					recojetptx[ix][isrc][ij] = recojetptx[ix][isrc][jk];
					recojetscl[ix][isrc][ij] = recojetscl[ix][isrc][jk];
					recojetindx[ix][isrc][ij] = recojetindx[ix][isrc][jk];					
		
					recojetptx[ix][isrc][jk] = tmppt;
					recojetscl[ix][isrc][jk] = tmpscl;
					recojetindx[ix][isrc][jk] = tmpindx;
				  }
			  } //jk
		  } //ij
	 	}
   	} // nsrc	
 }// loop over ix (algo no)


  if(recojetptx[7][0].size()==0) return ;
  
  int tmpptbin = getbinid(recojetptx[7][0][0], nHLTmx, leadingPtThreshold); //leading AK8 jet is used to fill the  met, SumET, MET/Sum_ET histograms

  edm::Handle<pat::METCollection> pfmet_ ; 
  iEvent.getByToken(tok_mets_,pfmet_) ;
  
  miset = misphi = -1000 ;
  
  
  if(pfmet_.isValid()){
	  miset = pfmet_->begin()->corPt();
	  misphi = pfmet_->begin()->corPhi(); 
	  sumEt = pfmet_->begin()->corSumEt() ; 
	  if(sumEt<1.) { sumEt = 1.; } 
	  }
	  
	  if((tmpptbin>=0)&&(tmpptbin<nHLTmx)&&(ihlttrg[tmpptbin]>0)){
		  hist_pfmet->Fill(miset,weighttrg[tmpptbin]) ;
		  hist_METbyET->Fill(miset*1.0/sumEt,weighttrg[tmpptbin]) ;
		  hist_SumEt->Fill(sumEt,weighttrg[tmpptbin]) ;
		  }
	  
	  
	  if((miset*1.0/sumEt)>0.3) return ;


  for(int ix=0 ; ix<nalgo ; ix++) {
	  
    npfjets[ix] = 0;
    
    int tmpptbin = -1;
 
    if(PFJets[ix].isValid()) {

      for (unsigned jet1 = 0; jet1<PFJets[ix]->size(); jet1++) {

        int jet = recojetindx[ix][0][jet1];

	HepLorentzVector jet4v((*PFJets[ix])[jet].px(),(*PFJets[ix])[jet].py(),(*PFJets[ix])[jet].pz(), (*PFJets[ix])[jet].energy());
	scale_factor[ix]->Fill(recojetscl[ix][0][jet]);
	jet4v *= recojetscl[ix][0][jet1] ;

	double jec_factor = recojetscl[ix][0][jet1];

        double tmppt = jet4v.perp();
        double tmpeta = jet4v.eta();
        double tmpy = jet4v.rapidity();

	if (tmppt<ptbins[0]) continue;
  	if (abs(tmpy)>4.7) continue;
    
	//Jet ID =================
	double NHF = (*PFJets[ix])[jet].neutralHadronEnergyFraction();
	double NEMF = (*PFJets[ix])[jet].neutralEmEnergyFraction();
	double CHF = (*PFJets[ix])[jet].chargedHadronEnergyFraction();
	double CEMF = (*PFJets[ix])[jet].chargedEmEnergyFraction();
	double MUF = (*PFJets[ix])[jet].muonEnergyFraction();
	double PHF = (*PFJets[ix])[jet].photonEnergyFraction();
	int NumConst = (*PFJets[ix])[jet].chargedMultiplicity()+(*PFJets[ix])[jet].neutralMultiplicity();
	int NumNeutralParticles =(*PFJets[ix])[jet].neutralMultiplicity();
	int CHM = (*PFJets[ix])[jet].chargedHadronMultiplicity();
	int NHM = (*PFJets[ix])[jet].neutralHadronMultiplicity();
	int MUM = (*PFJets[ix])[jet].muonMultiplicity();
	int PHM = (*PFJets[ix])[jet].photonMultiplicity();
	int CEMM =(*PFJets[ix])[jet].chargedMultiplicity()-(*PFJets[ix])[jet].chargedHadronMultiplicity()-(*PFJets[ix])[jet].muonMultiplicity();
	int NEMM =(*PFJets[ix])[jet].neutralMultiplicity()-(*PFJets[ix])[jet].neutralHadronMultiplicity();

   // cout<<"charged hadron "<<CHM<<" neutral hadron "<<NHM<<" no. neutral particles "<<NumNeutralParticles<<" total hadron "<<NumConst<<endl;
    
      if((jet1==0)&&(recojetptx[7][0].size()>0)){
		tmpptbin = getbinid(recojetptx[7][0][0], nHLTmx, leadingPtThreshold);
		 }
     if((tmpptbin<0)||(tmpptbin>=nHLTmx)) break ;
 

    // JEC_fac[ix]->Fill(tmppt,jec_factor,weighttrg[tmpptbin]);

     int ybin_tag = getbinid(abs(tmpy),netarange,etarng);
     int ptbin_tag  = getbinid(tmppt,nopbins,pbins);
     
     if((ybin_tag<0)||(ybin_tag>=netarange)) continue;
     if((ptbin_tag<0)||(ptbin_tag>=nopbins)) continue;
     
		JEC_fac[ix][ybin_tag]->Fill(tmppt,jec_factor,weighttrg[tmpptbin]);
	
//	bool looseJetID = false;
	bool tightJetID =false;
//	bool tightlepVeto = false;
	
	if(abs(tmpeta)<=2.7){
		if( (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || (abs(tmpeta)>2.4)) ){
			tightJetID = true;
			}
	//	if( (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || (abs(tmpeta)>2.4)) && (abs(tmpeta)<=2.7) ){
	//		looseJetID = true;
	//		}
	//	if( (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.9) || (abs(tmpeta)>2.4)) && (abs(tmpeta)<=2.7) ){
	//		tightlepVeto = true;
	//		}		
		}
		else{
			if((abs(tmpeta)>2.7)&&(abs(tmpeta)<3.0)){
				#ifdef Data2015 
				 if( (NEMF<0.90) && (NumNeutralParticles>2)){tightJetID = true; /*looseJetID = true;*/ } 
				#elif defined(Data2016)   
				if( (NEMF>0.01) && (NHF<0.98) && (NumNeutralParticles>2)){tightJetID = true; /*looseJetID = true;*/ } 
				#endif
				}
				else{
					if ((NEMF<0.90) && (NumNeutralParticles>10)){tightJetID = true; /*looseJetID = true;*/}
					}
			}
	
	if( jet1==0 && !tightJetID) break;
	if (!tightJetID) continue;
	
	if(jet1==0) { 
	iRecoPTbin[ix] = getbinid(recojetptx[ix][0][0], nHLTmx, leadingPtThreshold); 
	if((iRecoPTbin[ix]<0)||(iRecoPTbin[ix]>=nHLTmx)) break;
	
	 if(isMC){
				float leadjetratio = recojetptx[ix][0][0]*1./pthat;
              //  cout<<"leadjetratio "<<leadjetratio<<endl;
                LeadJetRatio[ix][ybin_tag]->Fill(leadjetratio,weighttrg[iRecoPTbin[ix]]) ;
                if(leadjetratio > 3.) break ;
			}
    }

	
		
	int etatag=-1 ;
	etatag = getbinid(abs(tmpy),netarange,etarng);
	
	if((etatag>netarange)||(etatag<0)) continue;
	
	pfjetmom[ix][npfjets[ix]] = jet4v.rho();
	pfjetpT[ix][npfjets[ix]] = jet4v.perp();
	pfjetenr[ix][npfjets[ix]] = jet4v.e();
	pfjetthe[ix][npfjets[ix]] = jet4v.theta();
	pfjety[ix][npfjets[ix]] = jet4v.rapidity();
	pfjetphi[ix][npfjets[ix]]= jet4v.phi();
	pfjetpz[ix][npfjets[ix]] = jet4v.pz();
	pfjetarea[ix][npfjets[ix]] = (*PFJets[ix])[jet].jetArea() ;   
	/*
	if (jet1==0) { 
	  iRecoPTbin[ix] = getbinid(recojetptx[ix][0][0], nHLTmx, leadingPtThreshold);
	}
	*/
	hist_weight->Fill(7.,iRecoPTbin[ix]);
	
	if (iRecoPTbin[ix]<0 || iRecoPTbin[ix]>=nHLTmx || ihlttrg[iRecoPTbin[ix]]==0) break;

    hist_weight->Fill(8.,weighttrg[iRecoPTbin[ix]]);
     
	Jeteta[ix]->Fill(tmpy, weighttrg[iRecoPTbin[ix]]);
	
	
	if(etatag>=0) {
		
			JetpT[ix][etatag]->Fill(tmppt, weighttrg[iRecoPTbin[ix]]);

			for(int isrc=0; isrc<njecmcmx; isrc++){
				int ptbinxx = getbinid(recojetptx[ix][isrc][0],nHLTmx,leadingPtThreshold);
				
				if((ptbinxx<0)||(ptbinxx>=nHLTmx)) continue;
				RecoJetpT[ix][etatag][isrc]->Fill(recojetptx[ix][isrc][npfjets[ix]],weighttrg[iRecoPTbin[ix]]);//[iRecoPTbin[ix]]);
												 }
					
				if(jet1==0) { Prescale_JetpT[ix][etatag][iRecoPTbin[ix]]->Fill(tmppt);}
				Prescale_JetpT_all[ix][etatag][iRecoPTbin[ix]]->Fill(tmppt);
		     }
	
	if (++npfjets[ix] >=njetmx) break;
 
    }//jet1
      
 
   if(npfjets[ix]>0) {
		
	  int   etatag = -1;
	  etatag = getbinid(abs(pfjety[ix][0]),netarange,etarng);  
	  
	  if(etatag>=0) {
	  LeadJetpT[ix][etatag]->Fill(pfjetpT[ix][0],weighttrg[iRecoPTbin[ix]]);
		}
	  LeadJeteta[ix]->Fill(pfjety[ix][0],weighttrg[iRecoPTbin[ix]]) ;
	  
	  if(npfjets[ix]>1)    {
	    Leading2JetsDeltaR[ix]->Fill(delta2R(pfjety[ix][0],pfjetphi[ix][0],pfjety[ix][1],pfjetphi[ix][1]),weighttrg[iRecoPTbin[ix]]); 
	    Leading2JetsDeltaPhi[ix]->Fill(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]),weighttrg[iRecoPTbin[ix]]);
					}  
		}//npfjets[ix]>0
		
		 if(npfjets[ix]>=2){
			
			if((npfjets[ix]==2)||((npfjets[ix]>2)&&(pfjetpT[ix][2]<50.))){
			double p4[3]={0};
		
			if(abs(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]))>(2*M_PI/3.)){
				for(int jt=0; jt<2; jt++){
					p4[0]+=pfjetenr[ix][jt];
					p4[1]+=pfjetpT[ix][jt];
					p4[2]+=pfjetpz[ix][jt];
				    }
			
			double refy ;
			 if(abs(pfjety[ix][0])>abs(pfjety[ix][1])){ refy = abs(pfjety[ix][0]);}
			 else { refy = abs(pfjety[ix][1]); }
			int etatag = getbinid(refy,netarange,etarng)  ; 
			
			if(etatag>=0) {
				double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
				DiJet_Mass[ix][etatag]->Fill(mass,weighttrg[iRecoPTbin[ix]]);	
						}
					}//phi condn
				}
			}//npfjets[ix]>=2
    }
    
    if (isMC) {
      
      ngenjets[ix] = 0;
      iEvent.getByToken(tok_genjets_[ix], GenJets[ix]);
 
      if (GenJets[ix].isValid()) {
	
		for (unsigned jet = 0; jet<GenJets[ix]->size(); jet++) {
		
		HepLorentzVector genjet4v((*GenJets[ix])[jet].px(),(*GenJets[ix])[jet].py(),(*GenJets[ix])[jet].pz(), (*GenJets[ix])[jet].energy());
		
		double tmpgenpt = genjet4v.perp();
	//  double tmpgeneta = genjet4v.eta();
		double tmpgeny = genjet4v.rapidity();
		
		if (tmpgenpt<ptbins[0]/*leadingPtThreshold[0]*/) continue;
		if (abs(tmpgeny)>4.7) continue;

		genjetmom[ix][ngenjets[ix]] = genjet4v.rho() ;
		genjetpT[ix][ngenjets[ix]] = genjet4v.perp() ;
		genjetenr[ix][ngenjets[ix]] = genjet4v.e() ;
		genjetthe[ix][ngenjets[ix]] = genjet4v.theta();
		genjety[ix][ngenjets[ix]] = genjet4v.rapidity();
		genjetphi[ix][ngenjets[ix]]= genjet4v.phi();
		genjetpz[ix][ngenjets[ix]] = genjet4v.pz();
		genjetarea[ix][ngenjets[ix]] = (*GenJets[ix])[jet].jetArea() ;
 
		if (jet==0) { 
			iGenPTbin[ix] = getbinid(tmpgenpt, nHLTmx, leadingPtThreshold);
			if (iGenPTbin[ix]<0 || iGenPTbin[ix]>=nHLTmx || ihlttrg[iGenPTbin[ix]]==0) break;
		}
	
			hist_weight->Fill(9.,iGenPTbin[ix]);
	  
	        hist_weight->Fill(10.,weighttrg[iGenPTbin[ix]]);
	  
			GenJeteta[ix]->Fill(tmpgeny, weighttrg[iGenPTbin[ix]]);
	  
			int etatag=-1 ;
			etatag = getbinid(abs(tmpgeny),netarange,etarng);
	  
			if(etatag>=0) {
		  
			GenMCJetpT[ix][etatag]->Fill(tmpgenpt,weighttrg[iGenPTbin[ix]]) ;
			cout<<"gen pt "<<tmpgenpt<<endl;
			GenMCJetpT_pow[ix][etatag]->Fill(tmpgenpt,tmpgenpt*weighttrg[iGenPTbin[ix]]) ;
		     cout<<"pow "<<tmpgenpt*weighttrg[iGenPTbin[ix]]<<endl;
	
			#ifdef LHAPDF		  
			for(int ipdf=0 ; ipdf<nnmx; ipdf++) {  
				GenJetpT[ix][etatag][ipdf]->Fill(tmpgenpt,weighttrg[iGenPTbin[ix]]*pdfwt[ipdf]);
				}
			#elif defined(GenPDF)
			for(int ipdf=0 ; ipdf<nnmx; ipdf++) {  
				GenJetpT[ix][etatag][ipdf]->Fill(tmpgenpt,weighttrg[iGenPTbin[ix]]*pdfwt[ipdf]);
				}
			#endif
			}
	  
			if (++ngenjets[ix] >=njetmx) break;
	
		}//jet
      
      if(ngenjets[ix]>0) {
		
		int   etatag = -1;
		etatag = getbinid(abs(genjety[ix][0]),netarange,etarng);
		
		if(etatag>=0) {
		
		GenMCLeadJetpT[ix][etatag]->Fill(genjetpT[ix][0]) ;
	  
			for(int ipdf=0 ; ipdf<nnmx; ipdf++) {
				GenLeadJetpT[ix][etatag][ipdf]->Fill(genjetpT[ix][0], weighttrg[iGenPTbin[ix]]*pdfwt[ipdf]);
				}
	
			GenLeadJeteta[ix]->Fill(genjety[ix][0], weighttrg[iGenPTbin[ix]]) ;

			GenpT[ix] = genjetpT[ix][0] ;
	  
			if(ngenjets[ix]>1) {
			GenLeading2JetsDeltaR[ix]->Fill(delta2R(genjety[ix][0], genjetphi[ix][0],genjety[ix][1],genjetphi[ix][1]), weighttrg[iGenPTbin[ix]]); 
			GenLeading2JetsDeltaPhi[ix]->Fill(PhiInRange(genjetphi[ix][0]-genjetphi[ix][1]), weighttrg[iGenPTbin[ix]]);
			} 
		}  
       } //if(ngenjets[ix]>0)
       
       
        if(ngenjets[ix]>=2){
			
			if((ngenjets[ix]==2)||((ngenjets[ix]>2)&&(genjetpT[ix][2]<50.))){
			
			double p4[3]={0};
			
			if(abs(genjetphi[ix][0]-genjetphi[ix][1])>(2*M_PI/3.)){
				for(int jt=0; jt<2; jt++){
					p4[0]+=genjetenr[ix][jt];
					p4[1]+=genjetpT[ix][jt];
					p4[2]+=genjetpz[ix][jt];
				    }
			double refy ;
			 if(abs(genjety[ix][0])>abs(genjety[ix][1])){ refy = abs(genjety[ix][0]);}
			 else { refy = abs(genjety[ix][1]); }
			int etatag = getbinid(refy,netarange,etarng)  ; 
			
			if(etatag>=0){
			double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
			Gen_DiJet_Mass[ix][etatag]->Fill(mass,weighttrg[iGenPTbin[ix]]);		
						}
					}//phi condn
				}
			}//npfjets[ix]>=2
       
     } //if (GenJets[ix].isValid())
 
//// ====== Resolution ==============
 
    double deltaR_min = 0.5*(ix+1)*0.1;
 
	for(int reco = 0; reco<npfjets[ix]; reco++){
		
		deltaR_min = 0.75*(ix+1)*0.1;
		int match_gen = -1;
		
		for(int gen = 0; gen<ngenjets[ix]; gen++){
			
			int geneta_tag = -1;
			geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
			int genpt_tag = -1;
			genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);
			
			if((geneta_tag<0)||(genpt_tag<0)) continue ;
			
			double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
			
			if((genjetpT[ix][gen]>0.5*(pfjetpT[ix][reco]))&&(genjetpT[ix][gen]<2.*(pfjetpT[ix][reco]))){
			DeltaR_RecoGen[ix][geneta_tag][genpt_tag]->Fill(delR_rg/*,weighttrg[iGenPTbin[ix]]*/) ;
			}
			
			if(delR_rg < deltaR_min) { deltaR_min = delR_rg ; match_gen = gen; }
			
		}//gen
			
				int gen = match_gen;
			   
			if(gen>=0){
					
				int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
				int genpt_tag =  getbinid(genjetpT[ix][gen],noptbins,ptbins);	
					
				if((geneta_tag>=0)&&(genpt_tag>=0)){	
				double res_pt = 0;
				res_pt = (pfjetpT[ix][reco] - genjetpT[ix][gen])*1.0/genjetpT[ix][gen]; // (RecopT[ix] - GenpT[ix])*1.0/(GenpT[ix]) ;
				int nbins = Resolution[ix][geneta_tag][genpt_tag]->GetNbinsX();
				if(res_pt<(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(0))) {
				res_pt = (Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(0))+0.0001;
				}else {
				if(res_pt>(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1))) {
				res_pt = Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1) -0.0001;
						}
				      }
				
			Resolution[ix][geneta_tag][genpt_tag]->Fill(res_pt/*,weighttrg[iGenPTbin[ix]]*/) ;
				}
			}
	}//reco
				 
//// ====== Resolution End ==========	

////   =======Response Matrix ===========
	
	if ((iRecoPTbin[ix]>=0 && iRecoPTbin[ix]<nHLTmx && ihlttrg[iRecoPTbin[ix]]>0) && 
	    (iGenPTbin[ix]>=0 && iGenPTbin[ix]<nHLTmx && ihlttrg[iGenPTbin[ix]]>0)) {
	  
	  for(int reco = 0; reco<npfjets[ix]; reco++) { 
	    int receta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	    if ((receta_tag<0)||(receta_tag>=netarange)) continue;
	    
	    bool ismatched =false;
	    
	    double min_deltaR = 100.;
	    double pfjetpt = -100;
	    double genjetpt = -100;
	    
	    int geneta_tag = -1;
	    int genpt_tag = -1;		
	    int tmpgeneta_tag = -1;	//170515

	    for(int gen = 0; gen<ngenjets[ix]; gen++){
	      
	      geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	      genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);
	      
	      if ((geneta_tag>=0)&&(geneta_tag<netarange)&&(genpt_tag>=0)&&(genpt_tag<noptbins)) {
		
		double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
		if(delR_rg>(0.05*(ix+1))) continue ;
		
		if( delR_rg < 	min_deltaR) { 
		  min_deltaR = delR_rg ; 
		  pfjetpt = pfjetpT[ix][reco];
		  genjetpt = genjetpT[ix][gen];
		  tmpgeneta_tag = geneta_tag;
		  ismatched = true;
		}		
	      }		
	    }//gen
	    
	    if (ismatched) { 	
	      if (tmpgeneta_tag == receta_tag) { //170515
		RecoVsGenJetpT[ix][tmpgeneta_tag]->Fill(pfjetpt,genjetpt,weighttrg[iGenPTbin[ix]]) ; //170515
	      }
	      else{
		if(receta_tag>=0) {
		  RecoVsGenJetpT[ix][receta_tag]->Fill(pfjetpt,-1.,weighttrg[iRecoPTbin[ix]]) ;
		}
		
		if(tmpgeneta_tag>=0){
		  RecoVsGenJetpT[ix][tmpgeneta_tag]->Fill(-1.,genjetpt,weighttrg[iGenPTbin[ix]]) ; //170515
		}
	      }
	      break;
	    }
	    
	    if (!ismatched) { 
	      if(receta_tag>=0) {
		RecoVsGenJetpT[ix][receta_tag]->Fill(pfjetpT[ix][reco],-1.,weighttrg[iRecoPTbin[ix]]) ;
	      }
	    }
	  }//reco	
	  
	  for(int gen = 0; gen<ngenjets[ix]; gen++){
	    int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	    if (geneta_tag<0) continue;
	    bool ismatched =false;
	    for(int reco = 0; reco<npfjets[ix]; reco++) { 
	      int receta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	      
	      if ((receta_tag>=0)&&(receta_tag<netarange)) {
		double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
		if(delR_rg>(0.05*(ix+1))) continue ; 
		ismatched =true; break;
	      }
	    }//reco
	    if (!ismatched) { 
	      if(geneta_tag>=0) {
		RecoVsGenJetpT[ix][geneta_tag]->Fill(-1, genjetpT[ix][gen],weighttrg[iGenPTbin[ix]]) ;
	      }
	    }
	  }//gen
	  
	} else {
	  if(iRecoPTbin[ix]>=0 && iRecoPTbin[ix]<nHLTmx && ihlttrg[iRecoPTbin[ix]]>0){
	    for(int reco = 0; reco<npfjets[ix]; reco++){
	      int receta_tag = -1;
	      receta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	      if(receta_tag>0) {RecoVsGenJetpT[ix][receta_tag]->Fill(pfjetpT[ix][reco],-1.,weighttrg[iRecoPTbin[ix]]) ;}
	    }//reco
	  } else if(iGenPTbin[ix]>=0 && iGenPTbin[ix]<nHLTmx && ihlttrg[iGenPTbin[ix]]>0){
	    for(int gen = 0; gen<ngenjets[ix]; gen++){
	      int geneta_tag = -1;
	      geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	      if(geneta_tag>=0){ RecoVsGenJetpT[ix][geneta_tag]->Fill(-1.,genjetpT[ix][gen],weighttrg[iGenPTbin[ix]]) ;}
	    } //gen
	  }
	}
	
	
	//// ======= Response Matrix End ===================	


//// ===== Response Matrix for Rapidity Starts Here =========

if ((iRecoPTbin[ix]>=0 && iRecoPTbin[ix]<nHLTmx && ihlttrg[iRecoPTbin[ix]]>0) && 
				(iGenPTbin[ix]>=0 && iGenPTbin[ix]<nHLTmx && ihlttrg[iGenPTbin[ix]]>0)) {
					
			for(int reco = 0; reco<npfjets[ix]; reco++) { 
				
				bool ismatched =false;
						
				int recopt_tag = getbinid(pfjetpT[ix][reco],noptbins,ptbins);	
				
				double pseudo_pfy = -100.;
			    double pseudo_geny = -100.;
					
				for(int gen = 0; gen<ngenjets[ix]; gen++){
							
					double delphi = PhiInRange(pfjetphi[ix][reco]-genjetphi[ix][gen]);
				    double deltapt = (pfjetpT[ix][reco]-genjetpT[ix][gen])/genjetpT[ix][gen] ;
				   
					int genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);
				
					if (genpt_tag>=0) {
						
						double miny = 100.;
					
					if((deltapt>(-0.5))&&(deltapt<1.)&&(abs(delphi)<(0.05*(ix+1)))){
						   if(abs(pfjety[ix][reco]-genjety[ix][gen])<miny) {
							   miny = abs(pfjety[ix][reco]-genjety[ix][gen]) ;
							   pseudo_pfy = abs(pfjety[ix][reco]);
							   pseudo_geny = abs(genjety[ix][gen]) ;
							   }
					      
					       ismatched =true;
					       }
								
							// break;
					}// if (genpt_tag>=0)
				}//gen
				
				if(ismatched) {   Response_y[ix]->Fill(pseudo_pfy,pseudo_geny,weighttrg[iGenPTbin[ix]]) ; }
				
				if (!ismatched) { 
				  if(recopt_tag>=0) {
						Response_y[ix]->Fill(abs(pfjety[ix][reco]),-1.,weighttrg[iRecoPTbin[ix]]) ;
						    }
						}
					}//reco	
					
                      for(int gen = 0; gen<ngenjets[ix]; gen++){
                      int genpt_tag = getbinid(abs(genjetpT[ix][gen]),noptbins,ptbins);
                      if (genpt_tag<0) continue;
                         bool ismatched =false;
				for(int reco = 0; reco<npfjets[ix]; reco++) { 
				  int recpt_tag = getbinid(abs(pfjetpT[ix][reco]),noptbins,ptbins);
				   double deltaphi = PhiInRange(abs(pfjetphi[ix][reco]-genjetphi[ix][gen]));
				   double deltapT = (pfjetpT[ix][reco]-genjetpT[ix][gen])*1.0/genjetpT[ix][gen];
							
					if (recpt_tag>=0) {
				 				if((deltaphi>(0.05*(ix+1)))||(deltapT<(-0.5))||(deltapT>1.)) continue ; 
								ismatched =true; break;
							}
						}//reco
					if (!ismatched) { 
					   if(genpt_tag>=0) {
					Response_y[ix]->Fill(-1, abs(genjety[ix][gen]),weighttrg[iGenPTbin[ix]]) ;
							}
						}
					}//gen	
				}else {
				if(iRecoPTbin[ix]>=0 && iRecoPTbin[ix]<nHLTmx && ihlttrg[iRecoPTbin[ix]]>0){
				 for(int reco = 0; reco<npfjets[ix]; reco++){
					int recpt_tag = -1;
					recpt_tag = getbinid(abs(pfjetpT[ix][reco]),noptbins,ptbins);
			if(recpt_tag>0) {Response_y[ix]->Fill(pfjety[ix][reco],-1.,weighttrg[iRecoPTbin[ix]]) ;}
							}//reco
						} else if(iGenPTbin[ix]>=0 && iGenPTbin[ix]<nHLTmx && ihlttrg[iGenPTbin[ix]]>0){
						for(int gen = 0; gen<ngenjets[ix]; gen++){
						 int genpt_tag = -1;
						  genpt_tag = getbinid(abs(genjetpT[ix][gen]),noptbins,ptbins);
			if(genpt_tag>=0){ Response_y[ix]->Fill(-1.,genjetpT[ix][gen],weighttrg[iGenPTbin[ix]]) ;}
							} //gen
						 }
					   }

// ========== Response Matrix for y Ends ===================

		} //isMC
    
 } //for(int ix=0 ; ix<nalgo ; ++ix) 

 
  for(int ix=0 ; ix<nalgo; ++ix) {
  
    switch(ix) {
		
	case 0 : 
    
    npfjets01 =  npfjets[ix] ;
    
    for(int jc = 0 ;jc<npfjets01 ; ++jc) { 
	
	pfjetpT01[jc] = pfjetpT[ix][jc]  ;
	pfjety01[jc] = pfjety[ix][jc] ;
	pfjetphi01[jc] = pfjetphi[ix][jc] ;
	pfjetarea01[jc] = pfjetarea[ix][jc] ; 
         }
	
	if(isMC) {
	  ngenjets01 =  ngenjets[ix] ;
	  
	  for(int jc = 0 ;jc<ngenjets01 ; ++jc) {   
	
	  genjetpT01[jc] = genjetpT[ix][jc] ;
	  genjety01[jc] = genjety[ix][jc] ;
	  genjetphi01[jc] = genjetphi[ix][jc] ;
	  genjetarea01[jc] = genjetarea[ix][jc] ;	  
		}
      }
      break;	
      
    case 1 : 
    
    npfjets02 =  npfjets[ix] ;
    
    for(int jc = 0 ;jc<npfjets02 ; ++jc){ 
	
	pfjetpT02[jc] = pfjetpT[ix][jc]  ;
	pfjety02[jc] = pfjety[ix][jc] ;
	pfjetphi02[jc] = pfjetphi[ix][jc] ;
	pfjetarea02[jc] = pfjetarea[ix][jc] ; 
	}
	
	if(isMC){
	  ngenjets02 =  ngenjets[ix] ;
	  
	  for(int jc = 0 ;jc<ngenjets02 ; ++jc) {
	 
	  genjetpT02[jc] = genjetpT[ix][jc] ;
	  genjety02[jc] = genjety[ix][jc] ;
	  genjetphi02[jc] = genjetphi[ix][jc] ;
	  genjetarea02[jc] = genjetarea[ix][jc] ;	  
		}
      }
      break;
      
 case 2 :

  npfjets03 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets03 ; ++jc){
	 
 pfjetpT03[jc] = pfjetpT[ix][jc]  ;
 pfjety03[jc] = pfjety[ix][jc] ;
 pfjetphi03[jc] = pfjetphi[ix][jc] ;
 pfjetarea03[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets03 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets03 ; ++jc){
	 
 genjetpT03[jc] = genjetpT[ix][jc]  ;
 genjety03[jc] = genjety[ix][jc] ;
 genjetphi03[jc] = genjetphi[ix][jc] ;
 genjetarea03[jc] = genjetarea[ix][jc] ;
    }
  }
 break ;

  case 3 :

  npfjets04 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets04 ; ++jc){
	 
 pfjetpT04[jc] = pfjetpT[ix][jc] ;
 pfjety04[jc] = pfjety[ix][jc] ;
 pfjetphi04[jc] = pfjetphi[ix][jc] ;
 pfjetarea04[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets04 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets04 ; ++jc){
 
 genjetpT04[jc] = genjetpT[ix][jc] ;
 genjety04[jc] = genjety[ix][jc] ;
 genjetphi04[jc] = genjetphi[ix][jc] ;
 genjetarea04[jc] = genjetarea[ix][jc] ;

    }
  }


 break ;

 case 4 :
 
 npfjets05 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets05 ; ++jc){

 pfjetpT05[jc] = pfjetpT[ix][jc]  ;
 pfjety05[jc] = pfjety[ix][jc] ;
 pfjetphi05[jc] = pfjetphi[ix][jc] ;
 pfjetarea05[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets05 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets05 ; ++jc){
 
 genjetpT05[jc] = genjetpT[ix][jc]  ;
 genjety05[jc] = genjety[ix][jc] ;
 genjetphi05[jc] = genjetphi[ix][jc] ;
 genjetarea05[jc] = genjetarea[ix][jc] ;

    }
  }

break ;

case 5 :

 npfjets06 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets06 ; ++jc){

 pfjetpT06[jc] = pfjetpT[ix][jc]  ;
 pfjety06[jc] = pfjety[ix][jc] ;
 pfjetphi06[jc] = pfjetphi[ix][jc] ;
 pfjetarea06[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets06 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets06 ; ++jc){
 
 genjetpT06[jc] = genjetpT[ix][jc]  ;
 genjety06[jc] = genjety[ix][jc] ;
 genjetphi06[jc] = genjetphi[ix][jc] ;
 genjetarea06[jc] = genjetarea[ix][jc] ;

    }
  }

 break ;

 case 6 :
 
  npfjets07 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets07 ; ++jc){

 pfjetpT07[jc] = pfjetpT[ix][jc] ;
 pfjety07[jc] = pfjety[ix][jc] ;
 pfjetphi07[jc] = pfjetphi[ix][jc] ;
 pfjetarea07[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets07 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets07 ; ++jc){
 
 genjetpT07[jc] = genjetpT[ix][jc]  ;
 genjety07[jc] = genjety[ix][jc] ;
 genjetphi07[jc] = genjetphi[ix][jc] ;
 genjetarea07[jc] = genjetarea[ix][jc] ;

    }
  }

 break ;

 case 7 :
 
 npfjets08 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets08 ; ++jc){

 pfjetpT08[jc] = pfjetpT[ix][jc];
 pfjety08[jc] = pfjety[ix][jc] ;
 pfjetphi08[jc] = pfjetphi[ix][jc] ;
 pfjetarea08[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets08 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets08 ; ++jc){
 
 genjetpT08[jc] = genjetpT[ix][jc] ;
 genjety08[jc] = genjety[ix][jc] ;
 genjetphi08[jc] = genjetphi[ix][jc] ;
 genjetarea08[jc] = genjetarea[ix][jc] ;

    }
  }

 
 break ;

 case 8 :
 
 npfjets09 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets09 ; ++jc){

 pfjetpT09[jc] = pfjetpT[ix][jc]  ;
 pfjety09[jc] = pfjety[ix][jc] ;
 pfjetphi09[jc] = pfjetphi[ix][jc] ;
 pfjetarea09[jc] = pfjetarea[ix][jc] ;
 }
 
 if(isMC){

  ngenjets09  =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets09 ; ++jc){
 
 genjetpT09[jc] = genjetpT[ix][jc]  ;
 genjety09[jc] = genjety[ix][jc] ;
 genjetphi09[jc] = genjetphi[ix][jc] ;
 genjetarea09[jc] = genjetarea[ix][jc] ;

    }
  }


  break ;  

  case 9 :
 
  npfjets10 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets10 ; ++jc){

 pfjetpT10[jc] = pfjetpT[ix][jc]  ;
 pfjety10[jc] = pfjety[ix][jc] ;
 pfjetphi10[jc] = pfjetphi[ix][jc] ;
 pfjetarea10[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets10 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets10 ; ++jc){
 
 genjetpT10[jc] = genjetpT[ix][jc] ;
 genjety10[jc] = genjety[ix][jc] ;
 genjetphi10[jc] = genjetphi[ix][jc] ;
 genjetarea10[jc] = genjetarea[ix][jc] ;

    }
  }


 break ; 

 case 10 :
 
 npfjets11 =  npfjets[ix] ;

 for(int jc = 0 ;jc<npfjets11 ; ++jc){

 pfjetpT11[jc] = pfjetpT[ix][jc] ;
 pfjety11[jc] = pfjety[ix][jc];
 pfjetphi11[jc] = pfjetphi[ix][jc] ;
 pfjetarea11[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets11 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets11 ; ++jc){
 
 genjetpT11[jc] = genjetpT[ix][jc]  ;
 genjety11[jc] = genjety[ix][jc] ;
 genjetphi11[jc] = genjetphi[ix][jc] ;
 genjetarea11[jc] = genjetarea[ix][jc] ;

			}
		}

 break ;
 
 case 11 :
 
 npfjets12 =  npfjets[ix] ;
 
 for(int jc = 0 ;jc<npfjets12 ; ++jc){

 pfjetpT12[jc] = pfjetpT[ix][jc] ;
 pfjety12[jc] = pfjety[ix][jc];
 pfjetphi12[jc] = pfjetphi[ix][jc] ;
 pfjetarea12[jc] = pfjetarea[ix][jc] ;
 }

 if(isMC){

  ngenjets12 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets12 ; ++jc){
 
 genjetpT12[jc] = genjetpT[ix][jc]  ;
 genjety12[jc] = genjety[ix][jc] ;
 genjetphi12[jc] = genjetphi[ix][jc] ;
 genjetarea12[jc] = genjetarea[ix][jc] ;

			}
		}

 break ;
 
    }//switch
    
  }// ix loop
  
 
  T1->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
MCJetsMINIAOD_SingleRad::beginJob()
{
	////JEC /////
  L1FastAK4       = new JetCorrectorParameters(mJECL1FastFileAK4.c_str());
  L2RelativeAK4   = new JetCorrectorParameters(mJECL2RelativeFileAK4.c_str());
  L3AbsoluteAK4   = new JetCorrectorParameters(mJECL3AbsoluteFileAK4.c_str());
  L2L3ResidualAK4 = new JetCorrectorParameters(mJECL2L3ResidualFileAK4.c_str());

  vecL1FastAK4.push_back(*L1FastAK4);
  vecL2RelativeAK4.push_back(*L2RelativeAK4);
  vecL3AbsoluteAK4.push_back(*L3AbsoluteAK4);
  vecL2L3ResidualAK4.push_back(*L2L3ResidualAK4);
  
  jecL1FastAK4       = new FactorizedJetCorrector(vecL1FastAK4);
  jecL2RelativeAK4   = new FactorizedJetCorrector(vecL2RelativeAK4);
  jecL3AbsoluteAK4   = new FactorizedJetCorrector(vecL3AbsoluteAK4);
  jecL2L3ResidualAK4 = new FactorizedJetCorrector(vecL2L3ResidualAK4);
  
  L1FastAK8       = new JetCorrectorParameters(mJECL1FastFileAK8.c_str());
  L2RelativeAK8   = new JetCorrectorParameters(mJECL2RelativeFileAK8.c_str());
  L3AbsoluteAK8   = new JetCorrectorParameters(mJECL3AbsoluteFileAK8.c_str());
  L2L3ResidualAK8 = new JetCorrectorParameters(mJECL2L3ResidualFileAK8.c_str());

  vecL1FastAK8.push_back(*L1FastAK8);
  vecL2RelativeAK8.push_back(*L2RelativeAK8);
  vecL3AbsoluteAK8.push_back(*L3AbsoluteAK8);
  vecL2L3ResidualAK8.push_back(*L2L3ResidualAK8);
  
  jecL1FastAK8       = new FactorizedJetCorrector(vecL1FastAK8);
  jecL2RelativeAK8   = new FactorizedJetCorrector(vecL2RelativeAK8);
  jecL3AbsoluteAK8   = new FactorizedJetCorrector(vecL3AbsoluteAK8);
  jecL2L3ResidualAK8 = new FactorizedJetCorrector(vecL2L3ResidualAK8);
  
  	
  	//// JEC End /////
  	
  Nevt = 0;
  if (isMC) { 
    double dattot[nHLTmx]={0};
    double mctot=0;
    for (int ij=0; ij<npileupmx; ij++) {
      for (int jk=0; jk<nHLTmx; jk++) {
	dattot[jk] +=datpileup[jk][ij];
      }
      mctot +=mcpileup[ij];
    }
    
    for (int ij=0; ij<npileupmx; ij++) {
      mcpileup[ij] /=max(1.e-6,mctot);
      for (int jk=0; jk<nHLTmx; jk++) {
	datpileup[jk][ij] /=max(1.e-6,dattot[jk]);
	
	rat_pileup[jk][ij] =  datpileup[jk][ij]*1./mcpileup[ij];
	if(jk==0) { cout<<ij<<" ratio "<<rat_pileup[jk][ij]<<endl;}
      }
    }
  }

  #ifdef Data2015

  for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compres15[ij];
          }
          

  #elif defined(Data2016)

  if(Data2016B||Data2016C){
          for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compresBC[ij];
          }
          }
  if(Data2016D||Data2016E){
          for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compresDE[ij];
          }
          }
  if(Data2016F){
          for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compresF[ij];
          }
          }
  if(Data2016G){
          for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compresG[ij];
          }
          }
  if(Data2016H){
          for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compresH[ij];
          }
          }
  #endif


  #ifdef JETEnergyScale

  for (int isrc = 0; isrc < nsrc; isrc++) {
    const char *name = srcnames[isrc];
    JetCorrectorParameters *p = new JetCorrectorParameters("Fall15_25nsV2_DATA_UncertaintySources_AK4PFchs.txt", name); //"Summer16_23Sep2016BCDV4_DATA_UncertaintySources_AK4PFchs.txt"
    JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
		//    vsrc[isrc] = unc;
		vsrc.push_back(unc);
  }
 
#endif  


}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCJetsMINIAOD_SingleRad::endJob() 
{
// T1->Write();
 //fs->cd();
// fs->Write();
// fs->Close();

//delete fs;	

if(isMC){

  for(int ix=0; ix<nalgo; ix++){
	  for(int jk=0; jk<netarange; jk++){
		  for(int kl=0; kl<noptbins; kl++){
			  double fake;							/*fake*/
			  fake = RecoVsGenJetpT[ix][jk]->GetBinContent(kl+1,0);
			  double total = 0;
			  for(int lm=0; lm<noptbins; lm++){
				  total+= RecoVsGenJetpT[ix][jk]->GetBinContent(kl+1,lm+1);
				  }//lm
				  if (total<0.01) {total = 0.01;}
				  fake = fake *1.0/total ;
				  Resolution[ix][jk][kl]->Fill(-2.,fake) ;
				  
				  total = 0;				/*ineffficiency*/
				  double ineff = 0;
				  ineff = RecoVsGenJetpT[ix][jk]->GetBinContent(0,kl+1);
				  for(int lm=0; lm<noptbins; lm++){
				  total+= RecoVsGenJetpT[ix][jk]->GetBinContent(lm+1,kl+1);
				  }//lm
				  if (total<0.01) {total = 0.01;}
				  ineff = ineff*1.0/total ;
				  Resolution[ix][jk][kl]->Fill(10.,ineff) ;
			}//kl
		  }//jk
	  }//ix

}
  
  theFile->cd();
  theFile->Write();
  theFile->Close();
  cout<<"End of HOinPFAlgo with event "<<Nevt<<endl;
}

// ------------ method called when starting to processes a run  ------------
void 
MCJetsMINIAOD_SingleRad::beginRun(edm::Run const& iRun, edm::EventSetup const& pset)
{
 
  bool changed(true);
  
  if (hltPrescaleProvider_.init(iRun, pset,theHLTTag.c_str(),changed)) {
    HLTConfigProvider const&  hltConfig_ = hltPrescaleProvider_.hltConfigProvider(); 
    hltConfig_.dump("Triggers");
    hltConfig_.dump("PrescaleTable");
    
    for (unsigned int ij=0; ij<nHLTmx; ij++) {
      l1pres[ij] = hltpres[ij]=-7;
    }
  }
  else {
    }
}

// ------------ method called when ending the processing of a run  ------------
void 
MCJetsMINIAOD_SingleRad::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MCJetsMINIAOD_SingleRad::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MCJetsMINIAOD_SingleRad::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MCJetsMINIAOD_SingleRad::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCJetsMINIAOD_SingleRad);
/*
edmDumpEventContent /store/data/Run2015D/JetHT/MINIAOD/PromptReco-v4/000/260/727/00000/32143F94-C084-E511-AC67-02163E01363A.root
 
Type                                  Module                      Label             Process   
----------------------------------------------------------------------------------------------
edm::TriggerResults                   "TriggerResults"            ""                "HLT"     
HcalNoiseSummary                      "hcalnoise"                 ""                "RECO"    
L1GlobalTriggerReadoutRecord          "gtDigis"                   ""                "RECO"    
double                                "fixedGridRhoAll"           ""                "RECO"    
double                                "fixedGridRhoFastjetAll"    ""                "RECO"    
double                                "fixedGridRhoFastjetAllCalo"   ""                "RECO"    
double                                "fixedGridRhoFastjetCentralCalo"   ""                "RECO"    
double                                "fixedGridRhoFastjetCentralChargedPileUp"   ""                "RECO"    
double                                "fixedGridRhoFastjetCentralNeutral"   ""                "RECO"    
edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >    "reducedEgamma"             "reducedEBRecHits"   "RECO"    
edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >    "reducedEgamma"             "reducedEERecHits"   "RECO"    
edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >    "reducedEgamma"             "reducedESRecHits"   "RECO"    
edm::TriggerResults                   "TriggerResults"            ""                "RECO"    
edm::ValueMap<float>                  "offlineSlimmedPrimaryVertices"   ""                "RECO"    
pat::PackedTriggerPrescales           "patTrigger"                ""                "RECO"    
pat::PackedTriggerPrescales           "patTrigger"                "l1max"           "RECO"    
pat::PackedTriggerPrescales           "patTrigger"                "l1min"           "RECO"    
reco::BeamSpot                        "offlineBeamSpot"           ""                "RECO"    
vector<l1extra::L1EmParticle>         "l1extraParticles"          "Isolated"        "RECO"    
vector<l1extra::L1EmParticle>         "l1extraParticles"          "NonIsolated"     "RECO"    
vector<l1extra::L1EtMissParticle>     "l1extraParticles"          "MET"             "RECO"    
vector<l1extra::L1EtMissParticle>     "l1extraParticles"          "MHT"             "RECO"    
vector<l1extra::L1HFRings>            "l1extraParticles"          ""                "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Central"         "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Forward"         "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "IsoTau"          "RECO"    
vector<l1extra::L1JetParticle>        "l1extraParticles"          "Tau"             "RECO"    
vector<l1extra::L1MuonParticle>       "l1extraParticles"          ""                "RECO"    
vector<pat::Electron>                 "slimmedElectrons"          ""                "RECO"    
vector<pat::Jet>                      "slimmedJets"               ""                "RECO"    
vector<pat::Jet>                      "slimmedJetsAK8"            ""                "RECO"    
vector<pat::Jet>                      "slimmedJetsPuppi"          ""                "RECO"    
vector<pat::Jet>                      "slimmedJetsAK8PFCHSSoftDropPacked"   "SubJets"         "RECO"    
vector<pat::Jet>                      "slimmedJetsCMSTopTagCHSPacked"   "SubJets"         "RECO"    
vector<pat::MET>                      "slimmedMETs"               ""                "RECO"    
vector<pat::MET>                      "slimmedMETsNoHF"           ""                "RECO"    
vector<pat::MET>                      "slimmedMETsPuppi"          ""                "RECO"    
vector<pat::Muon>                     "slimmedMuons"              ""                "RECO"    
vector<pat::PackedCandidate>          "lostTracks"                ""                "RECO"    
vector<pat::PackedCandidate>          "packedPFCandidates"        ""                "RECO"    
vector<pat::Photon>                   "slimmedPhotons"            ""                "RECO"    
vector<pat::Tau>                      "slimmedTaus"               ""                "RECO"    
vector<pat::TriggerObjectStandAlone>    "selectedPatTrigger"        ""                "RECO"    
vector<reco::CATopJetTagInfo>         "caTopTagInfosPAT"          ""                "RECO"    
vector<reco::CaloCluster>             "reducedEgamma"             "reducedEBEEClusters"   "RECO"    
vector<reco::CaloCluster>             "reducedEgamma"             "reducedESClusters"   "RECO"    
vector<reco::Conversion>              "reducedEgamma"             "reducedConversions"   "RECO"    
vector<reco::Conversion>              "reducedEgamma"             "reducedSingleLegConversions"   "RECO"    
vector<reco::GsfElectronCore>         "reducedEgamma"             "reducedGedGsfElectronCores"   "RECO"    
vector<reco::PhotonCore>              "reducedEgamma"             "reducedGedPhotonCores"   "RECO"    
vector<reco::SuperCluster>            "reducedEgamma"             "reducedSuperClusters"   "RECO"    
vector<reco::Vertex>                  "offlineSlimmedPrimaryVertices"   ""                "RECO"    
vector<reco::VertexCompositePtrCandidate>    "slimmedSecondaryVertices"   ""                "RECO"    


*/
