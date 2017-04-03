import sys
import FWCore.ParameterSet.Config as cms

process = cms.Process("TriggerCounter")

process.load('FWCore/MessageService/MessageLogger_cfi')
process.load("Configuration.StandardSequences.Services_cff")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = autoCond['startup']

process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_1.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_10.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_2.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_3.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_4.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_5.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_6.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_7.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_8.root",
"root://cmseos.fnal.gov:1094//eos/uscms/store/user/plujan/HTo2LongLived/4BScan_MH_200_MFF_20_CTau300_8TeV/HTo2LongLivedTo4BScan_MH_200_MFF_20_CTau300_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_9.root",
                             )
                             )
process.source.skipEvents = cms.untracked.uint32(0)
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.TrigSim = cms.EDAnalyzer(
    "L1TriggerSimulator",
    )

process.p1 = cms.Path( process.TrigSim )
