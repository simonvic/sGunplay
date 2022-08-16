modded class DayZPlayerImplement {

	protected bool m_isInspectingWeapon;
	protected UAInput m_inputWeaponInspect;
	
	void DayZPlayerImplement() {
		m_inputWeaponInspect = GetUApi().GetInputByName("SUA_ADSWeaponInspect");
	}
	
	override void HandleADS() {
		super.HandleADS();
		
		if (!m_inputWeaponInspect) {
			SLog.e("input is null","DayZPlayerImplement::HandleADS");
			return;
		}
		
		if (m_inputWeaponInspect.LocalPress() || m_inputWeaponInspect.LocalHold()) {
			m_isInspectingWeapon = GetInputController().CameraIsFreeLook();
		}
		
		if (m_inputWeaponInspect.LocalRelease()) {
			m_isInspectingWeapon = false;
		}

	}
	
	bool isInspectingWeapon() {
		return m_isInspectingWeapon;
	}
	
	
}