modded class DayZPlayerImplementAiming{
	
	protected float m_inertiaXVel[1];
	protected float m_inertiaYVel[1];
	
	static vector m_sCrosshairPosition;
	static bool m_isSCrosshairVisible;
	protected float m_sCrosshairXVel[1];
	protected float m_sCrosshairYVel[1];
	
	protected ref SRaycast m_sCrosshairRay;
	
	void DayZPlayerImplementAiming(DayZPlayerImplement player){
		m_sCrosshairRay = new SRaycast("0 0 0", "0 0 0", 0.05, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);
		//pModel.m_fAimXHandsOffset *= 5;
		//pModel.m_fAimYHandsOffset *= 5;
		if(GunplayConstants.USE_LEGACY_MODE){
			float aimChangeX = getAimChangeDegree()[0];
			float aimChangeY = getAimChangeDegree()[1];
		
			Weapon_Base weapon = Weapon_Base.Cast(m_PlayerPb.GetItemInHands());
			float inertiaMultiplier = computeDragMultiplier(weapon);
			
			aimChangeX *= inertiaMultiplier ;
			aimChangeY *= inertiaMultiplier ;

			pModel.m_fAimXHandsOffset = Math.SmoothCD(pModel.m_fAimXHandsOffset, pModel.m_fAimXHandsOffset - aimChangeX, m_inertiaXVel, GunplayConstants.INERTIA_SMOOTHNESS, 1000, pDt);
			pModel.m_fAimYHandsOffset = Math.SmoothCD(pModel.m_fAimYHandsOffset, pModel.m_fAimYHandsOffset - aimChangeY, m_inertiaYVel, GunplayConstants.INERTIA_SMOOTHNESS, 1000, pDt);
			
			updateSCrosshair(weapon, pDt);
		}
		
		
		DayZPlayerCameraIronsights.m_weaponDeadzoneX = pModel.m_fAimXHandsOffset ;
		DayZPlayerCameraIronsights.m_weaponDeadzoneY = pModel.m_fAimYHandsOffset ;
		
		return result;
	}
	
	protected void updateSCrosshair(Weapon_Base weapon, float pDt){
		if(!GetGame().GetMission() || m_PlayerDpi.IsInIronsights() || m_PlayerDpi.IsInOptics()){
			m_isSCrosshairVisible = false;
		}else{
			m_isSCrosshairVisible = true;
			vector muzzlePosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));
			vector barrelPosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));
			vector target = barrelPosition + (vector.Direction(barrelPosition, muzzlePosition ) * GunplayConstants.CROSSHAIR_PRECISION);
			
			m_sCrosshairRay.setBegPos(muzzlePosition);
			m_sCrosshairRay.setEndPos(target);
			m_sCrosshairRay.launch();
			
			vector pos = GetGame().GetScreenPosRelative(m_sCrosshairRay.getContactPos());
			
			m_sCrosshairPosition[0] = Math.SmoothCD(m_sCrosshairPosition[0], pos[0], m_sCrosshairXVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
			m_sCrosshairPosition[1] = Math.SmoothCD(m_sCrosshairPosition[1], pos[1], m_sCrosshairYVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
			
		}
	}
	
	protected vector getAimChangeDegree(){
		vector aimChange = "0 0 0";
		aimChange[0] = m_PlayerDpi.GetInputController().GetAimChange()[0] * Math.RAD2DEG;
		aimChange[1] = m_PlayerDpi.GetInputController().GetAimChange()[1] * Math.RAD2DEG;
		return aimChange;
	}
	
	protected float computeDragMultiplier(Weapon_Base weapon){
		float inertiaMultiplier = GunplayConstants.INERTIA_MULTIPLIER_BASE;
		if(weapon) inertiaMultiplier = weapon.GetWeight() / 1000;
		if(!m_PlayerDpi.IsInOptics() && !m_PlayerDpi.IsInIronsights()){
			inertiaMultiplier *= GunplayConstants.INERTIA_MULTIPLIER_HIPFIRE;
		}
		
		inertiaMultiplier *= getStanceInertiaMultiplier();
		
		
		return inertiaMultiplier;
	}
	
	
	protected float getStanceInertiaMultiplier(){
		if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.INERTIA_MULTIPLIER_ERECT;
		} else if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.INERTIA_MULTIPLIER_CROUCHED;
		} else if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.INERTIA_MULTIPLIER_PRONE;
		} 
		
		return 1;
	}
	
	
	
}