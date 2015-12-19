
//  SyntacticTreeGenerator.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "SyntacticTreeGenerator.hpp"


SyntacticTreeGenerator::SyntacticTreeGenerator()
{
    lexicon.loadFiles();
}

SyntacticTree SyntacticTreeGenerator::projectHead(SyntacticTree tree, Head* h)
{
    SyntacticTree addedTree = tree;
    addedTree.toBeDetermined.clear();
    
    Phrase* lastPhrase;
    if(addedTree.phraseStack.empty()) lastPhrase = NULL;
    else lastPhrase = addedTree.phraseStack.back();
    
    //XBar Projection
    XBar* xbar = new XBar(h);
    
    /*
     TODO
     
     나중에 함수로 따로 빼내서 XBar가 반복되는 경우를 처리
     complement를 취할 수 있어도, 취하지 않는 경우의 트리도 만들어야 함.
     */
    if(lastPhrase != NULL)
    {
        std::pair< std::string, std::string > posPair;
        posPair = std::make_pair(lastPhrase->getPartOfSpeech(), h->getPartOfSpeech());
        if(lexicon.complementRule.find(posPair) != lexicon.complementRule.end())
        {
            xbar->complement = lastPhrase;
            addedTree.phraseStack.pop_back();
            
            if(addedTree.phraseStack.empty()) lastPhrase = NULL;
            else lastPhrase = addedTree.phraseStack.back();
        }
    }
    
    
    
    //Phrase Projection
    Phrase* phrase = new Phrase(xbar);
    
    addedTree.phraseStack.push_back(phrase);
    
    return addedTree;
}

std::vector<SyntacticTree> SyntacticTreeGenerator::addCharacter(SyntacticTree tree, std::string character)
{
    std::vector<SyntacticTree> trees;
    
    trees.push_back(tree.addCharToTBD(character));
    
    std::string notTaggedWord = trees.back().toBeDetermined;
    
    
    if(lexicon.nouns.find(notTaggedWord) != lexicon.nouns.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Noun")));
    }
    if(lexicon.postpositions.find(notTaggedWord) != lexicon.postpositions.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Postposition")));
    }
    
    
    return trees;
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
        
        if(Decoder::isHangeul(lastCharacter[0]))
        {
            oldList = generatePartOfTrees(remainder);
            
            for(std::vector<SyntacticTree>::iterator tIter = oldList.begin(); tIter != oldList.end(); tIter++)
            {
                std::vector<SyntacticTree> addedTrees = addCharacter(*tIter, lastCharacter);
                newList.insert(std::end(newList), std::begin(addedTrees), std::end(addedTrees));
            }
            
            oldList.clear();
            return newList;
        }
        else
        {
            return generatePartOfTrees(remainder);
        }
        
    }
    
}

void SyntacticTreeGenerator::generateTrees(std::string str)
{
    trees = generatePartOfTrees(str);
}