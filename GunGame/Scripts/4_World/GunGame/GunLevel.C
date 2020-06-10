class GunLevel extends Managed
{
    string weaponName = "NONE";
    string magName = "NONE";
    ref array<string> attachmentNames;

    void GunLevel(string _WeaponName, string _MagName, array<string> _Attachments)
    {
        weaponName = _WeaponName;
        attachmentNames = _Attachments;

        if(_MagName == "")
        {
            magName = GetAmmoType();
        }
        else
        {
            magName = _MagName;
        }
    }


    string GetAmmoType()
    {
        return "";
    }
}