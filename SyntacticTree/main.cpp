//
//  main.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include <iostream>
#include "SyntacticTreeGenerator.hpp"

int main(int argc, const char * argv[])
{
    static SyntacticTreeGenerator *stg = new SyntacticTreeGenerator();
    
    std::vector<SyntacticTree> trees;
    trees = stg->generateTrees("나는 밥을 먹는다");
    
    for(std::vector<SyntacticTree>::iterator tIter = trees.begin(); tIter != trees.end(); tIter++)
    {
        std::string taggedSyntax = tIter->getTaggedString();
        std::cout << taggedSyntax << std::endl;
    }
    
    return 0;
}
