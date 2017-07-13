//
//  TFFrameDisplayView.m
//  OPGLES_iOS
//
//  Created by wei shi on 2017/7/12.
//  Copyright © 2017年 wei shi. All rights reserved.
//

#import "TFTriangleDemoView.h"
#import <OpenGLES/ES3/gl.h>
#import <iostream>

@interface TFTriangleDemoView (){
    GLuint program;
    GLuint VAO;
}

@end

@implementation TFTriangleDemoView

const GLchar *vertexShaderSource =
"#version 300 es                            \n\
precision mediump float;                    \n\
layout (location = 0) in vec3 position;     \n\
void main(){                                \n\
gl_Position = vec4(position, 1.0f);         \n\
}                                           \n\
";
const GLchar *fragmentShaderSource =
"#version 300 es                            \n\
out mediump vec4  color;                    \n\
void main(){                                \n\
color = vec4(1.0f, 0.0f, 0.0f, 1.0f);       \n\
}                                           \n\
";

-(int)loadShadersAndLinkProgram{
    
    //load and compile shaders
    
    //vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);
    
    GLint succeed;
    GLchar infoLog[256];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeed);
    if (!succeed) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog),NULL, infoLog);
        std::cout<< "compile vertex shader error: "<< infoLog << std::endl;
        return -1;
    }
    
    //fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeed);
    if (!succeed) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog),NULL, infoLog);
        std::cout<< "compile fragment shader error: "<< infoLog << std::endl;
        return -1;
    }
    
    //attach shaders and link program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &succeed);
    if (!succeed) {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cout<< "link program error: "<< infoLog << std::endl;
        return -1;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return 0;
}

-(void)configData{
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    GLfloat vertices[] = {
        -0.5f, -0.3f, 0.0f,
        0.5f, -0.3f, 0.0f,
        0.0f, 0.7f, 0.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

-(void)layoutSubviews{
    [super layoutSubviews];
    
    [self rendering];
}

-(void)startRender{
    
    
    glViewport(0, 0, self.bufferSize.width, self.bufferSize.height);
    
    if ([self loadShadersAndLinkProgram] < 0) {
        return;
    }
    
    [self configData];
    
    [self rendering];
}

-(void)rendering{
    
    glBindFramebuffer(GL_FRAMEBUFFER, self.frameBuffer);
    
    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    
    glUseProgram(program);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
    glBindRenderbuffer(GL_RENDERBUFFER, self.colorBuffer);
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}

@end
