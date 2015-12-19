//
//  SyntacticTreeGenerator.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticTreeGenerator.hpp"


SyntacticTreeGenerator::SyntacticTreeGenerator()
{
    //file load.
    
}

std::vector<SyntacticTree> SyntacticTreeGenerator::generatePartOfTrees(std::string str)
{
    if(str.empty())
    {
        std::vector<SyntacticTree> initialList;
        initialList.push_back(SyntacticTree());
        return initialList;
    }
    else
    {
        std::vector<SyntacticTree> oldList, newList;
        
        std::string lastCharacter = Decoder::extractLastCharacter(str);
        std::string remainder = Decoder::deleteLastCharacter(str);
        
        oldList = generatePartOfTrees(remainder);
        
        for(std::vector<SyntacticTree>::iterator tIter = oldList.begin(); tIter != oldList.end(); tIter++)
        {
            std::vector<SyntacticTree> addedTrees = addCharacter(*tIter, lastCharacter);
            newList.insert(std::end(newList), std::begin(addedTrees), std::end(addedTrees));
        }
        
        oldList.clear();
        return newList;
    }
    
}

void SyntacticTreeGenerator::generateTrees(std::string str)
{
    trees = generatePartOfTrees(str);
}

std::vector<SyntacticTree> SyntacticTreeGenerator::addCharacter(SyntacticTree tree, std::string character)
{
    std::vector<SyntacticTree> trees;

    trees.push_back(tree.addCharToTBD(character));
    
    
    /*
     
     TODO
     
     character가 특별한 의미를 지니는 경우 처리
     
     */
    
    return trees;
}

