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
    
    std::set<std::string> nouns, postpositions, verbs, tenses, complementizers;
    std::set< std::pair<std::string, std::string> > complementRule, adjunctRule, specRule;
    
    private :
    
    bool loadNounDictionary();
    bool loadPostpositionDictionary();
    bool loadVerbDictionary();
    bool loadTenseDictionary();
    bool loadComplementizerDictionary();
    
    bool loadComplementRule();
    bool loadAdjunctRule();
    bool loadSpecRule();
};
#endif /* Lexicon_hpp */
