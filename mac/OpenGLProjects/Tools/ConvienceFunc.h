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


#define ShaderString(str) "#"#str

#define standardTriangle {-0.5f, -0.4f, 0.0f,   0.5f, -0.4f, 0.0f,   0.0f, 0.45f, 0.0f}
#define standardRectangle {-0.5f, 0.5f, 0.0f,   -0.5f, -0.5f, 0.0f,   0.5f, 0.5f, 0.0f,   0.5f, -0.5f, 0.0f}
#define standardRectangleIndices {0, 1, 3, 0, 3, 2}

#define standardCube {-0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, 0.5f,   0.5f, 0.5f, 0.5f,   0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, -0.5f,   -0.5f, -0.5f, -0.5f,   0.5f, 0.5f, -0.5f,   0.5f, -0.5f, -0.5f}
#define standardCubeTexcoord {0,0, 0,1, 1,0, 1,1, 0,0, 0,1, 1,0, 1,1}
#define standardCubeIndices {0,1,2,3, 2,3,6,7, 3,1,7,5, 1,0,5,4, 0,2,4,6, 4,5,6,7}


inline void copyVertex(GLfloat *v1, GLfloat *v2){
    for (int i = 0; i<3; i++) {
        *v1 = *v2;
        v1++;
        v2++;
    }
}


#endif /* ConvienceFunc_h */
