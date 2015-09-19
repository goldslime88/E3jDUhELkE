/*
 * ActorGraph.hpp
 * Author: Bobby Huang, Lijun Chen
 * Date: 3/2/2015
 *
 * This file is meant to read the input file format defined in movie_casts.tsv. 
 * Then read pair of actors in test_pairs.tsv. After building several hashtables,
 * we can build the graph actor by methods buildVertexArray() and store the vertexs
 * in the array.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP


#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;


struct vertex 
{
  vector<int> adj; // The adjacency list
  int dist; // The distance from the source
  int index; // The index of this vertex
  int prev; // The index of the vertex previous in the path
  bool done;//The flag of Dijkstra's algorithm
};

struct item
{
  string actorName; 
  string movieTitle;
  string movieYear;
};


struct privertex
{
  vertex* aVertex; 
  int cost;  
};


class actorGraph {
protected:
  //record items from input file.
  vector<item> itemList;

  //store pointer to the vertexs after building graph
  vector<vertex*> vertexArray;

  //store name of actor by the index in array
  vector<string> actorArray;

  //hashtable with key of actor and value of movies belong to this actor
  unordered_map< string, vector<string> > actorHash;

  //hashtable with key of pair of actors and value of movies belong both of them
  unordered_map< string, string > actorPairToMovie;

public:
  actorGraph(void);
  ~actorGraph();
  //these two data structures are set as public for moviespan access
  //hashtable with key of movie and value of actors in that movie
  unordered_map< string, vector<string> > movieHash;

  //hashtable with key of movie and value of the year of movie
  unordered_map< string, int > movieYearHash;

  //hashtable with key of actor and value of index of that actor
  unordered_map< string, int > actorIndexHash;
 
  /* Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
  /* Load the pair from a tab-delimited file of actor-actor relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return actors' index stored in the vector of int
   */
  vector<int> loadTestFromFile(const char* in_filename, bool use_weighted_edges);

  /* Build the hashtable named moviehash
   * return the size of this hashtable
   */
  int buildMovieHash();

  /* Build the hashtable named actorHash
   * return the size of this hashtable
   */
  int buildActorHash();

  /* Build the hashtable named actorIndexHash
   * return the size of this hashtable
   */
  int buildActorIndexHash();

  /* Build the array of pointers to vertex by building graph
   * return this array of vertex
   */
  vector<vertex*> buildVertexArray();

  /* Translate the index of an actor to its name
   * return the string of this actor's name
   */
  string indexToActor(int index);

  /* Build the hashtable named actorPairToMovie
   * return the vector of string that is the movie belong to
   * this pair of actors 
   */
  string actorPairToMovieString(string actor1, string actor2);

  /* reset all the vertexs in this graph
   */
  void reset();

  /* input the index of two actors.
   * return the weight of the edge.
   */

  int getWeight(int index1, int index2);

  /* input the index of start vertex and end vertex.
   * return the array of int to record the shortest 
   * unweighted path.
   */
  vector<int> BFSTraverse(int startPoint, int endPoint);
  
  /* input the index of start vertex and end vertex.
   * return the array of int to record the shortest 
   * weighted path.
   */
  vector<int> Dijkstra(int startPoint, int endPoint);

  
};


#endif // ACTORGRAPH_HPP