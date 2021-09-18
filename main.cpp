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

using namespace::std;

string keyword[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};

int findKeyword(string line){
    int num = 0;
    for (int i=0; i<32; i++) {

        size_t fi = line.find(keyword[i], 0);
        while (fi!=line.npos && keyword[i] != "do")
        {
            num++;
            fi = line.find(keyword[i], fi + 1);
        }
    }
    return num;
}

int main(int argc, const char * argv[]) {
    int level = 0,keyNum = 0;
    string p,text;
    vector<string> content;
    ifstream fp;
    
    cin>>p>>level;
    
    fp.open(p,ios::in);
    if (!fp.is_open()) {
        cout<<"Error!"<<endl;
        return 1;
    }
    
    while (getline(fp, text)) {
        content.push_back(text);
    }
    fp.close();
    
    for (int i = 0; i<=content.size(); i++) {
        string line = content[i];
//        cout<<line<<endl;
//        cout<<findKeyword(line)<<endl;
        keyNum += findKeyword(line);
    }
    cout<<"total num: "<<keyNum<<endl;

    return 0;
}
