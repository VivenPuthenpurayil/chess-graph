# Chess graph
[Slides](https://docs.google.com/presentation/d/1TfvjVHeO4fC0OuBWD21Kz7FtHWPW0xUsqJKufKUEVmg/edit?usp=sharing) 


[Video](https://www.youtube.com/watch?v=1n9DixM1hq4&ab_channel=AmanSingh)

[Final Report] (https://github.com/VivenPuthenpurayil/chess-graph/blob/main/results.md)

[Inspiration](https://snap.stanford.edu/class/cs224w-2013/projects2013/cs224w-023-final.pdf)

## Preprocess Tutorial

  preprocess.py [infile] [outfile] --evaluation

  Example:

  ```
  python3 code/src/scripts/preprocess.py --no-evaluation "data/lichess_2013.pgn" 'output.txt'
  ```

## Code

### Code Organization

Data of random online chess games:<br>
chess-graph/data/lichess_games.txt<br>

Data of just carlsen grandmaster games:<br>
chess-graph/data/carlsen_preprocessed.txt<br>

Script to process the data:<br>
chess-graph/code/src/scripts/preprocess.py<br>

Files which creates our graph from the data:<br>
chess-graph/code/src/position.h<br>
chess-graph/code/src/graph_generator.h<br>
chess-graph/code/src/graph.h<br>

File which houses our Brandes, Eulerian, and Tarjans algorithim:<br>
chess-graph/code/src/graph_algorithms.h<br>

File that creates the visualization of the chess board<br>
chess-graph/code/src/visualizer.h<br>

Output of the visualization:<br>
chess-graph/output<br>

Test files located here<br>
chess-graph/code/tests<br>

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
