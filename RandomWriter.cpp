/*
 * File: RandomWriter.cpp
 * ----------------------
 * Copyright 2012 Alok K Shukla
 * MNNIT Allahabad
 *
 * RandomWriter : Writes some "random" text in an output file, 
 *                that resembles the input file text.
 * The degree of resemblane depends upon the seed size used for Markov model.
 * Bigger the seed, better the resemblance.
 *
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

/*
 * The datastructure that keeps all possible seeds of provided size
 * and lists of all charcters that follow them.
 */
Map<string, Vector<char> > seeds;

// Input filename, shared between multiple functions.
 string filename;

// Opens the file and get it ready for reading from the beginning.
string getFileReady(ifstream & infile, string prompt="");

// Calculates the file-size
int fileSize(ifstream & infile);

// Fills up the 'seeds' data structure 
void makeModel(ifstream & infile,int n,int size);

/*
 * Returns the most frequently used seed in the input file.
 * Its the character sequence thats written first in output file, to start with.
 */
string mostFrequentSeed();

/*
 * Returns a charcter selected from a string,
 * based on frequency distribution of charcter in the string.
 */
char nextChar(string s);

// Writes in the output file.
void outputFile(ofstream & outfile,string seed,int limit);

int main() {
    ifstream infile;
    
    // Get some working filename.
	while (getFileReady(infile,"Please enter a valid text file name: ")!="success");
    
    int n=getInteger("And, the Markov model# to be used(<=10): ");
    int l=getInteger("How, number of characters to be generated (<=10000): ");
    
    int size=fileSize(infile);
    getFileReady(infile);
    makeModel(infile, n, size);
    
    string outfilename = filename.substr(0,filename.find('.'))+"_extended.txt";
    ofstream outfile(outfilename.c_str());
    
    // Writes the most frequent used word in file to the output file to start with.
    string seed=mostFrequentSeed();
    for (int i=0; i<seed.size(); i++) {
        outfile.put(seed[i]);
    }
    
    
    cout<<"Your output is ready in "<<outfilename<<".\n"<<"And, it looks like following.\n";
    sleep(2);
    outputFile(outfile,seed,l);
	return 0;
}

string getFileReady(ifstream & infile, string prompt){
    if (prompt=="") {
        infile.open(filename.c_str());
        if (infile.is_open()) {
            return "success";
            
        }
        return "failure";
    }
    
    filename=getLine(prompt);
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        infile.clear();
        return "error";
    }
    return "success";
}

int fileSize(ifstream & infile){
    char ch;
    int n=0;
    while (infile.get(ch)) {
        n++;
    }
    infile.close();
    return n;
}


/*
 * Reads file charcter by charcter and 
 * prepare the seeds data structure.
 *
 */
void makeModel(ifstream & infile,int n,int size){
    char ch;
    string s,prev="";
    int temp=n;
    temp++;
    while (size-->0) {
        if (prev=="") {
            while (temp-->0) {
                infile.get(ch);
                s+=ch;
            }        
        }
        else {
            s+=prev;
            infile.get(ch);
            s+=ch;
        }
        prev=s.substr(1);
        seeds[s.substr(0,n)].add(s[n]);
        temp=n;
        s="";
    }
    return;
}

string mostFrequentSeed(){
    int max=0;
    string res;
    foreach(string s in seeds){
        if (seeds[s].size()>=max) {
            max=seeds[s].size();
            res=s;
        }
    }

    return res;
}

char nextChar(string s){
    int n=randomInteger(0, seeds[s].size()-1);
    return seeds[s][n];
}

/*
 * After first seed is written to file,
 * writes the next character that follows the seed, 
 * and is randomly chosen from a set of charcters that follow the seed in the input file.
 * now the seed is updated to choose next charcter to be written in file.
 *
 */

void outputFile(ofstream & outfile,string seed,int limit){
    static int count=0;
    char ch=nextChar(seed);
    while (count++<limit) {
        count++;
        outfile.put(ch);
        cout<<ch;
        seed+=ch;
        
        outputFile(outfile, seed.substr(1),limit);
    }
    return;
}




