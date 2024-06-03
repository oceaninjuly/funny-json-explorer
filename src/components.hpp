#pragma once
#include<memory>
#include<vector>
#include<iostream>
#include<style_family.hpp>

class Component{
public:
    const std::string title; //属性的名称
    int level; //深度
    Component(std::string t,int l):title(t),level(l){}
    virtual void draw(Style& style,std::string prefix,int max_len=0,int flag=0){};
    virtual void add(std::shared_ptr<Component> component){};
};

class Container:public Component{
public:
    std::vector<std::shared_ptr<Component>> childs; //中间属性的儿子
    Container(std::string t,int l):Component(t,l){}
    void draw(Style& style,std::string prefix,int max_len=0,int flag=0){
        //使用style的draw函数,并获取儿子列表在绘制时的前缀
        std::string next_prefix="";
        if(level!=0){
            next_prefix=style.draw_container(title,prefix,max_len,flag);
        }
        for(int i=0;i<childs.size();i++){
            int next_flag=1;
            if(level==0&&i==0) next_flag=0;
            next_flag = (i==childs.size()-1)? -1 : next_flag; //用于标记当前属性是否处在末尾
            if(next_flag==-1&&(level==0||flag==-2)) next_flag=-2;
            childs[i]->draw(style,next_prefix,max_len,next_flag);
        }
    }
    void add(std::shared_ptr<Component> component){
        childs.push_back(component);
    }
};

class Leaf:public Component{
public:
    const std::string value; //叶子属性的值
    Leaf(std::string t,int l,std::string v=""):Component(t,l),value(v){}
    void draw(Style& style,std::string prefix,int max_len=0,int flag=0){
        style.draw_leaf(title,value,prefix,max_len,flag);
    }
};