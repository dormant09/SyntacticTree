//
//  SyntacticNode.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticNode.hpp"


SyntacticNode::SyntacticNode()
{
    
}
std::string SyntacticNode::getCode(Head *h)
{
    if(typeid(*h) == typeid(Case)) return "case";
    else if(typeid(*h) == typeid(Noun)) return "N";
    else if(typeid(*h) == typeid(Verb)) return "V";
    else if(typeid(*h) == typeid(Complementizer)) return "C";
    else if(typeid(*h) == typeid(Tense)) return "T";
    else return "X";
}

Head* Phrase::getHead()
{
    return xbarChild->getHead();
}
std::string Phrase::getTaggedString()
{
    std::string taggedString;
    taggedString = "[";
    taggedString += getCode(getHead());
    taggedString += "P ";
    
    if(spec != NULL) taggedString += spec->getTaggedString();
    if(xbarChild != NULL) taggedString += xbarChild->getTaggedString();
    
    taggedString += "]";
    return taggedString;
}


XBar::XBar()
{
    
}

std::string RecXBar::getTaggedString()
{
    std::string taggedString;
    taggedString = "[";
    taggedString += getCode(getHead());
    taggedString += "' ";
    
    if(adjunct != NULL) taggedString += adjunct->getTaggedString();
    if(xbarChild != NULL) taggedString += xbarChild->getTaggedString();
    
    taggedString += "]";
    return taggedString;
}
std::string LastXBar::getTaggedString()
{
    std::string taggedString;
    taggedString = "[";
    taggedString += getCode(getHead());
    taggedString += "' ";
    
    if(complement != NULL) taggedString += complement->getTaggedString();
    if(headChild != NULL) taggedString += headChild->getTaggedString();
    
    taggedString += "]";
    return taggedString;
}

Head* RecXBar::getHead()
{
    return xbarChild->getHead();
}
Head* LastXBar::getHead()
{
    return headChild;
}

Head* Head::getHead()
{
    return this;
}
bool Head::operator < (const Head& h) const
{
    return (str.compare(h.str) < 0);
}

std::string Head::getTaggedString()
{
    std::string taggedString;
    taggedString = "[";
    taggedString += getCode(getHead());
    taggedString += " ";
    
    taggedString += str;
    
    taggedString += "]";
    return taggedString;
}
