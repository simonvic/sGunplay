/**
*	Transparent data carrier of random recoil values, to be used from outside
*/
modded class RecoilBase {
	
	static bool legacyMode = false;
	static int refcount;
	
	void RecoilBase(Weapon_Base weapon) {
		if (legacyMode) {
			m_recoilControl = computeRecoilControl();
		} else {
			initRecoilParameters();
			compute();
		}
		refcount++;
	}
	
	void ~RecoilBase() {
		refcount--;
	}
	
	protected void initRecoilParameters();
	
	//@todo replace hands and mouse with vector for more precision?
	
	//////////////////////////////////////////////////
	// IN
	float handsRanges[4]       = {-0.350, 0.450,  1.250,  1.300}; // Hands offset random ranges {min horizontal, max horizontal, min vertical, max vertical}
	float handsAccumSpeed      = 0.925;                           // speed of hands offset accumulation
	float handsResetSpeed      = 0.400;                           // speed of hands offset reset
	
	float misalignIntensity[2] = {0.150, 0.150};                  // Misalignment intensity compared to handsRanges {intensity horizontal, intensity vertical}
	float misalignAccumSpeed   = 0.600;                           // speed of misalignment accumulation
	float misalignResetSpeed   = 0.200;                           // speed of misalignment reset
	
	float mouseRanges[4]       = {-0.050, 0.100,  1.500,  1.600}; // Mouse offset random ranges {min horizontal, max horizontal, min vertical, max vertical}
	float mouseTime            = 0.250;                           // speed of mouse movement
	
	float kick                 = 0.0314;                          // Back kick intensity
	float kickResetTime        = 1.000;                           // speed of back kick reset
	//////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////
	// OUT
	float hands[2];
	float mouse[2];
	//////////////////////////////////////////////////
	
	array<ref array<string>> toDebugTable() {
		array<ref array<string>> t = {{ClassName()}};
		t.Insert({"handsRanges",       string.Format("%1 %2 %3 %4", handsRanges[0],    handsRanges[1],     handsRanges[2],    handsRanges[3])});
		t.Insert({"handsAccumSpeed",   ""+handsAccumSpeed});
		t.Insert({"handsResetSpeed",   ""+handsResetSpeed});
		t.Insert({"misalignIntensity", string.Format("%1 %2", misalignIntensity[0],    misalignIntensity[1])});
		t.Insert({"misalignAccumSpeed",""+misalignAccumSpeed});
		t.Insert({"misalignResetSpeed",""+misalignResetSpeed});
		t.Insert({"mouseRanges",       string.Format("%1 %2 %3 %4", mouseRanges[0],    mouseRanges[1],     mouseRanges[2],    mouseRanges[3])});
		t.Insert({"mouseTime",         ""+mouseTime});		
		t.Insert({"kick",              ""+kick});
		t.Insert({"kickResetTime",     ""+kickResetTime});
		return t;
	}
	
	static array<string> getCSVHeader() {
		return {
			"weapon"
			"handsMinX"
			"handsMaxX"
			"handsMinY"
			"handsMaxY"
			"handsAccumSpeed"
			"handsResetSpeed"
			"misalignIntensityX"
			"misalignIntensityY"
			"mouseMinX"
			"mouseMaxX"
			"mouseMinY"
			"mouseMaxY"
			"mouseTime"
			"kick"
			"kickResetTime"
		};
	}
	array<string> toCSV() {
		return {
			""+handsRanges[0]
			""+handsRanges[1]
			""+handsRanges[2]
			""+handsRanges[3]
			""+handsAccumSpeed
			""+handsResetSpeed
			""+misalignIntensity[0]
			""+misalignIntensity[1]
			""+mouseRanges[0]
			""+mouseRanges[1]
			""+mouseRanges[2]
			""+mouseRanges[3]
			""+mouseTime
			""+kick
			""+kickResetTime
		};
	}
	
	static array<ref array<string>> toCSV(array<ref RecoilBase> recoils) {
		array<ref array<string>> csv = {getCSVHeader()};
		foreach (RecoilBase r : recoils) {
			csv.Insert(r.toCSV());
		}
		return csv;
	}
	
	static string toCSVStringAll() {
		array<ref RecoilBase> recoils = {
			new Ak101Recoil(null),
			new Ak74Recoil(null),
			new AkmRecoil(null),
			new Aks74uRecoil(null),
			new B95Recoil(null),
			new Colt1911Recoil(null),
			new CZ527Recoil(null),
			new DEagleRecoil(null),
			new FALRecoil(null),
			new Fnx45Recoil(null),
			new GlockRecoil(null),
			new Izh43Recoil(null),
			new Izh18SawedOffRecoil(null),
			new M4a1Recoil(null),
			new MagnumRecoil(null),
			new MakarovRecoil(null),
			new MkiiRecoil(null),
			new MosinRecoil(null),
			new MosinSawedOffRecoil(null),
			new Mp133Recoil(null),
			new Mp5kRecoil(null),
			new RepeaterRecoil(null),
			new Ruger1022Recoil(null),
			new ScoutRecoil(null),
			new SiagaRecoil(null),
			new Cz61Recoil(null),
			new SKSRecoil(null),
			new SvdRecoil(null),
			new Ump45Recoil(null),
			new VSSRecoil(null),
			new Winchester70Recoil(null)
		};
		string delimiter = "\"";
		string separator = ",";
		string csv;
		auto header = getCSVHeader();
		foreach (auto column : header) {
			csv += string.Format("%1%2%1%3", delimiter, column, separator);
		}
		csv += "\n";
		foreach (auto recoil : recoils) {
			csv += string.Format("%1%2%1", delimiter, recoil.Type());
			auto values = recoil.toCSV();
			foreach (auto value : values) {
				csv += string.Format("%3%1%2%1", delimiter, value, separator);
			}
			csv += "\n";
		}
		return csv;
	}
	
	
	protected void compute() {
		computeOffsetHands();
		computeOffsetMouse();
	}
	
	protected void computeOffsetHands() {
		hands = {
			getSyncedRandom(handsRanges[0], handsRanges[1]),
			getSyncedRandom(handsRanges[2], handsRanges[3])
		};
	}
	
	protected void computeOffsetMouse() {
		mouse = {
			getSyncedRandom(mouseRanges[0], mouseRanges[1]),
			getSyncedRandom(mouseRanges[2], mouseRanges[3])
		};
	}
	
	protected float getSyncedRandom(float min = 0, float max = 1) {
		return m_Player.GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSRecoil, min, max);
	}
	
	
	
	
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LEGACY
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
	
	
	/**
	*	@brief Compute the ability of the player to control the weapon recoil based on multiple variables
	*	 @return \p float - value between -1 (worst control) to +1 (best control)
	*/
	protected float computeRecoilControl(){
		float control = 0;
		if(GunplayConstants.RECOIL_CONTROL_USE_STRENGTH){
			control += computeStrengthRecoilControl();
		}
		
		if(GunplayConstants.RECOIL_CONTROL_USE_PLAYER_INVENTORY_WEIGHT){
			control += computeInventoryWeightRecoilControl();
		}
		
		if(GunplayConstants.RECOIL_CONTROL_USE_STANCE){
			control += computeStanceRecoilControl();
		}
		
		if(GunplayConstants.RECOIL_CONTROL_USE_MOVEMENT){
			control += computeMovementRecoilControl();
		}

		return Math.Clamp(control, GunplayConstants.RECOIL_CONTROL_MINIMUM, GunplayConstants.RECOIL_CONTROL_MAXIMUM); //to-do change this to the custom soft skills when done: weapon dexterity, strength etc
	}
	
	/**
	*	@brief compute the recoil control based on strength
	*/
	protected float computeStrengthRecoilControl(){
		return m_Player.GetSoftSkillsManager().GetSpecialtyLevel() * GunplayConstants.RECOIL_CONTROL_STRENGTH_WEIGHT;
	}
	
	/**
	*	@brief compute the recoil control based on the player inventory weight
	*/
	protected float computeInventoryWeightRecoilControl(){
		return GunplayConstants.RECOIL_CONTROL_INVENTORY_MINIMUM + (m_Player.GetWeight() * GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT);
	}
	
	/**
	*	@brief compute the recoil control based on player stance
	*/
	protected float computeStanceRecoilControl(){
		return GunplayConstants.RECOIL_CONTROL_STANCE_MINIMUM + getStanceRecoilControlModifier();
	}
	
	/**
	*	@brief compute the recoil control based on the player movement
	*/
	protected float computeMovementRecoilControl(){
		return GunplayConstants.RECOIL_CONTROL_MOVEMENT_MINIMUM + getMovementRecoilControlModifier();
	}
	
	/**
	*	@brief Get the recoil control modifier based on the player stance
	*	 @return float - recoil control modifier
	*/
	protected float getStanceRecoilControlModifier(){
		if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.RECOIL_CONTROL_STANCE_ERECT;
		} else if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.RECOIL_CONTROL_STANCE_CROUCHED;
		} else if(m_Player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.RECOIL_CONTROL_STANCE_PRONE;
		} 
		
		return 1;
	}
	
	/**
	*	@brief Get the recoil control modifier based on the player movement
	*	 @return float - recoil control modifier
	*/
	protected float getMovementRecoilControlModifier(){
		switch(m_Player.m_MovementState.m_iMovement){ 
			case 0:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_STANDING;			
			case 1:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_WALKING;
			case 2:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_JOGGING;
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
		//@todo send recoil offset Z to camera (SendRecoilOffsetZ() from 1.13)
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
