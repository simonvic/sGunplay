modded class PlayerBase {
	protected ref RecoilControl m_recoilControl;
	
	void PlayerBase() {
		m_recoilControl = new RecoilControl(this);
	}
	
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
	
	RecoilControl getRecoilControl() {
		return m_recoilControl;
	}
}