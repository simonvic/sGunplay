modded class HandsPreview {
	
	protected Widget m_recoilControlStats;
	
	void HandsPreview(LayoutHolder parent) {
		m_recoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_hands.layout", GetMainWidget());
	}
	
	//@todo improve this. Just update it when needed
	override void UpdateInterval() {
		super.UpdateInterval();
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, m_Item)) {
			m_recoilControlStats.Show(false);
		} else {
			m_recoilControlStats.Show(true);
			updateRecoilControlStats(weapon);
		}
	}
	
	void updateRecoilControlStats(Weapon_Base weapon) {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		updateRecoilControlStat("s_recoilControlStabilityX", prop.recoilControlHandsX);
		updateRecoilControlStat("s_recoilControlStabilityY", prop.recoilControlHandsY);
		updateRecoilControlStat("s_recoilControlMisalignmentX", prop.recoilControlMisalignmentX);
		updateRecoilControlStat("s_recoilControlMisalignmentY", prop.recoilControlMisalignmentY);
		updateRecoilControlStat("s_recoilControlKick", prop.recoilControlKick);
	}
	
	protected void updateRecoilControlStat(string stat, float value) {
		TextWidget w = TextWidget.Cast(m_recoilControlStats.FindAnyWidget(stat));
		if (!w) return;
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		w.SetText(string.Format(format, value * 100));
	}
}