#!/bin/bash

alias python='pypy' # (faster, but optional)

mkdir -p tests
OUT=tests # output directory

rm -rf tests/*

# Subtask 1 (20 points): 1 <= R <= 10, 1 <= C <= 10
cp manual/sample.txt                      $OUT/portals.01p-1245.in  # sample
cp manual/single-line.txt                 $OUT/portals.02-12345.in   # single line, no portal usage
cp manual/single-column.txt               $OUT/portals.03-12345.in   # single column, no portal usage
cp manual/walking.txt                     $OUT/portals.04-12345.in   # no portal usage
cp manual/crossing.txt                    $OUT/portals.05-1245.in   # crossing of portal paths
python gen-maze.py 10 10 1 0 1           >$OUT/portals.06-12345.in   # long path
python gen-maze.py 10 10 1 20 6          >$OUT/portals.07-1245.in   # labyrinth with some freedom
#python gen-maze.py 10 10 1 25 8          >$OUT/portals.07-1245.in   # another one
python gen-maze.py 10 10 1 40 14         >$OUT/portals.07-1245.in   # a third one
python gen-random.py 10 10 20 0 15       >$OUT/portals.08-1245.in   # random, some open areas

# Subtask 2 (20 points): 1 <= R <= 50, 1 <= C <= 50
python gen-random.py 50 50 30 0 1        >$OUT/portals.10-245.in   # sparse random
python gen-empty.py 50 50                >$OUT/portals.11-245.in   # large empty areas
python gen-maze.py 50 50 1 0 4           >$OUT/portals.12-245.in   # long path
#python gen-maze.py 50 50 1 240 11        >$OUT/portals.13-245.in   # labyrinth with some freedom
python gen-maze.py 50 50 1 240 16        >$OUT/portals.13-245.in   # another one, with a crossing
python gen-maze.py 50 50 1 700 19        >$OUT/portals.14-245.in   # labyrinth with even more freedom

# Subtask 3 (20 points): 1 <= R <= 200, 1 <= C <= 200, and every open square has at least one wall adjacent to it
python gen-maze.py 200 200 0 0 5         >$OUT/portals.15-345.in   # long path
python gen-maze.py 200 200 0 7000 6      >$OUT/portals.16-345.in   # labyrinth with some freedom
python gen-maze.py 200 200 0 42000 612   >$OUT/portals.17-345.in   # labyrinth with even more freedom

# Subtask 4 (20 points): 1 <= R <= 200, 1 <= C <= 200
python gen-random.py 200 200 30 1 9      >$OUT/portals.18-45.in   # fractalish, with a crossing
python gen-random.py 200 200 10000 0 11  >$OUT/portals.19-45.in   # dense random
python gen-random.py 200 200 10 0 12     >$OUT/portals.20-45.in   # sparse, no portal usage
python gen-empty.py 200 200              >$OUT/portals.21-45.in   # large empty areas
python gen-maze.py 200 200 1 0 4         >$OUT/portals.22-45.in   # long path
python gen-maze.py 200 200 1 300 7       >$OUT/portals.23-45.in   # labyrinth with some freedom
python gen-maze.py 200 200 1 3000 7      >$OUT/portals.24-45.in   # labyrinth with even more freedom

# Subtask 5 (20 points): 1 <= R <= 1000, 1 <= C <= 1000
python gen-random.py 1000 1000 1200 1 20 >$OUT/portals.25-5.in   # fractalish, with a crossing
python gen-random.py 1000 1000 100 0 20  >$OUT/portals.26-5.in   # sparse
python gen-random.py 1000 1000 3 0 23    >$OUT/portals.27-5.in   # sparse, no portal usage
python gen-empty.py 1000 1000            >$OUT/portals.28-5.in   # large empty areas
python gen-maze.py 1000 1000 0 0 10      >$OUT/portals.29-5.in   # long path (85k steps) (note: takes quite long to generate)
python gen-maze.py 1000 1000 1 1000 32   >$OUT/portals.30-5.in   # labyrinth with some freedom
python gen-maze.py 1000 1000 1 30000 27  >$OUT/portals.31-5.in   # labyrinth with even more freedom



# large empty areas, need to visit most of cells
python gen-empty2.py 200 200             >$OUT/portals.32-45.in
python gen-empty2.py 1000 1000           >$OUT/portals.33-5.in

# failing with Dijkstra finished too early
cp manual/empty.txt                      $OUT/portals.34-1245.in  # sample
python gen-pikc.py 50 50                >$OUT/portals.35-245.in
python gen-pikc.py 1000 1000            >$OUT/portals.36-5.in

# very long path
python gen-zigzag.py 50 50              >$OUT/portals.37-2345.in
python gen-zigzag.py 200 200            >$OUT/portals.38-345.in
python gen-zigzag.py 1000 1000          >$OUT/portals.39-5.in

python gen-snake.py 1000 1000           >$OUT/portals.40-5.in

# Solutions
g++ -O2 solver.cpp -o solver
for T in $OUT/*.in; do
	echo $T
	./solver <$T >${T%.in}.sol
done
