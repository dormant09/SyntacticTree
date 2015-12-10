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

XBar::XBar()
{
    
}

Head* RecXBar::getHead()
{
    return xbarChild->getHead();
}
Head* LastXBar::getHead()
{
    return headChild;
}
