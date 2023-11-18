modded class HandsPreview {
	
	protected Widget m_wRecoilControlStats;
	
	void HandsPreview(LayoutHolder parent) {
		m_wRecoilControlStats = GetGame().GetWorkspace().CreateWidgets("MyMODS/sGunplay/GUI/layouts/recoil_control_compact.layout", GetMainWidget());
	}
	
	override void UpdateInterval() {
		super.UpdateInterval();
		// TODO(perf): improve this. Just update it when needed
		ItemManager.GetInstance().updateRecoilControlStats(m_wRecoilControlStats, m_Item);
	}
}