modded class InspectMenuNew {
	
	protected Widget m_wRecoilControlStats;
	
	override Widget Init() {
		super.Init();
		m_wRecoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_inspect.layout", layoutRoot.FindAnyWidget("ItemFrameWidgetPanel"));
		return layoutRoot;
	}
	
	override void SetItem(EntityAI item) {
		super.SetItem(item);
		if (!m_wRecoilControlStats) return;
		if (!item) {
			m_wRecoilControlStats.Show(false);
			return;
		}
		updateRecoilControlStats(item);
	}
	
	protected void updateRecoilControlStats(EntityAI item) {
		Weapon_Base weapon;
		if (Class.CastTo(weapon, item)) {
			updateWeaponStats(weapon);	
			m_wRecoilControlStats.Show(true);
		}  else {
			bool hasStats;
			foreach (string stat : RecoilControl.STAT_NAMES) {
				float value;
				if (item.ConfigIsExisting(stat)) {
					value = item.ConfigGetFloat(stat);
				}
				updateRecoilControlStat(m_wRecoilControlStats.FindAnyWidget(stat), value);
				hasStats |= value != 0;
			}
			m_wRecoilControlStats.Show(hasStats);
		}
	}
	
	protected void updateWeaponStats(Weapon_Base weapon) {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		updateWeaponStat("s_recoilControlStabilityX",    prop.recoilControlHandsX,        weapon.ConfigGetFloat("s_recoilControlStabilityX"));
		updateWeaponStat("s_recoilControlStabilityY",    prop.recoilControlHandsY,        weapon.ConfigGetFloat("s_recoilControlStabilityY"));
		updateWeaponStat("s_recoilControlMisalignmentX", prop.recoilControlMisalignmentX, weapon.ConfigGetFloat("s_recoilControlMisalignmentX"));
		updateWeaponStat("s_recoilControlMisalignmentY", prop.recoilControlMisalignmentY, weapon.ConfigGetFloat("s_recoilControlMisalignmentY"));
		updateWeaponStat("s_recoilControlKick",          prop.recoilControlKick,          weapon.ConfigGetFloat("s_recoilControlKick"));
	}
	
	protected void updateWeaponStat(string stat, float value, float integratedValue) {
		Widget w = m_wRecoilControlStats.FindAnyWidget(stat);
		updateRecoilControlStat(w, value);
		SliderWidget.Cast(w.FindAnyWidget(stat + "_integrated")).SetCurrent(integratedValue);
	}
	
	protected void updateRecoilControlStat(Widget w, float value) {
		if (!w) return;
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		SliderWidget.Cast(w).SetCurrent(value);
		TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_value")).SetText(string.Format(format, value * 100));
	}
	
}