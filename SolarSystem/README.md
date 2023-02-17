参考链接
	C++ 实现太阳系行星系统（OpenGL）https://blog.csdn.net/github_39533414/article/details/84898477
	openGL编程学习(3):太阳、地球、月亮（含自转和公转）和航天飞机 https://blog.csdn.net/qq_41310405/article/details/109137944
	learnopengl官方网站 https://learnopengl-cn.github.io/
	OpenGL入门三——变换进阶 https://mp.weixin.qq.com/s/PXMD1bIlBFAljg1Twr0SQg


texture.cpp 
	line 18, 19:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	若采用GL_CLAMP_TO_BORDER参数，球体拼接处会存在黑线
	地球旋转时纹理贴图存在形变，
	希望地球绕着某倾斜轴旋转