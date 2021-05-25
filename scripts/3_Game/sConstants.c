class GunplayConstants{
	/////////////////////////////////////////////////////////////
	// FOCUS
	static const float FOCUS_RESET_SPEED = 0.2;
	
	static const float ERECT_FOCUS_SPEED = 1.0;
	static const float CROUCH_FOCUS_SPEED = 0.5;
	static const float PRONE_FOCUS_SPEED = 0.25;
	
	/////////////////////////////////////////////////////////////
	// FOV and OPTIC LENS
	static const float ADS_LENS_ACTIVATION_DELAY = -250;              // Delay in milliseconds added to the camera transition time
	static const float ADS_FOV_REDUCTION_CONSTRAINTS[] = {2, 3};      // Minimum and maximum optic fov reduction
	static const float ADS_LENS_STRENGTH_CONSTRAINTS[] = {0, 4};      // A zoom boost too high can cause pixellated image and wrong reticles (boost < 3 is recommended)
	
	/////////////////////////////////////////////////////////////
	// ADS
	static const float ANGLES_CONSTRAINT_WEAPON_INSPECT[] = { 
		   10,
		-35, 35,
		  -5  };
	
	static const float ANGLES_CONSTRAINT_FREELOOK[] = { 
		   45,
		-45, 45,
		  -45 };
	
	static const float TIME_TO_ADS = 0.5;        //Entering ADS
	static const float TIME_FROM_ADS = 0.3;      //Exiting ADS	
	static const float TIME_3RD = -0.2;          //Added to TIME_TO_ADS	
	static const float TIME_BACKUP_SIGHT = 0.2;  //Switching beetween optic/ironsight and viceversa
	
	/////////////////////////////////////////////////////////////
	// AIMING MODEL
	static const float RESET_SPEED_INSPECTION = 0.1;          // how fast the camera will reset from inspection angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_FREELOOK = 0.1;            // how fast the camera will reset from freelook angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE = 0.3;            // how fast the camera will reset from deadzone angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_WEAPON_INERTIA = 0.3;      // how fast the camera will reset from weapon deadzone angles to default. 0.1 = fast | 0.4 = slow
	
	static const bool CAMERA_FOLLOWS_BREATHING_SWAY = false;  // Camera will move along the breathing sway
		
	static const bool AIMING_MODEL_USE_WEAPON_INERTIA = true;                       // Use weapon inertia in the player aiming model
	static const bool AIMING_MODEL_USE_MODIFIER_MOVEMENT = true;                    // Use the player movement in the player aiming model
	static const bool AIMING_MODEL_USE_MODIFIER_INJURY = true;                      // Use the player injure state in the player aiming model
	
	static const float AIMING_MODEL_MODIFIER_MOVEMENT_MULTIPLIER = 2;    // Overall strength of the movement modifier
	static const float AIMING_MODEL_MODIFIER_MOVEMENT_SMOOTHTIME = 0.3;  // Smooth time of the movement modifier
	static const float AIMING_MODEL_MODIFIER_MOVEMENT[] = {
		1.0, 1.0,  //yaw strength, yaw frequency
		1.5, 7.0   //pitch strength, pitch frequency
	};
	
	static const float AIMING_MODEL_MODIFIER_INJURY_MULTIPLIER = 1;    // Overall strength of the injury modifier
	static const float AIMING_MODEL_MODIFIER_INJURY[] = {
		15.0, 5.0,  //yaw strength, yaw frequency
		2.0, 0.0    //pitch strength, pitch frequency
	};
		
	//////////////////
	// INERTIA
	  
	static const float INERTIA_SMOOTHNESS = 0.3;                       // how smooths the hands will "lag" behind the camera. Recommended 0.15 > x > 0.40
	static const float INERTIA_MULTIPLIER_BASE = 2;                    // Base multiplier of the amount of inertia to be applied
	static const float INERTIA_MULTIPLIER_WEAPON_WEIGHT = 3 * 0.0001;  // Multiplier of the amount of inertia to be applied based on weapon weight (example: 5 * 0.0001 means 5 every kilogram)
	static const float INERTIA_MULTIPLIER_PLAYER_WEIGHT = 0.5 * 0.0001;// Multiplier of the amount of inertia to be applied based on player inventory weight
	static const float INERTIA_MULTIPLIER_HIPFIRE = 5;                 // Multiplier of the amount of inertia to be applied when the player is in hipfire
	
	static const float INERTIA_MULTIPLIER_STANDING = 1.0;              // Multiplier of the amount of inertia to be applied when the player is NOT MOVING
	static const float INERTIA_MULTIPLIER_WALKING = 1.5;               // Multiplier of the amount of inertia to be applied when the player is WALKING
	static const float INERTIA_MULTIPLIER_JOGGING = 2.0;               // Multiplier of the amount of inertia to be applied when the player is JOGGING
	
	static const float INERTIA_MULTIPLIER_ERECT = 1;                   // Multiplier of the amount of inertia to be applied when the player is ERECT
	static const float INERTIA_MULTIPLIER_CROUCHED = 0.5;              // Multiplier of the amount of inertia to be applied when the player is CROUCHED
	static const float INERTIA_MULTIPLIER_PRONE = 0.9;                 // Multiplier of the amount of inertia to be applied when the player is PRONE
	
	static const float INERTIA_MIN_MULTIPLIER = 1;                     // Minimum value of inertia
	static const float INERTIA_MAX_MULTIPLIER = 50;                    // Maximum value of inertia
	
	/////////////////////////////////////////////////////////////
	// DYNAMIC CROSSHAIR
	static const float CROSSHAIR_PRECISION = 50;              // How much precise the crosshair placement will be. (metres)
	static const float CROSSHAIR_SMOOTHNESS = 0.05;           // How much smooth the crosshair placement will be.
}



class RecoilConstants {
	static const float HAND_RECOIL_MULTIPLIER = 1; //for easy debug tweaking of all recoils; use 1 for default recoil
	static const float RELOAD_TIME_MULTIPLIER = 1; //time to repositionate weapon multiplier
	
	//----------------------------------------------------------
	//				HIPFIRE
	//----------------------------------------------------------
	static const float HIPFIRE_H_RECOIL_MULTIPLIER = 15; // how much the horizontal recoil will increase when hip firing; use 1 to keep it the same as ADS
	static const float HIPFIRE_V_RECOIL_MULTIPLIER = 2; // how much the vertical recoil will increase when hip firing; use 1 to keep it the same as ADS
	static const float HIPFIRE_RELOAD_TIME_MULTIPLIER = 2; // how much the time to repositionate the gun will increase when hip firing; use 1 to keep it the same as ADS
	
	//----------------------------------------------------------
	//				RECOIL CONTROL
	//----------------------------------------------------------	
	static const float RECOIL_CONTROL_COEFF = 0.5; // how much the specialty will impact the recoil during early stages of Strength progression. (see arctan function)
	static const float RECOIL_INVENTORY_WEIGHT = 0.2 * 0.0001; // how much every Gram of your inventory will affect final recoil calculation (0.2 * 0.0001 = 0.2 per kilogram)	
	static const float RECOIL_SOFTSKILL_WEIGHT = 1; // how much the soft skills will affect final recoil calculation
}