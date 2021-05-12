class SDayZPlayerCameraBase : DayZPlayerCamera {

	void DayZPlayerCameraBase(DayZPlayer pPlayer, HumanInputController pInput){
	}
	
	override void OnActivate (DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult){
		super.OnActivate(pPrevCamera, pPrevCameraResult);
	}

	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.OnUpdate(pDt, pOutResult);
		int boneIdx = m_pPlayer.GetBoneIndexByName("Head");
		if(boneIdx == -1) {
			m_pPlayer.GetBoneIndexByName("Head");
			SLog.c("Bone index not found");
		}
		pOutResult.m_iDirectBone = boneIdx;
		pOutResult.m_iDirectBoneMode = 1;
	
		pOutResult.m_fFovAbsolute = g_Game.GetUserFOV();
		pOutResult.m_fFovMultiplier = 1.0;
		
		pOutResult.m_bUpdateWhenBlendOut	= false;
		pOutResult.m_fPositionModelSpace	= 0.0;
		
		pOutResult.m_fDistance 				= 0;
		pOutResult.m_fUseHeading 			= 0.0;
		pOutResult.m_fInsideCamera 			= 1.0;
		pOutResult.m_fShootFromCamera		= 0.0;
		pOutResult.m_fIgnoreParentRoll		= 0.0;
		
		pOutResult.m_fNearPlane = 0.04; //0.07 default
		
		HumanCommandWeapons hcw = m_pPlayer.GetCommandModifier_Weapons();		
		HumanCommandMove hcm = m_pPlayer.GetCommand_Move();
		HumanMovementState hms = new HumanMovementState();
		m_pPlayer.GetMovementState(hms)	;
		HumanCommandAdditives hma = m_pPlayer.GetCommandModifier_Additives();
		hma.SetInjured(0.0, false);
		hma.SetExhaustion(0.0, false);
		
		
		vector curAngles;
		curAngles[0] = hcw.GetBaseAimingAngleLR();
		curAngles[1] = hcw.GetBaseAimingAngleUD();
		curAngles[2] = hms.m_fLeaning * 45;
		//SLog.d(hms.m_CommandTypeId);

		vector aimChangeTM[4];
		Math3D.YawPitchRollMatrix(curAngles, pOutResult.m_CameraTM);
		pOutResult.m_CameraTM[3] = "0 0 0";
	}

	override vector GetBaseAngles(){
		return "0 0 0";
	}
	
	override string GetCameraName(){
		return "SDayZPlayerCameraBase";
	}
	
}	















