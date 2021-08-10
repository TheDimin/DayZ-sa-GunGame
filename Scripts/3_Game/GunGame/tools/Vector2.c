
modded class Vector2
{
    //Combines  the 2 vectors
    void Add(Vector2 value)
    {
        x += value.x;
        y += value.y;
    }

    void Divide(float amount)
    {
        x = x / amount;
        y = y / amount;
    }

    static Vector2 GetAverage(array<ref Vector2> vectors)
    {
        Vector2 result = new Vector2(0,0);

        foreach(auto sourceVector : vectors)
        {
            result.Add(sourceVector);
        }

        result.Divide(vectors.Count());
        return result;
    }

        
    static array<ref Vector2> ToVector2Array(array<string> values)
    {
        auto result = new array<ref Vector2>();
        foreach (auto sourceValue : values)
        {
            result.Insert(ToVector2(sourceValue));
        }

        return result;
    }


    static Vector2 GetAverageFromStrings(array<string> vectorStrings)
    {
        return GetAverage(ToVector2Array(vectorStrings));
    }

    static Vector2 ToVector2(string value)
    {
        array<string> strgs = new array<string>;
		value.Split(" ", strgs); //TODO delete empty strings

        return new Vector2(strgs[0].ToFloat(),strgs[1].ToFloat());
    }
}