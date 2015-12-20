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
    else if(pos == "Verb") return "V";
    else if(pos == "Noun") return "N";
    else if(pos == "Postposition") return "P";
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

void Head::print()
{
    std::cout << "[" << makeAcronym(getPartOfSpeech()) << " " << str << "]";
}
std::string Head::getPartOfSpeech()
{
    return partOfSpeech;
}