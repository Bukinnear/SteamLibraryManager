#pragma once
#include <filesystem>

namespace fs = std::filesystem;

// cl /EHsc Main.cpp Library.cpp Menu.cpp Output.cpp /nologo /std:c++latest
// cd C:\Code\SteamLibraryManager
 
 int main(int argc, char const *argv[])
 {
     /* 
     int phase = 0;
     Library selectedLibrary;
     GameFolder selectedGameFolder;
     DirectoryEntry selectedDestination;


     mainloop
     {
         if (phase > 4)
         {
            cout << "error, restarting";
            phase = 0;
            continue;
         }

        else if (phase = 0)
        {
            showLibraryList();
            try 
            {
                getValidLibrary() = validLibrary;
                phase = 1;
                continue;
            }
            catch (backException)
            {
                --phase;
                continue;
            }
            Catch (Exceptions)
            {
                // Handle exceptions
            }
        }

        else if (phase = 1)
        {
            selectedLibrary.showGameFolderList();
            try 
            {
                selectedLibrary.getValidGameFolderSelection() = validGameFolder;
                phase = 2;
                continue;
            }
            catch (backException)
            {
                --phase;
                continue;
            }
            Catch (Exceptions)
            {
                // Handle exceptions
            }
        }

        else if (phase = 2)
        {
            showLibraryList();
            try 
            {
                validDestinationLibrary = getValidDestinationLibrary();
                phase = 3;
                continue;
            }
            catch (backException)
            {
                --phase;
                continue;
            }
            Catch (Exceptions)
            {
                // Handle exceptions
            }
        }

        else if (phase = 3)
        {
            try
            {
                copyGameFolderToDestination(selectedGameFolder, selectedDestination);
            }
            catch (Exceptions)
            {
                deleteCopiedFiles();
            }

            try 
            {
                deleteOldFiles();
            }
            catch (Exceptions)
            {
                // Handle Exceptions
            }
            
        }
        else if (phase = 4)
        {
            
        }

     }

      */
     return 0;
 } 