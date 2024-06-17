#pragma once
#include<iostream>

class Icon{
    std::string container_icon;
    std::string leaf_icon;
public:
    Icon():container_icon(),leaf_icon(){}
    
    Icon(std::string c1,std::string c2):container_icon(c1),leaf_icon(c2){}
    
    //返回中间节点符号
    const std::string get_container_icon()const{return container_icon;}

    //返回叶子节点符号
    const std::string get_leaf_icon()const{return leaf_icon;}

    //浅拷贝赋值
    const Icon& operator=(const Icon& other){
        this->container_icon=other.container_icon;
        this->leaf_icon=other.leaf_icon;
        return *this;
    }
};

//对于继承类,只需实现自己的构造器,并为父类构造器提供特定字符即可
class Icon1:public Icon{
public:
    Icon1():Icon("♢","♧"){}
};

class Icon2:public Icon{
public:
    Icon2():Icon("♦","♣"){}
};
