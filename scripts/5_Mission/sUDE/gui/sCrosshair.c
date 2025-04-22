class SCrosshair : Managed {
	
	static const ref array<ref array<string>> STYLES = {
		{"set:sCrosshairs image:curve",        "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_DEFAULT"},
		{"set:sCrosshairs image:curve",        "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_CURVE"},
		{"set:sCrosshairs image:chevron",      "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_CHEVRON"},
		{"set:sCrosshairs image:double_curve", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_DOUBLECURVE"},
		{"set:sCrosshairs image:dot",          "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_DOT"},
		{"set:sCrosshairs image:cross",        "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_CROSS"},
		{"set:sCrosshairs image:tcross",       "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_TCROSS"},
		{"set:sCrosshairs image:angles",       "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_ANGLES"}
	};
	
	static array<string> getStyleImages() {
		auto images = new array<string>;
		foreach (array<string> style : STYLES) {
			images.Insert(style[0]);
		}
		return images;
	}
	
	static array<string> getStyleNames() {
		auto images = new array<string>;
		foreach (array<string> style : STYLES) {
			images.Insert(style[1]);
		}
		return images;
	}
	
	protected ref Widget m_sCrosshairRoot;
	protected ref ImageWidget m_staticCrosshair;
	protected ref Widget m_dynamicCrosshairRoot;
	protected ref ImageWidget m_dynamicCrosshair;
	protected PlayerBase m_player;
	
	protected ref SUserConfigGunplay m_userCfgGunplay;
	
	void SCrosshair() {
		m_userCfgGunplay = SUserConfig.gunplay();
		m_sCrosshairRoot = GetGame().GetWorkspace().CreateWidgets(getCrosshairLayoutName());
		m_staticCrosshair = ImageWidget.Cast(m_sCrosshairRoot.FindWidget("img_staticCrosshair"));
		m_dynamicCrosshairRoot = m_sCrosshairRoot.FindWidget("c_dynamicCrosshair");
		m_dynamicCrosshair = ImageWidget.Cast(m_dynamicCrosshairRoot.FindWidget("img_dynamicCrosshair"));
		setStyle(m_userCfgGunplay.getDynamicCrosshairType());
		setColor(m_userCfgGunplay.getDynamicCrosshairColor());
	}
	
	string getCrosshairLayoutName() {
		return "MyMODS/sGunplay/GUI/layouts/ingame/hud/sCrosshair.layout";
	}
	
	protected bool canShowStaticCrosshair() {
		return m_userCfgGunplay.isStaticCrosshairEnabled() && m_player && !m_player.IsFireWeaponRaised();
	}

	protected bool canShowDynamicCrosshair() {
		return m_userCfgGunplay.isDynamicCrosshairEnabled() && m_player && m_player.IsFireWeaponRaised() && (!m_player.IsInIronsights() && !m_player.IsInOptics());
	}
	
	void setStyle(int styleIndex) {
		styleIndex = Math.Clamp(styleIndex, 0, STYLES.Count() - 1);
		m_dynamicCrosshair.LoadImageFile(0, STYLES[styleIndex][0]);
	}
	
	void setColor(SColor color) {
		m_staticCrosshair.SetColor(color.getARGB());
		m_dynamicCrosshair.SetColor(color.getARGB());
	}
	
	void onUpdate(float deltaTime) {
		if (canShowStaticCrosshair()) {
			if (!m_staticCrosshair.IsVisible()) {
				m_staticCrosshair.Show(true);
			}
		} else {
			if (m_staticCrosshair.IsVisible()) {
				m_staticCrosshair.Show(false);
			}
		}
		m_player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!m_player) return; // TODO: temp-fix, change this
		
		if (!canShowDynamicCrosshair()) {
			if (m_dynamicCrosshair.IsVisible()) {
				m_dynamicCrosshair.Show(false);
			}
			return;
		}
		
		vector pos = m_player.GetAimingModel().getSCrosshairPosition();
		m_dynamicCrosshairRoot.SetPos(pos[0], pos[1]);
		if (!m_dynamicCrosshair.IsVisible()) {
			m_dynamicCrosshair.Show(true);
		}

	}

}

