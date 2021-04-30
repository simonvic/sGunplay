modded class SConfig{
	private static ref SConfigGunplay m_gunplay = new SConfigGunplay();
	
	static SConfigGunplay gunplay(){
		return m_gunplay;
	}
}