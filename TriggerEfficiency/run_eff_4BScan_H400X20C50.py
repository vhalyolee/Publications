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
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_1.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_10.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_2.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_3.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_4.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_5.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_6.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_7.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_8.root",
"/store/user/plujan/HTo2LongLived/4BScan_MH_400_MFF_20_CTau50_8TeV/HTo2LongLivedTo4BScan_MH_400_MFF_20_CTau50_noPU_Pythia6_8TeV_CMSSW_5_3_12_FastSim_9.root",
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

process.TrigEff = cms.EDAnalyzer(
    "TriggerEfficiencyH4b",
    outfileName = cms.untracked.string("outfile_4BScan_H400X20C50.root"),
    writeTriggerInfo = cms.untracked.bool(True),
    # Note: in order for the L1 seeding to work properly, please arrange these
    # so that each L1 seed is followed by its HLT counterpart.
    targetTrigNames = cms.untracked.vstring("L1_DoubleMu_10_3p5",
                                            "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v3",
                                            "L1_DoubleMu0_HighQ_EtaCuts",
                                            "HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v7",
                                            "L1_TripleMu0",
                                            "HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v7",
                                            "L1_HTT150",
                                            "HLT_HT300_DoubleDisplacedPFJet60_v9",
                                            "L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12",
                                            "HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v7"
                                            ),
    unprescaledTriggersHLT = cms.untracked.vstring("HLT_PFJet320_v8",
                                                   "HLT_Jet370_NoJetID_v15",
                                                   "HLT_PFJet400_v8",
                                                   "HLT_DiPFJetAve400_v9",
                                                   "HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v9",
                                                   "HLT_DiJet80_DiJet60_DiJet20_v5",
                                                   "HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v8",
                                                   "HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v8",
                                                   "HLT_Jet80Eta1p7_Jet70Eta1p7_DiBTagIP3DFastPV_v7",
                                                   "HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose_v7",
                                                   "HLT_QuadJet50_v5",
                                                   "HLT_QuadJet50_Jet20_v4",
                                                   "HLT_QuadJet60_DiJet20_v5",
                                                   "HLT_QuadJet80_v6",
                                                   "HLT_QuadJet90_v6",
                                                   "HLT_QuadJet75_55_38_20_BTagIP_VBF_v6",
                                                   "HLT_QuadPFJet82_65_48_35_BTagCSV_VBF_v4",
                                                   "HLT_SixJet45_v6",
                                                   "HLT_SixJet50_v6",
                                                   "HLT_EightJet30_eta3p0_v5",
                                                   "HLT_EightJet35_eta3p0_v5",
                                                   "HLT_HT200_AlphaT0p57_v8",
                                                   "HLT_HT250_AlphaT0p55_v8",
                                                   "HLT_HT250_AlphaT0p57_v8",
                                                   "HLT_HT300_AlphaT0p53_v8",
                                                   "HLT_HT300_AlphaT0p54_v14",
                                                   "HLT_HT300_DoubleDisplacedPFJet60_v9",
                                                   "HLT_HT300_DoubleDisplacedPFJet60_ChgFraction10_v9",
                                                   "HLT_HT350_AlphaT0p52_v8",
                                                   "HLT_HT350_AlphaT0p53_v19",
                                                   "HLT_HT400_AlphaT0p51_v19",
                                                   "HLT_HT400_AlphaT0p52_v14",
                                                   "HLT_HT450_AlphaT0p51_v14",
                                                   "HLT_HT650_Track50_dEdx3p6_v10",
                                                   "HLT_HT650_Track60_dEdx3p7_v10",
                                                   "HLT_HT750_v7",
                                                   "HLT_PFMET150_v6",
                                                   "HLT_PFMET180_v6",
                                                   "HLT_DiCentralJetSumpT100_dPhi05_DiCentralPFJet60_25_PFMET100_HBHENoiseCleaned_v4",
                                                   "HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v4",
                                                   "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d03_v4",
                                                   "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d05_v4",
                                                   "HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v4",
                                                   "HLT_MET80_Track50_dEdx3p6_v6",
                                                   "HLT_MET80_Track60_dEdx3p7_v6",
                                                   "HLT_MET120_HBHENoiseCleaned_v5",
                                                   "HLT_MET200_v12",
                                                   "HLT_MET200_HBHENoiseCleaned_v5",
                                                   "HLT_MET300_v4",
                                                   "HLT_MET300_HBHENoiseCleaned_v5",
                                                   "HLT_MET400_v7",
                                                   "HLT_MET400_HBHENoiseCleaned_v5",
                                                   "HLT_L2Mu70_2Cha_eta2p1_PFMET55_v1",
                                                   "HLT_L2Mu70_2Cha_eta2p1_PFMET60_v1",
                                                   "HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v7",
                                                   "HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v7",
                                                   "HLT_Mu40_v14",
                                                   "HLT_Mu40_eta2p1_v11",
                                                   "HLT_Mu50_eta2p1_v8",
                                                   "HLT_IsoMu15_eta2p1_L1ETM20_v7",
                                                   "HLT_IsoMu24_v17",
                                                   "HLT_IsoMu24_eta2p1_v15",
                                                   "HLT_IsoMu30_v11",
                                                   "HLT_IsoMu30_eta2p1_v15",
                                                   "HLT_IsoMu34_eta2p1_v13",
                                                   "HLT_IsoMu40_eta2p1_v10",
                                                   "HLT_Mu40_eta2p1_Track50_dEdx3p6_v5",
                                                   "HLT_Mu40_eta2p1_Track60_dEdx3p7_v5",
                                                   "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v3",
                                                   "HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_v3",
                                                   "HLT_DoubleMu11_Acoplanarity03_v5",
                                                   "HLT_DoubleMu4_Jpsi_Displaced_v12",
                                                   "HLT_DoubleMu4_JpsiTk_Displaced_v6",
                                                   "HLT_DoubleMu3_4_Dimuon5_Bs_Central_v5",
                                                   "HLT_DoubleMu3p5_4_Dimuon5_Bs_Central_v5",
                                                   "HLT_DoubleMu4_Dimuon7_Bs_Forward_v5",
                                                   "HLT_DoubleMu3p5_LowMass_Displaced_v6",
                                                   "HLT_DoubleMu3p5_LowMassNonResonant_Displaced_v6",
                                                   "HLT_Dimuon5_Upsilon_v6",
                                                   "HLT_Dimuon5_PsiPrime_v6",
                                                   "HLT_Dimuon7_Upsilon_v7",
                                                   "HLT_Dimuon8_Jpsi_v7",
                                                   "HLT_Dimuon8_Upsilon_v6",
                                                   "HLT_Dimuon10_Jpsi_v6",
                                                   "HLT_Dimuon11_Upsilon_v6",
                                                   "HLT_Dimuon0_Jpsi_Muon_v18",
                                                   "HLT_Dimuon0_Upsilon_Muon_v18",
                                                   "HLT_Tau2Mu_ItTrack_v7",
                                                   "HLT_Mu13_Mu8_v21",
                                                   "HLT_Mu17_Mu8_v21",
                                                   "HLT_Mu17_TkMu8_v13",
                                                   "HLT_Mu22_TkMu8_v8",
                                                   "HLT_Mu22_TkMu22_v8",
                                                   "HLT_TripleMu5_v19",
                                                   "HLT_DoubleMu5_IsoMu5_v20",
                                                   "HLT_Photon26_R9Id85_Photon18_R9Id85_Mass60_v4",
                                                   "HLT_Photon26_R9Id85_Photon18_CaloId10_Iso50_Mass60_v6",
                                                   "HLT_Photon26_CaloId10_Iso50_Photon18_R9Id85_Mass60_v6",
                                                   "HLT_Photon26_CaloId10_Iso50_Photon18_CaloId10_Iso50_Mass60_v6",
                                                   "HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass60_v6",
                                                   "HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass70_v2",
                                                   "HLT_Photon36_R9Id85_Photon22_R9Id85_v4",
                                                   "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50_v6",
                                                   "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85_v6",
                                                   "HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50_v6",
                                                   "HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50_v6",
                                                   "HLT_Photon70_CaloIdXL_PFMET100_v6",
                                                   "HLT_DisplacedPhoton65_CaloIdVL_IsoL_PFMET25_v3",
                                                   "HLT_DisplacedPhoton65EBOnly_CaloIdVL_IsoL_PFMET30_v3",
                                                   "HLT_Photon150_v4",
                                                   "HLT_Photon160_v4",
                                                   "HLT_Photon300_NoHE_v5",
                                                   "HLT_DoublePhoton48_HEVT_v8",
                                                   "HLT_DoublePhoton53_HEVT_v2",
                                                   "HLT_DoublePhoton70_v6",
                                                   "HLT_DoublePhoton80_v7",
                                                   "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v18",
                                                   "HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v7",
                                                   "HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_HFT15_v7",
                                                   "HLT_Ele23_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_HFT30_v7",
                                                   "HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_v3",
                                                   "HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet50_40_30_v3",
                                                   "HLT_Ele27_WP80_v11",
                                                   "HLT_Ele27_WP80_PFMET_MT50_v6",
                                                   "HLT_Ele80_CaloIdVT_GsfTrkIdT_v2",
                                                   "HLT_Ele90_CaloIdVT_GsfTrkIdT_v2",
                                                   "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v7",
                                                   "HLT_DoubleEle33_CaloIdT_v10",
                                                   "HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL_v6",
                                                   "HLT_LooseIsoPFTau35_Trk20_Prong1_MET70_v9",
                                                   "HLT_LooseIsoPFTau35_Trk20_Prong1_MET75_v9",
                                                   "HLT_IsoMu15_eta2p1_LooseIsoPFTau35_Trk20_Prong1_L1ETM20_v9",
                                                   "HLT_BTagMu_Jet300_Mu5_v6",
                                                   "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9",
                                                   "HLT_IsoMu24_PFJet30_PFJet25_Deta3_CentralPFJet25_v3",
                                                   "HLT_IsoMu24_CentralPFJet30_CentralPFJet25_v3",
                                                   "HLT_IsoMu24_CentralPFJet30_CentralPFJet25_PFMET20_v3",
                                                   "HLT_Ele32_WP80_PFJet30_PFJet25_Deta3_CentralPFJet30_v3",
                                                   "HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25_v3",
                                                   "HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25_PFMET20_v3",
                                                   "HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v3",
                                                   "HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_v3",
                                                   "HLT_IsoMu20_WCandPt80_v3",
                                                   "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9",
                                                   "HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v7",
                                                   "HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v7",
                                                   "HLT_Mu30_Ele30_CaloIdL_v8",
                                                   "HLT_IsoMu20_eta2p1_CentralPFJet80_v8",
                                                   "HLT_Mu40_PFNoPUHT350_v3",
                                                   "HLT_Mu60_PFNoPUHT350_v3",
                                                   "HLT_DoubleMu8_Ele8_CaloIdT_TrkIdVL_v5",
                                                   "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v8",
                                                   "HLT_Ele27_WP80_CentralPFJet80_v8",
                                                   "HLT_Ele27_WP80_WCandPt80_v8",
                                                   "HLT_Ele30_CaloIdVT_TrkIdT_PFNoPUJet100_PFNoPUJet25_v7",
                                                   "HLT_Ele30_CaloIdVT_TrkIdT_PFNoPUJet150_PFNoPUJet25_v7",
                                                   "HLT_DoubleEle10_CaloIdL_TrkIdVL_Ele10_CaloIdT_TrkIdVL_v12",
                                                   "HLT_TripleEle10_CaloIdL_TrkIdVL_v18",
                                                   "HLT_RsqMR45_Rsq0p09_v5",
                                                   "HLT_RsqMR55_Rsq0p09_MR150_v6",
                                                   "HLT_RsqMR60_Rsq0p09_MR150_v6",
                                                   "HLT_RsqMR65_Rsq0p09_MR150_v5",
                                                   "HLT_IsoMu12_RsqMR30_Rsq0p04_MR200_v4",
                                                   "HLT_IsoMu12_RsqMR40_Rsq0p04_MR200_v4",
                                                   "HLT_Ele12_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_RsqMR30_Rsq0p04_MR200_v4",
                                                   "HLT_Ele12_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_RsqMR40_Rsq0p04_MR200_v4",
                                                   "HLT_Photon40_CaloIdL_RsqMR40_Rsq0p09_MR150_v6",
                                                   "HLT_Photon40_CaloIdL_RsqMR45_Rsq0p09_MR150_v6",
                                                   "HLT_Photon40_CaloIdL_RsqMR50_Rsq0p09_MR150_v6",
                                                   "HLT_DoublePhoton40_CaloIdL_Rsq0p035_v6",
                                                   "HLT_DoublePhoton40_CaloIdL_Rsq0p06_v6",
                                                   "HLT_Mu22_Photon22_CaloIdL_v7",
                                                   "HLT_Mu8_DoubleEle8_CaloIdT_TrkIdVL_v7",
                                                   "HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Ele8_CaloIdL_TrkIdVL_v7",
                                                   "HLT_DoubleMu14_Mass8_PFMET40_v7",
                                                   "HLT_DoubleMu14_Mass8_PFMET50_v7",
                                                   "HLT_DoubleEle14_CaloIdT_TrkIdVL_Mass8_PFMET40_v7",
                                                   "HLT_DoubleEle14_CaloIdT_TrkIdVL_Mass8_PFMET50_v7",
                                                   "HLT_Mu14_Ele14_CaloIdT_TrkIdVL_Mass8_PFMET40_v7",
                                                   "HLT_Mu14_Ele14_CaloIdT_TrkIdVL_Mass8_PFMET50_v7",
                                                   "HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v5",
                                                   "HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v5",
                                                   "HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v5",
                                                   "HLT_Ele22_eta2p1_WP90Rho_LooseIsoPFTau20_v6",
                                                   "HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v6",
                                                   "DST_HT250_v4",
                                                   "DST_Mu5_HT250_v4",
                                                   "DST_Ele8_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_HT250_v4",
    ),
    unprescaledTriggersL1 = cms.untracked.vstring("L1_DoubleEG_13_7",
                                                  #"L1_DoubleEG5_RomanPotsOR",
                                                  "L1_DoubleEG6_HTT100",
                                                  "L1_DoubleEG6_HTT125",
                                                  "L1_DoubleJet64_Central",
                                                  "L1_DoubleJetC36_ETM30",
                                                  #"L1_DoubleJetC36_RomanPotsOR",
                                                  "L1_DoubleJetC44_ETM30",
                                                  "L1_DoubleJetC56",
                                                  "L1_DoubleJetC56_Eta1p74_WdEta4",
                                                  "L1_DoubleMu0_HighQ_EtaCuts",
                                                  "L1_DoubleMu3er_HighQ_WdEta22",
                                                  "L1_DoubleMu3p5_EG5",
                                                  "L1_DoubleMu5_EG5",
                                                  #"L1_DoubleMu5_RomanPotsOR",
                                                  "L1_DoubleMu_10_3p5",
                                                  "L1_DoubleMu_10_Open",
                                                  "L1_DoubleMu_12_5",
                                                  "L1_DoubleMu_5er_0er_HighQ_WdEta22",
                                                  "L1_DoubleTauJet44_Eta2p17",
                                                  #"L1_EG18er_JetC_Cen28_Tau20_dPhi1",
                                                  #"L1_EG18er_JetC_Cen36_Tau28_dPhi1",
                                                  "L1_EG22_ForJet24",
                                                  "L1_EG22_ForJet32",
                                                  "L1_ETM100",
                                                  "L1_ETM36",
                                                  "L1_ETM40",
                                                  "L1_ETM50",
                                                  "L1_ETM70",
                                                  "L1_ETT300",
                                                  "L1_HTT150",
                                                  "L1_HTT175",
                                                  "L1_HTT200",
                                                  #"L1_IsoEG18er_JetC_Cen32_Tau24_dPhi1",
                                                  #"L1_IsoEG18er_JetC_Cen36_Tau28_dPhi1",
                                                  "L1_Mu0_HTT100",
                                                  "L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12",
                                                  "L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12",
                                                  "L1_Mu10er_JetC32",
                                                  "L1_Mu12_EG7",
                                                  "L1_Mu12er_ETM20",
                                                  "L1_Mu3_JetC52_WdEtaPhi2",
                                                  "L1_Mu3p5_EG12",
                                                  "L1_Mu4_HTT125",
                                                  "L1_Mu5_DoubleEG5",
                                                  "L1_Mu5_DoubleEG6",
                                                  "L1_MuOpen_EG12",
                                                  "L1_QuadJetC32",
                                                  "L1_QuadJetC36",
                                                  "L1_QuadJetC40",
                                                  "L1_SingleEG18er",
                                                  "L1_SingleEG20",
                                                  #"L1_SingleEG20_RomanPotsOR",
                                                  "L1_SingleEG22",
                                                  "L1_SingleEG24",
                                                  "L1_SingleEG30",
                                                  "L1_SingleIsoEG18er",
                                                  "L1_SingleIsoEG20er",
                                                  "L1_SingleJet128",
                                                  #"L1_SingleJet52_RomanPotsOR",
                                                  "L1_SingleJetC32_NotBptxOR",
                                                  "L1_SingleMu14_Eta2p1",
                                                  "L1_SingleMu16",
                                                  "L1_SingleMu16_Eta2p1",
                                                  "L1_SingleMu18er",
                                                  "L1_SingleMu20",
                                                  #"L1_SingleMu20_RomanPotsOR",
                                                  "L1_SingleMu20er",
                                                  "L1_SingleMu25er",
                                                  "L1_SingleMu6_NotBptxOR",
                                                  "L1_TripleEG7",
                                                  "L1_TripleEG_12_7_5",
                                                  "L1_TripleJet_64_44_24_VBF",
                                                  "L1_TripleJet_64_48_28_VBF",
                                                  "L1_TripleJet_68_48_32_VBF",
                                                  "L1_TripleMu0",
                                                  "L1_TripleMu0_HighQ",
                                                  "L1_TripleMu_5_5_0"
                                                  )
    )

process.p1 = cms.Path( process.TrigEff )
