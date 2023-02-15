class AimingModelFilterShake : AimingModelFilterBase {
	
	static const float SECONDS_BETWEEN_SHAKES = Math.PI2;
	static const float SECONDS_SHAKE_LENGTH = Math.PI_HALF;
	
	protected float m_shakeTimer;
	
	override bool isActive() {
		return GetGame().IsClient();
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		if (getPlayer().GetShakeLevel() != 0) {
			m_shakeTimer += pDt;
			if (m_shakeTimer >= SECONDS_BETWEEN_SHAKES) {
				if (m_shakeTimer < SECONDS_BETWEEN_SHAKES + SECONDS_SHAKE_LENGTH) {
					onShake(pDt, pModel);
				} else {
					m_shakeTimer = 0;
				}
			}
		}
		onCamShake(pDt, pModel);
	}
	
	protected void onShake(float pDt, SDayZPlayerAimingModel pModel) {
		float noise = getPlayer().GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSAimingModel, -1, 1);
		pModel.m_fCamPosOffsetX += noise * 0.00050;
		pModel.m_fCamPosOffsetY += noise * 0.00025;
	}
	
	protected void onCamShake(float pDt, SDayZPlayerAimingModel pModel) {
		vector camShake = getAimingModel().getCamShake();
		pModel.m_fAimXCamOffset += camShake[0];
		pModel.m_fAimYCamOffset += camShake[1];
	}
	
	
}