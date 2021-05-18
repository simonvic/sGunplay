modded class DayZPlayerImplement{

	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished){
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
	}
	
	override bool AimingModel(float pDt, SDayZPlayerAimingModel pModel){
		m_AimingModel.m_isSCrosshairVisible = false;
		return super.AimingModel(pDt, pModel);
	}
			
	override void HandleADS(){
		super.HandleADS();
		
		UAInput uain = GetUApi().GetInputByName("SUA_ADSWeaponInspect");
		
		if(uain.LocalPress() || uain.LocalHold()){
			DayZPlayerCameraIronsights.isInspectingWeapon = GetInputController().CameraIsFreeLook();
		}
		
		if(uain.LocalRelease()){
			DayZPlayerCameraIronsights.isInspectingWeapon = false;
		}

	}
	
}