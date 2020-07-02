class MapLocation : Managed
{
    string DisplayName;
    ref array<string> Locations = new array<string>();

    array<string> GetLocations()
    {
        return Locations;
    }
}

class GunGameLocation : MapLocation
{
    ref array<ref GunLevel> Weapons = new array<ref GunLevel>();
}