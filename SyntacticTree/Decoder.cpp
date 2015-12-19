//
//  Decoder.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "Decoder.hpp"

int Decoder::decodeUnicode(std::string character)
{
    int pos = 0;
    std::string::iterator cIter = character.begin();
    
    for(int i=3; i>=0; i--)
    {
        pos *= 2;
        pos += ((*cIter >> i) & 1);
    }
    
    cIter++;
    
    for(int i=5; i>=0; i--)
    {
        pos *= 2;
        pos += ((*cIter >> i) & 1);
    }
    
    cIter++;
    for(int i=5; i>=0; i--)
    {
        pos *= 2;
        pos += ((*cIter >> i) & 1);
    }
    
    return pos - HANGEUL_INITIAL;
}

bool Decoder::endsWithCoda(std::string str)
{
    int pos = decodeUnicode( extractLastCharacter(str) );
    
    return (pos % HANGEUL_CODA_NUM != 0);
}
bool Decoder::isHangeul(char initial)
{
    //이진코드가 1110으로 시작하는지 확인
    return (initial & 0xF0) == 0xE0;
}


std::string Decoder::extractLastCharacter(std::string str)
{
    std::string lastCharacter = "";
    
    if(isHangeul(*(str.end() - 3)))
    {
        lastCharacter += *(str.end() - 3);
        lastCharacter += *(str.end() - 2);
        lastCharacter += *(str.end() - 1);
    }
    else
    {
        lastCharacter += *(str.end() - 1);
    }
    
    return lastCharacter;
}

std::string Decoder::deleteLastCharacter(std::string str)
{
    std::string deletedStr;
    
    if(isHangeul(*(str.end() - 3)))
    {
        deletedStr = str.substr(0, str.length() - 3);
    }
    else
    {
        deletedStr = str.substr(0, str.length() - 1);
    }
    
    return deletedStr;
}
