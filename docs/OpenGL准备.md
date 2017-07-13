###mac和win
####1. 需要4个库：[glfw](http://www.glfw.org/), [glew](https://github.com/nigels-com/glew), [soil](https://github.com/kbranigan/Simple-OpenGL-Image-Library) 和 [glm](https://github.com/g-truc/glm).
 * glfw用来打开窗口、生成OpenGL context、接入键盘鼠标控制等。
 * glew提供对应各平台OpenGL统一的接口，不需要自己根据平台不同而再做处理
 * soil用来加载图片，用于纹理生成。
 * glm提供了矩阵、向量等3D变量类型的定义和操作。glm只是头文件，和其他稍有不同。

 安装：
	
	1. 使用homebrew下载，除了soil，其他的都有,这个最方便。而soil可以用[stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)代替。
	2. 到网站下载代码，除了glm，其他几个都要编译成静态库才能用，而且要用[cmake](https://cmake.org/download/),因为各个平台不一样。cmake使用官网下载桌面程序（glfw和glew），或者在终端使用cmake命令（soil）。cmake程序使用先点击Configure，然后点Generate,在目标目录生成对应的程序。mac上是xcode,win上是vs，然后运行项目，编译静态库。soil下载好后，进入soil根目录,运行make & make install得到静态库。
	3. 或者使用我示例项目里编译好的包。
	4. 把静态库和对应的头文件放到项目里。
	
####2.初始配置

建好项目后，在main函数里开始编写。

* 配置GLFW
	
	```
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, 	GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	```
	mac上加上：
	
	`glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);`
	
	然后创建窗口：
	
	`GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);`
	
	使用窗口构建当前的context：
	`glfwMakeContextCurrent(window);`
	
	设置OpenGL的视野大小，这个是渲染的内容的大小，这里选择和window一样大。
	
	```
	int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
	```

* 初始化GLEW:

	```
	glewExperimental = GLFW_TRUE;
	if (glewInit() != GLEW_OK) {
	    std::cout<< "Failed to initilize GLEW" <<std::endl;
	    return -1;
	}
	```
* 循环调用渲染命令

	```
	while (!glfwWindowShouldClose(window)) {
	        glfwPollEvents();
	        
	        //Here is render commands
	        
	        glfwSwapBuffers(window);
	    }
	```
	glfwPollEvents处理窗口事件，有了这句窗口才能响应用户才做。
	glfwSwapBuffers 是切换前后缓冲区，即有两个缓冲区存储图像，一个是当前显示的，另一个是当前写入的，所以写入后要切换，让刚写入的显示，然后在渲染另一个缓冲区。这样可以让显示和写入同时进行，加快速度。
	
####3.简单测试
在渲染命令位置加上：

```
glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
```
glClearColor设置清除后的颜色，glClear对响应缓冲区进行清除，这里只清除颜色，使用GL_COLOR_BUFFER_BIT。

如果没问题，运行后，窗口填充为刚设置的颜色，即淡黄色。

###iOS
iOS上和电脑上比较不同，不需要第三方库管理窗口，而且Apple本身也有一些OpenGL ES上的封装。主要依据[Drawing to Other Rendering Destinations](https://developer.apple.com/library/content/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/WorkingwithEAGLContexts/WorkingwithEAGLContexts.html#//apple_ref/doc/uid/TP40008793-CH103-SW1)这一篇来处理。

1. 首先iOS上可以使用GLKit，这个是对OpenGL ES封装后的工具库，而为了学习，就不使用这个，而是自己搭建环境。
2. 根据上面的文档，主要就是建立自己的*Framebuffer*,它包含了一帧画面需要的颜色、深度和模板测试数据这些信息。我们使用绘制命令，把数据输出到Framebuffer里，然后framebuffer由一个和它贡献数据的*CAEAGLLayer*，由这个layer负责显示。

####所以根据文档进行操作：

1. 需要一个用来显示的view,新建一个UIView的子类用来封装我们的OpenGL ES绘制操作。`@interface TFGLView : UIView`,然后为了让它能呈现绘制的内容，把它的layer修改成`CAEAGLLayer`。

	```
+(Class)layerClass{
    return [CAEAGLLayer class];
}
```
2. 初始化EAGLContext

	`_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];`
这里使用OpenGL ES3，所以头文件导入为
`#import <OpenGLES/ES3/gl.h>`.

	然后把这个context设为当前context：
	`[EAGLContext setCurrentContext:_context]`
	
3. 初始化framebuffer
	
	```
	glGenBuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	```
	`glGenxxx`类型的函数很多，都是用来生成某个东西的，而拿到的一半都是int类型，也就是一个标志而已。比如这里生成一个framebuffer,你不会拿到一个对象，甚至内存地址都没有。_frameBuffer是`GLuint`类型。可以把它们看做一个id，我猜这样都是为了性能处理。写多了面向对象的程序，会对这样的状况稍有不适。
	
	`glBindxxx`也是常见类型，用来表示下面的操作都是针对绑定的对象的。比如这里，下面使用`GL_FRAMEBUFFER`的地方，都是对_frameBuffer的操作，知道你再次绑定了其他对象。

4. 构建colorbuffer,并把它附加到framebuffer上
 
 ```
 glGenRenderbuffers(1, &_colorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_renderLayer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorBuffer);
 ```
 前两句和framebuffer一样，先生成，然后绑定。第三句，给colorbuffer生成存储空间，这里使用了`_context`的方法，就是通过这里实现colorbuffer 和 _renderLayer的内存共享，所以之后_renderLayer可以显示colorbuffer的内容。
 
 	注意这里使用了GL_RENDERBUFFER，而不是 _colorBuffer，这就是glBindRenderbuffer绑定的作用.
 	
5. 设置OpenGL ES视野大小位置，即渲染的图像在layer中的位置和大小

	```
	GLint width,height;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    
    glViewport(0, 0, width, height);
	```
	同样使用glViewport函数。
 	
5. 检测一下framebuffer的状态，如果没问题就可以开始绘制了

	```
	    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    if(status != GL_FRAMEBUFFER_COMPLETE) {
        NSLog(@"failed to make complete framebuffer object %x", status);
    }
	```

####简单绘制

```
glBindFramebuffer(GL_FRAMEBUFFER, self.frameBuffer);
glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
```
glBindFramebuffer，保证这次渲染的目表是我们构建的framebuffer.
glClearColor设置清除后颜色，glClear清除缓冲区，GL_DEPTH_BUFFER_BIT是深度缓冲区，GL_COLOR_BUFFER_BIT是颜色缓冲区。如果不清除，那么上一次绘制的内容会保留，导致和这次绘制的内容叠加在一起。

然后把渲染结果提交显示：

```
glBindRenderbuffer(GL_RENDERBUFFER, self.colorBuffer);
[self.context presentRenderbuffer:GL_RENDERBUFFER];
```


 