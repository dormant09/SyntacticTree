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
}


void SyntacticTreeGenerator::generateTrees(std::string str)
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
}

//Private functions

bool SyntacticTreeGenerator::isHangeul(char initial)
{
    //이진코드가 1110으로 시작하는지 확인
    return (initial & 0x80) == 0x80;
}