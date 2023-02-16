modded class PlayerBase {
	protected ref RecoilControl m_recoilControl;
	
	void PlayerBase() {
		m_recoilControl = new RecoilControl(this);
	}
	
	override void UpdateMovementInertia() {
		super.UpdateMovementInertia();
		if (!GunplayConstants.PLAYER_INERTIA_ENABLE) return;
		HumanCommandMove hcm = GetCommand_Move();
		if (!hcm) return;
		float weight = GetWeight();
		hcm.SetRunSprintFilterModifier(SMath.mapClamp(weight,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_SPRINT_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_SPRINT_TIMING[1]));
		
		hcm.SetTurnSpanModifier(SMath.mapClamp(weight,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_TURNING_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_TURNING_TIMING[1]));
		
		hcm.SetTurnSpanSprintModifier(SMath.mapClamp(weight, 
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_VERYLIGHT,
			GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED,
			GunplayConstants.PLAYER_INERTIA_SPRINT_TURNING_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_SPRINT_TURNING_TIMING[1]));
		
		hcm.SetDirectionSprintFilterModifier(1);
	}
	
	RecoilControl getRecoilControl() {
		return m_recoilControl;
	}
}