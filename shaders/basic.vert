//-----------------------------------------------------------------------------
// basic.vert by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// Vertex shader
//-----------------------------------------------------------------------------
#version 330 core

layout (location = 0) in vec3 pos;  // in local coords
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

uniform float happy_w;
uniform float angry_w;
uniform float angry_l_w;
uniform float angry_r_w;
uniform float happy_l_w;
uniform float happy_r_w;
uniform float suck_l_w;
uniform float suck_r_w;
uniform float suck_vp_w;
uniform float jaw_open_w;
uniform float neutral;
uniform int flag;

uniform float pos1;
uniform float pos2;
uniform float pos3;
uniform float pos4;
uniform float pos5;
uniform float pos6;
uniform float pos7;
uniform float pos8;
uniform float pos9;
uniform float pos10;
uniform float pos11;
uniform float pos12;
uniform float pos13;
uniform float pos14;
uniform float pos15;
uniform float pos16;



vec3 neutral_vp;
vec3 happy_vp;
vec3 angry_vp;
vec3 angry_vp_l;
vec3 angry_vp_r;
vec3 happy_vp_l;
vec3 happy_vp_r;
vec3 suck_vp_l;
vec3 suck_vp_r;
vec3 suck_vp;
vec3 jaw_open;
vec3 pos1_vp;
vec3 pos2_vp;
vec3 pos3_vp;
vec3 pos4_vp;
vec3 pos5_vp;
vec3 pos6_vp;
vec3 pos7_vp;
vec3 pos8_vp;
vec3 pos9_vp;
vec3 pos10_vp;
vec3 pos11_vp;
vec3 pos12_vp;
vec3 pos13_vp;
vec3 pos14_vp;
vec3 pos15_vp;
vec3 pos16_vp;




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
        case 3: { 
            angry_vp_l = pos;
            break;
        }
        case 4: { // brick cube
            angry_vp_r = pos;
            break;
        }
        case 5: { // wooden cube
           happy_vp_l = pos;
           break;
        }
        case 6: { 
            happy_vp_r = pos;
            break;
        }
        case 7: { // brick cube
            suck_vp_l = pos;
            break;
        }
        case 8: { // wooden cube
           suck_vp_r = pos;
           break;
        }
        case 9: { 
            suck_vp = pos;
            break;
        }
        case 10: { // brick cube
            jaw_open = pos;
            break;
        }
        
        
        case 11: { // brick cube
            pos1_vp = pos;
            break;
        }
        case 12: { // wooden cube
           pos2_vp = pos;
           break;
        }
        case 13: { 
            pos3_vp = pos;
            break;
        }
        case 14: { // brick cube
            pos4_vp = pos;
            break;
        }
        case 15: { // wooden cube
           pos5_vp = pos;
           break;
        }
        case 16: { 
            pos6_vp = pos;
            break;
        }
         case 17: { // brick cube
            pos7_vp = pos;
            break;
        }
        case 18: { // wooden cube
           pos8_vp = pos;
           break;
        }
        case 19: { 
            pos9_vp = pos;
            break;
        }
        case 20: { // brick cube
            pos10_vp = pos;
            break;
        }
        
        case 21: { // brick cube
            pos11_vp = pos;
            break;
        }
        case 22: { // wooden cube
           pos12_vp = pos;
           break;
        }
        case 23: { 
            pos13_vp = pos;
            break;
        }
        case 24: { // brick cube
            pos14_vp = pos;
            break;
        }
        case 25: { // wooden cube
           pos15_vp = pos;
           break;
        }
        case 26: { 
            pos16_vp = pos;
            break;
        }


	}

	// if other weights add up to less than 1, use neutral target
    float neutral_w = neutral;
  	neutral_w = 1.0 - happy_w - angry_w - angry_l_w - angry_r_w - happy_l_w - happy_r_w - suck_l_w - suck_r_w - suck_vp_w - jaw_open_w - pos1 - pos2 - pos3 - pos4 - pos5 - pos6 - pos7 - pos8 - pos9 - pos10 - pos11 - pos12 - pos13 - pos14 - pos15 - pos16;
    
  	// clamp (neutral_w, 0.0, 1.0);
    if (neutral_w < 0.0f) { neutral_w = 0.0f; }
    if(neutral_w > 1.0f) { neutral_w = 1.0f; }
    
  	// get a sum of weights and work out factors for each target
  	float sum_w = neutral_w + happy_w + angry_w + angry_l_w + angry_r_w + happy_l_w + happy_r_w + suck_l_w + suck_r_w + suck_vp_w + jaw_open_w + pos1 + pos2 + pos3 + pos4 + pos5 + pos6 + pos7 + pos8 + pos9 + pos10 + pos11 + pos12 + pos13 + pos14 + pos15 + pos16;
  	float happy_f = happy_w / sum_w;
  	float angry_f = angry_w / sum_w;
    float angry_f_l = angry_l_w / sum_w;
    float angry_f_r = angry_r_w / sum_w;
    
    float happy_f_l = happy_l_w / sum_w;
    float happy_f_r = happy_r_w / sum_w;
  	float neutral_f = neutral_w / sum_w;

    float suck_f_l = suck_l_w / sum_w;
    float suck_f_r = suck_r_w / sum_w;
  	float suck_f = suck_vp_w / sum_w;
    
    float jaw_f =  jaw_open_w/sum_w;
    
    float pos1_f = pos1/sum_w;
    float pos2_f = pos2/sum_w;
    float pos3_f = pos3/sum_w;
    float pos4_f = pos4/sum_w;
    float pos5_f = pos5/sum_w;
    float pos6_f = pos6/sum_w;
    float pos7_f = pos7/sum_w;
    float pos8_f = pos8/sum_w;
    float pos9_f = pos9/sum_w;
    float pos10_f = pos10/sum_w;
    float pos11_f = pos11/sum_w;
    float pos12_f = pos12/sum_w;
    float pos13_f = pos13/sum_w;
    float pos14_f = pos14/sum_w;
    float pos15_f = pos15/sum_w;
    float pos16_f = pos16/sum_w;
    
    vec3 post = happy_f * happy_vp + angry_f * angry_vp + neutral_f * neutral_vp + angry_f_l * angry_vp_l + angry_f_r * angry_vp_r + happy_vp_l * happy_f_l + happy_vp_r * happy_f_r + suck_vp_r * suck_f_r	+ suck_vp_l * suck_f_l + suck_vp * suck_f + jaw_open_w *jaw_open + pos1_vp * pos1_f + pos2_vp * pos2_f + pos3_vp * pos3_f + pos4_vp * pos4_f + pos5_vp * pos5_f + pos6_vp * pos6_f + pos7_vp * pos7_f + pos8_vp * pos8_f + pos9_vp * pos9_f + pos10_vp * pos10_f + pos11_vp * pos11_f + pos12_vp * pos12_f + pos13_vp * pos13_f + pos14_vp * pos14_f + pos15_vp * pos15_f + pos16_vp * pos16_f;
    
    Normal = normal;
    FragPos = vec3(model *vec4(pos,1.0f));
	TexCoord = texCoord;
	gl_Position = projection * view * model * vec4(post, 1.0f);
	
}