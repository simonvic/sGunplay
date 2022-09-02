class AimingModelFilterShake : AimingModelFilterBase {
	
	protected int m_shakeCount;
	
	override bool isActive() {
		return GetGame().IsClient();
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		if (getPlayer().GetShakeLevel() != 0) {
			RandomGeneratorSyncManager rand = getPlayer().GetRandomGeneratorSyncManager();
			m_shakeCount++;
			//greater than threshold
			if (m_shakeCount > Math.Round(rand.GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 2, 4))) {
				m_shakeCount = 0;
				float weight = getPlayer().GetShakeLevel() / PlayerBase.SHAKE_LEVEL_MAX;
				float modifier = rand.GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0.45, 0.9);
				
				pModel.m_fCamPosOffsetX += 0.0075 * modifier * weight * rand.GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0, 1);
				pModel.m_fCamPosOffsetY += 0.005 * modifier * weight * rand.GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0, 1);
			}
		}
		
		// :facepalm:
		vector camShake = getAimingModel().getCamShake();
		pModel.m_fAimXCamOffset += camShake[0];
		pModel.m_fAimYCamOffset += camShake[1];
		
		
	}
}