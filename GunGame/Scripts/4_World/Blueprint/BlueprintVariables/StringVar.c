class StringVar: BlueprintVariable
{
    string ToCode(array<ref Blueprint> params = null)
    {
        return name + " = " + "\"" + value + "\";\n";
    }
}