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
        XBar* xbar = new LastXBar(head);
        Phrase* phrase = new Phrase(xbar);
        phraseStack.push_back(phrase);
    }
    else
    {
        //Head Projection
        Head* lastPhraseHead = phraseStack.back()->getHead();
        headStack.push_back(head);
        
        //XBar Projection
        LastXBar* xbar = new LastXBar(head);
        if(typeid(*head) == typeid(Case) && typeid(*lastPhraseHead) == typeid(Noun))
        {
            xbar->complement = phraseStack.back();
            phraseStack.pop_back();
        }
        else if(typeid(*head) == typeid(Verb) && typeid(*lastPhraseHead) == typeid(Case))
        {
            Case* lastCase = dynamic_cast<Case*>(lastPhraseHead);
            if(lastCase->grammaticalCase == Case::OBJECTIVE || lastCase->grammaticalCase == Case::TBD)
            {
                xbar->complement = phraseStack.back();
                phraseStack.pop_back();
            }
        }
        else if(typeid(*head) == typeid(Tense) && typeid(*lastPhraseHead) == typeid(Verb))
        {
            xbar->complement = phraseStack.back();
            phraseStack.pop_back();
        }
        else if(typeid(*head) == typeid(Complementizer) && typeid(*lastPhraseHead) == typeid(Tense))
        {
            xbar->complement = phraseStack.back();
            phraseStack.pop_back();
        }
        xbarStack.push_back(xbar);
        headStack.pop_back();
        
        
        //Phrase Projection
        Phrase* phrase = new Phrase(xbar);
        if(!phraseStack.empty())
        {
            lastPhraseHead = phraseStack.back()->getHead();
            
             if(typeid(*head) == typeid(Tense) && typeid(*lastPhraseHead) == typeid(Case))
             {
                 Case* lastCase = dynamic_cast<Case*>(lastPhraseHead);
                 if(lastCase->grammaticalCase == Case::SUBJECTIVE || lastCase->grammaticalCase == Case::TBD)
                 {
                     phrase->spec = phraseStack.back();
                     phraseStack.pop_back();
                 }
             }

        }
        
        phraseStack.push_back(phrase);
        xbarStack.pop_back();

    }
    
    
    toBeDetermined = "";
    
}