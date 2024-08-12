#include <bits/stdc++.h>
#include <iostream>
using namespace std;

//keywords,operators,relational operators,punctuation symbols,miscellaneous
//regex for identifiers
vector<int> lexAnalyser(string line,vector<vector<string>> db,vector<int> &res) {
  //taking each char one by one and making the tokens
  regex Literal("^[a-zA-Z_][a-zA-Z0-9_]*$");

  string token;
  vector<string> tokens;
  for(char a:line) {
    if(isalnum(a))  token+=a;
    else{
      if(!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
      tokens.push_back(string(1,a));
    }
  }

  for(string token:tokens){
    for(int i=0 ; i<db.size() ; i++){
      if(find(db[i].begin(),db[i].end(),token)!=db[i].end()) {
        res[i]++;
        break;
      }
    }
    if (regex_match(token, Literal)) res[4]++;
  }

  return res;
}

void printRes(vector<int> res){
  cout<<"Lexical Analysis is as follows"<<endl;
  cout<<"Keywords: "<<res[0]<<endl;
  cout<<"Operators: "<<res[1]<<endl;
  cout<<"Relational Operators: "<<res[2]<<endl;
  cout<<"Punctuations: "<<res[3]<<endl;
  cout<<"Literals: "<<res[4]<<endl;
}

int main() {
  ifstream testFile("FSM-hardcoded.cpp");
  string line;

  vector<vector<string>> db(5);
  db[0]={"asm","double","new","switch","auto","else","operator","template","break","enum","private","this","case","extern","protected","throw","catch","float","public","try","char","for","register","typedef","class","friend","return","union","const","goto","short","unsigned","continue","if","signed","virtual","default","inline","sizeof","void","delete","int","static","volatile","do","long","struct","while"};
  db[1]={"+","-","*","%","!","++","--","/","&&","||","&","^","<<",">>","~","=","+=","*=","/=",","};
  db[2]={">","<",">=","<=","==","!="};
  db[3]={",","{","}","(",")","[","]",";",":","->","::","?:","#","'","\\","//","/*","*/","*","&",""};

  vector<int> res(db.size(),0);

  while(getline(testFile,line)) {
    lexAnalyser(line,db,res);
  }
  printRes(res);
}