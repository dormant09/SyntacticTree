//
//  Lexicon.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 14..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "Lexicon.hpp"

Lexicon::Lexicon()
{
    formLexicon();
}
void Lexicon::formLexicon()
{
    formPostpositionLexicon();
    formComplementizerLexicon();
}
void Lexicon::formPostpositionLexicon()
{
    
    std::ifstream fin("postposition.lexicon");
    if(fin.fail())
    {
        std::cerr << std::strerror(errno);
    }
    else
    {
        std::string input;
        std::string str;
        std::string grammaticalCase;
        
        while(!fin.eof())
        {
            fin >> str >> grammaticalCase;
            
            
            if(grammaticalCase == "TOPIC")
            {
                postpositions.insert(std::map<std::string, Postposition>::value_type(str, Postposition(str, Case::TBD)));
            }
            else if(grammaticalCase == "SUBJECTIVE")
            {
                postpositions.insert(std::map<std::string, Postposition>::value_type(str, Postposition(str, Case::SUBJECTIVE)));
            }
            else if(grammaticalCase == "OBJECTIVE")
            {
                postpositions.insert(std::map<std::string, Postposition>::value_type(str, Postposition(str, Case::OBJECTIVE)));
            }
            
        }
        
    }
}
void Lexicon::formComplementizerLexicon()
{
    
    std::ifstream fin("complementizer.lexicon");
    if(fin.fail())
    {
        std::cerr << std::strerror(errno);
    }
    else
    {
        std::string input;
        std::string str;
        
        while(!fin.eof())
        {
            fin >> str;
        
            complementizers.insert(std::map<std::string, Complementizer>::value_type(str, Complementizer(str)));
            
        
            
        }
        
    }
}

