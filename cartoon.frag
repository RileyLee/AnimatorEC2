varying vec3 N;
varying vec3 v;

void main() {
  vec3 Normal = normalize(N);
  vec3 Viewer = -normalize(v);


  vec4 color = vec4(0,0,0,1);
  bool isWhite = false;
  bool fullIllum = false;

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
	float specularShade = 
	  B * pow(max(dot(Half, Normal), 0.0), gl_FrontMaterial.shininess);

	if(specularShade > 0.9) {
	  isWhite = isWhite || bool(length(gl_LightSource[i].specular.rgb) > 0.0);
	} else if(diffuseShade < 0.5) {
	  color += B * vec4(0.2, 0.2, 0.2, 0) * gl_LightSource[i].diffuse;
	} else if(diffuseShade > 0.9) {
	  fullIllum = true;
	} else {
	  color += B * vec4(0.5, 0.5, 0.5, 0) * gl_LightSource[i].diffuse;
	}
  }

  if(isWhite) {
	color = vec4(1,1,1,1);
  } else if(fullIllum) {
	color = gl_FrontMaterial.diffuse;
  } else {
	color = gl_FrontMaterial.diffuse * color;
  }
  
  // Assign final color
  gl_FragColor = color;
}
