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
#include "Decoder.hpp"

class Lexicon
{
    public :
    
    Lexicon();
    
    bool loadFiles();
    static std::set< std::pair<std::string, std::string> > getConjugatablePair(std::string str, std::string pos);
    
    std::set<std::string> nouns, postpositions, verbs, tenses, complementizers, adverbs, adjectives;
    
    
    private :
    
    bool loadNounDictionary();
    bool loadPostpositionDictionary();
    bool loadVerbDictionary();
    bool loadTenseDictionary();
    bool loadComplementizerDictionary();
    bool loadAdverbDictionary();
    bool loadAdjectiveDictionary();
    
};
#endif /* Lexicon_hpp */
