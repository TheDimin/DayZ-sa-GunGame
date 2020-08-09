modded class IngameHud
{
   ref GunGameHud gunGameHud;

    void IngameHud()
    {
        gunGameHud = new GunGameHud();
    }

    void ~IngameHud()
    {
        delete gunGameHud;
    }


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

    }

    override void Show( bool show )
	{
        super.Show(show);
		gunGameHud.Show( show );
	}

#ifndef GG_Debug
    //supposed to do the job
    override void RefreshQuickbarVisibility()
	{
		m_QuickbarWidget.Show(false);
	} 
#endif

}