modded class IngameHud
{
    ref GunGameHud gunGameHud;

    override void Init( Widget hud_panel_widget )
	{
        super.Init(hud_panel_widget);

        #ifndef GG_Debug
            //Disabled Elements that we have disabled
            m_Notifiers.FindWidget("Temperature").Show(false);
            m_Notifiers.FindWidget("Hungry").Show(false);
            m_Notifiers.FindWidget("Thirsty").Show(false);
            m_Notifiers.FindWidget("NotifierDivider").Show(false);
            m_Notifiers.GetParent().FindWidget("BadgesSpacer").Show(false);
        #endif 
        gunGameHud = new GunGameHud();
    }

    override void Update( float timeslice )
	{
        super.Update(timeslice);

        gunGameHud.Update(timeslice);
    }

#ifndef GG_Debug
    //supposed to do the job
    override void RefreshQuickbarVisibility()
	{
		m_QuickbarWidget.Show(false);
	} 
#endif
}