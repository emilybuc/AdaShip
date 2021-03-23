# AdaShip
## Challenge Outline
### Summary and review of the problem, overall proposed solution 
We need to design and develop a battleships game in an object orientated way. Battleships is a simple game of placing ships of differring sizes onto a board. Your opponent then shoots at your board, the first person to sink all of their opponents ships wins.

In the simple game you only get one shot per turn but in the salvo variation of battleships you get a missile per ship left unsunk. 

The mine version of the game places random mines around the board, if your opponent hits a mine with a missile then the surrounding 8 tiles will also get hit. 

I also need to set up a computer player who will shoot at my board if its a one player verses computer game, the computer player needs to be able to place their ships automatically as well as shoot at the players board.

When taking user input there needs to be validation on where boats can be placed and where shots can be taken (i.e within the board).

My solution is to create two classes, the first of which will be 'Game' which will include functions such as the one to fire missiles, whether or not the missile has hit. 
The second class will be a board class to create the board, output the board and place the boats. 
I also want a struct - one that stores data about what is in the coordinate of the board (whether or not its been hit, if it has a boat or a mine) I will call this struct tile. 

I also want a file with functions about salvo mode, they will count the amount of boats left and a function that fires missiles but takes an argument for the amount of missiles.

### UML style diagram illustration inital overall solution 
![UML](AdaShip.png)
### Initial working plan, overall approach, development strategy and approach to quality
my inital working plan was to start off getting the data from the config file and inputting it into two classes, a boat and a board class, as both of these need to maintain state. It will also allow me to instanciate two instances of each of these classes for the one and two player boards (or computer). The board class will allow me to keep the state of each of the players' boards and carry out actions against them. For example the board class will keep the state of where the players boats are and where missiles have hit on their board.

My overall approach is to create as many functions that are reuseable especially in the board class as this class is going to be used to place ships onto the board and be used to fire missiles at the board. I decided that the board would own all of this functionality and not a game class as the board is where the state of the game is kept. 

The development strategy is to get functions working and useable before implementing more efficient versions, I will be constantly testing my code to check for bugs and inconsistencies. Once I have finished an epic I will get one of the other apprentices to look at my code to check for their understanding. If they are unsure of what my code is doing or the variable names make it confusing to follow what my code is doing I will refactor it. The best written code you can follow without any comments, the variable names should be self explanitory and you shouldnt have to reread a line more than once to understand what its doing.

My approach to quality is to create focused functions that have descriptive names and only do one task. If im trying to do a task more than once, for instance converting a string into all upper case then I will separate this task out into its own function. This will also make my code more readable as calling for a function called toUpper and passing in a string it is easier to understand what is happening.


### Analysis and decomposition of the overall problem into key epic style tasks
Analysis: 
The most difficult epic will be placing the boats and taking the users input as this requires me to not only figure out a way to convert letters that the user inputs into numbers; but also find a way to break up the letters from the numbers in the single entry.

Epics: 
Getting data from the config file and set-up of the board
Take users input and output a coordintate
Placing the boats
Game play setup - turn based play and when the game has ended
Configurable board, changing how the coordinates are inputted to take excel style x coordinates
Salvo mode
Unlimited additional boats
Hidden mines
Improved computer targeting

### Intial Object orientated design ideas  
I want to store the state of the board so I want to have that inside of a class. Making the game a class is probably not needed as it doesnt need to keep state itself. I will instead make a boat class to keep the state of the boats. 
I will make sure I use encapsulation, ensuring to use getters and setters when wanting to change the state of private member variables. 
I will also use inheritance so I can use my boat class inside of my board class, so my board class inherits the properties of the boat class and can access the boats that are being used for the game.

## Development
### Adoption and use of good standards 
The main thing I will be doing is writing readable but efficient code, this is really important as a whole function could be written on one line but nobody would understand what the function was doing so this would be a very poor standard to follow. 

I will also have helper methods inside my functions, i.e a function that sets the ship will have a helper function that checks if the space that the ship needs to go is free.

I should also try and avoid hard coding as the amount of ships may change and the size of the board.

When reading through my code I should also be mindful of code smells, this could indicate that my code needs to be refactored, if a function is getting too large or if im repeating lines these are indications that my code needs to be refactored.

### Phase 1 development 
tasks, code review and changes 

Epic - Getting data from the config file and set-up of the board

Task - Using file stream to read from the adaship_config and validate whether or not the line contains a the board details before writing those variables to a variable to be used in creating a 2d vector which will be how I hold the state of the board.
Code review: The comments made said I should access the fstream and get the board configuration from a helper function as the constructor was becoming too large.
Changes: I put  the config into a helper function to be called by the constructor, once the member variable for the board had been set up I knew how large the board needed to be before creating the 3d vector.

Epic - Take users input and output a coordintate
Task - Using isdigit and isalpha functions to break the input string into two strings of numbers and letters, once ive done this I can convert them seperately into coordinates for the board. I worked out that char can also be converted into a number, these numbers were always 65 characters larger than the coordinate that they were referring to so I used this to work out the coordinate from the letter dynamically.
Code review: I had not implemented a way to take in two letters for the coordinate.
Changes: the changes that needed to be made from the code review will be implemented during the next implementation of the board resizing.

Epic - Placing the boats
Task - Using file stream to read from the adaship_config and validate whether or not the line contains a boat before writing those variables to a struct and placing them in a vector.
Task - How to figure whether there was a boat intersecting the boat I am currently placing or if its partly off the board. I figured out that I needed to loop through and check the coordinates of the whole ship before actually placing it as I was getting partly placed ships. 

Epic - Game play setup - turn based play and when the game has ended
Task - Set up functions to be called to run different game modes
Task - Set up a menu to call these functions from.
Task - Use the random coordinates function to create the computer game play
Code Review Changes - I should create a menu function to call for the user to shoot the ships.
Changes: I broke out the computer shoot and player shoot functions as putting them together was confusing, it was a good idea to break them out though as I can now use them in other game mode functions.

Epic - Configurable board, changing how the coordinates are inputted to take excel style x coordinates
Task - outputting the board dynamically
Task - Taking in larger coordinates ie AA and BA 
Code Review - change the name of the variable used to change the letter coordinates into number ones as its a bit confusing what I was doing with the variable 
Changes - I changed the variable to be called 'convertCharToCoord'
Epic - Salvo mode
Epic - Unlimited additional boats
Epic - Hidden mines
Epic - Improved computer targeting


### Ensuring quality through testing and resolving bugs
### Reflection on key design challenges innovations and how I solved them





## Evaluation
### Analysis with embedded examples of key code refactoring, reuse, smells
### Implementation and effective use of advanced programming principles (with examples)
### Features showcase and embedded innovations (with examples) oppportunity to highlight best bits
### Improved targetting algorithm - research, design, implementation and tested confirmation with examples
### Relfective review, opportunies to imporve and continued professional development
