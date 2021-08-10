class GunLevel : Managed
{
    string weapon = "NONE";
    string mag = "NONE";
    ref array<string> attachments = new array<string>();
    //Required kills to complete this level (Name is made Nice for Json , not for Code side)
    protected int kills = 1;

    void GunLevel(string _WeaponName, string _MagName, array<string> _Attachments,int _Kills)
    {
        weapon = _WeaponName;
        attachments = _Attachments;
        mag = _MagName;
        kills = _Kills;
    }
    int GetRequiredKills()
    {
        return kills;
    }
}