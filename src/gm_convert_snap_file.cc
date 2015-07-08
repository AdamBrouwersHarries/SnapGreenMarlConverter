#include "gm_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <assert.h>
#include <sys/time.h>
#include <fstream>


using namespace std;

vector< pair<node_t, node_t> > parse_adjacency_file(char* filename){
  ifstream adjFile(filename);
  vector< pair<node_t, node_t> > adjVector;
  pair<node_t, node_t> temp;
  int source, sink;
  while( adjFile >> source >> sink)
  {
    temp.first = (node_t) source;
    temp.second = (node_t) sink;
    adjVector.push_back(temp);
  }
  return adjVector;
}

node_t max_node(std::vector<pair<node_t, node_t> > list){
  node_t mNode = 0;
  for(std::vector< pair<node_t, node_t> >::iterator it = list.begin(); it!= list.end(); ++it)
  {
    if((*it).first > mNode)
    {
      mNode = (*it).first;
    }
    if((*it).second > mNode)
    {
      mNode = (*it).first;
    }
  }
  return mNode;
}

int main(int argc, char** argv) {
  //super hacky: assume the first input is the source, the second is the output
  char* inFile = argv[1];
  char* outFile = argv[2];
  //get the adjacency lists from the snap file
  vector< pair<node_t, node_t> > adj = parse_adjacency_file(inFile);

  node_t N = max_node(adj)+1;
  
  gm_graph* g = new gm_graph();
  for(node_t i = 0;i<N; i++){
    g->add_node();
  }

  for(std::vector< pair<node_t, node_t> >::iterator it = adj.begin(); it!= adj.end(); ++it)
  {
    node_t from = (*it).first;
    node_t to = (*it).first;
    g->add_edge(from,to);
  }

  g->freeze();
  g->store_binary(outFile);

  delete g;
  return 0;
}