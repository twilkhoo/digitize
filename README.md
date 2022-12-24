# Digitize
Digitize is a stratego-style two player game. Players take turns moving their pieces, called "Links", in order to download 4 Data or make their opponent download 4 Viruses (Data and Viruses are types of Links). Each player has eight links- four Viruses and four Data, each with a strength 1-4 (unique for their data type). Players also choose five abilities- special effects which can help them in their gameplay. 

## Usage
After cloning, type `make` to build the project.\
Run `./digitize` to run the game without X11 graphics.\
Pass the `-graphics` flag to enable X11 graphics (XLib must be installed).\
Pass the `-link1 <placement-file.txt>` or `-link2 <placement-file.txt>` flags to control where links are placed for player one and two respectively- examples include the provided `placementP1.txt` and `placementP2.txt` files.\
Pass the `-ability1 <XXXXX>` or `-ability2 <XXXXX>` to control what abilities each player has- by default the ability string XXXXX is LFDSP, but you can make the string any five characters from LFDSPRHO, where each letter stands for a different ability and you can only pick up to two of the same ability.

> Note: the ability-character associations are as follows:
>- L: Link Boost
>- F: Firewall
>- D: Download
>- S: Scan
>- P: Polarize
>- R: Link Reborn
>- H: High Ground
>- O: Portal

> Note: in game, type "help" to get more information on all commands, and "abilities" to get more information on your abilities.

## Design
***MVC Architecture***- used to organize the flow of commands between different modules (user only interacts with the model).\
***Strategy Design Pattern***- used with the Ability class to enable creating/editing/removing new abilities as needed.\
***Simple Factory Idiom***- used to seperate Link objects into Virus and Data objects, created at runtime.\
***Observer Design Pattern***- coupled with the MVC to enable a pub/sub control flow where moves are observed by the X11 graphics view, and the terminal view.\
***RAII***- adhered to RAII principles through smart pointers, vectors, maps, and other C++ containers to enable automatic resource management/cleanup.\
***Exception Handling/Safety***- implemented strong exception guarantees with most functions that would throw.

## Pictures
![image](https://user-images.githubusercontent.com/30396273/209451599-6295631f-d64d-4846-a5d9-5f12decf0fab.png)
![image](https://user-images.githubusercontent.com/30396273/209451702-69293126-b561-462f-9eae-1cce5a944632.png)

