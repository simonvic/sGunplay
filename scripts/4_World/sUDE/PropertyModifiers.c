modded class PropertyModifiers {

	float recoilControlMouseX;
	float recoilControlMouseY;
	float recoilControlHandsX;
	float recoilControlHandsY;
	float recoilControlMisalignmentX;
	float recoilControlMisalignmentY;
	float recoilControlKick;
	
	//@todo improve this. Instead of recalculating everything, just add/remove when needed
	override void UpdateModifiers() {
		super.UpdateModifiers();

		recoilControlMouseX        = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlMouseX");
		recoilControlMouseY        = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlMouseY");
		recoilControlHandsX        = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlHandsX");
		recoilControlHandsY        = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlHandsY");		
		recoilControlMisalignmentX = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlMisalignmentX");
		recoilControlMisalignmentY = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlMisalignmentY");		
		recoilControlKick          = PropertyModifiers.getModifierFloat(m_OwnerItem, "s_recoilControlKick");

		for (int i = 0; i < m_OwnerItem.GetInventory().AttachmentCount(); i++) {
			applyAttachmentModifiers(ItemBase.Cast(m_OwnerItem.GetInventory().GetAttachmentFromIndex(i)));
		}

		//@todo check for needed clamps
		recoilControlMouseX        = 1 - recoilControlMouseX;
		recoilControlMouseY        = 1 - recoilControlMouseY;		
		recoilControlHandsX        = 1 - recoilControlHandsX;
		recoilControlHandsY        = 1 - recoilControlHandsY;
		recoilControlMisalignmentX = 1 - recoilControlMisalignmentX;
		recoilControlMisalignmentY = 1 - recoilControlMisalignmentY;
		recoilControlKick          = 1 - recoilControlKick;
	}
	
	protected void applyAttachmentModifiers(EntityAI attachment) {
		recoilControlMouseX        += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlMouseX");
		recoilControlMouseY        += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlMouseY");
		recoilControlHandsX        += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlHandsX");
		recoilControlHandsY        += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlHandsY");		
		recoilControlMisalignmentX += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlMisalignmentX");
		recoilControlMisalignmentY += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlMisalignmentY");		
		recoilControlKick          += PropertyModifiers.getModifierFloat(attachment, "s_recoilControlKick");
	}
	
	static float getModifierFloat(EntityAI entity, string modifierName, float defaultValue = 0.0) {
		if (entity.ConfigIsExisting(modifierName)) {
			return entity.ConfigGetFloat(modifierName);
		}
		return defaultValue;
	}
	
	static array<float> getModifierFloatArray(EntityAI entity, string modifierName, array<float> defaultValue = null) {
		array<float> temp = {};
		if (entity.ConfigIsExisting(modifierName)) {
			entity.ConfigGetFloatArray(modifierName, temp);
			return temp;
		}
		
		if (defaultValue != null) {
			return defaultValue;
		}
		
		return {0,0};
	}
	
}