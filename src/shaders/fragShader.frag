#version 410 core

out vec4 out_frag_color;

in vec4 normal;
in vec4 frag_pos;

uniform vec4 u_light_pos;
uniform vec4 u_view_pos;
uniform vec4 u_obj_color;

void main() {
	// vec4 object_color = vec4(0.337254f, 0.396078f, 0.450980f, 1.0f);
	vec4 light_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// ambient
	float ambient_light_stringth = 0.1f;
	vec4 ambient = ambient_light_stringth * light_color;

	vec4 norm = normalize(normal);
	vec4 light_dir = normalize(u_light_pos - frag_pos);
	float diff = abs(dot(norm, light_dir));
	vec4 diffuse = diff * light_color;

	// specular light
	float spec_strength = 1;
	vec4 view_dir = normalize(u_view_pos - frag_pos);
	vec4 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 64);
	vec4 specular = vec4(0, 0, 0, 0);//spec_strength * spec * light_color;

	vec4 result = (ambient + diffuse + specular) * u_obj_color;
	out_frag_color = result;
}
