//-----------------------------------------------------------------------------
// lighting_phong_materials.vert by Steve Jones 
// Copyright (c) 2015-2016 Game Institute. All Rights Reserved.
//
// Vertex shader for Blinn-Phong lighting with materials
//-----------------------------------------------------------------------------
#version 330 core

layout (location = 0) in vec3 pos;			
layout (location = 1) in vec3 normal;	
layout (location = 2) in vec2 texCoord;


uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

uniform float happy_w;
uniform float angry_w;
uniform int flag;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

vec3 neutral_vp;
vec3 happy_vp;
vec3 angry_vp;


void main()
{

	    switch (flag) {
        case 0: { 
            neutral_vp = pos;
            break;
        }
        case 1: { // brick cube
            angry_vp = pos;
            break;
        }
        case 2: { // wooden cube
           happy_vp = pos;
           break;
        }

	}
	
    FragPos = vec3(model * vec4(pos, 1.0f));			// vertex position in world space
	Normal = mat3(transpose(inverse(model))) * normal;	// normal direction in world space

	
	 // if other weights add up to less than 1, use neutral target
  	float neutral_w = 1.0 - happy_w - angry_w;
  	clamp (neutral_w, 0.0, 1.0);

  	// get a sum of weights and work out factors for each target
  	float sum_w = happy_w + angry_w + neutral_w;
  	float happy_f = happy_w / sum_w;
  	float angry_f = angry_w / sum_w;
  	float neutral_f = neutral_w / sum_w;

  	// interpolate targets to give us current pose
	vec3 post = (happy_f * happy_vp) + (angry_f * angry_vp) + (neutral_f * neutral_vp);
	
	TexCoord = texCoord;

	gl_Position = projection * view *  model * vec4(post, 1.0f);
}