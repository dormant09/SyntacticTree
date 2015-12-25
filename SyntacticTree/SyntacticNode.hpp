//
//  SyntacticNode.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 19..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticNode_hpp
#define SyntacticNode_hpp

#include <string>
#include <iostream>
#include <set>

#include "Lexicon.hpp"

class SyntacticNode
{
    public :
    SyntacticNode();
    
    virtual std::string getPartOfSpeech() = 0;
    virtual std::string getStr() = 0;
    virtual bool find(std::pair<std::string, std::string> pair) = 0;
    virtual void print() = 0;
    
    static std::string makeAcronym(std::string pos);
};

class Phrase;
class XBar;
class Head;

class Phrase : public SyntacticNode
{
    public :
    
    Phrase() : xbarChild(NULL), spec(NULL) {};
    Phrase(XBar *xbar) : xbarChild(xbar), spec(NULL) {};
    ~Phrase();
    
    std::string getPartOfSpeech();
    std::string getStr();
    bool find(std::pair<std::string, std::string> pair);
    void print();
    
    XBar* xbarChild;
    Phrase* spec;
};


class XBar : public SyntacticNode
{
    public :
    
    XBar() : xbarChild(NULL), adjunct(NULL), headChild(NULL), complement(NULL) {};
    XBar(Head* head) : xbarChild(NULL), adjunct(NULL), headChild(head), complement(NULL) {};
    XBar(XBar* xbar) : xbarChild(xbar), adjunct(NULL), headChild(NULL), complement(NULL) {};
    ~XBar();
    
    std::string getPartOfSpeech();
    std::string getStr();
    bool find(std::pair<std::string, std::string> pair);
    void print();
    
    XBar* xbarChild;
    Phrase* adjunct;
    
    Head* headChild;
    Phrase* complement;
    
};

class Head : public SyntacticNode
{
    public :
    
    Head();
    Head(std::string str, std::string pos);
  
    void print();
    std::string getPartOfSpeech();
    std::string getStr();
    bool find(std::pair<std::string, std::string> pair);
    
    std::string str;
    std::string partOfSpeech;
    
    std::set< std::pair<std::string, std::string> > conjugatable;
};
#endif /* SyntacticNode_hpp */
