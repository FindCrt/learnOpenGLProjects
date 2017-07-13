//
//  TFFrameDisplayView.m
//  OPGLES_iOS
//
//  Created by wei shi on 2017/7/12.
//  Copyright © 2017年 wei shi. All rights reserved.
//

#import "TFTriangleDemoView.h"
#import <OpenGLES/ES3/gl.h>

@interface TFTriangleDemoView (){
    
    GLuint VAO;
}

@end

@implementation TFTriangleDemoView

-(void)layoutSubviews{
    [super layoutSubviews];
    
    [self rendering];
}

-(void)startRender{
    
//    GLfloat vertices[] = {
//        -0.5f, -0.3f, 0.0f,
//        0.5f, -0.3f, 0.0f,
//        0.0f, 0.6f, 0.0f
//    };
//    
//    NSString *vertexPath = [[NSBundle mainBundle] pathForResource:@"triangle" ofType:@"vs"];
//    NSString *fragmentPath = [[NSBundle mainBundle] pathForResource:@"triangle" ofType:@"fs"];
//    _triangleProgram = new TFOPGLProgram([vertexPath UTF8String], [fragmentPath UTF8String]);
//    
//    
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    
//    GLuint VBO;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0);
//    glEnableVertexAttribArray(0);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
    
    glViewport(0, 0, self.bufferSize.width, self.bufferSize.height);
}

-(void)rendering{
    
    glBindFramebuffer(GL_FRAMEBUFFER, self.frameBuffer);
    
    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    
    //_triangleProgram->use();
    
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
    glBindRenderbuffer(GL_RENDERBUFFER, self.colorBuffer);
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}

@end
