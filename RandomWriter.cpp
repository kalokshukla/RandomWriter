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
Map<string, Map<char, double> > ultimate;
string filename;

string promptUserForFile(ifstream & infile, string prompt="");
void printVector(Vector<char> s);
void printMap();
int readFile(ifstream & infile);
void makeModel(ifstream & infile,int n,int size);
void updateMap();
string mostFrequentSeed();
void outputFile(ofstream & outfile,string seed,int limit);
char nextChar(string s);

int main() {
    ifstream infile;
    ofstream outfile("output.txt");
    
	while (promptUserForFile(infile,"Please enter a valid text file name: ")!="success");
    int n=getInteger("And, the Markov model# to be used: ");
    int l=getInteger("How, many characters approximately do you want to generate? ");
    int size=readFile(infile);
    //cout<<"*************************"<<size<<"\n";
    
    promptUserForFile(infile);
    //sleep(10);
    //readFile(infile);
    makeModel(infile, n, size);
    updateMap();
    
    //printMap();
    //cout<<"\nMost frequently used "<<n<<" letter sequence in "<<filename<<" is "<<"\""<<mostFrequentSeed()<<"\""<<endl;
    //printVector(seeds["Sawye"]);
    string seed=mostFrequentSeed();
    for (int i=0; i<seed.size(); i++) {
        outfile.put(seed[i]);
    }
    outputFile(outfile,seed,l);
    cout<<"Your output is ready in output.txt\n";
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
        //cout<<ch;
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

string mostFrequentSeed(){
    int count=0,max=0;
    string res;
    foreach(string s in final){
        count=0;
        foreach(char i in final[s]){
            count+=final[s][i];
        } 
        foreach(char i in final[s]){
            ultimate[s][i]=double(final[s][i])/double(count);
        }
        if (count>=max) {
            max=count;
            res=s;
        }
        //cout<<s<<" appeared "<<count<<" times\n";
    }
/*cout<<max<<endl;
    cout<<"[ ";
    foreach(char c in ultimate[res]){
        cout<<"( "<<c<<" --> "<<ultimate[res][c]<<" )";
    }
    cout<<" ]\n";*/
    return res;
}

void outputFile(ofstream & outfile,string seed,int limit){
    static int count=0;
    //cout<<seed<<endl;
    char ch=nextChar(seed);
    //cout<<ch<<endl;
    while (count++<limit) {
        count++;
        
        outfile.put(ch);
        seed+=ch;
        
        outputFile(outfile, seed.substr(1),limit);
    }
    return;
}

char nextChar(string s){
    int n=randomInteger(0, seeds[s].size()-1);
    return seeds[s][n];
}



