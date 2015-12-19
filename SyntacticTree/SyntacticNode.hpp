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

class SyntacticNode
{
    public :
    SyntacticNode();
    
    virtual std::string getPartOfSpeech() = 0;
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
    
    XBar* xbarChild;
    Phrase* adjunct;
    
    Head* headChild;
    Phrase* complement;
    
};

class Head : public SyntacticNode
{
    public :
    
    Head();
    Head(std::string str, std::string pos): str(str), partOfSpeech(pos) {};
  
    
    std::string getPartOfSpeech();
    
    std::string str;
    std::string partOfSpeech;
};
#endif /* SyntacticNode_hpp */
