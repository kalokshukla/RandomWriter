/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

Map<string, Vector<char> > seeds;
Map<string, Map<char, int> > final;
string filename;

string promptUserForFile(ifstream & infile, string prompt="");
void printVector(Vector<char> s);
void printMap();
int readFile(ifstream & infile);
void makeModel(ifstream & infile,int n,int size);
void updateMap();

int main() {
    ifstream infile;
	while (promptUserForFile(infile,"Please enter a valid text file name: ")!="success");
    int n=getInteger("And, the Markov model# to be used: ");
    int size=readFile(infile);
    cout<<"*************************"<<size<<"\n";
    
    promptUserForFile(infile);
    //sleep(10);
    //readFile(infile);
    makeModel(infile, n, size);
    updateMap();
    
    printMap();
    printVector(seeds["Sawye"]);
	return 0;
}

void printVector(Vector<char> s){
    cout<<"[";
    foreach(char v in s){
        cout<<" "<<v<<" ";
    }
    cout<<"]"<<endl;
}

void printMap(){
    foreach(string s in final){
        cout<<s<<"-->   [    ";
        foreach(char i in final[s]){
            cout<<"( "<<final[s][i]<<"--"<<i<<" )";
            cout<<"   ";
        }
        cout<<"   ]"<<endl;
    }
    return;
}

string promptUserForFile(ifstream & infile, string prompt){
    if (prompt=="") {
        infile.open(filename.c_str());
        if (infile.is_open()) {
            return "success";
            
        }
        return "xyz";
    }
    filename=getLine(prompt);
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        infile.clear();
        return "error";
    }
    return "success";
}

int readFile(ifstream & infile){
    char ch;
    int n=0;
    while (infile.get(ch)) {
        cout<<ch;
        n++;
    }
    infile.close();
    return n;
}

void makeModel(ifstream & infile,int n,int size){
    char ch;
    string s,prev="";
    int temp=n;
    temp++;
    while (size-->0) {
        //cout<<"I should be \n";
        if (prev=="") {
            while (temp-->0) {
                //cout<<"why am i not here?";
                infile.get(ch);
                //cout<<ch;
                s+=ch;
            }        
        }
        else {
            s+=prev;
            infile.get(ch);
            s+=ch;
        }
        //cout<<s<<" ";
        prev=s.substr(1);
        seeds[s.substr(0,n)].add(s[n]);
        temp=n;
        s="";
    }
    return;
}

void updateMap(){
    foreach(string s in seeds){
        final[s].put(' ',0);
    }
    
    int i=0;
    
    foreach(string s in seeds){
        foreach(char c in seeds[s]){
            final[s][c]++;
        }
        i=0;
    }
}
