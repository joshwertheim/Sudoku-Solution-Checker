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
