class AimingModelFilterKuru : AimingModelFilterBase {
	
	override bool isActive() {
		return getAimingModel().getKuruShake() != null;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		KuruShake kuru = getAimingModel().getKuruShake();
		if (!kuru) return;
		float kuruOffsetX;
		float kuruOffsetY;
		kuru.Update(pDt, kuruOffsetX, kuruOffsetY);
		pModel.m_fAimXHandsOffset += kuruOffsetX * 0.1;
		pModel.m_fAimYHandsOffset += kuruOffsetY * 0.1;
	}
}