#include<iostream>
#include<memory>
#include<components.hpp>
#include<icon_family.hpp>
#include<style_family.hpp>
using namespace std;

int main(){
    Icon1 icon;
    StyleTree style(icon);
    vector<shared_ptr<Component>> jsontree;
    shared_ptr<Component> c1 = make_shared<Container>("C0",0);
    c1->add(make_shared<Leaf>("M1",1,"leaf1"));
    shared_ptr<Component> c2 = make_shared<Container>("M2",1);
    c2->add(make_shared<Leaf>("MM1",1,"leaf2"));
    shared_ptr<Component> c3 = make_shared<Container>("C1",1);
    c3->add(make_shared<Leaf>("M4",2));
    c3->add(make_shared<Leaf>("M5",2,"leaf5"));
    c2->add(c3);
    c1->add(c2);
    c1->add(make_shared<Leaf>("M3",1,"leaf3"));
    c1->draw(style,"");
    std::string str="└──";
    for(int i=0;i<9-3;i++){
        str+="─";
    }
    cout<<str;
}