Title: Car CRush Game

About the game:
we created a fun driving game, the game has a car
which the player controls using the keyboard, and a road map.
we also implemented self-driving cars, that drive around the map.
the player needs to collect money at a specific time,
to win the game.
there are also other gifts on the road the player can collect.

Design:
We designed the project in a very object-oriented way(oop).
the game interface was divided into states, and managed by a StateStack class.
The Application class starts the game, and pushes The TitleState who displays
a nice intro and then pushes the MenuState who can push either the GameState
that starts the actual gameplay, or the HelpState which displays some instructions.

The states have buttons and the text using Gui design.
each state holds a container that can hold Label and Button objects.
all of them derived from the Component class.

The gameplay classes are:
World, Data and Map
World holds the player, the robot drivers, the cars, and the Map
Data holds players data like the money count and the amount of time left etc.  
Map holds the game-map information.

The game contains many Objects all of them derived from Obj class.
Edible
     	-Coin 
     	-GiftTime

Driver
	-Player 
	-RobotDriver 

MovableObj
	-Car	

Joint: joint objects that the self-driving cars recognize and can turn to some directions.
Wall:  the off-road rectangles which we create outside the road to prevent the car from going off the road.
		
We also built a template class ResourseHolder which manages all resources like Sounds, Textures, fonts etc.

CollisionHandling - handles all sort of collision between objects

We use .txt files to specify some data:
robots.txt - the places of the self-driving cars initial positions.
rects.txt - the off-road rectangles which we create outside the road to prevent the car from going off the road.
joints.txt - the joint objects that the self-driving cars recognize and can turn to some directions.
gifts.txt  - the gifts we put on the road.


Databases we have used:
A stack of states to manage all the states of the game.
A map that holds the resources.
A map that holds collision functions.
A few vectors that holds the game objects.


Design patterns We have used:
Multi methods, for collision handling.
Singelton, for having some classes that can have only one object and can be accessed all over the code.
StateStack, to manage game interface divided into states.
Component, for Gui management.
and more.

Algorithms We have used:
We made our own algorithm for self-driving cars.
We also implemented some math for the player driving abilities.

Note to the reviewers:
We worked hard on this project, in a very short time to complete that project (only 3 weeks).
when we designed our game, we had a much bigger game in mind.
thus, we made a design that will suit a very large game with many more elements.
we spent a long time on the math behind the self-driving and driving in general.
unfortunately, the game graphics and effects suffer from the short time and the "big plans".
we hope you will enjoy reviewing it.
have a great day!
