/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.


 * Side Note: I used a CPP file for every implementation detail,
 * Including helper functions, structs, includes, etc.
 * Using a header file could make this process easier, but it would undermine my intent
 * Of encapsulating the implementation details and 
 * Providing only necessary functions to the client without exposing how the program works.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include "hashmap.h"
#include <limits>
using namespace std;


/*						SHORTEST PATH IMPLEMENTATION						   */
/******************************************************************************/


/* 
 * Structure: Cell
 * ------------------------------------------------------
 * Object of Cell contains location of current node, its parent node, accumulated cost/distance and color.
 * It has two constructors, where the second one initializes node, parent, sets distance to 0.0 and color to gray.
 * Using structure is a convenient way of storing data compared to variables. My choice doesn't slow down the program
 * and is fairly efficient.
 */
struct Cell {

	Loc node;
	Cell* parent;		// Points to the previous node

	double distance;
	Color color;

	Cell() {}

	Cell(Loc newNode) {			// Makes possible to pass an argument of type Loc (For fast initialization)
		node = newNode;

		parent = NULL;

		distance = 0.0;
		color = GRAY;
	}

};

/* Function prototypes */
void exploreNeighbors(Cell*, TrailblazerPQueue<Cell*>&, Grid<Cell>&, Grid<double>&, Loc, double(Loc, Loc, Grid<double>&), double(Loc, Loc, Grid<double>&));
void checkNeighbor(Cell*, Cell*, double, double, TrailblazerPQueue<Cell*>&, Grid<double>&);


/* Function: fillGrid
 * Usage: fillGrid(cellGrid);
 * ---------------------------------------------
 * As the name suggests, this function takes a Grid of Cells as a parameter and fills it with initialized Cells
 */
void fillGrid(Grid<Cell>& cellGrid) {

	for(int row = 0; row < cellGrid.numRows(); row++) {
		for(int col = 0; col < cellGrid.numCols(); col++) {
			
			cellGrid[row][col] = Cell( makeLoc(row, col) );

		}
	}

}

/* Function: getPath
 * Usage: getPath(curr, path);
 * -----------------------------------------------
 * Given Cell pointer and a vector, this function traverses recursively to the first parent node,
 * adds it to the vector and goes back to the child, thus creating a complete path
 */
void getPath(Cell* curr, Vector<Loc>& path) {

	if(curr == NULL) {
		return;
	}

	getPath(curr->parent, path);

	path.push_back(curr->node);

}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, 
						 double costFn(Loc from, Loc to, Grid<double>& world), 
						 double heuristic(Loc start, Loc end, Grid<double>& world)) {

	/* Initialization */
	TrailblazerPQueue<Cell*> cellQueue;
	Grid<Cell> cellGrid(world.numRows(), world.numCols());
	Vector<Loc> path;

	/* Set-up of a grid */
	fillGrid(cellGrid);

	/* First node created and added to the queue */
	Cell startNode(start);
	startNode.color = YELLOW;

	cellQueue.enqueue(&startNode, heuristic(startNode.node, end, world));

	/* Core logic of this algorithm */
	while(!cellQueue.isEmpty()) {

		Cell* curr = cellQueue.dequeueMin();
		curr->color = GREEN;

		colorCell(world, curr->node, curr->color);

		if(curr->node == end) {
			getPath(curr, path);
			break;
		}

		/* Adds neighbors to the queue if curr is not equal to end node */
		exploreNeighbors(curr, cellQueue, cellGrid, world, end, costFn, heuristic);

	}

    return path;

}

/* Function: exploreNeighbors
 * Usage: exploreNeighbors(curr, cellQueue, cellGrid, world, end, costFn, heuristic);
 * -----------------------------------------------------------------------------------
 * Checks all 8 neighbor Cells of a given node.
 * If coordinates are valid, calls helper function 
 */
void exploreNeighbors(Cell* curr, TrailblazerPQueue<Cell*>& cellQueue, Grid<Cell>& cellGrid, Grid<double>& world, Loc end,
					  double costFn(Loc from, Loc to, Grid<double>& world),
					  double heuristic(Loc start, Loc end, Grid<double>& world)) {

	for(int x = -1; x <= 1; x++) {

		for(int y = -1; y <= 1; y++) {

			int row = curr->node.row + x;
			int col = curr->node.col + y;

			if(!world.inBounds(row, col)) {
				continue;
			}

			Cell* neighbor = &cellGrid[row][col];					

			double cost = costFn(curr->node, neighbor->node, world);

		/* When searching in a maze, the cost can be infinite if the direction is diagonall or through a wall.
		 * Adding an if statement neglects such nodes, which makes the search much faster */		
																						/* Idea provided by Discord user Nika13 */ 
			if(cost == numeric_limits<double>::infinity()) {
				continue;
			}


			/* Examines neighbor Cell's characteristics */
			checkNeighbor(curr, neighbor, curr->distance + cost, heuristic(neighbor->node, end, world), cellQueue, world);

		}

	}

}

/* Function: checkNeighbor
 * Usage: checkNeighbor(curr, neighbor, distance, heuristicDistance, cellQueue, world);
 * -------------------------------------------------------------------------------------
 * Based on neighbor's color, this function either ignores(GREEN), adds(GRAY) or updates(YELLOW)
 * Cell's data and Cell itself in the priority queue
 */
void checkNeighbor(Cell* curr, Cell* neighbor, double distance, double heuristicDistance,
				   TrailblazerPQueue<Cell*>& cellQueue, Grid<double>& world) {

	if(neighbor->color == GRAY) {
					
		neighbor->color = YELLOW;
		neighbor->distance = distance;
		neighbor->parent = curr;

		cellQueue.enqueue(neighbor, neighbor->distance + heuristicDistance);
		colorCell(world, neighbor->node, neighbor->color);

	} else if(neighbor->color == YELLOW && neighbor->distance > distance) {

		neighbor->distance = distance;
		neighbor->parent = curr;

		cellQueue.decreaseKey(neighbor, neighbor->distance + heuristicDistance);

	}

}


/*							 MAZE IMPLEMENTATION							   */
/******************************************************************************/


/* Function prototypes */
void storeEdgesAndClusters(TrailblazerPQueue<Edge>&, HashMap<Loc, Loc>&, int, int);
Set<Edge> formSpanningTree(TrailblazerPQueue<Edge>&, HashMap<Loc, Loc>&);

/* Function: createMaze
 * Usage: Set<Edge> s = createMaze(numRows, numCols);
 * -----------------------------------------------------------
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols) {

	/* Stores edges */
	TrailblazerPQueue<Edge> edges;

	/* Stores clusters */
	HashMap<Loc, Loc> clusters;

	/* Fills up pq and hashmap */
	storeEdgesAndClusters(edges, clusters, numRows, numCols);

	/* Returns formed spanning tree */
	return formSpanningTree(edges, clusters);

}

/* Function: formAndStore
 * Usage: formAndStore(edges, clusters, x1, y1, x2, y2, numOfNodes);
 * -----------------------------------------------------------------------
 * Helper of storeEdgesAndClusters's function. Constructs an edge with the given coorditanes.
 * Stores edges into a priority queue and initializes nodes in a hashmap - every node is its own parent
 */
void formAndStore(TrailblazerPQueue<Edge>& edges, HashMap<Loc, Loc>& clusters, int x1, int y1, int x2, int y2, int numOfNodes) {

	/* makeEdge and makeLoc functions defined in a TrailblazerTypes.h, makes code simpler and easier to read */
	Edge last = makeEdge( makeLoc(x1, y1), makeLoc(x2, y2) );

	edges.enqueue(last, randomReal(0, numOfNodes));

	clusters[last.start] = last.start;
	clusters[last.end]   = last.end;

}

/* Function: storeEdgesAndClusters
 * Usage: storeEdgesAndClusters(edges, clusters, numRows, numCols);
 * -----------------------------------------------------------------------
 * The function storeEdgesAndClusters is used to populate a priority queue of edges 
 * And a HashMap of clusters, based on the given number of rows and columns.
 */
void storeEdgesAndClusters(TrailblazerPQueue<Edge>& edges, HashMap<Loc, Loc>& clusters, int numRows, int numCols) {
 
 /* The total number of nodes. Is used for generating random numbers 
  * From 0 to numOfNodes-1, which in fact is total number of edges */
	int numOfNodes = numRows * numCols;
	
	for(int row = 1; row < numRows; row++) {

		for(int col = 1; col < numCols; col++) {

			formAndStore(edges, clusters, row - 1, col - 1, row - 1, col,     numOfNodes);	// Horizontal line

			formAndStore(edges, clusters, row - 1, col - 1, row,     col - 1, numOfNodes);	// Vertical line


			if(col == numCols - 1) {

				formAndStore(edges, clusters, row, col,     row - 1, col, numOfNodes);	// Outer vertical line

			}

			if(row == numRows - 1) {

				formAndStore(edges, clusters, row, col - 1, row,     col, numOfNodes);	// Outer horizontal line

			}

		}

	}

}

/* Function: getClusterHead
 * Usage: Loc l = getClusterHead(clusters, head);
 * --------------------------------------------------------
 * Helper of formSpanningTree's function. Recursively searches for the cluster head and returns it
 */
Loc getClusterHead(HashMap<Loc, Loc>& clusters, Loc head) {
	
	/* Base case - if head is the cluster head returns result*/
	if(head == clusters[head]) {
		return head;
	}

	/* Passes cluster head as a parameter and continues the recursive call*/
	return getClusterHead(clusters, clusters[head]);

}

/* Function: formSpanningTree
 * Usage: Set<Edge> s = formSpanningTree(edges, clusters);
 * --------------------------------------------------------------
 * This function takes a priority queue and a HashMap as parameters.
 * It forms and returns a spanning tree
 */
Set<Edge> formSpanningTree(TrailblazerPQueue<Edge>& edges, HashMap<Loc, Loc>& clusters) {

	/* stores the edges of the spanning tree */
	 Set<Edge> spanningTree;
	 
	 /* Main logic in spanning tree creation */
	 while(!edges.isEmpty()) {

		Edge e = edges.dequeueMin();

		/* Cluster heads of both endpoints */
		Loc head1 = getClusterHead(clusters, e.start);
		Loc head2 = getClusterHead(clusters, e.end);

		/* If cluster heads are in a different clusters adds an edge to the set */
		if(head1 != head2) {

			clusters[head1] = head2;

			spanningTree.add(e);

		}

	}

	return spanningTree;

}
