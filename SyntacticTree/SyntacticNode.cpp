//
//  SyntacticNode.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 19..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticNode.hpp"


SyntacticNode::SyntacticNode()
{
    
}

std::string SyntacticNode::makeAcronym(std::string pos)
{
    if(pos == "Complementizer") return "C";
    else if(pos == "Tense") return "T";
    else if(pos == "Verb" || pos == "Predicative") return "V";
    else if(pos == "Noun") return "N";
    else if(pos == "Postposition") return "P";
    else if(pos == "Adjective") return "Adj";
    else if(pos == "Adverb") return "Adv";
    else return "X";
}

Phrase::~Phrase()
{
    if(xbarChild != NULL)
    {
        xbarChild->~XBar();
    }
    if(spec != NULL)
    {
        spec->~Phrase();
    }
}

XBar::~XBar()
{
    if(headChild != NULL)
    {
        headChild->~Head();
    }
    if(complement != NULL)
    {
        complement->~Phrase();
    }
    if(xbarChild != NULL)
    {
        xbarChild->~XBar();
    }
    if(adjunct != NULL)
    {
        adjunct->~Phrase();
    }
}

Head::Head(std::string str, std::string pos)
{
    this->str = str;
    this->partOfSpeech = pos;
    this->conjugatable = Lexicon::getConjugatablePair(str, pos);
    
}
void Phrase::print()
{
    std::cout << "[" << makeAcronym(getPartOfSpeech()) << "P ";
    
    if(spec != NULL)
    {
        spec->print();
        std::cout << " ";
    }
    
    if(xbarChild != NULL)
    {
        xbarChild->print();
    }
    
    std::cout << "]";
    
}

std::string Phrase::getPartOfSpeech()
{
    if(xbarChild != NULL) return xbarChild->getPartOfSpeech();
    else return "";
}
bool Phrase::find(std::pair<std::string, std::string> pair)
{
    if(xbarChild != NULL) return xbarChild->find(pair);
    else return false;
}

void XBar::print()
{
    std::cout << "[" << makeAcronym(getPartOfSpeech()) << "' ";
    
    if(complement != NULL)
    {
        complement->print();
        std::cout << " ";
    }
    if(headChild != NULL)
    {
        headChild->print();
    }
    
    
    if(adjunct != NULL)
    {
        adjunct->print();
        std::cout << " ";
    }
    if(xbarChild != NULL)
    {
        xbarChild->print();
    }
    
    std::cout << "]";
}
std::string XBar::getPartOfSpeech()
{
    if(headChild != NULL) return headChild->getPartOfSpeech();
    else if(xbarChild != NULL) return xbarChild->getPartOfSpeech();
    else return "";
}
bool XBar::find(std::pair<std::string, std::string> pair)
{
    if(headChild != NULL) return headChild->find(pair);
    else if(xbarChild != NULL) return xbarChild->find(pair);
    else return false;
}
    


void Head::print()
{
    std::cout << "[" << makeAcronym(getPartOfSpeech()) << " " << str << "]";
}
std::string Head::getPartOfSpeech()
{
    return partOfSpeech;
}
bool Head::find(std::pair<std::string, std::string> pair)
{
    bool result = conjugatable.find(pair) != conjugatable.end();
    return result;
}
