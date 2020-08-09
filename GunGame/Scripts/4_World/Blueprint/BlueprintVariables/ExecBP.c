
//Special Type TODO
class ExecBP : BlueprintVariable
{
    string ToCode(array<ref Blueprint> params = null)
    {
        Error("ExecBP cannot be cast to value");
        return "";
    }
}