modded class PlayerBase {
	protected ref RecoilControl m_recoilControl;
	
	void PlayerBase() {
		m_recoilControl = new RecoilControl(this);
	}
	
	override void OnCommandHandlerTick(float delta_time, int pCurrentCommandID) {
		super.OnCommandHandlerTick(delta_time, pCurrentCommandID);
		//if (CfgGameplayHandler.GetAllowStaminaAffectInertia())
		//	UpdateMovementInertia();
		
		if (CfgGameplayHandler.GetAllowStaminaAffectInertia() && GunplayConstants.PLAYER_INERTIA_AFFECTED_BY_WEIGHT) {
			updateMovementInertiaByWeight();
		}
	}
	
	void updateMovementInertiaByWeight() {
		HumanCommandMove hcm = GetCommand_Move();
		if (!hcm) return;
		float weight = GetWeight();
		hcm.SetRunSprintFilterModifier(SMath.mapClamp(weight,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT[0],
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT[1]));
		
		hcm.SetTurnSpanModifier(SMath.mapClamp(weight,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TIMING_TURNING[0],
			GunplayConstants.PLAYER_INERTIA_TIMING_TURNING[1]));
		
		hcm.SetTurnSpanSprintModifier(SMath.mapClamp(weight, 
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT_TURNING[0],
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT_TURNING[1]));
		
		hcm.SetDirectionFilterModifier(SMath.mapClamp(weight, 
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TIMING_DIRECTION[0],
			GunplayConstants.PLAYER_INERTIA_TIMING_DIRECTION[1]));
		
		hcm.SetDirectionSprintFilterModifier(SMath.mapClamp(weight,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT_DIRECTION[0],
			GunplayConstants.PLAYER_INERTIA_TIMING_SPRINT_DIRECTION[1]));
	}
	
	RecoilControl getRecoilControl() {
		return m_recoilControl;
	}
}