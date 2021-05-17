modded class DayZPlayerImplement{

	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished){
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);

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