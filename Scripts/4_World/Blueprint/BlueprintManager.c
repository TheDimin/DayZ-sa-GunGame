class BlueprintManager
{
    ref array<ref BlueprintTypedFunction> BlueprintTypes = new array<ref BlueprintTypedFunction>();

    void BlueprintManager()
    {
        RegisterBlueprints();
        Temp();
    }

    void Temp()
    {
        RegisterNode("Print","Print({0});",StringVar);

        auto params = new array<string>();
        params.Insert("LEL");

        auto GeneratedClass = new BlueprintClass("TestClass","Object");

        GeneratedClass.variables.Insert(new StringVar("Test", "Hello World!"));

        auto function = new BlueprintFunction("TestClass","void");
        function.rootNode = new BlueprintNode(BlueprintTypes[0]);
        function.rootNode.InputNodes.Insert(GeneratedClass.variables[0]);
        
        function.rootNode.child = new BlueprintNode(new StringVar("Test2", "Bye World!"));

        function.rootNode.child.child = new BlueprintNode(BlueprintTypes[0]);
        function.rootNode.child.child.InputNodes.Insert(function.rootNode.child.node);
        
        GeneratedClass.functions.Insert(function);
        Print("[Parser] Generated class :: '" + GeneratedClass.ToCode() + "'");

        
        ClassLoader.BeginLoad();
    }

    void RegisterBlueprints()
    {
    }

    void RegisterNode(string _Name,string _Code,typename _Input1)
    {
        auto params = new array<ref typename>();
        params.Insert(_Input1);

        params.Insert(ExecBP);
        BlueprintTypes.Insert(new BlueprintTypedFunction(_Name,_Code,params));
    }
}