modded class DayZPlayerImplementAiming{
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);
		DayZPlayerCameraIronsights.m_weaponDeadzoneX = pModel.m_fAimXCamOffset;
		DayZPlayerCameraIronsights.m_weaponDeadzoneY = pModel.m_fAimYCamOffset;
		return result;
	}
}