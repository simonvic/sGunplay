class AimingModelFilterWallPush : AimingModelFilterBase {
	
	protected ref SRaycast m_ray; //@todo use RaycastBullet
	
	void AimingModelFilterWallPush(DayZPlayerImplementAiming aimingModel){
		m_ray = new SRaycast(vector.Zero, vector.Zero, 0.1, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		vector barrel, muzzle, target;
		DayZPlayerImplementAiming.getWeaponComponentsPositionWS(getWeapon(),barrel, muzzle, target, 5);
		m_ray.setBegPos(muzzle);
		m_ray.setEndPos(target);
		m_ray.launch();
		
		float distance = vector.Distance(muzzle, m_ray.getContactPos());		
		
		if(distance < 0.5){
			pModel.m_fCamPosOffsetZ += 0.05 - SMath.mapTo(distance, 0, 0.5, 0, 0.05);
		}

	}
	
}