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
#include <vector>
#include "Lexicon.hpp"
#include "SyntacticTree.hpp"

class SyntacticTreeGenerator
{

    public :
    
    SyntacticTreeGenerator();
    void generateTrees(std::string str);
    void printTrees();
    
    
    private :
    
    Lexicon lexicon;
    std::vector<SyntacticTree> trees;
    
    std::vector<SyntacticTree> addPhiToTree(SyntacticTree tree);
    SyntacticTree projectHead(SyntacticTree tree, Head* h);
    std::vector<SyntacticTree> addCharacter(SyntacticTree tree, std::string character);
    std::vector<SyntacticTree> generatePartOfTrees(std::string str);
    
};
#endif /* SyntacticTreeGenerator_hpp */
