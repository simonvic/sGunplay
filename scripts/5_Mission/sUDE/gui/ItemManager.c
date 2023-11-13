modded class ItemManager {
	
	protected Widget m_wTooltipRecoilControlStats;
	
	static const ref array<string> RECOIL_CONTROL_STATS = {
		"s_recoilControlStabilityX"
		"s_recoilControlStabilityY"
		"s_recoilControlMisalignmentX"
		"s_recoilControlMisalignmentY"
		"s_recoilControlKick"
	};
	
	void ItemManager(Widget root) {
		m_wTooltipRecoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_compact.layout", m_TooltipWidget.FindAnyWidget("GridSpacerWidget1"));
	}
	
	override void PrepareTooltip(EntityAI item, int x = 0, int y = 0) {
		super.PrepareTooltip(item, x, y);
		if (IsDragging() || !item) return;
		updateRecoilControlStats(m_wTooltipRecoilControlStats, item);
	}
	
	void updateRecoilControlStats(Widget statWidgetRoot, EntityAI item) {
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
	
	
	protected bool updateWeaponStats(Widget statWidgetRoot, Weapon_Base weapon)  {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlStabilityX",    prop.recoilControlHandsX);
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlStabilityY",    prop.recoilControlHandsY);
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlMisalignmentX", prop.recoilControlMisalignmentX);
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlMisalignmentY", prop.recoilControlMisalignmentY);
		updateRecoilControlStat(statWidgetRoot, "s_recoilControlKick",          prop.recoilControlKick);
		return true;
	}
	
	protected bool updateAttachmentStats(Widget statWidgetRoot, EntityAI item) {
		bool hasStats;
		foreach (string stat : RECOIL_CONTROL_STATS) {
			if (!item.ConfigIsExisting(stat)) {
				continue;
			}
			float value = item.ConfigGetFloat(stat);
			updateRecoilControlStat(statWidgetRoot, stat, value);
			hasStats |= value != 0;
		}
		return hasStats;
	}
	
	static void updateRecoilControlStat(Widget statWidgetRoot, string stat, float value) {
		TextWidget w = TextWidget.Cast(statWidgetRoot.FindAnyWidget(stat));
		if (!w) return;
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		w.SetText(string.Format(format, value * 100));
	}
	
}