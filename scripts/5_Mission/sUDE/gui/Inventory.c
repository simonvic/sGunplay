modded class Inventory {

	protected Widget m_rootGunplayStats;
	protected Widget m_meterRecoilControl;
	protected Widget m_meterWeight;

	void Inventory(LayoutHolder parent) {
		m_rootGunplayStats = g_Game.GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/gunplay_stats.layout", GetMainWidget().FindAnyWidget("InventoryFrameWidget"));
		m_meterRecoilControl = m_rootGunplayStats.FindAnyWidget("recoil_control_indicator");
		m_meterWeight = m_rootGunplayStats.FindAnyWidget("weight_indicator");
		if (!GunplayConstants.SHOW_PLAYER_STATS) {
			m_rootGunplayStats.Show(false);
		}
	}

	override void Update(float timeslice) {
		super.Update(timeslice);
		if (!GunplayConstants.SHOW_PLAYER_STATS) return;
		updateStatMeters();
	}

	protected void updateStatMeters() {
		PlayerBase pb = PlayerBase.Cast(g_Game.GetPlayer());
		RecoilControl recoilControl = pb.getRecoilControl();
		recoilControl.compute(); // FIXME: am i dumb? probably yes
		setMeterValue(m_meterRecoilControl, recoilControl.get(), -1, 1);
		setMeterValue(m_meterWeight, pb.GetWeightEx(), GunplayConstants.INVENTORY_WEIGHT_GRAMS_LIGHT, GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED);
	}

	protected void setMeterValue(Widget meter, float value, float min = 0, float max = 1, bool clamp = true) {
		value = SMath.mapTo(value, min, max, -0.5, 0.5);
		if (clamp) value = Math.Clamp(value, -0.5, 0.5);
		meter.SetPos(value, -0.75);
	}
}
