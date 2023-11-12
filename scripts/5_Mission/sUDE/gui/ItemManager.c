modded class ItemManager {
	
	protected Widget m_wTooltipRecoilControlStats;
	
	void ItemManager(Widget root) {
		m_wTooltipRecoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_tooltip.layout", m_TooltipWidget);		
		m_wTooltipRecoilControlStats.Show(false);
	}
	
	override void PrepareTooltip(EntityAI item, int x = 0, int y = 0) {
		super.PrepareTooltip(item, x, y);
		if (IsDragging() || !item) return;
		updateRecoilControlStats(item);
	}
	
	protected void updateRecoilControlStats(EntityAI item) {
		Weapon_Base weapon;
		if (Class.CastTo(weapon, item)) {
			updateWeaponStats(weapon);
			m_wTooltipRecoilControlStats.Show(true);
		} else {
			bool hasStats;
			foreach (string stat : RecoilControl.STAT_NAMES) {
				float value;
				if (item.ConfigIsExisting(stat)) {
					value = item.ConfigGetFloat(stat);
				}
				updateRecoilControlStat(stat, value);
				hasStats |= value != 0;
			}
			m_wTooltipRecoilControlStats.Show(hasStats);
		}
	}
	
	protected void updateWeaponStats(Weapon_Base weapon)  {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		updateRecoilControlStat("s_recoilControlStabilityX", prop.recoilControlHandsX);
		updateRecoilControlStat("s_recoilControlStabilityY", prop.recoilControlHandsY);
		updateRecoilControlStat("s_recoilControlMisalignmentX", prop.recoilControlMisalignmentX);
		updateRecoilControlStat("s_recoilControlMisalignmentY", prop.recoilControlMisalignmentY);
		updateRecoilControlStat("s_recoilControlKick", prop.recoilControlKick);
	}
	
	protected void updateRecoilControlStat(string stat, float value) {
		TextWidget w = TextWidget.Cast(m_wTooltipRecoilControlStats.FindAnyWidget(stat));
		if (!w) return;
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		w.SetText(string.Format(format, value * 100));
	}
	
}