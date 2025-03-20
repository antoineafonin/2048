# 2048
Game K
Do you know the game 2048? Even though the game was programmed in March 2014 over a weekend by 19-year-old Italian web developer Gabriele Cirulli, it quickly became popular and beloved. If you have missed the craze surrounding the name 2048, don't hesitate and give this game a try. This assignment is, in fact, closer to the game 2048 than it may seem at first glance.

The Game 2048 as We All Know It
The game 2048, as we all know it, is played on a 4x4 grid. The only difference between this game and the original 2048 is that in Game K, instead of numbers on the tiles, you will use letters. The player can move the tiles in four directions (in the original game, using arrow keys, and in our version, using characters or strings loaded from standard input).

Each new move in the game starts by generating a random tile with either the letter 'A' or 'B'. When moving the tiles, they slide as far as possible in the given direction. They can be stopped either by another tile or by the edge of the grid. If two tiles with the same letter meet (touch), they combine into the next letter in the alphabet sequence. For example, if two 'C' tiles meet, they merge into a single 'D' tile. The resulting tile created by merging two tiles cannot combine with any other tile with the same letter during the current move.

The player earns points during the game. The score is updated every time two or more tiles combine during a move. The method for calculating the score is described in a separate part of this text.

The game ends when a tile with the letter 'K' appears on the game board (hence the name of the game).
