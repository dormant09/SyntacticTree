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

std::set< std::pair<std::string, std::string> > Lexicon::getConjugatablePair(std::string str, std::string pos)
{
    std::set< std::pair<std::string, std::string> > conjugatable;
    
    
    if(pos == "Verb")
    {
        //VP는 T의 complemnt가 될 수 있음을 의미
        conjugatable.insert(std::make_pair("Complement", "Tense"));
    }
    else if(pos == "Tense")
    {
        conjugatable.insert(std::make_pair("Complement", "Complementizer"));
    }
    else if(pos == "Noun")
    {
        conjugatable.insert(std::make_pair("Complement", "Postposition"));
    }
    else if(pos == "Adverb")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Verb"));
        conjugatable.insert(std::make_pair("Adjunct", "Adjective"));
        conjugatable.insert(std::make_pair("Adjunct", "Tense"));
        conjugatable.insert(std::make_pair("Adjunct", "Complemlentizer"));
    }
    else if(pos == "Adjective")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Noun"));
    }
    else if(pos == "Postposition")
    {
        if(str == "은" || str == "는" || str == "ㄴ")
        {
            //conjugatable.insert(std::make_pair("Complement", "Verb"));
            conjugatable.insert(std::make_pair("Spec", "Tense"));
        }
        else if(str == "을" || str == "를" || str == "ㄹ")
        {
            conjugatable.insert(std::make_pair("Complement", "Tense"));
        }
        else if(str == "이" || str == "가")
        {
            conjugatable.insert(std::make_pair("Spec", "Verb"));
        }
        else if(str == "의")
        {
            conjugatable.insert(std::make_pair("Adjunct", "Noun"));
        }
        else
        {
            conjugatable.insert(std::make_pair("Adjunct", "Verb"));
        }
    }
    else if(pos == "Complementizer")
    {
        
    }
    
    return conjugatable;
}

