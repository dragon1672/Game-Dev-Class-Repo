@echo off
echo "+---------------------------------------------------------------+"
echo "| controls                                                      |"
echo "+---------------------------------------------------------------+"
echo "|               Editor Mode                                     |"
echo "+-------------------+-------------------------------------------+"
echo "| L Mouse Click     | Place or select nodes                     |"
echo "| Shift + LMouse    | connect nodes/delete existing connection  |"
echo "| Right Mouse Click | move camera                               |"
echo "| Ctrl + 'A'        | show all connections                      |"
echo "| Delete            | remove current node                       |"
echo "| shift+Del         | remove all nodes                          |"
echo "+---------------------------------------------------------------+"
echo "|              Pathing Mode                                     |"
echo "+-------------------+-------------------------------------------+"
echo "| L Mouse Click     | selecte a node to path to                 |"
echo "| Right Mouse Click | Move cam if not attached                  |"
echo "+-------------------+-------------------------------------------+"

pause

LevelEditor\LevelEditor.sln
::start "" "LevelEditor\LevelEditor.sln"


::this will compile and run, find a better way to link to visual studio
::"C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" /run