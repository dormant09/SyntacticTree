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
std::string Decoder::getCodaFromCode(int code)
{
    if(code == 1) return "ㄱ";
    else if(code == 2) return "ㄲ";
    else if(code == 3) return "ㄳ";
    else if(code == 4) return "ㄴ";
    else if(code == 5) return "ㄵ";
    else if(code == 6) return "ㄶ";
    else if(code == 7) return "ㄷ";
    else if(code == 8) return "ㄹ";
    else if(code == 9) return "ㄺ";
    else if(code == 10) return "ㄻ";
    else if(code == 11) return "ㄼ";
    else if(code == 12) return "ㄽ";
    else if(code == 13) return "ㄾ";
    else if(code == 14) return "ㄿ";
    else if(code == 15) return "ㅀ";
    else if(code == 16) return "ㅁ";
    else if(code == 17) return "ㅂ";
    else if(code == 18) return "ㅄ";
    else if(code == 19) return "ㅅ";
    else if(code == 20) return "ㅆ";
    else if(code == 21) return "ㅇ";
    else if(code == 22) return "ㅈ";
    else if(code == 23) return "ㅊ";
    else if(code == 24) return "ㅋ";
    else if(code == 25) return "ㅌ";
    else if(code == 26) return "ㅍ";
    else if(code == 27) return "ㅎ";
    else return "";
}
int Decoder::getCodeFromCoda(std::string coda)
{
    if(coda == "ㄱ") return 1;
    else if(coda == "ㄲ") return 2;
    else if(coda == "ㄳ") return 3;
    else if(coda == "ㄴ") return 4;
    else if(coda == "ㄵ") return 5;
    else if(coda == "ㄶ") return 6;
    else if(coda == "ㄷ") return 7;
    else if(coda == "ㄹ") return 8;
    else if(coda == "ㄺ") return 9;
    else if(coda == "ㄻ") return 10;
    else if(coda == "ㄼ") return 11;
    else if(coda == "ㄽ") return 12;
    else if(coda == "ㄾ") return 13;
    else if(coda == "ㄿ") return 14;
    else if(coda == "ㅀ") return 15;
    else if(coda == "ㅁ") return 16;
    else if(coda == "ㅂ") return 17;
    else if(coda == "ㅄ") return 18;
    else if(coda == "ㅅ") return 19;
    else if(coda == "ㅆ") return 20;
    else if(coda == "ㅇ") return 21;
    else if(coda == "ㅈ") return 22;
    else if(coda == "ㅊ") return 23;
    else if(coda == "ㅋ") return 24;
    else if(coda == "ㅌ") return 25;
    else if(coda == "ㅍ") return 26;
    else if(coda == "ㅎ") return 27;
    else return 0;
}
std::string Decoder::extractCoda(std::string str)
{
    int pos = decodeUnicode( extractLastCharacter(str) );
    pos %= HANGEUL_CODA_NUM;
    
    if(pos == 0) return "";
    else return getCodaFromCode(pos);
    
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
std::string Decoder::composeSyllable(std::string str)
{
    if(str.empty()) return str;
    
    std::string lastCharacter = extractLastCharacter(str);
    std::string remainder = deleteLastCharacter(str);
    
    if(isHangeulAlphabet(lastCharacter))
    {
        if(remainder.empty())
        {
            return lastCharacter;
        }
        else
        {
            std::string lastLastCharacter = extractLastCharacter(remainder);
            remainder = deleteLastCharacter(remainder);
            
            return composeSyllable(remainder) + encodeUnicode(decodeUnicode(lastLastCharacter) + getCodeFromCoda(lastCharacter));
            
        }
    }
    else
    {
        return composeSyllable(remainder) + lastCharacter;
    }
    
    
}
bool Decoder::isHangeul(std::string character)
{
    if(is3bytesEncoded(character[0]))
    {
        int code = decodeUnicode(character) + HANGEUL_INITIAL;
        
        return (code >= HANGEUL_INITIAL) && (code <= HANGEUL_FINAL);
    }
    else return false;
}
bool Decoder::isHangeulAlphabet(std::string character)
{
    if(is3bytesEncoded(character[0]))
    {
        int code = decodeUnicode(character) + HANGEUL_INITIAL;
        
        return (code >= HANGEUL_ALPHABET_INITIAL) && (code <= HANGEUL_ALPHABET_FINAL);
    }
    else return false;
}
bool Decoder::is3bytesEncoded(char initial)
{
    //이진코드가 1110으로 시작하는지 확인
    return (initial & 0xF0) == 0xE0;
}


std::string Decoder::extractLastCharacter(std::string str)
{
    std::string lastCharacter = "";
    
    if(is3bytesEncoded(*(str.end() - 3)))
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
    
    if(is3bytesEncoded(*(str.end() - 3)))
    {
        deletedStr = str.substr(0, str.length() - 3);
    }
    else
    {
        deletedStr = str.substr(0, str.length() - 1);
    }
    
    return deletedStr;
}
std::vector<std::string> Decoder::normalize(std::string str)
{
    std::vector<std::string> result;
    std::vector<std::string> normalized;
    std::vector<std::string>::iterator nIter, cIter;
    if(str.empty())
    {
        result.push_back(str);
        return result;
    }
    else
    {
        std::string lastCharacter = extractLastCharacter(str);
        std::string remainder = deleteLastCharacter(str);
        if(isHangeulAlphabet(lastCharacter))
        {
            std::string lastLastCharacter = extractLastCharacter(remainder);
            if((lastCharacter == "ㄴ") || (lastCharacter == "ㄹ"))
            {
                if(lastLastCharacter == "으")
                {
                    lastCharacter = lastLastCharacter + lastCharacter;
                    remainder = deleteLastCharacter(remainder);
                    lastLastCharacter = extractLastCharacter(remainder);
                    normalized = normalize(remainder);
                    
                    for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
                    {
                        result.push_back(*nIter + lastCharacter);
                        
                        if(!isHangeulAlphabet(lastLastCharacter))
                        {
                            result.push_back(*nIter + "ㅅ" + lastCharacter);
                            result.push_back(*nIter + "ㅎ" + lastCharacter);

                        }
                        
                    }
                    
                    return result;
                    
                }
                else if(lastLastCharacter == "느")
                {
                    lastCharacter = lastLastCharacter + lastCharacter;
                    remainder = deleteLastCharacter(remainder);
                    lastLastCharacter = extractLastCharacter(remainder);
                    normalized = normalize(remainder);
                    
                    for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
                    {
                        result.push_back(*nIter + lastCharacter);
                        if(!isHangeulAlphabet(lastLastCharacter))
                        {
                            result.push_back(*nIter + "ㄹ" + lastCharacter);
                            
                        }
                        
                    }
                    return result;
                }
                else
                {
                    normalized = normalize(remainder);
                    for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
                    {
                        result.push_back(*nIter + lastCharacter);
                        if(!isHangeulAlphabet(lastLastCharacter))
                        {
                            result.push_back(*nIter + "ㄹ" + lastCharacter);
                            if(lastCharacter == "ㄹ") result.push_back(*nIter + "ㄷ");
                            
                        }
                        
                    }
                    return result;
                }
            }
           
            
            normalized = normalize(deleteLastCharacter(str));
            for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
            {
                result.push_back(*nIter + lastCharacter);
            }
            
    
        }
        else if(isHangeul(lastCharacter))
        {
            normalized = normalize(remainder);
            std::vector<std::string> normalizedCharacter;
            normalizedCharacter.push_back(lastCharacter);
            
            if(lastCharacter == "게") normalizedCharacter.push_back("것이");
            else if(lastCharacter == "해") normalizedCharacter.push_back("하어");
            else if(lastCharacter == "돼") normalizedCharacter.push_back("되어");
            else if(lastCharacter == "내") normalizedCharacter.push_back("나");
            else if(lastCharacter == "네") normalizedCharacter.push_back("너");
            else if(lastCharacter == "제") normalizedCharacter.push_back("저");
            else if(lastCharacter == "와" || lastCharacter == "워") normalizedCharacter.push_back("ㅂ어");
            
            for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
            {
                for(cIter = normalizedCharacter.begin(); cIter != normalizedCharacter.end(); cIter++)
                {
                    result.push_back((*nIter) + (*cIter));
                }
            }
            
        }
        else
        {
            normalized = normalize(deleteLastCharacter(str));
            for(nIter = normalized.begin(); nIter != normalized.end(); nIter++)
            {
                result.push_back(*nIter + lastCharacter);
            }
            
        }
        
        
        return result;
    }
}