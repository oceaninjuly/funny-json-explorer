#include<iostream>
#include<memory>
#include <windows.h>
#include<jsonexplorer.hpp>
using namespace std;

int main(int argc,char **argv){
    //读取命令行参数
    string filename;
    int style_id=2,icon_id=2;
    char *endptr;
    if(argc<7){
        cout<<"usage: fje -f [filePath] -i [1~2] -s [1~2] \n\n";
    }
    for(int i=1;i<argc;i+=2){
        string in_1(argv[i]);
        if(in_1=="-f"){
            filename=string(argv[i+1]);
        }else if(in_1=="-s"){
            style_id=strtol(argv[i+1],&endptr,10);
            if (*endptr != '\0') {
                printf("style不是一个有效的整数。\n");
                style_id=0;
            }
        }else if(in_1=="-i"){
            icon_id=strtol(argv[i+1],&endptr,10);
            if (*endptr != '\0') {
                printf("icon不是一个有效的整数。\n");
                icon_id=0;
            }
        }
    }
    JsonExplorer explorer(style_id,icon_id);
    explorer._load(filename);
    SetConsoleOutputCP(CP_UTF8); //让控制台支持unicode字符输出
    explorer.show();
    using namespace nlohmann::literals;
    return 0;
}

/*
   ─ │  ┌ ┐ └ ┘ ├ ┬ ┤ ┴ ┼
*/

