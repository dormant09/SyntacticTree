//
//  main.cpp
//  SyntacticTree
//
//  Created by Sijoon Kim on 2015. 12. 10..
//  Copyright © 2015년 Sijoon Kim. All rights reserved.
//

#include <iostream>
#include "SyntacticTreeGenerator.hpp"

int main(int argc, const char * argv[])
{
    
    std::cout << Decoder::decomposeSyllable("나는 사람이었다.") << std::endl;
    //SyntacticTreeGenerator *stg = new SyntacticTreeGenerator();
    //stg->generateTrees("나는 사람이었다.");
    //stg->printTrees();
    
    return 0;
}
