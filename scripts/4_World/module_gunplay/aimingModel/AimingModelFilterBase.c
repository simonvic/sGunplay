class AimingModelFilterBase {
	
	protected DayZPlayerImplementAiming m_aimingModel
	
	void AimingModelFilterBase(DayZPlayerImplementAiming aimingModel){
		m_aimingModel = aimingModel;
	}
	
	void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex);
	
	bool isActive(){
		return true;
	}
	
	protected DayZPlayerImplementAiming getAimingModel(){
		return m_aimingModel;
	}
	
	protected PlayerBase getPlayer(){
		return m_aimingModel.getPlayer();
	}
	
	protected Weapon_Base getWeapon(){
		return m_aimingModel.getWeapon();
	}
	
}