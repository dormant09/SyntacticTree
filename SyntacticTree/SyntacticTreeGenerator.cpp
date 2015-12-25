
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
     
     tree에 Head stack이랑 xbar stack을 만들어서
     tree를 복사해가면서 서로 다르게 projection시킨다.
     */
    //Complement
    if(lastPhrase != NULL)
    {
        if(lastPhrase->find(std::make_pair("Complement", h->getPartOfSpeech())))
        {
            xbar->complement = lastPhrase;
            addedTree.phraseStack.pop_back();
            
            if(addedTree.phraseStack.empty()) lastPhrase = NULL;
            else lastPhrase = addedTree.phraseStack.back();
        }
    }
    
    //Adjunct
    while(lastPhrase != NULL)
    {
        XBar* adjunctXbar = new XBar(xbar);
        if(lastPhrase->find(std::make_pair("Adjunct", h->getPartOfSpeech())))
        {
            adjunctXbar->adjunct = lastPhrase;
            addedTree.phraseStack.pop_back();
            
            if(addedTree.phraseStack.empty()) lastPhrase = NULL;
            else lastPhrase = addedTree.phraseStack.back();
            
            xbar = adjunctXbar;
        }
        else break;
    }
    
    
    
    //Phrase Projection
    Phrase* phrase = new Phrase(xbar);
    
    //Spec
    if(lastPhrase != NULL)
    {
        if(lastPhrase->find(std::make_pair("Spec", h->getPartOfSpeech())))
        {
            phrase->spec = lastPhrase;
            addedTree.phraseStack.pop_back();
            
            if(addedTree.phraseStack.empty()) lastPhrase = NULL;
            else lastPhrase = addedTree.phraseStack.back();
        }
    }
    
    addedTree.phraseStack.push_back(phrase);
    
    return addedTree;
}

std::vector<SyntacticTree> SyntacticTreeGenerator::addCharacter(SyntacticTree tree, std::string character)
{
    std::vector<SyntacticTree> trees;
    
    trees.push_back(tree.addCharToTBD(character));
    
    std::string notTaggedWord = trees.back().toBeDetermined;
    
    
    if(notTaggedWord == "이") //서술격조사
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Predicative")));
    }
    if(lexicon.nouns.find(notTaggedWord) != lexicon.nouns.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Noun")));
    }
    
    if(lexicon.verbs.find(notTaggedWord + "다") != lexicon.verbs.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Verb")));
    }
    else if(lexicon.verbs.find(notTaggedWord + "ㄹ다") != lexicon.verbs.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord + "ㄹ", "Verb")));
    }
    else if(lexicon.verbs.find(notTaggedWord + "ㅅ다") != lexicon.verbs.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord + "ㅅ", "Verb")));
    }
    else if(lexicon.verbs.find(notTaggedWord + "ㅎ다") != lexicon.verbs.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord + "ㅎ", "Verb")));
    }
    
    
    if(lexicon.adjectives.find(notTaggedWord) != lexicon.adjectives.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Adjective")));
    }
    if(lexicon.adverbs.find(notTaggedWord) != lexicon.adverbs.end())
    {
        trees.push_back(projectHead(tree, new Head(notTaggedWord, "Adverb")));
    }
    if(lexicon.postpositions.find(notTaggedWord) != lexicon.postpositions.end())
    {
        if(!tree.phraseStack.empty())
        {
            Phrase* lastPhrase = tree.phraseStack.back();
            if(lastPhrase->getPartOfSpeech() == "Noun")
            {
                trees.push_back(projectHead(tree, new Head(notTaggedWord, "Postposition")));
            }
        }
        
    }
    if(lexicon.tenses.find(notTaggedWord) != lexicon.tenses.end())
    {
        if(!tree.phraseStack.empty())
        {
            Phrase* lastPhrase = tree.phraseStack.back();
            if(lastPhrase->getPartOfSpeech() == "Verb" || lastPhrase->getPartOfSpeech() == "Predicative")
            {
                trees.push_back(projectHead(tree, new Head(notTaggedWord, "Tense")));
            }
        }
    }
    if(lexicon.complementizers.find(notTaggedWord) != lexicon.complementizers.end())
    {
        if(!tree.phraseStack.empty())
        {
            Phrase* lastPhrase = tree.phraseStack.back();
            if(lastPhrase->getPartOfSpeech() == "Mood")
            {
                trees.push_back(projectHead(tree, new Head(notTaggedWord, "Complementizer")));
            }
        }
    }
    if(lexicon.moods.find(notTaggedWord) != lexicon.moods.end())
    {
        if(!tree.phraseStack.empty())
        {
            Phrase* lastPhrase = tree.phraseStack.back();
            if(lastPhrase->getPartOfSpeech() == "Tense")
            {
                trees.push_back(projectHead(tree, new Head(notTaggedWord, "Mood")));
            }
        }
    }
    
    
    
    /*
     trees를 돌면서
     \phi가 붙을 수 있는지를 검사
     붙을 수 있으면 붙은 것과 붙지 않은 것을 만든다.
     
     */
    
    
    std::vector<SyntacticTree> phiAddedTrees;
    
    for(std::vector<SyntacticTree>::iterator tIter = trees.begin(); tIter != trees.end(); tIter++)
    {
        std::vector<SyntacticTree> results = addPhiToTree(*tIter);
        
        phiAddedTrees.insert(phiAddedTrees.end(), results.begin(), results.end());
    }
    trees.insert(trees.end(), phiAddedTrees.begin(), phiAddedTrees.end());
    
    
    return trees;
}
std::vector<SyntacticTree> SyntacticTreeGenerator::addPhiToTree(SyntacticTree tree)
{
    std::vector<SyntacticTree> phiAddedTrees;
    
    if(tree.toBeDetermined.empty())
    {
        Phrase* lastPhrase;
        if(!tree.phraseStack.empty())
        {
            lastPhrase = tree.phraseStack.back();
            
            if(lastPhrase->getPartOfSpeech() == "Verb" || lastPhrase->getPartOfSpeech() == "Predicative")
            {
                phiAddedTrees.push_back(projectHead(tree, new Head("Ø", "Tense")));
            }
            if(lastPhrase->getPartOfSpeech() == "Tense")
            {
                phiAddedTrees.push_back(projectHead(tree, new Head("Ø", "Mood")));
            }
            if(lastPhrase->getPartOfSpeech() == "Mood")
            {
                phiAddedTrees.push_back(projectHead(tree, new Head("Ø", "Complementizer")));
            }
        }
    }
    
    std::vector<SyntacticTree> phiAddedTreesRec;
    for(std::vector<SyntacticTree>::iterator tIter = phiAddedTrees.begin(); tIter != phiAddedTrees.end(); tIter++)
    {
        std::vector<SyntacticTree> result = addPhiToTree(*tIter);
        phiAddedTreesRec.insert(phiAddedTreesRec.end(), result.begin(), result.end());
    }
    
    
    phiAddedTrees.insert(phiAddedTrees.begin(), phiAddedTreesRec.begin(), phiAddedTreesRec.end());
    
    return phiAddedTrees;
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
        
        if(Decoder::isHangeul(lastCharacter) || Decoder::isHangeulAlphabet(lastCharacter))
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
            oldList = generatePartOfTrees(remainder);
            
            if(lastCharacter == " ")
            {
                for(std::vector<SyntacticTree>::iterator tIter = oldList.begin(); tIter != oldList.end(); tIter++)
                {
                    if(tIter->toBeDetermined.empty())
                    {
                        newList.push_back(*tIter);
                    }
                }
            }
            else return oldList;
            
            oldList.clear();
            return newList;
            
        }
        
    }
    
}
std::vector<std::string> SyntacticTreeGenerator::normalize(std::string str)
{
    if(str.empty())
    {
        std::vector<std::string> initialList;
        initialList.push_back(std::string());
        return initialList;
    }
    else
    {
        std::vector<std::string> oldList, newList;
        
        std::string lastCharacter = Decoder::extractLastCharacter(str);
        std::string remainder = Decoder::deleteLastCharacter(str);
        
        oldList = normalize(remainder);
        
        if(Decoder::isHangeul(lastCharacter))
        {
            std::string coda = Decoder::extractCoda(lastCharacter);
            
            if((coda == "ㄴ") || (coda == "ㄹ") || (coda == "ㅂ") || (coda == "ㅆ"))
            {
              
                for(std::vector<std::string>::iterator nIter = oldList.begin(); nIter != oldList.end(); nIter++)
                {
                    newList.push_back((*nIter) + Decoder::deleteCoda(lastCharacter) + coda);
                }
                
            }
            
        }
        
        for(std::vector<std::string>::iterator nIter = oldList.begin(); nIter != oldList.end(); nIter++)
        {
            newList.push_back((*nIter) + lastCharacter);
        }
        
        oldList.clear();
        return newList;
        
    }
}

void SyntacticTreeGenerator::generateTrees(std::string str)
{
    std::vector<std::string> normalizedText;// = normalize(str);
    normalizedText.push_back(Decoder::decomposeSyllable(str));
    
    for(std::vector<std::string>::iterator nIter = normalizedText.begin(); nIter != normalizedText.end(); nIter++)
    {
        std::vector<SyntacticTree> taggedTree = generatePartOfTrees(*nIter);
        
        
        for(std::vector<SyntacticTree>::iterator tIter = taggedTree.begin(); tIter != taggedTree.end(); tIter++)
        {
            if(tIter->toBeDetermined.empty() && tIter->phraseStack.size() == 1)
            {
                Phrase* lastPhrase = tIter->phraseStack.back();
                if(lastPhrase->getPartOfSpeech() == "Complementizer")
                {
                    trees.push_back(*tIter);
                }
                
            }
        }
    }
    
}

void SyntacticTreeGenerator::printTrees()
{
    if(trees.empty())
    {
        std::cout << "알맞은 통사 수형도를 찾을 수 없습니다." << std::endl;
    }
    else
    {
        for(std::vector<SyntacticTree>::iterator tIter = trees.begin(); tIter != trees.end(); tIter++)
        {
            tIter->printTree();
            std::cout << std::endl << std::endl;
        }
        
    }
    
}