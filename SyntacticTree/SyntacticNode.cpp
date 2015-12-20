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

Head::Head(std::string str, std::string pos)
{
    this->str = str;
    this->partOfSpeech = pos;
    
    if(pos == "Verb")
    {
        //VP는 T의 complemnt가 될 수 있음을 의미
        conjugatable.insert(std::make_pair("Complement", "Tense"));
    }
    else if(pos == "Tense")
    {
        conjugatable.insert(std::make_pair("Complement", "Complementizer"));
    }
    else if(pos == "Noun")
    {
        conjugatable.insert(std::make_pair("Complement", "Postposition"));
    }
    else if(pos == "Adverb")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Verb"));
        conjugatable.insert(std::make_pair("Adjunct", "Adjective"));
    }
    else if(pos == "Adjective")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Noun"));
    }
    else if(pos == "Postposition")
    {
        if(str == "은" || str == "는" || str == "ㄴ")
        {
            conjugatable.insert(std::make_pair("Adjunct", "Verb"));
            conjugatable.insert(std::make_pair("Spec", "Tense"));
        }
        else if(str == "을" || str == "를" || str == "ㄹ")
        {
            conjugatable.insert(std::make_pair("Adjunct", "Verb"));
        }
        else if(str == "이" || str == "가")
        {
            conjugatable.insert(std::make_pair("Spec", "Tense"));
        }
        else if(str == "의")
        {
            conjugatable.insert(std::make_pair("Adjunct", "Noun"));
        }
    }
    else if(pos == "Complementizer")
    {
        
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
