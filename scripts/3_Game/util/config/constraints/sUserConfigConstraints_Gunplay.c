class SUserConfigConstraints_Gunplay : SUserConfigConstraintsBase {

	override string getPath() {
		return "$profile:\\sUDE\\config\\sGunplay_constraints.json";
	}
	
	override void deserialize(string data, out string error){
		auto constraints = this;
		getSerializer().ReadFromString(constraints, data, error);
	}
	
	override string serialize(){
		string result;
		auto constraints = this;
		getSerializer().WriteToString(constraints, true, result);
		return result;
	}
	
	
	///////////////////////////////////////
	// these go in json
	protected ref SConstraintPrimitiveMinMaxNumeric adsDOFIntensity         = new SConstraintPrimitiveMinMaxNumeric(0, 1);
	protected ref SConstraintSwitch                 hideWeaponBarrelInOptic = new SConstraintSwitch(false);
	protected ref SConstraintSwitch                 hideClothingInOptic     = new SConstraintSwitch(true);
	protected ref SConstraintPrimitiveMinMaxNumeric lensZoomStrength        = new SConstraintPrimitiveMinMaxNumeric(0, 1);
	protected ref SConstraintMinMaxArrayNumeric     deadzoneLimits          = new SConstraintMinMaxArrayNumeric({0,0,0,0}, {1,1,1,1});
	protected ref SConstraintSwitch                 resetDeadzoneOnFocus    = new SConstraintSwitch(true);
	protected ref SConstraintSwitch                 showDynamicCrosshair    = new SConstraintSwitch(true);
	///////////////////////////////////////
	
	SConstraintPrimitiveMinMaxNumeric getADSDOFIntensity() {
		return adsDOFIntensity;
	}
	
	SConstraintSwitch getHideWeaponBarrelInOptic() {
		return hideWeaponBarrelInOptic;
	}
	
	SConstraintSwitch getHideClothingInOptic() {
		return hideClothingInOptic;
	}
	
	SConstraintPrimitiveMinMaxNumeric getLensZoomStrength() {
		return lensZoomStrength;
	}
	
	SConstraintMinMaxArrayNumeric getDeadzoneLimits() {
		return deadzoneLimits;
	}

	SConstraintSwitch getResetDeadzoneOnFocus() {
		return resetDeadzoneOnFocus;
	}

	SConstraintSwitch getShowDynamicCrosshair() {
		return showDynamicCrosshair;
	}
		
}