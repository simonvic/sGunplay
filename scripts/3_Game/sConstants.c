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
	static const float ADS_FOV_REDUCTION = 3;                         // Minimum and maximum optic fov reduction
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
	static const bool AIMING_MODEL_USE_FILTER_MOVEMENT = true;                    // Use the player movement in the player aiming model
	static const bool AIMING_MODEL_USE_FILTER_INJURY = true;                      // Use the player injure state in the player aiming model
	
	static const float AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER = 2;    // Overall strength of the movement modifier
	static const float AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME = 0.4;  // Smooth time of the movement modifier
	static const float AIMING_MODEL_FILTER_MOVEMENT[] = {
		2.5, 2.0,  //yaw strength, yaw frequency
		3.5, 7.5   //pitch strength, pitch frequency
	};
	
	static const float AIMING_MODEL_FILTER_INJURY_MULTIPLIER = 1;    // Overall strength of the injury modifier
	static const float AIMING_MODEL_FILTER_INJURY[] = {
		15.0, 2.0,  //yaw strength, yaw frequency
		2.0, 0.0    //pitch strength, pitch frequency
	};
	
	static const float AIMING_MODEL_HANDS_OFFSET_RECOIL_CONTRIBUTION[] = {0, 0}; //{X, Y} how much the recoil will contribute to the hands offset calculation (therefore camera offset and more). Use -1 to nullify
	
	/////////////////////////////////////////////////////////////
	// SWAY
	static const float SWAY_AMPLITUDE[] = {1.5, 2.8};    //{X, Y} amplitude of sway with no modifiers
	static const float SWAY_FREQUENCY[] = {0.2, 0.7};    //{X, Y} frequency of sway with no modifiers
	static const float SWAY_MULTIPLEIR_ERECT = 1;        // Multiplier to be applied when the player is ERECT
	static const float SWAY_MULTIPLEIR_CROUCHED = 0.3;   // Multiplier to be applied when the player is CROUCHED
	static const float SWAY_MULTIPLEIR_PRONE = 0.1;      // Multiplier to be applied when the player is PRONE
	static const float SWAY_DECREASE_FOCUSING = 4;       // Amount of sway to reduce while holding breath
	static const float SWAY_DECAY_POWER = 8;             // How much the percentage left of stamina will impact the sway (SWAY_DECAY_POWER ^ stamina_percentage)
	static const float SWAY_MINIMUM = 0.2;               // This minimum will be added during the sway multiplication (even while holding breath)
		
	//////////////////
	// INERTIA
	static const float INERTIA_SMOOTHNESS = 0.3;                         // how smooths the hands will "lag" behind the camera. Recommended 0.15 > x > 0.40
	static const float INERTIA_MULTIPLIER_BASE = 2;                      // Base multiplier of the amount of inertia to be applied
	static const float INERTIA_MULTIPLIER_WEAPON_WEIGHT = 3.5 * 0.0001;  // Multiplier of the amount of inertia to be applied based on weapon weight (example: 5 * 0.0001 means 5 every kilogram)
	static const float INERTIA_MULTIPLIER_WEAPON_LENGTH_WEIGHT = 2;      // Multiplier of the amount of inertia to be applied based on weapon length
	static const float INERTIA_MULTIPLIER_PLAYER_WEIGHT = 0.5 * 0.0001;  // Multiplier of the amount of inertia to be applied based on player inventory weight
	static const float INERTIA_MULTIPLIER_HIPFIRE = 4.0;                 // Multiplier of the amount of inertia to be applied when the player is in hipfire
	
	static const float INERTIA_MULTIPLIER_STANDING = 1.0;              // Multiplier of the amount of inertia to be applied when the player is NOT MOVING
	static const float INERTIA_MULTIPLIER_WALKING = 1.5;               // Multiplier of the amount of inertia to be applied when the player is WALKING
	static const float INERTIA_MULTIPLIER_JOGGING = 2.0;               // Multiplier of the amount of inertia to be applied when the player is JOGGING
	
	static const float INERTIA_MULTIPLIER_ERECT = 1;                   // Multiplier of the amount of inertia to be applied when the player is ERECT
	static const float INERTIA_MULTIPLIER_CROUCHED = 1.5;              // Multiplier of the amount of inertia to be applied when the player is CROUCHED
	static const float INERTIA_MULTIPLIER_PRONE = 2.0;                 // Multiplier of the amount of inertia to be applied when the player is PRONE
	
	static const float INERTIA_MIN_MULTIPLIER = 1;                     // Minimum value of inertia
	static const float INERTIA_MAX_MULTIPLIER = 50;                    // Maximum value of inertia
	
	/////////////////////////////////////////////////////////////
	// DYNAMIC CROSSHAIR
	static const float CROSSHAIR_PRECISION = 50;              // How much precise the crosshair placement will be. (metres)
	static const float CROSSHAIR_SMOOTHNESS = 0.05;           // How much smooth the crosshair placement will be.


	/////////////////////////////////////////////////////////////
	// RECOIL
	static const float RECOIL_HAND_MULTIPLIER = 1; //for easy debug tweaking of all recoils; use 1 for default recoil
	static const float RECOIL_RELOAD_TIME_MULTIPLIER = 1; //time to repositionate weapon multiplier
	
	/////////////////////////////////////////////////////////////
	// HIPFIRE
	static const float RECOIL_HIPFIRE_H_MULTIPLIER = 5; // how much the horizontal recoil will increase when hip firing; use 1 to keep it the same as ADS
	static const float RECOIL_HIPFIRE_V_MULTIPLIER = 2; // how much the vertical recoil will increase when hip firing; use 1 to keep it the same as ADS
	static const float RECOIL_HIPFIRE_RELOAD_TIME_MULTIPLIER = 2; // how much the time to repositionate the gun will increase when hip firing; use 1 to keep it the same as ADS
	
	/////////////////////////////////////////////////////////////
	// RECOIL CONTROL
	static const bool RECOIL_CONTROL_USE_PLAYER_INVENTORY_WEIGHT = true;  // the player inventory weight will contribute to the recoil control
	static const bool RECOIL_CONTROL_USE_STRENGTH = true;                 // the player strength (soft skill) will contribute to the recoil control
	static const bool RECOIL_CONTROL_USE_STANCE = true;                   // the player stance will contribute to the recoil control
	static const bool RECOIL_CONTROL_USE_MOVEMENT = true;                 // the player movement will contribute to the recoil control
	
	static const float RECOIL_CONTROL_COEFF = 0.5;                        // how much the specialty will impact the recoil during early stages of Strength progression. (see arctan function)
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT = -0.2 * 0.0001;   // how much every Gram of your inventory will affect final recoil calculation (0.2 * 0.0001 = 0.2 per kilogram)	
	static const float RECOIL_CONTROL_STRENGTH_WEIGHT = 1;                // how much the strength (soft skills) will affect final recoil calculation. The strength goes from -1 to 1
	
	static const float RECOIL_CONTROL_MULTIPLIER_ERECT = 1;               // how much the ERECT stance will affect final recoil calculation
	static const float RECOIL_CONTROL_MULTIPLIER_CROUCHED = 0.5;          // how much the CROUCHED stance will affect final recoil calculation
	static const float RECOIL_CONTROL_MULTIPLIER_PRONE = 0.25;            // how much the PRONE stance will affect final recoil calculation
	
	static const float RECOIL_CONTROL_MULTIPLIER_STANDING = 1.0;          // how much STANDING will affect final recoil calculation
	static const float RECOIL_CONTROL_MULTIPLIER_WALKING = 1.5;           // how much WALKING will affect final recoil calculation
	static const float RECOIL_CONTROL_MULTIPLIER_JOGGING = 2.0;           // how much JOGGING will affect final recoil calculation
	
}