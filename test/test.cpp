#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 创建一个processInput函数实现一些输入控制
void processInput(GLFWwindow* window);

// 窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // 在main函数中调用glfwInit函数来初始化GLFW
    glfwInit();

    // glfwWindowHint函数的第一个参数代表选项的名称，可以从很多以GLFW_开头的枚举值中选择。第二个参数接受一个整型，用来设置这个选项的值
    // 将主版本号(Major)和次版本号(Minor)都设为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // GLFW_OPENGL_PROFILE指定要为其创建上下文的 OpenGL 配置文件。可能的值为GLFW_OPENGL_CORE_PROFILE或之一
    // 明确告诉GLFW我们使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     // 使用Mac OS X系统取消注释

    // 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
    // glfwCreateWindow函数需要窗口的宽和高作为它的前两个参数。
    // 第三个参数表示这个窗口的名称（标题）
    // 第四个和第五个暂时忽略
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    // 如果窗口创建失败，NULL会返回，所以需要检查返回值。
    // 窗口句柄被传递给所有与窗口相关的函数，并与所有输入事件一起提供，因此事件处理程序可以判断哪个窗口接收到事件。
    if (window == NULL)
    {
        // std::cout << "未能创建 GLFW 窗口" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
    // 给GLAD传入用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // std::cout << "初始化 GLAD 失败" << std::endl;
        return -1;
    }
    // 开始渲染之前，必须告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
    // 通过调用glViewport函数来设置窗口的维度
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    // 实际上也可以将视口的维度设置为比GLFW的维度小，这样子之后所有的OpenGL渲染将会在一个更小的窗口中显示，这样子的话我们也可以将一些其它元素显示在OpenGL视口之外
    // glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // 告诉GLFW我们希望每当窗口调整大小的时候调用这个函数，当窗口被第一次显示的时候framebuffer_size_callback也会被调用，所以上面的glViewport函数可以删除
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 渲染循环
    // glfwWindowShouldClose函数在每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        // 在渲染循环的每一个迭代中调用processInput
        processInput(window);

        // 渲染指令
        // ...
        // 在每个新的渲染迭代开始的时候调用glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲
        // 可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT     // 颜色缓冲、深度缓冲、模板缓冲
        // 调用glClearColor来设置清空屏幕所用的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 检查并调用事件，交换缓冲
        // glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);
        // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
        glfwPollEvents();
    }

    // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源，在main函数的最后调用glfwTerminate函数来完成
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // glfwGetKey函数需要一个窗口以及一个按键作为输入，这个函数将会返回这个按键是否正在被按下
    // 检查用户是否按下了返回键(Esc)
    //（如果没有按下，glfwGetKey将会返回GLFW_RELEASE。
    // 如果用户的确按下了返回键，我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。下一次while循环的条件检测将会失败，程序将会关闭。
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}