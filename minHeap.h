#ifndef _HEAP_h
#define _HEAP_h

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>


using namespace std;



class HeapNode {
    public:
        HeapNode(int id, int total_points);
        HeapNode();
        int getID(){return id;}
        int getPoints(){return total_points;}
        int getLocation(){return loc;}
        HeapNode * getLeft(){return left;}
        HeapNode * getRight(){return right;}
        void setID(int id2){id = id2;}
        void setPoints(int pts){total_points = pts;}
        void setLocation(int location){loc = location;}
        void setLeft(HeapNode * l){left = l;}
        void setRight(HeapNode * r){right = r;}
        friend ostream& operator<<(ostream& os, const HeapNode& node){
            os << "Contestant <" << node.id << "> in extended heap location <" << node.loc << "> with score <" << node.total_points << ">" << endl;
            return os;
        }
    private:
        int id;
        int total_points;
        int loc;
        HeapNode * left;
        HeapNode * right;
};

class minHeap {
    public:
        minHeap();
        void eliminateWeakest(ofstream& out); //remove top (lowest score)
        void earnPoints(string id, string pts, ofstream& out);
        void losePoints( string id, string pts, ofstream& out);
        void showContestants(ofstream& out);
        void showLocation(string id, ofstream& out);
        void showHandles(ofstream& out);
        void findContestant(string id, ofstream& out);
        void insertContestant(string id, string pts, int size, ofstream& out);
        void percolateDown(int index);
        void percolateUp(int index);
        void crownWinner(ofstream& out);
        void fixHandler();
        void setSize(int s){size = s;}
        int getSize(){return size;}
        //add rest of functions

    private:
        vector<HeapNode> contestants;
        int size;
        vector<int> handler;
        
};

#endif