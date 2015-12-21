//
//  Decoder.hpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#ifndef Decoder_hpp
#define Decoder_hpp

#include <string>



class Decoder
{
    public :
    
    static const int HANGEUL_INITIAL = 44032; //"가"의 UTF-8 코드의 십진수 값
    static const int HANGEUL_FINAL = 55203; //"힣"의 UTF-8 코드의 십진수 값
    
    static const int HANGEUL_ONSET_NUM = 19;
    static const int HANGEUL_NUCLEUS_NUM = 21;
    static const int HANGEUL_CODA_NUM = 28;
    
    static int decodeUnicode(std::string character);
    static std::string encodeUnicode(int code);
    static bool endsWithCoda(std::string str);
    static std::string deleteCoda(std::string str);
    static std::string extractCoda(std::string str);
    static bool isHangeul(char initial);
    
    
    static std::string extractLastCharacter(std::string str);
    static std::string deleteLastCharacter(std::string str);
};


#endif /* Decoder_hpp */
