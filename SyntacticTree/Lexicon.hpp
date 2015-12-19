//
//  Lexicon.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 19..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef Lexicon_hpp
#define Lexicon_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>

class Lexicon
{
    public :
    
    Lexicon();
    
    bool loadFiles();
    
    std::set<std::string> nouns, postpositions;
    std::set< std::pair<std::string, std::string> > complementRule;
    
    private :
    
    bool loadNounDictionary();
    bool loadPostpositionDictionary();
    
    bool loadComplementRule();
};
#endif /* Lexicon_hpp */
