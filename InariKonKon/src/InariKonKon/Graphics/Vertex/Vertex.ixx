export module Vertex;

import Vector2;
import Vector3;
import Color;

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