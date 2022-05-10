
# SnakeGame

Classic Snake game written in C++ to be used in my SnakeAI project.

Arrow keys are used to control the snake, the objective is to eat as much food as you can. Eating food increases the size of the snake.
The game ends when the snake touches the edges of the screen or itself.

![](https://media1.giphy.com/media/CdS8m86amQlVxaMlZJ/giphy.gif?cid=790b7611d8e9b28ee4ef019653d77bdeb45a3e2cc2e8cd85&rid=giphy.gif&ct=g)

## Code

The 40x40 grid is stored as a 2D array. Each index in the array holds one of three values:

![Array is populated with these](https://i.imgur.com/CIQPBTg.jpg)

The snake is stored as a linked list of pairs of integers. Each link in the linked list corresponds to one segment of the snake.
The linked list updates movement by adding a new link at the front of the list (head of snake), and removing the last link (tail of snake).
When food is eaten, the new link is added to the front but the last link is not removed, increasing the overall length of the linked list.

![Linked list example](https://i.imgur.com/cnYFIc0.png)

Every time the game updates, the grid is reset (each index is set to EMPTY). Then we iterate through the linked list and use the coordinates
to plot the snake into the array. The coordinates for the food are also stored and it gets placed into the array as well.

Finally, [SDL2](https://www.libsdl.org/) and [SDL_TTF](https://github.com/libsdl-org/SDL_ttf) are used as the graphics library to display the array and statistics.
