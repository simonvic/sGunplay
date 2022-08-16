class AimingModelFilterWallPush : AimingModelFilterBase {
	
	override bool isActive() {
		return GetGame().IsClient();
	}
	
	protected ref SRaycast m_ray; //@todo use RaycastBullet
	protected float m_vel[1];
	protected float m_currentOffset;
	
	void AimingModelFilterWallPush(DayZPlayerImplementAiming aimingModel) {
		m_ray = new SRaycast(vector.Zero, vector.Zero, 0.1, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		vector barrel, muzzle, target;
		DayZPlayerImplementAiming.getWeaponComponentsPositionWS(getWeapon(),barrel, muzzle, target, 5);
		
		m_ray.from(barrel).to(target).ignore(getWeapon(), getPlayer()).launch();
		float distance = vector.Distance(muzzle, m_ray.getContactPosition());
		
		float targetOffset;
		if (distance < 0.5) {
			targetOffset = (0.05 - SMath.mapTo(distance, 0, 0.5, 0, 0.05)) / Math.Max(getWeapon().getWeaponLength(), 0.01);
		}
		
		m_currentOffset = Math.SmoothCD(
			m_currentOffset,
			targetOffset,
			m_vel, 0.15, 1000, pDt);
		
		pModel.m_fCamPosOffsetZ += m_currentOffset;

	}
	
}