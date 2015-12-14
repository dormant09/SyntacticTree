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

std::string Decoder::extractLastCharacter(std::string str)
{
    std::string lastCharacter = "";
    
    for(std::string::iterator sIter = str.end() - 3; sIter != str.end(); sIter++)
    {
        lastCharacter += *sIter;
    }
    
    return lastCharacter;
}

bool Decoder::isHangeul(char initial)
{
    //이진코드가 1110으로 시작하는지 확인
    return (initial & 0x80) == 0x80;
}