modded class IngameHud
{
    override void Init( Widget hud_panel_widget )
	{
        super.Init(hud_panel_widget);


        //Disabled so we can make sure stuff doesn't brake first
        //this is the spot we can hide certain Ui elements
        //m_Notifiers.FindWidget("Temperature").Show(false);
        //m_Notifiers.FindWidget("Hungry").Show(false);
        //m_Notifiers.FindWidget("Thirsty").Show(false);
        //m_Notifiers.FindWidget("NotifierDivider").Show(false);
        //m_Notifiers.GetParent().FindWidget("BadgesSpacer").Show(false);
       
        
    }

    //supposed to do the job
    override void RefreshQuickbarVisibility()
	{
		m_QuickbarWidget.Show(false);
	}
}