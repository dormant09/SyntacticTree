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
std::string Decoder::encodeUnicode(int unicode)
{
    unicode += HANGEUL_INITIAL;
    
    int code[16];
    
    for(int i=15; i>=0; i--)
    {
        code[i] = unicode % 2;
        unicode /= 2;
    }
    
    int decCode[3];
    
    
    decCode[0] = 224;
    int pos = 8;
    for(int i=0; i<4; i++)
    {
        decCode[0] += pos*code[i];
        pos /= 2;
    }
    
    decCode[1] = 128;
    pos = 32;
    for(int i=4; i<10; i++)
    {
        decCode[1] += pos*code[i];
        pos /= 2;
    }
    
    decCode[2] = 128;
    pos = 32;
    for(int i=10; i<16; i++)
    {
        decCode[2] += pos*code[i];
        pos /= 2;
    }
    
    std::string encoded;
    encoded += (char)decCode[0];
    encoded += (char)decCode[1];
    encoded += (char)decCode[2];
    
    return encoded;
}
bool Decoder::endsWithCoda(std::string str)
{
    std::string lastCharacter = str.substr(str.length() - 3, 3);
    
    int pos = decodeUnicode( lastCharacter );
    
    return (pos % HANGEUL_CODA_NUM != 0);
}

std::string Decoder::deleteCoda(std::string str)
{
    std::string lastCharacter = str.substr(str.length() - 3, 3);
    std::string remainder = str.substr(0, str.length() - 3);
    
    int pos = decodeUnicode( lastCharacter );
    int coda = pos % HANGEUL_CODA_NUM;
    
    pos -= coda;
    
    std::string codaDeletedCharacter = encodeUnicode(pos);
    return remainder + codaDeletedCharacter;

}

std::string Decoder::getCoda(std::string str)
{
    std::string lastCharacter = str.substr(str.length() - 3, 3);
    
    int pos = decodeUnicode( lastCharacter );
    int coda = pos % HANGEUL_CODA_NUM;
    
    if(coda == 0) return "";
    else if(coda == 1) return "ㄱ";
    else if(coda == 2) return "ㄲ";
    else if(coda == 3) return "ㄳ";
    else if(coda == 4) return "ㄴ";
    else if(coda == 5) return "ㄵ";
    else if(coda == 6) return "ㄶ";
    else if(coda == 7) return "ㄷ";
    else if(coda == 8) return "ㄹ";
    else if(coda == 9) return "ㄺ";
    else if(coda == 10) return "ㄻ";
    else if(coda == 11) return "ㄼ";
    else if(coda == 12) return "ㄽ";
    else if(coda == 13) return "ㄾ";
    else if(coda == 14) return "ㄿ";
    else if(coda == 15) return "ㅀ";
    else if(coda == 16) return "ㅁ";
    else if(coda == 17) return "ㅂ";
    else if(coda == 18) return "ㅄ";
    else if(coda == 19) return "ㅅ";
    else if(coda == 20) return "ㅆ";
    else if(coda == 21) return "ㅇ";
    else if(coda == 22) return "ㅈ";
    else if(coda == 23) return "ㅊ";
    else if(coda == 24) return "ㅋ";
    else if(coda == 25) return "ㅌ";
    else if(coda == 26) return "ㅍ";
    else return "ㅎ";

}

bool Decoder::isHangeul(char initial)
{
    //이진코드가 1110으로 시작하는지 확인
    return (initial & 0x80) == 0x80;
}