#pragma once
#include<memory>
#include<icon_family.hpp>
#include<style_family.hpp>

class AbstractIconFactory{
    int id=0;
public:
    std::shared_ptr<Icon> create(){
        std::shared_ptr<Icon> icon;
        switch (id){
        case 1:
            icon=std::make_shared<Icon1>();
            break;
        case 2:
            icon=std::make_shared<Icon2>();
            break;
        default:
            icon=std::make_shared<Icon>();
            break;
        }
        return icon;
    }
    void set_id(int id){this->id=id;}
};

class AbstractStyleFactory{
    int id=0;
public:
    std::shared_ptr<Style> create(std::shared_ptr<Icon> icon){
        std::shared_ptr<Style> style;
        switch (id){
        case 1:
            style=std::make_shared<StyleTree>(*icon);
            break;
        case 2:
            style=std::make_shared<StyleRectangle>(*icon);
            break;
        default:
            style=std::make_shared<StyleTree>(*icon);
            break;
        }
        return style;
    }
    void set_id(int id){this->id=id;}
};