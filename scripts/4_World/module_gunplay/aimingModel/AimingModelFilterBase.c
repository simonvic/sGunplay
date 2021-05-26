class AimingModelFilterBase {
	
	protected PlayerBase m_player;
	protected Weapon_Base m_weapon;
	
	void AimingModelFilterBase(PlayerBase player, Weapon_Base weapon){
		m_player = player;
		m_weapon = weapon;
	}
	
	void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex);
	
	bool isActive(){
		return false;
	}
	
}