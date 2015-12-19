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

SyntacticTree SyntacticTree::addCharToTBD(std::string character)
{
    SyntacticTree addedTree = *this;
    addedTree.toBeDetermined += character;
    return addedTree;
}