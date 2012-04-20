import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:GMSB_Lambda140_CTau4000_8TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.root'
    )
)

process.demo = cms.EDAnalyzer('DPAnalysis',

    rootFileName     = cms.untracked.string('Photon_2012A_test'), # Out Put File
    triggerName      = cms.untracked.string('HLT_Photon90_CaloIdVL_IsoL_v4'),
    trigSource = cms.InputTag("TriggerResults","","HLT"),
    jetSource   = cms.InputTag("ak5PFJets"),
    metSource   = cms.InputTag("pfMet"),
    muonSource  = cms.InputTag("muons"),
    electronSource   = cms.InputTag("gsfElectrons"),
    photonSource     = cms.InputTag("photons"),
    pvSource         = cms.InputTag("offlinePrimaryVertices"),
    beamSpotSource   = cms.InputTag("offlineBeamSpot"),
    EBRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
    EERecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),

#    pileupSource       = cms.InputTag("addPileupInfo"),
    # Set up cuts for physics objects
    # vertex cuts                z   ndof   d0 
    vtxCuts       = cms.vdouble( 99,    0,  99 ),
    # jet cuts                   pt    eta  nJets
    jetCuts       = cms.vdouble( 30. , 2.4, 3 ),
    # photon cuts                pt   eta  dR   sMinMin, sMinMax,  Num  
    photonCuts    = cms.vdouble( 65, 2.4, 0.3,   0.15,      0.3,    1  ),
    # photon isolation           trk,  ecalSumEt, ecalR, hcalSumEt, hcalR 
    photonIso     = cms.vdouble(  0.2,       4.5,   0.1,       4.0,   0.1 ),
    # electron cuts              pt  eta  EBIso  EEIso nLostHit  
    electronCuts  = cms.vdouble( 25, 2.4,  0.15,   0.1,      2 ),
    metCuts       = cms.vdouble(  0. ),
    muonCuts      = cms.vdouble( 25, 2.1, 0.2, 0.3 ),
    #MC   stuff
    isData        = cms.bool(False),         # Are you Running Data Or MC?
    genParticles  = cms.InputTag("genParticles"),      # MC source
    ctau          = cms.double(4000 ),
    seedGenNum    = cms.double(117),         # Choose different Seed To Generate Neutralino  Lab frame  Lifetime                          

)


process.p = cms.Path(process.demo)
