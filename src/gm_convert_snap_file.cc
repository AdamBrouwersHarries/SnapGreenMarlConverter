#include "gm_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <assert.h>
#include <string.h>
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
  struct timeval T1, T2;
  
  char* inFile = argv[1];
  char* outFile = argv[2];
  printf("Converting: %s -> %s\n", inFile, outFile);
  //get the adjacency lists from the snap file
  gettimeofday(&T1, NULL);
  vector< pair<node_t, node_t> > adj = parse_adjacency_file(inFile);
  gettimeofday(&T2, NULL);
  printf("File reading time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);


  node_t N = max_node(adj)+1; //node count
  edge_t M = adj.size(); //edge count

  printf("Found %i Nodes, %i Edges\n", N, M);

  // allocate space for edges, and degree counts
  node_t* src = new node_t[M];
  node_t* dst = new node_t[M];
  edge_t* deg = new edge_t[N];
  memset(deg, 0, sizeof(edge_t) * N);
  
  gm_graph* g = new gm_graph();
  g->prepare_external_creation(N, M);
  gettimeofday(&T1, NULL);
  printf("Reading from vector to dense data.\n");
  //assign to our internal structures
  for(unsigned int i = 0; i<M; ++i) //iterate over edges - should use iterator :/
  {
    src[i] = adj[i].first;
    dst[i] = adj[i].second;
    deg[src[i]]++;
  }

  printf("Setting adjacencies\n");
  //manually manipulate the sparse internal graph format
  //see graph_gen.cc in $GREEN_MARL/apps/output_cpp/gm_graph/src
  g->begin[0] = 0;
  for (node_t i = 1; i <= N; i++) {
    g->begin[i] = g->begin[i - 1] + deg[i - 1];
  } 
  
  printf("Adding edges\n");
  for (edge_t i = 0; i < M; i++) {
    node_t u = src[i];
    node_t v = dst[i];

    edge_t pos = deg[u]--;
    assert(pos > 0);
    g->node_idx[g->begin[u] + pos - 1] = v;  // set end node of this edge
  }
  gettimeofday(&T2, NULL);
  printf("Manipulation time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);

  printf("Storing binary\n");
  gettimeofday(&T1, NULL);
  g->store_binary(outFile);
  gettimeofday(&T2, NULL);
  printf("storing time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);
  printf("Done, freeing memory\n");
  delete g;
  delete[] src;
  delete[] dst;
  delete[] deg;
  return 0;
}