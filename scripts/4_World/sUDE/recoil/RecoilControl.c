class RecoilControl : Managed {
	
	protected PlayerBase m_player;
	protected float m_control;
	
	void RecoilControl(PlayerBase player) {
		m_player = player;
		compute();
	}
	
	float get() {
		return m_control;
	}
	
	void compute() {
		m_control  = 0;
		m_control += getModifierStrength();
		m_control += getModifierInventoryWeight();
		m_control += getModifierStance();
		m_control += getModifierMovement();
		m_control  = Math.Clamp(m_control, GunplayConstants.RECOIL_CONTROL_MINIMUM, GunplayConstants.RECOIL_CONTROL_MAXIMUM);
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
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED) return GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT_OVERLOADED;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_HEAVY)      return GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT_HEAVY;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_MEDIUM)     return GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT_MEDIUM;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_LIGHT)      return GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT_LIGHT;
		return GunplayConstants.RECOIL_CONTROL_INVENTORY_WEIGHT_VERYLIGHT;
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