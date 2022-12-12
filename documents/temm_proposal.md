## Leading Question 
We will construct a graph to represent a chess board to come up with predictors on which side would win based on the data received from numerous chess games online. We will use the positional dominance that each side has, by creating a control graph that reflects how each square of the board is controlled by the pieces on each side, and these nodes would be connected by the movement abilities of the pieces that occupy a given square. We will evaluate the graph based on the following predictors to help predict which side will win the game

1.  Evaluating Strongly connected components. Using the Tarjans Connected Components algorithm the code base will return the side with the largest set of connected pieces/squares that could represent a players positional dominance/defensive prowess

2.  Cycles. Using a Eulerian Path Algorithm we hope to find powerful cycles that can represent defensive fortresses in a chess match that could also help predict winners based on the defensiveness of the position.

3.  (If time permits)  Betweeness Centrality. Using a Brandes Algorithm, we will compare the centrality of different. This could give us a predictor that could compare how many different choices and moves each side have.

4. (If time permits) Combining Predictors. We hope if time permits to create a model that can utilize multiple predictors to get a more accurate prediciton of which side is winning in a given moment. (We could also look into a machine learning algorithm to evaluate instead since we have a lot of data).

###### Other questions we will look at answering (Optional)
Do knights perform better in closed positions? and likewise do bishops perform better in open positions? Does the ELO of the player matter when looking for correlation between graph characteristics and game result? How does this compare to traditional positional evaluation functions used by popular chess engines? 



## Dataset Acquisition


## Data Format
We will use a dataset found on lichess that stores gameplay from their website in a pgn game format (a common chess notation system), there are nearly 4 billion chess games here. We only plan to use a subset of this because that will likely be too much data, so we will take 10,000 games from their data found in january 2013 at https://database.lichess.org/. We will define this subset as the first 10,000 games that meet the following conditions: the game does not end in a tie and both elos must be 1500+. Once we process this data into FEN strings, we will then use a script to turn each position into a graph for analysis by our chosen algorithms.


## Data Correction
We will use a python script to parse through the data and clean it from inputs that we don’t want. We will then convert these PGN formatted chess games to FEN formatted positions using a python library. We will then check the FEN formatted strings that represent these games for invalid game states (this should be unlikely since these are datasets from real games) and throw out any bad data sets. We will choose games of at least 20 moves, and then take the 20th position to analyze. The 20th position will tend to be the most complex and interesting to analyze. We are hoping our graph based approach will lead to interesting, non-obvious results upon analyzing more complicated positions.
## Data Storage

##### Position Strings

Position strings are just strings, we only plan to look at one position at a time, so storage of these inside the main application is not a worry. Otherwise, we can use a text file for both the PGN and the FEN strings before we process them. 


##### Graph Implementation

We will use an Adjaceny Matrix, as we are only looking at one position at a time, we do not need to worry about adding or removing verticies. We also are not concerned with the space as our graphs will not be very large, limited by the size of the chess board and amount of pieces in the game. For some types of graphs (listed below), we will need an auxillary data structure to map the pieces to nodes in the graph. 

## Graphs
We are planning on creating one big graph which we are going to call the control graph. In this control graph we are planning on have it be composed of 64 nodes each representing a spot on the board. The way we are going to generate these graphs is from FEN strings will be a considerable part of our project.


###### Control Graph (directed graph)
The control graph, or the mobility graph, would include information about what empty squares each side controls. Analyzing the size of this graph for one side, could tell us how much space that side controls, a common parameter used in traditional position evaluation functions. Each vertex in this graph would represent a square, and each edge (directed) would point from a square where a piece is, to a square that that piece can move to. As a result of this implementation, we would also be able to extrapolate other useful metrics such as which pieces can defend/attack others.


###### 

## Algorithms 
We are very much open to ideas of interesting algorithms to run here. We will also study simpler things not found by these algorithms, such as node density, max degree, average degree, and size of the various graphs. We don't know exactly what the output of these algorithms will represent, but the goal is to find if they correlate to who ends up winning the game.


###### Tarjans Strongly Connected Components.
We can use Tarjan's Algorithm to compute the strongly connnected components of the graph. We hope to run this in linear time with respect to the size of our graph (edges + verticies) giving us a time complexity of O(E+V) where E os edges and V is vertices. The connected components can tell us about the defensiveness of one sides position. The output from this should be a list of nodes that correspond to the strongly connected to components. The input for this graph would be the control graph by itself.

###### Eulerian Path Algorithm
We can use a Eulerian Path algorithm on a control graph to locate cycles, which could represent . We hope to run this in O(E+V) time where e is edges and v is verticies. The output should inform of us powerful defensive structures on the board. This output should also be stored as a list of nodes that correspond to the cycle. 

###### Brandes Algorithm? (Optional)
If time permits we could use the Brandes Algorithm which would use the control graph as an input. It's output would be a float that corresponds to each node that tells about its centrality. Its run time would hopefully, O(nm + n2logn) where n is vertices and m is edges. This data would tell us about the openess and closedness of a position.

## Timeline

###### Minimum Product
Week 1 - Convert PGN data to FEN. (Python) (separate script)
Weeks 1 and 2 - Convert FEN to graph representation. (C++) (main)
Week 3 - Graph implementation. (C++) (main)
Week 4 - Implement graph algorithms. (C++) (main)
Week 5 - Analyze corellation between graph characteristics and game result.
###### Optional

TBD - Graphical representation of position.
TBD - Compare graph characteristics winning correllation across different ELOs.
TBD - Begin to look at how graphs evolve over the course of a game, rather than just a snapshot of one position.