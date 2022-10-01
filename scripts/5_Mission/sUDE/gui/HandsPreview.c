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
		updateRecoilControlStat("stabilityX", prop.recoilControlHandsX);
		updateRecoilControlStat("stabilityY", prop.recoilControlHandsY);
		updateRecoilControlStat("misalignX", prop.recoilControlMisalignmentX);
		updateRecoilControlStat("misalignY", prop.recoilControlMisalignmentY);
		updateRecoilControlStat("kick", prop.recoilControlKick);
	}
	
	protected void updateRecoilControlStat(string stat, float value) {
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		TextWidget.Cast(m_recoilControlStats.FindAnyWidget(stat)).SetText(string.Format(format, value * 100));
	}
}