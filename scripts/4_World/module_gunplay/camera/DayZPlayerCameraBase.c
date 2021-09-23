modded class DayZPlayerCameraBase{
	
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom) {
		super.SetCameraPP(state, launchedFrom);
		SPPEManager.resetMask();
		SPPEManager.resetOpticLens();
	}
	
}