class BlueprintClass : Blueprint
{
    string name = "test";
    string parent = "";

    ref array<ref BlueprintVariable> variables = new array<ref BlueprintVariable>();
    ref array<ref BlueprintFunction> functions = new array<ref BlueprintFunction>();
    
    void BlueprintClass(string _Name,string _Parent = "")
    {
        name = _Name;
        parent = _Parent;
    }

    string ToCode(array<ref Blueprint> params = null)
    {
        string generated = "class ";
        generated += name;
        if(parent != "")
        {
            generated += " : " + parent;
        }
        generated += "\n {"
        
        foreach (BlueprintVariable variable : variables)
        {
            generated += "\n" + variable.ToCode();
        }  

        foreach (BlueprintFunction function : functions)
        {
            generated += "\n" + function.ToCode();
        }

        if(params != null)
            foreach (Blueprint param : params)
            {
                generated += "\n" + param.ToCode();
            }

        generated += "\n }"
        return generated;
    }

    string ToVariable()
    {
        return "this";
    }
}