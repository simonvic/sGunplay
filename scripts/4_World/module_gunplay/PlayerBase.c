modded class PlayerBase {
	protected ref RecoilControl m_recoilControl;
	
	void PlayerBase() {
		m_recoilControl = new RecoilControl(this);
	}
	
	RecoilControl getRecoilControl() {
		return m_recoilControl;
	}
}