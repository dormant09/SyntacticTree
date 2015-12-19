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



std::string Phrase::getPartOfSpeech()
{
    if(xbarChild != NULL) return xbarChild->getPartOfSpeech();
    else return "";
}

std::string XBar::getPartOfSpeech()
{
    if(headChild != NULL) return headChild->getPartOfSpeech();
    else if(xbarChild != NULL) return xbarChild->getPartOfSpeech();
    else return "";
}
std::string Head::getPartOfSpeech()
{
    return partOfSpeech;
}