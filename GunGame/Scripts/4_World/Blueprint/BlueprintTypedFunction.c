class BlueprintTypedFunction : Blueprint
{
    string name;
    string code;
    ref array<ref typename> inputTypes;
    //array<BlueprintVariable> OutputParams;

    void BlueprintTypedFunction(string _Name,string _Code,array<ref typename> _InputTypes)
    {
        name = _Name;
        code = _Code;
        inputTypes = _InputTypes; 
    }

    string ToCode(array<ref Blueprint> params = null)
    {
        auto generatedCode = code;

        int inputCount = inputTypes.Count();
        inputCount -= 1;
        if(params.Count() != inputCount) //get rid of the Exec node by adding -1
        {
            BPParseError("Requires '"+inputCount+"' params but only recieved '"+params.Count()+"'");
            return "";
        }


        for (int i = 0; i < inputCount; i++)
        {
            string searchTerm = "{" + i.ToString() + "}";
            if(generatedCode.Contains(searchTerm)) //ToDo typecheck ?
            {
                auto castedVariable = BlueprintVariable.Cast(params[i])
                generatedCode.Replace(searchTerm,castedVariable.ToVariable());
            }
        }
        generatedCode+= "\n";
        return generatedCode;
    }
}