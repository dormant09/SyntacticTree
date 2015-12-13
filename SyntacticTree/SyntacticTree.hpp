//
//  SyntacticTree.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticTree_hpp
#define SyntacticTree_hpp

#include <vector>
#include <typeinfo>
#include <iostream>
#include "SyntacticNode.hpp"
#include "Decoder.hpp"

class SyntacticTree
{
    public :
    
    SyntacticTree();
      
    std::string toBeDetermined;
    
    std::vector<Phrase*> phraseStack;
    std::vector<XBar*> xbarStack;
    std::vector<Head*> headStack;
    
    
    void project(Head *head);
    std::string getTaggedString();
    
    
    private :
    
    bool possibilityOfComplement(Head* head, XBar* xbar, Head* lastPhraseHead);
    
};

#endif /* SyntacticTree_hpp */
