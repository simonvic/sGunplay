modded class DayZPlayerCameraBase{
	
	protected float m_enteringTransitionTime = DayZPlayerCameras.DEFAULT_UNREGISTERED_TIME;
	
	override void OnActivate(DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera, pPrevCameraResult);
		if(DayZPlayerCameraBase.Cast(pPrevCamera)){
			m_enteringTransitionTime = DayZPlayerCameras.GetTransitionTime(DayZPlayerCameraBase.Cast(pPrevCamera).getRegisteredCameraID(), getRegisteredCameraID());
		}
	}
	
	int getRegisteredCameraID(){
		return -1;
	}
	
}

modded class DayZPlayerCamera1stPerson{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_1ST;
	}
}

modded class DayZPlayerCamera3rdPersonErc{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_ERC;
	}
}

modded class DayZPlayerCamera3rdPersonErcSpr{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_ERC_SPR;
	}
}

modded class DayZPlayerCamera3rdPersonErcRaised{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_ERC_RAISED;
	}
}

modded class DayZPlayerCamera3rdPersonCrouch{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_CRO;
	}
}

modded class DayZPlayerCamera3rdPersonCrouchRaised{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_CRO_RAISED;
	}
}

modded class DayZPlayerCamera3rdPersonProne{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_PRO;
	}
}

modded class DayZPlayerCamera3rdPersonProneRaised{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_PRO_RAISED;
	}
}

modded class DayZPlayerCamera3rdPersonErcRaisedMelee{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_ERC_RAISED_MELEE;
	}
}

modded class DayZPlayerCamera1stPersonUnconscious{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_1ST_UNCONSCIOUS;
	}
}

modded class DayZPlayerCamera3rdPersonJump{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_JUMP;
	}
}

modded class DayZPlayerCamera3rdPersonClimb{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_CLIMB;
	}
}

modded class DayZPlayerCamera1stPersonVehicle{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
	}
}

modded class DayZPlayerCamera3rdPersonVehicle{
	override int getRegisteredCameraID(){
		return DayZPlayerCameras.DAYZCAMERA_3RD_VEHICLE;
	}
}
