modded class PropertyModifiers {
	
	ref array<float> recoilOffsetHands;
	ref array<float> recoilMisalignment;
	ref array<float> recoilOffsetMouse;
	float recoilKick;
	
	override void UpdateModifiers() {
		super.UpdateModifiers();
		recoilOffsetHands = {0,0};
		recoilMisalignment = {0,0};
		recoilOffsetMouse = {0,0};
		recoilKick = 0;
		for (int i = 0; i < m_OwnerItem.GetInventory().AttachmentCount(); i++) {
			applyAttachmentModifiers(ItemBase.Cast(m_OwnerItem.GetInventory().GetAttachmentFromIndex(i)));
		}
		
		recoilOffsetHands[0] =  1 - recoilOffsetHands[0];   //@todo check for needed clamps
		recoilOffsetHands[1] =  1 - recoilOffsetHands[1];
		recoilMisalignment[0] = 1 - recoilMisalignment[0];
		recoilMisalignment[1] = 1 - recoilMisalignment[1];
		recoilOffsetMouse[0] =  1 - recoilOffsetMouse[0];
		recoilOffsetMouse[1] =  1 - recoilOffsetMouse[1];
		recoilKick =            1 - recoilKick;
	}
	
	protected void applyAttachmentModifiers(ItemBase attachment) {
		array<float> temp = PropertyModifiers.getModifierFloatArray(attachment, "s_hands");
		recoilOffsetHands[0] = recoilOffsetHands[0] + temp[0];
		recoilOffsetHands[1] = recoilOffsetHands[1] + temp[1];
		
		temp = PropertyModifiers.getModifierFloatArray(attachment, "s_misalignment");
		recoilMisalignment[0] = recoilMisalignment[0] + temp[0];
		recoilMisalignment[1] = recoilMisalignment[1] + temp[1];
		
		temp = PropertyModifiers.getModifierFloatArray(attachment, "s_mouse");
		recoilOffsetMouse[0] = recoilOffsetMouse[0] + temp[0];
		recoilOffsetMouse[1] = recoilOffsetMouse[1] + temp[1];
		
		recoilKick += PropertyModifiers.getModifierFloat(attachment, "s_kick");
	}
	
	static float getModifierFloat(ItemBase item, string modifierName, float defaultValue = 0.0) {
		if (item.ConfigIsExisting(modifierName)) {
			return item.ConfigGetFloat(modifierName);
		}
		return defaultValue;
	}
	
	static array<float> getModifierFloatArray(ItemBase item, string modifierName, array<float> defaultValue = null) {
		array<float> temp = {};
		if (item.ConfigIsExisting(modifierName)) {
			item.ConfigGetFloatArray(modifierName, temp);
			return temp;
		}
		
		if (defaultValue != null) {
			return defaultValue;
		}
		
		return {0,0};
	}
	
}