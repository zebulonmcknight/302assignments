| N             | Elapsed Time  | Memory Usage   |
|---------------|---------------|----------------|
| 10            | 0.003s        | 86,876         |
| 20            | 0.003s        | 95,684         |
| 50            | 0.005s        | 145,436        |
| 100           | 0.013s        | 308,612        |
| 200           | 0.049s        | 935,252        |
| 500           | 0.316s        | 5,233,220      |
| 1000          | 1.346s        | 20,384,756     |
|---------------|---------------|----------------|

^^^ Honestly I don't even know if this is right, this feels way to fast for how 
little I understood of what I was doing. I did reference some online materials 
though so maybe I'm just cracked. 

I did everything because I did not work with a partner. 

1. I represented the graph as an adjacency matrix. Specifically a vector <vector<int>> 
where each element matrix[i][j] was the weight of that node. I also used a a priority 
queue which stored nodes as tuples (cost, x, y).

2. Because I used a priority queue to find the lowest cost nodes, my implementation 
should be O(n logn) where n is the number of tiles (rows * columns). I also didn't 
process the cost or the parents of nodes I didn't need to visit, so this should keep 
complexity down. 

3. I think my program scaled very well, especially in terms of time. Compared to 
the results I've heard others get the run time for even a 1000 * 1000 graph is very
fast. Memory however scaled somewhat poorly. This is probably because I combined 
multiple implementations and am thus using multiple containers in my Dijkstras function. 
This means the same data is technically stored multiple times in an inefficient manner. 
You can see based off of my benchmarks that memory is scaling exponentially faster than
time. 
