//
//  TFGeoObject.hpp
//  multiObject
//
//  Created by shiwei on 2018/7/4.
//  Copyright © 2018年 wei shi. All rights reserved.
//

#ifndef TFGeoObject_hpp
#define TFGeoObject_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glfw3.h"

class TFGeoObject {
    
protected:
    bool initFine;
    
    GLuint program;
    GLuint matrix_loc;
    GLuint VAO;
    
    virtual int loadShadersAndLinkProgram() = 0;
    virtual void configData() = 0;
    
public:
    bool isInitFine(){
        return initFine;
    }
    void applyMatrix(glm::mat4 &matrix);
    virtual void activate() = 0;
    virtual void draw() = 0;
};

#endif /* TFGeoObject_hpp */
