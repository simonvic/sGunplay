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
	
	static const float TIME_TO_ADS = 0.5;        //Entering ADS
	static const float TIME_FROM_ADS = 0.3;      //Exiting ADS	
	static const float TIME_3RD = -0.2;          //Added to TIME_TO_ADS	
	static const float TIME_BACKUP_SIGHT = 0.2;  //Switching beetween optic/ironsight and viceversa
	
	/////////////////////////////////////////////////////////////
	// AIMING MODEL
	static const float HANDS_DRAG_SMOOTHNESS = 0.2;        // how smooths the hands will "lag" behind the camera. Recommended 0.15 > x > 0.40
	static const float RESET_SPEED_INSPECTION = 0.1;        // how fast the camera will reset from inspection angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_FREELOOK = 0.1;          // how fast the camera will reset from freelook angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE = 0.3;          // how fast the camera will reset from deadzone angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE_WEAPON = 0.3;   // how fast the camera will reset from weapon deadzone angles to default. 0.1 = fast | 0.4 = slow
}