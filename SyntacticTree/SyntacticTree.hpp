//
//  SyntacticTree.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef SyntacticTree_hpp
#define SyntacticTree_hpp

#include <vector>
#include "SyntacticNode.hpp"
#include "Decoder.hpp"

class SyntacticTree
{
    public :
    
    SyntacticTree();
    
    SyntacticTree addCharToTBD(std::string character);

    std::string toBeDetermined;
    
    
};

#endif /* SyntacticTree_hpp */
