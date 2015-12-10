//
//  SyntacticTree.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticTree_hpp
#define SyntacticTree_hpp

#include <string>
#include <iostream>
#include <vector>
#include "SyntacticNode.hpp"

class SyntacticTree
{
    public :
    
        SyntacticTree();
    
    
        std::vector<SyntacticTree> add(std::string character);
    
        bool isValid();
    
        void setValid();
    
    
    
    private :
    
        bool validity;
    
        std::string toBeDetermined;
    
    
};

#endif /* SyntacticTree_hpp */
