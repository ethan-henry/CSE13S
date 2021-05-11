INFER ERRORS:
	NULL_DEREFERENCE in stack.c on line 10 and 27
Commands:
	run program: ./pathfinder

Arguments:
	-m prints the matrix
	-u sets the graph to an undirected matrix
	-d sets the graph to a directed matrix
	-i declares the input
		requires an input of a text file
Defaults:
	if no -i is provided, takes values from stdin
	if no -d or -u is provided, defaults to -u

Purpose:
	The purpose of this file is to take in pairs of letters that represent junctions in a maze
	the program will take these, create a matrix and return all possible paths, including the 
	length of the shortest path, how many paths are the shortest, and the total number of paths
	found
