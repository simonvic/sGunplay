modded class PlayerBase {
	protected ref RecoilControl m_recoilControl;
	
	void PlayerBase() {
		m_recoilControl = new RecoilControl(this);
	}
	
#ifdef DAYZ_1_20
	override void UpdateMovementInertia() {
		super.UpdateMovementInertia();
		HumanCommandMove hcm = GetCommand_Move();
		if (!hcm) return;
		float weight = GetWeight();
		hcm.SetRunSprintFilterModifier(SMath.mapClamp(weight, 0, 40000,
			GunplayConstants.PLAYER_INERTIA_SPRINT_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_SPRINT_TIMING[1]));
		
		hcm.SetTurnSpanModifier(SMath.mapClamp(weight, 0, 40000,
			GunplayConstants.PLAYER_INERTIA_TURNING_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_TURNING_TIMING[1]));
		
		hcm.SetTurnSpanSprintModifier(SMath.mapClamp(weight, 0, 40000,
			GunplayConstants.PLAYER_INERTIA_SPRINT_TURNING_TIMING[0],
			GunplayConstants.PLAYER_INERTIA_SPRINT_TURNING_TIMING[1]));
		
		hcm.SetDirectionSprintFilterModifier(1);
	}
#else
	override void Init() {
		super.Init();
		RegisterNetSyncVariableFloat("m_Weight");
	}
	
	override void UpdateWeight(WeightUpdateType updateType = WeightUpdateType.FULL, float weightAdjustment = 0) {
		if (GetGame().IsClient()) return;
		super.UpdateWeight(updateType, weightAdjustment);
		
		
		/* mod friendly version
		if (GetGame().IsClient()) {
			float temp = m_Weight;
			super.UpdateWeight(updateType, weightAdjustment);
			m_Weight = temp;
		} else {
			super.UpdateWeight(updateType, weightAdjustment);
		}
		*/
	}
#endif
	
	RecoilControl getRecoilControl() {
		return m_recoilControl;
	}
}