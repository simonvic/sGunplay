modded class DayZPlayerImplement{

	protected bool m_isInspectingWeapon;
	protected UAInput m_inputWeaponInspect;
	bool m_isMoveSettingsChanged = true;
	
	void DayZPlayerImplement(){
		m_inputWeaponInspect = GetUApi().GetInputByName("SUA_ADSWeaponInspect");
	}
	
	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished){
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
	}
	
	override bool AimingModel(float pDt, SDayZPlayerAimingModel pModel){
		return super.AimingModel(pDt, pModel);
	}
			
	override void HandleADS(){
		super.HandleADS();
		
		if(!m_inputWeaponInspect){
			SLog.d("input is null");
			return;
		}
		
		if(m_inputWeaponInspect.LocalPress() || m_inputWeaponInspect.LocalHold()){
			m_isInspectingWeapon = GetInputController().CameraIsFreeLook();
		}
		
		if(m_inputWeaponInspect.LocalRelease()){
			m_isInspectingWeapon = false;
		}

	}
	
	bool isInspectingWeapon(){
		return m_isInspectingWeapon;
	}
	
	void updateMovementSettings(){
		
		if (!m_MoveSettings)
			m_MoveSettings = GetDayZPlayerType().CommandMoveSettingsW();

		//! run sprint (SHIFT HOLD) filter 
		m_MoveSettings.m_fRunSpringTimeout	= 1;							//!< filter span value		[s]
		m_MoveSettings.m_fRunSpringMaxChange	= 0.5;							//!< filter speed value		[val/s]

		//! WSAD direction filter 
		m_MoveSettings.m_fDirFilterTimeout	= 0.1;						//!< direction filter timeout [s]
		m_MoveSettings.m_fDirFilterSpeed		= Math.DEG2RAD * 360; 		//!< direction filter max rot speed [rad/s]
		m_MoveSettings.m_fMaxSprintAngle		= Math.DEG2RAD * 45.01;		//!< max sprint angle [rad]

		m_MoveSettings.m_fTurnAngle 			= 45;						//!< this is when char starts tu turn
		m_MoveSettings.m_fTurnEndUpdateNTime	= 0.7;						//!< this is end norm time (turn amount is not updated after this time)
		m_MoveSettings.m_fTurnNextNTime		= 0.9;						//!< this is norm time when new turn from old turn is evaluated again (turn->turn)


		m_MoveSettings.m_fHeadingChangeLimiterIdle 	= 500000; 			//!<
		m_MoveSettings.m_fHeadingChangeLimiterWalk 	= 2000;				//!<
		m_MoveSettings.m_fHeadingChangeLimiterRun		= 1500;				//!<
		
		if(m_inputWeaponInspect.LocalPress() || m_inputWeaponInspect.LocalHold()){
			m_isMoveSettingsChanged = m_MoveSettings.m_fLeaningSpeed != 1;
			m_MoveSettings.m_fLeaningSpeed = 1;
		}else{
			m_isMoveSettingsChanged = m_MoveSettings.m_fLeaningSpeed != 10;
			m_MoveSettings.m_fLeaningSpeed = 10;
		}
		/*
		m_MoveSettings.m_fSlidingPoseAngle = 0;		//!< angle (0.707 * PI)	- when angle is bigger - sliding pose is done (rad)
		m_MoveSettings.m_fSlidingPoseTrackTime = 0.1;	//!< time change of angle is tracked in the past (sec)
		m_MoveSettings.m_fSlidingPoseRepTime = 1;
		*/
	}
	
}