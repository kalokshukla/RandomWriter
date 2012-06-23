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
string filename;
void printVector(Vector<char> s);

void printVector(Vector<char> s){
    cout<<"[";
    foreach(char v in s){
        cout<<" "<<v<<" ";
    }
    cout<<"]"<<endl;
}

void printMap(){
    foreach(string s in seeds){
        cout<<s<<"-->";
        printVector(seeds[s]);
    }
    return;
}

string promptUserForFile(ifstream & infile, string prompt=""){
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
    printMap();
    printVector(seeds["Sawye"]);
	return 0;
}
