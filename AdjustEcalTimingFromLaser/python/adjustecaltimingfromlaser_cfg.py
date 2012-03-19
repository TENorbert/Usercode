import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )


process.source = cms.Source("EmptySource",
                                   numberEventsInRun = cms.untracked.uint32(1),
                                   firstRun = cms.untracked.uint32(888888), # Use last IOV for event setup info - irrelevant for adjustecaltimingfromlaser
                            )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag. connect = cms.string('frontier://(proxyurl=http://localhost:3128)(serverurl=http://localhost:8000/FrontierOnProd)(serverurl=http://localhost:8000/FrontierOnProd)(retrieve-ziplevel=0)(failovertoserver=no)/CMS_COND_31X_GLOBALTAG')
# tag below tested in CMSSW_4_3_0_pre3
#process.GlobalTag.globaltag = 'GR_R_42_V14::All'

#this one below is specific of P5
#process.GlobalTag.globaltag = 'GR_H_V24::All'
#process.GlobalTag.globaltag = 'GR10_P_V12::All'
#process.GlobalTag.globaltag = 'GR_H_V23::All'
process.GlobalTag.globaltag = 'GR_H_V24::All'  # to be used inside P5, fall 2011



process.load("Configuration.StandardSequences.Geometry_cff")



process.demo = cms.EDAnalyzer('AdjustEcalTimingFromLaser',

                              doDebugMessages = cms.bool(True),
                              
                              # Tambe tests with this directory
                              # dirInPutFilesname = cms.string("/hdfs/cms/user/norbert/data/Validlaser/"),
                              # gio tests with this OTHER directory
                              # dirInPutFilesname = cms.string("/data/franzoni/data/LaserSelected/"),
                              # the following one is for P5
                              dirInPutFilesname = cms.string("/nfshome0/franzoni/data/LaserSelected/"),

                              # directory where the output plots will be stored
                              dirOutPutPlotsname = cms.string("LaserTimingShiftRun163297VsRun1634833/"),
                              # name of the output .root file
                              fileOutPutName = cms.string("output-file.root"),

                              # the two runs to be compared
                              # Tambe uses these runs
                              RunB4TS = cms.int32(163291), 
                              RunAFTS = cms.int32(163333), 
                              
                              # laser wavelength being considered
                              NWL = cms.int32(3), 

                              # Set Max and Min time on Each Runs
                              binlow  = cms.double(-50.),
                              binhigh = cms.double(50.),
                              
                              # SetMaximum Minimum of Bins on TimeshiftHist
                              lbin = cms.double(-5.0),
                              hbin = cms.double(5.0),

                              # this flag determines whether for single fed plots
                              # the average difference should be removed from the displayed single-CCU differences
                              # the average to be subtracted is computed over:
                              #    - a whole sector, for EE feds
                              #    - separately for the two laser light distribution modules (I-shaped and L-shaped) of EB supermodules 
                              subtractAverageDifferences  = cms.bool(True),
                              doHwSetFromDb               = cms.bool(False),
                              
)

process.p = cms.Path(process.demo)
