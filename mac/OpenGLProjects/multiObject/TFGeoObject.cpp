//
//  TFGeoObject.cpp
//  multiObject
//
//  Created by shiwei on 2018/7/4.
//  Copyright © 2018年 wei shi. All rights reserved.
//

#include "TFGeoObject.hpp"

void TFGeoObject::applyMatrix(glm::mat4 &matrix){
    glUniformMatrix4fv(matrix_loc, 1, GL_FALSE, &matrix[0][0]);
}
