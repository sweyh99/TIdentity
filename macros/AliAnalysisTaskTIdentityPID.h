#ifndef ALIANALYSISEBYERATIOS_H
#define ALIANALYSISEBYERATIOS_H

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This analysis extracts pT-spectra of charged kaons, protons, and pions.  //
// It is based on particles identifation via the dE/dx signal of the TPC.   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

class TH1;
class THn;
class TH1F;
class TH2D;
class TH3D;
class TList;
class TTree;
class TObjArray;
class AliESDEvent;
class AliESDtrack;
class AliESDtrackCuts;
class AliPIDResponse;
class AliHeader;
class AliESDpid;
class fPIDCombined;


#include "AliAnalysisTaskSE.h"
#include "AliPIDCombined.h"
#include "AliTPCdEdxInfo.h"
#include "THnSparse.h"
#include "THn.h"
#include "TVectorF.h"
#include "TCutG.h"
#include "TTreeStream.h"
#include "AliESDv0Cuts.h"

// class AliAnalysisTaskPIDetaTreeElectrons : public AliAnalysisTaskPIDV0base {
class AliAnalysisTaskTIdentityPID : public AliAnalysisTaskSE {
public:

  // ---------------------------------------------------------------------------------
  //                           Constructor and Destructor
  // ---------------------------------------------------------------------------------

  AliAnalysisTaskTIdentityPID(const char *name);
  AliAnalysisTaskTIdentityPID();
  virtual ~AliAnalysisTaskTIdentityPID();

  enum momentType {kPi=0,kKa=1,kPr=2,kPiPi=3,kKaKa=4,kPrPr=5,kPiKa=6,kPiPr=7,kKaPr=8,kLa=9,kLaLa=10,kCh=11,kChCh=12,kBa=13,kBaBa=14};
  enum momentTypeUnlike {
    kPiPosPiNeg=0,
    kPiPosKaNeg=1,
    kPiPosPrNeg=2,
    kKaPosPiNeg=3,
    kKaPosKaNeg=4,
    kKaPosPrNeg=5,
    kPrPosPiNeg=6,
    kPrPosKaNeg=7,
    kPrPosPrNeg=8,
    kLaPosLaNeg=9,
    kChPosChNeg=10,
    kBaPosBaNeg=11,
  };
  enum trackCutBit {
    kNCrossedRowsTPC60=0,
    kNCrossedRowsTPC80=1,
    kNCrossedRowsTPC100=2,
    kMaxChi2PerClusterTPC3=3,
    kMaxChi2PerClusterTPC4=4,
    kMaxChi2PerClusterTPC5=5,
    kMaxDCAToVertexXYPtDepSmall=6,
    kMaxDCAToVertexXYPtDep=7,
    kMaxDCAToVertexXYPtDepLarge=8,
    kVertexZSmall=9,
    kVertexZ=10,
    kVertexZLarge=11,
    kEventVertexZSmall=12,
    kEventVertexZ=13,
    kEventVertexZLarge=14,
    kClusterRequirementITS=15,
    kNewITSCut=16,
    kActiveZoneSmall=17,
    kActiveZone=18,
    kActiveZoneLarge=19,
  };

  // ---------------------------------------------------------------------------------
  //                                    Methods
  // ---------------------------------------------------------------------------------

  virtual void   UserCreateOutputObjects();            // create output objects
  virtual void   UserExec(Option_t *option);           // run over event-by-event and fill output objects
  virtual void   Terminate(Option_t *);                // run only once and terminate

  // ---------------------------------------------------------------------------------
  //                                    Settings
  // ---------------------------------------------------------------------------------

  void   SetESDtrackCuts(AliESDtrackCuts * trackCuts){fESDtrackCuts = trackCuts;};
  void   SetIsMCtrue(Bool_t isMCdata = kTRUE){fMCtrue = isMCdata;};
  void   Initialize();
  void   PrintNumInBinary(UInt_t num);

  // Some boolian settings
  void   SetRunOnGrid(const Bool_t ifRunOnGrid = kTRUE)               {fRunOnGrid           = ifRunOnGrid;}
  void   SetIncludeITScuts(const Bool_t ifITSCuts = kTRUE)            {fIncludeITS          = ifITSCuts;}
  void   SetFillArmPodTree(const Bool_t ifArmpodTree = kTRUE)         {fFillArmPodTree      = ifArmpodTree;}
  void   SetTightCuts(const Bool_t ifTightCuts = kFALSE)              {fTightCuts           = ifTightCuts;}
  void   SetDeDxCheck(const Bool_t ifDeDxCheck = kFALSE)              {fDEdxCheck           = ifDeDxCheck;}
  void   SetEffMatrix(const Bool_t ifEffMatrix = kFALSE)              {fEffMatrix           = ifEffMatrix;}
  void   SetCleanSamplesOnly(const Bool_t ifSamplesOnly = kFALSE)     {fCleanSamplesOnly    = ifSamplesOnly;}
  void   SetFillBayesianProb(const Bool_t ifBayesProb = kFALSE)       {fFillBayes           = ifBayesProb;}
  void   SetFillAllCutVariables(const Bool_t ifAllCuts = kFALSE)      {fFillCuts            = ifAllCuts;}
  void   SetFillDeDxTree(const Bool_t ifDeDxTree = kFALSE)            {fFillDeDxTree        = ifDeDxTree;}
  void   SetRunFastSimulation(const Bool_t ifFastSimul = kFALSE)      {fRunFastSimulation   = ifFastSimul;}
  void   SetRunFastHighMomentCal(const Bool_t ifFastHighMom = kFALSE) {fRunFastHighMomentCal   = ifFastHighMom;}
  void   SetFillDnchDeta(const Bool_t ifDnchDetaCal = kFALSE)         {fFillDnchDeta        = ifDnchDetaCal;}
  void   SetIncludeTOF(const Bool_t ifIncludeTOF = kFALSE)            {fIncludeTOF          = ifIncludeTOF;}
  void   SetUseThnSparse(const Bool_t ifUseThnSparse = kFALSE)        {fUseThnSparse        = ifUseThnSparse;}
  void   SetUseCouts(const Bool_t ifUseCouts = kFALSE)                {fUseCouts            = ifUseCouts;}
  void   SetWeakAndMaterial(const Bool_t ifWeakAndMaterial = kFALSE)  {fWeakAndMaterial     = ifWeakAndMaterial;}
  void   SetFillTIdenTrees(const Bool_t ifTIdentity = kFALSE)         {fTIdentity           = ifTIdentity;}
  void   SetFillEventInfo(const Bool_t ifEventInfo = kFALSE)          {fEventInfo           = ifEventInfo;}
  void   SetPercentageOfEvents(const Int_t nPercentageOfEvents = 0)   {fPercentageOfEvents = nPercentageOfEvents;}


  // Setters for the systematic uncertainty checks
  void   SetSystCentEstimator(const Int_t systCentEstimator = 0)  {fSystCentEstimatetor = systCentEstimator;}
  void   SetSystDCAxy(const Int_t systDCAxy = 0)                  {fSystDCAxy           = systDCAxy;}
  void   SetSystNCrossedRows(const Int_t systNCrossedRows = 0)    {fSystCrossedRows     = systNCrossedRows;}
  void   SetSystTPCChi2(const Int_t systTPCChi2 = 0)              {fSystChi2            = systTPCChi2;}
  void   SetSystVz(const Int_t systVz = 0)                        {fSystVz              = systVz;}

  // Setters for the eta momentum dEdx and centrality bins
  void   SetSampleDeDxUpperEdge(const Float_t dEdxCleanUp = 200.) {fDEdxCleanUp         = dEdxCleanUp;}
  void   SetDeDxBinWidth(const Float_t dEdxBinWidth = 2.5)        {fDEdxBinWidth        = dEdxBinWidth;}
  void   SetDeDxLowerEdge(const Float_t dEdxLowerEdge = 20.)      {fDEdxDown            = dEdxLowerEdge;}
  void   SetDeDxUpperEdge(const Float_t dEdxUpperEdge = 1020.)    {fDEdxUp              = dEdxUpperEdge;}

  void   SetEtaLowerEdge(const Float_t etaLowerEdge = -1.)        {fEtaDown             = etaLowerEdge;}
  void   SetEtaUpperEdge(const Float_t etaUpperEdge = 1.)         {fEtaUp               = etaUpperEdge;}
  void   SetNEtabins(const Int_t nEtaBins = 20)                   {fNEtaBins            = nEtaBins;}
  void   SetMomLowerEdge(const Float_t momLowerEdge = 0.)         {fMomDown             = momLowerEdge;}
  void   SetMomUpperEdge(const Float_t momUpperEdge = 12.)        {fMomUp               = momUpperEdge;}
  void   SetNMomBins(const Int_t nMombins = 600)                  {fNMomBins            = nMombins;}

  // Set the binning of centrality
  void   SetCentralityBinning(const Int_t tmpCentbins, Float_t tmpfxCentBins[])
  {
    // Create the histograms to be used in the binning of eta, cent and momentum
    std::cout << " Info::marsland: !!!!!! Centrality binning is being set !!!!!!! " << std::endl;
    fhEta  =  new TH1F("fhEta" ,"Eta Bins"       ,fNEtaBins        ,fEtaDown, fEtaUp );
    fhPtot =  new TH1F("fhPtot","Momentum Bins"  ,fNMomBins        ,fMomDown, fMomUp );
    fhCent =  new TH1F("fhCent","Centrality Bins",tmpCentbins-1    ,tmpfxCentBins );
    // ==========================================
    // prepare real data centrality bins
    fNCentbinsData = tmpCentbins;
    fNCentBinsMC   = tmpCentbins-1;
    fxCentBins = new Float_t[fNCentbinsData];
    for (Int_t i=0; i<fNCentbinsData; i++) fxCentBins[i] =  tmpfxCentBins[i];
    fcentDownArr = new Float_t[fNCentBinsMC];
    fcentUpArr   = new Float_t[fNCentBinsMC];
    for (Int_t i=0; i<fNCentbinsData-1; i++) fcentDownArr[i] =  tmpfxCentBins[i];
    for (Int_t i=1; i<fNCentbinsData; i++)   fcentUpArr[i-1] =  tmpfxCentBins[i];
  }

  void SetMCEtaScanArray(const Int_t tmpEtaBinsMC, Float_t tmpetaDownArr[], Float_t tmpetaUpArr[])
  {
    // set MC eta values to scan
    std::cout << " Info::marsland: !!!!!! SetMCEtaScanArray is being set !!!!!!! " << std::endl;
    fNEtaWinBinsMC = tmpEtaBinsMC;
    fetaDownArr = new Float_t[fNEtaWinBinsMC];
    fetaUpArr   = new Float_t[fNEtaWinBinsMC];
    for (Int_t i=0; i<fNEtaWinBinsMC; i++) {
      fetaDownArr[i] =  tmpetaDownArr[i];
      fetaUpArr[i]   =  tmpetaUpArr[i];
    }
  }

  void SetMCResonanceArray(const Int_t tmpNRes, TString tmpResArr[])
  {
    // set MC eta values to scan
    std::cout << " Info::marsland: !!!!!! SetMCResonanceArray is being set !!!!!!! " << std::endl;
    fNResBins = tmpNRes;
    fResonances = new TString[fNResBins];
    for (Int_t i=0; i<fNResBins; i++) fResonances[i] = tmpResArr[i];

  }

  void SetMCBaryonArray(const Int_t tmpNBar, Int_t tmpBarArr[])
  {
    // set MC eta values to scan
    std::cout << " Info::marsland: !!!!!! SetMCBaryonArray is being set !!!!!!! " << std::endl;
    fNBarBins = tmpNBar;
    fBaryons = new Int_t[fNBarBins];
    for (Int_t i=0; i<fNBarBins; i++) fBaryons[i] = tmpBarArr[i];
  }

  void SetMCMomScanArray(const Int_t tmpMomBinsMC, Float_t tmppDownArr[], Float_t tmppUpArr[])
  {
    // set MC momentum values to scan
    std::cout << " Info::marsland: !!!!!! SetMCMomScanArray is being set !!!!!!! " << std::endl;
    fNMomBinsMC = tmpMomBinsMC;
    fpDownArr = new Float_t[fNMomBinsMC];
    fpUpArr   = new Float_t[fNMomBinsMC];
    for (Int_t i=0; i<fNMomBinsMC; i++) {
      fpDownArr[i] =  tmppDownArr[i];
      fpUpArr[i]   =  tmppUpArr[i];
    }
  }

  void SetLookUpTableFirstMoments(TTree *lookUpTree, Int_t partType, Float_t pArr[],Float_t centArr[],Float_t etaArr[],const Int_t tmpMomBinsMC, const Int_t tmpCentbins, const Int_t tmpEtaBinsMC)
  {
    // set MC eta values to scan
    std::cout << " Info::marsland: !!!!!! SetLookUpTableFirstMoments is being set !!!!!!!   " << std::endl;
    //
    // fill arrays from lookup table
    TH1D *h=NULL, *h1=NULL;
    for (Int_t imom=0; imom<tmpMomBinsMC; imom++){
      for (Int_t icent=0; icent<tmpCentbins; icent++){
        for (Int_t ieta=0; ieta<tmpEtaBinsMC; ieta++){
          //
          // with resonances
          lookUpTree->Draw(Form("momentPos.fElements[%d]-momentNeg.fElements[%d]",partType,partType),Form("abs(etaUp-%f)<0.01&&abs(pDown-%f)<0.01&&abs(centDown-%f)<0.01",etaArr[ieta],pArr[imom],centArr[icent]),"goff");
          h= (TH1D*)lookUpTree->GetHistogram()->Clone(); h-> SetName("Res");
          if (partType==0)  fPiFirstMoments[0][imom][icent][ieta] = h->GetMean();
          if (partType==1)  fKaFirstMoments[0][imom][icent][ieta] = h->GetMean();
          if (partType==2)  fPrFirstMoments[0][imom][icent][ieta] = h->GetMean();
          if (partType==9)  fLaFirstMoments[0][imom][icent][ieta] = h->GetMean();
          if (partType==11) fChFirstMoments[0][imom][icent][ieta] = h->GetMean();
          delete h;
          //
          // without resonances
          lookUpTree->Draw(Form("noResmomentPos.fElements[%d]-noResmomentNeg.fElements[%d]",partType,partType),Form("abs(etaUp-%f)<0.01&&abs(pDown-%f)<0.01&&abs(centDown-%f)<0.01",etaArr[ieta],pArr[imom],centArr[icent]),"goff");
          h1= (TH1D*)lookUpTree->GetHistogram()->Clone(); h1-> SetName("noRes");
          if (partType==0)  fPiFirstMoments[1][imom][icent][ieta] = h1->GetMean();
          if (partType==1)  fKaFirstMoments[1][imom][icent][ieta] = h1->GetMean();
          if (partType==2)  fPrFirstMoments[1][imom][icent][ieta] = h1->GetMean();
          if (partType==9)  fLaFirstMoments[1][imom][icent][ieta] = h1->GetMean();
          if (partType==11) fChFirstMoments[1][imom][icent][ieta] = h1->GetMean();
          delete h1;

        }
      }
    }

  }

private:

  AliAnalysisTaskTIdentityPID(const AliAnalysisTaskTIdentityPID&);
  AliAnalysisTaskTIdentityPID& operator=(const AliAnalysisTaskTIdentityPID&);

  // ---------------------------------------------------------------------------------
  //                                   Functions
  // ---------------------------------------------------------------------------------

  void  FillTPCdEdxReal();                   // Main function to fill all info + TIden
  void  FillTPCdEdxCheck();                  // Quick check for the TPC dEdx
  void  FillTPCdEdxMC();                     // Fill all info + TIdenMC from MC to do MC closure test
  void  FastGen();                           // Run over galice.root for Fastgen
  void  CalculateFastGenHigherMoments();     // Run over galice.root for Fastgen and calculate higher moments
  void  WeakAndMaterial();                   // Look full acceptance, weak decay and material
  void  FillDnchDeta();                      // Fill dnch/deta values for each cent and eta bin
  void  FillTPCdEdxMCEffMatrix();            // Prepare efficiency matrix
  void  FillCleanElectrons();                // Fill Clean Electrons
  void  FillCleanPions();                    // Fill Clean Pions
  void  SelectCleanSamplesFromV0s(AliESDv0 *v0, AliESDtrack *track0, AliESDtrack *track1);
  Bool_t  ApplyDCAcutIfNoITSPixel(AliESDtrack *track);
  void  CalculateMedianTPCDCAinPhi();
  Int_t CountEmptyEvents(Int_t counterBin);  // Just count if there is empty events
  void  BinLogAxis(TH1 *h);
  void  CalculateEventVariables();


  // ---------------------------------------------------------------------------------
  //                                   Members
  // ---------------------------------------------------------------------------------


  AliPIDResponse   * fPIDResponse;            //! PID response object
  AliESDEvent      * fESD;                    //! ESD object
  TList            * fListHist;               //! list for histograms
  AliESDtrackCuts  * fESDtrackCuts;           // basic cut variables
  AliESDv0Cuts     * fESDtrackCutsV0;         // basic cut variables for V0
  AliESDtrackCuts  * fESDtrackCutsCleanSamp;  // basic cut variables for clean pion and electron form V0s
  AliPIDCombined   * fPIDCombined;            //! combined PID object
  AliTPCdEdxInfo   * fTPCdEdxInfo;            // detailed dEdx info
  AliStack         * fMCStack;                  // stack object to get Mc info

  TTree            * fTree;                   // data Tree for real Data
  TTree            * fIdenTree;               // data tree for TIdentity
  TTree            * fIdenTreeMC;             // data tree for TIdentity
  TTree            * fArmPodTree;             // Tree for clean pion and proton selection
  TTreeSRedirector * fTreeSRedirector;        //! temp tree to dump output
  TTree            * fTreeMCrec;              // tree for reconstructed moments
  TTree            * fTreeMCgen;              // tree for reconstructed moments
  TTree            * fTreeDnchDeta;           // tree for dnch/deta calculation
  TTree            * fTreeMC;                 // tree for mc samples
  TTree            * fTreedEdxCheck;          // tree to check dEdx performance for a small data sample
  TTree            * fTreeBayes;              // tree to save bayesian probabilities
  TTree            * fTreeCuts;               // tree to save all variables for control plots
  TTree            * fTreeMCFullAcc;          // tree with full acceptance filled with MC
  TTree            * fTreeResonance;          // tree with full acceptance filled with MC
  TTree            * fTreeMCgenMoms;          // tree with higher moment calculations
  TTree            * fTreeEvents;
  TTree            * fTreeDScaled;

  TH1F             * fhEta;                   // helper histogram for TIdentity tree
  TH1F             * fhCent;                  // helper histogram for TIdentity tree
  TH1F             * fhPtot;                  // helper histogram for TIdentity tree
  TH1F             * fHistPhiTPCcounterA;         // helper histogram for TIdentity tree
  TH1F             * fHistPhiTPCcounterC;         // helper histogram for TIdentity tree
  TH1F             * fHistPhiTPCcounterAITS;         // helper histogram for TIdentity tree
  TH1F             * fHistPhiTPCcounterCITS;         // helper histogram for TIdentity tree
  TH1F             * fHistPhiITScounterA;         // helper histogram for TIdentity tree
  TH1F             * fHistPhiITScounterC;         // helper histogram for TIdentity tree


  THnSparseF       * fHndEdx;                 // histogram which hold all dEdx info
  THnSparseF       * fHnExpected;             // histogram which hold all PIDresponse info
  THnSparseF       * fHnCleanEl;              // histogram which hold Clean Electrons
  THnSparseF       * fHnCleanKa;              // histogram which hold Clean Kaons
  THnSparseF       * fHnCleanDe;              // histogram which hold Clean Deuterons

  UInt_t            fTrackCutBits;           // integer which hold all cut variations as bits
  Int_t             myBin[3];                // binning array to be used for TIdentity module
  Int_t             myBinMC[3];              // binning array to be used for MC TIdentity module
  Double_t          fEtaDown;
  Double_t          fEtaUp;
  Int_t             fNEtaBins;
  Int_t             fPercentageOfEvents;     // when only a fPercentageOfEvents is enough

  Bool_t            fRunOnGrid;              // flag if real data or MC is processed
  Bool_t            fMCtrue;                 // flag if real data or MC is processed
  Bool_t            fTIdentity;              // flag if tidentity trees are to be filled
  Bool_t            fEventInfo;              // flag if event info and downscaled track tree is filled
  Bool_t            fWeakAndMaterial;        // flag for the Weak and Material analysis
  Bool_t            fEffMatrix;              // flag for efficiency matrix filling
  Bool_t            fDEdxCheck;              // flag to check only the dEdx performance
  Bool_t            fCleanSamplesOnly;       // flag for only clean sample production
  Bool_t            fTightCuts;              // addtional cuts from jens and Marian
  Bool_t            fIncludeITS;             // decide whether to use ITS or not
  Bool_t            fFillBayes;              // switch whether to use bayesian PID or not
  Bool_t            fFillCuts;               // switch whether to fill all cut variables
  Bool_t            fFillDeDxTree;           // switch whether to fill dEdx tree
  Bool_t            fFillArmPodTree;         // switch whether to fill clean sample tree
  Bool_t            fRunFastSimulation;      // when running over galice.root do not fill other objects
  Bool_t            fRunFastHighMomentCal;   // when running over galice.root do not fill other objects

  Bool_t            fFillDnchDeta;           // switch on calculation of the dncdeta for fastgens
  Bool_t            fIncludeTOF;             // Include TOF information to investigate the efficiency loss effects on observable
  Bool_t            fUseThnSparse;           // in case thnsparse is filled
  Bool_t            fUseCouts;               // for debugging

  Int_t             fNMomBins;               // number of mombins --> for 20MeV slice 150 and 10MeV 300
  Float_t           fMomDown;                // bottom limit for the momentum range (default 0.2)
  Float_t           fMomUp;                  // uppper limit for the momentum range (default 3.2)
  Float_t           fDEdxBinWidth;           // bin width for the dEdx histograms (default 2.5)
  Float_t           fDEdxUp;                 // bottom limit for dEdx histogram (default 20)
  Float_t           fDEdxDown;               // upper limit for dEdx histogram (default 1020)
  Float_t           fDEdxCleanUp;            // upper limit for dEdx histogram of clean kaons and electrons (default 140)

  Float_t           fArmPodTPCSignal;
  Float_t           fArmPodptot;
  Float_t           fArmPodEta;
  Float_t           fArmPodCentrality;
  Float_t           fQt;
  Float_t           fAlfa;
  Float_t           fPiNSigmasTOF;           // TOF N sigma for Pion
  Float_t           fPrNSigmasTOF;           // TOF N sigma for Proton

  Float_t           fDEdxEl;                 // Expected Electron dEdx
  Float_t           fDEdxKa;                 // Expected Kaon dEdx
  Float_t           fDEdxPi;                 // Expected Pion dEdx
  Float_t           fDEdxPr;                 // Expected Proton dEdx
  Float_t           fDEdxDe;                 // Expected Proton dEdx

  Float_t           fSigmaEl;                // Expected Electron sigma
  Float_t           fSigmaKa;                // Expected Kaon sigma
  Float_t           fSigmaPi;                // Expected Pion sigma
  Float_t           fSigmaPr;                // Expected Proton sigma
  Float_t           fSigmaDe;                // Expected Proton sigma

  Float_t           fNSigmasElTPC;           // TOF N sigma for Electron
  Float_t           fNSigmasPiTPC;           // TOF N sigma for Pion
  Float_t           fNSigmasKaTPC;           // TOF N sigma for Kaon
  Float_t           fNSigmasPrTPC;           // TOF N sigma for Proton
  Float_t           fNSigmasDeTPC;           // TOF N sigma for Proton

  Float_t           fTPCSignalMC;
  Float_t           fPtotMC;
  Float_t           fPtotMCtruth;
  Float_t           fPtMC;
  Float_t           fEtaMC;
  Float_t           fCentralityMC;
  Int_t             fSignMC;

  Float_t           fPxMC;                     // x component of momentum
  Float_t           fPyMC;                     // y component of momentum
  Float_t           fPzMC;                     // z component of momentum

  Float_t           fElMC;
  Float_t           fPiMC;
  Float_t           fKaMC;
  Float_t           fPrMC;
  Float_t           fDeMC;
  Float_t           fMuMC;
  Float_t           fLaMC;

  Float_t           fPtotMCgen;
  Float_t           fPtMCgen;
  Float_t           fEtaMCgen;
  Float_t           fCentralityMCgen;
  Int_t             fSignMCgen;
  Double_t          fMCImpactParameter;

  Float_t           fElMCgen;
  Float_t           fPiMCgen;
  Float_t           fKaMCgen;
  Float_t           fPrMCgen;
  Float_t           fDeMCgen;
  Float_t           fMuMCgen;
  Float_t           fLaMCgen;
  Float_t           fBaMCgen;


  Float_t           fPx;                     // x component of momentum
  Float_t           fPy;                     // y component of momentum
  Float_t           fPz;                     // z component of momentum
  Float_t           fPtot;                   // TPC momentum
  Float_t           fPt;                     // Transverse momentum
  Float_t           fY;                      // rapidity

  Int_t              fMultiplicity;           // Multiplicity in case of PbPb
  Int_t              fMultiplicityMC;
  Float_t            fCentrality;             // centrality information
  Double_t           fVz;                     // Vertex position
  ULong64_t          fEventGID;               // global Event Id
  Int_t              fEventGIDMC;             // global MC event id
  Int_t              fEventCountInFile;       // event count per job
  Int_t              fEvent;                  // Event counter for Christian
  Int_t              fEventMC;                // Event id for MC data
  Int_t              fEventMCgen;             // Event id for MC generated

  Float_t            fTPCSignal;              // Measured dE/dx
  Double_t           myDeDx;                  // dEdx for TIdentity module
  Int_t              signNew;                 // Sign Info for TIdentity module
  Double_t           myDeDxMC;                  // dEdx for TIdentity module
  Int_t              signNewMC;                 // Sign Info for TIdentity module
  Float_t            fEta;                    // pseudo rapidity
  Float_t            fNContributors;          // Ntracks
  Float_t            fTheta;                  // theta
  Float_t            fPhi;                    // azimut angle
  Int_t              fSign;                   // sign of the particle
  Int_t              fTPCShared;              // number of shared clusters
  Int_t              fNcl;                    // number of points used for dEdx

  Int_t              fNResBins;
  Int_t              fNBarBins;
  Int_t              fNEtaWinBinsMC;
  Int_t              fNMomBinsMC;
  Int_t              fNCentBinsMC;
  Int_t              fNResModeMC;
  Int_t              fNCentbinsData;
  Float_t            fMissingCl;
  Int_t              fTPCMult;
  Int_t              fEventMult;
  UInt_t             fTimeStamp;
  Float_t            fIntRate;

  // Additional cuts from marian
  Bool_t             fIsITSpixel01;           // if track has hits in innermost 2 pixels of ITS
  Int_t              fNITSclusters;           // number of ITS clusters
  Float_t            fPrimRestriction;        // prim vertex cut recommended by marian
  Float_t            fTPCvZ;                  // TPC vertex

  //   CleanSample cuts
  Bool_t             fCleanPionsFromK0;
  Bool_t             fCleanPion0FromK0;
  Bool_t             fCleanPion1FromK0;
  Bool_t             fCleanPion0FromLambda;
  Bool_t             fCleanPion1FromLambda;
  Bool_t             fCleanProton0FromLambda;
  Bool_t             fCleanProton1FromLambda;
  Bool_t             fHasTrack0FirstITSlayer;
  Bool_t             fHasTrack1FirstITSlayer;
  Bool_t             fHasV0FirstITSlayer;

  TCutG              *fPionCutG;
  TCutG              *fAntiProtonCutG;
  TCutG              *fProtonCutG;



  //  Variables for systematic uncertainty checks
  //  B field configurations -->  use default settings and analyse the following set of runs
  //  ***********************************************
  //  Field (++)  --> run interval is [137161, 138275]
  //  Field (--)  --> run interval is [138364, 139510]
  //  ***********************************************
  Int_t              fSystCentEstimatetor;   // 0 --> "V0M"   ||| -1 -->  "TRK" ||| +1 --> "CL1"
  Int_t              fSystCrossedRows;       // 0 -->  80     ||| -1 -->   60   ||| +1 -->  100
  Int_t              fSystDCAxy;             // 0 --> default ||| -1 --> -sigma ||| +1 --> +sigma
  Int_t              fSystChi2;              // 0 -->  4      ||| -1 -->    3   ||| +1 -->   5
  Int_t              fSystVz;                // 0 -->  10     ||| -1 -->    8   ||| +1 -->   12
  Float_t            fPiFirstMoments[2][4][20][20];    //[fNResModeMC][fNMomBinsMC][fNCentBinsMC][fNEtaWinBinsMC]
  Float_t            fKaFirstMoments[2][4][20][20];    //[fNResModeMC][fNMomBinsMC][fNCentBinsMC][fNEtaWinBinsMC]
  Float_t            fPrFirstMoments[2][4][20][20];    //[fNResModeMC][fNMomBinsMC][fNCentBinsMC][fNEtaWinBinsMC]
  Float_t            fLaFirstMoments[2][4][20][20];    //[fNResModeMC][fNMomBinsMC][fNCentBinsMC][fNEtaWinBinsMC]
  Float_t            fChFirstMoments[2][4][20][20];    //[fNResModeMC][fNMomBinsMC][fNCentBinsMC][fNEtaWinBinsMC]
  Float_t            *fetaDownArr;           //[fNEtaWinBinsMC]
  Float_t            *fetaUpArr;             //[fNEtaWinBinsMC]
  Float_t            *fcentDownArr;          //[fNCentBinsMC]
  Float_t            *fcentUpArr;            //[fNCentBinsMC]
  Float_t            *fpDownArr;             //[fNMomBinsMC]
  Float_t            *fpUpArr;               //[fNMomBinsMC]
  Float_t            *fxCentBins;            //[fNCentbinsData]
  TString            *fResonances;           //[fNResBins]
  Int_t              *fBaryons;              //[fNBarBins]

  //
  // control and QA histograms
  //
  THnF             * fHistPosEffMatrixRec;       // histogram efficiency matrix --> reconstructed traks
  THnF             * fHistNegEffMatrixRec;       // histogram efficiency matrix --> generated traks
  THnF             * fHistPosEffMatrixGen;       // histogram efficiency matrix --> reconstructed pions
  THnF             * fHistNegEffMatrixGen;       // histogram efficiency matrix --> generated pions

  TH1F             * fHistEmptyEvent;         // control histogram for empty event
  TH1F             * fHistCentrality;         // control histogram for centrality
  TH1F             * fHistCentralityImpPar;         // control histogram for centrality
  TH1F             * fHistImpParam;           // control histogram for impact parameter
  TH1F             * fHistVertex;             // control histogram for vertexZ
  THnF             * fHistdEdxTPC;            // 5D hist of dEdx from all TPC
  TH2F             * fHistArmPod;             // control histogram for Armanteros Podolanski plot

  TVectorF         * fPhiTPCdcarA;  // track counter
  TVectorF         * fPhiTPCdcarC; // dedx info counter
  TVectorF         * fCacheTrackCounters;  // track counter
  TVectorF         * fCacheTrackdEdxRatio; // dedx info counter
  TVectorF         * fCacheTrackNcl;       // ncl counter
  TVectorF         * fCacheTrackChi2;      // chi2 counter
  TVectorF         * fCacheTrackMatchEff;  // matchEff counter
  TGraph           * fLumiGraph;           // grap for the interaction rate info for a run


  ClassDef(AliAnalysisTaskTIdentityPID, 3);

};

#endif
