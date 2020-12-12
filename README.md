# Donkey Kong

Hi there! This is the repository for my final project for CS211: Fundamentals of Computer Programming II. We were tasked with implementing a video game using the
ge211 game environment in C++, so my partner and I chose to create Donkey Kong. 

# Proposal: Donkey Kong

## Synopsis

### Elements
Our game will have four elements:
- Stationary rectangular platforms that the player can move on top of
- Stationary rectangular ladders which are randomly placed between platforms and allow the player to vertically move to the next platform
- Circular barrels which move across the platform they are in before dropping down to the next one and repeating the process
- The player that moves horizontally or vertically up ladders and is controlled by the user

### Goal
The goal of the user is to bring the player from the bottom platform to the top platform without letting the player touch any of the barrels.

### Gameplay
The player begins in the bottom left corner of the screen, on the bottommost platform. 
The user moves the player by using the arrow keys (left to move left, right to move right, and up to move up the ladder). 
After a random amount of seconds, a barrel is placed on the leftmost corner of the top platform and moves down the platforms accordingly. 
The player attempts to reach the top platform by going up the ladders while also avoiding getting hit by the barrels by jumping (which the user can do by pressing the space bar).   

## Functional requirements

1. The platforms will alternate between having holes at the right end or the left end of the platform.
2. There will only be one ladder leading to the winning platform. 
3. A barrel will be generated randomly.
4. A barrel can only move between platforms by falling through the holes at the left or right end of the platform.
5. The player will only have 3 lives. 
6. When the player reaches the topmost platform, the barrels and the player stop moving and the player wins.
7. The player can only move up platforms using the ladders and cannot move down ladders.
8. Once the user places the player within a ladder and clicks the up arrow key, the player will go all the way up to the next platform automatically. 
9. There will be constant gravity on the player, such as when they jump or fall through holes.
10. Barrels are destroyed when they reach the bottom right of the window.
11. When a barrel hits a player, they die and are reset to where they first started.
12. The player cannot leave the screen. 

## Open questions
- How do we add unique sprites?
- How do we implement animations?
- How do we animate the player to have it run?
- Which dimensions and velocities would work best?
- Since the special barrels “track” the player, should we make the special barrels keep track of which level they are on within the class? Should we make special barrels in a different class than the normal barrels?


