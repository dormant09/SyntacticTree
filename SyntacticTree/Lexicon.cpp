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
    if(!loadVerbDictionary()) return false;
    if(!loadTenseDictionary()) return false;
    if(!loadComplementizerDictionary()) return false;
    if(!loadAdjectiveDictionary()) return false;
    if(!loadAdverbDictionary()) return false;
    
    if(!loadComplementRule()) return false;
    if(!loadAdjunctRule()) return false;
    if(!loadSpecRule()) return false;

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

bool Lexicon::loadVerbDictionary()
{
    std::ifstream fileIn("Resources/verbs.lex");
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
            
            verbs.insert(str);
            
        }
        return true;
    }
}

bool Lexicon::loadTenseDictionary()
{
    std::ifstream fileIn("Resources/tenses.lex");
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
            
            tenses.insert(str);
            
        }
        return true;
    }
}

bool Lexicon::loadComplementizerDictionary()
{
    std::ifstream fileIn("Resources/complementizers.lex");
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
            
            complementizers.insert(str);
            
        }
        return true;
    }
}
bool Lexicon::loadAdjectiveDictionary()
{
    std::ifstream fileIn("Resources/adjectives.lex");
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
            
            adjectives.insert(str);
            
        }
        return true;
    }
}

bool Lexicon::loadAdverbDictionary()
{
    std::ifstream fileIn("Resources/adverbs.lex");
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
            
            adverbs.insert(str);
            
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

bool Lexicon::loadAdjunctRule()
{
    std::ifstream fileIn("Resources/adjunct.psr");
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
            
            adjunctRule.insert(std::make_pair(left, right));
            
        }
        return true;
    }
}

bool Lexicon::loadSpecRule()
{
    std::ifstream fileIn("Resources/spec.psr");
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
            
            specRule.insert(std::make_pair(left, right));
            
        }
        return true;
    }
}


