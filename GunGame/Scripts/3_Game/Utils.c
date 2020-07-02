class Utils
{
    static Vector2 StrToVector2(string value)
    {
        array<string> strgs = new array<string>;
		value.Split(" ", strgs); //TODO delete empty strings

        return new Vector2(strgs[0].ToFloat(),strgs[1].ToFloat());
    }
}