import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

# Run Over all Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# I guess MC stuff
process.load( "SimGeneral.HepPDTESSource.pythiapdt_cfi" )


# get Input file Here!
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:test/GMSB_Lambda140_CTau4000_8TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.root'
    )
)


# Make some Plots Let me see
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("GMSB_Lambda140_CTau4000_8TeV_10April.root")
)


# Bare Analyzer for now with no Parameters
process.HepMCEvt = cms.EDAnalyzer('NeutralinoLifetimeAnalyzer'
)


process.p = cms.Path(process.HepMCEvt)
