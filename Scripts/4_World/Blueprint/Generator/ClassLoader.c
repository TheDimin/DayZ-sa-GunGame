//General Notes(This stuff will become very complex):

//We should write the class to some "tempData" as json or binary.
//Between Itteration a file could become invalid to be parsed. and we fallback to the binary data(fails to load if there is no binary data)

//Class that will Manage generating runtime classes from "strings"
class ClassLoader
{
    static void BeginLoad()
    {
        Print("FileParsing started");
        string fileName;
		FileAttr fileAttr;
		FindFileHandle scripts = FindFile("*.C", fileName, fileAttr, 2);
		
		if (!scripts)
        {
            Print("Failed to get file handle");
            return;
        }
			

		while(FindNextFile(scripts, fileName, fileAttr))
		{
			Print(fileName);
		}

		CloseFindFile(scripts);
    }

    //public void 

}