modded class IngameHud {

	protected ref SCrosshair m_sCrosshair;
	
	void IngameHud() {
		m_sCrosshair = new SCrosshair();
	}
	
	override void Update(float timeslice) {
		super.Update(timeslice);
		m_sCrosshair.onUpdate(timeslice);
	}
}