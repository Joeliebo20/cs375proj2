#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include "minHeap.h"
#include <algorithm>
#include <array>

using namespace std;

void parseInput(string in_file, string out_file){
    ifstream f;
    ofstream out;
    out.open(out_file);
    f.open(in_file);
    int heap_size;
    string func_call;
    string arg1, arg2;
    string chars = "<>";
    minHeap heap;
    int counter = 0;
    bool go = true;
    while(go) {
        f >> heap_size;
        go = false;
    }
    heap.setSize(heap_size);
    while(f >> func_call) {
        if(func_call == "insertContestant") {
            f >> arg1 >> arg2;
            counter++;
            arg1.erase(remove_if(arg1.begin(), arg1.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg1.end());
            arg2.erase(remove_if(arg2.begin(), arg2.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg2.end());
            heap.insertContestant(arg1, arg2, heap_size, out);
            
        }
        if(func_call == "earnPoints") {
            f >> arg1 >> arg2;
            arg1.erase(remove_if(arg1.begin(), arg1.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg1.end());
            arg2.erase(remove_if(arg2.begin(), arg2.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg2.end());
            heap.earnPoints(arg1, arg2, out);
        }
        if(func_call == "losePoints") {
            f >> arg1 >> arg2;
            arg1.erase(remove_if(arg1.begin(), arg1.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg1.end());
            arg2.erase(remove_if(arg2.begin(), arg2.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg2.end());
            heap.losePoints(arg1, arg2, out);
        }
        if(func_call == "findContestant") {
            f >> arg1;
            arg1.erase(remove_if(arg1.begin(), arg1.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg1.end());
            heap.findContestant(arg1, out);
        }
        if(func_call == "showLocation") {
            f >> arg1;
            arg1.erase(remove_if(arg1.begin(), arg1.end(), [&chars](const char & c) {
                return chars.find(c) != string::npos;
            }), arg1.end());
            heap.showLocation(arg1, out);
        }
        if(func_call == "showContestants") {
            heap.showContestants(out);
        }
        if(func_call == "eliminateWeakest") {
            heap.eliminateWeakest(out);
        }
        if(func_call == "crownWinner") {
            heap.crownWinner(out);
        }
        if(func_call == "showHandles") {
            heap.showHandles(out);
        }
    }
}

int main(int argc, char * argv[]){
    string inputFile(argv[1]);
    string outputFile(argv[2]);
    parseInput(inputFile, outputFile);
}