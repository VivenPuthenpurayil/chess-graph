## Leading Question 
Can we use graph-based analysis of chess positions to predict who wins a game of chess? We will construct various graphs based on different chess positions found in various chess games online. These graphs will be built to represent information that one would expect to be important to predicting the result of a chess game. Some examples would be a graph that represents what pieces can attack other pieces, or what pieces can move where, or what pieces are defending pieces of the same color. We will then run various algorithms on these graphs and gather characteristics as a result of these algorithms. Things such as max degree, size, and strongly connected components are basic ideas. We will then see if there is any correlation between these characteristics and which side ends up winning the game. In order to calculate this correlation we can use a neural network or some simpler method. We can also compare our graph-based analysis against a traditional, non graph-based function used by chess engines to analyze a position. It is important to note that we will not be analyzing one large graph, instead many graphs of at most 64 vertices. Roughly based on [this paper] (https://snap.stanford.edu/class/cs224w-2013/projects2013/cs224w-023-final.pdf).

###### Other questions we will look at answering
Do knights perform better in closed positions? and likewise do bishops perform better in open positions? Does the ELO of the player matter when looking for correlation between graph characteristics and game result? How does this compare to traditional positional evaluation functions used by popular chess engines? 



## Dataset Acquisition


## Data Format
We will use a dataset found on lichess that stores gameplay from their website in a pgn game format (a common chess notation system), there are nearly 4 billion chess games here. We only plan to use a subset of this because that will likely be too much data, so we will take 10,000 games from their data found in january 2013 at https://database.lichess.org/. We will define this subset as the first 10,000 games that meet the following conditions: the game does not end in a tie and both elos must be 1500+. Once we process this data into FEN strings, we will then use a script to turn each position into a graph for analysis by our chosen algorithms.


## Data Correction
We will use a python script to parse through the data and clean it from inputs that we don’t want. We will then convert these PGN formatted chess games to FEN formatted games using an online library. We will then check the FEN formatted strings that represent these games for invalid game states (this should be unlikely since these are datasets from real games) and throw out any bad data sets
## Data Storage

##### Position Strings

Position strings are just strings, we only plan to look at one position at a time, so storage of these inside the main application is not a worry. Otherwise, we can use a text file for both the PGN and the FEN strings before we process them. 


##### Graph Implementation

We will use an Adjaceny Matrix, as we are only looking at one position at a time, we do not need to worry about adding or removing verticies. We also are not concerned with the space as our graphs will not be very large, limited by the size of the chess board and amount of pieces in the game. For some types of graphs (listed below), we will need an auxillary data structure to map the pieces to nodes in the graph. 

## Graphs
Instead of analyzing one big graph like most other projects, we will instead analyze many graphs, one representing each position from our dataset. There are two interesting options for how we will represent a position using a graph. These are the Support Graph and the Attack Graph. We might find that it makes sense to analyze these graphs together or separately. We could easily create a union of the two graphs and run the same algorithms on this new graph. Nodes on our graph could be either pieces, or squares on the board, depending on what we find more useful for the type of graph. The generation of these graphs from FEN strings will be a considerable part of our project.

###### Support Graph
The support graph (directed graph) would represent what pieces are defending what other pieces of the same color. Each color would have its own support graph. We would use this graph to compare characteristics of one color against characterisics of the other color.


###### Attack graph
The attack graph would represent what pieces are attacking what other pieces of the opposite color. There would be one attack graph for the entire position.


###### Attack & Support graph
The combination of the two above graphs would better represent the entire position. We would use this graph to attempt to describe the position as a whole. 


###### Control Graph
The control graph, or the mobility graph, would include information about what empty squares each side controls. Analyzing the size of this graph for one side, could tell us how much space that side controls, a common parameter used in traditional position evaluation functions.


###### 

## Algorithms 
We are very much open to ideas of interesting algorithms to run here. We will also study simpler things not found by these algorithms, such as node density, max degree, average degree, and size of the various graphs. We don't know exactly what the output of these algorithms will represent, but the goal is to find if they correlate to who ends up winning the game.
###### Traversals

We will use DFS / BFS to calculate at the very least, the connected components of the graph. We can then expand this to weakly connected and strongly connected components. We can also use disjoint sets to calculate connected components, but im not sure if simply looping over the edges would count as a graph algorithm. 

###### Tarjans Strongly Connected Components.
We can use Tarjan's Algorithm to compute the strongly connnected components of the graph. We hope to run this in linear time with respect to the size of our graph (edges + verticies). The connected components can tell us about the defensiveness of one sides position. The output from this should be a list of nodes that correspond to the strongly connected to components.

##### Eulerian Path Algorithm
We can use a Eulerian Path algorithm on a support graph to locate cycles. We hope to run this in O(E+V) time where e is edges and v is verticies. The output should inform of us powerful defensive structures on the board. This output should also be stored as a list of nodes that correspond to the cycle.

###### Pathfinding Algorithms?
The most interesting use for pathfinding algorithms in our case would be to find a path to the enemy king. This could be an optional algorithm we implement if needed. The length of this path, could tell us something about who wins. Djkstras is our algorithm of choice, because it saves the paths for various end points, not just one. We hope to run it in quadratic time at the worst.

###### MST

The size of the Minimum Spanning Tree of a position could tell us about the openess / closedness of a position. We will attempt to run Prim's algorithm in quadratic time or better, using the implementation with a adjaceny matrix discussed in lecture.

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