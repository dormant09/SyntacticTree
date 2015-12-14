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
    
    
    std::vector<SyntacticTree> generateTrees(std::string str);
    
    
    
    private :
    
    
    
    std::vector<SyntacticTree> addCharacterToTree(SyntacticTree tree, std::string character);
    
    SyntacticTree projectCasePhrase(SyntacticTree tree, std::string character, Case::Type grammaticalCase);
    SyntacticTree projectTensePhrase(SyntacticTree tree, std::string character, Tense::Type tense);
    SyntacticTree projectComplementizerPhrase(SyntacticTree tree, std::string character);
    SyntacticTree projectPostpositionPhrase(SyntacticTree tree, std::string character);
    
};
#endif /* SyntacticTreeGenerator_hpp */
