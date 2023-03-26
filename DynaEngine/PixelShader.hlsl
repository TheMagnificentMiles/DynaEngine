Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal: NORMAL0;
	float3 direction_to_camera: TEXCOORD1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float ka = 0.1;
	float3 ia = float3(1.0, 1.0, 1.0);
	float3 ambient_light = ka * ia;

	float kd = 0.7;
	float3 id = float3(1.0, 1.0, 1.0);
	float amount_diffuse_light = max(0.0, dot(m_light_direction.xyz, input.normal));
	float3 diffuse_light = kd * amount_diffuse_light * id;

	float3 specular_light = 0.0;

	if (amount_diffuse_light > 0.0) {
		float ks = 1.0;
		float3 is = float3(1.0, 1.0, 1.0);
		float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
		float shininess = 10.0;
		float3 halfway_direction = normalize(m_light_direction + input.direction_to_camera);
		float amount_specular_light = pow(max(0.0, dot(reflected_light, halfway_direction)), shininess);
		specular_light = ks * amount_specular_light * is;
	}

	float3 final_light = ambient_light + diffuse_light + specular_light;

	float3 final_mapped = final_light / (1.0f + final_light);

	return float4(final_mapped,1.0);
}

