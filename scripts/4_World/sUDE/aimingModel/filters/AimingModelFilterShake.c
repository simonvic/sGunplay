class AimingModelFilterShake : AimingModelFilterBase {
	
	protected int m_shakeCount;
	
	override bool isActive() {
		return GetGame().IsClient() && getPlayer().GetShakeLevel() != 0;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		m_shakeCount++;
		//greater than threshold
		if (m_shakeCount > Math.Round(getPlayer().GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 2, 4))) {
			m_shakeCount = 0;
			float weight = getPlayer().GetShakeLevel() / PlayerBase.SHAKE_LEVEL_MAX;
			float modifier = getPlayer().GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0.45, 0.9);
			
			pModel.m_fCamPosOffsetX += 0.0075 * modifier * weight * getPlayer().GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0, 1);
			pModel.m_fCamPosOffsetY += 0.005 * modifier * weight * getPlayer().GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, 0, 1);
		}
		
		
	}
}