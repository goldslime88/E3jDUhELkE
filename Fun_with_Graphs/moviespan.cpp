/*
 * moviespan.cpp
 * Author: Bobby Huang, Lijun Chen
 * Date: 3/12/2015
 *
 * run moviespan with 2 command-line arguments:
 * first is a text file containing the movie casts.
 * second argument is an output text file containing the actors and movies.
 * It returns minimum set of movies that connects all actors/actresses
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "ActorGraph.hpp"
#include "DisjointSets.hpp" 
using namespace std; 

//the struct of movie name and its total number 
// of union sets inside it 
struct movieWNum{
  string movieName;
  int num;
};

//input the string movie@#year
//output the string of movie name
string movieNameReturn(string movieString){
  string ans;
  for(int i = 0; i < movieString.size()-6; ++i){
    ans = ans + movieString[i];
  }
  return ans;
}

int main(int argc, char const *argv[]){ 
  if(argc != 3){ 
    cout<<"command error!\n";
    return 1; 
  }

  //build actorGraph
  actorGraph newActorGraph;
  newActorGraph.loadFromFile(argv[1], 0);
  newActorGraph.buildMovieHash();
  newActorGraph.buildActorHash();
  int index = newActorGraph.buildActorIndexHash();
  disjointSets actorDs(index); 
  set<string> movieOutput; 
  for(int i=0; i<index; i++){ 
    actorDs.add(i);  
  } 
  vector<movieWNum> movieArray;
  unordered_map< string, vector<int> > aMovieHash;
  for(unordered_map< string, vector<string> >::iterator it = (newActorGraph.movieHash).begin(); 
    it != (newActorGraph.movieHash).end(); it++){
    vector<int> temp;
    aMovieHash[it->first] = temp;
    for(vector<string>::iterator iit = (it->second).begin(); iit != (it->second).end(); ++iit){
        aMovieHash[it->first].push_back((newActorGraph.actorIndexHash)[*iit]);
    }
  } 
  unordered_map< string, int> actorIndexHash = newActorGraph.actorIndexHash;
  unordered_set<int> updateSet;
  for(unordered_map< string, vector<int> >::iterator it = aMovieHash.begin(); it != aMovieHash.end(); ++it){
    movieWNum temp;
    temp.movieName = it->first;
    temp.num = (it->second).size();
    movieArray.push_back(temp);
  }
  int count = 0;
  ofstream outfile(argv[2]);
  outfile<<"Actor/Actress\tMovie\tYear"<<endl;
  if(!outfile){
    cout<<"File open error!\n";
    return 1; 
  }

  //pick one movie one at a time
  while(actorDs.numOfSets() > 1){
    vector<movieWNum>::iterator itmaxOne= movieArray.begin();
    for(vector<movieWNum>::iterator it = movieArray.begin(); it != movieArray.end(); ++it){
      if(it->num > itmaxOne->num){
        itmaxOne = it;
      }
    }
    int year = newActorGraph.movieYearHash[itmaxOne->movieName];
    string movieNameR = movieNameReturn(itmaxOne->movieName); 
    vector<string> actorList = newActorGraph.movieHash[itmaxOne->movieName]; 
    for(int i = 0; i < actorList.size(); ++i){   
      outfile<<actorList[i]<<'\t'<<movieNameR<<'\t'<<year<<endl; 
    }   
    vector<int> actorsIn = aMovieHash[itmaxOne->movieName];
    for(int i = 0; i < actorsIn.size(); i++){
      for(int j = i + 1; j < actorsIn.size(); j++){
        actorDs.setUnion(actorsIn[i], actorsIn[j]);     
      }
    }
    movieArray.erase(itmaxOne);
    for(vector<movieWNum>::iterator it = movieArray.begin(); it != movieArray.end(); ++it){
      updateSet.clear();
      unordered_set<int>::iterator itSet;
      vector<int> actorOfMovie = aMovieHash[it->movieName];
      for(int i = 0; i < actorOfMovie.size(); i++){
        int par = actorDs.find(actorOfMovie[i]);
        itSet = updateSet.find(par);
        if(itSet == updateSet.end()){
          updateSet.insert(par);
        }
      }
      it->num = updateSet.size();
    }
  }
  outfile.close();
  return 0;
}
