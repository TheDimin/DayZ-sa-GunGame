class ScriptableElement extends ScriptedWidgetEventHandler
{
    ref ButtonWidget root;

    ref ScriptInvoker OnClickEvent = new ScriptInvoker();

    void OnWidgetScriptInit(Widget layoutRoot)
	{
        root = ButtonWidget.Cast(layoutRoot);
        
        root.SetHandler( this );

    }

    void SetTitle(string _Name)
    {
        root.SetText(_Name);
    }
     
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if(w == root)
        {
            OnClickEvent.Invoke();
        }
        return false;
    }
}