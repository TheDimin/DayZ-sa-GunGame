class MapLocation : Managed
{
    string LocationName = "Null";
    ref array<string> SpawnPoints = new array<string>();

    array<string> GetLocations()
    {
        return SpawnPoints;
    }
}

class GunGameLocation : MapLocation
{
    ref array<ref GunLevel> Weapons = new array<ref GunLevel>();
}