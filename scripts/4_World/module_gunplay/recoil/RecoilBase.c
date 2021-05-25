modded class RecoilBase{
	
	protected float m_recoilControl;
	protected float m_handsMinHorizontalRecoil;
	protected float m_handsMaxHorizontalRecoil;	
	protected float m_handsMinVerticalRecoil;
	protected float m_handsMaxVerticalRecoil;
	protected int m_handsRecoilsteps;
	protected float m_relativeReloadTime;
		
	void RecoilBase(Weapon_Base weapon){
		m_recoilControl = computeRecoilControl();
	}
	
	
	/**
	* @brief Compute the ability of the player to control the weapon recoil based on multiple variables
	* 	@return \p float - value between -1 (worst control) to +1 (best control)
	*/
	protected float computeRecoilControl(){ //to-do move this to PlayerBase?
		SLog.d("","computeRecoilControl",1, m_DebugMode );
		float control = 0;
		// vanilla softskills
		if(m_vanillaSoftSkillsAffectsRecoil){
			control += m_Player.GetSoftSkillsManager().GetSpecialtyLevel() * RecoilConstants.RECOIL_SOFTSKILL_WEIGHT;
			SLog.d("SoftSkills = "+m_Player.GetSoftSkillsManager().GetSpecialtyLevel() + " * "+RecoilConstants.RECOIL_SOFTSKILL_WEIGHT, "computeRecoilControl",2,m_DebugMode);
		}
		// player inventory weight
		if(m_inventoryAffectsRecoil){
			control -= m_Player.GetWeight() * RecoilConstants.RECOIL_INVENTORY_WEIGHT;
			SLog.d("player weight = "+m_Player.GetWeight() + " * "+RecoilConstants.RECOIL_INVENTORY_WEIGHT, "computeRecoilControl",2,m_DebugMode);
		}
		SLog.d("recoil control (clamp -1,1) = "+control, "computeRecoilControl",2,m_DebugMode);
		return Math.Clamp(control,-1,1); //to-do change this to the custom soft skills when done: weapon dexterity, strength etc
	}
	
	/**
	* @brief Compute the offset positions which the weapon will follow when shooting 
	*/
	protected void createHandRecoilPoints(){ //this gets called by every weaponRecoil.c init 
		vector newPoint;
		vector lastPoint;
		
		for (int i=0; i<m_handsRecoilsteps; i++){
			newPoint[0] = Math.RandomFloatInclusive(m_handsMinHorizontalRecoil,m_handsMaxHorizontalRecoil) * RecoilConstants.HAND_RECOIL_MULTIPLIER;
			newPoint[1] = Math.RandomFloatInclusive(m_handsMinVerticalRecoil,m_handsMaxVerticalRecoil) * RecoilConstants.HAND_RECOIL_MULTIPLIER;
			newPoint[2] = 0;
			
			if( !m_Player.IsInOptics() && !m_Player.IsInIronsights()){
				newPoint[0] = newPoint[0] * RecoilConstants.HIPFIRE_H_RECOIL_MULTIPLIER;
				newPoint[1] = newPoint[1] * RecoilConstants.HIPFIRE_V_RECOIL_MULTIPLIER;
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
			//float lerpValue = SMath.DampedSin(-0.05, 2.5, 2.7, 5.8, 1, stepValue); old - too bouncy
			float lerpValue = SMath.DampedSin(0.2, 0.8, 0.9, 1.4, 1, stepValue);
			m_HandsCurvePoints.Insert(vector.Lerp(newPoint,"0 0 0", lerpValue));
			stepValue += 0.5;
			count++;
		}
	}
	
	override void PostInit(Weapon_Base weapon){
		super.PostInit(weapon);
		computeReloadTime();
		applyRecoilControl(m_ReloadTime, m_recoilControl);
	}
	
	protected void computeReloadTime(){
		m_ReloadTime *= m_relativeReloadTime * RecoilConstants.RELOAD_TIME_MULTIPLIER;
		if(!isADS()) {
			m_ReloadTime *= RecoilConstants.HIPFIRE_RELOAD_TIME_MULTIPLIER;
		}
	}
	
	//! Destroys this object next update tick
	override void Destroy(){
		super.Destroy();
	}
	
	// called externally per update, not to be overriden in children
	override void Update( SDayZPlayerAimingModel pModel, out float axis_mouse_x, out float axis_mouse_y, out float axis_hands_x, out float axis_hands_y, float pDt ){
		if( m_DeleteRequested ){
			//SLog.d("destroying");
		}
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
		SLog.d(pRecResultX,"before");
		applyRecoilControl(pRecResultX, m_recoilControl);
		SLog.d(pRecResultX, " after");
		applyRecoilControl(pRecResultY, m_recoilControl);
	}
	
	override void ApplyHandsOffset(float pDt, out float pRecResultX, out float pRecResultY){
		super.ApplyHandsOffset(pDt, pRecResultX, pRecResultY);
		applyRecoilControl(pRecResultX, m_recoilControl);
		applyRecoilControl(pRecResultY, m_recoilControl);
	}
	
	override void ApplyCamOffset(SDayZPlayerAimingModel pModel){
        super.ApplyCamOffset(pModel);
		applyRecoilControl(pModel.m_fCamPosOffsetZ, m_recoilControl);
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
	* 	Arctangent: (early "Strength" progression (~ -0.5 , ~ 0.5) will be more visible based on the RecoilConstants.RECOIL_CONTROL_COEFF)
	*	-1 ---___
	*	         \
	*	 0        \
	*	           \___
	*	 1             ---
	*/
	protected void applyRecoilControl(out float offsetToControl, float recoilControl){
		offsetToControl = SMath.Arctan(-offsetToControl, RecoilConstants.RECOIL_CONTROL_COEFF, 0, offsetToControl, recoilControl);
	}
}