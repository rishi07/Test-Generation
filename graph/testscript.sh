input="input"
if [ -d $input ] 
then
	rm -r $input
fi
mkdir $input
g++ undirected_connected_graph.cpp
./a.out
