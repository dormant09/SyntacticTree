//
//  Lexicon.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 19..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "Lexicon.hpp"


Lexicon::Lexicon()
{
    
}

bool Lexicon::loadFiles()
{
    if(!loadNounDictionary()) return false;
    if(!loadPostpositionDictionary()) return false;
    
    if(!loadComplementRule()) return false;

    return true;
}
bool Lexicon::loadPostpositionDictionary()
{
    std::ifstream fileIn("Resources/postpositions.lex");
    if(fileIn.fail())
    {
        std::cerr << "File not found : " << std::strerror(errno) << std::endl;
        return false;
    }
    else
    {
        while(!fileIn.eof())
        {
            std::string str;
            fileIn >> str;
            
            postpositions.insert(str);
            
        }
        return true;
    }
}

bool Lexicon::loadNounDictionary()
{
    std::ifstream fileIn("Resources/nouns.lex");
    if(fileIn.fail())
    {
        std::cerr << "File not found : " << std::strerror(errno) << std::endl;
        return false;
    }
    else
    {
        while(!fileIn.eof())
        {
            std::string str;
            fileIn >> str;
            
            nouns.insert(str);
            
        }
        return true;
    }
}

bool Lexicon::loadComplementRule()
{
    std::ifstream fileIn("Resources/complement.psr");
    if(fileIn.fail())
    {
        std::cerr << "File not found : " << std::strerror(errno) << std::endl;
        return false;
    }
    else
    {
        while(!fileIn.eof())
        {
            std::string left, right;
            fileIn >> left >> right;
            
            complementRule.insert(std::make_pair(left, right));
            
        }
        return true;
    }
}

