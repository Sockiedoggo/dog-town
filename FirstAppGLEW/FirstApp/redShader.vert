#version 150

in vec4 vPosition;
in vec4 vColor;
uniform vec4 uniformColor;

out vec4 fragmentColor;

uniform mat4 ModelView;
uniform mat4 Projection;


void
main()
{
    gl_Position = Projection * ModelView * vPosition;
    fragmentColor = uniformColor;
}
