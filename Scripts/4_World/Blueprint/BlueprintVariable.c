class BVData
{
    const int StringColor = 0xFFFFFF;
    const int IntColor= 0x000000;
}

//TODO: parameter of a blueprint node
class BlueprintVariable : Blueprint
{
    string name;
    string value;
    void BlueprintVariable(string _Name,string _Value)
    {
        name = _Name;
        value = _Value;
    }
    
    override string ToVariable()
    {
        return name;
    }
}
