# Auto generated configuration file
# using: 
# Revision: 1.357 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/EightTeV/GMSB_Lambda100_CTau1000_8TeV_pythia6_cff.py -s GEN:ProductionFilterSequence,SIM,DIGI,L1,DIGI2RAW --conditions FrontierConditions_GlobalTag,START52_V2B::All -n 5 --mc --no_exec --datatier GEN-SIM-RAW --eventcontent RAWSIM
import FWCore.ParameterSet.Config as cms

process = cms.Process('DIGI2RAW')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.RandomNumberGeneratorService.generator.initialSeed =  5238398
process.RandomNumberGeneratorService.VtxSmeared.initialSeed =  4017956
process.RandomNumberGeneratorService.g4SimHits.initialSeed =  4024435
process.RandomNumberGeneratorService.mix.initialSeed =  2830407
process.RandomNumberGeneratorService.mixData.initialSeed =  9797736
process.RandomNumberGeneratorService.simSiStripDigis.initialSeed =  2039867
process.RandomNumberGeneratorService.simSiPixelDigis.initialSeed =  4234653
process.RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed = 9766348
process.RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed = 7065557
process.RandomNumberGeneratorService.simMuonDTDigis.initialSeed = 5368037
process.RandomNumberGeneratorService.simMuonCSCDigis.initialSeed = 8550378
process.RandomNumberGeneratorService.simMuonRPCDigis.initialSeed = 4743578
process.RandomNumberGeneratorService.simCastorDigis.initialSeed = 6222599


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(80)
)

# Input source
process.source = cms.Source("EmptySource")

#source = cms.Source("LHESource",
#    fileNames = cms.untracked.vstring(
#    'file:../Configuration/Generator/data/gmsb_lambda140_8TeV_pythia6_ctau0.slha')
#)


process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('GMSB Lambda=140TeV and ctau=1 at 8 TeV'),
    name = cms.untracked.string('$Source: /afs/cern.ch/project/cvs/reps/CMSSW/CMSSW/Configuration/GenProduction/python/EightTeV/GMSB_Lambda140_CTau1_8TeV_pythia6_cff.py,v $')
)

# Output definitionls
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('GMSB-RAW/gmsb_Lambda140_CTau1_8TeV_RAW1.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'START52_V2B::All'

process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(8000.0),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.921 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.227 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model'),
        processParameters = cms.vstring('MSEL=39                  ! All SUSY processes', 
            'IMSS(1) = 11             ! Spectrum from external SLHA file', 
            'IMSS(11) = 1             ! keeps gravitino mass from being overwritten', 
            'IMSS(21) = 33            ! LUN number for SLHA File (must be 33)', 
            'IMSS(22) = 33            ! Read-in SLHA decay table', 
            'PARJ(71) = 0.            ! for which ctau  1000 mm', 
            'RMSS(21) = 0             ! The gravitino mass'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters', 
            'SLHAParameters'),
        #SLHAParameters = cms.vstring('SLHAFILE = Configuration/Generator/data/GMSB_Lambda100_CTau1000_pythia6.slha')
        SLHAParameters = cms.vstring('SLHAFILE = Configuration/Generator/data/gmsb_lambda140_8TeV_pythia6_ctau1.slha')
    )
)


process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.ProductionFilterSequence)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.endjob_step,process.RAWSIMoutput_step)

