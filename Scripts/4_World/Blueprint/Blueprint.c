class Blueprint
{
    void BPParseWarning(string message)
    {
        Print(this.Type().ToString() + "::[Parse Warning] "+message);
    }

    void BPParseError(string message)
    {
        Error(this.Type().ToString() + "::[Parse Error] "+message);
    }

    string ToCode(array<ref Blueprint> params = null)
    {
        BPParseWarning("no implementation for ToCode");
        return "";
    }

    string ToVariable()
    {
        BPParseWarning("no implementation for ToVariable");
        return "";
    }
}