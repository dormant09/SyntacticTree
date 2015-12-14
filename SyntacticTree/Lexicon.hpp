//
//  Lexicon.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 14..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef Lexicon_hpp
#define Lexicon_hpp

#include <iostream>
#include <fstream>
#include <map>

#include "SyntacticNode.hpp"

class Lexicon
{
    public :
    
    Lexicon();
    
    void formLexicon();
    
    
    std::map<std::string, Postposition> postpositions;
};

#endif /* Lexicon_hpp */
