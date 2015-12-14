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
#include <typeinfo>

class Phrase;
class XBar;
class Head;

class SyntacticNode
{
    public :
    
    SyntacticNode();
    
    virtual std::string getTaggedString() = 0;
    virtual Head* getHead() = 0;
    
    static std::string getCode(Head *h);
};

class Phrase : public SyntacticNode
{
    public :
    
    Phrase();
    Phrase(XBar* xbar) : xbarChild(xbar), spec(NULL) {};
    
    XBar* xbarChild;
    Phrase* spec;
    
    Head* getHead();

    std::string getTaggedString();
    
};
class XBar : public SyntacticNode
{
    public :
    
    XBar();
    
};
class RecXBar : public XBar
{
    public :
    
    RecXBar();
    RecXBar(XBar* xbar) : xbarChild(xbar), adjunct(NULL) {};
    
    XBar* xbarChild;
    Phrase* adjunct;
    
    Head* getHead();
    
    std::string getTaggedString();
    
};
class LastXBar : public XBar
{
    public :
    
    LastXBar();
    LastXBar(Head* head) : headChild(head), complement(NULL) {};
    
    Head* headChild;
    Phrase* complement;
    
    Head* getHead();
    
    std::string getTaggedString();
    
};
class Head : public SyntacticNode
{
    public :
    
    Head();
    Head(std::string str) : str(str) {};
    
    
    Head* getHead();
    std::string getTaggedString();
    
    bool operator < (const Head& h) const;
    
    std::string str;
};
class Noun : public Head
{
    public :
    
    Noun();
    Noun(std::string str) : Head(str) {};
    
};
namespace Case
{
    enum Type
    {
        SUBJECTIVE, OBJECTIVE, TBD
    };
}
class Postposition : public Head
{
    public :
    
    
    
    
    Postposition();
    Postposition(std::string str) : Head(str) {};
    Postposition(std::string str, Case::Type c) : Head(str), grammaticalCase(c) {};
    
    
    
    Case::Type grammaticalCase;
    
};
class Tense : public Head
{
    public :
    
    enum Type
    {
        PAST, PRESENT, FUTURE
    };
    
    Tense();
    Tense(std::string str) : Head(str) {};
    Tense(std::string str, Type t) : Head(str), tense(t) {};
    
    Type tense;
};
class Verb : public Head
{
    public :
    
    Verb();
    Verb(std::string str) : Head(str) {};
    
};
class Complementizer : public Head
{
    public :
    
    Complementizer();
    Complementizer(std::string str) : Head(str) {};
    
    
};



#endif /* SyntacticNode_hpp */
