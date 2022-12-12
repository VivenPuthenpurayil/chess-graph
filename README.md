# Chess graph
https://snap.stanford.edu/class/cs224w-2013/projects2013/cs224w-023-final.pdf

## Preprocess Tutorial

  preprocess.py [infile] [outfile] --evaluation

  Example:

  ```python3 code/src/scripts/preprocess.py --no-evaluation "data/lichess_2013.pgn" 'output.txt'```

## Code
Once you are in the chess-graph directory to run the code you need to run this in your terminal

```
cd code
mkdir build
cd build
cmake ..
make
```

To run the main file you can do
```
./main
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

## Documents
Our signed team contract, our project description file, and our dev logs will be here along with other documents

## Feedback
Any feedback received from the mentor will be in this folder
