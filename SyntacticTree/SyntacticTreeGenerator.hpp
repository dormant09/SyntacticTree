//
//  SyntacticTreeGenerator.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticTreeGenerator_hpp
#define SyntacticTreeGenerator_hpp

#include <string>
#include <iostream>
#include <vector>
#include "SyntacticTree.hpp"

class SyntacticTreeGenerator
{

    public :
    
    SyntacticTreeGenerator();
    void generateTrees(std::string str);
    
    
    private :
    
    
    std::vector<SyntacticTree> addCharacter(SyntacticTree tree, std::string character);
    std::vector<SyntacticTree> generatePartOfTrees(std::string str);
    std::vector<SyntacticTree> trees;
    
};
#endif /* SyntacticTreeGenerator_hpp */
