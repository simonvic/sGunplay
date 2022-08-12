class AimingModelFilterKuru : AimingModelFilterBase {
	
	override bool isActive(){
		return getAimingModel().getKuruShake() != null;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		KuruShake kuru = getAimingModel().getKuruShake();
		if(!kuru) return;
		float kuruOffsetX;
		float kuruOffsetY;
		kuru.Update(pDt, kuruOffsetX, kuruOffsetY);
		pModel.m_fAimXHandsOffset += kuruOffsetX;
		pModel.m_fAimYHandsOffset += kuruOffsetY;
		//pModel.m_fAimXCamOffset   -= kuruOffsetX;
		//pModel.m_fAimYCamOffset   -= kuruOffsetY;
		pModel.m_fAimXMouseShift  -= kuruOffsetX / 10;
		pModel.m_fAimYMouseShift  += kuruOffsetY / 10;
	}
}