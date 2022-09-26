class GunplayConstants {
	
	/////////////////////////////////////////////////////////////
	// DYNAMIC CROSSHAIR
	static const float CROSSHAIR_PRECISION = 50;              // How precise the crosshair placement will be. (metres)
	static const float CROSSHAIR_SMOOTHNESS = 0.05;           // How smooth the crosshair placement will be.
	
	/////////////////////////////////////////////////////////////
	// SWAY
	static const float SWAY_AMPLITUDE[] = {1.5, 2.8};    //{X, Y} amplitude of sway with no modifiers
	static const float SWAY_FREQUENCY[] = {0.2, 1.1};    //{X, Y} frequency of sway with no modifiers
	static const float SWAY_MULTIPLEIR_ERECT = 1;        // Multiplier to be applied when the player is ERECT
	static const float SWAY_MULTIPLEIR_CROUCHED = 0.3;   // Multiplier to be applied when the player is CROUCHED
	static const float SWAY_MULTIPLEIR_PRONE = 0.1;      // Multiplier to be applied when the player is PRONE
	static const float SWAY_DECREASE_FOCUSING = 4;       // Amount of sway to reduce while holding breath
	static const float SWAY_DECAY_POWER = 8;             // How much the percentage left of stamina will impact the sway (SWAY_DECAY_POWER ^ stamina_percentage)
	static const float SWAY_MINIMUM = 0.2;               // This minimum will be added during the sway multiplication (even while holding breath)
	
	/////////////////////////////////////////////////////////////
	// AIMING MODEL
	
	static const float RESET_SPEED_INSPECTION = 0.1;          // how fast the camera will reset from inspection angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_FREELOOK = 0.1;            // how fast the camera will reset from freelook angles to default. 0.1 = fast | 0.4 = slow
	static const float RESET_SPEED_DEADZONE = 0.3;            // how fast the camera will reset from deadzone angles to default. 0.1 = fast | 0.4 = slow
	
	///////////////////
	// HIPFIRE
	static const bool AIMING_MODEL_USE_FILTER_HIPFIRE_DEADZONE = true;       // Use hipfire deadzone filter in the player aiming model
	static const float HIPFIRE_DEADZONE_AMOUNT_DEGREE[4] = {                 // amount of deadzone to use when hipfiring (in degrees)
		    1,
		-10,   10,
		   -1    };
	
	///////////////////
	// INERTIA
	static const bool AIMING_MODEL_USE_WEAPON_INERTIA = true;                  // Use weapon inertia in the player aiming model
	
	static const float INERTIA_VELOCITY_LIMIT[] = {                            // Velocity limit in inertia build up (degree per second ?)
		    10,
		-30,   30,
		   -10    };
	static const float INERTIA_SPEED_ACCELERATION[2]         = {0.1, 0.1};     // Speed of acceleration (horizontal and vertical) in inertia build up (smoothTime value)
	static const float INERTIA_SPEED_RESET[2]                = {0.2, 0.2};     // Speed of deceleration (horizontal and vertical) in inertia reset (smoothTime 
	static const float INERTIA_SPEED_ACCELERATION_HIPFIRE[2] = {0.1, 0.1};     // Speed of acceleration (horizontal and vertical) in inertia build up while hipfiring(smoothTime value)
	static const float INERTIA_SPEED_RESET_HIPFIRE[2]        = {0.2, 0.2};     // Speed of deceleration (horizontal and vertical) in inertia reset while hipfiring (smoothTime value)
	
	static const float INERTIA_MULTIPLIER_BASE = 1;                            // Base multiplier of the amount of inertia to be applied
	static const float INERTIA_MIN_MULTIPLIER  = 0;                            // Minimum value of inertia
	static const float INERTIA_MAX_MULTIPLIER  = 1;                            // Maximum value of inertia
	
	static const float INERTIA_MULTIPLIER_STANDING = 1.00;                     // Multiplier of the amount of inertia to be applied when the player is NOT MOVING
	static const float INERTIA_MULTIPLIER_WALKING  = 1.25;                     // Multiplier of the amount of inertia to be applied when the player is WALKING
	static const float INERTIA_MULTIPLIER_JOGGING  = 1.50;                     // Multiplier of the amount of inertia to be applied when the player is JOGGING
	
	static const float INERTIA_MULTIPLIER_ERECT    = 1.00;                     // Multiplier of the amount of inertia to be applied when the player is ERECT
	static const float INERTIA_MULTIPLIER_CROUCHED = 0.30;                     // Multiplier of the amount of inertia to be applied when the player is CROUCHED
	static const float INERTIA_MULTIPLIER_PRONE    = 0.25;                     // Multiplier of the amount of inertia to be applied when the player is PRONE
	
	static const float INERTIA_MULTIPLIER_WEAPON_LENGTH_WEIGHT = 0.25;         // Multiplier of the amount of inertia to be applied based on weapon length
	
	static const float INERTIA_MULTIPLIER_HIPFIRE = 1.00;                      // Multiplier of the amount of inertia to be applied when the player is in hipfire

	static const float INERTIA_MISALIGNMENT_INTENSITY[2] = {0.05, 0.05};       // Horizontal and vertical misalignment caused by weapon inertia
	
	
	///////////////////
	// MOVEMENT
	static const bool AIMING_MODEL_USE_FILTER_MOVEMENT = true;  // Use the player movement in the player aiming model
	static const float AIMING_MODEL_FILTER_MOVEMENT[] = {
		1.25, 2.0,  //yaw strength, yaw frequency
		1.75, 7.5   //pitch strength, pitch frequency
	};
	static const float AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER = 2;    // Overall strength of the movement modifier
	static const float AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME = 0.4;  // Smooth time of the movement modifier
	
	///////////////////
	// INJURY
	static const bool AIMING_MODEL_USE_FILTER_INJURY = true;  // Use the player injure state in the player aiming model
	static const float AIMING_MODEL_FILTER_INJURY[] = {
		15.0, 2.0,  //yaw strength, yaw frequency
		2.0, 0.0    //pitch strength, pitch frequency
	};
	
	///////////////////
	// WEAPON INTERACTION
	static const bool AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION = true;     // Use the weapon interaction in the player aiming model (firemode change, zeroing, zooming)
	static const float AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION_OFFSETS[] = {-20, 10}; //{X, Y} offset to be applied when interacting with the weapon
	
	/////////////////////////////////////////////////////////////
	
	
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
	
	static const float TIME_TO_ADS = 0.4;                           //Entering ADS
	static const float TIME_FROM_ADS = 0.3;                         //Exiting ADS	
	static const float TIME_3RD = -0.2;                             //Added to TIME_TO_ADS	
	static const float TIME_BACKUP_SIGHT = 0.25;                    //Switching beetween optic/ironsight and viceversa
	
	static const float ADS_MOVEMENT_MISALIGNMENT_STRENGTH = 2;      //how strong is the misalignment
	static const float ADS_MOVEMENT_MISALIGNMENT_FREQUENCY = 1.15;  //how fast is the misalignment
	static const float ADS_MOVEMENT_MISALIGNMENT_SMOOTHNESS = 0.3;  //how smooth is the misalignment
	
	// FOV and OPTIC LENS
	static const float ADS_LENS_ACTIVATION_DELAY = -250;            // Delay in milliseconds added to the camera transition time
	static const float ADS_HIDE_CLOTHING_DELAY = -200;              // Delay in milliseconds added to the camera transition time
	static const float ADS_FOV_REDUCTION_OPTICS = 3;                // Minimum and maximum ads fov reduction in optics
	static const float ADS_LENS_STRENGTH_CONSTRAINTS[] = {0, 4};    // A zoom boost too high can cause pixellated image and wrong reticles (boost < 3 is recommended)
	
	///////////////////
	// FOCUS
	static const float FOCUS_RESET_SPEED = 0.2;
	static const float FOCUS_SPEED_ERECT = 0.6;
	static const float FOCUS_SPEED_CROUCHED = 0.4;
	static const float FOCUS_SPEED_PRONE = 0.1;
	
	static const float FOCUS_SPEED_NON_MAGN_MULTIPLIER = 0.70;      // Multiplier of focus speed when using a non-magnifying optic
	static const float FOCUS_SPEED_IRONSIGHT_MULTIPLIER = 0.75;     // Multiplier of focus speed when using a ironsight optic
	/////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////
	// RECOIL CONTROL
	static /*const*/ float RECOIL_CONTROL_COEFF = 0.5;             // how much the specialty will impact the overall recoil. (see arctan function)
	static /*const*/ float RECOIL_CONTROL_STEEPNESS = 4.6;         // "steepness" of the arctan function curve (see arctan function)
	
	///////////////////
	// STRENGTH
	static const bool RECOIL_CONTROL_USE_STRENGTH = true;          // the player strength (soft skill) will contribute to the recoil control
	static const float RECOIL_CONTROL_MINIMUM = -1;                // minimum value of recoil control (used on arctangent function)
	static const float RECOIL_CONTROL_MAXIMUM = 1;                 // maximum value of recoil control (used on arctangent function)
	static const float RECOIL_CONTROL_STRENGTH_WEIGHT = 0.25;      // how much the strength (soft skills) will affect final recoil calculation. The strength goes from -1 to 1
	
	///////////////////
	// PLAYER INVENTORY WEIGHT
	static const bool RECOIL_CONTROL_USE_PLAYER_INVENTORY_WEIGHT = true;  // the player inventory weight will contribute to the recoil control
	
	
	///////////////////
	// PLAYER STANCE
	static const bool RECOIL_CONTROL_USE_STANCE = true;            // the player stance will contribute to the recoil control
	static const float RECOIL_CONTROL_STANCE_ERECT = 0;            // how much the ERECT stance will affect final recoil calculation
	static const float RECOIL_CONTROL_STANCE_CROUCHED = 0.70;      // how much the CROUCHED stance will affect final recoil calculation
	static const float RECOIL_CONTROL_STANCE_PRONE = 0.80;         // how much the PRONE stance will affect final recoil calculation
	
	///////////////////
	// PLAYER MOVEMENT
	static const bool RECOIL_CONTROL_USE_MOVEMENT = true;          // the player movement will contribute to the recoil control
	static const float RECOIL_CONTROL_MOVEMENT_STANDING = 0;       // how much STANDING will affect final recoil calculation
	static const float RECOIL_CONTROL_MOVEMENT_WALKING = -0.3;     // how much WALKING will affect final recoil calculation
	static const float RECOIL_CONTROL_MOVEMENT_JOGGING = -0.5;     // how much JOGGING will affect final recoil calculation

	/////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////
	// SOUNDS
	static const string SOUND_CHANGE_ZEROING = "combinationlock_changenumber_SoundSet";
	static const string SOUND_CHANGE_ZOOM = "combinationlock_changedial_SoundSet";
	/////////////////////////////////////////////////////////////
	
	
}
