//
//  SyntacticNode.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticNode_hpp
#define SyntacticNode_hpp

#include <string> 

class Phrase;
class XBar;
class Head;

class Phrase
{
    public :
    
    Phrase();
    Phrase(XBar* xbar);
    
    XBar* xbarChild;
    Phrase* spec;
    
    Head* getHead();
    
};
class XBar
{
    public :
    
    XBar();
    XBar(Head* head);
    
    XBar* xbarChild;
    Phrase* adjunct;
    
    Head* headChild;
    Phrase* complement;
    
    
    Head* getHead();
    
};
class Head
{
    public :
    
    Head();
    Head(std::string str) : str(str) {};
    
    virtual int a() = 0;
    
    std::string str;
};
class Noun : public Head
{
    public :
    
    Noun();
    Noun(std::string str) : Head(str) {};
    
    int a() {return 1;};
    
};
class Case : public Head
{
    public :
    
    Case();
    Case(std::string str) : Head(str) {};
    
    int a() {return 2;};
    
};

#endif /* SyntacticNode_hpp */
