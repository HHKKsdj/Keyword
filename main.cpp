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

void exclude () {
    string text,line,str[4]={"//","\"","/*","*/"};
    size_t j=0,k=0,t=0,p[50]={0};
    int i=0,f=0,r=0;
    for (i=0; i<content.size(); i++) {
        line = content[i];
        if (line.find(str[0]) != line.npos) {
            j = line.find("//");
            if (j==0) {
                content.erase(content.begin()+i);
                i--;
            } else {
                text = line.substr(0,j);
                content[i] = text;
            }
        } else if (line.find(str[1]) != line.npos) {
            while ((t=line.find("\"",k)) != line.npos) {
                p[f] = t;
                f++;
                k=t+1;
            }
            p[f] = line.length();
            text = line.substr(0,p[0]);
            for (r=1; p[r]!=0; r+=2) {
                text += line.substr(p[r]+1,p[r+1]-p[r]-1);
            }
            content[i] = text;
        } else if (line.find(str[2]) != line.npos) {
            j = line.find("/*");
            k = line.find("*/");
            
            if (k != line.npos) {
                content[i] = line.substr(0,j);
            } else {
                content[i] = line.substr(0,j);
                i += 1;
                line = content[i];
                while (line.find("*/") == line.npos) {
                    content.erase(content.begin()+i);
                    line = content[i];
                }
                k = line.find("*/")+2;
                content[i] = line.substr(k,line.length()-k);
            }
            
        }
    }
    
}

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

int main(int argc, const char * argv[]) {
    string path,text;
    
    cin>>path;
    
    read(path);
    
    exclude();
    
    for (int i=0; i<content.size(); i++) {
        cout<<content[i]<<endl;
    }
    return 0;
}
