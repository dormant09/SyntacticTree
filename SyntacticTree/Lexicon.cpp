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
    if(!loadMoodDictionary()) return false;
    

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
            
            postpositions.insert(Decoder::decomposeSyllable(str));
            
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
            
            nouns.insert(Decoder::decomposeSyllable(str));
            
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
            
            verbs.insert(Decoder::decomposeSyllable(str));
            
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
            
            tenses.insert(Decoder::decomposeSyllable(str));
            
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
            
            complementizers.insert(Decoder::decomposeSyllable(str));
            
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
            
            adjectives.insert(Decoder::decomposeSyllable(str));
            
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
            
            adverbs.insert(Decoder::decomposeSyllable(str));
            
        }
        return true;
    }
}

bool Lexicon::loadMoodDictionary()
{
    std::ifstream fileIn("Resources/moods.lex");
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
            
            moods.insert(Decoder::decomposeSyllable(str));
            
        }
        return true;
    }
}

std::set< std::pair<std::string, std::string> > Lexicon::getConjugatablePair(std::string str, std::string pos)
{
    std::set< std::pair<std::string, std::string> > conjugatable;
    
    
    if(pos == "Verb" || pos == "Predicative")
    {
        //VP는 T의 complemnt가 될 수 있음을 의미
        conjugatable.insert(std::make_pair("Complement", "Tense"));
    }
    else if(pos == "Tense")
    {
        conjugatable.insert(std::make_pair("Complement", "Mood"));
    }
    else if(pos == "Noun")
    {
        conjugatable.insert(std::make_pair("Complement", "Postposition"));
        conjugatable.insert(std::make_pair("Complement", "Predicative"));
    }
    else if(pos == "Adverb")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Verb"));
        conjugatable.insert(std::make_pair("Adjunct", "Adjective"));
        conjugatable.insert(std::make_pair("Adjunct", "Tense"));
        conjugatable.insert(std::make_pair("Adjunct", "Mood"));
        conjugatable.insert(std::make_pair("Adjunct", "Complemlentizer"));
    }
    else if(pos == "Adjective")
    {
        conjugatable.insert(std::make_pair("Adjunct", "Noun"));
    }
    else if(pos == "Postposition")
    {
        if(str == "으ㄴ" || str == "느ㄴ" || str == "ㄴ")
        {
            //conjugatable.insert(std::make_pair("Complement", "Verb"));
            conjugatable.insert(std::make_pair("Spec", "Tense"));
        }
        else if(str == "으ㄹ" || str == "르ㄹ" || str == "ㄹ")
        {
            conjugatable.insert(std::make_pair("Complement", "Verb"));
        }
        else if(str == "이" || str == "가")
        {
            conjugatable.insert(std::make_pair("Spec", "Tense"));
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
    else if(pos == "Mood")
    {
        conjugatable.insert(std::make_pair("Complement", "Complementizer"));
        
    }
    else if(pos == "Complementizer")
    {
        if(str == "느ㄴ" || str == "Ø")
        {
            conjugatable.insert(std::make_pair("Adjunct", "Noun"));
        }
        else conjugatable.insert(std::make_pair("Adjunct", "Complementizer"));
        
        
        
    }
    
   
    
    return conjugatable;
}

