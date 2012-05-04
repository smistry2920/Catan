*****************************************************
**Suneil Mistry/ Jake Lubben/ Michael Strumsky     **
**ECE2524: Introduction to Unix                    **
**Final Unix Group Project                         **
**www.git@github.com:lubbs65/Catan.git             **
**04/30/12                                         **
*****************************************************
				                                    
				                                    
				                                   *********************
				                                   * Settlers of Catan *
				                                   *********************
				
**************
** Purpose: **
**************

The purpose of our project is to create a virtual model of the popular board game “Settlers of Catan.” This games is a multi-player board game made for players to assume the role of settlers, each attempting to build and develop holdings while trading and acquiring resources. As a players settlement  grow they receive victory points, and the first player to achieve 10 victory points is the winner. However, there are  many more rules and regulations to the game, which are included along with this documentation. 

*********************
** HOW TO RUN: **
*********************

Our program works with Qt. You can install Qt Creator from your Ubuntu Software Center or from http://qt.nokia.com/downloadsac. It has software for the updated versions of Windows, Mac, and Linux. 
After installing qt:
-->First, run “make clean” in terminal inside the "catan_final" directory to prevent errors. 
-->Then run “qmake” inside the "catan_final" folder using the terminal
-->Then run “make.”  
->This should compile with no errors.
If you have any problems setting up please email smistry@vt.edu.

***************
** Progress: **
***************

	All the standard conditions of the game have been implemented based on regular 	guidelines and rules (Settlers_ofCatan_Guide.txt), with a few modifications.

********************
** Modifications: **
********************

    -No longest road
    -Robber: Steal from every person at where the robber is        placed. Also, the robber can be placed in the same place as previously placed.


**************************
** Not Yet Implemented: **
**************************

    -Pop-up window to view player's hand
    -Development Card functions
    -Start of Game
    -Trades

***************************
** Problems Encountered: **
***************************
	
	Problem 1:
	Hexagons: Trouble with using GUI buttons on each side of the hexagons to 	implement roads and developments.

	Solution : 
	Found a way to manipulate the size and shape of GUI buttons, so that we could 	place roads and developments on all the required sections of the hexagons

	Problem 2:
	Characterization of Settlements/Cities on Map: Difficulty on how to take in 		specifics of 	map locations.

	Solution:
	Used a String of characters to describe each aspect of the node like the 	example above. This way we could use information and check the maps nodes 	easily.

	e.g 221|0|0|d|1|0|0|3|s
	Format is city ID|left Color|left node|right Color|right node|top color|top node|port
	
	Problem 3:
 	Map Checking: How to make sure that settlements, cities, and roads can be 	bought and meet the right placement guidelines.

	Solution:
	Recorded all outputs of purchases of settlements, cities, and roads on lists. 	Checks surrounding areas using the numerical labeling and lists. Also, it makes 	sure that players have enough resources to buy the item of interest. 
	
	
	
