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
    SyntacticTreeGenerator *stg = new SyntacticTreeGenerator();
    stg->generateTrees("소년은 개울가에서 소녀를 보자");
    stg->printTrees();
    
    return 0;
}
