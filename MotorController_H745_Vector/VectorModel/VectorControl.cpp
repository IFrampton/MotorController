// RemovedFunctions.c
// Contains definitions for model functions that are not used in the code due to impracticality, inefficiency,
// poor functionality, or myopic architecture design.

extern "C"
{
#include "P2319ASW01.h"
}
#include "DataMan.h"
#include "VectorControl.h"
#include "BspAnalog.h"

VectorControl::VectorConfig *VectorControl::_config;
VectorControl::VectorInputs *VectorControl::_analogIn;
VectorControl::VectorOutputs *VectorControl::_analogOut;

void VectorControl::UpdateConfig()
{
	AuxPwrAcvDebFall_C = _config->AuxPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */
	AuxPwrAcvDebRisng_C = _config->AuxPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */
	AuxPwrAcvDialEna_C = _config->AuxPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */
	AuxPwrAcvDialVal_C = _config->AuxPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */
	AuxPwrStsIvt_C = _config->AuxPwrStsIvt_C;/* Referenced by: '<S16>/Model' */
	BdT1DialEna_C = _config->BdT1DialEna_C;/* Referenced by: '<S16>/Model' */
	BdT1DialVal_C = _config->BdT1DialVal_C;/* Referenced by: '<S16>/Model' */
	BdT1FilTiCon_C = _config->BdT1FilTiCon_C;/* Referenced by: '<S16>/Model' */
	BdT1Gain_C = _config->BdT1Gain_C;/* Referenced by: '<S16>/Model' */
	BdT1Ofs_C = _config->BdT1Ofs_C;/* Referenced by: '<S16>/Model' */
	BdT2DialEna_C = _config->BdT2DialEna_C;/* Referenced by: '<S16>/Model' */
	BdT2DialVal_C = _config->BdT2DialVal_C;/* Referenced by: '<S16>/Model' */
	BdT2FilTiCon_C = _config->BdT2FilTiCon_C;/* Referenced by: '<S16>/Model' */
	BdT2Gain_C = _config->BdT2Gain_C;/* Referenced by: '<S16>/Model' */
	BdT2Ofs_C = _config->BdT2Ofs_C;/* Referenced by: '<S16>/Model' */
	CanPwrPwmEna_C = _config->CanPwrPwmEna_C;/* Referenced by: '<S17>/Model' */
	DrvModDialEna_C = _config->DrvModDialEna_C;/* Referenced by: '<S15>/Model' */
	DrvModDialVal_C = _config->DrvModDialVal_C;/* Referenced by: '<S15>/Model' */
	DrvModReqDft_C = _config->DrvModReqDft_C;/* Referenced by: '<S18>/Model' */
	DrvModReqDialEna_C = _config->DrvModReqDialEna_C;/* Referenced by: '<S18>/Model' */
	DrvModReqDialVal_C = _config->DrvModReqDialVal_C;/* Referenced by: '<S18>/Model' */
	EncoderCtPerRev_C = _config->EncoderCtPerRev_C;/* Referenced by: '<S13>/Model' */
	EncoderOfs_C = _config->EncoderOfs_C;/* Referenced by: '<S13>/Model' */
	FluxLinkage_C = _config->FluxLinkage_C;/* Referenced by: '<S10>/Model' */
	GreenLedDialEna_C = _config->GreenLedDialEna_C;/* Referenced by: '<S17>/Model' */
	GreenLedDialVal_C = _config->GreenLedDialVal_C;/* Referenced by: '<S17>/Model' */
	GreenLedIvt_C = _config->GreenLedIvt_C;/* Referenced by: '<S17>/Model' */
	HvBusCurDialEna_C = _config->HvBusCurDialEna_C;/* Referenced by: '<S8>/Model' */
	HvBusCurDialVal_C = _config->HvBusCurDialVal_C;/* Referenced by: '<S8>/Model' */
	HvBusCurFilTiCon_C = _config->HvBusCurFilTiCon_C;/* Referenced by: '<S8>/Model' */
	HvBusCurGain_C = _config->HvBusCurGain_C;/* Referenced by: '<S8>/Model' */
	HvBusCurOfs_C = _config->HvBusCurOfs_C;/* Referenced by: '<S8>/Model' */
	HvBusUDialEna_C = _config->HvBusUDialEna_C;/* Referenced by: '<S8>/Model' */
	HvBusUDialVal_C = _config->HvBusUDialVal_C;/* Referenced by: '<S8>/Model' */
	HvBusUFilTiCon_C = _config->HvBusUFilTiCon_C;/* Referenced by: '<S8>/Model' */
	HvBusUGain_C = _config->HvBusUGain_C;/* Referenced by: '<S8>/Model' */
	HvBusUOfs_C = _config->HvBusUOfs_C;/* Referenced by: '<S8>/Model' */
	InPwrPwmEna_C = _config->InPwrPwmEna_C;/* Referenced by: '<S17>/Model' */
	LedOffTi_C = _config->LedOffTi_C;/* Referenced by: '<S17>/Model' */
	LedPlsCtDft_C = _config->LedPlsCtDft_C;/* Referenced by: '<S17>/Model' */
	LedPlsCtOpenLoop_C = _config->LedPlsCtOpenLoop_C;/* Referenced by: '<S17>/Model' */
	LedPlsCtSpdCtl_C = _config->LedPlsCtSpdCtl_C;/* Referenced by: '<S17>/Model' */
	LedPlsCtTqCtl_C = _config->LedPlsCtTqCtl_C;/* Referenced by: '<S17>/Model' */
	MaiPwrAcvDebFall_C = _config->MaiPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */
	MaiPwrAcvDebRisng_C = _config->MaiPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */
	MaiPwrAcvDialEna_C = _config->MaiPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */
	MaiPwrAcvDialVal_C = _config->MaiPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */
	MaiPwrStsIvt_C = _config->MaiPwrStsIvt_C;/* Referenced by: '<S16>/Model' */
	McuData1DaDialEna_C = _config->McuData1DaDialEna_C;/* Referenced by: '<S19>/Model' */
	for( short x = 0; x < 8; x++)
	{
		McuData1DaDialVal_CA[x] = _config->McuData1DaDialVal_CA[x];       /* Referenced by: '<S19>/Model' */
	}
	McuData2DaDialEna_C = _config->McuData2DaDialEna_C;/* Referenced by: '<S17>/Model' */
	for( short x = 0; x < 8; x++)
	{
		McuData2DaDialVal_CA[x] = _config->McuData2DaDialVal_CA[x];       /* Referenced by: '<S17>/Model' */
	}
	McuReqTout_C = _config->McuReqTout_C;/* Referenced by: '<S18>/Model' */
	McuTDialEna_C = _config->McuTDialEna_C;/* Referenced by: '<S16>/Model' */
	McuTDialVal_C = _config->McuTDialVal_C;/* Referenced by: '<S16>/Model' */
	McuTFilTiCon_C = _config->McuTFilTiCon_C ;/* Referenced by: '<S16>/Model' */
	McuTGain_C = _config->McuTGain_C;/* Referenced by: '<S16>/Model' */
	McuTOfs_C = _config->McuTOfs_C;/* Referenced by: '<S16>/Model' */
	McuUBatFilTiCon_C = _config->McuUBatFilTiCon_C;/* Referenced by: '<S16>/Model' */
	McuUBatGain_C = _config->McuUBatGain_C;/* Referenced by: '<S16>/Model' */
	McuUBatOfs_C = _config->McuUBatOfs_C;/* Referenced by: '<S16>/Model' */
	McuURefFilTiCon_C = _config->McuURefFilTiCon_C;/* Referenced by: '<S16>/Model' */
	McuURefGain_C = _config->McuURefGain_C;/* Referenced by: '<S16>/Model' */
	McuURefOfs_C = _config->McuURefOfs_C;/* Referenced by: '<S16>/Model' */
	MotPolePairs_C = _config->MotPolePairs_C;/* Referenced by: '<S13>/Model' */
	MotPosnEstimrGainI_C = _config->MotPosnEstimrGainI_C;/* Referenced by: '<S13>/Model' */
	MotPosnEstimrGainP_C = _config->MotPosnEstimrGainP_C;/* Referenced by: '<S13>/Model' */
	MotPosnEstimrIntglEna_C = _config->MotPosnEstimrIntglEna_C; /* Referenced by: '<S13>/Model' */
	MotPosnMagDialEna_C = _config->MotPosnMagDialEna_C;/* Referenced by: '<S13>/Model' */
	MotPosnMagDialVal_C = _config->MotPosnMagDialVal_C;/* Referenced by: '<S13>/Model' */
	MotPosnOfs_C = _config->MotPosnOfs_C;/* Referenced by: '<S13>/Model' */
	MotPosnSenMeth_C = _config->MotPosnSenMeth_C;/* Referenced by: '<S13>/Model' */
	MotPosnTrigDialEna_C = _config->MotPosnTrigDialEna_C;/* Referenced by: '<S14>/Model' */
	for( short x = 0; x < 6; x++)
	{
		MotPosnTrigDialVal_CA[x] = _config->MotPosnTrigDialVal_CA[x];/* Referenced by: '<S14>/Model' */
	}
	MotSpdDialEna_C = _config->MotSpdDialEna_C;/* Referenced by: '<S13>/Model' */
	MotSpdDialVal_C = _config->MotSpdDialVal_C;/* Referenced by: '<S13>/Model' */
	MotSpdFilTiCon_C = _config->MotSpdFilTiCon_C;/* Referenced by: '<S13>/Model' */
	MotSpdMagDialEna_C = _config->MotSpdMagDialEna_C;/* Referenced by: '<S13>/Model' */
	MotSpdMagDialVal_C = _config->MotSpdMagDialVal_C;/* Referenced by: '<S13>/Model' */
	MotSpdRateLim_C = _config->MotSpdRateLim_C;/* Referenced by: '<S20>/Model' */
	MotSpdReqCanDft_C = _config->MotSpdReqCanDft_C;/* Referenced by: '<S18>/Model' */
	MotSpdReqCanDialEna_C = _config->MotSpdReqCanDialEna_C;/* Referenced by: '<S18>/Model' */
	MotSpdReqCanDialVal_C = _config->MotSpdReqCanDialVal_C;/* Referenced by: '<S18>/Model' */
	MotSpdReqMax_C = _config->MotSpdReqMax_C;/* Referenced by: '<S20>/Model' */
	MotSpdReqThdModChg_C = _config->MotSpdReqThdModChg_C;/* Referenced by: '<S15>/Model' */
	MotSpdThdModChg_C = _config->MotSpdThdModChg_C;/* Referenced by: '<S15>/Model' */
	MotTqCmdSpdCtlDialEna_C = _config->MotTqCmdSpdCtlDialEna_C;  /* Referenced by: '<S20>/Model' */
	MotTqCmdSpdCtlDialVal_C = _config->MotTqCmdSpdCtlDialVal_C;/* Referenced by: '<S20>/Model' */
	MotTqCon_C = _config->MotTqCon_C;/* Referenced by: '<S21>/Model' */
	for( short x = 0; x < 5; x++)
	{
		MotTqGainBdT1_Ax[x] = _config->MotTqGainBdT1_Ax[x];       /* Referenced by: '<S21>/Model' */
		MotTqGainBdT1_T[x] = _config->MotTqGainBdT1_T[x];           /* Referenced by: '<S21>/Model' */
		MotTqGainBdT2_Ax[x] = _config->MotTqGainBdT2_Ax[x];       /* Referenced by: '<S21>/Model' */
		MotTqGainBdT2_T[x] = _config->MotTqGainBdT2_T[x];           /* Referenced by: '<S21>/Model' */
	}
	MotTqGainI_C = _config->MotTqGainI_C;/* Referenced by: '<S20>/Model' */
	MotTqGainP_C = _config->MotTqGainP_C;/* Referenced by: '<S20>/Model' */
	MotTqMaxDialEna_C = _config->MotTqMaxDialEna_C;/* Referenced by: '<S21>/Model' */
	MotTqMaxDialVal_C = _config->MotTqMaxDialVal_C;/* Referenced by: '<S21>/Model' */
	for( short x = 0; x < 5; x++)
	{
		MotTqMaxMotSpd_Ax[x] = _config->MotTqMaxMotSpd_Ax[x];/* Referenced by: '<S21>/Model' */
		MotTqMaxMotSpd_T[x] = _config->MotTqMaxMotSpd_T[x];           /* Referenced by: '<S21>/Model' */
	}
	MotTqReqCanDft_C = _config->MotTqReqCanDft_C;/* Referenced by: '<S18>/Model' */
	MotTqReqCanDialEna_C = _config->MotTqReqCanDialEna_C;/* Referenced by: '<S18>/Model' */
	MotTqReqCanDialVal_C = _config->MotTqReqCanDialVal_C;/* Referenced by: '<S18>/Model' */
	MotTqReqThdModChg_C = _config->MotTqReqThdModChg_C;/* Referenced by: '<S15>/Model' */
	MtrPwrPwmEna_C = _config->MtrPwrPwmEna_C;/* Referenced by: '<S17>/Model' */
	PhaAPwmDcDialEna_C = _config->PhaAPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */
	PhaAPwmDcDialVal_C = _config->PhaAPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */
	PhaBPwmDcDialEna_C = _config->PhaBPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */
	PhaBPwmDcDialVal_C = _config->PhaBPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */
	PhaCPwmDcDialEna_C = _config->PhaCPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */
	PhaCPwmDcDialVal_C = _config->PhaCPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */
	PhaCurADialEna_C = _config->PhaCurADialEna_C;/* Referenced by: '<S8>/Model' */
	PhaCurADialVal_C = _config->PhaCurADialVal_C;/* Referenced by: '<S8>/Model' */
	PhaCurAFilTiCon_C = _config->PhaCurAFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaCurAOfs_C = _config->PhaCurAGain_C;/* Referenced by: '<S8>/Model' */
	PhaCurAOfs_C = _config->PhaCurAOfs_C;/* Referenced by: '<S8>/Model' */
	PhaCurBDialEna_C = _config->PhaCurBDialEna_C;/* Referenced by: '<S8>/Model' */
	PhaCurBDialVal_C = _config->PhaCurBDialVal_C;/* Referenced by: '<S8>/Model' */
	PhaCurBFilTiCon_C = _config->PhaCurBFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaCurBGain_C = _config->PhaCurBGain_C;/* Referenced by: '<S8>/Model' */
	PhaCurCDialEna_C = _config->PhaCurBOfs_C;/* Referenced by: '<S8>/Model' */
	PhaCurCDialEna_C = _config->PhaCurCDialEna_C;/* Referenced by: '<S8>/Model' */
	PhaCurCDialVal_C = _config->PhaCurCDialVal_C;/* Referenced by: '<S8>/Model' */
	PhaCurCFilTiCon_C = _config->PhaCurCFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaCurCGain_C = _config->PhaCurCGain_C;/* Referenced by: '<S8>/Model' */
	PhaCurCOfs_C = _config->PhaCurCOfs_C;/* Referenced by: '<S8>/Model' */
	PhaCurDDialEna_C = _config->PhaCurDDialEna_C;/* Referenced by: '<S9>/Model' */
	PhaCurDDialVal_C = _config->PhaCurDDialVal_C;/* Referenced by: '<S9>/Model' */
	PhaCurDTarVal_C = _config->PhaCurDTarVal_C;/* Referenced by: '<S21>/Model' */
	PhaCurQDialEna_C = _config->PhaCurQDialEna_C;/* Referenced by: '<S9>/Model' */
	PhaCurQDialVal_C = _config->PhaCurQDialVal_C;/* Referenced by: '<S9>/Model' */
	PhaCurQTarDialVal_C = _config->PhaCurQTarDialEna_C;/* Referenced by: '<S21>/Model' */
	PhaCurQTarDialVal_C = _config->PhaCurQTarDialVal_C;/* Referenced by: '<S21>/Model' */
	PhaPwmEnaDialEna_C = _config->PhaPwmEnaDialEna_C;/* Referenced by: '<S17>/Model' */
	PhaPwmEnaDialVal_C = _config->PhaPwmEnaDialVal_C;/* Referenced by: '<S17>/Model' */
	PhaUACmdDialEna_C = _config->PhaUACmdDialEna_C;/* Referenced by: '<S12>/Model' */
	PhaUACmdDialVal_C = _config->PhaUACmdDialVal_C;/* Referenced by: '<S12>/Model' */
	PhaUAFilTiCon_C = _config->PhaUAFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaUAGain_C = _config->PhaUAGain_C;/* Referenced by: '<S8>/Model' */
	PhaUAOfs_C = _config->PhaUAOfs_C;/* Referenced by: '<S8>/Model' */
	PhaUBCmdDialEna_C = _config->PhaUBCmdDialEna_C;/* Referenced by: '<S12>/Model' */
	PhaUBCmdDialVal_C = _config->PhaUBCmdDialVal_C;/* Referenced by: '<S12>/Model' */
	PhaUBFilTiCon_C = _config->PhaUBFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaUBGain_C = _config->PhaUBGain_C;/* Referenced by: '<S8>/Model' */
	PhaUBOfs_C = _config->PhaUBOfs_C;/* Referenced by: '<S8>/Model' */
	PhaUCCmdDialEna_C = _config->PhaUCCmdDialEna_C;/* Referenced by: '<S12>/Model' */
	PhaUCCmdDialVal_C = _config->PhaUCCmdDialVal_C;/* Referenced by: '<S12>/Model' */
	PhaUCFilTiCon_C = _config->PhaUCFilTiCon_C;/* Referenced by: '<S8>/Model' */
	PhaUCGain_C = _config->PhaUCGain_C;/* Referenced by: '<S8>/Model' */
	PhaUCOfs_C = _config->PhaUCOfs_C;/* Referenced by: '<S8>/Model' */
	PhaUDAntiWindupGain_C = _config->PhaUDAntiWindupGain_C;/* Referenced by: '<S10>/Model' */
	PhaUDCmdDialEna_C = _config->PhaUDCmdDialEna_C;/* Referenced by: '<S10>/Model' */
	PhaUDCmdDialVal_C = _config->PhaUDCmdDialVal_C;/* Referenced by: '<S10>/Model' */
	PhaUDCmdOpenLoop_C = _config->PhaUDCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */
	PhaUDGainI_C = _config->PhaUDGainI_C;/* Referenced by: '<S10>/Model' */
	PhaUDGainP_C = _config->PhaUDGainP_C;/* Referenced by: '<S10>/Model' */
	PhaUMaxVal_C = _config->PhaUMaxVal_C;/* Referenced by: '<S10>/Model' */
	PhaUQAntiWindupGain_C = _config->PhaUQAntiWindupGain_C;/* Referenced by: '<S10>/Model' */
	PhaUQCmdDialVal_C = _config->PhaUQCmdDialEna_C;/* Referenced by: '<S10>/Model' */
	PhaUQCmdDialVal_C = _config->PhaUQCmdDialVal_C;/* Referenced by: '<S10>/Model' */
	PhaUQCmdOpenLoop_C = _config->PhaUQCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */
	PhaUQGainI_C = _config->PhaUQGainI_C;/* Referenced by: '<S10>/Model' */
	PhaUQGainP_C = _config->PhaUQGainP_C;/* Referenced by: '<S10>/Model' */
	PlsOffTi_C = _config->PlsOffTi_C;/* Referenced by: '<S17>/Model' */
	PlsOnTi_C = _config->PlsOnTi_C;/* Referenced by: '<S17>/Model' */
	PwrCmdDialEna_C = _config->PwrCmdDialEna_C;/* Referenced by: '<S15>/Model' */
	PwrCmdDialVal_C = _config->PwrCmdDialVal_C;/* Referenced by: '<S15>/Model' */
	RedLedDialEna_C = _config->RedLedDialEna_C;/* Referenced by: '<S17>/Model' */
	RedLedDialVal_C = _config->RedLedDialVal_C;/* Referenced by: '<S17>/Model' */
	RedLedIvt_C = _config->RedLedIvt_C;/* Referenced by: '<S17>/Model' */
	ReloadRegisterMax_C = _config->ReloadRegisterMax_C;/* Referenced by: '<S11>/Model' */
	ResolverCosFilTiCon_C = _config->ResolverCosFilTiCon_C;/* Referenced by: '<S8>/Model' */
	ResolverCosGain_C = _config->ResolverCosGain_C;/* Referenced by: '<S8>/Model' */
	ResolverCosOfs_C = _config->ResolverCosOfs_C;/* Referenced by: '<S8>/Model' */
	ResolverExctEna_C = _config->ResolverExctEna_C;/* Referenced by: '<S17>/Model' */
	ResolverSinCosDialEna_C = _config->ResolverSinCosDialEna_C;/* Referenced by: '<S8>/Model' */
	ResolverSinCosDialVal_CA[0] = _config->ResolverSinCosDialVal_CA[0]; /* Referenced by: '<S8>/Model' */
	ResolverSinCosDialVal_CA[1] = _config->ResolverSinCosDialVal_CA[1]; /* Referenced by: '<S8>/Model' */
	ResolverSinFilTiCon_C = _config->ResolverSinFilTiCon_C;/* Referenced by: '<S8>/Model' */
	ResolverSinGain_C = _config->ResolverSinGain_C;/* Referenced by: '<S8>/Model' */
	ResolverSinOfs_C = _config->ResolverSinOfs_C;/* Referenced by: '<S8>/Model' */
	StatorInductanceD_C = _config->StatorInductanceD_C;/* Referenced by: '<S10>/Model' */
	StatorInductanceQ_C = _config->StatorInductanceQ_C;/* Referenced by: '<S10>/Model' */
	SwPwrPwmEna_C = _config->SwPwrPwmEna_C;/* Referenced by: '<S17>/Model' */
	WakeRetry_C = _config->WakeRetry_C;/* Referenced by: '<S15>/Model' */
	WakeTout_C = _config->WakeTout_C;/* Referenced by: '<S15>/Model' */
	YellowLedCmd_C = _config->YellowLedCmd_C;/* Referenced by: '<S17>/Model' */
}

void VectorControl::UpdateInputsToXcp()//float *analogData)
{
	//_analogIn->BdT1 = analogData[0];
	//_analogIn->BdT2 = analogData[1];
	//_analogIn->McuT = analogData[2];
	//_analogIn->HvBusU = analogData[3];
	//_analogIn->PhaCurA = analogData[4];
	//_analogIn->PhaCurB = analogData[5];
	//_analogIn->PhaCurC = analogData[6];
	//_analogIn->HvBusCur = analogData[7];
	//_analogIn->ResolverSinCos[0] = analogData[8];
	//_analogIn->ResolverSinCos[1] = analogData[9];

	BdT1 = _analogIn->BdT1;
	BdT2 = _analogIn->BdT2;
	McuT = _analogIn->McuT;
	// Handled in ADCINP Override
	//HvBusU = _analogIn->HvBusU;
	//PhaCurA = _analogIn->PhaCurA;
	//PhaCurB = _analogIn->PhaCurB;
	//PhaCurC = _analogIn->PhaCurC;
	//HvBusCur = _analogIn->HvBusCur;
	//ResolverSinCos[0] = _analogIn->ResolverSinCos[0];
	//ResolverSinCos[1] = _analogIn->ResolverSinCos[1];
	ASWIN_BdT1 = _analogIn->ASWIN_BdT1;
	ASWIN_BdT2 = _analogIn->ASWIN_BdT2;
	ASWIN_McuURef = _analogIn->ASWIN_McuURef;
	ASWIN_McuT = _analogIn->ASWIN_McuT;
	ASWIN_McuUBat = _analogIn->ASWIN_McuUBat;
	ASWIN_HvBusU = _analogIn->ASWIN_HvBusU;
	ASWIN_PhaCurA = _analogIn->ASWIN_PhaCurA;
	ASWIN_PhaCurB = _analogIn->ASWIN_PhaCurB;
	ASWIN_PhaCurC = _analogIn->ASWIN_PhaCurC;
	ASWIN_HvBusCur = _analogIn->ASWIN_HvBusCur;
	ASWIN_PhaUA = _analogIn->ASWIN_PhaUA;
	ASWIN_PhaUB = _analogIn->ASWIN_PhaUB;
	ASWIN_PhaUC = _analogIn->ASWIN_PhaUC;
	ASWIN_ResolverSin = _analogIn->ASWIN_ResolverSin;
	ASWIN_ResolverCos = _analogIn->ASWIN_ResolverCos;
	ASWIN_EncoderCt = _analogIn->ASWIN_EncoderCt;
	for( short x = 0; x < 8; x++)
	{
		ASWIN_McuReqDa[x] = _analogIn->ASWIN_McuReqDa[x];
	}
	ASWIN_McuReqCt = _analogIn->ASWIN_McuReqCt;
	ASWIN_MaiPwrSts = _analogIn->ASWIN_MaiPwrSts;
	ASWIN_AuxPwrSts = _analogIn->ASWIN_AuxPwrSts;
	ASWIN_EncoderZ = _analogIn->ASWIN_EncoderZ;
	DrvModReq = _analogIn->DrvModReq;
}

void VectorControl::UpdateOutputsFromXcp()
{
	// These are inputs, but are updated in the override routines
	_analogIn->HvBusU = HvBusU;
	_analogIn->PhaCurA = PhaCurA;
	_analogIn->PhaCurB = PhaCurB;
	_analogIn->PhaCurC = PhaCurC;
	_analogIn->HvBusCur = HvBusCur;
	_analogIn->ResolverSinCos[0] = ResolverSinCos[0];
	_analogIn->ResolverSinCos[1] = ResolverSinCos[1];

	_analogOut->MotPosnMag = MotPosnMag;
	_analogOut->MotSpdMag = MotSpdMag;
	for( short x = 0; x < 6; x++)
	{
		_analogOut->MotPosnTrig[x] = MotPosnTrig[x];
	}
	_analogOut->PhaCurD = PhaCurD;
	_analogOut->PhaCurQ = PhaCurQ;
	_analogOut->PhaUDCmd = PhaUDCmd;
	_analogOut->PhaUQCmd = PhaUQCmd;
	_analogOut->PhaUACmd = PhaUACmd;
	_analogOut->PhaUBCmd = PhaUBCmd;
	_analogOut->PhaUCCmd = PhaUCCmd;
	_analogOut->MotTqReqCan = MotTqReqCan;
	_analogOut->MotTqCmdSpdCtl = MotTqCmdSpdCtl;
	_analogOut->PhaCurQTar = PhaCurQTar;
	_analogOut->PhaCurDTar = PhaCurDTar;
	_analogOut->MotTqMax = MotTqMax;
	_analogOut->ASWOUT_PhaAPwmDc = ASWOUT_PhaAPwmDc;
	_analogOut->ASWOUT_PhaBPwmDc = ASWOUT_PhaBPwmDc;
	_analogOut->ASWOUT_PhaCPwmDc = ASWOUT_PhaCPwmDc;
	_analogOut->MotSpd = MotSpdReqCan;
	_analogOut->MotSpdReqCan = MotSpdReqCan;
	for( short x = 0; x < 8; x++)
	{
		_analogOut->ASWOUT_McuData2Da[x] = ASWOUT_McuData2Da[x];
	}
	for( short x = 0; x < 8; x++)
	{
		_analogOut->ASWOUT_McuData1Da[x] = ASWOUT_McuData1Da[x];
	}
	_analogOut->MaiPwrAcv = MaiPwrAcv;
	_analogOut->AuxPwrAcv = AuxPwrAcv;
	_analogOut->PwrCmd = PwrCmd;
	_analogOut->ASWOUT_GreenLed = ASWOUT_GreenLed;
	_analogOut->ASWOUT_RedLed = ASWOUT_RedLed;
	_analogOut->ASWOUT_YellowLed = ASWOUT_YellowLed;
	_analogOut->ASWOUT_ResolverExctEna = ASWOUT_ResolverExctEna;
	_analogOut->ASWOUT_CanPwrPwmEna = ASWOUT_CanPwrPwmEna;
	_analogOut->ASWOUT_InPwrPwmEna = ASWOUT_InPwrPwmEna;
	_analogOut->ASWOUT_MtrPwrPwmEna = ASWOUT_MtrPwrPwmEna;
	_analogOut->ASWOUT_SwPwrPwmEna = ASWOUT_SwPwrPwmEna;
	_analogOut->ASWOUT_PhaPwmEna = ASWOUT_PhaPwmEna;
	_analogOut->DrvMod = DrvMod;
}

void VectorControl::UpdateInputsToInt()
{
	_analogIn->BdT1 = BdT1;
	_analogIn->BdT2 = BdT2;
	_analogIn->McuT = McuT;
	_analogIn->HvBusU = HvBusU;
	_analogIn->PhaCurA = PhaCurA;
	_analogIn->PhaCurB = PhaCurB;
	_analogIn->PhaCurC = PhaCurC;
	_analogIn->HvBusCur = HvBusCur;
	_analogIn->ResolverSinCos[0] = ResolverSinCos[0];
	_analogIn->ResolverSinCos[1] = ResolverSinCos[1];
	_analogIn->ASWIN_BdT1 = ASWIN_BdT1;
	_analogIn->ASWIN_BdT2 = ASWIN_BdT2;
	_analogIn->ASWIN_McuURef = ASWIN_McuURef;
	_analogIn->ASWIN_McuT = ASWIN_McuT;
	_analogIn->ASWIN_McuUBat = ASWIN_McuUBat;
	_analogIn->ASWIN_HvBusU = ASWIN_HvBusU;
	_analogIn->ASWIN_PhaCurA = ASWIN_PhaCurA;
	_analogIn->ASWIN_PhaCurB = ASWIN_PhaCurB;
	_analogIn->ASWIN_PhaCurC = ASWIN_PhaCurC;
	_analogIn->ASWIN_HvBusCur = ASWIN_HvBusCur;
	_analogIn->ASWIN_PhaUA = ASWIN_PhaUA;
	_analogIn->ASWIN_PhaUB = ASWIN_PhaUB;
	_analogIn->ASWIN_PhaUC = ASWIN_PhaUC;
	_analogIn->ASWIN_ResolverSin = ASWIN_ResolverSin;
	_analogIn->ASWIN_ResolverCos = ASWOUT_PhaAPwmDc;
	_analogIn->ASWIN_EncoderCt = ASWIN_EncoderCt;
	for( short x = 0; x < 8; x++)
	{
		_analogIn->ASWIN_McuReqDa[x] = ASWIN_McuReqDa[x];
	}
	_analogIn->ASWIN_McuReqCt = ASWIN_McuReqCt;
	_analogIn->ASWIN_MaiPwrSts = ASWIN_MaiPwrSts;
	_analogIn->ASWIN_AuxPwrSts = ASWIN_AuxPwrSts;
	_analogIn->ASWIN_EncoderZ = ASWIN_EncoderZ;
	_analogIn->DrvModReq = DrvModReq;
}

void VectorControl::UpdateOutputsFromInt()
{
	MotPosnMag = _analogOut->MotPosnMag;
	MotSpdMag = _analogOut->MotSpdMag;
	for( short x = 0; x < 6; x++)
	{
		MotPosnTrig[x] = _analogOut->MotPosnTrig[x];
	}
	PhaCurD = _analogOut->PhaCurD;
	PhaCurQ = _analogOut->PhaCurQ;
	PhaUDCmd = _analogOut->PhaUDCmd;
	PhaUQCmd = _analogOut->PhaUQCmd;
	PhaUACmd = _analogOut->PhaUACmd;
	PhaUBCmd = _analogOut->PhaUBCmd;
	PhaUCCmd = _analogOut->PhaUCCmd;
	MotTqReqCan = _analogOut->MotTqReqCan;
	MotTqCmdSpdCtl = _analogOut->MotTqCmdSpdCtl;
	PhaCurQTar = _analogOut->PhaCurQTar;
	PhaCurDTar = _analogOut->PhaCurDTar;
	MotTqMax = _analogOut->MotTqMax;
	ASWOUT_PhaAPwmDc = _analogOut->ASWOUT_PhaAPwmDc;
	ASWOUT_PhaBPwmDc = _analogOut->ASWOUT_PhaBPwmDc;
	ASWOUT_PhaCPwmDc = _analogOut->ASWOUT_PhaCPwmDc;
	MotSpdReqCan = _analogOut->MotSpd;
	MotSpdReqCan = _analogOut->MotSpdReqCan;
	for( short x = 0; x < 8; x++)
	{
		ASWOUT_McuData2Da[x] = _analogOut->ASWOUT_McuData2Da[x];
	}
	for( short x = 0; x < 8; x++)
	{
		ASWOUT_McuData1Da[x] = _analogOut->ASWOUT_McuData1Da[x];
	}
	MaiPwrAcv = _analogOut->MaiPwrAcv;
	AuxPwrAcv = _analogOut->AuxPwrAcv;
	PwrCmd = _analogOut->PwrCmd;
	ASWOUT_GreenLed = _analogOut->ASWOUT_GreenLed;
	ASWOUT_RedLed = _analogOut->ASWOUT_RedLed;
	ASWOUT_YellowLed = _analogOut->ASWOUT_YellowLed;
	ASWOUT_ResolverExctEna = _analogOut->ASWOUT_ResolverExctEna;
	ASWOUT_CanPwrPwmEna = _analogOut->ASWOUT_CanPwrPwmEna;
	ASWOUT_InPwrPwmEna = _analogOut->ASWOUT_InPwrPwmEna;
	ASWOUT_MtrPwrPwmEna = _analogOut->ASWOUT_MtrPwrPwmEna;
	ASWOUT_SwPwrPwmEna = _analogOut->ASWOUT_SwPwrPwmEna;
	ASWOUT_PhaPwmEna = _analogOut->ASWOUT_PhaPwmEna;
	DrvMod = _analogOut->DrvMod;
}
