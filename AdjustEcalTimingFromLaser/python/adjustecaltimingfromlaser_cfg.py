import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )


process.source = cms.Source("EmptySource",
                                   numberEventsInRun = cms.untracked.uint32(1),
                                   firstRun = cms.untracked.uint32(888888), # Use last IOV for event setup info - irrelevant for adjustecaltimingfromlaser
                            )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag. connect = cms.string('frontier://(proxyurl=http://localhost:3128)(serverurl=http://localhost:8000/FrontierOnProd)(serverurl=http://localhost:8000/FrontierOnProd)(retrieve-ziplevel=0)(failovertoserver=no)/CMS_COND_31X_GLOBALTAG')
# tag below tested in CMSSW_4_3_0_pre3
process.GlobalTag.globaltag = 'GR_R_42_V14::All'

#this one below is specific of P5
#process.GlobalTag.globaltag = 'GR_H_V24::All'
#process.GlobalTag.globaltag = 'GR10_P_V12::All'
#process.GlobalTag.globaltag = 'GR_H_V23::All'
#process.GlobalTag.globaltag = 'GR_H_V24::All'  # to be used inside P5, fall 2011



process.load("Configuration.StandardSequences.Geometry_cff")



process.demo = cms.EDAnalyzer('AdjustEcalTimingFromLaser',


                              doDebugMessages = cms.bool(False), #False means don't getCCUId and Timing shift.
                              
                              # Tambe tests with this directory
                              # dirInPutFilesname = cms.string("/hdfs/cms/user/norbert/data/Validlaser/"),
                              # gio tests with this OTHER directory
                              # dirInPutFilesname = cms.string("/data/franzoni/data/LaserSelected/"),
                              # the following one is for P5
                              dirInPutFilesname = cms.string("/hdfs/cms/user/norbert/data/file22march/"),

                              # directory where the output plots will be stored
                              dirOutPutPlotsname = cms.string("LaserTimingShift_No_AvegSubtraction_April08_Run163337VsRun163338"),
                              # name of the output .root file
                              fileOutPutName = cms.string("EcalLaserTimingRun163337VsRun163338_April08No_Ave_Subtraction.root"),

                              # the two runs to be compared
                              # Tambe uses these runs
                              RunB4TS = cms.int32(163338), 
                              RunAFTS = cms.int32(163337), 
                              
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
                              subtractAverageDifferences       = cms.bool(False),
                              
                              # This Flag determines if you are using T_MAX_APD or something else
                              # IsTmaxAPD == True, then you are using T_MAX_APD  else something else.
                              IsTmaxAPD                        = cms.bool(True),  # False means not using T_MAX_APD.

                              # if a time difference is larger than this:
                              # 1) exclude it from the computation of the light-module average
                              # 2) don't use it to modify the hardware settings in the xml files
                              maxTimeDifferenceUsedForAverage  = cms.double(30.),

                              # if measured time shift is less than a certain amount, don't consider it for a change to the xml's
                              minTimeChangeToApply = cms.double(1.),
                              

                              # decide whether you want only to do  analysi (False) or also connect to the database and deploy xml files (True)
                              doHwSetFromDb               = cms.bool(False),
                              # if you decide to connect to the database and deploy xml files:
                              # 1) have time-shift-corrected xml (True) or
                              # 2) xml which are the an unmodified dump of what's in the confdb 
                              operateInDumpMode	          = cms.bool(False),
                              # prefix for xml files
                              xmlFileNameBeg  = cms.string("xml-fromLaser"),

)

process.p = cms.Path(process.demo)
