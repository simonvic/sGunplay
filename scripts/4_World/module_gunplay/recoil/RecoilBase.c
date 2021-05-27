modded class RecoilBase{
	
	protected float m_recoilControl;
	protected float m_handsMinHorizontalRecoil;
	protected float m_handsMaxHorizontalRecoil;	
	protected float m_handsMinVerticalRecoil;
	protected float m_handsMaxVerticalRecoil;
	protected int m_handsRecoilsteps;
	protected float m_relativeReloadTime;
	
	protected vector m_currentMouseOffset;
	protected vector m_currentHandsOffset;
	protected vector m_currentCamOffset;
		
	void RecoilBase(Weapon_Base weapon){
		m_recoilControl = computeRecoilControl();
	}
	
	
	/**
	* @brief Compute the ability of the player to control the weapon recoil based on multiple variables
	* 	@return \p float - value between -1 (worst control) to +1 (best control)
	*/
	protected float computeRecoilControl(){
		float control = 0;
		// vanilla softskills
		if(GunplayConstants.RECOIL_CONTROL_USE_STRENGTH){
			control += m_Player.GetSoftSkillsManager().GetSpecialtyLevel() * GunplayConstants.RECOIL_CONTROL_STRENGTH_WEIGHT;
		}
		// player inventory weight
		if(GunplayConstants.RECOIL_CONTROL_USE_PLAYER_INVENTORY_WEIGHT){
			control += m_Player.GetWeight() * GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT;
		}
		
		// stance
		if(GunplayConstants.RECOIL_CONTROL_USE_STANCE){
			control *= getStanceRecoilControl();
		}
		
		// movement
		if(GunplayConstants.RECOIL_CONTROL_USE_MOVEMENT){
			control *= getMovementRecoilControl();
		}

		return Math.Clamp(control,-1,1); //to-do change this to the custom soft skills when done: weapon dexterity, strength etc
	}
	
	
	/**
	*	@brief Get the recoil control multiplier based on the player stance
	*	 @return float - recoil control multiplier
	*/
	protected float getStanceRecoilControl(){
		if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_ERECT;
		} else if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_CROUCHED;
		} else if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_PRONE;
		} 
		
		return 1;
	}
	
	/**
	*	@brief Get the recoil control multiplier based on the player movement
	*	 @return float - recoil control multiplier
	*/
	protected float getMovementRecoilControl(){
		switch(m_Player.m_MovementState.m_iMovement){ 
			case 0:	return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_STANDING;			
			case 1:	return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_WALKING;
			case 2:	return GunplayConstants.RECOIL_CONTROL_MULTIPLIER_JOGGING;
		}
		
		return 1;
	}
	
	/**
	*	@brief Compute the "reload time", the time that takes to repositionate the weapon
	*/
	protected void computeReloadTime(){
		m_ReloadTime *= m_relativeReloadTime * GunplayConstants.RECOIL_RELOAD_TIME_MULTIPLIER;
		if(!isADS()) {
			m_ReloadTime *= GunplayConstants.RECOIL_HIPFIRE_RELOAD_TIME_MULTIPLIER;
		}
	}
	
	/**
	* @brief Compute the offset positions which the weapon will follow when shooting 
	*/
	protected void createHandRecoilPoints(){ //this gets called by every weaponRecoil.c init 
		vector newPoint;
		vector lastPoint;
		
		for (int i=0; i<m_handsRecoilsteps; i++){
			newPoint[0] = Math.RandomFloatInclusive(m_handsMinHorizontalRecoil,m_handsMaxHorizontalRecoil) * GunplayConstants.RECOIL_HAND_MULTIPLIER;
			newPoint[1] = Math.RandomFloatInclusive(m_handsMinVerticalRecoil,m_handsMaxVerticalRecoil) * GunplayConstants.RECOIL_HAND_MULTIPLIER;
			newPoint[2] = 0;
			
			if( !isADS()){
				newPoint[0] = newPoint[0] * GunplayConstants.RECOIL_HIPFIRE_H_MULTIPLIER;
				newPoint[1] = newPoint[1] * GunplayConstants.RECOIL_HIPFIRE_V_MULTIPLIER;
			}
			m_HandsCurvePoints.Insert(newPoint);
		}
		
		/*smoother transition from last recoil point to "0 0 0" following a damped sin wave (something like this):
			  _
			 / \        __
			/   \      /  \     ______
			     \    /    \___/
			      \__/
			                         Call me Giotto please
		*/
		
		float stepValue = -1;
		float count = 0;
		while(stepValue <= 1.5){
			//float lerpValue = SMath.DampedSin(-0.05, 2.5, 2.7, 5.8, 1, stepValue); //old - too bouncy
			float lerpValue = getDampedSin(stepValue);
			m_HandsCurvePoints.Insert(vector.Lerp(newPoint,"0 0 0", lerpValue));
			stepValue += 0.5;
			count++;
		}
	}
	
	protected float getDampedSin(float time){
		return SMath.DampedSin(0.2, 0.8, 0.9, 5, 1, time);
	}
	
	override void PostInit(Weapon_Base weapon){
		super.PostInit(weapon);
		computeReloadTime();
		applyRecoilControl(m_ReloadTime, m_recoilControl);
	}
	
	//! Destroys this object next update tick
	override void Destroy(){
		super.Destroy();
	}
	
	// called externally per update, not to be overriden in children
	override void Update( SDayZPlayerAimingModel pModel, out float axis_mouse_x, out float axis_mouse_y, out float axis_hands_x, out float axis_hands_y, float pDt ){
		super.Update(pModel, axis_mouse_x, axis_mouse_y, axis_hands_x, axis_hands_y, pDt);
	}
	
	override void ApplyMouseOffset(float pDt, out float pRecResultX, out float pRecResultY){
		if( m_MouseOffsetTargetAccum[1] < m_MouseOffsetTarget[1] ){
			float relative_delta = pDt / m_ReloadTime / Math.Clamp(m_MouseOffsetRelativeTime , 0.001,1);
			
			float delta_mouse_offset_x = m_MouseOffsetTarget[0] * relative_delta;
			float delta_mouse_offset_y = m_MouseOffsetTarget[1] * relative_delta;
			
			if( ( m_MouseOffsetTargetAccum[1] + delta_mouse_offset_y) > m_MouseOffsetTarget[1] ){
				delta_mouse_offset_x = m_MouseOffsetTarget[0] - m_MouseOffsetTargetAccum[0];
				delta_mouse_offset_y = m_MouseOffsetTarget[1] - m_MouseOffsetTargetAccum[1];
			}
			
			m_MouseOffsetTargetAccum[0] = m_MouseOffsetTargetAccum[0] + delta_mouse_offset_x;
			m_MouseOffsetTargetAccum[1] = m_MouseOffsetTargetAccum[1] + delta_mouse_offset_y;
			
			pRecResultX = delta_mouse_offset_x;
			pRecResultY = delta_mouse_offset_y;
			
		}	
		applyRecoilControl(pRecResultX, m_recoilControl);
		applyRecoilControl(pRecResultY, m_recoilControl);
		
		m_currentMouseOffset[0] = pRecResultX;
		m_currentMouseOffset[1] = pRecResultY;
	}
	
	override void ApplyHandsOffset(float pDt, out float pRecResultX, out float pRecResultY){
		float relative_time = m_TimeNormalized / Math.Clamp(m_HandsOffsetRelativeTime, 0.001,5);
		vector pos_on_curve = GetPositionOnCurve(m_HandsCurvePoints, relative_time);
		pRecResultX = pos_on_curve[0];
		pRecResultY = pos_on_curve[1];
		applyRecoilControl(pRecResultX, m_recoilControl);
		applyRecoilControl(pRecResultY, m_recoilControl);
		m_currentHandsOffset[0] = pRecResultX;
		m_currentHandsOffset[1] = pRecResultY;
	}
	
	override void ApplyCamOffset(SDayZPlayerAimingModel pModel){
        float time_rel = Math.Clamp(Math.InverseLerp(0, m_CamOffsetRelativeTime, m_TimeNormalized), 0, 1);
        float offset = 0;
        float time = Easing.EaseOutBack(time_rel);
		
        if(time == 1){
            offset = 0;
        }else{
            offset = Math.Lerp(m_CamOffsetDistance,0,time);	
        }
		
		//=====Recoil control
        //pModel.m_fCamPosOffsetZ = Math.Lerp(offset,0,m_recoilControl); // linear
		//pModel.m_fCamPosOffsetZ = SMath.Gauss(offset,-1,RecoilConstants.RECOIL_CONTROL_COEFF,m_recoilControl); // gauss
		applyRecoilControl(offset, m_recoilControl);
		pModel.m_fCamPosOffsetZ = offset;
		m_currentCamOffset[2] = offset;
    }
	
	override vector GetPositionOnCurve(array<vector> points, float time){
		return super.GetPositionOnCurve(points, time);
	}
	
	/**
	* @brief Check if player is aiming down sight
	* 	@return \p bool - player is ADS
	*/
	protected bool isADS(){
		return m_Player.IsInOptics() || m_Player.IsInIronsights();
	}
	
	/**
	* @brief Apply the player ability to control the recoil
	* 	@param offsetToControl \p float - value to be modified
	* 
	* 
	* 	Arctangent: (early "Strength" progression (~ -0.5 , ~ 0.5) will be more visible based on the GunplayConstants.RECOIL_CONTROL_COEFF)
	*	-1 ---___
	*	         \
	*	 0        \
	*	           \___
	*	 1             ---
	*/
	protected void applyRecoilControl(out float offsetToControl, float recoilControl){
		offsetToControl = SMath.Arctan(-offsetToControl, GunplayConstants.RECOIL_CONTROL_COEFF, 0, offsetToControl, recoilControl);
	}
	
	vector getCurrentMouseOffset(){
		return m_currentMouseOffset;
	}

	vector getCurrentCamOffset(){
		return m_currentCamOffset;
	}

	vector getCurrentHandsOffset(){
		return m_currentHandsOffset;
	}
}
