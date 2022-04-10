#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// ����һ��processInput����ʵ��һЩ�������
void processInput(GLFWwindow* window);

// ���ڴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // ��main�����е���glfwInit��������ʼ��GLFW
    glfwInit();

    // glfwWindowHint�����ĵ�һ����������ѡ������ƣ����ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񡣵ڶ�����������һ�����ͣ������������ѡ���ֵ
    // �����汾��(Major)�ʹΰ汾��(Minor)����Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // GLFW_OPENGL_PROFILEָ��ҪΪ�䴴�������ĵ� OpenGL �����ļ������ܵ�ֵΪGLFW_OPENGL_CORE_PROFILE��֮һ
    // ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     // ʹ��Mac OS Xϵͳȡ��ע��

    // ����һ�����ڶ���������ڶ����������кʹ�����ص����ݣ����һᱻGLFW����������Ƶ�����õ���
    // glfwCreateWindow������Ҫ���ڵĿ�͸���Ϊ����ǰ����������
    // ������������ʾ������ڵ����ƣ����⣩
    // ���ĸ��͵������ʱ����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    // ������ڴ���ʧ�ܣ�NULL�᷵�أ�������Ҫ��鷵��ֵ��
    // ���ھ�������ݸ������봰����صĺ������������������¼�һ���ṩ������¼������������ж��ĸ����ڽ��յ��¼���
    if (window == NULL)
    {
        // std::cout << "δ�ܴ��� GLFW ����" << std::endl;
        glfwTerminate();
        return -1;
    }

    // �����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
    glfwMakeContextCurrent(window);

    // GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
    // ��GLAD������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // std::cout << "��ʼ�� GLAD ʧ��" << std::endl;
        return -1;
    }
    // ��ʼ��Ⱦ֮ǰ���������OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
    // ͨ������glViewport���������ô��ڵ�ά��
    // glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
    // ʵ����Ҳ���Խ��ӿڵ�ά������Ϊ��GLFW��ά��С��������֮�����е�OpenGL��Ⱦ������һ����С�Ĵ�������ʾ�������ӵĻ�����Ҳ���Խ�һЩ����Ԫ����ʾ��OpenGL�ӿ�֮��
    // glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // ����GLFW����ϣ��ÿ�����ڵ�����С��ʱ�������������������ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���ã����������glViewport��������ɾ��
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ��Ⱦѭ��
    // glfwWindowShouldClose������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ���������
    while (!glfwWindowShouldClose(window))
    {
        // ����
        // ����Ⱦѭ����ÿһ�������е���processInput
        processInput(window);

        // ��Ⱦָ��
        // ...
        // ��ÿ���µ���Ⱦ������ʼ��ʱ�����glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���
        // ���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT     // ��ɫ���塢��Ȼ��塢ģ�建��
        // ����glClearColor�����������Ļ���õ���ɫ
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ��鲢�����¼�����������
        // glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
        glfwSwapBuffers(window);
        // glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
        glfwPollEvents();
    }

    // ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ����main������������glfwTerminate���������
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // glfwGetKey������Ҫһ�������Լ�һ��������Ϊ���룬����������᷵����������Ƿ����ڱ�����
    // ����û��Ƿ����˷��ؼ�(Esc)
    //�����û�а��£�glfwGetKey���᷵��GLFW_RELEASE��
    // ����û���ȷ�����˷��ؼ������ǽ�ͨ��glfwSetwindowShouldCloseʹ�ð�WindowShouldClose��������Ϊ true�ķ����ر�GLFW����һ��whileѭ����������⽫��ʧ�ܣ����򽫻�رա�
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}