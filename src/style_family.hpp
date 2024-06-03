#pragma once
#include<icon_family.hpp>
#include<memory>
#include<iostream>
using std::string;

string repeat(int times,string str){
    string res="";
    for(int i=0;i<times;i++) res+=str;
    return res;
}

class Style{
protected:
    Icon icon;
public:
    Style():icon(){}
    Style(Icon& icon_):icon(icon_){}
    void set_icon(const Icon& icon_){icon=icon_;}

    virtual std::string draw_container(const std::string& title,std::string& prefix,int max_len,int flag){return "";};
    virtual void draw_leaf(const std::string& title,const std::string& value,std::string& prefix,int max_len,int flag){};
};

class StyleTree:public Style{
public:
    StyleTree():Style(){}
    StyleTree(Icon& icon_):Style(icon_){}
    std::string draw_container(const std::string& title,std::string& prefix,int max_len,int flag){
        std::cout<<prefix;
        std::string next_prefix=prefix;
        if(flag<0){
            next_prefix+="   ";
            std::cout<<"└─";
        }else{
            next_prefix+="│  ";
            std::cout<<"├─";
        }
        std::cout<<icon.get_container_icon()<<title<<'\n';
        return next_prefix;
    }

    void draw_leaf(const std::string& title,const std::string& value,std::string& prefix,int max_len,int flag){
        std::cout<<prefix;
        if(flag<0) {std::cout<<"└─";} 
        else {std::cout<<"├─";}
        std::cout<<icon.get_leaf_icon()<<title;
        if(value.size()!=0){
            std::cout<<": "+value;
        }
        std::cout<<'\n';
    } 
};


/*
   ─ │  ┌ ┐ └ ┘ ├ ┬ ┤ ┴ ┼
*/

class StyleRectangle:public Style{
public:
    StyleRectangle():Style(){}
    StyleRectangle(Icon& icon_):Style(icon_){}
    string draw_container(const string& title,string& prefix,int max_len,int flag){
        std::cout<<prefix;
        string next_prefix=prefix,end="┤";
        if(flag<0){
            std::cout<<"├─";
        }else if(flag==0){
            std::cout<<"┌─";
            end="┐";
        }
        else{
            std::cout<<"├─";
        }
        next_prefix+="│  ";
        std::cout<<icon.get_container_icon()<<title<<" ";
        int res_len=max_len-(prefix.size()/5)*3-3-title.size()-1+5;
        // std::cout<<prefix.size();
        std::cout<<repeat(res_len,"─")+end<<'\n';
        return next_prefix;
    }
    
    void draw_leaf(const std::string& title,const std::string& value,std::string& prefix,int max_len,int flag){
        string end="┤";
        if(flag==0){
            std::cout<<prefix;
            std::cout<<"┌─";
            end="┐";
        }else if(flag>-2){
            std::cout<<prefix;
            std::cout<<"├─";
        }else{
            if(prefix.size()>4){
                std::cout<<"└──"+repeat(((int)prefix.size()-5)/5,"┴──");
                std::cout<<"┴─";
            }else{
                std::cout<<"└─";
            }
            end="┘";   
        }
        std::cout<<icon.get_leaf_icon()<<title;
        std::cout<<" ";
        int res_len=max_len;
        if(value.size()!=0){
            std::cout<<": "+value;
            res_len-=2;
        }
        res_len=res_len-(prefix.size()/5)*3-3-title.size()-value.size()-1+5;
        // std::cout<<prefix.size();
        std::cout<<repeat(res_len,"─")+end;
        std::cout<<'\n';
    } 
};
