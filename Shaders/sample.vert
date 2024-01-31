#version 330 core

//gets data at attrib 0 and stores in vec3
layout(location=0) in vec3 aPos;

//declare a var to hold the data to be passed or not because fuck you
//uniform float x;
//uniform float y;

//create transform variable
uniform mat4 transform;

uniform mat4 projection;

void main(){
//create vec3 for the new position
//vec3 newPos = vec3(aPos.x + x, aPos.y + y, aPos.z);

//gl_Pos is predefined
//denotes final pos of the vertex
gl_Position = projection * transform * vec4(aPos, 1.0); 
//turns the above vec3 into a vec4


}