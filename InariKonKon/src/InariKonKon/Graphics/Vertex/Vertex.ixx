export module Vertex;

export import Vector2;
export import Vector3;
export import Color;

export namespace ikk
{
	struct VertexBase {};

	struct Vertex : public VertexBase
	{
		vec3f position;
		Color color;
		vec2f texCoord;
	};
}