modded class InspectMenuNew {
	
	override void SetItem(EntityAI item) {
		super.SetItem(item);
		Weapon_Base weapon;
		if (item && Class.CastTo(weapon, item)) {
			updateRecoilControlStats(weapon);
		}
	}

	protected void updateRecoilControlStats(Weapon_Base weapon) {
		PropertyModifiers prop = weapon.GetPropertyModifierObject();
		Widget stats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_inspect.layout", layoutRoot.FindAnyWidget("ItemFrameWidgetPanel"));
		updateRecoilControlStat(stats.FindAnyWidget("stabilityX"), prop.recoilControlHandsX);
		updateRecoilControlStat(stats.FindAnyWidget("stabilityY"), prop.recoilControlHandsY);
		updateRecoilControlStat(stats.FindAnyWidget("misalignX"), prop.recoilControlMisalignmentX);
		updateRecoilControlStat(stats.FindAnyWidget("misalignY"), prop.recoilControlMisalignmentY);
		updateRecoilControlStat(stats.FindAnyWidget("kick"), prop.recoilControlKick);
	}
	
	protected void updateRecoilControlStat(Widget w, float value) {
		string format = "%1%%";
		if (value >= 0) format = "+" + format;
		SliderWidget.Cast(w).SetCurrent(value);
		TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_value")).SetText(string.Format(format, value * 100));
	}
	
}