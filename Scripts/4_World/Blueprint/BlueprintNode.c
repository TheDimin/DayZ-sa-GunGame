class BlueprintNode
{
    ref Blueprint node;
    ref array<ref Blueprint> InputNodes = new array<ref Blueprint>();
    ref BlueprintNode child;
    int paramCount;

    void BlueprintNode(Blueprint _Node)
    {
        node = _Node;
    }

    void SetChild(BlueprintNode _Child)
    {
        child = _Child;
    } 

    void SetParam(int index,BlueprintVariable _Node)
    {
        for (int i = InputNodes.Count(); i <= index; i++)
        {
            InputNodes.Insert(null);
        }
        InputNodes.Set(index,_Node);
    }

    string Generate()
    {
        string value = node.ToCode(InputNodes);
        if(child != null && child != this)
            value += child.Generate();
        return value;
    }
}