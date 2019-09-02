#version 410 core

out vec4 out_frag_color;

in vec4 normal;
in vec4 frag_pos;
in vec4 local_pos;
// in vec2 tex_coord;

uniform vec4 u_light_pos;
uniform vec4 u_view_pos;
uniform vec4 u_obj_color;
uniform bool u_show_texture;
uniform sampler2D my_texture;

vec4 norm = normalize(normal);


vec4 get_ambient(vec4 light_color) {
	float ambient_light_stringth = 0.1f;
	return ambient_light_stringth * light_color;
}

vec4 get_diffuse(vec4 light_color) {
	vec4 light_dir = normalize(u_light_pos - frag_pos);
	float diff = abs(dot(norm, light_dir));
	return diff * light_color;
}

vec4 get_specular(vec4 light_color) {
	float spec_strength = 1;
	vec4 light_dir = normalize(u_light_pos - frag_pos);
	vec4 view_dir = normalize(u_view_pos - frag_pos);
	vec4 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 64);
	return spec_strength * spec * light_color;
}

vec4 tri_planar_texture_map() {
	// in wNorm is the world-space normal of the fragment
	vec3 blending = abs( normal.xyz );
	blending = normalize(max(blending, 0.00001)); // Force weights to sum to 1.0
	float b = (blending.x + blending.y + blending.z);
	blending /= vec3(b, b, b);

	vec4 xaxis = texture( my_texture, local_pos.yz);
	vec4 yaxis = texture( my_texture, local_pos.xz);
	vec4 zaxis = texture( my_texture, local_pos.xy);
	// blend the results of the 3 planar projections.
	return xaxis * blending.x + xaxis * blending.y + zaxis * blending.z;
}

void main() {
	// vec4 object_color = vec4(0.337254f, 0.396078f, 0.450980f, 1.0f);
	vec4 light_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// light
	vec4 ambient = get_ambient(light_color);
	vec4 diffuse = get_diffuse(light_color);
	vec4 specular = get_specular(light_color);

	vec4 result = 
		(ambient + diffuse + specular) * 
		(u_show_texture ? tri_planar_texture_map() : u_obj_color);
	out_frag_color = result;
}
