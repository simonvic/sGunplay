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
		recoilControlMouseX        = Math.Clamp(1 - recoilControlMouseX, 0, 1);
		recoilControlMouseY        = Math.Clamp(1 - recoilControlMouseY, 0, 1);
		recoilControlHandsX        = Math.Clamp(1 - recoilControlHandsX, 0, 1);
		recoilControlHandsY        = Math.Clamp(1 - recoilControlHandsY, 0, 1);
		recoilControlMisalignmentX = Math.Clamp(1 - recoilControlMisalignmentX, 0, 1);
		recoilControlMisalignmentY = Math.Clamp(1 - recoilControlMisalignmentY, 0, 1);
		recoilControlKick          = Math.Clamp(1 - recoilControlKick, 0, 1);
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