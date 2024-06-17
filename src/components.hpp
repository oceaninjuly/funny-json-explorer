#pragma once
#include<memory>
#include<vector>
#include<iostream>
#include<stack>
#include<style_family.hpp>
using std::shared_ptr;

class Component{
public:
    const std::string title; //属性的名称
    int level; //深度
    Component(std::string t,int l):title(t),level(l){}
    virtual string draw(Style& style,std::string prefix,int max_len=0,int flag=0){return "";}
    virtual void add(std::shared_ptr<Component> component){}
    virtual bool is_leaf(){return false;}
    virtual std::vector<std::shared_ptr<Component>>* get_childs(){return nullptr;}
};

class Container:public Component{
public:
    std::vector<std::shared_ptr<Component>> childs; //中间属性的儿子
    Container(std::string t,int l):Component(t,l){}
    string draw(Style& style,std::string prefix,int max_len=0,int flag=0){
        return style.draw_container(title,prefix,max_len,flag);
    }
    void add(std::shared_ptr<Component> component){
        childs.push_back(component);
    }

    std::vector<std::shared_ptr<Component>>* get_childs(){return &childs;}
};

class Leaf:public Component{
public:
    const std::string value; //叶子属性的值
    Leaf(std::string t,int l,std::string v=""):Component(t,l),value(v){}
    string draw(Style& style,std::string prefix,int max_len=0,int flag=0){
        style.draw_leaf(title,value,prefix,max_len,flag);
        return "";
    }
    bool is_leaf(){return true;}
};

class ComponentIter{
    std::vector<shared_ptr<Component>>* childs=nullptr;
    shared_ptr<Component> head;
    std::string prefix;
    int max_len;
    int flag;
    int iter_num = -1;
    shared_ptr<ComponentIter> current=nullptr;
public:
    ComponentIter(shared_ptr<Component> component,int max_len_,int f=0,std::string pre=""):
    head(component),flag(f),max_len(max_len_),prefix(pre){
        if(!component->is_leaf()) 
            childs = component->get_childs();
    }
    bool has_more(){
        return childs!=nullptr&&(iter_num<(int)childs->size()-1||(iter_num==(int)childs->size()-1&&current->has_more()));
    }

    bool is_end(){
        return (childs!=nullptr&&iter_num>=(int)childs->size())||(childs==nullptr&&iter_num==0);
    }
    void next(){
        if(childs!=nullptr){
            if(current!=nullptr&&current->has_more()){
                current->next();
            }else{
                iter_num++;
                if(iter_num<(int)childs->size()){
                    int next_flag=1;
                    int level = head->level;
                    if(level==0&&iter_num==0) next_flag=0;
                    next_flag = (iter_num==(int)childs->size()-1)? -1 : next_flag; //用于标记当前属性是否处在末尾
                    if(next_flag==-1&&(level==0||flag==-2)) next_flag=-2;
                    current = std::make_shared<ComponentIter>((*childs)[iter_num],max_len,next_flag,prefix);
                }
            }
        }else{
            iter_num++;
        }
    }

    void draw(Style& style){
        if(iter_num==-1){
            if(head->level==0) prefix = "";
            else{
                prefix = head->draw(style,prefix,max_len,flag);
            }
        }else{
            current->draw(style);
        }
    }
};