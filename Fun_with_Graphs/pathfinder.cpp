/*
 * pathfinder.cpp
 * Author: Bobby Huang, Lijun Chen
 * Date: 3/2/2015
 *
 * run pathfinder with 4 command-line arguments:
 * first is a text file containing the movie casts
 * second is a lower-case character equal to u or w
 * -"u" means build the graph with un-weighted edges, while "w" means build the graph with weighted edges
 * third is a text file containing pairs of actors for which you will find paths.
 * fourth argument is an output text file containing the shortest path.
 * The function BFSTraverse can calculate the shortest path.
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include <string>
#include "ActorGraph.hpp"

using namespace std;


class privertexPtrComp {
public:
    bool operator()(privertex*& lhs, privertex*& rhs) const {
        return (lhs->cost) > (rhs->cost);
    }
};

int main(int argc, char const *argv[])
{
	if(argc != 5){
		cout<<"command error!\n";
		return 1;
	}
	//build actorGraph
	actorGraph newActorGraph;
	newActorGraph.loadFromFile(argv[1], 0);
	newActorGraph.buildMovieHash();
	newActorGraph.buildActorHash();
	newActorGraph.buildActorIndexHash();
	vector<vertex*> graph = newActorGraph.buildVertexArray();

	//read test pairs of actors
	vector<int> testPair = newActorGraph.loadTestFromFile(argv[3],0);

	//write to reslut file
	ofstream outfile(argv[4]);
	if(!outfile){
		cout<<"File open error!\n";
		return 1; 
	}

	//for unweighted pathfinder
	if(argv[2][0] == 'u'){
		outfile << "(actor)--[movie#@year]-->(actor)--..."<<endl;
		for(int i = 0; i < testPair.size()/2 ;++i){
			vector<int> ans = newActorGraph.BFSTraverse(testPair[2*i], testPair[2*i+1]);
			vector<string> ansString;
			for(int j = 0; j < ans.size(); ++j){
				ansString.push_back(newActorGraph.indexToActor(ans[j]));
			}

			outfile<<'('<<ansString[0]<<')';
			for(int j = 1; j < ansString.size(); ++j){
				outfile<<"--["<<(newActorGraph.actorPairToMovieString(ansString[j-1],ansString[j]))<<']';
				outfile<<"-->("<<ansString[j]<<")";

			}
			outfile<<endl;

		}
	}
	//for weighted pathfinder
	else if(argv[2][0] == 'w'){
		outfile << "(actor)--[movie#@year]-->(actor)--..."<<endl;
		for(int i = 0; i < testPair.size()/2 ;++i){
			vector<int> ans = newActorGraph.Dijkstra(testPair[2*i], testPair[2*i+1]);
			vector<string> ansString;
			for(int j = 0; j < ans.size(); ++j){
				ansString.push_back(newActorGraph.indexToActor(ans[j]));
			}
			outfile<<'('<<ansString[0]<<')';
			for(int j = 1; j < ansString.size(); ++j){
				outfile<<"--["<<(newActorGraph.actorPairToMovieString(ansString[j-1],ansString[j]))<<']';
				outfile<<"-->("<<ansString[j]<<")";
			}
			outfile<<endl;
		}		
	}
	else{
		cout<<"Neither 'w' nor 'u'"<<endl;
	}
	outfile.close();
	return 0;
}

