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

static const int nalgo = 12 ;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double jetsize[nalgo] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2};
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


const int nHLTmx= 10; 

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
class MCJetsMINIAOD_NTuplizer : public edm::EDAnalyzer {
   public:
      explicit MCJetsMINIAOD_NTuplizer(const edm::ParameterSet&);
      ~MCJetsMINIAOD_NTuplizer();

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
  double maxEta;

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
 
  
  int irunold;
  int irun, ilumi, ifltr, nprim, ibrnch;
  double event_weight;
  
  unsigned ievt;
  
  static const int njetmx =20; 
  
  double Rho ;
    
  int nvert;
  int nchict;
  int npu_vert;

  int npfjets[nalgo] ;
  int pfjetmul[nalgo][njetmx] ;
  float pfjetenr[nalgo][njetmx], pfjetmom[nalgo][njetmx], pfjetpT[nalgo][njetmx],  pfjetarea[nalgo][njetmx], pfjetthe[nalgo][njetmx], pfjety[nalgo][njetmx], pfjetphi[nalgo][njetmx],  pfjetpTup[nalgo][njetmx], pfjetpTdn[nalgo][njetmx], pfjetJEC[nalgo][njetmx],pfjetJECL1[nalgo][njetmx], pfjetSF[nalgo][njetmx], pfjetSFup[nalgo][njetmx], pfjetSFdn[nalgo][njetmx];
  bool pfjettightID[nalgo][njetmx], pfjetlooseID[nalgo][njetmx] ;
 
  int npfjets01;
  int pfjetmul01[njetmx];
  float pfjetenr01[njetmx], pfjetpT01[njetmx], pfjetarea01[njetmx], pfjety01[njetmx], pfjetphi01[njetmx], pfjetpTup01[njetmx], pfjetpTdn01[njetmx], pfjetJEC01[njetmx], pfjetJECL101[njetmx], pfjetSF01[njetmx], pfjetSFup01[njetmx], pfjetSFdn01[njetmx];
  bool pfjettightID01[njetmx],  pfjetlooseID01[njetmx]   ;
  
  int npfjets02;
  int pfjetmul02[njetmx];
  float pfjetenr02[njetmx], pfjetpT02[njetmx], pfjetarea02[njetmx], pfjety02[njetmx], pfjetphi02[njetmx], pfjetpTup02[njetmx], pfjetpTdn02[njetmx], pfjetJEC02[njetmx], pfjetJECL102[njetmx], pfjetSF02[njetmx], pfjetSFup02[njetmx], pfjetSFdn02[njetmx];
  bool pfjettightID02[njetmx],  pfjetlooseID02[njetmx]   ;
  
  int npfjets03;
  int pfjetmul03[njetmx];
  float pfjetenr03[njetmx], pfjetpT03[njetmx], pfjetarea03[njetmx], pfjety03[njetmx], pfjetphi03[njetmx], pfjetpTup03[njetmx], pfjetpTdn03[njetmx], pfjetJEC03[njetmx], pfjetJECL103[njetmx], pfjetSF03[njetmx], pfjetSFup03[njetmx], pfjetSFdn03[njetmx];
  bool pfjettightID03[njetmx],  pfjetlooseID03[njetmx]   ;

  int npfjets04;
  int pfjetmul04[njetmx];
  float pfjetenr04[njetmx], pfjetpT04[njetmx], pfjetarea04[njetmx], pfjety04[njetmx], pfjetphi04[njetmx], pfjetpTup04[njetmx], pfjetpTdn04[njetmx], pfjetJEC04[njetmx], pfjetJECL104[njetmx], pfjetSF04[njetmx], pfjetSFup04[njetmx], pfjetSFdn04[njetmx];
  bool pfjettightID04[njetmx],  pfjetlooseID04[njetmx]   ;

  int npfjets05;
  int pfjetmul05[njetmx];
  float pfjetenr05[njetmx], pfjetpT05[njetmx], pfjetarea05[njetmx], pfjety05[njetmx], pfjetphi05[njetmx], pfjetpTup05[njetmx], pfjetpTdn05[njetmx], pfjetJEC05[njetmx], pfjetJECL105[njetmx], pfjetSF05[njetmx], pfjetSFup05[njetmx], pfjetSFdn05[njetmx];
  bool pfjettightID05[njetmx],  pfjetlooseID05[njetmx]   ;

  int npfjets06;
  int pfjetmul06[njetmx];
  float pfjetenr06[njetmx], pfjetpT06[njetmx], pfjetarea06[njetmx], pfjety06[njetmx], pfjetphi06[njetmx], pfjetpTup06[njetmx], pfjetpTdn06[njetmx], pfjetJEC06[njetmx], pfjetJECL106[njetmx], pfjetSF06[njetmx], pfjetSFup06[njetmx], pfjetSFdn06[njetmx];
  bool pfjettightID06[njetmx],  pfjetlooseID06[njetmx]   ;

  int npfjets07;
  int pfjetmul07[njetmx];
  float pfjetenr07[njetmx], pfjetpT07[njetmx], pfjetarea07[njetmx], pfjety07[njetmx], pfjetphi07[njetmx], pfjetpTup07[njetmx], pfjetpTdn07[njetmx], pfjetJEC07[njetmx], pfjetJECL107[njetmx], pfjetSF07[njetmx], pfjetSFup07[njetmx], pfjetSFdn07[njetmx];
  bool pfjettightID07[njetmx] ,  pfjetlooseID07[njetmx]  ;

  int npfjets08;
  int pfjetmul08[njetmx];
  float pfjetenr08[njetmx], pfjetpT08[njetmx], pfjetarea08[njetmx], pfjety08[njetmx], pfjetphi08[njetmx], pfjetpTup08[njetmx], pfjetpTdn08[njetmx], pfjetJEC08[njetmx], pfjetJECL108[njetmx], pfjetSF08[njetmx], pfjetSFup08[njetmx], pfjetSFdn08[njetmx];
  bool pfjettightID08[njetmx],  pfjetlooseID08[njetmx]   ;

  int npfjets09;
  int pfjetmul09[njetmx];
  float pfjetenr09[njetmx], pfjetpT09[njetmx], pfjetarea09[njetmx], pfjety09[njetmx], pfjetphi09[njetmx], pfjetpTup09[njetmx], pfjetpTdn09[njetmx], pfjetJEC09[njetmx], pfjetJECL109[njetmx], pfjetSF09[njetmx], pfjetSFup09[njetmx], pfjetSFdn09[njetmx];
  bool pfjettightID09[njetmx],  pfjetlooseID09[njetmx] ;

  int npfjets10;
  int pfjetmul10[njetmx];
  float pfjetenr10[njetmx], pfjetpT10[njetmx], pfjetarea10[njetmx], pfjety10[njetmx], pfjetphi10[njetmx], pfjetpTup10[njetmx], pfjetpTdn10[njetmx], pfjetJEC10[njetmx], pfjetJECL110[njetmx], pfjetSF10[njetmx], pfjetSFup10[njetmx], pfjetSFdn10[njetmx];
  bool pfjettightID10[njetmx],  pfjetlooseID10[njetmx]   ;

  int npfjets11;
  int pfjetmul11[njetmx];
  float pfjetenr11[njetmx], pfjetpT11[njetmx], pfjetarea11[njetmx], pfjety11[njetmx], pfjetphi11[njetmx], pfjetpTup11[njetmx], pfjetpTdn11[njetmx], pfjetJEC11[njetmx], pfjetJECL111[njetmx], pfjetSF11[njetmx], pfjetSFup11[njetmx], pfjetSFdn11[njetmx];
  bool pfjettightID11[njetmx],  pfjetlooseID11[njetmx]   ;

  int npfjets12;
  int pfjetmul12[njetmx];
  float pfjetenr12[njetmx], pfjetpT12[njetmx], pfjetarea12[njetmx], pfjety12[njetmx], pfjetphi12[njetmx], pfjetpTup12[njetmx], pfjetpTdn12[njetmx], pfjetJEC12[njetmx], pfjetJECL112[njetmx], pfjetSF12[njetmx], pfjetSFup12[njetmx], pfjetSFdn12[njetmx]; 
  bool pfjettightID12[njetmx],  pfjetlooseID12[njetmx]   ;
  
  int npfjets13;
  int pfjetmul13[njetmx];
  float pfjetenr13[njetmx], pfjetpT13[njetmx], pfjetarea13[njetmx], pfjety13[njetmx], pfjetphi13[njetmx], pfjettightID13[njetmx]  ;
  
  int npfjets14;
  int pfjetmul14[njetmx];
  float pfjetenr14[njetmx], pfjetpT14[njetmx], pfjetarea14[njetmx], pfjety14[njetmx], pfjetphi14[njetmx], pfjettightID14[njetmx]  ;
  
  int npfjets15;
  int pfjetmul15[njetmx];
  float pfjetenr15[njetmx], pfjetpT15[njetmx], pfjetarea15[njetmx], pfjety15[njetmx], pfjetphi15[njetmx], pfjettightID15[njetmx]  ;

  
  static const int ngenjetmx =20;

  int ngenjets[nalgo] ;
  int genjetmul[nalgo];
  float genjetenr[nalgo][njetmx], genjetmom[nalgo][njetmx], genjetpT[nalgo][njetmx], genjetarea[nalgo][njetmx], genjetthe[nalgo][njetmx], genjety[nalgo][njetmx], genjetphi[nalgo][njetmx] ;

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
  float genjetenr10[njetmx], genjetpT10[njetmx], genjetarea10[njetmx], genjety10[njetmx], genjetphi10[njetmx];

  int ngenjets11;
  int genjetmul11[njetmx];
  float genjetenr11[njetmx], genjetpT11[njetmx], genjetarea11[njetmx], genjety11[njetmx], genjetphi11[njetmx];
  
  int ngenjets12;
  int genjetmul12[njetmx];
  float genjetenr12[njetmx], genjetpT12[njetmx], genjetarea12[njetmx], genjety12[njetmx], genjetphi12[njetmx];
  
  int ngenjets13;
  int genjetmul13[njetmx];
  float genjetenr13[njetmx], genjetpT13[njetmx], genjetarea13[njetmx], genjety13[njetmx], genjetphi13[njetmx];
  
  int ngenjets14;
  int genjetmul14[njetmx];
  float genjetenr14[njetmx], genjetpT14[njetmx], genjetarea14[njetmx], genjety14[njetmx], genjetphi14[njetmx];
  
  int ngenjets15;
  int genjetmul15[njetmx];
  float genjetenr15[njetmx], genjetpT15[njetmx], genjetarea15[njetmx], genjety15[njetmx], genjetphi15[njetmx];
  
  
  float miset , misphi , sumEt;
  
  int isReco[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;
  float RecopT[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;
  int  iRecoPTbin[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;

  int isGen[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;
  float GenpT/*[njecmcmx]*/[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;// {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}} ;
  int  iGenPTbin[nalgo] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;

  unsigned int mypow_2[32];

  int irunhlt, l1pres[nHLTmx], hltpres[nHLTmx];
  
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
MCJetsMINIAOD_NTuplizer::MCJetsMINIAOD_NTuplizer(const edm::ParameterSet& pset) :
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
  minPFPt =  pset.getUntrackedParameter<double>("minPFPt", 20.0);
  maxEta =  pset.getUntrackedParameter<double>("maxEta",5.0);
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
  T1->Branch("sumEt",&sumEt,"sumEt/F") ;

  T1->Branch("nvert",&nvert,"nvert/I");
  T1->Branch("nchict",&nchict,"nchict/I");

  if(isMC){
	  T1->Branch("npu_vert",&npu_vert,"npu_vert/I");
	  T1->Branch("pthat",&pthat,"pthat/F");
	  }

  T1->Branch("npfjets01",&npfjets01, "npfjets01/I"); 
  T1->Branch("pfjetpT01",pfjetpT01,"pfjetpT01[npfjets01]/F");
  T1->Branch("pfjetarea01",pfjetarea01,"pfjetarea01[npfjets01]/F");
  T1->Branch("pfjety01",pfjety01,"pfjety01[npfjets01]/F"); 
  T1->Branch("pfjetphi01",pfjetphi01,"pfjetphi01[npfjets01]/F") ;
  T1->Branch("pfjetenr01",pfjetenr01,"pfjetenr01[npfjets01]/F") ;
  T1->Branch("pfjettightID01",pfjettightID01,"pfjettightID01[npfjets01]/O");
  T1->Branch("pfjetlooseID01",pfjetlooseID01,"pfjetlooseID01[npfjets01]/O");
/*
  T1->Branch("pfjetpTup01",pfjetpTup01,"pfjetpTup01[npfjets01]/F");
  T1->Branch("pfjetpTdn01",pfjetpTdn01,"pfjetpTdn01[npfjets01]/F");
*/
  T1->Branch("pfjetJEC01",pfjetJEC01,"pfjetJEC01[npfjets01]/F");
  T1->Branch("pfjetJECL101",pfjetJECL101,"pfjetJECL101[npfjets01]/F");
  T1->Branch("pfjetSF01",pfjetSF01,"pfjetSF01[npfjets01]/F");
  T1->Branch("pfjetSFup01",pfjetSFup01,"pfjetSFup01[npfjets01]/F");
  T1->Branch("pfjetSFdn01",pfjetSFdn01,"pfjetSFdn01[npfjets01]/F");

  T1->Branch("npfjets02", &npfjets02, "npfjets02/I"); 
  T1->Branch("pfjetpT02",pfjetpT02,"pfjetpT02[npfjets02]/F");
  T1->Branch("pfjetarea02",pfjetarea02,"pfjetarea02[npfjets02]/F");
  T1->Branch("pfjety02",pfjety02,"pfjety02[npfjets02]/F"); 
  T1->Branch("pfjetphi02",pfjetphi02,"pfjetphi02[npfjets02]/F") ;
  T1->Branch("pfjetenr02",pfjetenr02,"pfjetenr02[npfjets02]/F") ;
  T1->Branch("pfjettightID02",pfjettightID02,"pfjettightID02[npfjets02]/O");
  T1->Branch("pfjetlooseID02",pfjetlooseID02,"pfjetlooseID02[npfjets02]/O");
/*
  T1->Branch("pfjetpTup02",pfjetpTup02,"pfjetpTup02[npfjets02]/F");
  T1->Branch("pfjetpTdn02",pfjetpTdn02,"pfjetpTdn02[npfjets02]/F");
*/
  T1->Branch("pfjetJEC02",pfjetJEC02,"pfjetJEC02[npfjets02]/F");
  T1->Branch("pfjetJECL102",pfjetJECL102,"pfjetJECL102[npfjets02]/F");
  T1->Branch("pfjetSF02",pfjetSF02,"pfjetSF02[npfjets02]/F");
  T1->Branch("pfjetSFup02",pfjetSFup02,"pfjetSFup02[npfjets02]/F");
  T1->Branch("pfjetSFdn02",pfjetSFdn02,"pfjetSFdn02[npfjets02]/F");

  T1->Branch("npfjets03", &npfjets03, "npfjets03/I");
  T1->Branch("pfjetpT03",pfjetpT03,"pfjetpT03[npfjets03]/F");
  T1->Branch("pfjetarea03",pfjetarea03,"pfjetarea03[npfjets03]/F");
  T1->Branch("pfjety03",pfjety03,"pfjety03[npfjets03]/F");
  T1->Branch("pfjetphi03",pfjetphi03,"pfjetphi03[npfjets03]/F") ;
  T1->Branch("pfjetenr03",pfjetenr03,"pfjetenr03[npfjets03]/F") ;
  T1->Branch("pfjettightID03",pfjettightID03,"pfjettightID03[npfjets03]/O");
  T1->Branch("pfjetlooseID03",pfjetlooseID03,"pfjetlooseID03[npfjets03]/O");
/*
  T1->Branch("pfjetpTup03",pfjetpTup03,"pfjetpTup03[npfjets03]/F");
  T1->Branch("pfjetpTdn03",pfjetpTdn03,"pfjetpTdn03[npfjets03]/F");
*/
  T1->Branch("pfjetJEC03",pfjetJEC03,"pfjetJEC03[npfjets03]/F");
  T1->Branch("pfjetJECL103",pfjetJECL103,"pfjetJECL103[npfjets03]/F");
  T1->Branch("pfjetSF03",pfjetSF03,"pfjetSF03[npfjets03]/F"); 
  T1->Branch("pfjetSFup03",pfjetSFup03,"pfjetSFup03[npfjets03]/F");
  T1->Branch("pfjetSFdn03",pfjetSFdn03,"pfjetSFdn03[npfjets03]/F");

  T1->Branch("npfjets04", &npfjets04, "npfjets04/I");
  T1->Branch("pfjetpT04",pfjetpT04,"pfjetpT04[npfjets04]/F");
  T1->Branch("pfjetarea04",pfjetarea04,"pfjetarea04[npfjets04]/F");
  T1->Branch("pfjety04",pfjety04,"pfjety04[npfjets04]/F");
  T1->Branch("pfjetphi04",pfjetphi04,"pfjetphi04[npfjets04]/F") ;
  T1->Branch("pfjetenr04",pfjetenr04,"pfjetenr04[npfjets01]/F") ;
  T1->Branch("pfjettightID04",pfjettightID04,"pfjettightID04[npfjets04]/O");
  T1->Branch("pfjetlooseID04",pfjetlooseID04,"pfjetlooseID04[npfjets04]/O");
/*
  T1->Branch("pfjetpTup04",pfjetpTup04,"pfjetpTup04[npfjets04]/F");
  T1->Branch("pfjetpTdn04",pfjetpTdn04,"pfjetpTdn04[npfjets04]/F");
*/
  T1->Branch("pfjetJEC04",pfjetJEC04,"pfjetJEC04[npfjets04]/F");
  T1->Branch("pfjetJECL104",pfjetJECL104,"pfjetJECL104[npfjets04]/F");
  T1->Branch("pfjetSF04",pfjetSF04,"pfjetSF04[npfjets04]/F");
  T1->Branch("pfjetSFup04",pfjetSFup04,"pfjetSFup04[npfjets04]/F");
  T1->Branch("pfjetSFdn04",pfjetSFdn04,"pfjetSFdn04[npfjets04]/F");

  T1->Branch("npfjets05", &npfjets05, "npfjets05/I");
  T1->Branch("pfjetpT05",pfjetpT05,"pfjetpT05[npfjets05]/F");
  T1->Branch("pfjetarea05",pfjetarea05,"pfjetarea05[npfjets05]/F");
  T1->Branch("pfjety05",pfjety05,"pfjety05[npfjets05]/F");
  T1->Branch("pfjetphi05",pfjetphi05,"pfjetphi05[npfjets05]/F") ;
  T1->Branch("pfjetenr05",pfjetenr05,"pfjetenr05[npfjets05]/F") ;
  T1->Branch("pfjettightID05",pfjettightID05,"pfjettightID05[npfjets05]/O");
  T1->Branch("pfjetlooseID05",pfjetlooseID05,"pfjetlooseID05[npfjets05]/O");
/*
  T1->Branch("pfjetpTup05",pfjetpTup05,"pfjetpTup05[npfjets05]/F");
  T1->Branch("pfjetpTdn05",pfjetpTdn05,"pfjetpTdn05[npfjets05]/F");
*/
  T1->Branch("pfjetJEC05",pfjetJEC05,"pfjetJEC05[npfjets05]/F");
  T1->Branch("pfjetJECL105",pfjetJECL105,"pfjetJECL105[npfjets05]/F");
  T1->Branch("pfjetSF05",pfjetSF05,"pfjetSF05[npfjets05]/F");
  T1->Branch("pfjetSFup05",pfjetSFup05,"pfjetSFup05[npfjets05]/F");
  T1->Branch("pfjetSFdn05",pfjetSFdn05,"pfjetSFdn05[npfjets05]/F");

  T1->Branch("npfjets06", &npfjets06, "npfjets06/I");
  T1->Branch("pfjetpT06",pfjetpT06,"pfjetpT06[npfjets06]/F");
  T1->Branch("pfjetarea06",pfjetarea06,"pfjetarea06[npfjets06]/F");
  T1->Branch("pfjety06",pfjety06,"pfjety06[npfjets06]/F");
  T1->Branch("pfjetphi06",pfjetphi06,"pfjetphi06[npfjets06]/F") ;
  T1->Branch("pfjetenr06",pfjetenr06,"pfjetenr06[npfjets06]/F") ;
  T1->Branch("pfjettightID06",pfjettightID06,"pfjettightID06[npfjets06]/O");
  T1->Branch("pfjetlooseID06",pfjetlooseID06,"pfjetlooseID06[npfjets06]/O"); 
/*
  T1->Branch("pfjetpTup06",pfjetpTup06,"pfjetpTup06[npfjets06]/F");
  T1->Branch("pfjetpTdn06",pfjetpTdn06,"pfjetpTdn06[npfjets06]/F");
*/
  T1->Branch("pfjetJEC06",pfjetJEC06,"pfjetJEC06[npfjets06]/F");
  T1->Branch("pfjetJECL106",pfjetJECL106,"pfjetJECL106[npfjets06]/F");
  T1->Branch("pfjetSF06",pfjetSF06,"pfjetSF06[npfjets06]/F");
  T1->Branch("pfjetSFup06",pfjetSFup06,"pfjetSFup06[npfjets06]/F");
  T1->Branch("pfjetSFdn06",pfjetSFdn06,"pfjetSFdn06[npfjets06]/F");

  T1->Branch("npfjets07", &npfjets07, "npfjets07/I");
  T1->Branch("pfjetpT07",pfjetpT07,"pfjetpT07[npfjets07]/F");
  T1->Branch("pfjetarea07",pfjetarea07,"pfjetarea07[npfjets07]/F");
  T1->Branch("pfjety07",pfjety07,"pfjety07[npfjets07]/F");
  T1->Branch("pfjetphi07",pfjetphi07,"pfjetphi07[npfjets07]/F") ; 
  T1->Branch("pfjetenr07",pfjetenr07,"pfjetenr07[npfjets07]/F") ;
  T1->Branch("pfjettightID07",pfjettightID07,"pfjettightID07[npfjets07]/O");
  T1->Branch("pfjetlooseID07",pfjetlooseID07,"pfjetlooseID07[npfjets07]/O"); 
/*
  T1->Branch("pfjetpTup07",pfjetpTup07,"pfjetpTup07[npfjets07]/F");
  T1->Branch("pfjetpTdn07",pfjetpTdn07,"pfjetpTdn07[npfjets07]/F");
*/
  T1->Branch("pfjetJEC07",pfjetJEC07,"pfjetJEC07[npfjets07]/F");
  T1->Branch("pfjetJECL107",pfjetJECL107,"pfjetJECL107[npfjets07]/F");
  T1->Branch("pfjetSF07",pfjetSF07,"pfjetSF07[npfjets07]/F");
  T1->Branch("pfjetSFup07",pfjetSFup07,"pfjetSFup07[npfjets07]/F");
  T1->Branch("pfjetSFdn07",pfjetSFdn07,"pfjetSFdn07[npfjets07]/F");

  T1->Branch("npfjets08", &npfjets08, "npfjets08/I");
  T1->Branch("pfjetpT08",pfjetpT08,"pfjetpT08[npfjets08]/F");
  T1->Branch("pfjetarea08",pfjetarea08,"pfjetarea08[npfjets08]/F");
  T1->Branch("pfjety08",pfjety08,"pfjety08[npfjets08]/F");
  T1->Branch("pfjetphi08",pfjetphi08,"pfjetphi08[npfjets08]/F") ;
  T1->Branch("pfjetenr08",pfjetenr08,"pfjetenr08[npfjets08]/F") ;
  T1->Branch("pfjettightID08",pfjettightID08,"pfjettightID08[npfjets08]/O");
  T1->Branch("pfjetlooseID08",pfjetlooseID08,"pfjetlooseID08[npfjets08]/O"); 
/*
  T1->Branch("pfjetpTup08",pfjetpTup08,"pfjetpTup08[npfjets08]/F");
  T1->Branch("pfjetpTdn08",pfjetpTdn08,"pfjetpTdn08[npfjets08]/F");
*/
  T1->Branch("pfjetJEC08",pfjetJEC08,"pfjetJEC08[npfjets08]/F");
  T1->Branch("pfjetJECL108",pfjetJECL108,"pfjetJECL108[npfjets08]/F");
  T1->Branch("pfjetSF08",pfjetSF08,"pfjetSF08[npfjets08]/F");
  T1->Branch("pfjetSFup08",pfjetSFup08,"pfjetSFup08[npfjets08]/F");
  T1->Branch("pfjetSFdn08",pfjetSFdn08,"pfjetSFdn08[npfjets08]/F");

  T1->Branch("npfjets09", &npfjets09, "npfjets09/I");
  T1->Branch("pfjetpT09",pfjetpT09,"pfjetpT09[npfjets09]/F");
  T1->Branch("pfjetarea09",pfjetarea09,"pfjetarea09[npfjets09]/F");
  T1->Branch("pfjety09",pfjety09,"pfjety09[npfjets09]/F");
  T1->Branch("pfjetphi09",pfjetphi09,"pfjetphi09[npfjets09]/F") ;
  T1->Branch("pfjetenr09",pfjetenr09,"pfjetenr09[npfjets09]/F") ;
  T1->Branch("pfjettightID09",pfjettightID09,"pfjettightID09[npfjets09]/O");
  T1->Branch("pfjetlooseID09",pfjetlooseID09,"pfjetlooseID09[npfjets09]/O");
/*
  T1->Branch("pfjetpTup09",pfjetpTup09,"pfjetpTup09[npfjets09]/F");
  T1->Branch("pfjetpTdn09",pfjetpTdn09,"pfjetpTdn09[npfjets09]/F");
*/
  T1->Branch("pfjetJEC09",pfjetJEC09,"pfjetJEC09[npfjets09]/F");
  T1->Branch("pfjetJECL109",pfjetJECL109,"pfjetJECL109[npfjets09]/F");
  T1->Branch("pfjetSF09",pfjetSF09,"pfjetSF09[npfjets09]/F"); 
  T1->Branch("pfjetSFup09",pfjetSFup09,"pfjetSFup09[npfjets09]/F");
  T1->Branch("pfjetSFdn09",pfjetSFdn09,"pfjetSFdn09[npfjets09]/F");

  T1->Branch("npfjets10", &npfjets10, "npfjets10/I");
  T1->Branch("pfjetpT10",pfjetpT10,"pfjetpT10[npfjets10]/F");
  T1->Branch("pfjetarea10",pfjetarea10,"pfjetarea10[npfjets10]/F");
  T1->Branch("pfjety10",pfjety10,"pfjety10[npfjets10]/F");
  T1->Branch("pfjetphi10",pfjetphi10,"pfjetphi10[npfjets10]/F") ;
  T1->Branch("pfjetenr10",pfjetenr10,"pfjetenr10[npfjets10]/F") ;
  T1->Branch("pfjettightID10",pfjettightID10,"pfjettightID10[npfjets10]/O");
  T1->Branch("pfjetlooseID10",pfjetlooseID10,"pfjetlooseID11[npfjets10]/O"); 
/*
  T1->Branch("pfjetpTup10",pfjetpTup10,"pfjetpTup10[npfjets10]/F");
  T1->Branch("pfjetpTdn10",pfjetpTdn10,"pfjetpTdn10[npfjets10]/F");
*/
  T1->Branch("pfjetJEC10",pfjetJEC10,"pfjetJEC10[npfjets10]/F");
  T1->Branch("pfjetJECL110",pfjetJECL110,"pfjetJECL110[npfjets10]/F");
  T1->Branch("pfjetSF10",pfjetSF10,"pfjetSF10[npfjets10]/F");
  T1->Branch("pfjetSFup10",pfjetSFup10,"pfjetSFup10[npfjets10]/F");
  T1->Branch("pfjetSFdn10",pfjetSFdn10,"pfjetSFdn10[npfjets10]/F");

  T1->Branch("npfjets11", &npfjets11, "npfjets11/I");
  T1->Branch("pfjetpT11",pfjetpT11,"pfjetpT11[npfjets11]/F");
  T1->Branch("pfjetarea11",pfjetarea11,"pfjetarea11[npfjets11]/F");
  T1->Branch("pfjety11",pfjety11,"pfjety11[npfjets11]/F");
  T1->Branch("pfjetphi11",pfjetphi11,"pfjetphi11[npfjets11]/F") ; 
  T1->Branch("pfjetenr11",pfjetenr11,"pfjetenr11[npfjets11]/F") ;
  T1->Branch("pfjettightID11",pfjettightID11,"pfjettightID11[npfjets11]/O");
  T1->Branch("pfjetlooseID11",pfjetlooseID11,"pfjetlooseID11[npfjets11]/O");
/*
  T1->Branch("pfjetpTup11",pfjetpTup11,"pfjetpTup11[npfjets11]/F");
  T1->Branch("pfjetpTdn11",pfjetpTdn11,"pfjetpTdn11[npfjets11]/F");
*/
  T1->Branch("pfjetJEC11",pfjetJEC11,"pfjetJEC11[npfjets11]/F");
  T1->Branch("pfjetJECL111",pfjetJECL111,"pfjetJECL111[npfjets11]/F");
  T1->Branch("pfjetSF11",pfjetSF11,"pfjetSF11[npfjets11]/F");  
  T1->Branch("pfjetSFup11",pfjetSFup11,"pfjetSFup11[npfjets11]/F");
  T1->Branch("pfjetSFdn11",pfjetSFdn11,"pfjetSFdn11[npfjets11]/F");

  T1->Branch("npfjets12", &npfjets12, "npfjets12/I");
  T1->Branch("pfjetpT12",pfjetpT12,"pfjetpT12[npfjets12]/F");
  T1->Branch("pfjetarea12",pfjetarea12,"pfjetarea12[npfjets12]/F");
  T1->Branch("pfjety12",pfjety12,"pfjety12[npfjets12]/F");
  T1->Branch("pfjetphi12",pfjetphi12,"pfjetphi12[npfjets12]/F") ; 
  T1->Branch("pfjetenr12",pfjetenr12,"pfjetenr12[npfjets12]/F") ;
  T1->Branch("pfjettightID12",pfjettightID12,"pfjettightID12[npfjets12]/O");
  T1->Branch("pfjetlooseID12",pfjetlooseID12,"pfjetlooseID12[npfjets12]/O");
/*
  T1->Branch("pfjetpTup12",pfjetpTup12,"pfjetpTup12[npfjets12]/F");
  T1->Branch("pfjetpTdn12",pfjetpTdn12,"pfjetpTdn12[npfjets12]/F");
*/
  T1->Branch("pfjetJEC12",pfjetJEC12,"pfjetJEC12[npfjets12]/F");
  T1->Branch("pfjetJECL112",pfjetJECL112,"pfjetJECL112[npfjets12]/F");
  T1->Branch("pfjetSF12",pfjetSF12,"pfjetSF12[npfjets12]/F");
  T1->Branch("pfjetSFup12",pfjetSFup12,"pfjetSFup12[npfjets12]/F");
  T1->Branch("pfjetSFdn12",pfjetSFdn12,"pfjetSFdn12[npfjets12]/F");

  if(isMC){
 
    T1->Branch("ngenjets01", &ngenjets01, "ngenjets01/I");
    T1->Branch("genjetpT01",genjetpT01,"genjetpT01[ngenjets01]/F");
    T1->Branch("genjetarea01",genjetarea01,"genjetarea01[ngenjets01]/F");
    T1->Branch("genjety01",genjety01,"genjety01[ngenjets01]/F");
    T1->Branch("genjetphi01",genjetphi01,"genjetphi01[ngenjets01]/F") ;
    T1->Branch("genjetenr01",genjetenr01,"genjetenr01[ngenjets01]/F") ;
   
    T1->Branch("ngenjets02", &ngenjets02, "ngenjets02/I");
    T1->Branch("genjetpT02",genjetpT02,"genjetpT02[ngenjets02]/F");
    T1->Branch("genjetarea02",genjetarea02,"genjetarea02[ngenjets02]/F");
    T1->Branch("genjety02",genjety02,"genjety02[ngenjets02]/F");
    T1->Branch("genjetphi02",genjetphi02,"genjetphi02[ngenjets02]/F") ;
    T1->Branch("genjetenr02",genjetenr02,"genjetenr02[ngenjets02]/F") ;
    
    T1->Branch("ngenjets03", &ngenjets03, "ngenjets03/I");
    T1->Branch("genjetpT03",genjetpT03,"genjetpT03[ngenjets03]/F");
    T1->Branch("genjetarea03",genjetarea03,"genjetarea03[ngenjets03]/F");
    T1->Branch("genjety03",genjety03,"genjety03[ngenjets03]/F");
    T1->Branch("genjetphi03",genjetphi03,"genjetphi03[ngenjets03]/F") ;
    T1->Branch("genjetenr03",genjetenr03,"genjetenr03[ngenjets03]/F") ;
   
    T1->Branch("ngenjets04", &ngenjets04, "ngenjets04/I");
    T1->Branch("genjetpT04",genjetpT04,"genjetpT04[ngenjets04]/F");
    T1->Branch("genjetarea04",genjetarea04,"genjetarea04[ngenjets04]/F");
    T1->Branch("genjety04",genjety04,"genjety04[ngenjets04]/F");
    T1->Branch("genjetphi04",genjetphi04,"genjetphi04[ngenjets04]/F") ;
    T1->Branch("genjetenr04",genjetenr04,"genjetenr04[ngenjets04]/F") ;
    
    T1->Branch("ngenjets05", &ngenjets05, "ngenjets05/I");
    T1->Branch("genjetpT05",genjetpT05,"genjetpT05[ngenjets05]/F");
    T1->Branch("genjetarea05",genjetarea05,"genjetarea05[ngenjets05]/F");
    T1->Branch("genjety05",genjety05,"genjety05[ngenjets05]/F");
    T1->Branch("genjetphi05",genjetphi05,"genjetphi05[ngenjets05]/F") ;
    T1->Branch("genjetenr05",genjetenr05,"genjetenr05[ngenjets05]/F") ;
   
    T1->Branch("ngenjets06", &ngenjets06, "ngenjets06/I");
    T1->Branch("genjetpT06",genjetpT06,"genjetpT06[ngenjets06]/F");
    T1->Branch("genjetarea06",genjetarea06,"genjetarea06[ngenjets06]/F");
    T1->Branch("genjety06",genjety06,"genjety06[ngenjets06]/F");
    T1->Branch("genjetphi06",genjetphi06,"genjetphi06[ngenjets06]/F") ;
    T1->Branch("genjetenr06",genjetenr06,"genjetenr06[ngenjets06]/F") ;
    
    T1->Branch("ngenjets07", &ngenjets07, "ngenjets07/I");
    T1->Branch("genjetpT07",genjetpT07,"genjetpT07[ngenjets07]/F");
    T1->Branch("genjetarea07",genjetarea07,"genjetarea07[ngenjets07]/F");
    T1->Branch("genjety07",genjety07,"genjety07[ngenjets07]/F");
    T1->Branch("genjetphi07",genjetphi07,"genjetphi07[ngenjets07]/F") ;
    T1->Branch("genjetenr07",genjetenr07,"genjetenr07[ngenjets07]/F") ;
   
    T1->Branch("ngenjets08", &ngenjets08, "ngenjets08/I");
    T1->Branch("genjetpT08",genjetpT08,"genjetpT08[ngenjets08]/F");
    T1->Branch("genjetarea08",genjetarea08,"genjetarea08[ngenjets08]/F");
    T1->Branch("genjety08",genjety08,"genjety08[ngenjets08]/F");
    T1->Branch("genjetphi08",genjetphi08,"genjetphi08[ngenjets08]/F") ;
    T1->Branch("genjetenr08",genjetenr08,"genjetenr08[ngenjets08]/F") ;
    
    T1->Branch("ngenjets09", &ngenjets09, "ngenjets09/I");
    T1->Branch("genjetpT09",genjetpT09,"genjetpT09[ngenjets09]/F");
    T1->Branch("genjetarea09",genjetarea09,"genjetarea09[ngenjets09]/F");
    T1->Branch("genjety09",genjety09,"genjety09[ngenjets09]/F");
    T1->Branch("genjetphi09",genjetphi09,"genjetphi09[ngenjets09]/F") ;
    T1->Branch("genjetenr09",genjetenr09,"genjetenr09[ngenjets09]/F") ;
   
    T1->Branch("ngenjets10", &ngenjets10, "ngenjets10/I");
    T1->Branch("genjetpT10",genjetpT10,"genjetpT10[ngenjets10]/F");
    T1->Branch("genjetarea10",genjetarea10,"genjetarea10[ngenjets10]/F");
    T1->Branch("genjety10",genjety10,"genjety10[ngenjets10]/F");
    T1->Branch("genjetphi10",genjetphi10,"genjetphi10[ngenjets10]/F") ;
    T1->Branch("genjetenr10",genjetenr10,"genjetenr10[ngenjets10]/F") ;
   
    T1->Branch("ngenjets11", &ngenjets11, "ngenjets11/I");
    T1->Branch("genjetpT11",genjetpT11,"genjetpT11[ngenjets11]/F");
    T1->Branch("genjetarea11",genjetarea11,"genjetarea11[ngenjets11]/F");
    T1->Branch("genjety11",genjety11,"genjety11[ngenjets11]/F");
    T1->Branch("genjetphi11",genjetphi11,"genjetphi11[ngenjets11]/F") ;
    T1->Branch("genjetenr11",genjetenr11,"genjetenr11[ngenjets11]/F") ;
    
    T1->Branch("ngenjets12", &ngenjets12, "ngenjets12/I");
    T1->Branch("genjetpT12",genjetpT12,"genjetpT12[ngenjets12]/F");
    T1->Branch("genjetarea12",genjetarea12,"genjetarea12[ngenjets12]/F");
    T1->Branch("genjety12",genjety12,"genjety12[ngenjets12]/F");
    T1->Branch("genjetphi12",genjetphi12,"genjetphi12[ngenjets12]/F") ;
    T1->Branch("genjetenr12",genjetenr12,"genjetenr12[ngenjets12]/F") ;
   
  } //isMC
  
      
  Nevt=0;
  irunold = -1;
  
  for (int ix=0; ix<32; ix++) { mypow_2[ix] = pow(2,ix);}
  
}


MCJetsMINIAOD_NTuplizer::~MCJetsMINIAOD_NTuplizer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MCJetsMINIAOD_NTuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& pset) {

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
      wtfact = weight2*eventinfo->weight();
      event_weight = eventinfo->weight();
     //cout<<"weight "<<event_weight<<endl;
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
  

 npu_vert = 0;

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

   npu_vert = npu;
   
    }//isMC
   else {  if(ihlttrg[nHLTmx]==0) { return; } }
   
 
  Handle<VertexCollection> primaryVertices;
  
  iEvent.getByToken(tok_primaryVertices_, primaryVertices); 
 
   nvert = 0;
   nchict = 0;

  if (primaryVertices.isValid()) {
    int ndofct_org=0;
    int nchict_org=0;
    int nvert_org = 0;
    for (reco::VertexCollection::const_iterator vert=primaryVertices->begin(); vert<primaryVertices->end(); vert++) {
      nvert_org++;
      if (vert->isValid() && !vert->isFake()) {
	if (vert->ndof()>7) { 
	  ndofct_org++;
	  if (vert->normalizedChi2()<5) nchict_org++;
		}
      }
    }
    
    nvert = nvert_org;
    nchict = nchict_org;
    
    nprim = min(99,nvert) + 100*min(99,ndofct_org) + 10000*min(99,nchict);
  
}  
  
  edm::Handle<edm::View<pat::Jet>/*reco::PFJetCollection*/> PFJets[nalgo];
  edm::Handle<reco::GenJetCollection> GenJets[nalgo];

  vector<double> recojetptx[nalgo][njecmcmx];
  vector<double> recojetptxx[nalgo][njecmcmx];
  vector<double> recojetscl[nalgo][njecmcmx];
  vector<double> recojetjecL1[nalgo][njecmcmx];
  vector<double> recojetjec[nalgo][njecmcmx];
  vector<int> recojetindx[nalgo][njecmcmx];

	for(int ix=0; ix<nalgo; ix++){
	
	iEvent.getByToken(tok_pfjets_[ix], PFJets[ix]);
	iEvent.getByToken(tok_genjets_[ix], GenJets[ix]);
	
	for (unsigned jet = 0; jet<PFJets[ix]->size(); jet++) {
	  
	  HepLorentzVector pfjet4v((*PFJets[ix])[jet].px(),(*PFJets[ix])[jet].py(),(*PFJets[ix])[jet].pz(), (*PFJets[ix])[jet].energy());
	  
	  double tmprecpt = pfjet4v.perp();
	  double tmpreceta = pfjet4v.eta();
	  double tmprecphi = pfjet4v.phi();
	  double tmprecarea = (*PFJets[ix])[jet].jetArea();
	 
	  double total_cor = 1. ;
	  double corL1 = 1.;
	  
	  if(ix<=5){
	  
	  jecL1FastAK4->setJetPt(tmprecpt); 
	  jecL1FastAK4->setJetA(tmprecarea);
      jecL1FastAK4->setRho(*Rho_PF);
      jecL1FastAK4->setJetEta(tmpreceta);
      
      double corFactorL1Fast = jecL1FastAK4->getCorrection();
      total_cor*= corFactorL1Fast;
      tmprecpt = tmprecpt * corFactorL1Fast;
      
      corL1 = corL1 * corFactorL1Fast;
      
      jecL2RelativeAK4->setJetPt(tmprecpt);
      jecL2RelativeAK4->setJetEta(tmpreceta);
      
      double corFactorL2Relative = jecL2RelativeAK4->getCorrection();
      total_cor*= corFactorL2Relative ;
      tmprecpt = tmprecpt * corFactorL2Relative;
      
      jecL3AbsoluteAK4->setJetPt(tmprecpt); 
	  jecL3AbsoluteAK4->setJetEta(tmpreceta);
	  
	  double corFactorL3Absolute = jecL3AbsoluteAK4->getCorrection();
	  total_cor*= corFactorL3Absolute ;
	  tmprecpt = tmprecpt * corFactorL3Absolute;
	  
	  if(!isMC){
		  double corFactorL2L3Residual;
		  
		  jecL2L3ResidualAK4->setJetPt(tmprecpt);
		  jecL2L3ResidualAK4->setJetEta(tmpreceta);
    
		  corFactorL2L3Residual = jecL2L3ResidualAK4->getCorrection();
		  total_cor*= corFactorL2L3Residual;
          tmprecpt *=corFactorL2L3Residual;
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
			
				corL1 = corL1 * corFactorL1Fast;
      
				jecL2RelativeAK8->setJetPt(tmprecpt);
				jecL2RelativeAK8->setJetEta(tmpreceta);
      
				double corFactorL2Relative = jecL2RelativeAK8->getCorrection();
				total_cor*= corFactorL2Relative ;
				tmprecpt = tmprecpt * corFactorL2Relative;
      
				jecL3AbsoluteAK8->setJetPt(tmprecpt); 
				jecL3AbsoluteAK8->setJetEta(tmpreceta);
	  
				double corFactorL3Absolute = jecL3AbsoluteAK8->getCorrection();
				total_cor*= corFactorL3Absolute ;
				tmprecpt = tmprecpt * corFactorL3Absolute;
	  
				if(!isMC){
				double corFactorL2L3Residual;
		  
				jecL2L3ResidualAK8->setJetPt(tmprecpt);
				jecL2L3ResidualAK8->setJetEta(tmpreceta);
    
				corFactorL2L3Residual = jecL2L3ResidualAK8->getCorrection();
				total_cor*= corFactorL2L3Residual;
				tmprecpt *=corFactorL2L3Residual;
				}
			}//else  
	  	  
	  	  
	 // 	  cout<<"algo"<<ix+1<<" jet "<<jet+1<<" correction factor "<<total_cor<<endl;
	  	  
	 double gasureso[njecmcmx] = {0};
	  	  
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
		   /*
				if((ix==7)&&(tmprecpt<300.&&tmprecpt>60.)&&(abs(tmpreceta)<0.5)){ 
				cout<<JetRad[ix]<<" sf "<<sf<<'\t'<<sf_up<<'\t'<<sf_dn<<" reso par "<<rp<<endl;
				} 
		  */
		        bool match = false;
		        int match_gen = -1;
		        
		        for (unsigned get = 0; get<(GenJets[ix]->size()); get++) {
				HepLorentzVector genjet4v((*GenJets[ix])[get].px(),(*GenJets[ix])[get].py(),(*GenJets[ix])[get].pz(), (*GenJets[ix])[get].energy());
				if((delta2R(tmpreceta,tmprecphi,genjet4v.eta(),genjet4v.phi()) < (0.5*jetsize[ix])) &&(fabs(tmprecpt-genjet4v.perp())<(3*fabs(rp)*tmprecpt))){
					match = true;
					match_gen = get;
					break;
					}
				}
			
//				match = false;////Not Using Linear Scaling
				

				if(match&&(match_gen>=0)){
					if(isrc==0) { reso = (sf-1.)*(tmprecpt-(*GenJets[ix])[match_gen].pt())*1./tmprecpt;}
					else if(isrc==1){ reso = (sf_up-1.)*(tmprecpt-(*GenJets[ix])[match_gen].pt())*1./tmprecpt;}
					else if(isrc==2){ reso = (sf_dn-1.)*(tmprecpt-(*GenJets[ix])[match_gen].pt())*1./tmprecpt;}
					}
		        else{
				if(isrc==0) { gasureso[isrc] = gRandom->Gaus(0.,rp); }
				else { gasureso[isrc] = gasureso[0]; }
				if(isrc==0) { reso = sqrt(max(0.,(sf*sf-1))) * gasureso[isrc]; }
				else if(isrc==1) {reso = sqrt(max(0.,(sf_up*sf_up-1))) * gasureso[isrc]; }
				else if(isrc==2) {reso = sqrt(max(0.,(sf_dn*sf_dn-1))) * gasureso[isrc]; }	
			    }
	
				sup = 1.+reso;
/*	
				 if((ix==7)&&(tmprecpt<300.&&tmprecpt>60.)&&(abs(tmpreceta)<0.5)){ 
				cout<<JetRad[ix]<<" pt "<<tmprecpt<<" isrc "<<isrc<<" gausreso "<<gasureso[isrc]<<" fac "<<sup<<" match "<<match<<endl;
				}
*/
				
		 	    #endif
				
				if((total_cor<1.e-7)||(total_cor>1.e3)){total_cor = 1.;}
				
				recojetptxx[ix][isrc].push_back(sup*tmprecpt);
				recojetptx[ix][isrc].push_back(tmprecpt);
				recojetscl[ix][isrc].push_back(sup);
				recojetindx[ix][isrc].push_back(jet);
				recojetjec[ix][isrc].push_back(total_cor);
				recojetjecL1[ix][isrc].push_back(corL1);
		 
//				if(ix==7) { cout<<JetRad[ix]<<" isrc "<<isrc<<" pt "<<tmprecpt<<endl;}
 
			} // loop over isrc
		} // loop over jet no
	} // loop over ix
	
	// now shuffle 
	
	for(int ix=0 ; ix<nalgo; ix++) { 
	    for (int isrc = 0; isrc < njecmcmx; isrc++) {
	 	if(recojetptxx[ix][isrc].size()>1) { 
		for (unsigned int ij=0; ij<recojetptxx[ix][isrc].size()-1; ij++) {
			for (unsigned int jk=ij+1; jk<recojetptxx[ix][isrc].size(); jk++) {
				
				if (recojetptx[ix][isrc][jk]>recojetptx[ix][isrc][ij]) {
					
					double tmpptx = recojetptxx[ix][isrc][ij];
					double tmppt = recojetptx[ix][isrc][ij];
					double tmpscl = recojetscl[ix][isrc][ij];
					double tmpjec = recojetjec[ix][isrc][ij];
					double tmpL1 = recojetjecL1[ix][isrc][ij];
					int tmpindx = recojetindx[ix][isrc][ij];

					recojetptxx[ix][isrc][ij] = recojetptxx[ix][isrc][jk];
					recojetptx[ix][isrc][ij] = recojetptx[ix][isrc][jk];
					recojetscl[ix][isrc][ij] = recojetscl[ix][isrc][jk];
					recojetjec[ix][isrc][ij] = recojetjec[ix][isrc][jk];
					recojetjecL1[ix][isrc][ij] = recojetjecL1[ix][isrc][jk];
					recojetindx[ix][isrc][ij] = recojetindx[ix][isrc][jk];					
		
					recojetptxx[ix][isrc][jk] = tmpptx;
					recojetptx[ix][isrc][jk] = tmppt;
					recojetscl[ix][isrc][jk] = tmpscl;
					recojetjec[ix][isrc][jk] = tmpjec;
					recojetjecL1[ix][isrc][jk] = tmpL1;
					recojetindx[ix][isrc][jk] = tmpindx;
				  }
			  } //jk
		  } //ij
	 	}
   	} // nsrc	
 }// loop over ix (algo no)

  edm::Handle<pat::METCollection> pfmet_ ; 
  iEvent.getByToken(tok_mets_,pfmet_) ;
  
  miset = misphi = sumEt = -1000 ;
  
  
  if(pfmet_.isValid()){
	  miset = pfmet_->begin()->corPt();
	  misphi = pfmet_->begin()->corPhi(); 
	  sumEt = pfmet_->begin()->corSumEt() ; 
	  if(sumEt<1.) { sumEt = 1.; } 
	  }
	 

  for(int ix=0 ; ix<nalgo ; ix++) {
	  
    npfjets[ix] = 0;
   
    if(PFJets[ix].isValid()) {

      for (unsigned jet1 = 0; jet1<PFJets[ix]->size(); jet1++) {

        int jet = recojetindx[ix][0][jet1];
        
	HepLorentzVector jet4v((*PFJets[ix])[jet].px(),(*PFJets[ix])[jet].py(),(*PFJets[ix])[jet].pz(), (*PFJets[ix])[jet].energy());
	jet4v *= recojetjec[ix][0][jet1] ;

	double jec_factor = recojetjec[ix][0][jet1];
	double jec_L1 = recojetjecL1[ix][0][jet1];
	double scale_factor = recojetscl[ix][0][jet1];

        double tmppt = jet4v.perp();
        double tmpeta = jet4v.eta();
        double tmpy = jet4v.rapidity();
/*
	if(ix==7){
	cout<<"jet pt "<<tmppt<<" recojetpt "<<recojetptx[ix][0][jet1]<<" "<<recojetptx[ix][1][jet1]<<" "<<recojetptx[ix][2][jet1]<<endl;
	}
*/
  	if (abs(tmpy)>maxEta || tmppt<minPFPt) continue;
    
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

	bool looseJetID = false;
	bool tightJetID =false;
//	bool tightlepVeto = false;
	
	if(abs(tmpeta)<=2.7){
		if( (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || (abs(tmpeta)>2.4)) ){
			tightJetID = true;
			}
		if( (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || (abs(tmpeta)>2.4)) && (abs(tmpeta)<=2.7) ){
			looseJetID = true;
			}
	//	if( (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((abs(tmpeta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.9) || (abs(tmpeta)>2.4)) && (abs(tmpeta)<=2.7) ){
	//		tightlepVeto = true;
	//		}		
		}
		else{
			if((abs(tmpeta)>2.7)&&(abs(tmpeta)<3.0)){
				#ifdef Data2015 
				 if( (NEMF<0.90) && (NumNeutralParticles>2)){tightJetID = true; looseJetID = true; } 
				#elif defined(Data2016)   
				if( (NEMF>0.01) && (NHF<0.98) && (NumNeutralParticles>2)){tightJetID = true; looseJetID = true; } 
				#endif
				}
				else{
					if ((NEMF<0.90) /*&& (NumNeutralParticles>10)*/){tightJetID = true; looseJetID = true;}
					}
			}
	
	pfjettightID[ix][npfjets[ix]] = tightJetID;
	pfjetlooseID[ix][npfjets[ix]] = looseJetID;
	pfjetSF[ix][npfjets[ix]] = scale_factor;//RESO scale_factor;
        pfjetJEC[ix][npfjets[ix]] = jec_factor;
        pfjetJECL1[ix][npfjets[ix]] = jec_L1;
/*	if( jet1==0 && !tightJetID) break;
	if (!tightJetID) continue;
*/
	pfjetmom[ix][npfjets[ix]] = jet4v.rho();
	pfjetpT[ix][npfjets[ix]] = jet4v.perp();
	pfjetenr[ix][npfjets[ix]] = jet4v.e();
	pfjetthe[ix][npfjets[ix]] = jet4v.theta();
	pfjety[ix][npfjets[ix]] = jet4v.rapidity();
	pfjetphi[ix][npfjets[ix]]= jet4v.phi();
	pfjetarea[ix][npfjets[ix]] = (*PFJets[ix])[jet].jetArea() ;  
	
	pfjetpTup[ix][npfjets[ix]] = recojetptx[ix][1][jet1] ;
	pfjetpTdn[ix][npfjets[ix]] = recojetptx[ix][2][jet1] ;

	pfjetSFup[ix][npfjets[ix]] = recojetscl[ix][1][jet1] ;
        pfjetSFdn[ix][npfjets[ix]] = recojetscl[ix][2][jet1] ;
	
	if (++npfjets[ix] >=njetmx) break;
 
    }//jet1
   }//PFenJets[ix].isValid()  
    
    if (isMC) {
      
      ngenjets[ix] = 0;
   //   iEvent.getByToken(tok_genjets_[ix], GenJets[ix]);
 
      if (GenJets[ix].isValid()) {
	
		for (unsigned jet = 0; jet<GenJets[ix]->size(); jet++) {
		
		HepLorentzVector genjet4v((*GenJets[ix])[jet].px(),(*GenJets[ix])[jet].py(),(*GenJets[ix])[jet].pz(), (*GenJets[ix])[jet].energy());
		
		double tmpgenpt = genjet4v.perp();
	//  double tmpgeneta = genjet4v.eta();
		double tmpgeny = genjet4v.rapidity();
		
	     
		if (abs(tmpgeny)>maxEta || tmpgenpt<minPFPt) continue;

		genjetmom[ix][ngenjets[ix]] = genjet4v.rho() ;
		genjetpT[ix][ngenjets[ix]] = genjet4v.perp() ;
		genjetenr[ix][ngenjets[ix]] = genjet4v.e() ;
		genjetthe[ix][ngenjets[ix]] = genjet4v.theta();
		genjety[ix][ngenjets[ix]] = genjet4v.rapidity();
		genjetphi[ix][ngenjets[ix]]= genjet4v.phi();
		genjetarea[ix][ngenjets[ix]] = (*GenJets[ix])[jet].jetArea() ;
	  
	  
			if (++ngenjets[ix] >=njetmx) break;
	
		}//jet
    
       
     } //if (GenJets[ix].isValid())
 
		} //isMC
    
 } //for(int ix=0 ; ix<nalgo ; ++ix) 

  //Trigger
 

  for(int ix=0 ; ix<nalgo; ++ix) {
   
    switch(ix) {
		
	case 0 : 
    
    npfjets01 =  npfjets[ix] ;
    
    for(int jc = 0 ;jc<npfjets01 ; ++jc) { 
	
	pfjetpT01[jc] = pfjetpT[ix][jc]  ;
	pfjety01[jc] = pfjety[ix][jc] ;
	pfjetphi01[jc] = pfjetphi[ix][jc] ;
	pfjetarea01[jc] = pfjetarea[ix][jc] ; 
	pfjetenr01[jc] = pfjetenr[ix][jc] ;
	pfjetpTup01[jc] = pfjetpTup[ix][jc] ;
	pfjetpTdn01[jc] = pfjetpTdn[ix][jc] ;
	pfjettightID01[jc] = pfjettightID[ix][jc];
	pfjetlooseID01[jc] = pfjetlooseID[ix][jc];
	pfjetJEC01[jc] = pfjetJEC[ix][jc];
	pfjetJECL101[jc] = pfjetJECL1[ix][jc];
     	pfjetSF01[jc] = pfjetSF[ix][jc];
	pfjetSFup01[jc] = pfjetSFup[ix][jc];
	pfjetSFdn01[jc] = pfjetSFdn[ix][jc];
	    }
	
	if(isMC) {
	  ngenjets01 =  ngenjets[ix] ;
	  
	  for(int jc = 0 ;jc<ngenjets01 ; ++jc) {   
	
	  genjetpT01[jc] = genjetpT[ix][jc] ;
	  genjety01[jc] = genjety[ix][jc] ;
	  genjetphi01[jc] = genjetphi[ix][jc] ;
	  genjetarea01[jc] = genjetarea[ix][jc] ;
	  genjetenr01[jc] = genjetenr[ix][jc] ;
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
	pfjetenr02[jc] = pfjetenr[ix][jc] ;
	pfjetpTup02[jc] = pfjetpTup[ix][jc] ;
	pfjetpTdn02[jc] = pfjetpTdn[ix][jc] ;
	pfjettightID02[jc] = pfjettightID[ix][jc];
	pfjetlooseID02[jc] = pfjetlooseID[ix][jc];
	pfjetJEC02[jc] = pfjetJEC[ix][jc];
	pfjetJECL102[jc] = pfjetJECL1[ix][jc];
	pfjetSF02[jc] = pfjetSF[ix][jc];
	pfjetSFup02[jc] = pfjetSFup[ix][jc];
        pfjetSFdn02[jc] = pfjetSFdn[ix][jc];
	}
	
	if(isMC){
	  ngenjets02 =  ngenjets[ix] ;
	  
	  for(int jc = 0 ;jc<ngenjets02 ; ++jc) {
	 
	  genjetpT02[jc] = genjetpT[ix][jc] ;
	  genjety02[jc] = genjety[ix][jc] ;
	  genjetphi02[jc] = genjetphi[ix][jc] ;
	  genjetarea02[jc] = genjetarea[ix][jc] ;	
	  genjetenr02[jc] = genjetenr[ix][jc] ;
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
 pfjetenr03[jc] = pfjetenr[ix][jc] ;
 pfjetpTup03[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn03[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID03[jc] = pfjettightID[ix][jc];
 pfjetlooseID03[jc] = pfjetlooseID[ix][jc];
 pfjetJEC03[jc] = pfjetJEC[ix][jc];
 pfjetJECL103[jc] = pfjetJECL1[ix][jc];
 pfjetSF03[jc] = pfjetSF[ix][jc];
 pfjetSFup03[jc] = pfjetSFup[ix][jc];
 pfjetSFdn03[jc] = pfjetSFdn[ix][jc];

 }

 if(isMC){

  ngenjets03 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets03 ; ++jc){
	 
 genjetpT03[jc] = genjetpT[ix][jc]  ;
 genjety03[jc] = genjety[ix][jc] ;
 genjetphi03[jc] = genjetphi[ix][jc] ;
 genjetarea03[jc] = genjetarea[ix][jc] ;
 genjetenr03[jc] = genjetenr[ix][jc] ;
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
 pfjetenr04[jc] = pfjetenr[ix][jc] ;
 pfjetpTup04[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn04[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID04[jc] = pfjettightID[ix][jc];
 pfjetlooseID04[jc] = pfjetlooseID[ix][jc];
 pfjetJEC04[jc] = pfjetJEC[ix][jc];
 pfjetJECL104[jc] = pfjetJECL1[ix][jc];
 pfjetSF04[jc] = pfjetSF[ix][jc];
 pfjetSFup04[jc] = pfjetSFup[ix][jc];
 pfjetSFdn04[jc] = pfjetSFdn[ix][jc];

 }

 if(isMC){

  ngenjets04 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets04 ; ++jc){
 
 genjetpT04[jc] = genjetpT[ix][jc] ;
 genjety04[jc] = genjety[ix][jc] ;
 genjetphi04[jc] = genjetphi[ix][jc] ;
 genjetarea04[jc] = genjetarea[ix][jc] ;
 genjetenr04[jc] = genjetenr[ix][jc] ;
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
 pfjetenr05[jc] = pfjetenr[ix][jc] ;
 pfjetpTup05[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn05[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID05[jc] = pfjettightID[ix][jc];
 pfjetlooseID05[jc] = pfjetlooseID[ix][jc];
 pfjetJEC05[jc] = pfjetJEC[ix][jc];
 pfjetJECL105[jc] = pfjetJECL1[ix][jc];
 pfjetSF05[jc] = pfjetSF[ix][jc];
 pfjetSFup05[jc] = pfjetSFup[ix][jc];
 pfjetSFdn05[jc] = pfjetSFdn[ix][jc];
 //cout<<"sf "<<pfjetSF05[jc]<<" jec "<<pfjetJEC05[jc]<<endl;
 }

 if(isMC){

  ngenjets05 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets05 ; ++jc){
 
 genjetpT05[jc] = genjetpT[ix][jc]  ;
 genjety05[jc] = genjety[ix][jc] ;
 genjetphi05[jc] = genjetphi[ix][jc] ;
 genjetarea05[jc] = genjetarea[ix][jc] ;
 genjetenr05[jc] = genjetenr[ix][jc] ;
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
 pfjetenr06[jc] = pfjetenr[ix][jc] ;
 pfjetpTup06[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn06[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID06[jc] = pfjettightID[ix][jc];
 pfjetlooseID06[jc] = pfjetlooseID[ix][jc];
 pfjetJEC06[jc] = pfjetJEC[ix][jc];
 pfjetJECL106[jc] = pfjetJECL1[ix][jc];
 pfjetSF06[jc] = pfjetSF[ix][jc];
 pfjetSFup06[jc] = pfjetSFup[ix][jc];
 pfjetSFdn06[jc] = pfjetSFdn[ix][jc];
 }

 if(isMC){

  ngenjets06 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets06 ; ++jc){
 
 genjetpT06[jc] = genjetpT[ix][jc]  ;
 genjety06[jc] = genjety[ix][jc] ;
 genjetphi06[jc] = genjetphi[ix][jc] ;
 genjetarea06[jc] = genjetarea[ix][jc] ;
 genjetenr06[jc] = genjetenr[ix][jc] ;
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
 pfjetenr07[jc] = pfjetenr[ix][jc] ;
 pfjetpTup07[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn07[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID07[jc] = pfjettightID[ix][jc];
 pfjetlooseID07[jc] = pfjetlooseID[ix][jc];
 pfjetJEC07[jc] = pfjetJEC[ix][jc];
 pfjetJECL107[jc] = pfjetJECL1[ix][jc];
 pfjetSF07[jc] = pfjetSF[ix][jc];
 pfjetSFup07[jc] = pfjetSFup[ix][jc];
 pfjetSFdn07[jc] = pfjetSFdn[ix][jc];
 }

 if(isMC){

  ngenjets07 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets07 ; ++jc){
 
 genjetpT07[jc] = genjetpT[ix][jc]  ;
 genjety07[jc] = genjety[ix][jc] ;
 genjetphi07[jc] = genjetphi[ix][jc] ;
 genjetarea07[jc] = genjetarea[ix][jc] ;
 genjetenr07[jc] = genjetenr[ix][jc] ;
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
 pfjetenr08[jc] = pfjetenr[ix][jc] ;
 pfjetpTup08[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn08[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID08[jc] = pfjettightID[ix][jc];
 pfjetlooseID08[jc] = pfjetlooseID[ix][jc];
 pfjetJEC08[jc] = pfjetJEC[ix][jc];
 pfjetJECL108[jc] = pfjetJECL1[ix][jc];
 pfjetSF08[jc] = pfjetSF[ix][jc];
 pfjetSFup08[jc] = pfjetSFup[ix][jc];
 pfjetSFdn08[jc] = pfjetSFdn[ix][jc];
 }

 if(isMC){

  ngenjets08 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets08 ; ++jc){
 
 genjetpT08[jc] = genjetpT[ix][jc] ;
 genjety08[jc] = genjety[ix][jc] ;
 genjetphi08[jc] = genjetphi[ix][jc] ;
 genjetarea08[jc] = genjetarea[ix][jc] ;
 genjetenr08[jc] = genjetenr[ix][jc] ;
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
 pfjetenr09[jc] = pfjetenr[ix][jc] ;
 pfjetpTup09[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn09[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID09[jc] = pfjettightID[ix][jc];
 pfjetlooseID09[jc] = pfjetlooseID[ix][jc];
 pfjetJEC09[jc] = pfjetJEC[ix][jc];
 pfjetJECL109[jc] = pfjetJECL1[ix][jc];
 pfjetSF09[jc] = pfjetSF[ix][jc];
 pfjetSFup09[jc] = pfjetSFup[ix][jc];
 pfjetSFdn09[jc] = pfjetSFdn[ix][jc];
 }
 
 if(isMC){

  ngenjets09  =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets09 ; ++jc){
 
 genjetpT09[jc] = genjetpT[ix][jc]  ;
 genjety09[jc] = genjety[ix][jc] ;
 genjetphi09[jc] = genjetphi[ix][jc] ;
 genjetarea09[jc] = genjetarea[ix][jc] ;
 genjetenr09[jc] = genjetenr[ix][jc] ;
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
 pfjetenr10[jc] = pfjetenr[ix][jc] ;
 pfjetpTup10[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn10[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID10[jc] = pfjettightID[ix][jc];
 pfjetlooseID10[jc] = pfjetlooseID[ix][jc];
 pfjetJEC10[jc] = pfjetJEC[ix][jc];
 pfjetJECL110[jc] = pfjetJECL1[ix][jc];
 pfjetSF10[jc] = pfjetSF[ix][jc];
 pfjetSFup10[jc] = pfjetSFup[ix][jc];
 pfjetSFdn10[jc] = pfjetSFdn[ix][jc];
 }

 if(isMC){

  ngenjets10 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets10 ; ++jc){
 
 genjetpT10[jc] = genjetpT[ix][jc] ;
 genjety10[jc] = genjety[ix][jc] ;
 genjetphi10[jc] = genjetphi[ix][jc] ;
 genjetarea10[jc] = genjetarea[ix][jc] ;
 genjetenr10[jc] = genjetenr[ix][jc] ;
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
 pfjetenr11[jc] = pfjetenr[ix][jc] ;
 pfjetpTup11[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn11[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID11[jc] = pfjettightID[ix][jc];
 pfjetlooseID11[jc] = pfjetlooseID[ix][jc];
 pfjetJEC11[jc] = pfjetJEC[ix][jc];
 pfjetJECL111[jc] = pfjetJECL1[ix][jc];
 pfjetSF11[jc] = pfjetSF[ix][jc];
 pfjetSFup11[jc] = pfjetSFup[ix][jc];
 pfjetSFdn11[jc] = pfjetSFdn[ix][jc];
 }

 if(isMC){

  ngenjets11 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets11 ; ++jc){
 
 genjetpT11[jc] = genjetpT[ix][jc]  ;
 genjety11[jc] = genjety[ix][jc] ;
 genjetphi11[jc] = genjetphi[ix][jc] ;
 genjetarea11[jc] = genjetarea[ix][jc] ;
 genjetenr11[jc] = genjetenr[ix][jc] ;
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
 pfjetenr12[jc] = pfjetenr[ix][jc] ;
 pfjetpTup12[jc] = pfjetpTup[ix][jc] ;
 pfjetpTdn12[jc] = pfjetpTdn[ix][jc] ;
 pfjettightID12[jc] = pfjettightID[ix][jc];
 pfjetlooseID12[jc] = pfjetlooseID[ix][jc];
 pfjetJEC12[jc] = pfjetJEC[ix][jc];
 pfjetJECL112[jc] = pfjetJECL1[ix][jc];
 pfjetSF12[jc] = pfjetSF[ix][jc];
 pfjetSFup12[jc] = pfjetSFup[ix][jc];
 pfjetSFdn12[jc] = pfjetSFdn[ix][jc];

 }

 if(isMC){

  ngenjets12 =  ngenjets[ix] ;

 for(int jc = 0 ;jc<ngenjets12 ; ++jc){
 
 genjetpT12[jc] = genjetpT[ix][jc]  ;
 genjety12[jc] = genjety[ix][jc] ;
 genjetphi12[jc] = genjetphi[ix][jc] ;
 genjetarea12[jc] = genjetarea[ix][jc] ;
 genjetenr12[jc] = genjetenr[ix][jc] ;
 		}
	}

 break ;
 
    }//switch
    
  }// ix loop
  
 
  T1->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
MCJetsMINIAOD_NTuplizer::beginJob()
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
MCJetsMINIAOD_NTuplizer::endJob() 
{
// T1->Write();
 //fs->cd();
// fs->Write();
// fs->Close();

//delete fs;	
  
  theFile->cd();
  theFile->Write();
  theFile->Close();
  cout<<"End of HOinPFAlgo with event "<<Nevt<<endl;
}

// ------------ method called when starting to processes a run  ------------
void 
MCJetsMINIAOD_NTuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& pset)
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
MCJetsMINIAOD_NTuplizer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MCJetsMINIAOD_NTuplizer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MCJetsMINIAOD_NTuplizer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MCJetsMINIAOD_NTuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCJetsMINIAOD_NTuplizer);
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
