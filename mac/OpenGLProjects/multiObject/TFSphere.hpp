//
//  TFSphere.hpp
//  multiObject
//
//  Created by shiwei on 2018/7/4.
//  Copyright © 2018年 wei shi. All rights reserved.
//

#ifndef TFSphere_hpp
#define TFSphere_hpp

#include "TFGeoObject.hpp"

class TFSphere : public TFGeoObject {
    
    GLfloat radius = 1.f;
    
    int actualSize;
    int fanSize;
    
protected:
    int loadShadersAndLinkProgram();
    void configData();
    
public:
    TFSphere(GLfloat radius = 1.f);
    void activate();
    void draw();
};

#endif /* TFSphere_hpp */
