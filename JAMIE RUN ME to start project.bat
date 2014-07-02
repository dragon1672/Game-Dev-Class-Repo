@echo off
::echo "+---------------------------------------------------------------+"
::echo "| controls                                                      |"
::echo "+---------------------------------------------------------------+"
::echo "|               Editor Mode                                     |"
::echo "+-------------------+-------------------------------------------+"
::echo "| L Mouse Click     | Place or select nodes                     |"
::echo "| Shift + LMouse    | connect nodes/delete existing connection  |"
::echo "| Right Mouse Click | move camera                               |"
::echo "| Ctrl + 'A'        | show all connections                      |"
::echo "| Delete            | remove current node                       |"
::echo "| shift+Del         | remove all nodes                          |"
::echo "+---------------------------------------------------------------+"
::echo "|              Pathing Mode                                     |"
::echo "+-------------------+-------------------------------------------+"
::echo "| L Mouse Click     | selecte a node to path to                 |"
::echo "| Right Mouse Click | Move cam if not attached                  |"
::echo "+-------------------+-------------------------------------------+"

::pause

::LevelEditor\LevelEditor.sln
::start "" "LevelEditor\LevelEditor.sln"

::echo "+---------------------------------------------------------------+"
::echo "| controls                                                      |"
::echo "+---------------------------------------------------------------+"
::echo "|               Editor Mode                                     |"
::echo "+-------------------+-------------------------------------------+"
::echo "| Click and Move    | Move position and vel of particle         |"
::echo "| Arrow Keys        | accelerate particle in arrow direction    |"
::echo "+-------------------+-------------------------------------------+"

echo prepare yourself for the most visual effects you have ever seen in a virtual world

ComputerGraphics\ComputerGraphics.sln


::this will compile and run, find a better way to link to visual studio
::"C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" /run