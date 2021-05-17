class GunplayConstants{
	/////////////////////////////////////////////////////////////
	//				FOCUS
	static const float FOCUS_RESET_SPEED = 0.2;
	
	static const float ERECT_FOCUS_SPEED = 1.0;
	static const float CROUCH_FOCUS_SPEED = 0.5;
	static const float PRONE_FOCUS_SPEED = 0.25;
	
	/////////////////////////////////////////////////////////////
	//				FOV and OPTIC LENS
	static const float OPTIC_FOV_REDUCTION = 3;	// how much the fov will be reduced compared to vanilla
	static const float OPTIC_LENS_ZOOM_BOOST = 2; // A zoom boost too high can cause pixellated image and wrong reticles (boost < 3 is recommended)
	
	/////////////////////////////////////////////////////////////
	// ADS
	static const float WEAPON_INSPECT_MIN_Y_ANGLE = -5;
	static const float WEAPON_INSPECT_MAX_Y_ANGLE = 10;
	static const float WEAPON_INSPECT_MIN_X_ANGLE = -35;
	static const float WEAPON_INSPECT_MAX_X_ANGLE = 35;
}