//
//  ConvienceFunc.h
//  OpenGLProjects
//
//  Created by shiwei on 2018/6/13.
//  Copyright © 2018年 wei shi. All rights reserved.
//

#ifndef ConvienceFunc_h
#define ConvienceFunc_h

#include <stdio.h>
#include "glew.h"

#define ShaderString(str) "#"#str

#define standardTriangle {-0.5f, -0.4f, 0.0f,   0.5f, -0.4f, 0.0f,   0.0f, 0.45f, 0.0f}
#define standardRectangle {-0.5f, 0.5f, 0.0f,   -0.5f, -0.5f, 0.0f,   0.5f, 0.5f, 0.0f,   0.5f, -0.5f, 0.0f}
#define standardRectangleIndices {0, 1, 3, 1, 3, 2}

#define standardCube {-0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, 0.5f,   0.5f, 0.5f, 0.5f,   0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, -0.5f,   -0.5f, -0.5f, -0.5f,   0.5f, 0.5f, -0.5f,   0.5f, -0.5f, -0.5f}
#define standardCubeIndices {0,1,2,3, 2,3,7,8, 3,1,8,5, 1,0,5,4, 0,2,4,7, 4,5,7,8}


#endif /* ConvienceFunc_h */
