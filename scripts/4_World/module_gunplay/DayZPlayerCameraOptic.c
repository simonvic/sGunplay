//////////////////////////////////////////
// OPTICS
modded class DayZPlayerCameraOptics{
	override void OnActivate (DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera,pPrevCameraResult);
		
		PlayerBase player = PlayerBase.Cast(m_pPlayer);
		if (player){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(player.HideClothing,m_CameraPPDelay*1000,false,m_opticsUsed,false);
		}
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.OnUpdate(pDt, pOutResult);
	}
	
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult){
		m_iBoneIndex = m_pPlayer.GetBoneIndexByName("RightHand_Dummy");
		if(m_iBoneIndex == -1 ) m_iBoneIndex = m_pPlayer.GetBoneIndexByName("Head");
		pOutResult.m_iDirectBone 			= m_iBoneIndex;
		pOutResult.m_iDirectBoneMode 		= 3;
	
		pOutResult.m_fFovAbsolute = m_fFovAbsolute;
		//pOutResult.m_fFovMultiplier = 1.0;
		
		pOutResult.m_bUpdateWhenBlendOut	= false;
		pOutResult.m_fDistance 				= 0;
		pOutResult.m_fUseHeading 			= 0.0;
		pOutResult.m_fInsideCamera 			= 1.0;
		pOutResult.m_fShootFromCamera		= 0.0;
		pOutResult.m_fIgnoreParentRoll      = 0.0;
		pOutResult.m_fNearPlane = 0.06; //0.07 default
	}
	
	override void updateFOVFocus(float pDt, out DayZPlayerCameraResult pOutResult){
		super.updateFOVFocus(pDt, pOutResult);	
		
	}
		
	override void getFOVFocusValues(out float targetFOV, out float speed){
		speed = 0.2;
		targetFOV = GetDayZGame().GetUserFOV();
		
		// No optic
		if (!m_opticsUsed){	
			SLog.d("No optic used");
			m_fFovAbsolute = targetFOV; //immediately
			return;
		}
		
		float opticCurrentFOV = m_opticsUsed.GetCurrentStepFOV();
		float fovReduction = SMath.mapTo(m_camManager.getAdsFovReduction(), 0, 1, 2, 3);
		
		
		// Non magnifying optic
		if(!isMagnifyingOptic()){
			SLog.d("non mang");
			if(playerIsFocusing()){
				targetFOV = opticCurrentFOV;
				speed = getFocusSpeed();
			}
			return;
		}
		
		// Magnifying optic
		if(isSniperOptic()){
			targetFOV = opticCurrentFOV;
			speed = 0.0001;
		}else{
			targetFOV = opticCurrentFOV * fovReduction;
		}
						
		if (m_isEntering){
			m_fFovAbsolute = opticCurrentFOV * fovReduction; // immediately set the fov
			m_isEntering = false;
		}else if (playerIsFocusing()){
			targetFOV = opticCurrentFOV;
			speed = getFocusSpeed();
		}
		
		
		
	}
	
	

	
	protected void resetPPE(){
		SLog.d("reset ppe");
		PPEffects.ResetPPMask();
		PPEffects.SetLensEffect(0, 0, 0, 0);
		PPEffects.OverrideDOF(false, 0, 0, 0, 0, 1);
		PPEffects.SetBlurOptics(0);
		
		if (IsCameraNV()){
			SetNVPostprocess(NVTypes.NV_GOGGLES);
		}else{
			SetNVPostprocess(NVTypes.NONE);
		}
		
		if (m_weaponUsed){
			m_weaponUsed.HideWeaponBarrel(false);
		}
	}
	
	protected void updateNightVision(bool allowNightVisionGoggles = false){
		// optics NV mode
		SLog.d("updateNightVision");
		if (m_opticsUsed.IsNVOptic()){
			if (m_opticsUsed.IsWorking()){
				SetCameraNV(true);
				SetNVPostprocess(NVTypes.NV_OPTICS_ON);
			}else{
				SetCameraNV(false);
				SetNVPostprocess(NVTypes.NV_OPTICS_OFF);
			}
		}else{
			if (IsCameraNV() && allowNightVisionGoggles){
				SetNVPostprocess(NVTypes.NV_GOGGLES);
			}else{
				SetNVPostprocess(NVTypes.NONE);
			}
		}
	}
	
	protected void setNonMagnifyingOpticPPE(){
		SLog.d("setNonMagnifyingOpticPPE");
		PPEffects.SetLensEffect(0, 0, 0, 0);
		
		if (!m_weaponUsed){
			PPEffects.OverrideDOF(false, 0, 0, 0, 0, 1);
			return;
		}
		
		if (m_opticsUsed.GetOpticsDOF().Count() == 6){
			temp_array = m_opticsUsed.GetOpticsDOF();
		}else{
			temp_array = m_weaponUsed.GetWeaponDOF(); //TODO should some optics have own DOF settings (different eye point)?
		}
		
		if (temp_array.Count() == 6){
			PPEffects.OverrideDOF(temp_array[0],temp_array[1],temp_array[2],temp_array[3],temp_array[4],temp_array[5]);
		}
	}
	
	protected void updateLens(){
		SLog.d("updateLens");
		// optics mask
		if (m_opticsUsed.GetOpticsPPMask() && m_opticsUsed.GetOpticsPPMask().Count() == 4){
			temp_array = m_opticsUsed.GetOpticsPPMask();
			
			//PPEffects.AddPPMask(temp_array[0], temp_array[1], temp_array[2], temp_array[3]);
			//PPEffects.AddPPMask(0.5, 0.5, 0.4, 0.05);
		}
		
		//optics lens
		if (m_opticsUsed.GetOpticsPPLens() && m_opticsUsed.GetOpticsPPLens().Count() == 4){
			temp_array = m_opticsUsed.GetOpticsPPLens();
			
			//PPEffects.SetLensEffect(temp_array[0], temp_array[1], temp_array[2], temp_array[3]);
			//PPEffects.SetLensEffect(1, 0.15, 0, 0 );
		}else{
			PPEffects.SetLensEffect(0, 0, 0, 0);
		}
	}
	
	protected void updateBlur(){
		SLog.d("updateBlur");
		//optics blur
		if (m_opticsUsed.GetOpticsPPBlur() != 0){
			PPEffects.SetBlurOptics(m_opticsUsed.GetOpticsPPBlur());
		}else{
			PPEffects.SetBlurOptics(0);
		}
	}
	
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom){
		//Print("SetCameraPP - optics");
		if (!isOpticChange(state, launchedFrom)){
			resetPPE();
			return;
		}
		
		
		// 1x scopes only
		if (!isMagnifyingOptic() && !NVGoggles.Cast(m_opticsUsed)){
			setNonMagnifyingOpticPPE();
			updateNightVision(true);
		}else {//magnifying scopes
			
			updateLens();
			updateBlur();
			updateNightVision(false);
		}
		
		if (m_weaponUsed){
			m_weaponUsed.HideWeaponBarrel(m_camManager.isHideWeaponBarrelInOpticEnabled());
		}
		
	}
	
	protected bool isOpticChange(bool state, DayZPlayerCamera launchedFrom){
		return state && m_opticsUsed && (PlayerBase.Cast(m_pPlayer) && launchedFrom == PlayerBase.Cast(m_pPlayer).GetCurrentPlayerCamera());
	}
	
	override bool canApplyDeadzone(){
		return super.canApplyDeadzone();
	}
	
	override bool canApplyHandsOffset(){
		return super.canApplyHandsOffset();
	}
	
	override bool canZoom(){
		return super.canZoom();
	}
	
	override bool canFreelook(){
		return false;
	}
	
	override bool canInspectWeapon(){
		return false;
	}
	
	override bool isMagnifyingOptic(){
		return !m_opticsUsed.AllowsDOF();
	}
	
	override bool isSniperOptic(){
		return m_opticsUsed.GetStepFOVCount() > 0;
	}
	
		
}