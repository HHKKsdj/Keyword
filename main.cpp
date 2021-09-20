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
#include <stack>

using namespace::std;

string keyword[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
vector<string> content;

void exclude () {
    string text,line;
    size_t j=0,k=0,t=0;
    int i=0,f=0,r=0;
    for (i=0; i<content.size(); i++) {
        line = content[i];
        
        if (line.find("\t") != line.npos && line.find("\t") == 0) {     /*删除行首制表符*/
            do {
                k = line.find("\t")+1;
                line = line.substr(k,line.length()-k);
            } while (line.find("\t") != line.npos && line.find("\t") == 0);

            content[i] = line;
        }
        if (line.find("//") != line.npos) {     /*查找以“//”开头的注释语句*/
            j = line.find("//");        /*查找“//”在字符串中的位置*/
            if (j==0) {
                content.erase(content.begin()+i);       /*若“//”位于行首则整行删除*/
                i--;
            } else {
                text = line.substr(0,j);        /*若“//”不位于行首则进行裁切*/
                content[i] = text;
            }
        } else if (line.find("\"") != line.npos) {      /*查找字符串*/
            size_t p[50] = {0};
            
            while ((t=line.find("\"",k)) != line.npos) {        /*查找字符串“"”的位置*/
                p[f] = t;
                f++;
                k=t+1;
            }

            p[f] = line.length();
            text = line.substr(0,p[0]);
            
            for (r=1; p[r]!=0; r+=2) {
                text += line.substr(p[r]+1,p[r+1]-p[r]-1);      /*对行中的字符串进行删除*/
            }
            content[i] = text;
        } else if (line.find("/*") != line.npos) {      /*查找以“/*”开头的注释语句*/
            j = line.find("/*");
            k = line.find("*/");
            
            if (k != line.npos) {
                content[i] = line.substr(0,j);      /*如果注释语句只有一行，则删除注释语句*/
            } else {
                content[i] = line.substr(0,j);
                i += 1;
                line = content[i];
                while (line.find("*/") == line.npos) {
                    content.erase(content.begin()+i);       /*如果有多行注释语句，则逐行删除*/
                    line = content[i];
                }
                k = line.find("*/")+2;
                content[i] = line.substr(k,line.length()-k);
            }
        }
    }
}

bool subJudge (string l, long i) {
    if (l[i] < 48 || (l[i] > 57 && l[i] < 65) || (l[i] > 90 && l[i] < 97) || l[i] >122) {
        return true;
    } else {
        return false;
    }
}

bool judge(string l, string s){
    size_t i;
    i=l.find(s);
    if (i == 0) {
        if (subJudge(l, s.length()) || s.length() == l.length()) {
            return true;
        } else {
            return false;
        }
    } else {
        if (subJudge(l, i-1) && (subJudge(l, i+s.length()) || i+s.length() == l.length())) {
            return true;
        } else {
            return false;
        }
    }
    
}

void read (string path) {
    ifstream fp;
    string text;
    
    fp.open(path,ios::in);      /*打开文件*/
    if (!fp.is_open()) {        /*逐行读取文件内容*/
        cout<<"Error!"<<endl;
        return;
    }
    
    while (getline(fp, text)) {
        content.push_back(text);
    }
    fp.close();     /*关闭文件*/
}

void findKeyword () {
    int num = 0;
    string line;
    for (int i = 0; i<content.size(); i++) {
        line = content[i];
        for (int j=0; j<32; j++) {
            size_t fi = line.find(keyword[j], 0);
            while (fi!=line.npos && judge(line,keyword[j])) {
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
        if (line.find("switch") != line.npos && judge(line, "switch")) {        /*查找switch*/
            snum += 1;
            f += 1;
        }
        if (line.find("case") != line.npos && judge(line, "case")) {        /*查找case*/
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

void findIfElse (int level) {
    int sum1 = 0,sum2 = 0;
    stack<int> s;
    string line;
    for (int i = 0; i<content.size(); i++) {
        line = content[i];
        if (line.find("if") != line.npos && line.find("else") == line.npos && judge(line, "if")) {      /*遇到if时将1入栈*/
            s.push(1);
        } else if (line.find("if") == line.npos && line.find("else") != line.npos &&  s.empty() == false) {
            if (s.top() == 1) {
                sum1++;     /*若栈顶为1则与 if else 结构匹配成功*/
            } else {
                sum2++;     /*若栈顶为2则与 if else_if else 结构匹配成功*/
            }
            s.pop();        /*出栈*/
            
        }else  if (line.find("if") != line.npos && line.find("else") != line.npos && judge(line, "if")) {
            s.push(2);      /*遇到if_else时则将2入栈*/
        }
    }
    if (level == 3) {
        cout<<"if-else num: "<<sum1<<endl;
    } else if (level == 4) {
        cout<<"if-else num: "<<sum1<<endl;
        cout<<"if-else-if num: "<<sum2<<endl;
    }
}



int main(int argc, const char * argv[]) {
    int level = 0;
    string path,text;
    
    cin>>path>>level;
    
    read(path);
    exclude();
    
    switch (level) {
        case 1:
            findKeyword();
            break;
        case 2:
            findKeyword();
            findSwitchCase();
            break;
        case 3:
            findKeyword();
            findSwitchCase();
            findIfElse(3);
            break;
        case 4:
            findKeyword();
            findSwitchCase();
            findIfElse(4);
            break;
        default:
            cout<<"Error!"<<endl;
            break;
    }

    return 0;
}
