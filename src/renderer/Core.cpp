#include "Core.h"

Core::Core()
{
    init();
}

Core::~Core()
{
    destroy();
}

int Core::init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    return true;
}

void Core::run(GLFWwindow *window, InputManager &inputManager)
{

    //TESTING VAO, VBO, EBO
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    VAO vao;
    VBO vbo(vertices, sizeof(vertices));
    vao.AddBuffer(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    Shader shader("/Users/blaga/Documents/GitHub/TitaniumChess/assets/shaders/vertexShader.vert", "/Users/blaga/Documents/GitHub/TitaniumChess/assets/shaders/fragmentShader.frag");

    // ----------------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        inputManager.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEST DRAW TRIANGLE
        vbo.Bind();
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // ----------------------------


         // Începere interfață ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Desenează interfața ImGui
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        ImGui::End();

        // Finalizare desen interfață ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // ----------------------------

        glfwSwapBuffers(window);
    }
}

void Core::destroy()
{
    // Încheiere ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // ----------------------------

    glfwTerminate();
}