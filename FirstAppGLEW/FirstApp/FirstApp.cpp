/* sierpinski gasket using vertex buffer objects */

#include "Angel.h"

const int NumPoints = 200;
vec3 points[NumPoints];
vec3 colors[NumPoints];
GLuint shader1, shader2, currentShader;
vec4 uniformColor1, uniformColor2;

static GLfloat xCenter = 0.0f, yCenter = 0.0f;
static GLfloat magnify = 1.0f;
static int windowWidth, windowHeight;
static GLfloat worldMousePositionX, worldMousePositionY;

enum Shapes {L, J, Z, S, O, I, T};

enum State {MYINPUT, DRAGGING};
State state = MYINPUT;
Shapes selectedShape = L;

struct ShapeInfo
{
    int start;
    int nVertices;
    Shapes shape;
    vec4 color;
    vec3 position;
    GLfloat rotation;
    vec3 scale;
};

struct StartEnd
{
    int start;
    int nVertices;
};

ShapeInfo allShapes[7] = {};
StartEnd startEnds[7] = {};
int nextShapePosition = 0;
int currentShape = -1;
float currentRotation = 0.0f;

//----------------------------------------------------------------------------
/* This function initializes an array of 3d vectors 
   and sends it to the graphics card along with shaders
   properly connected to them.
*/

void
init( void ) //{L, J, Z, S, O, I, T};
{
    startEnds[L].start = 0;
    startEnds[L].nVertices = 24;

    startEnds[J].start = 24;
    startEnds[J].nVertices = 24;

    startEnds[Z].start = 48;
    startEnds[Z].nVertices = 24;

    startEnds[S].start = 72;
    startEnds[S].nVertices = 24;

    startEnds[O].start = 96;
    startEnds[O].nVertices = 24;

    startEnds[I].start = 120;
    startEnds[I].nVertices = 24;

    startEnds[T].start = 144;
    startEnds[T].nVertices = 24;


    //L complete
    points[0] = vec3(-1.0, 1.0, 0.0);
    points[1] = vec3(0.0, 0.0, 0.0);
    points[2] = vec3(-1.0, 0.0, 0.0);
    points[3] = vec3(-1.0, 1.0, 0.0);
    points[4] = vec3(0.0, 1.0, 0.0);
    points[5] = vec3(0.0, 0.0, 0.0);

    points[6] = vec3(-2.0, 1.0, 0.0);
    points[7] = vec3(-1.0, 0.0, 0.0);
    points[8] = vec3(-2.0, 0.0, 0.0);
    points[9] = vec3(-2.0, 1.0, 0.0);
    points[10] = vec3(-1.0, 1.0, 0.0);
    points[11] = vec3(-1.0, 0.0, 0.0);

    points[12] = vec3(-3.0, 2.0, 0.0);
    points[13] = vec3(-2.0, 1.0, 0.0);
    points[14] = vec3(-3.0, 1.0, 0.0);
    points[15] = vec3(-3.0, 2.0, 0.0);
    points[16] = vec3(-2.0, 2.0, 0.0);
    points[17] = vec3(-2.0, 1.0, 0.0);

    points[18] = vec3(-3.0, 1.0, 0.0);
    points[19] = vec3(-2.0, 0.0, 0.0);
    points[20] = vec3(-3.0, 0.0, 0.0);
    points[21] = vec3(-3.0, 1.0, 0.0);
    points[22] = vec3(-2.0, 1.0, 0.0);
    points[23] = vec3(-2.0, 0.0, 0.0);

    //J complete
    points[24] = vec3(-1.0, 1.0, 0.0);
    points[25] = vec3(0.0, 0.0, 0.0);
    points[26] = vec3(-1.0, 0.0, 0.0);
    points[27] = vec3(-1.0, 1.0, 0.0);
    points[28] = vec3(0.0, 1.0, 0.0);
    points[29] = vec3(0.0, 0.0, 0.0);

    points[30] = vec3(-2.0, 1.0, 0.0);
    points[31] = vec3(-1.0, 0.0, 0.0);
    points[32] = vec3(-2.0, 0.0, 0.0);
    points[33] = vec3(-2.0, 1.0, 0.0);
    points[34] = vec3(-1.0, 1.0, 0.0);
    points[35] = vec3(-1.0, 0.0, 0.0);

    points[36] = vec3(-1.0, 2.0, 0.0);
    points[37] = vec3(0.0, 1.0, 0.0);
    points[38] = vec3(-1.0, 1.0, 0.0);
    points[39] = vec3(-1.0, 2.0, 0.0);
    points[40] = vec3(0.0, 2.0, 0.0);
    points[41] = vec3(0.0, 1.0, 0.0);

    points[42] = vec3(-3.0, 1.0, 0.0);
    points[43] = vec3(-2.0, 0.0, 0.0);
    points[44] = vec3(-3.0, 0.0, 0.0);
    points[45] = vec3(-3.0, 1.0, 0.0);
    points[46] = vec3(-2.0, 1.0, 0.0);
    points[47] = vec3(-2.0, 0.0, 0.0);

    //Z complete 
    points[48] = vec3(-1.0, 1.0, 0.0);
    points[49] = vec3(0.0, 0.0, 0.0);
    points[50] = vec3(-1.0, 0.0, 0.0);
    points[51] = vec3(-1.0, 1.0, 0.0);
    points[52] = vec3(0.0, 1.0, 0.0);
    points[53] = vec3(0.0, 0.0, 0.0);

    points[54] = vec3(-2.0, 1.0, 0.0);
    points[55] = vec3(-1.0, 0.0, 0.0);
    points[56] = vec3(-2.0, 0.0, 0.0);
    points[57] = vec3(-2.0, 1.0, 0.0);
    points[58] = vec3(-1.0, 1.0, 0.0);
    points[59] = vec3(-1.0, 0.0, 0.0);

    points[60] = vec3(-3.0, 2.0, 0.0);
    points[61] = vec3(-2.0, 1.0, 0.0);
    points[62] = vec3(-3.0, 1.0, 0.0);
    points[63] = vec3(-3.0, 2.0, 0.0);
    points[64] = vec3(-2.0, 2.0, 0.0);
    points[65] = vec3(-2.0, 1.0, 0.0);

    points[66] = vec3(-2.0, 2.0, 0.0);
    points[67] = vec3(-1.0, 1.0, 0.0);
    points[68] = vec3(-2.0, 1.0, 0.0);
    points[69] = vec3(-2.0, 2.0, 0.0);
    points[70] = vec3(-1.0, 2.0, 0.0);
    points[71] = vec3(-1.0, 1.0, 0.0);

    //S complete
    points[72] = vec3(-1.0, 1.0, 0.0);
    points[73] = vec3(0.0, 0.0, 0.0);
    points[74] = vec3(-1.0, 0.0, 0.0);
    points[75] = vec3(-1.0, 1.0, 0.0);
    points[76] = vec3(0.0, 1.0, 0.0);
    points[77] = vec3(0.0, 0.0, 0.0);

    points[78] = vec3(-2.0, 1.0, 0.0);
    points[79] = vec3(-1.0, 0.0, 0.0);
    points[80] = vec3(-2.0, 0.0, 0.0);
    points[81] = vec3(-2.0, 1.0, 0.0);
    points[82] = vec3(-1.0, 1.0, 0.0);
    points[83] = vec3(-1.0, 0.0, 0.0);

    points[84] = vec3(-1.0, 2.0, 0.0);
    points[85] = vec3(0.0, 1.0, 0.0);
    points[86] = vec3(-1.0, 1.0, 0.0);
    points[87] = vec3(-1.0, 2.0, 0.0);
    points[88] = vec3(0.0, 2.0, 0.0);
    points[89] = vec3(0.0, 1.0, 0.0);

    points[90] = vec3(0.0, 2.0, 0.0);
    points[91] = vec3(1.0, 1.0, 0.0);
    points[92] = vec3(0.0, 1.0, 0.0);
    points[93] = vec3(0.0, 2.0, 0.0);
    points[94] = vec3(1.0, 2.0, 0.0);
    points[95] = vec3(1.0, 1.0, 0.0);

    //0 complete
    points[96] = vec3(-1.0, 1.0, 0.0);
    points[97] = vec3(0.0, 0.0, 0.0);
    points[98] = vec3(-1.0, 0.0, 0.0);
    points[99] = vec3(-1.0, 1.0, 0.0);
    points[100] = vec3(0.0, 1.0, 0.0);
    points[101] = vec3(0.0, 0.0, 0.0);

    points[102] = vec3(-2.0, 1.0, 0.0);
    points[103] = vec3(-1.0, 0.0, 0.0);
    points[104] = vec3(-2.0, 0.0, 0.0);
    points[105] = vec3(-2.0, 1.0, 0.0);
    points[106] = vec3(-1.0, 1.0, 0.0);
    points[107] = vec3(-1.0, 0.0, 0.0);

    points[108] = vec3(-1.0, 2.0, 0.0);
    points[109] = vec3(0.0, 1.0, 0.0);
    points[110] = vec3(-1.0, 1.0, 0.0);
    points[111] = vec3(-1.0, 2.0, 0.0);
    points[112] = vec3(0.0, 2.0, 0.0);
    points[113] = vec3(0.0, 1.0, 0.0);

    points[114] = vec3(-2.0, 2.0, 0.0);
    points[115] = vec3(-1.0, 1.0, 0.0);
    points[116] = vec3(-2.0, 1.0, 0.0);
    points[117] = vec3(-2.0, 2.0, 0.0);
    points[118] = vec3(-1.0, 2.0, 0.0);
    points[119] = vec3(-1.0, 1.0, 0.0);

    //I complete
    points[120] = vec3(-1.0, 1.0, 0.0);
    points[121] = vec3(0.0, 0.0, 0.0);
    points[122] = vec3(-1.0, 0.0, 0.0);
    points[123] = vec3(-1.0, 1.0, 0.0);
    points[124] = vec3(0.0, 1.0, 0.0);
    points[125] = vec3(0.0, 0.0, 0.0);

    points[126] = vec3(-1.0, 2.0, 0.0);
    points[127] = vec3(0.0, 1.0, 0.0);
    points[128] = vec3(-1.0, 1.0, 0.0);
    points[129] = vec3(-1.0, 2.0, 0.0);
    points[130] = vec3(0.0, 2.0, 0.0);
    points[131] = vec3(0.0, 1.0, 0.0);

    points[132] = vec3(-1.0, 3.0, 0.0);
    points[133] = vec3(0.0, 2.0, 0.0);
    points[134] = vec3(-1.0, 2.0, 0.0);
    points[135] = vec3(-1.0, 3.0, 0.0);
    points[136] = vec3(0.0, 3.0, 0.0);
    points[137] = vec3(0.0, 2.0, 0.0);

    points[138] = vec3(-1.0, 4.0, 0.0);
    points[139] = vec3(0.0, 3.0, 0.0);
    points[140] = vec3(-1.0, 3.0, 0.0);
    points[141] = vec3(-1.0, 4.0, 0.0);
    points[142] = vec3(0.0, 4.0, 0.0);
    points[143] = vec3(0.0, 3.0, 0.0);

    //T complete
    points[144] = vec3(-1.0, 1.0, 0.0);
    points[145] = vec3(0.0, 0.0, 0.0);
    points[146] = vec3(-1.0, 0.0, 0.0);
    points[147] = vec3(-1.0, 1.0, 0.0);
    points[148] = vec3(0.0, 1.0, 0.0);
    points[149] = vec3(0.0, 0.0, 0.0);

    points[150] = vec3(-2.0, 0.0, 0.0);
    points[151] = vec3(-1.0, -1.0, 0.0);
    points[152] = vec3(-2.0, -1.0, 0.0);
    points[153] = vec3(-2.0, 0.0, 0.0);
    points[154] = vec3(-1.0, 0.0, 0.0);
    points[155] = vec3(-1.0, -1.0, 0.0);

    points[156] = vec3(-1.0, 0.0, 0.0);
    points[157] = vec3(0.0, -1.0, 0.0);
    points[158] = vec3(-1.0, -1.0, 0.0);
    points[159] = vec3(-1.0, 0.0, 0.0);
    points[160] = vec3(0.0, 0.0, 0.0);
    points[161] = vec3(0.0, -1.0, 0.0);

    points[162] = vec3(0.0, 0.0, 0.0);
    points[163] = vec3(1.0, -1.0, 0.0);
    points[164] = vec3(0.0, -1.0, 0.0);
    points[165] = vec3(0.0, 0.0, 0.0);
    points[166] = vec3(1.0, 0.0, 0.0);
    points[167] = vec3(1.0, -1.0, 0.0);
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

    // Load shaders and use the resulting shader program
    shader1 = InitShader( "simpleShader.vert", "simpleShader.frag" );
    shader2 = InitShader("redShader.vert", "redShader.frag");
    currentShader = shader1;
    // make these shaders the current shaders
    glUseProgram( currentShader );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(currentShader, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint colorLoc = glGetAttribLocation(currentShader, "vColor");
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

    uniformColor1 = vec4(253, 245, 230, 255) / 255;
    uniformColor2 = vec4(255, 228, 181, 255) / 255;

    glClearColor( 0.5, 0.5, 0.5, 1.0 ); // gray background
}

void
reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);
}

//----------------------------------------------------------------------------

void
computeMouseWorldCoordinates(int x, int y)
{
    worldMousePositionX = (GLfloat)(x - windowWidth / 2) / (windowWidth / 2) * magnify + xCenter;
    worldMousePositionY = (GLfloat)(windowHeight / 2 - y) / (windowHeight / 2) * magnify + yCenter;
}



//----------------------------------------------------------------------------
/* This function handles the display and it is automatically called by GLUT
   once it is declared as the display function. The application should not
   call it directly.
*/

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );				// clear the window
    mat4 projection = Ortho(xCenter - magnify, xCenter + magnify, yCenter - magnify, yCenter + magnify, -5.0, 5.0);
    GLint uniformColorPosition = glGetUniformLocation(currentShader, "uniformColor");
    glUseProgram(currentShader);

    for (int i = 0; i < nextShapePosition; i++)
    {
        mat4 modelView = Translate(allShapes[i].position.x, allShapes[i].position.y, allShapes[i].position.z); // Translate(0.5f, 0.5f, 0);
        modelView = modelView * RotateZ(allShapes[i].rotation);
        modelView = modelView * Scale(allShapes[i].scale.x, allShapes[i].scale.y, allShapes[i].scale.z); 
        glUniform4fv(uniformColorPosition, 1, allShapes[i].color);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUniformMatrix4fv(glGetUniformLocation(currentShader, "Projection"), 1, GL_TRUE, projection);
        glUniformMatrix4fv(glGetUniformLocation(currentShader, "ModelView"), 1, GL_TRUE, modelView);
        glDrawArrays(GL_TRIANGLES, allShapes[i].start, allShapes[i].nVertices);    // draw the points
    }
    glFlush();									// flush the buffer
}

//----------------------------------------------------------------------------
/* This function handles the keyboard and it is called by GLUT once it is 
   declared as the keyboard function. The application should not call it
   directly. in order 
   
   to change the shapes "shift" must be held when pressing letter keys
*/

void
keyboard( unsigned char key, int x, int y )
{
    switch (key) {
    case 033:					// escape key
        exit(EXIT_SUCCESS);	// terminates the program
        break;
    case 'r':
    case 'R':
        currentShader = shader2;
        glutPostRedisplay();
        break;
    case 'v':
    case 'V':
        currentShader = shader1;
        glutPostRedisplay();
        break;
    case 'L':
        switch (state)
        {
        case MYINPUT:
            selectedShape = L;
            break;
        case DRAGGING:
            break;
        }
        break;
    case 'J':
    {
        switch (state)
        {
        case MYINPUT:
            selectedShape = J;
            break;
        case DRAGGING:
            break;
        }
        break;
    }
    case 'Z':
    {
        switch (state)
        {
        case MYINPUT:
            selectedShape = Z;
            break;
        case DRAGGING:
            break;
        }
        break;
    case 'S':
        switch (state)
        {
        case MYINPUT:
            selectedShape = S;
            break;
        case DRAGGING:
            break;
        }
        break;
    case 'O':
    {
        switch (state)
        {
        case MYINPUT:
            selectedShape = O;
            break;
        case DRAGGING:
            break;
        }
        break;
    }
    case 'I':
    {
        switch (state)
        {
        case MYINPUT:
            selectedShape = I;
            break;
        case DRAGGING:
            break;
        }
        break;
    }
    case 'T':
    {
        switch (state)
        {
        case MYINPUT:
            selectedShape = T;
            break;
        case DRAGGING:
            break;
        }
        break;
    }
    break;

    }


    }
}

void specialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        currentRotation += 90.0f;
        allShapes[currentShape].rotation = currentRotation;
        break;
    case GLUT_KEY_LEFT:
        currentRotation -= 90.0f;
        allShapes[currentShape].rotation = currentRotation;
        break;
    case GLUT_KEY_UP:
        allShapes[currentShape].scale.x += 0.1f * allShapes[currentShape].scale.x;
        allShapes[currentShape].scale.y += 0.1f * allShapes[currentShape].scale.x;
        allShapes[currentShape].scale.z += 0.1f * allShapes[currentShape].scale.x;
        break;
    case GLUT_KEY_DOWN:
        allShapes[currentShape].scale.x -= 0.1f * allShapes[currentShape].scale.x;
        allShapes[currentShape].scale.y -= 0.1f * allShapes[currentShape].scale.x;
        allShapes[currentShape].scale.z -= 0.1f * allShapes[currentShape].scale.x;
        break;
    }

    glutPostRedisplay();
}
void
mainMenu(GLint id)
{
    switch (id)
    {
    case 3: // exit the application
        exit(EXIT_SUCCESS);	// terminates the program
        break;
    default:
        break;
    }
}

void
shaderSelectSubMenu(GLint id)
{
    switch (id)
    {
    case 1: // Select Vertex Color shader
        currentShader = shader1;
        break;
    case 2: // Select Uniform Color shader
        currentShader = shader2;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void
colorSelectSubMenu(GLint id)
{
    switch (id)
    {
    case 1: // old lace/moccasin
        uniformColor1 = vec4(253, 245, 230, 255) / 255;
        uniformColor2 = vec4(255, 228, 181, 255) / 255;
        break;
    case 2: // lavender/navy
        uniformColor1 = vec4(230, 230, 250, 255) / 255;
        uniformColor2 = vec4(0, 0, 128, 255) / 255;
        break;
    case 3: // sea green/golden rod
        uniformColor1 = vec4(46, 139, 87, 255) / 255;
        uniformColor2 = vec4(218, 165, 32, 255) / 255;
        break;
    case 4: // state blue/gold2
        uniformColor1 = vec4(131, 111, 255, 255) / 255;
        uniformColor2 = vec4(238, 201, 0, 255) / 255;
        break;
    case 5: // unknown/unknown
        uniformColor1 = vec4(101, 101, 255, 255) / 255;
        uniformColor2 = vec4(117, 201, 44, 255) / 255;
        break;
    case 6: // state blue/gold2
        uniformColor1 = vec4(61, 101, 255, 255) / 255;
        uniformColor2 = vec4(88, 101, 7, 255) / 255;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void
menuInit()
{
    GLint colorsMenuID = glutCreateMenu(colorSelectSubMenu);
    glutAddMenuEntry("old lace/moccasin", 1);
    glutAddMenuEntry("lavender/navy", 2);
    glutAddMenuEntry("sea green/golden rod", 3);
    glutAddMenuEntry("state blue/gold2", 4);
    glutAddMenuEntry("test colors", 5);
    glutAddMenuEntry("test colors 2", 6);

    GLint shaderMenuID = glutCreateMenu(shaderSelectSubMenu);
    glutAddMenuEntry("Vertex Color Shader", 1);
    glutAddMenuEntry("Uniform Color Shader", 2);


    GLint mainMenuID = glutCreateMenu(mainMenu);
    glutAddSubMenu("Shader Selection", shaderMenuID);
    glutAddSubMenu("Color Pairs", colorsMenuID);
    glutAddMenuEntry("Exit", 3);

    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void
mouse(GLint button, GLint state, GLint x, GLint y)
{
    //printf("button: %i, state: %i, x: %i, y: %i\n", button, state, x, y);
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        switch (state)
        {
        case GLUT_DOWN:
            currentRotation = 0.0f;
            computeMouseWorldCoordinates(x, y);
            allShapes[nextShapePosition].color = uniformColor1;
            allShapes[nextShapePosition].start = startEnds[selectedShape].start;
            allShapes[nextShapePosition].nVertices = startEnds[selectedShape].nVertices;
            allShapes[nextShapePosition].position = vec3(worldMousePositionX, worldMousePositionY, 0);
            allShapes[nextShapePosition].scale = vec3(1, 1, 1);
            allShapes[nextShapePosition].rotation = currentRotation;
            currentShape = nextShapePosition;
            nextShapePosition++;
            state = DRAGGING;
            printf("Left Mouse Button - Pressed @ x: %i, y: %i\n", x, y);
            break;
        case GLUT_UP:
            currentShape = -1;
            currentRotation = 0.0f;
            state = MYINPUT;
            printf("Left Mouse Button - Released @ x: %i, y: %i\n", x, y);
            break;
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        switch (state)
        {
        case GLUT_DOWN:
            printf("Middle Mouse Button - Pressed @ x: %i, y: %i\n", x, y);
            break;
        case GLUT_UP:
            printf("Middle Mouse Button - Released @ x: %i, y: %i\n", x, y);
            break;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        switch (state)
        {
        case GLUT_DOWN:
            printf("Right Mouse Button - Pressed @ x: %i, y: %i\n", x, y);
            break;
        case GLUT_UP:
            printf("Right Mouse Button - Released @ x: %i, y: %i\n", x, y);
            break;
        }
        break;
    }
}

void
mouseMotion(GLint x, GLint y)
{
    if (currentShape > -1)
    {
        computeMouseWorldCoordinates(x, y);
        allShapes[currentShape].position = vec3(worldMousePositionX, worldMousePositionY, 0);
        allShapes[currentShape].rotation = currentRotation;
        glutPostRedisplay();
    }
    //printf("x: %i, y: %i\n", x, y);
}

//----------------------------------------------------------------------------
/* This is the main function that calls all the functions to initialize
   and setup the OpenGL environment through GLUT and GLEW.
*/

int
main( int argc, char **argv )
{
	// Initialize GLUT
    glutInit( &argc, argv );
	// Initialize the display mode to a buffer with Red, Green, Blue and Alpha channels
    glutInitDisplayMode( GLUT_RGBA );
	// Set the window size
    glutInitWindowSize( 512, 512 );
	// Here you set the OpenGL version
    glutInitContextVersion( 3, 2 );
	//Use only one of the next two lines
    //glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    // Uncomment if you are using GLEW
	glewInit(); 

    // initialize the array and send it to the graphics card
	init();

    // initialize the menu system
    menuInit();

    // provide the function that handles the display
	glutDisplayFunc( display );
	// provide the functions that handles the keyboard
    glutKeyboardFunc( keyboard );
    glutSpecialFunc(specialKeyboard);
    // provide the function that handles the mouse
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    // provide the function that handles the mouse motion
    glutMotionFunc(mouseMotion);

    // Wait for input from the user (the only meaningful input is the key escape)
	glutMainLoop();
    return 0;
}