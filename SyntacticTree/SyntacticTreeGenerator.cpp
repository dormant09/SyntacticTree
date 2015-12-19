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
        /*
         
         TODO
         
         lastCharacter 뽑아내기
         lastCharacter를 지워서 Recursive function에 넣기
         받아온 결과에 lastCharacter를 넣기
         
         */
        return std::vector<SyntacticTree>();
    }
    
}

void SyntacticTreeGenerator::generateTrees(std::string str)
{
    trees = generatePartOfTrees(str);
    /*
    std::vector<SyntacticTree> oTrees;
    std::vector<SyntacticTree> nTrees;
    
    std::vector<SyntacticTree>::iterator tIter, candidate;
    
    std::string character;
    
    
    oTrees.push_back( SyntacticTree() );
    
    
    for(std::string::iterator sIter = str.begin(); sIter != str.end();)
    {
        character = "";
        nTrees.clear();
        
        
        if(isHangeul(*sIter))
        {
            character += *(sIter);
            character += *(sIter + 1);
            character += *(sIter + 2);
            
            
            
            for(tIter = oTrees.begin(); tIter != oTrees.end(); tIter++)
            {
                std::vector<SyntacticTree> candidates = tIter->add(character);
                
                for(candidate = candidates.begin(); candidate != candidates.end(); candidate++)
                {
                    if(candidate->isValid()) nTrees.push_back(*candidate);
                }
                
            }
            
            
            //UTF-8에서 한글은 3bytes이므로 3칸씩 건너 뜀
            sIter += 3;
        }
        else
        {
            sIter++;
        }
        
        oTrees.clear();
        while(!nTrees.empty())
        {
            oTrees.push_back(nTrees.back());
            nTrees.pop_back();
        }
        
    }
     */
}
