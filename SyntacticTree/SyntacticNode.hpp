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

namespace PartOfSpeech
{
    enum Type
    {
        NOUN, CASE
    };
}

class Phrase
{
    public :
    
    Phrase();
    Phrase(XBar* xbar);
    
    XBar* xbarChild;
    Phrase* spec;
    
    PartOfSpeech::Type pos;
    
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
    
    PartOfSpeech::Type pos;
};
class Head
{
    public :
    
    Head();
    Head(std::string str, PartOfSpeech::Type pos);
    
    std::string str;
    PartOfSpeech::Type pos;
};

#endif /* SyntacticNode_hpp */
