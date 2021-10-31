#version 150

out vec4  fColor;

in vec4 fragmentColor;

void
main()
{
    fColor = fragmentColor;
}
