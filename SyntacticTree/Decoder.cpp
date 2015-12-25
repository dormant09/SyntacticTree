//
//  Decoder.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include "Decoder.hpp"

std::string Decoder::encodeUnicode(int code)
{
    std::string character;
    code += HANGEUL_INITIAL;
    
    char a, b, c;
    
    a = 224;
    b = 128;
    c = 128;
    
    
    
    for(int digit = 1; digit < 64; digit *= 2)
    {
        c += digit*(code % 2);
        code /= 2;
    }
    
    for(int digit = 1; digit < 64; digit *= 2)
    {
        b += digit*(code % 2);
        code /= 2;
    }
    
    for(int digit = 1; digit < 16; digit *= 2)
    {
        a += digit*(code % 2);
        code /= 2;
    }
    
    character += a;
    character += b;
    character += c;
    
    return character;
}
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
std::string Decoder::deleteCoda(std::string str)
{
    int pos = decodeUnicode( extractLastCharacter(str) );
    pos -= pos % HANGEUL_CODA_NUM;
    
    return encodeUnicode(pos);
}
std::string Decoder::extractCoda(std::string str)
{
    int pos = decodeUnicode( extractLastCharacter(str) );
    pos %= HANGEUL_CODA_NUM;
    
    if(pos == 1) return "ㄱ";
    else if(pos == 2) return "ㄲ";
    else if(pos == 3) return "ㄳ";
    else if(pos == 4) return "ㄴ";
    else if(pos == 5) return "ㄵ";
    else if(pos == 6) return "ㄶ";
    else if(pos == 7) return "ㄷ";
    else if(pos == 8) return "ㄹ";
    else if(pos == 9) return "ㄺ";
    else if(pos == 10) return "ㄻ";
    else if(pos == 11) return "ㄼ";
    else if(pos == 12) return "ㄽ";
    else if(pos == 13) return "ㄾ";
    else if(pos == 14) return "ㄿ";
    else if(pos == 15) return "ㅀ";
    else if(pos == 16) return "ㅁ";
    else if(pos == 17) return "ㅂ";
    else if(pos == 18) return "ㅄ";
    else if(pos == 19) return "ㅅ";
    else if(pos == 20) return "ㅆ";
    else if(pos == 21) return "ㅇ";
    else if(pos == 22) return "ㅈ";
    else if(pos == 23) return "ㅊ";
    else if(pos == 24) return "ㅋ";
    else if(pos == 25) return "ㅌ";
    else if(pos == 26) return "ㅍ";
    else if(pos == 27) return "ㅎ";
    else return "";
    
}
std::string Decoder::decomposeSyllable(std::string str)
{
    if(str.empty()) return str;
    
    std::string lastSyllable = extractLastCharacter(str);
    std::string result = decomposeSyllable(deleteLastCharacter(str));
    
    if(isHangeul(lastSyllable))
    {
        result += deleteCoda(lastSyllable);
        result += extractCoda(lastSyllable);
    }
    else
    {
        result += lastSyllable;
    }
    
    
    return result;
}
bool Decoder::isHangeul(std::string character)
{
    return isHangeul(character[0]);
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
