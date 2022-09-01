class RecoilControl : Managed {
	
	protected PlayerBase m_player;
	protected float m_control;
	
	static SDebugUI dui;
	static bool debugMonitor = false;
	
	void RecoilControl(PlayerBase player) {
		m_player = player;
		compute();
	}
	
	float get() {
		return m_control;
	}
	
	void compute() {
		m_control = 0;
		dui = SDebugUI.of(ClassName());
		dui.begin();
		if (debugMonitor) {
			dui.window(GetDebugName(), {(256+12)*1,512}, {(256+12)*3,0});
			bool useRecoilControl = true;
			dui.check("useRecoilControl", useRecoilControl);
			if (!useRecoilControl) return;
		}
		
		if (GunplayConstants.RECOIL_CONTROL_USE_STRENGTH) {
			m_control += getModifierStrength();
		}
		
		if (GunplayConstants.RECOIL_CONTROL_USE_PLAYER_INVENTORY_WEIGHT) {
			m_control += getModifierInventoryWeight();
		}
		
		if (GunplayConstants.RECOIL_CONTROL_USE_STANCE) {
			m_control += getModifierStance();
		}
		
		if (GunplayConstants.RECOIL_CONTROL_USE_MOVEMENT) {
			m_control += getModifierMovement();
		}
		
		m_control = Math.Clamp(m_control, GunplayConstants.RECOIL_CONTROL_MINIMUM, GunplayConstants.RECOIL_CONTROL_MAXIMUM);
		
		if (debugMonitor) {
			dui.text("coefficient * arctan(x^3 * steepness)");
			dui.newline();
			dui.slider("Coefficient", GunplayConstants.RECOIL_CONTROL_COEFF, 0.01);
			dui.slider("Steepness", GunplayConstants.RECOIL_CONTROL_STEEPNESS, 0.1, 0, 10);
			array<ref array<float>> line = {};
			for (float x=-1; x<1; x+=0.1) {
				line.Insert({x, GunplayConstants.RECOIL_CONTROL_COEFF * Math.Atan(Math.Pow(x, 3) * GunplayConstants.RECOIL_CONTROL_STEEPNESS)});
				
			}
			float atan = GunplayConstants.RECOIL_CONTROL_COEFF * Math.Atan(Math.Pow(get(), 3) * GunplayConstants.RECOIL_CONTROL_STEEPNESS);
			dui.plot("", {line, {{0,1},{get(), atan}}}, {128, 128}, {0.5, 0.5}, {0.5, 0.5}, 1);
			dui.table({
				{"Recoil control"}
				{"Strength",    ""+getModifierStrength(),        "+"}
				{"Inv weight",  ""+getModifierInventoryWeight(), "+"}
				{"Stance",      ""+getModifierStance(),          "+"}
				{"Movement",    ""+getModifierMovement(),        "="}
				{"--------------------"}
				{"total",       ""+get(),                        ""}
				{"atan",        ""+atan,                         ""}
			}, {256, 128});
		}
		dui.end();
	}
	
	/**
	*	@brief compute the recoil control based on strength
	*	@return float - recoil control modifier
	*/
	protected float getModifierStrength() {
		return m_player.GetSoftSkillsManager().GetSpecialtyLevel() * GunplayConstants.RECOIL_CONTROL_STRENGTH_WEIGHT;
	}
	
	/**
	*	@brief compute the recoil control based on the player inventory weight
	*	@return float - recoil control modifier
	*/
	protected float getModifierInventoryWeight() {
		int w = m_player.GetWeight();
		if (w > 40000) return -0.75;
		if (w > 20000) return -0.50;
		if (w > 10000) return -0.25;
		if (w > 5000)  return  0.25;
		return 0.75;
	}

	/**
	*	@brief Get the recoil control modifier based on the player stance
	*	@return float - recoil control modifier
	*/
	protected float getModifierStance() {
		if (m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)) {
			return GunplayConstants.RECOIL_CONTROL_STANCE_ERECT;
		}
		
		if (m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)) {
			return GunplayConstants.RECOIL_CONTROL_STANCE_CROUCHED;
		}
		
		if (m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)) {
			return GunplayConstants.RECOIL_CONTROL_STANCE_PRONE;
		} 
		
		return 1;
	}
	
	/**
	*	@brief Get the recoil control modifier based on the player movement
	*	@return float - recoil control modifier
	*/
	protected float getModifierMovement() {
		switch (m_player.m_MovementState.m_iMovement) {
			case 0:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_STANDING;			
			case 1:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_WALKING;
			case 2:	return GunplayConstants.RECOIL_CONTROL_MOVEMENT_JOGGING;
		}
		return 0;
	}
}