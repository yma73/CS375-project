We use C++ for codeing and create a makefile to simplify testing.

Our test datasets are in a directory datasets in the unziped folder CS375project, and our outputs will be produced to a directory named output in the unziped folder CS375project.
The outputs of our program is :
	kruskal_linked_list.txt: the results of Kruskal's algorithm with disjoint set implemented by linked list
	kruskal_tree.txt: the results of Kruskal's algorithm with disjoint set implemented by tree
	prim_heap.txt: the results of Prim's algorithm with queue of non-tree nodes implemented by MinHeap 
	prim_array.txt: the results of Prim's algorithm with queue of non-tree nodes implemented by array 

To test our programs, you can:
	make: to compile
	make run: to run with our datasets
	make produce: to compile the graph producer which creates random undirected weighted connected graphs
	./GraphProducer vertice_num edge_num: to create a graph with vertice_num vertices and edge_num edges


You can also modified the makefile to test graphs other than our test datasets 
