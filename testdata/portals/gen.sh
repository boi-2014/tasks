#!/bin/bash

alias python='pypy' # (faster, but optional)

mkdir -p tests
OUT=tests # output directory

# Subtask 1 (20 points): 1 <= R <= 10, 1 <= C <= 10
cp manual/sample.txt                      $OUT/task.1-01p.in  # sample
cp manual/single-line.txt                 $OUT/task.1-02.in   # single line, no portal usage
cp manual/walking.txt                     $OUT/task.1-03.in   # no portal usage
cp manual/crossing.txt                    $OUT/task.1-04.in   # crossing of portal paths
python gen-maze.py 10 10 1 0 1           >$OUT/task.1-05.in   # long path
python gen-maze.py 10 10 1 20 6          >$OUT/task.1-06.in   # labyrinth with some freedom
python gen-maze.py 10 10 1 25 8          >$OUT/task.1-07.in   # another one
python gen-maze.py 10 10 1 40 14         >$OUT/task.1-08.in   # a third one
python gen-random.py 10 10 20 0 15       >$OUT/task.1-09.in   # random, some open areas

# Subtask 2 (20 points): 1 <= R <= 50, 1 <= C <= 50
cp manual/single-line.txt                 $OUT/task.2-01.in   # single line, no portal usage
cp manual/walking.txt                     $OUT/task.2-02.in   # no portal usage
python gen-random.py 50 50 30 0 1        >$OUT/task.2-03.in   # sparse random
python gen-empty.py 50 50                >$OUT/task.2-04.in   # large empty areas
python gen-maze.py 50 50 1 0 4           >$OUT/task.2-05.in   # long path
python gen-maze.py 50 50 1 240 11        >$OUT/task.2-06.in   # labyrinth with some freedom
python gen-maze.py 50 50 1 240 16        >$OUT/task.2-07.in   # another one, with a crossing
python gen-maze.py 50 50 1 700 19        >$OUT/task.2-08.in   # labyrinth with even more freedom

# Subtask 3 (20 points): 1 <= R <= 200, 1 <= C <= 200, and every open square has at least one wall adjacent to it
cp manual/single-line.txt                 $OUT/task.3-01.in   # single line, no portal usage
cp manual/walking.txt                     $OUT/task.3-02.in   # no portal usage
python gen-maze.py 200 200 0 0 5         >$OUT/task.3-03.in   # long path
python gen-maze.py 200 200 0 7000 6      >$OUT/task.3-04.in   # labyrinth with some freedom
python gen-maze.py 200 200 0 42000 612   >$OUT/task.3-05.in   # labyrinth with even more freedom

# Subtask 4 (20 points): 1 <= R <= 200, 1 <= C <= 200
cp manual/single-line.txt                 $OUT/task.4-01.in   # single line, no portal usage
python gen-random.py 200 200 30 1 9      >$OUT/task.4-02.in   # fractalish, with a crossing
python gen-random.py 200 200 10000 0 11  >$OUT/task.4-03.in   # dense random
python gen-random.py 200 200 10 0 12     >$OUT/task.4-04.in   # sparse, no portal usage
python gen-empty.py 200 200              >$OUT/task.4-06.in   # large empty areas
python gen-maze.py 200 200 1 0 4         >$OUT/task.4-06.in   # long path
python gen-maze.py 200 200 1 300 7       >$OUT/task.4-07.in   # labyrinth with some freedom
python gen-maze.py 200 200 1 3000 7      >$OUT/task.4-08.in   # labyrinth with even more freedom

# Subtask 5 (20 points): 1 <= R <= 1000, 1 <= C <= 1000
cp manual/single-line.txt                 $OUT/task.5-01.in   # single line, no portal usage
python gen-random.py 1000 1000 1200 1 20 >$OUT/task.5-02.in   # fractalish, with a crossing
python gen-random.py 1000 1000 100 0 20  >$OUT/task.5-03.in   # sparse
python gen-random.py 1000 1000 3 0 23    >$OUT/task.5-04.in   # sparse, no portal usage
python gen-empty.py 1000 1000            >$OUT/task.5-05.in   # large empty areas
python gen-maze.py 1000 1000 0 0 10      >$OUT/task.5-06.in   # long path (85k steps) (note: takes quite long to generate)
python gen-maze.py 1000 1000 1 1000 32   >$OUT/task.5-07.in   # labyrinth with some freedom
python gen-maze.py 1000 1000 1 30000 27  >$OUT/task.5-08.in   # labyrinth with even more freedom

# Solutions
g++ -O2 solver.cpp -o solver
for T in $OUT/*.in; do
	./solver <$T >${T%.in}.sol
done
