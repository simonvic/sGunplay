modded class DayZPlayerCameraBase{
	
	protected static ref SCOOpticMisalignment m_opticMisalignmentOverlay = new SCOOpticMisalignment();
	
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom) {
		super.SetCameraPP(state, launchedFrom);
		SPPEManager.resetMask();
		SPPEManager.resetOpticLens();
	}
	
	override void OnActivate(DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera, pPrevCameraResult);
		if (pPrevCamera && pPrevCamera.Type() == DayZPlayerCameraOptics) {
			SCameraOverlaysManager.getInstance().deactivate(m_opticMisalignmentOverlay);
		}
	}
}