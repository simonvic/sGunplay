class GunplayConstants {
	
	/////////////////////////////////////////////////////////////
	// GENERAL
	
	// inventory weights threshold defined in grams
	// the values are expected to be in descending order from OVERLOADED to LIGHT
	static const float INVENTORY_WEIGHT_GRAMS_OVERLOADED  = 40000;  // weight limit; the player is carrying too much stuff
	static const float INVENTORY_WEIGHT_GRAMS_HEAVY       = 20000;  // inventory fairly full or with heavy items
	static const float INVENTORY_WEIGHT_GRAMS_MEDIUM      = 10000;  // average survivor inventory
	static const float INVENTORY_WEIGHT_GRAMS_LIGHT       = 5000;   // the player is carrying few items
	static const float INVENTORY_WEIGHT_GRAMS_VERYLIGHT   = 0;      // the player is carrying almost nothing
	/////////////////////////////////////////////////////////////
	
	
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
	// WEAPON INERTIA
	static const bool AIMING_MODEL_USE_WEAPON_INERTIA = true;                  // Use weapon inertia in the player aiming model
	
	static const float INERTIA_VELOCITY_LIMIT[] = {                            // Velocity limit in inertia build up (degree per second ?)
		    10,
		-30,   30,
		   -10    };
	static const float INERTIA_SPEED_ACCELERATION[2]                     = {0.1, 0.1};     // Acceleration (horizontal and vertical) in inertia build up (smoothTime value)
	static const float INERTIA_SPEED_RESET[2]                            = {0.2, 0.2};     // Deceleration (horizontal and vertical) in inertia reset (smoothTime value)
	static const float INERTIA_SPEED_ACCELERATION_HIPFIRE[2]             = {0.1, 0.1};     // Acceleration (horizontal and vertical) in inertia build up while hipfiring (smoothTime value)
	static const float INERTIA_SPEED_RESET_HIPFIRE[2]                    = {0.2, 0.2};     // Deceleration (horizontal and vertical) in inertia reset while hipfiring (smoothTime value)
	
	static const float INERTIA_MULTIPLIER_BASE                           = 1.00;   // Base multiplier of the amount of inertia to be applied
	static const float INERTIA_MIN_MULTIPLIER                            = 0.00;   // Minimum value of inertia
	static const float INERTIA_MAX_MULTIPLIER                            = 1.00;   // Maximum value of inertia
	
	static const float INERTIA_MULTIPLIER_STANDING                       = 1.00;   // Multiplier of the amount of inertia to be applied when the player is NOT MOVING
	static const float INERTIA_MULTIPLIER_WALKING                        = 1.25;   // Multiplier of the amount of inertia to be applied when the player is WALKING
	static const float INERTIA_MULTIPLIER_JOGGING                        = 1.50;   // Multiplier of the amount of inertia to be applied when the player is JOGGING
	
	static const float INERTIA_MULTIPLIER_ERECT                          = 1.00;   // Multiplier of the amount of inertia to be applied when the player is ERECT
	static const float INERTIA_MULTIPLIER_CROUCHED                       = 0.30;   // Multiplier of the amount of inertia to be applied when the player is CROUCHED
	static const float INERTIA_MULTIPLIER_PRONE                          = 0.25;   // Multiplier of the amount of inertia to be applied when the player is PRONE
	
	static const float INERTIA_MULTIPLIER_INVENTORY_WEIGHT_OVERLOADED    = 1.90;   // Multiplier of the amount of inertia to be applied when the player inventory is OVERLOADED
	static const float INERTIA_MULTIPLIER_INVENTORY_WEIGHT_HEAVY         = 1.75;   // Multiplier of the amount of inertia to be applied when the player inventory is HEAVY
	static const float INERTIA_MULTIPLIER_INVENTORY_WEIGHT_MEDIUM        = 1.50;   // Multiplier of the amount of inertia to be applied when the player inventory is MEDIUM
	static const float INERTIA_MULTIPLIER_INVENTORY_WEIGHT_LIGHT         = 1.25;   // Multiplier of the amount of inertia to be applied when the player inventory is LIGHT
	static const float INERTIA_MULTIPLIER_INVENTORY_WEIGHT_VERYLIGHT     = 1.00;   // Multiplier of the amount of inertia to be applied when the player inventory is VERYLIGHT
	
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
	static const float ADS_LENS_ACTIVATION_DELAY = -250;                         // Delay in milliseconds added to the camera transition time
	static const float ADS_HIDE_CLOTHING_DELAY = -200;                           // Delay in milliseconds added to the camera transition time
	static const float ADS_FOV_MULT_CONSTRAINTS[] = {0.75, 1.00};                // ads fov reduction constraints (min / max) in ironsight and non-magnifying optics
	static const float ADS_FOV_MULT_OPTICS_CONSTRAINTS[] = {1.57079, 3.14159};   // ads fov reduction constraints (min / max) in magnifying optics
	static const float ADS_LENS_STRENGTH_CONSTRAINTS[] = {0, 4};                 // A zoom boost too high can cause pixellated image and wrong reticles (boost < 3 is recommended)
	
	///////////////////
	// FOCUS
	static const float FOCUS_RESET_SPEED    = 0.20;
	static const float FOCUS_SPEED_ERECT    = 0.60;
	static const float FOCUS_SPEED_CROUCHED = 0.40;
	static const float FOCUS_SPEED_PRONE    = 0.10;
	
	static const float FOCUS_SPEED_NON_MAGN_MULTIPLIER  = 0.70;     // Multiplier of focus speed when using a non-magnifying optic
	static const float FOCUS_SPEED_IRONSIGHT_MULTIPLIER = 0.75;     // Multiplier of focus speed when using a ironsight optic
	/////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////
	// RECOIL CONTROL
	static const float RECOIL_CONTROL_COEFF = 0.5;                 // how much the specialty will impact the overall recoil. (see arctan function)
	static const float RECOIL_CONTROL_STEEPNESS = 4.6;             // "steepness" of the arctan function curve (see arctan function)
	
	///////////////////
	// STRENGTH
	// the player strength (soft skill) will contribute to the recoil control.
	// set RECOIL_CONTROL_STRENGTH_WEIGHT to 0 to disable
	static const float RECOIL_CONTROL_STRENGTH_WEIGHT = 0.25;      // how much the strength (soft skills) will affect final recoil calculation. The strength goes from -1 to 1
	static const float RECOIL_CONTROL_MINIMUM = -1;                // minimum value of recoil control (used on arctangent function)
	static const float RECOIL_CONTROL_MAXIMUM = 1;                 // maximum value of recoil control (used on arctangent function)
	
	///////////////////
	// PLAYER INVENTORY WEIGHT
	// the player inventory weight will contribute to the recoil control. Set all values to 0 to disable
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT_OVERLOADED  = -0.75;  // @see INVENTORY_WEIGHT_GRAMS_OVERLOADED
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT_HEAVY       = -0.50;  // @see INVENTORY_WEIGHT_GRAMS_HEAVY
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT_MEDIUM      = -0.25;  // @see INVENTORY_WEIGHT_GRAMS_MEDIUM
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT_LIGHT       =  0.25;  // @see INVENTORY_WEIGHT_GRAMS_LIGHT
	static const float RECOIL_CONTROL_INVENTORY_WEIGHT_VERYLIGHT   =  0.75;  // @see INVENTORY_WEIGHT_GRAMS_VERYLIGHT
	
	///////////////////
	// PLAYER STANCE
	// the player stance will contribute to the recoil control. Set all values to 0 to disable
	static const float RECOIL_CONTROL_STANCE_ERECT                 =  0.00;   // how much the ERECT stance will affect final recoil calculation
	static const float RECOIL_CONTROL_STANCE_CROUCHED              =  0.70;   // how much the CROUCHED stance will affect final recoil calculation
	static const float RECOIL_CONTROL_STANCE_PRONE                 =  0.80;   // how much the PRONE stance will affect final recoil calculation
	
	///////////////////
	// PLAYER MOVEMENT
	// the player movement will contribute to the recoil control. Set all values to 0 to disable
	static const float RECOIL_CONTROL_MOVEMENT_STANDING            =  0.00;   // how much STANDING will affect final recoil calculation
	static const float RECOIL_CONTROL_MOVEMENT_WALKING             = -0.30;   // how much WALKING will affect final recoil calculation
	static const float RECOIL_CONTROL_MOVEMENT_JOGGING             = -0.50;   // how much JOGGING will affect final recoil calculation

	/////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////
	// PLAYER CONTROLLER
	
	static const float PLAYER_INERTIA_SPRINT_TIMING[2] = {0.1, 3};             // Min / Max timing for transitioning from jogging to running
	static const float PLAYER_INERTIA_TURNING_TIMING[2] = {0.1, 2};            // Min / Max timing for changing direction (heading with mouse) when walking or jogging
	static const float PLAYER_INERTIA_SPRINT_TURNING_TIMING[2] = {0.1, 4};     // Min / Max timing for changing direction (heading with mouse) when running
	/////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////
	// SOUNDS
	static const string SOUND_CHANGE_ZEROING = "combinationlock_changenumber_SoundSet";
	static const string SOUND_CHANGE_ZOOM = "combinationlock_changedial_SoundSet";
	/////////////////////////////////////////////////////////////
	
	
}
