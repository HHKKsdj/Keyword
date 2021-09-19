//
//  main.cpp
//  Keyword
//
//  Created by HK on 2021/9/16.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>

using namespace::std;

string keyword[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
vector<string> content;

void read (string path) {
    ifstream fp;
    string text;
    
    fp.open(path,ios::in);
    if (!fp.is_open()) {
        cout<<"Error!"<<endl;
        return;
    }
    
    while (getline(fp, text)) {
        content.push_back(text);
    }
    fp.close();
}

void findKeyword () {
    int num = 0;
    string line;
    for (int i = 0; i<content.size(); i++) {
        line = content[i];
        for (int j=0; j<32; j++) {
            size_t fi = line.find(keyword[j], 0);
            while (fi!=line.npos && keyword[j] != "do")
            {
                num++;
                fi = line.find(keyword[j], fi + 1);
            }
        }
    }
    cout<<"total num: "<<num<<endl;
}

void findSwitchCase () {
    int snum = 0,f = -1,cnum[1000]={0};
    string line;
    for (int i = 0; i<content.size(); i++) {
        line = content[i];
        if (line.find("switch") != line.npos) {
            snum += 1;
            f += 1;
        }
        if (line.find("case") != line.npos) {
            cnum[f] += 1;
        }
    }
    cout<<"switch num: "<<snum<<endl;
    cout<<"case num:";
    for (int i = 0; i<=f; i++) {
        cout<<" "<<cnum[i];
    }
    cout<<endl;
}

void findIfElse () {
    
}

int main(int argc, const char * argv[]) {
    int level = 0;
    string path,text;
    
    cin>>path>>level;
    
    read(path);
    
    findKeyword();
    findSwitchCase();
    
    return 0;
}
