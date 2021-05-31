class AimingModelFilterWallPush : AimingModelFilterBase {
	
	protected ref SRaycast m_ray; //@todo use RaycastBullet
	
	void AimingModelFilterWallPush(DayZPlayerImplementAiming aimingModel){
		m_ray = new SRaycast(vector.Zero, vector.Zero, 0.1, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		vector barrel, muzzle, target;
		DayZPlayerImplementAiming.getWeaponComponentsPositionWS(getWeapon(),barrel, muzzle, target, 5);
		
		m_ray.ignore(getWeapon(), getPlayer());
		float distance = vector.Distance(muzzle, m_ray.from(barrel).to(target).launch().getContactPosition());
		
		/*
		SDebug.spawnDebugDot(barrel, 0.05, 0.1);
		SDebug.spawnDebugDot(muzzle, 0.05, 0.1);
		SDebug.spawnDebugDot(target, 0.05, 0.1);
		SDebug.spawnDebugDot(m_ray.getContactPosition(), 0.05, 0.1);
		SDebug.drawLine(muzzle, m_ray.getContactPosition(), true);
		*/
		
		if(distance < 0.5){
			pModel.m_fCamPosOffsetZ += 0.05 - SMath.mapTo(distance, 0, 0.5, 0, 0.05);
		}

	}
	
}