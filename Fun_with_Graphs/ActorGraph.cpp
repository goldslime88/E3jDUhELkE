/*
 * ActorGraph.cpp
 * Author: Bobby Huang, Lijun Chen
 * Date: 3/2/2015
 *
 * This file is meant to read the input file format defined in movie_casts.tsv. 
 * Then read pair of actors in test_pairs.tsv. After building several hashtables,
 * we can build the graph actor by methods buildVertexArray() and store the vertexs
 * in the array.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include "ActorGraph.hpp"

//the compare function for priority_queue in Dijkstra
class privertexPtrComp {
public:
    bool operator()(privertex*& lhs, privertex*& rhs) const {
        return (lhs->cost) > (rhs->cost);
    }
};

using namespace std;

actorGraph::actorGraph(void) {

    //initial the hashmap for quick build 
    actorPairToMovie.reserve(5000000);

}
actorGraph::~actorGraph(){
  for(int i = 0; i < vertexArray.size(); ++i){
    delete vertexArray[i];
  }
}

/* Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */

bool actorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){
  
  // Initialize the file stream
  ifstream infile(in_filename);
  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;
    
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      
      record.push_back( next );
    }
    
    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }
    
    string actor_name(record[0]);
    string movie_title(record[1]);
    string movie_year(record[2]);
    item newItem;
    newItem.actorName = actor_name;
    newItem.movieTitle = movie_title;
    newItem.movieYear = movie_year;
    itemList.push_back(newItem);
  }
  
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();  
  return true;
}

/* Load the pair from a tab-delimited file of actor-actor relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return actors' index stored in the vector of int
 */

vector<int> actorGraph::loadTestFromFile(const char* in_filename, bool use_weighted_edges){
  
  vector<int> testPair;
  // Initialize the file stream
  ifstream infile(in_filename);
  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;  
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;
    while (ss)
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;     
      record.push_back( next );
    }
    
    if (record.size() != 2)
    {
      // we should have exactly 2 columns
      continue;
    }
    
    //read the name of two actors and store them as indexes
    int startPoint(actorIndexHash[record[0]]);
    int endPoint(actorIndexHash[record[1]]);   
    testPair.push_back(startPoint);
    testPair.push_back(endPoint);
  }
  
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
  }
  infile.close();
  
  return testPair;
}

/* Build the hashtable named moviehash
 * return the size of this hashtable
 */
int actorGraph::buildMovieHash(){

  //combine movietitle and movieyear to the key of moviehash
  for(vector<item>::iterator it = itemList.begin(); it != itemList.end(); ++it){
    string movieKey;
    string actor;
    int year;
    movieKey = it->movieTitle + "#@" + it->movieYear;
    actor = it->actorName;
    year = stoi(it->movieYear);

    unordered_map< string, vector<string> >::iterator itHash = movieHash.find(movieKey);
    unordered_map< string, int >::iterator itMovieYearHash = movieYearHash.find(movieKey);
    if(itHash == movieHash.end()){
      vector<string> temp;
      temp.push_back(actor);
      movieHash[movieKey] = temp;
    }
    else{
      (itHash->second).push_back(actor);
    }
    if(itMovieYearHash == movieYearHash.end()){
      movieYearHash[movieKey] = year;
    }
    else{
    }
  }
  return movieHash.size();
}

/* Build the hashtable named actorHash
 * return the size of this hashtable
 */
int actorGraph::buildActorHash(){

  //combine movietitle and movieyear to the value of actorhash 
  for(vector<item>::iterator it = itemList.begin(); it != itemList.end(); ++it){
    string movieKey;
    string actor;
    movieKey = it->movieTitle + "#@" + it->movieYear;
    actor = it->actorName;
    unordered_map< string, vector<string> >::iterator itHash = actorHash.find(actor);
    if(itHash == actorHash.end()){
      vector<string> temp;
      temp.push_back(movieKey);
      actorHash[actor] = temp;
    }
    else{
      (itHash->second).push_back(movieKey);
    }
  }
  return actorHash.size();
}

/* Build the hashtable named actorIndexHash
 * return the size of this hashtable
 */
int actorGraph::buildActorIndexHash(){
  int index = 0;
  //give each actor an index
  for(vector<item>::iterator it = itemList.begin(); it != itemList.end(); ++it){
    string actor = it->actorName;
    unordered_map< string, int >::iterator itHash = actorIndexHash.find(actor);
    if(itHash == actorIndexHash.end()){
      actorIndexHash[actor] = index;
      index++;
      actorArray.push_back(actor);//
    }
  }
  return actorArray.size();
}

/* Build the array of pointers to vertex by building graph
 * return this array of vertex
 */
vector<vertex*> actorGraph::buildVertexArray(){
  
  for(int i = 0; i < actorArray.size(); i++){
    //initialize the vertex
    vertex *temp;
    temp = new vertex();
    temp->dist = numeric_limits<int>::max();
    temp->index = i;
    temp->prev = -1;
    temp->done = false;
    vertexArray.push_back(temp);
  }
  int numOfEdge = 0;
  for(unordered_map< string, vector<string> >::iterator it = movieHash.begin(); it != movieHash.end(); ++it){ 
    vector<string> actors = it->second;
    for(int i = 0; i < actors.size(); ++i){
      for(int j = 0; j < actors.size(); ++j){        
        if((actors[i]) != (actors[j])){          
          string actorPair, pairMovie;
          if(actorIndexHash[actors[i]] < actorIndexHash[actors[j]]){
            actorPair = actors[i] + actors[j];
          }
          else{
            actorPair = actors[j] + actors[i];
          }
          ((vertexArray[actorIndexHash[actors[i]]])->adj).push_back(actorIndexHash[actors[j]]);
          pairMovie = it->first;
          unordered_map< string, string >::iterator itPair;
          itPair = actorPairToMovie.find(actorPair);
          numOfEdge++;
          if(itPair == actorPairToMovie.end()){
            actorPairToMovie[actorPair] = pairMovie;        
          }
          else{
            if(movieYearHash[pairMovie] > movieYearHash[itPair->second]){
              itPair->second = pairMovie;
            }
          }  
        }
      }
    }
  }
  return vertexArray;
}

/* Translate the index of an actor to its name
 * return the string of this actor's name
 */
string actorGraph::indexToActor(int index){
  return actorArray[index];
}


/* Build the hashtable named actorPairToMovie
 * return the vector of string that is the movie belong to
 * this pair of actors 
 */
string actorGraph::actorPairToMovieString(string actor1, string actor2){
  string tempS;
  if(actorIndexHash[actor1] < actorIndexHash[actor2]){
    tempS = actor1 + actor2;
  }
  else{
    tempS = actor2 + actor1;
  }
  return actorPairToMovie[tempS];
}

/* reset all the vertexs in this graph
 */
void actorGraph::reset(){
  for(int i = 0; i < vertexArray.size(); ++i){
    vertexArray[i]->dist = numeric_limits<int>::max();
    vertexArray[i]->index = i;
    vertexArray[i]->prev = -1;
  }
}

/* input the index of two actors.
 * return the weight of the edge.
 */
int actorGraph::getWeight(int index1, int index2){
  string tempS = actorPairToMovieString(indexToActor(index1), indexToActor(index2));
  return 2016-movieYearHash[tempS];
}

/* input the index of start vertex and end vertex.
 * return the array of int to record the shortest 
 * unweighted path.
 */
vector<int> actorGraph::BFSTraverse(int startPoint, int endPoint){
  queue<vertex*> toExplore;
  vector<int> record;
  vertex* start = vertexArray[startPoint];
  vertex* temp;
  start->dist = 0;
  toExplore.push(start);
  while(!toExplore.empty()){
    vertex* next = toExplore.front();
    toExplore.pop();
    if(next->index == endPoint){
      temp = next;
      break;
    }
    vector<int>::iterator it = next->adj.begin();
    for(;it != next->adj.end(); ++it){
      vertex* neighbor = vertexArray[*it];
      if(neighbor->dist == numeric_limits<int>::max()){
        neighbor->dist = next->dist + 1;
        neighbor->prev = next->index;
        toExplore.push(neighbor);
      }
    }
  }
  while(temp->prev != -1){
    vector<int>::iterator it = record.begin();
    record.insert(it,temp->index);
    temp = vertexArray[temp->prev];
  }
  vector<int>::iterator it = record.begin();
  record.insert(it,startPoint);
  for(int i = 0; i < vertexArray.size(); ++i){
    vertexArray[i]->dist = numeric_limits<int>::max();
    vertexArray[i]->index = i;
    vertexArray[i]->prev = -1;
    }
  return record;
}

/* input the index of start vertex and end vertex.
 * return the array of int to record the shortest 
 * weighted path.
 */
vector<int> actorGraph::Dijkstra(int startPoint, int endPoint){
  vertex* temp;
  vector<int> record;
  std::priority_queue<privertex*,std::vector<privertex*>,privertexPtrComp> pvq;
  vertex* start = vertexArray[startPoint];
  start->dist = 0;
  privertex* newPrivertex = new privertex();
  newPrivertex->cost = 0;
  newPrivertex->aVertex = start;
  pvq.push(newPrivertex);
  while(!pvq.empty()){
    privertex* thePrivertex = pvq.top();
    pvq.pop();
    if((thePrivertex->aVertex)->done == true && (thePrivertex->aVertex)->index == endPoint){
      temp = thePrivertex->aVertex;
      delete thePrivertex;
      break;
    }
    if((thePrivertex->aVertex)->done == false){
      (thePrivertex->aVertex)->done = true;
      if((thePrivertex->aVertex)->index == endPoint){
        delete thePrivertex;
        break;
      }
      vector<int>::iterator it = ((thePrivertex->aVertex)->adj).begin();
      for(;it != ((thePrivertex->aVertex)->adj).end(); ++it){
        int theCost = getWeight((thePrivertex->aVertex)->index, *it);
        //cout<<theCost<<endl;
        if(theCost + (thePrivertex->aVertex)->dist < vertexArray[*it]->dist){
          vertexArray[*it]->dist = theCost + (thePrivertex->aVertex)->dist;
          vertexArray[*it]->prev =  (thePrivertex->aVertex)->index;
          privertex* aPrivertex = new privertex();
          aPrivertex->aVertex = vertexArray[*it];
          aPrivertex->cost = vertexArray[*it]->dist;
          pvq.push(aPrivertex);
        }
      }
    }
    delete thePrivertex;
  }
  
  temp = vertexArray[endPoint];
  while(temp->prev != -1){
    vector<int>::iterator it = record.begin();
    record.insert(it,temp->index);
    temp = vertexArray[temp->prev];
  }
  vector<int>::iterator it = record.begin();
  record.insert(it,startPoint);
  for(int i = 0; i < vertexArray.size(); ++i){
    vertexArray[i]->dist = numeric_limits<int>::max();
    vertexArray[i]->index = i;
    vertexArray[i]->prev = -1;
    vertexArray[i]->done = false;
  }

  while(!pvq.empty()){
    delete pvq.top();
    pvq.pop();
  }
  

  return record;
}





