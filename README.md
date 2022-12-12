# Chess graph
[Slides](https://docs.google.com/presentation/d/1TfvjVHeO4fC0OuBWD21Kz7FtHWPW0xUsqJKufKUEVmg/edit?usp=sharing) 


Video 


[Inspiration](https://snap.stanford.edu/class/cs224w-2013/projects2013/cs224w-023-final.pdf)

## Preprocess Tutorial

  preprocess.py [infile] [outfile] --evaluation

  Example:

  ```
  python3 code/src/scripts/preprocess.py --no-evaluation "data/lichess_2013.pgn" 'output.txt'
  ```

## Code

### Code Organization

Data of random online chess games:
chess-graph/data/lichess_games.txt

Data of just carlsen grandmaster games:
chess-graph/data/carlsen_preprocessed.txt

Script to process the data:
chess-graph/code/src/scripts/preprocess.py

Files which creates our graph from the data:
chess-graph/code/src/position.h
chess-graph/code/src/graph_generator.h
chess-graph/code/src/graph.h

File which houses our Brandes, Eulerian, and Tarjans algorithim:
chess-graph/code/src/graph_algorithms.h

File that creates the visualization of the chess board
chess-graph/code/src/visualizer.h

Output of the visualization:
chess-graph/output

Test files located here
chess-graph/code/tests

### Running Instructions
Once you are in the chess-graph directory to run the code you need to run this in your terminal

```
cd code
mkdir build
cd build
cmake ..
make
```

To run the main file you can do this where the -n flag represents the number of games and the -i flag represents the input file
```
./main -n 100 -i  "../../data/lichess_games.txt"
```

Then to run the test file you can do
```
./test
```

Then to run the visualizer you can do where the -n flag represents the number of games. Once you run that you can go to the output folder and see colored pngs of chess games based on our algorithims

```
./visualizer -n 10
```

## Data
All of the chess data we collect will be located in this folder


Data Source: [Lichess](https://database.lichess.org/)

## Documents
Our signed team contract, our project description file, and our dev logs will be here along with other documents

## Feedback
Any feedback received from the mentor will be in this folder
