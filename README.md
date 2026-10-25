# rush01 — Skyscrapers (42 C Piscine)

Solves the skyscraper puzzle. Bonus: any size from 1x1 to 9x9, not only 4x4.

## Build & run

```sh
cc -Wall -Wextra -Werror ex00/*.c -o rush-01   # or: make
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

```
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
```

Input: one argument, `4 * N` digits separated by single spaces —
column views from the top, column views from the bottom,
row views from the left, row views from the right.
Bad input or no solution prints `Error`.

## Rules kept

- Norminette: all files OK
- Only `write` is used, no `malloc`, no global variables
- No memory leaks (nothing is allocated)

## How it works

- `parse.c` — checks the argument, reads the views, gives every cell
  the values it can still have (a bit mask). A cell at distance `d` from an
  edge with view `c` can't be higher than `N - c + 1 + d`.
- `line.c` — checks if one row or column can still be completed so that both
  of its views are right. Heights are placed from `N` down to `1`, so each
  new tower is seen from the front only if it stands left of all taller ones.
- `check.c` — runs that check for the row and column of one cell.
- `solve.c` — removes every value that can't work, repeats until nothing
  changes, then guesses on the cell with the fewest options and backtracks.

## Tests

```sh
make test
```

Random puzzles from 1x1 to 9x9 plus bad input cases.
