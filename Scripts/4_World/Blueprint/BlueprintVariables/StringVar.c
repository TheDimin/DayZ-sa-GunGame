class StringVar: BlueprintVariable
{
    override string ToCode(array<ref Blueprint> params = null)
    {
        return name + " = " + "\"" + value + "\";\n";
    }
}