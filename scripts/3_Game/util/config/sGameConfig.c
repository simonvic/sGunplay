modded class SGameConfig{
	private static ref SGameConfigGunplay m_gunplay = new SGameConfigGunplay();
	
	static SGameConfigGunplay gunplay(){
		return m_gunplay;
	}
}