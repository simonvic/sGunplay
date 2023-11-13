modded class InspectMenuNew {
	
	protected Widget m_wRecoilControlStats;
	
	static const ref array<string> RECOIL_CONTROL_STATS = {
		"s_recoilControlStabilityX"
		"s_recoilControlStabilityY"
		"s_recoilControlMisalignmentX"
		"s_recoilControlMisalignmentY"
		"s_recoilControlKick"
	};
	
	override Widget Init() {
		super.Init();
		m_wRecoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_extended.layout", layoutRoot.FindAnyWidget("ItemFrameWidgetPanel"));
		return layoutRoot;
	}
	
	override void SetItem(EntityAI item) {
		super.SetItem(item);
		updateRecoilControlStats(m_wRecoilControlStats, item);
	}
	
	protected void updateRecoilControlStats(Widget statWidgetRoot, EntityAI item) {
		if (!statWidgetRoot) return;
		if (!item) {
			statWidgetRoot.Show(false);
			return;
		}
		bool showStats;
		Weapon_Base weapon;
		if (Class.CastTo(weapon, item)) {
			showStats = updateWeaponStats(statWidgetRoot, weapon);
		} else {
			showStats = updateAttachmentStats(statWidgetRoot, item);
		}
		statWidgetRoot.Show(showStats);
	}
	
	protected bool updateAttachmentStats(Widget statWidgetRoot, EntityAI item) {
		bool hasStats;
		foreach (string stat : RECOIL_CONTROL_STATS) {
			if (!item.ConfigIsExisting(stat)) {
				continue;
			}
			float value = item.ConfigGetFloat(stat);
			updateRecoilControlStat(statWidgetRoot, stat, value, 0);
			hasStats |= value != 0;
		}
		return hasStats;
	}
	
	protected bool updateWeaponStats(Widget statWidgetRoot, Weapon_Base weapon)  {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlStabilityX",    prop.recoilControlHandsX,        weapon.ConfigGetFloat("s_recoilControlStabilityX"));
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlStabilityY",    prop.recoilControlHandsY,        weapon.ConfigGetFloat("s_recoilControlStabilityY"));
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlMisalignmentX", prop.recoilControlMisalignmentX, weapon.ConfigGetFloat("s_recoilControlMisalignmentX"));
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlMisalignmentY", prop.recoilControlMisalignmentY, weapon.ConfigGetFloat("s_recoilControlMisalignmentY"));
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlKick",          prop.recoilControlKick,          weapon.ConfigGetFloat("s_recoilControlKick"));
		return true;
	}
	
	static void updateRecoilControlStat(Widget statWidgetRoot, string stat, float value, float integratedValue) {
		SliderWidget w = SliderWidget.Cast(statWidgetRoot.FindAnyWidget(stat));
		if (!w) return;
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		w.SetCurrent(value);
		TextWidget.Cast(w.FindAnyWidget(stat + "_value")).SetText(string.Format(format, value * 100));
		SliderWidget.Cast(w.FindAnyWidget(stat + "_integrated")).SetCurrent(integratedValue);
	}
	
}