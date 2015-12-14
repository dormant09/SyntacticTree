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
    formLexicon();
}

void SyntacticTreeGenerator::formLexicon()
{
    std::ifstream fin("case.lexicon");
    if(fin.fail())
    {
        std::cerr << std::strerror(errno);
    }
    else
    {
        std::string str;
        std::string grammaticalCase;
        
        while(!fin.eof())
        {
            if(grammaticalCase == "TOPIC") caseLexicon.push_back(Case(str, Case::TBD));
            else if(grammaticalCase == "SUBJECTIVE") caseLexicon.push_back(Case(str, Case::SUBJECTIVE));
            else if(grammaticalCase == "OBJECTIVE") caseLexicon.push_back(Case(str, Case::OBJECTIVE));
        }
    }
}

std::vector<SyntacticTree> SyntacticTreeGenerator::generateTrees(std::string str)
{
    std::vector<SyntacticTree> oTrees;
    std::vector<SyntacticTree> nTrees;
    
    std::vector<SyntacticTree>::iterator tIter, candidate;
    
    std::string character;
    
    
    oTrees.push_back( SyntacticTree() );
    
    
    for(std::string::iterator sIter = str.begin(); sIter != str.end();)
    {
        character = "";
        nTrees.clear();
        
        
        if(Decoder::isHangeul(*sIter))
        {
            character += *(sIter);
            character += *(sIter + 1);
            character += *(sIter + 2);
            
            
            
            for(tIter = oTrees.begin(); tIter != oTrees.end(); tIter++)
            {
                
                std::vector<SyntacticTree> candidates = addCharacterToTree(*tIter, character);
                
                for(candidate = candidates.begin(); candidate != candidates.end(); candidate++)
                {
                    nTrees.push_back(*candidate);
                }
                
            }
            
            
            oTrees.clear();
            while(!nTrees.empty())
            {
                oTrees.push_back(nTrees.back());
                nTrees.pop_back();
            }
            
            //UTF-8에서 한글은 3bytes이므로 3칸씩 건너 뜀
            sIter += 3;
        }
        else
        {
            //문장부호들
            if(*sIter == ' ')
            {
                while(!oTrees.empty())
                {
                    //띄어쓰기 단위로는 품사가 결정되어 있어야 한다. 정문이 품사가 결정되지 않은 경우 규칙을 추가하거나 바꿀 것.
                    if(oTrees.back().toBeDetermined.empty())
                    {
                        nTrees.push_back(oTrees.back());
                    }
                    oTrees.pop_back();
                }
                while(!nTrees.empty())
                {
                    oTrees.push_back(nTrees.back());
                    nTrees.pop_back();
                }
            }
            
            sIter++;
        }
        
        
        
    }
    
    std::vector<SyntacticTree> trees;
    
    for(tIter = oTrees.begin(); tIter != oTrees.end(); tIter++)
    {
        if(tIter->toBeDetermined.empty())
        {
            if( tIter->phraseStack.size() == 1 && tIter->xbarStack.empty() && tIter->headStack.empty())
            {
                trees.push_back(*tIter);
            }
        }
    }
    
    return trees;
    
    
    
}

//Private functions


std::vector<SyntacticTree> SyntacticTreeGenerator::addCharacterToTree(SyntacticTree tree, std::string character)
{
    std::vector<SyntacticTree> candidates;
    
    
    //들어온 문자가 어떤 뜻을 가지는지 모른다고 상정하는 경우
    SyntacticTree defaultCaseTree = tree;
    defaultCaseTree.toBeDetermined += character;
    candidates.push_back(defaultCaseTree);
    
    
    //들어온 문자가 특정한 역할을 하는 경우
    if(character == "은")
    {
        //앞 단어가 받침이 없을 때만
        if( Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::TBD));
        }
        if( tree.toBeDetermined != "")
        {
            candidates.push_back(projectTensePhrase(tree, character, Tense::PRESENT));
        }
    }
    else if(character == "는")
    {
        //앞 단어가 받침이 있을 때만
        if( ! Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::TBD));
        }
        if( tree.toBeDetermined != "")
        {
            candidates.push_back(projectTensePhrase(tree, character, Tense::PRESENT));
        }
    }
    else if(character == "이")
    {
        if( Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::SUBJECTIVE));
        }
    }
    else if(character == "가")
    {
        if( ! Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::SUBJECTIVE));
        }
    }
    else if(character == "을")
    {
        if( Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::OBJECTIVE));
        }
        if( tree.toBeDetermined != "")
        {
            candidates.push_back(projectTensePhrase(tree, character, Tense::FUTURE));
        }
    }
    else if(character == "를")
    {
        if( ! Decoder::endsWithCoda(tree.toBeDetermined) )
        {
            candidates.push_back(projectCasePhrase(tree, character, Case::OBJECTIVE));
        }
    }
    else if(character == "다")
    {
        Head* head = tree.phraseStack.back()->getHead();
        if(typeid(*head) == typeid(Tense))
        {
            candidates.push_back(projectComplementizerPhrase(tree, character));
        }
        
    }
    else if(character == "었" || character == "았")
    {
        if( tree.toBeDetermined != "")
        {
            candidates.push_back(projectTensePhrase(tree, character, Tense::PAST));
        }
        
    }
    else if(character == "에")
    {
        candidates.push_back(projectPostpositionPhrase(tree, character));
    }
    return candidates;
}
SyntacticTree SyntacticTreeGenerator::projectPostpositionPhrase(SyntacticTree tree, std::string character)
{
    SyntacticTree ppTree = tree;
    Noun* n = new Noun(ppTree.toBeDetermined);
    Postposition* p = new Postposition(character);
    
    ppTree.project(n);
    ppTree.project(p);
    
    return ppTree;
    
}
SyntacticTree SyntacticTreeGenerator::projectCasePhrase(SyntacticTree tree, std::string character, Case::Type grammaticalCase)
{
    SyntacticTree caseTree = tree;
    Noun* n = new Noun(caseTree.toBeDetermined);
    Case* c = new Case(character, grammaticalCase);
    
    caseTree.project(n);
    caseTree.project(c);
    
    return caseTree;
}
SyntacticTree SyntacticTreeGenerator::projectTensePhrase(SyntacticTree tree, std::string character, Tense::Type tense)
{
    SyntacticTree tenseTree = tree;
    Verb* v = new Verb(tenseTree.toBeDetermined);
    Tense* t = new Tense(character, tense);
    
    tenseTree.project(v);
    tenseTree.project(t);
    
    return tenseTree;
}
SyntacticTree SyntacticTreeGenerator::projectComplementizerPhrase(SyntacticTree tree, std::string character)
{
    SyntacticTree compTree = tree;
    Complementizer* c = new Complementizer(character);
    
    compTree.project(c);
    
    return compTree;
    
}