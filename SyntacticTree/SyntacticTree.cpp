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
    validity = false;
}


std::vector<SyntacticTree> SyntacticTree::add(std::string character)
{
    std::vector<SyntacticTree> candidates;
    
    
    //들어온 문자가 어떤 뜻을 가지는지 모른다고 상정하는 경우
    SyntacticTree defaultCaseTree = *this;
    defaultCaseTree.toBeDetermined += character;
    defaultCaseTree.setValid();
    candidates.push_back(defaultCaseTree);
    
    
    //들어온 문자가 특정한 역할을 하는 경우
    if(character == "는")
    {
        if( Decoder::endsWithCoda(character) )
        {
            
        }
    }
    
   
    
    
    
    
    
    
    return candidates;
}

void SyntacticTree::setValid()
{
    validity = true;
}
bool SyntacticTree::isValid()
{
    return validity;
}