#include "minHeap.h"
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <array>

using namespace std;

minHeap::minHeap(){}
//minHeap::~minHeap(){}
HeapNode::HeapNode(){}
HeapNode::HeapNode(int id2, int pts){
    id = id2;
    total_points = pts;
    left = nullptr;
    right = nullptr;
}
void minHeap::eliminateWeakest(ofstream& outFile){
    outFile << "eliminateWeakest" << endl;
    if(contestants.empty()){
        outFile << "No contestant can be eliminated since the extended heap is empty." << endl;
    }
    else {
        handler.at(contestants.at(0).getID() - 1) = -1;
        outFile << "Contestant <" << contestants.at(0).getID() << "> with current lowest score <" << contestants.at(0).getPoints() << "> eliminated." << endl;
        int tmp_location = contestants.at(0).getLocation();
        contestants.at(0).setLocation(contestants.at(contestants.size() - 1).getLocation());
        contestants.at(contestants.size() - 1).setLocation(tmp_location);
        swap(contestants.at(0), contestants.at(contestants.size() - 1));
        contestants.pop_back();
        percolateDown(contestants.at(0).getLocation());
        fixHandler();
    }
} 
void minHeap::earnPoints(string id, string pts, ofstream& outFile){
    vector<string> ids;
    outFile << "earnPoints <" << id << "> <" << pts << ">" << endl;
    for(int j = 0; j < contestants.size(); j++) {
        stringstream ss;
        ss << contestants.at(j).getID();
        ids.push_back(ss.str());
    }
    if(find(ids.begin(), ids.end(), id) == ids.end())  {
        outFile << "Contestant <" << id << "> is not in the extended heap" << endl;
    }

    for(int i = 0; i < contestants.size(); i++) {
        if(contestants.at(i).getID() == stoi(id)) {
            contestants.at(i).setPoints(contestants.at(i).getPoints() + stoi(pts));
            outFile << "Contestant <" << id << ">'s score increased by <" << pts << "> points to <" << contestants.at(i).getPoints() << ">" << endl;
            percolateDown(0);
            fixHandler();
            break;
        }
    }
}
void minHeap::losePoints(string id, string pts, ofstream& outFile){
    vector<string> ids;
    outFile << "losePoints <" << id << "> <" << pts << ">" << endl;
    for(int j = 0; j < contestants.size(); j++) {
        stringstream ss;
        ss << contestants.at(j).getID();
        ids.push_back(ss.str());
    }
    if(find(ids.begin(), ids.end(), id) == ids.end())  {
        outFile << "Contestant <" << id << "> is not in the extended heap" << endl;
    }
    for(int i = 0; i < contestants.size(); i++) {
        if(contestants.at(i).getID() == stoi(id)) {
            contestants.at(i).setPoints(contestants.at(i).getPoints() - stoi(pts));
            outFile << "Contestant <" << id << ">'s score decreased by <" << pts << "> points to <" << contestants.at(i).getPoints() << ">" << endl;
            percolateDown(0);
            fixHandler(); 
        }
    }
}
void minHeap::showContestants(ofstream& outFile){
    outFile << "showContestants" << endl;
    for(int i = 0; i < contestants.size(); i++) {
        outFile << contestants.at(i);
    }
}

void minHeap::showLocation(string id, ofstream& outFile){
    outFile << "showLocation <" << id << ">" << endl;
    if(stoi(id) >= handler.size()) {
        outFile << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1." << endl;
    }
    else if(stoi(id) <= 0) {
        outFile << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1." << endl;
    }
    else {
        outFile << "Contestant <" << id << ">  stored in extended heap location <" << handler.at(stoi(id) - 1) << ">" << endl;
    }
}
void minHeap::findContestant(string id, ofstream& outFile){
    int ID = stoi(id);
    if((ID - 1) >= handler.size()){
        outFile << "Contestant <" << ID << "> is not in the extended heap." << endl;
    }
    else if((ID - 1) < 0) {
        outFile << "Contestant <" << ID << "> is not in the extended heap." << endl;
    }
    else {
        outFile << "Contestant <" << ID << "> in extended heap with score <" << contestants.at(ID - 1).getPoints() << ">" << endl;
    }
}
void minHeap::showHandles(ofstream& outFile){
    outFile << "showHandles" << endl;
    for(int i = 0; i < handler.size(); i++) {
        if(handler.at(i) < 0) {
             outFile << "There is no Contestant <" << i + 1 << "> in the extended heap: handle[<" << i + 1 << ">] = -1." << endl;
        }
        else {
            outFile << "Contestant <" << i + 1 << ">  stored in extended heap location <" << handler.at(i) << ">" << endl;
        }
    }
}
void minHeap::insertContestant(string id, string pts, int heap_size, ofstream& outFile){
    outFile << "insertContestant <" << id << "> <" << pts << ">" << endl;
    HeapNode contestant;
    contestant.setID(stoi(id));
    contestant.setPoints(stoi(pts));
    contestant.setLocation(contestants.size());
    handler.push_back(contestant.getLocation());
    if(contestants.size() == heap_size) {
        cout << "Contestant <" << id << "> could not be inserted because the extended heap is full" << endl;
    }
    else {
        if(contestants.empty()) {
            contestants.push_back(contestant);
            outFile << "Contestant <" << id << "> inserted with initial score <" << pts << ">" << endl;
            //handler[stoi(id) - 1] = contestant.getLocation();
        }
        else {
            contestants.push_back(contestant);
            outFile << "Contestant <" << id << "> inserted with initial score <" << pts << ">" << endl;
            //handler[stoi(id) - 1] = contestant.getLocation();
            percolateUp(contestant.getLocation());
            fixHandler();
        }
    }
}

void minHeap::fixHandler() {
    for(int i = 0; i < contestants.size(); i++) {
        int current_id = contestants.at(i).getID();
        handler.at(current_id - 1) =  contestants.at(i).getLocation();
    }
}
void minHeap::percolateDown(int index){
    int child = (2 * index) + 1;
    //chiled = index 1
    int pts = contestants.at(index).getPoints();
    while(child < contestants.size()){
        int min = pts; //200
        int minIndex = -1;
        for(int i = 0; i < 2 && (i + child < contestants.size()); i++){
            if(contestants.at(i + child).getPoints() < min) {
                min = contestants.at(i + child).getPoints();
                minIndex = i + child;
                
            }
        }
        if(min == pts){return;}
        else {
            swap(contestants.at(index), contestants.at(minIndex));
            int tmp_location = contestants.at(index).getLocation();
            contestants.at(index).setLocation(contestants.at(minIndex).getLocation());
            contestants.at(minIndex).setLocation(tmp_location);
            swap(index, minIndex);
            child = (2 * index) + 1;
        }
    }
}
void minHeap::percolateUp(int index){
    int parent = (index - 1)/2;
    if(contestants.at(index).getPoints() >= contestants.at(parent).getPoints()) {
        return;
    }
    else {
        swap(contestants.at(index), contestants.at(parent));
        int tmp_location = contestants.at(index).getLocation();
        contestants.at(index).setLocation(contestants.at(parent).getLocation());
        contestants.at(parent).setLocation(tmp_location);
        swap(index, parent);
        percolateUp(parent);
    }
    return;
}

void minHeap::crownWinner(ofstream& outFile){
    outFile << "crownWinner" << endl;
    int index = 0;
    for(int i = 0; i < contestants.size(); i++) {
        if(contestants.size() == 1) {
            break;
        }
        contestants.erase(contestants.begin());
        fixHandler(); 
    }
    outFile << "Contestant <" << contestants.at(0).getID() << "> wins with score <" << contestants.at(0).getPoints() << ">!" << endl;
    //handler[(contestants.at(0).getLocation())];
}
