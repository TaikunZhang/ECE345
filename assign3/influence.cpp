//INSERTION_SORT ALGORITHM 

#include <cstdlib>
#include <iostream>     
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <set>
#include <limits>
#include <chrono>
#include <boost/heap/priority_queue.hpp>
using namespace std::chrono;
using namespace std;

class node{
public:
    unsigned id;
    double best_time;
    node(const unsigned intersection_id,const double time)
    {
        id = intersection_id;
        best_time=time;
    };
};
class nodeComparator{
public:
    bool operator()(node& lhs,node &rhs)
    {
        return lhs.best_time > rhs.best_time;
    }
};
struct edge{
    bool connected;
    double time;

    edge(const bool connect, const double t){
        connected = connect;
        time = t;
    }
};
struct vertex{
    vector<int> adjacent_nodes;
};


//globals
vector<vector<edge>> graph;
vector<vertex>adjacency_list;
int num_nodes;
double T;
int num_max_influenced;
int num_second_influenced;
int node_max_influence_id;
int node_second_influence_id;
vector<int>marked;

int find_nodes(string filename){
    int max = 0;
    ifstream myfile(filename);
    string line,word;

    if (myfile.is_open()){
        while (!myfile.eof()){
            getline (myfile,line);
            stringstream s(line); 
            int count = 0;
            while (getline(s, word,' ') && count < 2){ 
                count++;
                int node_id = stoi(word);
                if(node_id > max){
                    max = node_id;
                }
            }
        }
    } 
    return max;
}
void dijkstras_mark(int source_id){
    vector<vector<bool>> visited; //check visited for edges
    vector<double> best_times; //best times for relaxation
    vector<int> ids; //reaching ids for current node
    priority_queue <node,std::vector<node>,nodeComparator> pq; //min heap

    visited.resize(num_nodes);
    for(int i = 0; i < num_nodes; ++i){
        visited[i].resize(num_nodes,false);
    }
    best_times.resize(num_nodes,std::numeric_limits<double>::max());
    ids.resize(num_nodes);

    //create source node, set its cost to 0 and push into min heap
    node source(source_id,0);
    best_times[source_id] = 0;
    pq.push(source);

    //bfs search
    while(!pq.empty()){
        node n = pq.top();
        pq.pop();

        int start = n.id;
        int dest;
        for(int i = 0; i < adjacency_list[start].adjacent_nodes.size(); ++i){
            dest = adjacency_list[start].adjacent_nodes[i];
            if(!visited[start][dest]){
                visited[start][dest] = true;
                double traveltime = graph[start][dest].time;
                if(n.best_time + traveltime < best_times[dest]){
                    node newNode(dest,n.best_time + traveltime);
                    best_times[dest] = n.best_time + traveltime;
                    ids[dest] = start;
                    pq.push(newNode);
                }
            }
        }
    }
    //visited all edges
    //int influenced = 0;
    for(int i = 0; i < best_times.size(); ++i){
        if(best_times[i] < T){
           marked[i] = true;
        }
    }
    //return influenced;
}
int dijkstras_spread(int source_id){
    vector<vector<bool>> visited; //check visited for edges
    vector<double> best_times; //best times for relaxation
    vector<int> ids; //reaching ids for current node
    priority_queue <node,std::vector<node>,nodeComparator> pq; //min heap

    visited.resize(num_nodes);
    for(int i = 0; i < num_nodes; ++i){
        visited[i].resize(num_nodes,false);
    }
    best_times.resize(num_nodes,std::numeric_limits<double>::max());
    ids.resize(num_nodes);

    //create source node, set its cost to 0 and push into min heap
    node source(source_id,0);
    best_times[source_id] = 0;
    pq.push(source);

    //bfs search
    while(!pq.empty()){
        node n = pq.top();
        pq.pop();

        int start = n.id;
        int dest;
        for(int i = 0; i < adjacency_list[start].adjacent_nodes.size(); ++i){
            dest = adjacency_list[start].adjacent_nodes[i];
            if(!visited[start][dest]){
                visited[start][dest] = true;
                double traveltime = graph[start][dest].time;
                if(n.best_time + traveltime < best_times[dest]){
                    node newNode(dest,n.best_time + traveltime);
                    best_times[dest] = n.best_time + traveltime;
                    ids[dest] = start;
                    pq.push(newNode);
                }
            }
        }
    }
    //visited all edges
    int influenced = 0;
    for(int i = 0; i < best_times.size(); ++i){
        //time is under T and not marked by top influencer
        if(best_times[i] < T && !marked[i]){
            influenced++;
        }
    }
    return influenced;
}

int dijkstras(int source_id){
    vector<vector<bool>> visited; //check visited for edges
    vector<double> best_times; //best times for relaxation
    vector<int> ids; //reaching ids for current node
    priority_queue <node,std::vector<node>,nodeComparator> pq; //min heap

    visited.resize(num_nodes);
    for(int i = 0; i < num_nodes; ++i){
        visited[i].resize(num_nodes,false);
    }
    best_times.resize(num_nodes,std::numeric_limits<double>::max());
    ids.resize(num_nodes);

    //create source node, set its cost to 0 and push into min heap
    node source(source_id,0);
    best_times[source_id] = 0;
    pq.push(source);

    //bfs search
    while(!pq.empty()){
        node n = pq.top();
        pq.pop();

        int start = n.id;
        int dest;
        for(int i = 0; i < adjacency_list[start].adjacent_nodes.size(); ++i){
            dest = adjacency_list[start].adjacent_nodes[i];
            if(!visited[start][dest]){
                visited[start][dest] = true;
                double traveltime = graph[start][dest].time;
                if(n.best_time + traveltime < best_times[dest]){
                    node newNode(dest,n.best_time + traveltime);
                    best_times[dest] = n.best_time + traveltime;
                    ids[dest] = start;
                    pq.push(newNode);
                }
            }
        }
    }
    //visited all edges
    int influenced = 0;
    for(int i = 0; i < best_times.size(); ++i){
        if(best_times[i] < T){
            influenced++;
        }
    }
    return influenced;
}

void max_influencer(){
    int node_id;
    int max_influenced = 0;
    for(int i = 0; i < graph.size(); i++){
        int influenced = dijkstras(i);
        if(influenced > max_influenced){
            max_influenced = influenced;
            node_id = i;
        }
    }
    num_max_influenced = max_influenced;
    node_max_influence_id = node_id;
}
void second_influencer(){
    int node_id;
    int max_influenced = 0;
    for(int i = 0; i < graph.size(); i++){
        if(i != node_max_influence_id){
            int influenced = dijkstras_spread(i);
            if(influenced > max_influenced){
                max_influenced = influenced;
                node_id = i;
            }
        }
    }
    num_second_influenced = max_influenced;
    node_second_influence_id = node_id;
}
int main(int argc, char* argv[])
{
    ifstream myfile (argv[1]);
    string line,word;
    //final total number of nodes
    num_nodes = find_nodes(argv[1]);
    num_nodes++;
    
    //intialize adjacency matrix for graph
    graph.resize(num_nodes);
    marked.resize(num_nodes,false);
    adjacency_list.resize(num_nodes);
    for(int i = 0; i < num_nodes; ++i){
        graph[i].resize(num_nodes,edge(false,0));
    }

    //create adjacency matrix
    if (myfile.is_open()){
        while (!myfile.eof()){
            getline (myfile,line);
            stringstream s(line);
            int count = 0;
            int start,dest;
            double time;
            while (getline(s, word,' ')){ 
                if(count == 0){
                    start = stoi(word);
                    count++;
                }
                else if(count == 1){
                    dest = stoi(word);
                    count++;
                }
                else{
                    time = stod(word);
                    count++;
                }
            }
            //cout << start << " " << dest << " " << time << endl;
            graph[start][dest].connected = true;
            graph[start][dest].time = time;
            adjacency_list[start].adjacent_nodes.push_back(dest);
        }
    } 

    T = stod(argv[2]);
    //computer top 1 influencer
    high_resolution_clock::time_point t_start1 = high_resolution_clock::now();
    max_influencer();
    high_resolution_clock::time_point t_end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<nanoseconds>(t_end1-t_start1).count();
    cout << "TOP-1 INFLUENCER: " << node_max_influence_id << ", SPREAD: " << num_max_influenced << ", TIME: " << duration1 << " nanosec" << endl;
    

    //computer top 2 influencer
    high_resolution_clock::time_point t_start2 = high_resolution_clock::now();
    dijkstras_mark(node_max_influence_id);
    second_influencer();
    high_resolution_clock::time_point t_end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(t_end2-t_start2).count();
    cout << "TOP-2 INFLUENCER: " << node_second_influence_id << ",  MARGINAL SPREAD: " << num_second_influenced << ", TIME: " << duration2 << " nanosec" << endl;
    // for(int i = 0; i < num_nodes; i++){
    //     for(int j = 0; j < num_nodes; j++){
    //         if(graph[i][j].connected){
    //             if(graph[j][i].connected){
    //                 cout << "i->j: " << graph[i][j].time << " j->i: " << graph[j][i].time << endl;
    //             }
    //         }
    //     }
    // }
    // for(int i = 0; i < adjacency_list.size(); ++i){
    //     cout << "node_id " << i << " adjacent nodes: ";
    //     for(int j = 0; j < adjacency_list[i].adjacent_nodes.size(); ++j){
    //         cout<< adjacency_list[i].adjacent_nodes[j] << " ";
    //     }
    //     cout << " " << endl;
    // }
    return 0;
}