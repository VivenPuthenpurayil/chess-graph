# Final Written Report

## Leading Question

We want to use and create predictors based on data received from Tarjans, Brandes, Eulerian Circuits, etc. to see if we can predict outcomes of chess games

## Algorithim Overview

### Tarjans

On our directed graph we are finding the strongly connected components (a path exists between every pair of vertices).
<br>
<br>
Input: A graph
<br>
<br>
Output: A vector of integers where the integer at an index corresponds to the strongly connected component (SCC) that node belongs to. For example, if index 3 is 2 and index 27 is also 2 then node 3 and node 27 belong to the same SCC
<br>
<br>
Testing: Started by testing with an empty graph, then kept testing on larger and larger graphs. There were also some specific lowlink tests
<br>
<br>
Results: O(V)

<img width="286" alt="Screenshot 2022-12-12 at 7 29 51 PM" src="https://user-images.githubusercontent.com/31703606/207203867-5aed5b3f-8acb-49e1-aec3-25074cc11c9b.png">

### Brandes
Must calculate the amount of times a given node is a part of the shortest path between two other nodes. This map would give the centrality of each of the pieces, a possible significance for this in chess could be how central each team's piece is, a way to compare this could be to see which side has more centrality, or we could also compare which side has the individual piece with most centrality.
<br>
<br>
Input: A graph
<br>
<br>
Output: Map of vertices to their centrality
<br>
<br>
Testing: Created various model graphs and hand calculated correct centrality, and compared to graph output, also specifically check for interactions with nonconnected components.
<br>
<br>
Run Time of Brandes O(nm + (n^2)(logn))


<img width="297" alt="Screenshot 2022-12-12 at 7 30 20 PM" src="https://user-images.githubusercontent.com/31703606/207203923-ae6a6e08-1c99-45b1-ba6c-12a464370f11.png">

### Eulerian
First we find the weakly connected components (WCC) of the graph. Then we run the eulerian algorithm on each of the weakly connected components to find their respective eulerian cycle (a trail that starts and end at the same vertex using each edge once)
The idea behind using the eulerian algorithim in the scope of chess is to see how the defense works. Initally we thought that more cycles would be better
but through testing we saw that less cycles was better. A possible reason for this is that the pieces have less possible moves.
<br>
<br>
Input: A graph
<br>
<br>
Output: A vector of vectors which contain the eulerian cycle for each of the weakly connected components if they have one
<br>
<br>
Testing: Started testing on graphs with just 1 WCC which was a euler graph and then progressed to a graph with 2+ WCC’s that had euler cycles. After we tested with graphs that had a combination of WCC’s that have and don’t have euler circuits.
<br>
<br>
Runtime for finding WCC: O(V+E)
<br>
<br>
Runtime for Eulerian: O(V+E)


### Results
<img width="797" alt="Screenshot 2022-12-12 at 7 32 14 PM" src="https://user-images.githubusercontent.com/31703606/207204141-90119485-b4cd-4f8f-8c7b-8e46287307aa.png">
