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
    
    
    static void generateTrees(std::string str);
    
    
    
    private :
    
    
    static bool isHangeul(char initial);
    
    static std::vector<SyntacticTree> trees;
    
    static std::vector<SyntacticTree> add(SyntacticTree tree, std::string character);
    
};
#endif /* SyntacticTreeGenerator_hpp */
