#!/usr/bin/env python3
"""Random NxN skyscraper tests + error cases for rush-01."""
import random, subprocess, sys, time

BIN = sys.argv[1] if len(sys.argv) > 1 else "./rush-01"

def vis(line):
    m = c = 0
    for v in line:
        if v > m:
            m, c = v, c + 1
    return c

def clues(g):
    n = len(g)
    cols = [[g[y][x] for y in range(n)] for x in range(n)]
    return ([vis(c) for c in cols] + [vis(c[::-1]) for c in cols]
            + [vis(r) for r in g] + [vis(r[::-1]) for r in g])

def latin(n):
    base = [[(x + y) % n + 1 for x in range(n)] for y in range(n)]
    random.shuffle(base)
    perm = list(range(n)); random.shuffle(perm)
    g = [[r[p] for p in perm] for r in base]
    syms = list(range(1, n + 1)); random.shuffle(syms)
    return [[syms[v - 1] for v in r] for r in g]

def run(arg):
    t = time.time()
    out = subprocess.run([BIN] + ([arg] if arg is not None else []),
                         capture_output=True, text=True, timeout=60).stdout
    return out, time.time() - t

fail = 0
worst = 0
for n in range(1, 10):
    for _ in range(30 if n < 8 else 100):
        c = clues(latin(n))
        out, dt = run(" ".join(map(str, c)))
        worst = max(worst, dt)
        try:
            g = [list(map(int, l.split(" "))) for l in out.splitlines()]
            ok = (len(g) == n and all(sorted(r) == list(range(1, n + 1)) for r in g)
                  and all(sorted(col) == list(range(1, n + 1)) for col in zip(*g))
                  and clues(g) == c and out.endswith("\n"))
        except ValueError:
            ok = False
        if not ok:
            fail += 1
            print("FAIL", n, c, repr(out))
    print(f"n={n} ok")

errors = [None, "", " ", "4 3 2 1", "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2",
          "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2 ", " 4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2",
          "4  3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 a",
          "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", "0 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2",
          "43 2 1 1 2 2 2 4 3 2 1 1 2 2 2", "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4",
          "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1", "4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2"]
for e in errors:
    out, _ = run(e)
    if out != "Error\n":
        fail += 1
        print("FAIL error case", repr(e), repr(out))
out = subprocess.run([BIN, "1 1 1 1", "x"], capture_output=True, text=True).stdout
if out != "Error\n":
    fail += 1; print("FAIL argc=3")
print(f"errors ok, worst time {worst:.2f}s")
print("ALL OK" if not fail else f"{fail} FAILED")
sys.exit(1 if fail else 0)
