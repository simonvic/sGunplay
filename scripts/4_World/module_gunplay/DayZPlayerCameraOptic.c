//////////////////////////////////////////
// OPTICS
modded class DayZPlayerCameraOptics{
	override void OnActivate (DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera,pPrevCameraResult);
		
		PlayerBase player = PlayerBase.Cast(m_pPlayer);
		if (player){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(player.HideClothing,m_CameraPPDelay*1000,false,m_opticsUsed,true);
		}
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.OnUpdate(pDt, pOutResult);
		updateLens();
	}
	
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult){
		m_iBoneIndex = m_pPlayer.GetBoneIndexByName("RightHand_Dummy");
		if(m_iBoneIndex == -1 ) m_iBoneIndex = m_pPlayer.GetBoneIndexByName("Head");
		pOutResult.m_iDirectBone 			= m_iBoneIndex;
		pOutResult.m_iDirectBoneMode 		= 3;
		
		//m_fFovAbsolute = GetDayZGame().GetUserFOV();
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
		
	//@todo move stuff out of here if not needed updating every fram
	override void getFOVFocusValues(out float targetFOV, out float speed){
		speed = 0.2;
		targetFOV = GetDayZGame().GetUserFOV();
		
		// No optic
		if (!m_opticsUsed){	
			m_fFovAbsolute = targetFOV; //immediately
			return;
		}
		
		float opticCurrentFOV = m_opticsUsed.GetCurrentStepFOV();
		float fovReduction = m_camManager.getAdsFovReduction();
		
		// Non magnifying optic
		if(!isMagnifyingOptic()){
			if(playerIsFocusing()){
				targetFOV = opticCurrentFOV;
				speed = getFocusSpeed();
			}
			return;
		}
		
		// Sniping optic
		if(isSniperOptic()){
			targetFOV = opticCurrentFOV;
			speed = 0.0001;
			return;
		}
			
		// Magnifying optic
		targetFOV = opticCurrentFOV * fovReduction;
			
		//@todo optimize this			
		if (m_isEntering){
			m_fFovAbsolute = targetFOV; // immediately set the fov
			m_isEntering = false;
		}else if (playerIsFocusing()){
			targetFOV = opticCurrentFOV;
			speed = getFocusSpeed();
		}
		
		
		
	}
	
	

	
	protected void resetPPE(){
		SLog.d("reset ppe","",1,false);
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
	
	protected void updateNightVision(bool allowNightVisionGoggles){
		// optics NV mode
		SLog.d("updateNightVision","",1,false);
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
		SLog.d("setNonMagnifyingOpticPPE","",1,false);
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
		SLog.d("updateLens","",1,false);
		// optics mask
		TFloatArray mask = new TFloatArray;
		TFloatArray lens = new TFloatArray;
		float blur;
		
		m_opticsUsed.InitOpticsPP(mask, lens, blur);		

		computeMask(mask);
		computeLens(lens);
		PPEManager.requestOpticMask(mask);
		PPEManager.requestOpticLens(lens);

	}
	
	protected void computeMask(TFloatArray mask){		
		mask[0] = m_aimingModel.getSCrosshairPosition()[0]; //X position
		mask[1] = m_aimingModel.getSCrosshairPosition()[1]; //Y position
		mask[2] = (mask[2] / (Math.Pow(m_camManager.getAdsFovReduction(),2)) / m_fFovAbsolute; //radius
		mask[3] = 0.001; //blur
	}
	
	protected void computeLens(TFloatArray lens){
		/*
		lens[0] = lens[0] * m_camManager.getLensZoomStrength(); //intensity
		lens[1] = lens[1]; //X position
		lens[2] = lens[2] + m_opticsUsed.GetStepZeroing() * 0.05; //Y position
		lens[3] = 0; //chrom aber
		*/
		lens[0] = lens[0] * m_camManager.getLensZoomStrength(); //intensity
		lens[1] = 0; //X position
		lens[2] = m_opticsUsed.GetStepZeroing() * 0.05; //Y position
		lens[3] = 0; //chrom aber
		
	
	}
	
	protected void updateBlur(){
		SLog.d("updateBlur","",1,false);
		//optics blur
		if (m_opticsUsed.GetOpticsPPBlur() != 0){
			PPEffects.SetBlurOptics(m_opticsUsed.GetOpticsPPBlur());
		}else{
			PPEffects.SetBlurOptics(0);
		}
	}
	
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom){
		SLog.d("SetCameraPP");
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
		return super.canApplyDeadzone() && !isSniperOptic();
	}
	
	override bool canApplyHandsOffset(){
		return super.canApplyHandsOffset() && !isSniperOptic();
	}
	
	override bool canZoom(){
		return super.canZoom();
	}
	
	override bool canFreelook(){
		return super.canFreelook() && !isMagnifyingOptic();
	}
	
	override bool canInspectWeapon(){
		return super.canInspectWeapon() && !isMagnifyingOptic();
	}
	
	override bool isMagnifyingOptic(){
		return !m_opticsUsed.AllowsDOF();
	}
	
	override bool isSniperOptic(){
		return m_opticsUsed.GetStepFOVCount() > 0;
	}
	
		
}