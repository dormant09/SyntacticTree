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
   
    virtual Head* getHead() = 0;
    
};
class RecXBar : public XBar
{
    public :
    
    RecXBar();
    RecXBar(XBar* xbar) : xbarChild(xbar) {};
    
    XBar* xbarChild;
    Phrase* adjunct;
    
    Head* getHead();
    
};
class LastXBar : public XBar
{
    public :
    
    LastXBar();
    LastXBar(Head* head) : headChild(head) {};
    
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
    
    enum Type
    {
        SUBJECTIVE, OBJECTIVE, TBD
    };
    
    
    Case();
    Case(std::string str) : Head(str) {};
    Case(std::string str, Type c) : Head(str), grammaticalCase(c) {};
    
    int a() {return 2;};
    
    
    
    Type grammaticalCase;
    
};
class Tense : public Head
{
    public :
    
    Tense();
    Tense(std::string str) : Head(str) {};
    
    int a() {return 1;};
    
};
class Verb : public Head
{
    public :
    
    Verb();
    Verb(std::string str) : Head(str) {};
    
    int a() {return 1;};
    
};
class Complementizer : public Head
{
    public :
    
    Complementizer();
    Complementizer(std::string str) : Head(str) {};
    
    int a() {return 1;};
    
};

#endif /* SyntacticNode_hpp */
