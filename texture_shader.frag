// Fragment shader for per-pixel Phong interpolation and shading.

// The "varying" keyword means that the parameter's value is interpolated
// between the nearby vertices.
varying vec3 N;
varying vec3 v;

uniform float brightness;

uniform sampler2D tex;

void main() {
  vec4 color = gl_FrontMaterial.emission + gl_LightModel.ambient * gl_FrontMaterial.ambient;

  // The normal vectors is generally not normalized after being
  // interpolated across a triangle.  Here we normalize it.
  vec3 Normal = normalize(N);
  
  // Since the vertex is in eye space, the direction to the
  // viewer is simply the normalized vector from v to the
  // origin.
  vec3 Viewer = -normalize(v);

  for(int i = 0; i < 2; i++) {

	// Get the lighting direction and normalize it.
	vec3 Light  = normalize(gl_LightSource[i].position.xyz);
	if(i == 1) {
	  Light =  normalize(gl_LightSource[i].position.xyz - v);
	}

	// Compute halfway vector
	vec3 Half = normalize(Viewer+Light);

	// Compute factor to prevent light leakage from below the
	// surface
	float B = 1.0;
	if(dot(Normal, Light)<0.0) B = 0.0;

	// Compute geometric terms of diffuse and specular
	float diffuseShade = max(dot(Normal, Light), 0.0);
	
	float att = 1.0;
	if(i == 1) {
	  float dist = length(gl_LightSource[i].position.xyz - v);
	  att = 1.0 / (gl_LightSource[i].constantAttenuation +
				   gl_LightSource[i].linearAttenuation * dist +
				   gl_LightSource[i].quadraticAttenuation * dist * dist);
	}

	// Compute product of geometric terms with material and
	// lighting values
	vec4 diffuse = diffuseShade * gl_FrontLightProduct[i].diffuse;
	color += att * (gl_FrontLightProduct[i].ambient + diffuse);
  }
  color = color * texture2D(tex,gl_TexCoord[0].st);

  gl_FragColor = color;
}
