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


void SyntacticTree::project(Head* head)
{
    
    if(phraseStack.empty())
    {
        XBar* xbar = new XBar(head);
        Phrase* phrase = new Phrase(xbar);
        phraseStack.push_back(phrase);
    }
    else
    {
        Head* lastPhraseHead = NULL;
        lastPhraseHead = phraseStack.back()->getHead();
        
        headStack.push_back(head);
        
        XBar* xbar = new XBar(head);
        xbarStack.push_back(xbar);
        headStack.pop_back();
        if(typeid(*head) == typeid(Case) && typeid(*lastPhraseHead) == typeid(Noun))
        {
            xbar->complement = phraseStack.back();
            phraseStack.pop_back();
        }
        
        
        Phrase* phrase = new Phrase(xbar);
        phraseStack.push_back(phrase);
        xbarStack.pop_back();
        

    }
    
    
    toBeDetermined = "";
    
}