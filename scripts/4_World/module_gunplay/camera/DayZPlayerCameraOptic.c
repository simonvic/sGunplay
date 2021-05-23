//////////////////////////////////////////
// OPTICS
modded class DayZPlayerCameraOptics{
	
	protected ref TFloatArray m_opticPPMask = new TFloatArray;
	protected ref TFloatArray m_opticPPLens = new TFloatArray;
	protected float m_opticPPBlur;
	
	protected bool m_canShowLens = false;
	protected vector m_lensOffset;
	protected float m_lensOffsetVelX[1];
	protected float m_lensOffsetVelY[1];
	
	override void OnActivate (DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera,pPrevCameraResult);
		
		m_opticsUsed.InitOpticsPP(m_opticPPMask, m_opticPPLens, m_opticPPBlur);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.setShowLens, m_enteringTransitionTime*1000 + GunplayConstants.ADS_LENS_ACTIVATION_DELAY, false, true);
		
		PlayerBase player = PlayerBase.Cast(m_pPlayer);
		if (player){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(player.HideClothing, m_enteringTransitionTime*1000,false,m_opticsUsed,true);
		}
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.OnUpdate(pDt, pOutResult);
		//@todo do proper activation/deactivation
		if(m_player.IsInOptics() && isMagnifyingOptic()){
			updateLens(pDt);
		}
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
	override void computeFOVFocusValues(out float targetFOV, out float speed){
		speed = 0.2;
		targetFOV = GetDayZGame().GetUserFOV();
		
		//Handheld optics
		if(isHandHeldOptic()){
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			return;
		}
		
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
		SLog.d("reset ppe","",1,true);
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
	
	/**
	*	@brief Update the lens effect position and strength along with the PP mask
	*/
	protected void updateLens(float pDt){
		if(!canShowLens()) return;
		if(isHandHeldOptic()) return; 

		m_lensOffset = GetGame().GetScreenPosRelative(m_aimingModel.getWeaponTargetPosition());
		//m_lensOffset[0] = Math.SmoothCD(m_lensOffset[0], m_lensOffset[0], m_lensOffsetVelX, 0.03, 1000, pDt);
		//m_lensOffset[1] = Math.SmoothCD(m_lensOffset[1], m_lensOffset[1], m_lensOffsetVelY, 0.03, 1000, pDt);
		
		PPEManager.requestOpticMask(computeMask(m_opticPPMask, m_lensOffset[0], m_lensOffset[1]));
		PPEManager.requestOpticLens(computeLens(m_opticPPLens, m_lensOffset[0], m_lensOffset[1]));
	}
	
	/**
	*	@brief Compute the mask position, radius, and blur(smooth opacity)
	*	 Mask = {positionX [-1, 1], positionY [-1, 1], radius, blur}
	*	 @param mask \p TFloatArray - Starting mask array
	*	 @param offsetX \p float - arbitrary X offset
	*	 @param offsetY \p float - arbitrary Y offset
	*	 @return TFloatArray - computed mask array
	*/
	protected TFloatArray computeMask(TFloatArray mask, float offsetX, float offsetY){		
		return {
			mask[0] + offsetX,                                                        //X position
			mask[1] + offsetY,                                                        //Y position
			mask[2] / Math.Pow(m_camManager.getAdsFovReduction(),2) / m_fFovAbsolute, //radius
			mask[3]};                                                                 //blur
	}
	
	/**
	*	@brief Compute the lens intensity, position, and chromatic aberration
	*	 Lens = {intensity [-i, +i], positionX [-1, 1], positionY [-1, 1], chromatic aberration}
	*	 @param lens \p TFloatArray - Starting lens array
	*	 @param offsetX \p float - arbitrary X offset
	*	 @param offsetY \p float - arbitrary Y offset
	*	 @return TFloatArray - computed lens array
	*/
	protected TFloatArray computeLens(TFloatArray lens, float offsetX, float offsetY){
		//offsetX * 2 - 1; //@todo why the fuck does this work????!!!
		return  {
			lens[0] * m_camManager.getLensZoomStrength(),                                   //intensity
			lens[1] + (offsetX * 2 - 1),                                                    //X position
			lens[2] + (offsetY * 2 - 1) + getLensZeroingOffset(m_opticsUsed, 0.6, 0.05),    //Y position
			lens[3]};                                                                       //chrom aber	
	}
	
	/**
	*	@brief Get the offset based on the zeroing index of the scope
	*	 @param zeroing \p int - zeroing index
	*	 @param decay \p float - 
	*	 @param amplitude \p float - 
	*/
	static float getLensZeroingOffset(ItemOptics optic, float decay, float amplitude){
		return Math.Pow(optic.GetStepZeroing(), decay) * amplitude;
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
	
	protected bool canShowLens(){
		return m_canShowLens;
	}
	
	protected void setShowLens(bool showable){
		m_canShowLens = showable;
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

	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_OPTICS;
	}
		
}