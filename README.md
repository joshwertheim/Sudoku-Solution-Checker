# Sudoku-Solution-Checker
Checks a preset (in the source) grid in a certain format (2d array of ints).

Uses posix threads for checking various sections of the grid.

###To compile:
```
gcc -o sudoku sudoku.c -pthread
```

###To run:
```
./sudoku
```


###Note:

It may be buggy and the code likely isn't amazing.. obviously not production quality!! But just a little fun project. Feel free to submit a PR if you find something wrong that I can/should learn from!
