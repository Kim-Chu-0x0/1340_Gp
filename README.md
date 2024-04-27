In this game, you are a interstellar explorer who travel among galaxies.

Oneday, your crewship crushed on an unknown planet, you need to try to survive as long as possible.

Awful digital corruptions are approaching from everywhere and absorbing your limited energy, fix them with materials you mine from the planet!

----------------------------------------------------

Rules:

  1:Keep your energy higher than 0 to withstand the cold weather
  
  2:Some buildings consume resources to activate, close those which you do not meet their requirement first inorder to process to next turn
  
  3:For most situation, Use WASD to control, and E works as "Yes" while Q works as "No"
  
  4:Getting new cards require energy, and process to new turn regenerate some

  5:Having a high energy level will gain you some bouns, while low energy level will lead to some de-buff

----------------------------------------------------


----------------------------------------------------

Compilation:

  Use 
  
    g++ Main.cpp -o Main.exe
    
  to complie
  
  Then enter
  
    ./Main.exe
    
  to start the game
  
----------------------------------------------------

Team member:

  3036227434
  
(Yeah, only me)

----------------------------------------------------

Libraries:

  No non-standard libraries are used

----------------------------------------------------

Project reqs:

1.Generation of random game sets or events:

  All gaming data is generated randomly  (for example: Draw Card,Weighting system is used to control the output  (Calss_Card.h and its related h.files)  )

2.Data structures for storing game status (e.g., arrays, STL containers):

  Complex game data is stored in different classes and subclasses(In 90% head files)

3.Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers):

  Vector is frenquently used(In 90% head files)
  
4.File input/output (e.g., for loading/saving game status):

  The game has a well developed SL system, includes Auto-Saving, and provides Multiple Save-Slots for player to save their progress

  
5.Program codes in multiple files:

  Codes are distributted to different file
  
  All files are sorted into 4 layers:

    top: Main
    
    2:Control_Module
    
    3:Display_Module_Main
    
    bottom:Objects & Display_Module_Class
    
  files only access and respond to files in their neighbor layers, so the structure of the program is clear

----------------------------------------------------

Wanna try my render system?

  Read the readme.txt inside Display_Module_CLass, it explains how the complex render system works
