modded class Inventory {
	
	protected Widget m_rootGunplayStats;
	protected Widget m_meterRecoilControl;
	protected Widget m_meterWeight;
	
	void Inventory(LayoutHolder parent) {
		m_rootGunplayStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/gunplay_stats.layout", GetMainWidget().FindAnyWidget("InventoryFrameWidget"));
		m_meterRecoilControl = m_rootGunplayStats.FindAnyWidget("recoil_control_indicator");
		m_meterWeight = m_rootGunplayStats.FindAnyWidget("weight_indicator");
	}
	
	override void Update(float timeslice) {
		super.Update(timeslice);
		updateStatMeters();
	}
	
	protected void updateStatMeters() {
		PlayerBase pb = PlayerBase.Cast(GetGame().GetPlayer());
		RecoilControl recoilControl = pb.getRecoilControl();
		recoilControl.compute(); //@fixme am i dumb? probably yes
		setMeterValue(m_meterRecoilControl, recoilControl.get(), -1, 1);
		setMeterValue(m_SpecializationIcon, pb.GetSoftSkillsManager().GetSpecialtyLevel(), -1, 1);
		setMeterValue(m_meterWeight, pb.GetWeight(), 0, 40000);
	}
	
	protected void setMeterValue(Widget meter, float value, float min = 0, float max = 1, bool clamp = true) {
		value = SMath.mapTo(value, min, max, -0.5, 0.5);
		if (clamp) value = Math.Clamp(value, -0.5, 0.5);
		meter.SetPos(value, -0.75);
	}
}