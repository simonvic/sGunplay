class AimingModelFilterClamps : AimingModelFilterBase {
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {		
		pModel.m_fAimXHandsOffset = Math.Clamp(pModel.m_fAimXHandsOffset, -160, 160);
		pModel.m_fAimYHandsOffset = Math.Clamp(pModel.m_fAimYHandsOffset, -85 - pModel.m_fCurrentAimY, 85 - pModel.m_fCurrentAimY);
	}
	
}