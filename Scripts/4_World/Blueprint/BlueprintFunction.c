class BlueprintFunction : Blueprint
{
    string name = "";
    string returnType = "void";
    //ref array<string> paramTypes = new array<string>();

    ref BlueprintNode rootNode;

    void BlueprintFunction(string _Name,string _ReturnType)
    {
        name = _Name;
        returnType = _ReturnType;
    }


    override string ToCode(array<ref Blueprint> params = null)
    {
        auto generatedCode = "";

        generatedCode += returnType + " " + name;
        generatedCode += "(";
        //TODO support params
        //foreach (string value : paramTypes)
        //{
        //    generatedCode+= value;
        //}
        generatedCode += ") \n{\n";

        if(rootNode != null);
            generatedCode += rootNode.Generate();


        generatedCode += "\n}";
        return generatedCode;
    }
}