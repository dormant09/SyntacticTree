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
    
    
    static std::vector<SyntacticTree> generateTrees(std::string str);
    
    
    
    private :
    
    static bool isHangeul(char initial);
    
    static std::vector<SyntacticTree> addCharacterToTree(SyntacticTree tree, std::string character);
    
    static SyntacticTree projectCasePhrase(SyntacticTree tree, std::string character, Case::Type grammaticalCase);
    static SyntacticTree projectTensePhrase(SyntacticTree tree, std::string character);
    static SyntacticTree projectComplementizerPhrase(SyntacticTree tree, std::string character);
    
};
#endif /* SyntacticTreeGenerator_hpp */
