//
//  SyntacticTree.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticTree.hpp"


SyntacticTree::SyntacticTree()
{
}


void SyntacticTree::project(PartOfSpeech::Type pos)
{
    Head* head = new Head(toBeDetermined, pos);
    headStack.push_back(head);
    
    XBar* xbar = new XBar(head);
    xbarStack.push_back(xbar);
    headStack.pop_back();
    if(pos == PartOfSpeech::CASE && phraseStack.back()->pos == PartOfSpeech::NOUN)
    {
        xbarStack.back()->complement = phraseStack.back();
        phraseStack.pop_back();
    }
    
    Phrase* phrase = new Phrase(xbar);
    phraseStack.push_back(phrase);
    xbarStack.pop_back();
    
    
    toBeDetermined = "";
    
}