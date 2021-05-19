class GunplayConstants{
	/////////////////////////////////////////////////////////////
	//				FOCUS
	static const float FOCUS_RESET_SPEED = 0.2;
	
	static const float ERECT_FOCUS_SPEED = 1.0;
	static const float CROUCH_FOCUS_SPEED = 0.5;
	static const float PRONE_FOCUS_SPEED = 0.25;
	
	/////////////////////////////////////////////////////////////
	//				FOV and OPTIC LENS
	static const float OPTIC_FOV_REDUCTION = 3;	  // how much the fov will be reduced compared to vanilla
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
	static const bool USE_WEAPON_INERTIA = true;              // Use weapon inertia in the player aiming model
	static const bool CAMERA_FOLLOWS_BREATHING_SWAY = false;  // Camera will move along the breathing sway
	
	static const float RESET_SPEED_INSPECTION = 0.1;          // how fast the camera will reset from inspection angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_FREELOOK = 0.1;            // how fast the camera will reset from freelook angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE = 0.3;            // how fast the camera will reset from deadzone angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE_WEAPON = 0.3;     // how fast the camera will reset from weapon deadzone angles to default. 0.1 = fast | 0.4 = slow
	  
	static const float INERTIA_SMOOTHNESS = 0.2;                       // how smooths the hands will "lag" behind the camera. Recommended 0.15 > x > 0.40
	static const float INERTIA_MULTIPLIER_BASE = 2;                    // Base multiplier of the amount of inertia to be applied
	static const float INERTIA_MULTIPLIER_WEAPON_WEIGHT = 3 * 0.0001;  // Multiplier of the amount of inertia to be applied based on weapon weight (example: 5 * 0.0001 means 5 every kilogram)
	static const float INERTIA_MULTIPLIER_HIPFIRE = 5;                 // Multiplier of the amount of inertia to be applied when the player is in hipfire
	
	static const float INERTIA_MULTIPLIER_STANDING = 1.0;              // Multiplier of the amount of inertia to be applied when the player is NOT MOVING
	static const float INERTIA_MULTIPLIER_WALKING = 1.5;               // Multiplier of the amount of inertia to be applied when the player is WALKING
	static const float INERTIA_MULTIPLIER_JOGGING = 2.0;               // Multiplier of the amount of inertia to be applied when the player is JOGGING
	
	static const float INERTIA_MULTIPLIER_ERECT = 1;                   // Multiplier of the amount of inertia to be applied when the player is ERECT
	static const float INERTIA_MULTIPLIER_CROUCHED = 0.5;              // Multiplier of the amount of inertia to be applied when the player is CROUCHED
	static const float INERTIA_MULTIPLIER_PRONE = 0.9;                 // Multiplier of the amount of inertia to be applied when the player is PRONE
	
	/////////////////////////////////////////////////////////////
	// DYNAMIC CROSSHAIR
	static const float CROSSHAIR_PRECISION = 50;              // How much precise the crosshair placement will be. (metres)
	static const float CROSSHAIR_SMOOTHNESS = 0.05;           // How much smooth the crosshair placement will be.
}