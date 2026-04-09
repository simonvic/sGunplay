modded class IngameHud {

	protected ref SCrosshair m_sCrosshair;

	void IngameHud() {
		m_sCrosshair = new SCrosshair();
	}

	override void Update(float timeslice) {
		super.Update(timeslice);
		m_sCrosshair.onUpdate(timeslice);
	}

	override void setSCrosshairColor(SColor color) {
		m_sCrosshair.setColor(color);
	}

	override void setSCrosshairStyle(int styleIndex) {
		m_sCrosshair.setStyle(styleIndex);
	}

}
