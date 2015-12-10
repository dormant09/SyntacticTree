//
//  SyntacticNode.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticNode.hpp"

Phrase::Phrase(XBar* xbar)
{
    this->xbarChild = xbar;
    this->spec = NULL;
    
}
Head* Phrase::getHead()
{
    return xbarChild->getHead();
}

XBar::XBar(Head* head)
{
    this->xbarChild = NULL;
    this->adjunct = NULL;
    
    this->headChild = head;
    this->complement = NULL;
    
}

Head* XBar::getHead()
{
    if(xbarChild == NULL)
    {
        return headChild;
    }
    else
    {
        return xbarChild->getHead();
    }
}

/*
Head::Head(std::string str, PartOfSpeech::Type pos)
{
    this->str = str;
    this->pos = pos;
}

*/