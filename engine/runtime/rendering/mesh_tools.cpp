#include "mesh_tools.h"
#include "core/math/math_includes.h"

void convert_to_y_up(std::vector<math::vec3>& out_vertices)
{
	for(std::size_t i = 0; i < out_vertices.size(); ++i)
	{
		float y = out_vertices[i].y;
		out_vertices[i].y = out_vertices[i].z;
		out_vertices[i].z = -y;
	}
}

void triangle_mesh_tools::create_plane(std::vector<math::vec3>& out_vertices,
									   std::vector<std::uint32_t>& out_indices, float size_x, float size_y,
									   bool y_up)
{
	const math::vec3 v0 = math::vec3(-size_x, -size_y, 0.0f);
	const math::vec3 v1 = math::vec3(size_x, -size_y, 0.0f);
	const math::vec3 v2 = math::vec3(size_x, size_y, 0.0f);
	const math::vec3 v3 = math::vec3(-size_x, size_y, 0.0f);

	triangle_mesh_tools::add_quad(out_vertices, out_indices, v0, v3, v1, v2);

	if(y_up)
		convert_to_y_up(out_vertices);
}

void triangle_mesh_tools::create_tetrahedron(std::vector<math::vec3>& out_vertices,
											 std::vector<std::uint32_t>& out_indices, bool share_vertices,
											 bool y_up)
{
	const float a = 1.41421f / 3.0f;
	const float b = 2.4494f / 3.0f;

	const math::vec3 v0 = math::vec3(0.0f, 0.0f, 1.0f);
	const math::vec3 v1 = math::vec3(2 * a, 0.0f, -1.0f / 3.0f);
	const math::vec3 v2 = math::vec3(-a, b, -1.0f / 3.0f);
	const math::vec3 v3 = math::vec3(-a, -b, -1.0f / 3.0f);

	if(share_vertices)
	{
		const int i0 = triangle_mesh_tools::add_vertex(out_vertices, v0);
		const int i1 = triangle_mesh_tools::add_vertex(out_vertices, v1);
		const int i2 = triangle_mesh_tools::add_vertex(out_vertices, v2);
		const int i3 = triangle_mesh_tools::add_vertex(out_vertices, v3);
		triangle_mesh_tools::add_triangle(out_indices, i0, i1, i2);
		triangle_mesh_tools::add_triangle(out_indices, i0, i2, i3);
		triangle_mesh_tools::add_triangle(out_indices, i0, i3, i1);
		triangle_mesh_tools::add_triangle(out_indices, i1, i3, i2);
	}
	else
	{
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v1, v2);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v2, v3);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v3, v1);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v1, v3, v2);
	}

	if(y_up)
		convert_to_y_up(out_vertices);
}

void triangle_mesh_tools::create_cube(std::vector<math::vec3>& out_vertices,
									  std::vector<std::uint32_t>& out_indices, bool share_vertices,
									  float edge_half_length, bool y_up)
{
	const math::vec3 v0 = math::vec3(-1.0f, -1.0f, -1.0f) * edge_half_length;
	const math::vec3 v1 = math::vec3(1.0f, -1.0f, -1.0f) * edge_half_length;
	const math::vec3 v2 = math::vec3(1.0f, 1.0f, -1.0f) * edge_half_length;
	const math::vec3 v3 = math::vec3(-1.0f, 1.0f, -1.0f) * edge_half_length;
	const math::vec3 v4 = math::vec3(-1.0f, -1.0f, 1.0f) * edge_half_length;
	const math::vec3 v5 = math::vec3(1.0f, -1.0f, 1.0f) * edge_half_length;
	const math::vec3 v6 = math::vec3(1.0f, 1.0f, 1.0f) * edge_half_length;
	const math::vec3 v7 = math::vec3(-1.0f, 1.0f, 1.0f) * edge_half_length;

	if(share_vertices)
	{
		const int i0 = triangle_mesh_tools::add_vertex(out_vertices, v0);
		const int i1 = triangle_mesh_tools::add_vertex(out_vertices, v1);
		const int i2 = triangle_mesh_tools::add_vertex(out_vertices, v2);
		const int i3 = triangle_mesh_tools::add_vertex(out_vertices, v3);
		const int i4 = triangle_mesh_tools::add_vertex(out_vertices, v4);
		const int i5 = triangle_mesh_tools::add_vertex(out_vertices, v5);
		const int i6 = triangle_mesh_tools::add_vertex(out_vertices, v6);
		const int i7 = triangle_mesh_tools::add_vertex(out_vertices, v7);

		triangle_mesh_tools::add_quad(out_indices, i0, i3, i1, i2);
		triangle_mesh_tools::add_quad(out_indices, i0, i1, i4, i5);
		triangle_mesh_tools::add_quad(out_indices, i0, i4, i3, i7);
		triangle_mesh_tools::add_quad(out_indices, i6, i5, i2, i1);
		triangle_mesh_tools::add_quad(out_indices, i6, i7, i5, i4);
		triangle_mesh_tools::add_quad(out_indices, i6, i2, i7, i3);
	}
	else
	{
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v0, v3, v1, v2);
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v0, v1, v4, v5);
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v0, v4, v3, v7);
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v6, v5, v2, v1);
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v6, v7, v5, v4);
		triangle_mesh_tools::add_quad(out_vertices, out_indices, v6, v2, v7, v3);
	}
	if(y_up)
		convert_to_y_up(out_vertices);
}

void triangle_mesh_tools::create_octahedron(std::vector<math::vec3>& out_vertices,
											std::vector<std::uint32_t>& out_indices, bool share_vertices,
											bool y_up)
{
	const math::vec3 v0 = math::vec3(1.0f, 0.0f, 0.0f);
	const math::vec3 v1 = math::vec3(-1.0f, 0.0f, 0.0f);
	const math::vec3 v2 = math::vec3(0.0f, 1.0f, 0.0f);
	const math::vec3 v3 = math::vec3(0.0f, -1.0f, 0.0f);
	const math::vec3 v4 = math::vec3(0.0f, 0.0f, 1.0f);
	const math::vec3 v5 = math::vec3(0.0f, 0.0f, -1.0f);

	if(share_vertices)
	{
		const int i0 = triangle_mesh_tools::add_vertex(out_vertices, v0);
		const int i1 = triangle_mesh_tools::add_vertex(out_vertices, v1);
		const int i2 = triangle_mesh_tools::add_vertex(out_vertices, v2);
		const int i3 = triangle_mesh_tools::add_vertex(out_vertices, v3);
		const int i4 = triangle_mesh_tools::add_vertex(out_vertices, v4);
		const int i5 = triangle_mesh_tools::add_vertex(out_vertices, v5);

		triangle_mesh_tools::add_triangle(out_indices, i4, i0, i2);
		triangle_mesh_tools::add_triangle(out_indices, i4, i2, i1);
		triangle_mesh_tools::add_triangle(out_indices, i4, i1, i3);
		triangle_mesh_tools::add_triangle(out_indices, i4, i3, i0);
		triangle_mesh_tools::add_triangle(out_indices, i5, i2, i0);
		triangle_mesh_tools::add_triangle(out_indices, i5, i1, i2);
		triangle_mesh_tools::add_triangle(out_indices, i5, i3, i1);
		triangle_mesh_tools::add_triangle(out_indices, i5, i0, i3);
	}
	else
	{
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v4, v0, v2);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v4, v2, v1);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v4, v1, v3);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v4, v3, v0);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v5, v2, v0);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v5, v1, v2);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v5, v3, v1);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v5, v0, v3);
	}
	if(y_up)
		convert_to_y_up(out_vertices);
}

void triangle_mesh_tools::create_icosahedron(std::vector<math::vec3>& out_vertices,
											 std::vector<std::uint32_t>& out_indices, bool share_vertices,
											 bool y_up)
{
	const float t = (1.0f + 2.236067977f) / 2.0f;
	const float s = math::sqrt(1.0f + t * t);

	const math::vec3 v0 = math::vec3(t, 1.0f, 0.0f) / s;
	const math::vec3 v1 = math::vec3(-t, 1.0f, 0.0f) / s;
	const math::vec3 v2 = math::vec3(t, -1.0f, 0.0f) / s;
	const math::vec3 v3 = math::vec3(-t, -1.0f, 0.0f) / s;
	const math::vec3 v5 = math::vec3(1.0f, 0.0f, -t) / s;
	const math::vec3 v6 = math::vec3(-1.0f, 0.0f, t) / s;
	const math::vec3 v7 = math::vec3(-1.0f, 0.0f, -t) / s;
	const math::vec3 v4 = math::vec3(1.0f, 0.0f, t) / s;
	const math::vec3 v8 = math::vec3(0.0f, t, 1.0f) / s;
	const math::vec3 v9 = math::vec3(0.0f, -t, 1.0f) / s;
	const math::vec3 v10 = math::vec3(0.0f, t, -1.0f) / s;
	const math::vec3 v11 = math::vec3(0.0f, -t, -1.0f) / s;

	if(share_vertices)
	{
		out_vertices.reserve(out_vertices.size() + 12);

		const int i0 = triangle_mesh_tools::add_vertex(out_vertices, v0);
		const int i1 = triangle_mesh_tools::add_vertex(out_vertices, v1);
		const int i2 = triangle_mesh_tools::add_vertex(out_vertices, v2);
		const int i3 = triangle_mesh_tools::add_vertex(out_vertices, v3);
		const int i5 = triangle_mesh_tools::add_vertex(out_vertices, v5);
		const int i6 = triangle_mesh_tools::add_vertex(out_vertices, v6);
		const int i7 = triangle_mesh_tools::add_vertex(out_vertices, v7);
		const int i4 = triangle_mesh_tools::add_vertex(out_vertices, v4);
		const int i8 = triangle_mesh_tools::add_vertex(out_vertices, v8);
		const int i9 = triangle_mesh_tools::add_vertex(out_vertices, v9);
		const int i10 = triangle_mesh_tools::add_vertex(out_vertices, v10);
		const int i11 = triangle_mesh_tools::add_vertex(out_vertices, v11);

		triangle_mesh_tools::add_triangle(out_indices, i0, i8, i4);
		triangle_mesh_tools::add_triangle(out_indices, i0, i5, i10);
		triangle_mesh_tools::add_triangle(out_indices, i2, i4, i9);
		triangle_mesh_tools::add_triangle(out_indices, i2, i11, i5);
		triangle_mesh_tools::add_triangle(out_indices, i1, i6, i8);
		triangle_mesh_tools::add_triangle(out_indices, i1, i10, i7);
		triangle_mesh_tools::add_triangle(out_indices, i3, i9, i6);
		triangle_mesh_tools::add_triangle(out_indices, i3, i7, i11);
		triangle_mesh_tools::add_triangle(out_indices, i0, i10, i8);
		triangle_mesh_tools::add_triangle(out_indices, i1, i8, i10);
		triangle_mesh_tools::add_triangle(out_indices, i2, i9, i11);
		triangle_mesh_tools::add_triangle(out_indices, i3, i11, i9);
		triangle_mesh_tools::add_triangle(out_indices, i4, i2, i0);
		triangle_mesh_tools::add_triangle(out_indices, i5, i0, i2);
		triangle_mesh_tools::add_triangle(out_indices, i6, i1, i3);
		triangle_mesh_tools::add_triangle(out_indices, i7, i3, i1);
		triangle_mesh_tools::add_triangle(out_indices, i8, i6, i4);
		triangle_mesh_tools::add_triangle(out_indices, i9, i4, i6);
		triangle_mesh_tools::add_triangle(out_indices, i10, i5, i7);
		triangle_mesh_tools::add_triangle(out_indices, i11, i7, i5);
	}
	else
	{
		out_vertices.reserve(out_vertices.size() + 60);

		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v8, v4);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v5, v10);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v2, v4, v9);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v2, v11, v5);

		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v1, v6, v8);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v1, v10, v7);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v3, v9, v6);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v3, v7, v11);

		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v0, v10, v8);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v1, v8, v10);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v2, v9, v11);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v3, v11, v9);

		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v4, v2, v0);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v5, v0, v2);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v6, v1, v3);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v7, v3, v1);

		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v8, v6, v4);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v9, v4, v6);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v10, v5, v7);
		triangle_mesh_tools::add_triangle(out_vertices, out_indices, v11, v7, v5);
	}

	if(y_up)
		convert_to_y_up(out_vertices);
}

void triangle_mesh_tools::create_dodecahedron(std::vector<math::vec3>& out_vertices,
											  std::vector<std::uint32_t>& out_indices, bool share_vertices,
											  bool y_up)
{
	const float a = 1.0f / 1.7320508f;
	const float b = math::sqrt((3.0f - 2.23606797f) / 6.0f);
	const float c = math::sqrt((3.0f + 2.23606797f) / 6.0f);

	math::vec3 nv[20];

	nv[0] = math::vec3(a, a, a);
	nv[1] = math::vec3(a, a, -a);
	nv[2] = math::vec3(a, -a, a);
	nv[3] = math::vec3(a, -a, -a);
	nv[4] = math::vec3(-a, a, a);
	nv[5] = math::vec3(-a, a, -a);
	nv[6] = math::vec3(-a, -a, a);
	nv[7] = math::vec3(-a, -a, -a);
	nv[8] = math::vec3(b, c, 0.0f);
	nv[9] = math::vec3(-b, c, 0.0f);
	nv[10] = math::vec3(b, -c, 0.0f);
	nv[11] = math::vec3(-b, -c, 0.0f);
	nv[12] = math::vec3(c, 0.0f, b);
	nv[13] = math::vec3(c, 0.0f, -b);
	nv[14] = math::vec3(-c, 0.0f, b);
	nv[15] = math::vec3(-c, 0.0f, -b);
	nv[16] = math::vec3(0.0f, b, c);
	nv[17] = math::vec3(0.0f, -b, c);
	nv[18] = math::vec3(0.0f, b, -c);
	nv[19] = math::vec3(0.0f, -b, -c);

	if(share_vertices)
	{
		int ni[20];
		for(int i = 0; i < 20; i++)
			ni[i] = triangle_mesh_tools::add_vertex(out_vertices, nv[i]);

		triangle_mesh_tools::add_pentagon(out_indices, ni[0], ni[8], ni[9], ni[4], ni[16]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[0], ni[12], ni[13], ni[1], ni[8]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[0], ni[16], ni[17], ni[2], ni[12]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[8], ni[1], ni[18], ni[5], ni[9]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[12], ni[2], ni[10], ni[3], ni[13]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[16], ni[4], ni[14], ni[6], ni[17]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[9], ni[5], ni[15], ni[14], ni[4]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[6], ni[11], ni[10], ni[2], ni[17]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[3], ni[19], ni[18], ni[1], ni[13]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[7], ni[15], ni[5], ni[18], ni[19]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[7], ni[11], ni[6], ni[14], ni[15]);
		triangle_mesh_tools::add_pentagon(out_indices, ni[7], ni[19], ni[3], ni[10], ni[11]);
	}
	else
	{
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[0], nv[8], nv[9], nv[4], nv[16]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[0], nv[12], nv[13], nv[1], nv[8]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[0], nv[16], nv[17], nv[2], nv[12]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[8], nv[1], nv[18], nv[5], nv[9]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[12], nv[2], nv[10], nv[3], nv[13]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[16], nv[4], nv[14], nv[6], nv[17]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[9], nv[5], nv[15], nv[14], nv[4]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[6], nv[11], nv[10], nv[2], nv[17]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[3], nv[19], nv[18], nv[1], nv[13]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[7], nv[15], nv[5], nv[18], nv[19]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[7], nv[11], nv[6], nv[14], nv[15]);
		triangle_mesh_tools::add_pentagon(out_vertices, out_indices, nv[7], nv[19], nv[3], nv[10], nv[11]);
	}

	if(y_up)
		convert_to_y_up(out_vertices);
}

// ------------------------------------------------------------------------------------------------
static void tessellate_sphere(std::vector<math::vec3>& out_vertices, std::vector<std::uint32_t>& out_indices,
							  const std::vector<math::vec3>& in_vertices,
							  const std::vector<std::uint32_t>& in_indices, bool share_vertices)
{
	int base_out_vertex = static_cast<int>(out_vertices.size());

	for(size_t i = 0; i < in_indices.size(); i += 3)
	{
		const math::vec3& a = in_vertices[in_indices[i + 0]];
		const math::vec3& b = in_vertices[in_indices[i + 1]];
		const math::vec3& c = in_vertices[in_indices[i + 2]];

		math::vec3 v1 = math::normalize(a + b);
		math::vec3 v2 = math::normalize(b + c);
		math::vec3 v3 = math::normalize(c + a);

		if(share_vertices)
		{
			// very inefficient way but couldn't think of anything better: feel free
			// to improve!
			triangle_mesh_tools::add_triangle_merge_same_position_vertices(out_vertices, out_indices, v1, v2,
																		   v3, base_out_vertex);
			triangle_mesh_tools::add_triangle_merge_same_position_vertices(out_vertices, out_indices, a, v1,
																		   v3, base_out_vertex);
			triangle_mesh_tools::add_triangle_merge_same_position_vertices(out_vertices, out_indices, b, v2,
																		   v1, base_out_vertex);
			triangle_mesh_tools::add_triangle_merge_same_position_vertices(out_vertices, out_indices, c, v3,
																		   v2, base_out_vertex);
		}
		else
		{
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, v1, v2, v3);
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, a, v1, v3);
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, b, v2, v1);
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, c, v3, v2);
		}
	}
}

void triangle_mesh_tools::create_icosphere(std::vector<math::vec3>& out_vertices,
										   std::vector<std::uint32_t>& out_indices, int tessellation_level,
										   bool share_vertices, bool y_up)
{
	std::vector<math::vec3> temp0_vertices;
	std::vector<std::uint32_t> temp0_indices;
	std::vector<math::vec3> temp1_vertices;
	std::vector<std::uint32_t> temp1_indices;

	std::vector<math::vec3>* srcVertices = &temp0_vertices;
	std::vector<std::uint32_t>* srcIndices = &temp0_indices;
	std::vector<math::vec3>* dstVertices = &temp1_vertices;
	std::vector<std::uint32_t>* dstIndices = &temp1_indices;

	if(share_vertices && (tessellation_level > 5))
	{
		assert(false);
		// this code is not really suitable for high tessellation levels when
		// share_vertices is true; please
		// look into optimizing tessellate_sphere to avoid/optimize current
		// incredibly slow O(N^2) search
	}

	// Construct an icosahedron to start with
	create_icosahedron(*srcVertices, *srcIndices, share_vertices, y_up);

	for(int i = 0; i < tessellation_level; i++)
	{
		dstVertices->clear();
		dstIndices->clear();
		tessellate_sphere(*dstVertices, *dstIndices, *srcVertices, *srcIndices, share_vertices);
		std::swap(srcVertices, dstVertices);
		std::swap(srcIndices, dstIndices);
	}

	out_vertices = *srcVertices;
	out_indices = *srcIndices;
}

void triangle_mesh_tools::create_cylinder(std::vector<math::vec3>& out_vertices,
										  std::vector<std::uint32_t>& out_indices, float height,
										  float radius_bottom, float radius_top, int tessellation,
										  bool open_top_bottom, bool share_vertices, bool y_up)
{
	// has to have at least 3 sides!
	if(tessellation < 3)
		return;

	// No negative radii
	radius_bottom = math::abs(radius_bottom);
	radius_top = math::abs(radius_top);

	float half_height = height / 2;

	float radii_sum = radius_top + radius_bottom;
	if(radius_bottom < (radii_sum)*1e-4f)
		radius_bottom = 0.0f;
	if(radius_top < (radii_sum)*1e-4f)
		radius_top = 0.0f;

	// Now construct all segments
	const float angle_delta = math::pi<float>() * 2.0f / tessellation;

	const math::vec3 vT = math::vec3(0.0f, 0.0f, half_height);
	const math::vec3 vB = math::vec3(0.0f, 0.0f, -half_height);
	int iB = 0;
	int iT = 0;

	std::vector<math::vec3> vTs;
	std::vector<math::vec3> vBs;
	std::vector<std::uint32_t> iTs;
	std::vector<std::uint32_t> iBs;

	bool share_top_bottom_vertices = false; // = share_vertices

	if(share_top_bottom_vertices)
	{
		iT = triangle_mesh_tools::add_vertex(out_vertices, vT);
		iB = triangle_mesh_tools::add_vertex(out_vertices, vB);
	}

	float angle = 0.0f;

	for(int i = 0; i < tessellation; i++)
	{
		float s = math::cos(angle);
		float t = math::sin(angle);
		angle += angle_delta;

		vTs.push_back(math::vec3(s * radius_top, t * radius_top, half_height));
		vBs.push_back(math::vec3(s * radius_bottom, t * radius_bottom, -half_height));

		if(share_vertices)
		{
			iTs.push_back(triangle_mesh_tools::add_vertex(out_vertices, vTs[i]));
			iBs.push_back(triangle_mesh_tools::add_vertex(out_vertices, vBs[i]));
		}
	}

	for(int i = 0; i < tessellation; i++)
	{
		int next = (i + 1) % tessellation;
		if(!share_vertices)
		{
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, vTs[i], vBs[i], vTs[next]);
			triangle_mesh_tools::add_triangle(out_vertices, out_indices, vTs[next], vBs[i], vBs[next]);
		}
		else
		{
			triangle_mesh_tools::add_triangle(out_indices, iTs[i], iBs[i], iTs[next]);
			triangle_mesh_tools::add_triangle(out_indices, iTs[next], iBs[i], iBs[next]);
		}

		if(!open_top_bottom)
		{
			// top cap
			if(radius_top > 0.0f)
			{
				if(!share_top_bottom_vertices)
					triangle_mesh_tools::add_triangle(out_vertices, out_indices, vTs[i], vTs[next], vT);
				else
					triangle_mesh_tools::add_triangle(out_indices, iTs[i], iTs[next], iT);
			}

			// bottom cap
			if(radius_bottom > 0.0f)
			{
				if(!share_top_bottom_vertices)
					triangle_mesh_tools::add_triangle(out_vertices, out_indices, vBs[next], vBs[i], vB);
				else
					triangle_mesh_tools::add_triangle(out_indices, iBs[next], iBs[i], iB);
			}
		}
	}

	if(y_up)
		convert_to_y_up(out_vertices);
}

//----------------------------------------------------------------------------
// Teapot data
//----------------------------------------------------------------------------
#define NUMTEAPOTVERTICES 1178
#define NUMTEAPOTINDICES 6768

static float teapot_vertices_pos_only[NUMTEAPOTVERTICES * 3] = {
	0.678873f,  0.330678f,  0.000000f,  0.669556f,  0.358022f,  0.000000f,  0.671003f,  0.374428f,
	0.000000f,  0.680435f,  0.379897f,  0.000000f,  0.695077f,  0.374428f,  0.000000f,  0.712148f,
	0.358022f,  0.000000f,  0.728873f,  0.330678f,  0.000000f,  0.654243f,  0.330678f,  0.187963f,
	0.645254f,  0.358022f,  0.185461f,  0.646650f,  0.374428f,  0.185850f,  0.655751f,  0.379897f,
	0.188383f,  0.669877f,  0.374428f,  0.192314f,  0.686348f,  0.358022f,  0.196898f,  0.702484f,
	0.330678f,  0.201389f,  0.584502f,  0.330678f,  0.355704f,  0.576441f,  0.358022f,  0.350969f,
	0.577693f,  0.374428f,  0.351704f,  0.585854f,  0.379897f,  0.356498f,  0.598522f,  0.374428f,
	0.363938f,  0.613292f,  0.358022f,  0.372613f,  0.627762f,  0.330678f,  0.381111f,  0.475873f,
	0.330678f,  0.497000f,  0.469258f,  0.358022f,  0.490385f,  0.470285f,  0.374428f,  0.491412f,
	0.476982f,  0.379897f,  0.498109f,  0.487377f,  0.374428f,  0.508505f,  0.499498f,  0.358022f,
	0.520626f,  0.511373f,  0.330678f,  0.532500f,  0.334576f,  0.330678f,  0.605630f,  0.329842f,
	0.358022f,  0.597569f,  0.330577f,  0.374428f,  0.598820f,  0.335370f,  0.379897f,  0.606982f,
	0.342810f,  0.374428f,  0.619649f,  0.351485f,  0.358022f,  0.634419f,  0.359984f,  0.330678f,
	0.648889f,  0.166836f,  0.330678f,  0.675370f,  0.164334f,  0.358022f,  0.666381f,  0.164722f,
	0.374428f,  0.667777f,  0.167255f,  0.379897f,  0.676878f,  0.171187f,  0.374428f,  0.691004f,
	0.175771f,  0.358022f,  0.707475f,  0.180262f,  0.330678f,  0.723611f,  -0.021127f, 0.330678f,
	0.700000f,  -0.021127f, 0.358022f,  0.690683f,  -0.021127f, 0.374428f,  0.692130f,  -0.021127f,
	0.379897f,  0.701563f,  -0.021127f, 0.374428f,  0.716204f,  -0.021127f, 0.358022f,  0.733276f,
	-0.021127f, 0.330678f,  0.750000f,  -0.224715f, 0.330678f,  0.675370f,  -0.215631f, 0.358022f,
	0.666381f,  -0.211606f, 0.374428f,  0.667777f,  -0.211463f, 0.379897f,  0.676878f,  -0.214020f,
	0.374428f,  0.691004f,  -0.218098f, 0.358022f,  0.707475f,  -0.222516f, 0.330678f,  0.723611f,
	-0.396831f, 0.330678f,  0.605630f,  -0.383671f, 0.358022f,  0.597569f,  -0.378758f, 0.374428f,
	0.598820f,  -0.380125f, 0.379897f,  0.606982f,  -0.385806f, 0.374428f,  0.619649f,  -0.393832f,
	0.358022f,  0.634419f,  -0.402238f, 0.330678f,  0.648889f,  -0.535002f, 0.330678f,  0.497000f,
	-0.521278f, 0.358022f,  0.490385f,  -0.517539f, 0.374428f,  0.491412f,  -0.521346f, 0.379897f,
	0.498109f,  -0.530257f, 0.374428f,  0.508505f,  -0.541831f, 0.358022f,  0.520626f,  -0.553627f,
	0.330678f,  0.532500f,  -0.636757f, 0.330678f,  0.355704f,  -0.624483f, 0.358022f,  0.350969f,
	-0.622910f, 0.374428f,  0.351704f,  -0.629359f, 0.379897f,  0.356498f,  -0.641146f, 0.374428f,
	0.363938f,  -0.655593f, 0.358022f,  0.372613f,  -0.670016f, 0.330678f,  0.381111f,  -0.699623f,
	0.330678f,  0.187963f,  -0.689317f, 0.358022f,  0.185461f,  -0.689830f, 0.374428f,  0.185850f,
	-0.698396f, 0.379897f,  0.188382f,  -0.712247f, 0.374428f,  0.192314f,  -0.728617f, 0.358022f,
	0.196898f,  -0.744738f, 0.330678f,  0.201389f,  -0.721127f, 0.330678f,  0.000000f,  -0.711810f,
	0.358022f,  0.000000f,  -0.713257f, 0.374428f,  0.000000f,  -0.722690f, 0.379897f,  0.000000f,
	-0.737331f, 0.374428f,  0.000000f,  -0.754403f, 0.358022f,  0.000000f,  -0.771127f, 0.330678f,
	0.000000f,  -0.696498f, 0.330678f,  -0.187963f, -0.687508f, 0.358022f,  -0.185461f, -0.688904f,
	0.374428f,  -0.185850f, -0.698005f, 0.379897f,  -0.188383f, -0.712131f, 0.374428f,  -0.192314f,
	-0.728602f, 0.358022f,  -0.196898f, -0.744738f, 0.330678f,  -0.201389f, -0.626757f, 0.330678f,
	-0.355704f, -0.618696f, 0.358022f,  -0.350969f, -0.619948f, 0.374428f,  -0.351704f, -0.628109f,
	0.379897f,  -0.356498f, -0.640776f, 0.374428f,  -0.363938f, -0.655546f, 0.358022f,  -0.372613f,
	-0.670016f, 0.330678f,  -0.381111f, -0.518127f, 0.330678f,  -0.497000f, -0.511512f, 0.358022f,
	-0.490385f, -0.512539f, 0.374428f,  -0.491412f, -0.519237f, 0.379897f,  -0.498109f, -0.529632f,
	0.374428f,  -0.508505f, -0.541753f, 0.358022f,  -0.520626f, -0.553627f, 0.330678f,  -0.532500f,
	-0.376831f, 0.330678f,  -0.605630f, -0.372096f, 0.358022f,  -0.597569f, -0.372832f, 0.374428f,
	-0.598820f, -0.377625f, 0.379897f,  -0.606982f, -0.385065f, 0.374428f,  -0.619649f, -0.393740f,
	0.358022f,  -0.634419f, -0.402238f, 0.330678f,  -0.648889f, -0.209090f, 0.330678f,  -0.675370f,
	-0.206588f, 0.358022f,  -0.666381f, -0.206977f, 0.374428f,  -0.667777f, -0.209510f, 0.379897f,
	-0.676878f, -0.213441f, 0.374428f,  -0.691004f, -0.218025f, 0.358022f,  -0.707475f, -0.222516f,
	0.330678f,  -0.723611f, -0.021127f, 0.330678f,  -0.700000f, -0.021127f, 0.358022f,  -0.690683f,
	-0.021127f, 0.374428f,  -0.692130f, -0.021127f, 0.379897f,  -0.701563f, -0.021127f, 0.374428f,
	-0.716204f, -0.021127f, 0.358022f,  -0.733276f, -0.021127f, 0.330678f,  -0.750000f, 0.166836f,
	0.330678f,  -0.675370f, 0.164334f,  0.358022f,  -0.666381f, 0.164722f,  0.374428f,  -0.667777f,
	0.167255f,  0.379897f,  -0.676878f, 0.171187f,  0.374428f,  -0.691004f, 0.175771f,  0.358022f,
	-0.707475f, 0.180262f,  0.330678f,  -0.723611f, 0.334576f,  0.330678f,  -0.605630f, 0.329842f,
	0.358022f,  -0.597569f, 0.330577f,  0.374428f,  -0.598820f, 0.335370f,  0.379897f,  -0.606982f,
	0.342810f,  0.374428f,  -0.619649f, 0.351485f,  0.358022f,  -0.634419f, 0.359984f,  0.330678f,
	-0.648889f, 0.475873f,  0.330678f,  -0.497000f, 0.469258f,  0.358022f,  -0.490385f, 0.470285f,
	0.374428f,  -0.491412f, 0.476982f,  0.379897f,  -0.498109f, 0.487377f,  0.374428f,  -0.508505f,
	0.499498f,  0.358022f,  -0.520626f, 0.511373f,  0.330678f,  -0.532500f, 0.584502f,  0.330678f,
	-0.355704f, 0.576441f,  0.358022f,  -0.350969f, 0.577693f,  0.374428f,  -0.351704f, 0.585854f,
	0.379897f,  -0.356498f, 0.598522f,  0.374428f,  -0.363938f, 0.613292f,  0.358022f,  -0.372613f,
	0.627762f,  0.330678f,  -0.381111f, 0.654243f,  0.330678f,  -0.187963f, 0.645254f,  0.358022f,
	-0.185461f, 0.646650f,  0.374428f,  -0.185850f, 0.655751f,  0.379897f,  -0.188382f, 0.669877f,
	0.374428f,  -0.192314f, 0.686348f,  0.358022f,  -0.196898f, 0.702484f,  0.330678f,  -0.201389f,
	0.790794f,  0.199602f,  0.000000f,  0.849243f,  0.069567f,  0.000000f,  0.900748f,  -0.058384f,
	0.000000f,  0.941836f,  -0.183211f, 0.000000f,  0.969035f,  -0.303870f, 0.000000f,  0.978873f,
	-0.419322f, 0.000000f,  0.762227f,  0.199602f,  0.218016f,  0.818619f,  0.069567f,  0.233711f,
	0.868312f,  -0.058384f, 0.247541f,  0.907954f,  -0.183211f, 0.258573f,  0.934196f,  -0.303870f,
	0.265877f,  0.943688f,  -0.419322f, 0.268519f,  0.681335f,  0.199602f,  0.412576f,  0.731904f,
	0.069567f,  0.442277f,  0.776465f,  -0.058384f, 0.468449f,  0.812014f,  -0.183211f, 0.489328f,
	0.835546f,  -0.303870f, 0.503149f,  0.844058f,  -0.419322f, 0.508148f,  0.555337f,  0.199602f,
	0.576464f,  0.596836f,  0.069567f,  0.617963f,  0.633404f,  -0.058384f, 0.654531f,  0.662577f,
	-0.183211f, 0.683704f,  0.681888f,  -0.303870f, 0.703015f,  0.688873f,  -0.419322f, 0.710000f,
	0.391449f,  0.199602f,  0.702462f,  0.421150f,  0.069567f,  0.753032f,  0.447322f,  -0.058384f,
	0.797593f,  0.468201f,  -0.183211f, 0.833141f,  0.482022f,  -0.303870f, 0.856674f,  0.487021f,
	-0.419322f, 0.865185f,  0.196889f,  0.199602f,  0.783354f,  0.212583f,  0.069567f,  0.839746f,
	0.226413f,  -0.058384f, 0.889439f,  0.237446f,  -0.183211f, 0.929081f,  0.244750f,  -0.303870f,
	0.955323f,  0.247391f,  -0.419322f, 0.964815f,  -0.021127f, 0.199602f,  0.811921f,  -0.021127f,
	0.069567f,  0.870370f,  -0.021127f, -0.058384f, 0.921875f,  -0.021127f, -0.183211f, 0.962963f,
	-0.021127f, -0.303870f, 0.990162f,  -0.021127f, -0.419322f, 1.000000f,  -0.239143f, 0.199602f,
	0.783354f,  -0.254838f, 0.069567f,  0.839746f,  -0.268668f, -0.058384f, 0.889439f,  -0.279701f,
	-0.183211f, 0.929081f,  -0.287004f, -0.303870f, 0.955323f,  -0.289646f, -0.419322f, 0.964815f,
	-0.433704f, 0.199602f,  0.702462f,  -0.463404f, 0.069567f,  0.753032f,  -0.489576f, -0.058384f,
	0.797593f,  -0.510455f, -0.183211f, 0.833141f,  -0.524276f, -0.303870f, 0.856674f,  -0.529275f,
	-0.419322f, 0.865185f,  -0.597591f, 0.199602f,  0.576464f,  -0.639090f, 0.069567f,  0.617963f,
	-0.675658f, -0.058384f, 0.654531f,  -0.704831f, -0.183211f, 0.683704f,  -0.724142f, -0.303870f,
	0.703015f,  -0.731127f, -0.419322f, 0.710000f,  -0.723589f, 0.199602f,  0.412576f,  -0.774159f,
	0.069567f,  0.442277f,  -0.818720f, -0.058384f, 0.468449f,  -0.854269f, -0.183211f, 0.489328f,
	-0.877801f, -0.303870f, 0.503149f,  -0.886312f, -0.419322f, 0.508148f,  -0.804481f, 0.199602f,
	0.218016f,  -0.860873f, 0.069567f,  0.233711f,  -0.910566f, -0.058384f, 0.247540f,  -0.950208f,
	-0.183211f, 0.258573f,  -0.976450f, -0.303870f, 0.265877f,  -0.985942f, -0.419322f, 0.268518f,
	-0.833049f, 0.199602f,  0.000000f,  -0.891498f, 0.069567f,  0.000000f,  -0.943002f, -0.058384f,
	0.000000f,  -0.984090f, -0.183211f, 0.000000f,  -1.011289f, -0.303870f, 0.000000f,  -1.021127f,
	-0.419322f, 0.000000f,  -0.804481f, 0.199602f,  -0.218016f, -0.860873f, 0.069567f,  -0.233711f,
	-0.910566f, -0.058384f, -0.247541f, -0.950208f, -0.183211f, -0.258573f, -0.976450f, -0.303870f,
	-0.265877f, -0.985942f, -0.419322f, -0.268519f, -0.723589f, 0.199602f,  -0.412576f, -0.774159f,
	0.069567f,  -0.442277f, -0.818720f, -0.058384f, -0.468449f, -0.854269f, -0.183211f, -0.489328f,
	-0.877801f, -0.303870f, -0.503149f, -0.886312f, -0.419322f, -0.508148f, -0.597591f, 0.199602f,
	-0.576464f, -0.639090f, 0.069567f,  -0.617963f, -0.675658f, -0.058384f, -0.654531f, -0.704831f,
	-0.183211f, -0.683704f, -0.724142f, -0.303870f, -0.703015f, -0.731127f, -0.419322f, -0.710000f,
	-0.433704f, 0.199602f,  -0.702462f, -0.463404f, 0.069567f,  -0.753032f, -0.489576f, -0.058384f,
	-0.797593f, -0.510455f, -0.183211f, -0.833141f, -0.524276f, -0.303870f, -0.856674f, -0.529275f,
	-0.419322f, -0.865185f, -0.239143f, 0.199602f,  -0.783354f, -0.254838f, 0.069567f,  -0.839746f,
	-0.268668f, -0.058384f, -0.889439f, -0.279701f, -0.183211f, -0.929081f, -0.287004f, -0.303870f,
	-0.955323f, -0.289646f, -0.419322f, -0.964815f, -0.021127f, 0.199602f,  -0.811921f, -0.021127f,
	0.069567f,  -0.870370f, -0.021127f, -0.058384f, -0.921875f, -0.021127f, -0.183211f, -0.962963f,
	-0.021127f, -0.303870f, -0.990162f, -0.021127f, -0.419322f, -1.000000f, 0.196889f,  0.199602f,
	-0.783354f, 0.212583f,  0.069567f,  -0.839746f, 0.226413f,  -0.058384f, -0.889439f, 0.237446f,
	-0.183211f, -0.929081f, 0.244750f,  -0.303870f, -0.955323f, 0.247391f,  -0.419322f, -0.964815f,
	0.391449f,  0.199602f,  -0.702462f, 0.421150f,  0.069567f,  -0.753032f, 0.447322f,  -0.058384f,
	-0.797593f, 0.468201f,  -0.183211f, -0.833141f, 0.482022f,  -0.303870f, -0.856674f, 0.487021f,
	-0.419322f, -0.865185f, 0.555337f,  0.199602f,  -0.576464f, 0.596836f,  0.069567f,  -0.617963f,
	0.633404f,  -0.058384f, -0.654531f, 0.662577f,  -0.183211f, -0.683704f, 0.681888f,  -0.303870f,
	-0.703015f, 0.688873f,  -0.419322f, -0.710000f, 0.681335f,  0.199602f,  -0.412576f, 0.731904f,
	0.069567f,  -0.442277f, 0.776465f,  -0.058384f, -0.468449f, 0.812014f,  -0.183211f, -0.489328f,
	0.835546f,  -0.303870f, -0.503149f, 0.844058f,  -0.419322f, -0.508148f, 0.762227f,  0.199602f,
	-0.218016f, 0.818619f,  0.069567f,  -0.233711f, 0.868312f,  -0.058384f, -0.247540f, 0.907954f,
	-0.183211f, -0.258573f, 0.934196f,  -0.303870f, -0.265877f, 0.943688f,  -0.419322f, -0.268518f,
	0.960354f,  -0.522620f, 0.000000f,  0.914058f,  -0.608211f, 0.000000f,  0.853873f,  -0.677134f,
	0.000000f,  0.793688f,  -0.730433f, 0.000000f,  0.747391f,  -0.769148f, 0.000000f,  0.728873f,
	-0.794322f, 0.000000f,  0.925821f,  -0.522620f, 0.263546f,  0.881153f,  -0.608211f, 0.251115f,
	0.823086f,  -0.677134f, 0.234954f,  0.765018f,  -0.730433f, 0.218793f,  0.720351f,  -0.769148f,
	0.206361f,  0.702484f,  -0.794322f, 0.201389f,  0.828036f,  -0.522620f, 0.498738f,  0.787981f,
	-0.608211f, 0.475213f,  0.735910f,  -0.677134f, 0.444630f,  0.683839f,  -0.730433f, 0.414047f,
	0.643784f,  -0.769148f, 0.390521f,  0.627762f,  -0.794322f, 0.381111f,  0.675725f,  -0.522620f,
	0.696852f,  0.642854f,  -0.608211f, 0.663981f,  0.600123f,  -0.677134f, 0.621250f,  0.557391f,
	-0.730433f, 0.578519f,  0.524521f,  -0.769148f, 0.545648f,  0.511373f,  -0.794322f, 0.532500f,
	0.477611f,  -0.522620f, 0.849163f,  0.454085f,  -0.608211f, 0.809108f,  0.423502f,  -0.677134f,
	0.757037f,  0.392919f,  -0.730433f, 0.704966f,  0.369394f,  -0.769148f, 0.664911f,  0.359984f,
	-0.794322f, 0.648889f,  0.242419f,  -0.522620f, 0.946948f,  0.229987f,  -0.608211f, 0.902281f,
	0.213826f,  -0.677134f, 0.844213f,  0.197666f,  -0.730433f, 0.786145f,  0.185234f,  -0.769148f,
	0.741478f,  0.180262f,  -0.794322f, 0.723611f,  -0.021127f, -0.522620f, 0.981482f,  -0.021127f,
	-0.608211f, 0.935185f,  -0.021127f, -0.677134f, 0.875000f,  -0.021127f, -0.730433f, 0.814815f,
	-0.021127f, -0.769148f, 0.768519f,  -0.021127f, -0.794322f, 0.750000f,  -0.284673f, -0.522620f,
	0.946948f,  -0.272242f, -0.608211f, 0.902281f,  -0.256081f, -0.677134f, 0.844213f,  -0.239920f,
	-0.730433f, 0.786145f,  -0.227489f, -0.769148f, 0.741478f,  -0.222516f, -0.794322f, 0.723611f,
	-0.519865f, -0.522620f, 0.849163f,  -0.496340f, -0.608211f, 0.809108f,  -0.465757f, -0.677134f,
	0.757037f,  -0.435174f, -0.730433f, 0.704966f,  -0.411649f, -0.769148f, 0.664911f,  -0.402238f,
	-0.794322f, 0.648889f,  -0.717979f, -0.522620f, 0.696852f,  -0.685109f, -0.608211f, 0.663981f,
	-0.642377f, -0.677134f, 0.621250f,  -0.599646f, -0.730433f, 0.578519f,  -0.566775f, -0.769148f,
	0.545648f,  -0.553627f, -0.794322f, 0.532500f,  -0.870290f, -0.522620f, 0.498738f,  -0.830236f,
	-0.608211f, 0.475213f,  -0.778164f, -0.677134f, 0.444630f,  -0.726093f, -0.730433f, 0.414047f,
	-0.686038f, -0.769148f, 0.390521f,  -0.670016f, -0.794322f, 0.381111f,  -0.968075f, -0.522620f,
	0.263546f,  -0.923408f, -0.608211f, 0.251115f,  -0.865340f, -0.677134f, 0.234954f,  -0.807273f,
	-0.730433f, 0.218793f,  -0.762605f, -0.769148f, 0.206361f,  -0.744738f, -0.794322f, 0.201389f,
	-1.002609f, -0.522620f, 0.000000f,  -0.956312f, -0.608211f, 0.000000f,  -0.896127f, -0.677134f,
	0.000000f,  -0.835942f, -0.730433f, 0.000000f,  -0.789646f, -0.769148f, 0.000000f,  -0.771127f,
	-0.794322f, 0.000000f,  -0.968075f, -0.522620f, -0.263546f, -0.923408f, -0.608211f, -0.251115f,
	-0.865340f, -0.677134f, -0.234954f, -0.807273f, -0.730433f, -0.218793f, -0.762605f, -0.769148f,
	-0.206361f, -0.744738f, -0.794322f, -0.201389f, -0.870290f, -0.522620f, -0.498738f, -0.830236f,
	-0.608211f, -0.475213f, -0.778164f, -0.677134f, -0.444630f, -0.726093f, -0.730433f, -0.414047f,
	-0.686038f, -0.769148f, -0.390521f, -0.670016f, -0.794322f, -0.381111f, -0.717979f, -0.522620f,
	-0.696852f, -0.685109f, -0.608211f, -0.663981f, -0.642377f, -0.677134f, -0.621250f, -0.599646f,
	-0.730433f, -0.578519f, -0.566775f, -0.769148f, -0.545648f, -0.553627f, -0.794322f, -0.532500f,
	-0.519865f, -0.522620f, -0.849163f, -0.496340f, -0.608211f, -0.809108f, -0.465757f, -0.677134f,
	-0.757037f, -0.435174f, -0.730433f, -0.704966f, -0.411648f, -0.769148f, -0.664911f, -0.402238f,
	-0.794322f, -0.648889f, -0.284673f, -0.522620f, -0.946948f, -0.272242f, -0.608211f, -0.902281f,
	-0.256081f, -0.677134f, -0.844213f, -0.239920f, -0.730433f, -0.786145f, -0.227489f, -0.769148f,
	-0.741478f, -0.222516f, -0.794322f, -0.723611f, -0.021127f, -0.522620f, -0.981482f, -0.021127f,
	-0.608211f, -0.935185f, -0.021127f, -0.677134f, -0.875000f, -0.021127f, -0.730433f, -0.814815f,
	-0.021127f, -0.769148f, -0.768519f, -0.021127f, -0.794322f, -0.750000f, 0.242419f,  -0.522620f,
	-0.946948f, 0.229987f,  -0.608211f, -0.902281f, 0.213827f,  -0.677134f, -0.844213f, 0.197666f,
	-0.730433f, -0.786145f, 0.185234f,  -0.769148f, -0.741478f, 0.180262f,  -0.794322f, -0.723611f,
	0.477611f,  -0.522620f, -0.849163f, 0.454085f,  -0.608211f, -0.809108f, 0.423502f,  -0.677134f,
	-0.757037f, 0.392919f,  -0.730433f, -0.704966f, 0.369394f,  -0.769148f, -0.664911f, 0.359984f,
	-0.794322f, -0.648889f, 0.675725f,  -0.522620f, -0.696852f, 0.642854f,  -0.608211f, -0.663981f,
	0.600123f,  -0.677134f, -0.621250f, 0.557391f,  -0.730433f, -0.578519f, 0.524521f,  -0.769148f,
	-0.545648f, 0.511373f,  -0.794322f, -0.532500f, 0.828036f,  -0.522620f, -0.498738f, 0.787981f,
	-0.608211f, -0.475213f, 0.735910f,  -0.677134f, -0.444630f, 0.683839f,  -0.730433f, -0.414047f,
	0.643784f,  -0.769148f, -0.390521f, 0.627762f,  -0.794322f, -0.381111f, 0.925821f,  -0.522620f,
	-0.263546f, 0.881153f,  -0.608211f, -0.251115f, 0.823086f,  -0.677134f, -0.234954f, 0.765018f,
	-0.730433f, -0.218793f, 0.720351f,  -0.769148f, -0.206361f, 0.702484f,  -0.794322f, -0.201389f,
	0.722796f,  -0.812898f, 0.000000f,  0.692762f,  -0.830433f, 0.000000f,  0.621060f,  -0.845884f,
	0.000000f,  0.489984f,  -0.858211f, 0.000000f,  0.281824f,  -0.866370f, 0.000000f,  -0.021127f,
	-0.869322f, 0.000000f,  0.696621f,  -0.812898f, 0.199757f,  0.667643f,  -0.830433f, 0.191692f,
	0.598465f,  -0.845884f, 0.172439f,  0.472000f,  -0.858211f, 0.137243f,  0.271165f,  -0.866370f,
	0.081348f,  0.622505f,  -0.812898f, 0.378023f,  0.596519f,  -0.830433f, 0.362761f,  0.534484f,
	-0.845884f, 0.326326f,  0.421079f,  -0.858211f, 0.259720f,  0.240982f,  -0.866370f, 0.153944f,
	0.507059f,  -0.812898f, 0.528186f,  0.485734f,  -0.830433f, 0.506861f,  0.434826f,  -0.845884f,
	0.455953f,  0.341762f,  -0.858211f, 0.362889f,  0.193968f,  -0.866370f, 0.215095f,  0.356896f,
	-0.812898f, 0.643632f,  0.341634f,  -0.830433f, 0.617646f,  0.305199f,  -0.845884f, 0.555611f,
	0.238593f,  -0.858211f, 0.442206f,  0.132817f,  -0.866370f, 0.262109f,  0.178630f,  -0.812898f,
	0.717749f,  0.170565f,  -0.830433f, 0.688771f,  0.151312f,  -0.845884f, 0.619592f,  0.116116f,
	-0.858211f, 0.493128f,  0.060221f,  -0.866370f, 0.292292f,  -0.021127f, -0.812898f, 0.743924f,
	-0.021127f, -0.830433f, 0.713889f,  -0.021127f, -0.845884f, 0.642188f,  -0.021127f, -0.858211f,
	0.511111f,  -0.021127f, -0.866370f, 0.302951f,  -0.220884f, -0.812898f, 0.717749f,  -0.212820f,
	-0.830433f, 0.688771f,  -0.193566f, -0.845884f, 0.619592f,  -0.158370f, -0.858211f, 0.493128f,
	-0.102475f, -0.866370f, 0.292292f,  -0.399151f, -0.812898f, 0.643632f,  -0.383889f, -0.830433f,
	0.617646f,  -0.347454f, -0.845884f, 0.555611f,  -0.280847f, -0.858211f, 0.442206f,  -0.175071f,
	-0.866370f, 0.262109f,  -0.549313f, -0.812898f, 0.528186f,  -0.527988f, -0.830433f, 0.506861f,
	-0.477080f, -0.845884f, 0.455953f,  -0.384016f, -0.858211f, 0.362889f,  -0.236223f, -0.866370f,
	0.215095f,  -0.664759f, -0.812898f, 0.378023f,  -0.638773f, -0.830433f, 0.362761f,  -0.576738f,
	-0.845884f, 0.326326f,  -0.463333f, -0.858211f, 0.259720f,  -0.283236f, -0.866370f, 0.153944f,
	-0.738876f, -0.812898f, 0.199757f,  -0.709898f, -0.830433f, 0.191692f,  -0.640719f, -0.845884f,
	0.172439f,  -0.514255f, -0.858211f, 0.137243f,  -0.313419f, -0.866370f, 0.081348f,  -0.765051f,
	-0.812898f, 0.000000f,  -0.735016f, -0.830433f, 0.000000f,  -0.663315f, -0.845884f, 0.000000f,
	-0.532238f, -0.858211f, 0.000000f,  -0.324079f, -0.866370f, 0.000000f,  -0.738876f, -0.812898f,
	-0.199757f, -0.709898f, -0.830433f, -0.191692f, -0.640719f, -0.845884f, -0.172439f, -0.514255f,
	-0.858211f, -0.137243f, -0.313419f, -0.866370f, -0.081348f, -0.664759f, -0.812898f, -0.378023f,
	-0.638773f, -0.830433f, -0.362761f, -0.576738f, -0.845884f, -0.326326f, -0.463333f, -0.858211f,
	-0.259720f, -0.283236f, -0.866370f, -0.153944f, -0.549313f, -0.812898f, -0.528186f, -0.527988f,
	-0.830433f, -0.506861f, -0.477080f, -0.845884f, -0.455953f, -0.384016f, -0.858211f, -0.362889f,
	-0.236223f, -0.866370f, -0.215095f, -0.399151f, -0.812898f, -0.643632f, -0.383889f, -0.830433f,
	-0.617646f, -0.347454f, -0.845884f, -0.555611f, -0.280847f, -0.858211f, -0.442206f, -0.175071f,
	-0.866370f, -0.262109f, -0.220884f, -0.812898f, -0.717749f, -0.212820f, -0.830433f, -0.688771f,
	-0.193566f, -0.845884f, -0.619592f, -0.158370f, -0.858211f, -0.493128f, -0.102475f, -0.866370f,
	-0.292292f, -0.021127f, -0.812898f, -0.743924f, -0.021127f, -0.830433f, -0.713889f, -0.021127f,
	-0.845884f, -0.642188f, -0.021127f, -0.858211f, -0.511111f, -0.021127f, -0.866370f, -0.302951f,
	0.178630f,  -0.812898f, -0.717749f, 0.170565f,  -0.830433f, -0.688771f, 0.151312f,  -0.845884f,
	-0.619592f, 0.116116f,  -0.858211f, -0.493128f, 0.060221f,  -0.866370f, -0.292292f, 0.356896f,
	-0.812898f, -0.643632f, 0.341634f,  -0.830433f, -0.617646f, 0.305199f,  -0.845884f, -0.555611f,
	0.238593f,  -0.858211f, -0.442206f, 0.132817f,  -0.866370f, -0.262109f, 0.507059f,  -0.812898f,
	-0.528186f, 0.485734f,  -0.830433f, -0.506861f, 0.434826f,  -0.845884f, -0.455953f, 0.341762f,
	-0.858211f, -0.362889f, 0.193968f,  -0.866370f, -0.215095f, 0.622505f,  -0.812898f, -0.378023f,
	0.596519f,  -0.830433f, -0.362761f, 0.534484f,  -0.845884f, -0.326326f, 0.421079f,  -0.858211f,
	-0.259720f, 0.240982f,  -0.866370f, -0.153944f, 0.696621f,  -0.812898f, -0.199757f, 0.667643f,
	-0.830433f, -0.191692f, 0.598465f,  -0.845884f, -0.172439f, 0.472000f,  -0.858211f, -0.137243f,
	0.271165f,  -0.866370f, -0.081348f, -0.821127f, 0.143178f,  0.000000f,  -0.983396f, 0.142657f,
	0.000000f,  -1.119275f, 0.139012f,  0.000000f,  -1.227377f, 0.129116f,  0.000000f,  -1.306313f,
	0.109845f,  0.000000f,  -1.354692f, 0.078074f,  0.000000f,  -1.371127f, 0.030678f,  0.000000f,
	-0.817424f, 0.151512f,  0.062500f,  -0.984648f, 0.150952f,  0.062500f,  -1.124351f, 0.147036f,
	0.062500f,  -1.235248f, 0.136407f,  0.062500f,  -1.316052f, 0.115709f,  0.062500f,  -1.365477f,
	0.081585f,  0.062500f,  -1.382239f, 0.030678f,  0.062500f,  -0.808164f, 0.172345f,  0.100000f,
	-0.987777f, 0.171689f,  0.100000f,  -1.137040f, 0.167098f,  0.100000f,  -1.254924f, 0.154637f,
	0.100000f,  -1.340400f, 0.130370f,  0.100000f,  -1.392441f, 0.090362f,  0.100000f,  -1.410016f,
	0.030678f,  0.100000f,  -0.796127f, 0.199428f,  0.112500f,  -0.991845f, 0.198647f,  0.112500f,
	-1.153535f, 0.193178f,  0.112500f,  -1.280502f, 0.178335f,  0.112500f,  -1.372053f, 0.149428f,
	0.112500f,  -1.427493f, 0.101772f,  0.112500f,  -1.446127f, 0.030678f,  0.112500f,  -0.784090f,
	0.226511f,  0.100000f,  -0.995913f, 0.225605f,  0.100000f,  -1.170030f, 0.219258f,  0.100000f,
	-1.306081f, 0.202032f,  0.100000f,  -1.403706f, 0.168487f,  0.100000f,  -1.462545f, 0.113182f,
	0.100000f,  -1.482238f, 0.030678f,  0.100000f,  -0.774831f, 0.247345f,  0.062500f,  -0.999042f,
	0.246342f,  0.062500f,  -1.182719f, 0.239320f,  0.062500f,  -1.325757f, 0.220261f,  0.062500f,
	-1.428054f, 0.183147f,  0.062500f,  -1.489509f, 0.121959f,  0.062500f,  -1.510016f, 0.030678f,
	0.062500f,  -0.771127f, 0.255678f,  0.000000f,  -1.000294f, 0.254636f,  0.000000f,  -1.187794f,
	0.247345f,  0.000000f,  -1.333627f, 0.227553f,  0.000000f,  -1.437794f, 0.189011f,  0.000000f,
	-1.500294f, 0.125470f,  0.000000f,  -1.521127f, 0.030678f,  0.000000f,  -0.774831f, 0.247345f,
	-0.062500f, -0.999042f, 0.246342f,  -0.062500f, -1.182719f, 0.239320f,  -0.062500f, -1.325757f,
	0.220261f,  -0.062500f, -1.428054f, 0.183147f,  -0.062500f, -1.489509f, 0.121959f,  -0.062500f,
	-1.510016f, 0.030678f,  -0.062500f, -0.784090f, 0.226511f,  -0.100000f, -0.995913f, 0.225605f,
	-0.100000f, -1.170030f, 0.219258f,  -0.100000f, -1.306081f, 0.202032f,  -0.100000f, -1.403706f,
	0.168487f,  -0.100000f, -1.462545f, 0.113182f,  -0.100000f, -1.482238f, 0.030678f,  -0.100000f,
	-0.796127f, 0.199428f,  -0.112500f, -0.991845f, 0.198647f,  -0.112500f, -1.153535f, 0.193178f,
	-0.112500f, -1.280502f, 0.178335f,  -0.112500f, -1.372053f, 0.149428f,  -0.112500f, -1.427493f,
	0.101772f,  -0.112500f, -1.446127f, 0.030678f,  -0.112500f, -0.808164f, 0.172345f,  -0.100000f,
	-0.987777f, 0.171689f,  -0.100000f, -1.137040f, 0.167098f,  -0.100000f, -1.254924f, 0.154637f,
	-0.100000f, -1.340400f, 0.130370f,  -0.100000f, -1.392441f, 0.090362f,  -0.100000f, -1.410016f,
	0.030678f,  -0.100000f, -0.817424f, 0.151512f,  -0.062500f, -0.984648f, 0.150952f,  -0.062500f,
	-1.124351f, 0.147036f,  -0.062500f, -1.235248f, 0.136407f,  -0.062500f, -1.316052f, 0.115709f,
	-0.062500f, -1.365477f, 0.081585f,  -0.062500f, -1.382239f, 0.030678f,  -0.062500f, -1.362563f,
	-0.033905f, 0.000000f,  -1.335942f, -0.110988f, 0.000000f,  -1.289877f, -0.194322f, 0.000000f,
	-1.222979f, -0.277655f, 0.000000f,  -1.133859f, -0.354739f, 0.000000f,  -1.021127f, -0.419322f,
	0.000000f,  -1.373219f, -0.037332f, 0.062500f,  -1.345270f, -0.116647f, 0.062500f,  -1.297053f,
	-0.201440f, 0.062500f,  -1.227232f, -0.285886f, 0.062500f,  -1.134467f, -0.364159f, 0.062500f,
	-1.017424f, -0.430433f, 0.062500f,  -1.399861f, -0.045900f, 0.100000f,  -1.368590f, -0.130793f,
	0.100000f,  -1.314993f, -0.219235f, 0.100000f,  -1.237862f, -0.306462f, 0.100000f,  -1.135989f,
	-0.387709f, 0.100000f,  -1.008164f, -0.458211f, 0.100000f,  -1.434495f, -0.057039f, 0.112500f,
	-1.398905f, -0.149183f, 0.112500f,  -1.338315f, -0.242369f, 0.112500f,  -1.251683f, -0.333211f,
	0.112500f,  -1.137967f, -0.418324f, 0.112500f,  -0.996127f, -0.494322f, 0.112500f,  -1.469130f,
	-0.068177f, 0.100000f,  -1.429221f, -0.167573f, 0.100000f,  -1.361637f, -0.265502f, 0.100000f,
	-1.265503f, -0.359960f, 0.100000f,  -1.139946f, -0.448939f, 0.100000f,  -0.984090f, -0.530433f,
	0.100000f,  -1.495772f, -0.076745f, 0.062500f,  -1.452540f, -0.181719f, 0.062500f,  -1.379576f,
	-0.283298f, 0.062500f,  -1.276134f, -0.380536f, 0.062500f,  -1.141468f, -0.472489f, 0.062500f,
	-0.974831f, -0.558211f, 0.062500f,  -1.506428f, -0.080173f, 0.000000f,  -1.461868f, -0.187377f,
	0.000000f,  -1.386752f, -0.290416f, 0.000000f,  -1.280387f, -0.388766f, 0.000000f,  -1.142076f,
	-0.481909f, 0.000000f,  -0.971127f, -0.569322f, 0.000000f,  -1.495772f, -0.076745f, -0.062500f,
	-1.452540f, -0.181719f, -0.062500f, -1.379576f, -0.283298f, -0.062500f, -1.276134f, -0.380536f,
	-0.062500f, -1.141468f, -0.472489f, -0.062500f, -0.974831f, -0.558211f, -0.062500f, -1.469130f,
	-0.068177f, -0.100000f, -1.429221f, -0.167573f, -0.100000f, -1.361637f, -0.265502f, -0.100000f,
	-1.265503f, -0.359960f, -0.100000f, -1.139946f, -0.448939f, -0.100000f, -0.984090f, -0.530433f,
	-0.100000f, -1.434495f, -0.057039f, -0.112500f, -1.398905f, -0.149183f, -0.112500f, -1.338315f,
	-0.242369f, -0.112500f, -1.251683f, -0.333211f, -0.112500f, -1.137967f, -0.418324f, -0.112500f,
	-0.996127f, -0.494322f, -0.112500f, -1.399861f, -0.045900f, -0.100000f, -1.368590f, -0.130793f,
	-0.100000f, -1.314993f, -0.219235f, -0.100000f, -1.237862f, -0.306462f, -0.100000f, -1.135989f,
	-0.387709f, -0.100000f, -1.008164f, -0.458211f, -0.100000f, -1.373219f, -0.037332f, -0.062500f,
	-1.345270f, -0.116647f, -0.062500f, -1.297053f, -0.201440f, -0.062500f, -1.227232f, -0.285886f,
	-0.062500f, -1.134467f, -0.364159f, -0.062500f, -1.017424f, -0.430433f, -0.062500f, 0.828873f,
	-0.156822f, 0.000000f,  1.008271f,  -0.131127f, 0.000000f,  1.114058f,  -0.063766f, 0.000000f,
	1.172623f,  0.030678f,  0.000000f,  1.210354f,  0.137623f,  0.000000f,  1.253641f,  0.242484f,
	0.000000f,  1.328873f,  0.330678f,  0.000000f,  0.828873f,  -0.187377f, 0.137500f,  1.015061f,
	-0.156719f, 0.131173f,  1.123935f,  -0.083314f, 0.115355f,  1.183734f,  0.017484f,  0.094792f,
	1.222700f,  0.130318f,  0.074228f,  1.269073f,  0.239835f,  0.058411f,  1.351095f,  0.330678f,
	0.052083f,  0.828873f,  -0.263766f, 0.220000f,  1.032036f,  -0.220698f, 0.209877f,  1.148626f,
	-0.132182f, 0.184568f,  1.211512f,  -0.015502f, 0.151667f,  1.253564f,  0.112057f,  0.118765f,
	1.307654f,  0.233212f,  0.093457f,  1.406651f,  0.330678f,  0.083333f,  0.828873f,  -0.363072f,
	0.247500f,  1.054104f,  -0.303870f, 0.236111f,  1.180725f,  -0.195711f, 0.207639f,  1.247623f,
	-0.058384f, 0.170625f,  1.293688f,  0.088317f,  0.133611f,  1.357808f,  0.224602f,  0.105139f,
	1.478873f,  0.330678f,  0.093750f,  0.828873f,  -0.462377f, 0.220000f,  1.076172f,  -0.387043f,
	0.209877f,  1.212823f,  -0.259240f, 0.184568f,  1.283734f,  -0.101266f, 0.151667f,  1.333811f,
	0.064577f,  0.118765f,  1.407962f,  0.215992f,  0.093457f,  1.551095f,  0.330678f,  0.083333f,
	0.828873f,  -0.538766f, 0.137500f,  1.093148f,  -0.451022f, 0.131173f,  1.237515f,  -0.308108f,
	0.115355f,  1.311512f,  -0.134252f, 0.094792f,  1.364675f,  0.046316f,  0.074228f,  1.446543f,
	0.209369f,  0.058410f,  1.606651f,  0.330678f,  0.052083f,  0.828873f,  -0.569322f, 0.000000f,
	1.099938f,  -0.476614f, 0.000000f,  1.247391f,  -0.327655f, 0.000000f,  1.322623f,  -0.147447f,
	0.000000f,  1.377021f,  0.039012f,  0.000000f,  1.461975f,  0.206720f,  0.000000f,  1.628873f,
	0.330678f,  0.000000f,  0.828873f,  -0.538766f, -0.137500f, 1.093148f,  -0.451022f, -0.131173f,
	1.237515f,  -0.308108f, -0.115355f, 1.311512f,  -0.134252f, -0.094792f, 1.364675f,  0.046316f,
	-0.074228f, 1.446543f,  0.209369f,  -0.058410f, 1.606651f,  0.330678f,  -0.052083f, 0.828873f,
	-0.462377f, -0.220000f, 1.076172f,  -0.387043f, -0.209877f, 1.212823f,  -0.259240f, -0.184568f,
	1.283734f,  -0.101266f, -0.151667f, 1.333811f,  0.064577f,  -0.118765f, 1.407962f,  0.215992f,
	-0.093457f, 1.551095f,  0.330678f,  -0.083333f, 0.828873f,  -0.363072f, -0.247500f, 1.054104f,
	-0.303870f, -0.236111f, 1.180725f,  -0.195711f, -0.207639f, 1.247623f,  -0.058384f, -0.170625f,
	1.293688f,  0.088317f,  -0.133611f, 1.357808f,  0.224602f,  -0.105139f, 1.478873f,  0.330678f,
	-0.093750f, 0.828873f,  -0.263766f, -0.220000f, 1.032036f,  -0.220698f, -0.209877f, 1.148626f,
	-0.132182f, -0.184568f, 1.211512f,  -0.015502f, -0.151667f, 1.253564f,  0.112057f,  -0.118765f,
	1.307654f,  0.233212f,  -0.093457f, 1.406651f,  0.330678f,  -0.083333f, 0.828873f,  -0.187377f,
	-0.137500f, 1.015061f,  -0.156719f, -0.131173f, 1.123935f,  -0.083314f, -0.115355f, 1.183734f,
	0.017484f,  -0.094792f, 1.222700f,  0.130318f,  -0.074228f, 1.269073f,  0.239835f,  -0.058410f,
	1.351095f,  0.330678f,  -0.052083f, 1.353410f,  0.346303f,  0.000000f,  1.375169f,  0.355678f,
	0.000000f,  1.391373f,  0.358803f,  0.000000f,  1.399243f,  0.355678f,  0.000000f,  1.396003f,
	0.346303f,  0.000000f,  1.378873f,  0.330678f,  0.000000f,  1.377077f,  0.346641f,  0.050540f,
	1.398763f,  0.356295f,  0.046682f,  1.413711f,  0.359584f,  0.041667f,  1.419477f,  0.356450f,
	0.036651f,  1.413617f,  0.346834f,  0.032793f,  1.393688f,  0.330678f,  0.031250f,  1.436244f,
	0.347485f,  0.080864f,  1.457748f,  0.357839f,  0.074691f,  1.469556f,  0.361538f,  0.066667f,
	1.470060f,  0.358379f,  0.058642f,  1.457652f,  0.348160f,  0.052469f,  1.430725f,  0.330678f,
	0.050000f,  1.513161f,  0.348582f,  0.090972f,  1.534428f,  0.359845f,  0.084028f,  1.542154f,
	0.364077f,  0.075000f,  1.535817f,  0.360886f,  0.065972f,  1.514897f,  0.349884f,  0.059028f,
	1.478873f,  0.330678f,  0.056250f,  1.590078f,  0.349679f,  0.080864f,  1.611109f,  0.361851f,
	0.074691f,  1.614753f,  0.366616f,  0.066667f,  1.601575f,  0.363394f,  0.058642f,  1.572143f,
	0.351608f,  0.052469f,  1.527021f,  0.330678f,  0.050000f,  1.649245f,  0.350523f,  0.050540f,
	1.670094f,  0.363394f,  0.046682f,  1.670597f,  0.368569f,  0.041667f,  1.652158f,  0.365323f,
	0.036651f,  1.616178f,  0.352934f,  0.032793f,  1.564058f,  0.330678f,  0.031250f,  1.672912f,
	0.350860f,  0.000000f,  1.693688f,  0.364011f,  0.000000f,  1.692935f,  0.369350f,  0.000000f,
	1.672391f,  0.366095f,  0.000000f,  1.633792f,  0.353465f,  0.000000f,  1.578873f,  0.330678f,
	0.000000f,  1.649245f,  0.350523f,  -0.050540f, 1.670094f,  0.363394f,  -0.046682f, 1.670597f,
	0.368569f,  -0.041667f, 1.652158f,  0.365323f,  -0.036651f, 1.616178f,  0.352934f,  -0.032793f,
	1.564058f,  0.330678f,  -0.031250f, 1.590078f,  0.349679f,  -0.080864f, 1.611109f,  0.361851f,
	-0.074691f, 1.614753f,  0.366616f,  -0.066667f, 1.601575f,  0.363394f,  -0.058642f, 1.572143f,
	0.351608f,  -0.052469f, 1.527021f,  0.330678f,  -0.050000f, 1.513161f,  0.348582f,  -0.090972f,
	1.534428f,  0.359845f,  -0.084028f, 1.542154f,  0.364077f,  -0.075000f, 1.535817f,  0.360886f,
	-0.065972f, 1.514897f,  0.349884f,  -0.059028f, 1.478873f,  0.330678f,  -0.056250f, 1.436244f,
	0.347485f,  -0.080864f, 1.457748f,  0.357839f,  -0.074691f, 1.469556f,  0.361538f,  -0.066667f,
	1.470060f,  0.358379f,  -0.058642f, 1.457652f,  0.348160f,  -0.052469f, 1.430725f,  0.330678f,
	-0.050000f, 1.377077f,  0.346641f,  -0.050540f, 1.398763f,  0.356295f,  -0.046682f, 1.413711f,
	0.359584f,  -0.041667f, 1.419477f,  0.356450f,  -0.036651f, 1.413617f,  0.346834f,  -0.032793f,
	1.393688f,  0.330678f,  -0.031250f, -0.021127f, 0.705678f,  0.000000f,  0.118225f,  0.694220f,
	0.000000f,  0.160354f,  0.664011f,  0.000000f,  0.141373f,  0.621303f,  0.000000f,  0.097391f,
	0.572345f,  0.000000f,  0.064521f,  0.523386f,  0.000000f,  0.078873f,  0.480678f,  0.000000f,
	0.113346f,  0.694220f,  0.037539f,  0.154000f,  0.664011f,  0.048885f,  0.135681f,  0.621303f,
	0.043764f,  0.093237f,  0.572345f,  0.031902f,  0.061512f,  0.523386f,  0.023022f,  0.075354f,
	0.480678f,  0.026852f,  0.099515f,  0.694220f,  0.070966f,  0.135987f,  0.664011f,  0.092417f,
	0.119549f,  0.621303f,  0.082741f,  0.081463f,  0.572345f,  0.060324f,  0.052990f,  0.523386f,
	0.043553f,  0.065391f,  0.480678f,  0.050815f,  0.077943f,  0.694220f,  0.099070f,  0.107891f,
	0.664011f,  0.129019f,  0.094388f,  0.621303f,  0.115516f,  0.063104f,  0.572345f,  0.084231f,
	0.039709f,  0.523386f,  0.060836f,  0.049873f,  0.480678f,  0.071000f,  0.049838f,  0.694220f,
	0.120642f,  0.071290f,  0.664011f,  0.157114f,  0.061614f,  0.621303f,  0.140676f,  0.039197f,
	0.572345f,  0.102590f,  0.022426f,  0.523386f,  0.074117f,  0.029688f,  0.480678f,  0.086519f,
	0.016412f,  0.694220f,  0.134473f,  0.027758f,  0.664011f,  0.175127f,  0.022637f,  0.621303f,
	0.156808f,  0.010774f,  0.572345f,  0.114364f,  0.001895f,  0.523386f,  0.082639f,  0.005725f,
	0.480678f,  0.096482f,  -0.021127f, 0.694220f,  0.139352f,  -0.021127f, 0.664011f,  0.181482f,
	-0.021127f, 0.621303f,  0.162500f,  -0.021127f, 0.572345f,  0.118519f,  -0.021127f, 0.523386f,
	0.085648f,  -0.021127f, 0.480678f,  0.100000f,  -0.058666f, 0.694220f,  0.134473f,  -0.070013f,
	0.664011f,  0.175127f,  -0.064892f, 0.621303f,  0.156808f,  -0.053029f, 0.572345f,  0.114364f,
	-0.044149f, 0.523386f,  0.082639f,  -0.047979f, 0.480678f,  0.096481f,  -0.092093f, 0.694220f,
	0.120642f,  -0.113544f, 0.664011f,  0.157114f,  -0.103868f, 0.621303f,  0.140676f,  -0.081451f,
	0.572345f,  0.102590f,  -0.064680f, 0.523386f,  0.074117f,  -0.071942f, 0.480678f,  0.086519f,
	-0.120197f, 0.694220f,  0.099070f,  -0.150146f, 0.664011f,  0.129019f,  -0.136643f, 0.621303f,
	0.115516f,  -0.105359f, 0.572345f,  0.084231f,  -0.081963f, 0.523386f,  0.060836f,  -0.092127f,
	0.480678f,  0.071000f,  -0.141770f, 0.694220f,  0.070966f,  -0.178241f, 0.664011f,  0.092417f,
	-0.161803f, 0.621303f,  0.082741f,  -0.123717f, 0.572345f,  0.060324f,  -0.095244f, 0.523386f,
	0.043553f,  -0.107646f, 0.480678f,  0.050815f,  -0.155600f, 0.694220f,  0.037539f,  -0.196254f,
	0.664011f,  0.048885f,  -0.177936f, 0.621303f,  0.043764f,  -0.135491f, 0.572345f,  0.031902f,
	-0.103767f, 0.523386f,  0.023022f,  -0.117609f, 0.480678f,  0.026852f,  -0.160479f, 0.694220f,
	0.000000f,  -0.202609f, 0.664011f,  0.000000f,  -0.183627f, 0.621303f,  0.000000f,  -0.139646f,
	0.572345f,  0.000000f,  -0.106775f, 0.523386f,  0.000000f,  -0.121127f, 0.480678f,  0.000000f,
	-0.155600f, 0.694220f,  -0.037539f, -0.196254f, 0.664011f,  -0.048885f, -0.177936f, 0.621303f,
	-0.043764f, -0.135491f, 0.572345f,  -0.031902f, -0.103767f, 0.523386f,  -0.023022f, -0.117609f,
	0.480678f,  -0.026852f, -0.141770f, 0.694220f,  -0.070966f, -0.178241f, 0.664011f,  -0.092417f,
	-0.161803f, 0.621303f,  -0.082741f, -0.123717f, 0.572345f,  -0.060324f, -0.095244f, 0.523386f,
	-0.043553f, -0.107646f, 0.480678f,  -0.050815f, -0.120197f, 0.694220f,  -0.099070f, -0.150146f,
	0.664011f,  -0.129019f, -0.136643f, 0.621303f,  -0.115516f, -0.105359f, 0.572345f,  -0.084231f,
	-0.081963f, 0.523386f,  -0.060836f, -0.092127f, 0.480678f,  -0.071000f, -0.092093f, 0.694220f,
	-0.120642f, -0.113544f, 0.664011f,  -0.157114f, -0.103868f, 0.621303f,  -0.140676f, -0.081451f,
	0.572345f,  -0.102590f, -0.064680f, 0.523386f,  -0.074117f, -0.071942f, 0.480678f,  -0.086519f,
	-0.058666f, 0.694220f,  -0.134473f, -0.070013f, 0.664011f,  -0.175127f, -0.064892f, 0.621303f,
	-0.156808f, -0.053029f, 0.572345f,  -0.114364f, -0.044149f, 0.523386f,  -0.082639f, -0.047979f,
	0.480678f,  -0.096482f, -0.021127f, 0.694220f,  -0.139352f, -0.021127f, 0.664011f,  -0.181482f,
	-0.021127f, 0.621303f,  -0.162500f, -0.021127f, 0.572345f,  -0.118519f, -0.021127f, 0.523386f,
	-0.085648f, -0.021127f, 0.480678f,  -0.100000f, 0.016412f,  0.694220f,  -0.134473f, 0.027758f,
	0.664011f,  -0.175127f, 0.022637f,  0.621303f,  -0.156808f, 0.010774f,  0.572345f,  -0.114364f,
	0.001895f,  0.523386f,  -0.082639f, 0.005725f,  0.480678f,  -0.096481f, 0.049838f,  0.694220f,
	-0.120642f, 0.071290f,  0.664011f,  -0.157114f, 0.061614f,  0.621303f,  -0.140676f, 0.039197f,
	0.572345f,  -0.102590f, 0.022426f,  0.523386f,  -0.074117f, 0.029688f,  0.480678f,  -0.086519f,
	0.077943f,  0.694220f,  -0.099070f, 0.107891f,  0.664011f,  -0.129019f, 0.094388f,  0.621303f,
	-0.115516f, 0.063104f,  0.572345f,  -0.084231f, 0.039709f,  0.523386f,  -0.060836f, 0.049873f,
	0.480678f,  -0.071000f, 0.099515f,  0.694220f,  -0.070966f, 0.135987f,  0.664011f,  -0.092417f,
	0.119549f,  0.621303f,  -0.082741f, 0.081463f,  0.572345f,  -0.060324f, 0.052990f,  0.523386f,
	-0.043553f, 0.065391f,  0.480678f,  -0.050815f, 0.113346f,  0.694220f,  -0.037539f, 0.154000f,
	0.664011f,  -0.048885f, 0.135681f,  0.621303f,  -0.043764f, 0.093237f,  0.572345f,  -0.031902f,
	0.061512f,  0.523386f,  -0.023022f, 0.075354f,  0.480678f,  -0.026852f, 0.154336f,  0.448734f,
	0.000000f,  0.265910f,  0.425123f,  0.000000f,  0.391373f,  0.405678f,  0.000000f,  0.508502f,
	0.386234f,  0.000000f,  0.595077f,  0.362623f,  0.000000f,  0.628873f,  0.330678f,  0.000000f,
	0.148162f,  0.448734f,  0.047115f,  0.255810f,  0.425123f,  0.077075f,  0.376859f,  0.405678f,
	0.110764f,  0.489867f,  0.386234f,  0.142215f,  0.573395f,  0.362623f,  0.165462f,  0.606002f,
	0.330678f,  0.174537f,  0.130681f,  0.448734f,  0.089161f,  0.227213f,  0.425123f,  0.145857f,
	0.335762f,  0.405678f,  0.209611f,  0.437101f,  0.386234f,  0.269130f,  0.512003f,  0.362623f,
	0.313123f,  0.541243f,  0.330678f,  0.330296f,  0.103451f,  0.448734f,  0.124579f,  0.182669f,
	0.425123f,  0.203796f,  0.271748f,  0.405678f,  0.292875f,  0.354910f,  0.386234f,  0.376037f,
	0.416377f,  0.362623f,  0.437505f,  0.440373f,  0.330678f,  0.461500f,  0.068034f,  0.448734f,
	0.151808f,  0.124730f,  0.425123f,  0.248340f,  0.188484f,  0.405678f,  0.356889f,  0.248003f,
	0.386234f,  0.458228f,  0.291995f,  0.362623f,  0.533130f,  0.309169f,  0.330678f,  0.562370f,
	0.025988f,  0.448734f,  0.169289f,  0.055948f,  0.425123f,  0.276938f,  0.089637f,  0.405678f,
	0.397986f,  0.121088f,  0.386234f,  0.510995f,  0.144335f,  0.362623f,  0.594523f,  0.153410f,
	0.330678f,  0.627130f,  -0.021127f, 0.448734f,  0.175463f,  -0.021127f, 0.425123f,  0.287037f,
	-0.021127f, 0.405678f,  0.412500f,  -0.021127f, 0.386234f,  0.529630f,  -0.021127f, 0.362623f,
	0.616204f,  -0.021127f, 0.330678f,  0.650000f,  -0.068242f, 0.448734f,  0.169289f,  -0.098202f,
	0.425123f,  0.276938f,  -0.131891f, 0.405678f,  0.397986f,  -0.163343f, 0.386234f,  0.510995f,
	-0.186589f, 0.362623f,  0.594523f,  -0.195664f, 0.330678f,  0.627130f,  -0.110288f, 0.448734f,
	0.151808f,  -0.166985f, 0.425123f,  0.248340f,  -0.230738f, 0.405678f,  0.356889f,  -0.290258f,
	0.386234f,  0.458228f,  -0.334250f, 0.362623f,  0.533130f,  -0.351424f, 0.330678f,  0.562370f,
	-0.145706f, 0.448734f,  0.124579f,  -0.224924f, 0.425123f,  0.203796f,  -0.314002f, 0.405678f,
	0.292875f,  -0.397164f, 0.386234f,  0.376037f,  -0.458632f, 0.362623f,  0.437505f,  -0.482627f,
	0.330678f,  0.461500f,  -0.172935f, 0.448734f,  0.089161f,  -0.269467f, 0.425123f,  0.145857f,
	-0.378016f, 0.405678f,  0.209611f,  -0.479355f, 0.386234f,  0.269130f,  -0.554258f, 0.362623f,
	0.313123f,  -0.583498f, 0.330678f,  0.330296f,  -0.190416f, 0.448734f,  0.047115f,  -0.298065f,
	0.425123f,  0.077075f,  -0.419113f, 0.405678f,  0.110764f,  -0.532122f, 0.386234f,  0.142215f,
	-0.615650f, 0.362623f,  0.165462f,  -0.648257f, 0.330678f,  0.174537f,  -0.196590f, 0.448734f,
	0.000000f,  -0.308164f, 0.425123f,  0.000000f,  -0.433627f, 0.405678f,  0.000000f,  -0.550757f,
	0.386234f,  0.000000f,  -0.637331f, 0.362623f,  0.000000f,  -0.671127f, 0.330678f,  0.000000f,
	-0.190416f, 0.448734f,  -0.047115f, -0.298065f, 0.425123f,  -0.077075f, -0.419113f, 0.405678f,
	-0.110764f, -0.532122f, 0.386234f,  -0.142215f, -0.615650f, 0.362623f,  -0.165462f, -0.648257f,
	0.330678f,  -0.174537f, -0.172935f, 0.448734f,  -0.089161f, -0.269467f, 0.425123f,  -0.145857f,
	-0.378016f, 0.405678f,  -0.209611f, -0.479355f, 0.386234f,  -0.269130f, -0.554258f, 0.362623f,
	-0.313123f, -0.583498f, 0.330678f,  -0.330296f, -0.145706f, 0.448734f,  -0.124579f, -0.224924f,
	0.425123f,  -0.203796f, -0.314002f, 0.405678f,  -0.292875f, -0.397164f, 0.386234f,  -0.376037f,
	-0.458632f, 0.362623f,  -0.437505f, -0.482627f, 0.330678f,  -0.461500f, -0.110288f, 0.448734f,
	-0.151808f, -0.166985f, 0.425123f,  -0.248340f, -0.230738f, 0.405678f,  -0.356889f, -0.290258f,
	0.386234f,  -0.458228f, -0.334250f, 0.362623f,  -0.533130f, -0.351424f, 0.330678f,  -0.562370f,
	-0.068242f, 0.448734f,  -0.169289f, -0.098202f, 0.425123f,  -0.276938f, -0.131891f, 0.405678f,
	-0.397986f, -0.163343f, 0.386234f,  -0.510995f, -0.186589f, 0.362623f,  -0.594523f, -0.195664f,
	0.330678f,  -0.627130f, -0.021127f, 0.448734f,  -0.175463f, -0.021127f, 0.425123f,  -0.287037f,
	-0.021127f, 0.405678f,  -0.412500f, -0.021127f, 0.386234f,  -0.529630f, -0.021127f, 0.362623f,
	-0.616204f, -0.021127f, 0.330678f,  -0.650000f, 0.025988f,  0.448734f,  -0.169289f, 0.055948f,
	0.425123f,  -0.276938f, 0.089637f,  0.405678f,  -0.397986f, 0.121088f,  0.386234f,  -0.510995f,
	0.144335f,  0.362623f,  -0.594523f, 0.153410f,  0.330678f,  -0.627130f, 0.068034f,  0.448734f,
	-0.151808f, 0.124730f,  0.425123f,  -0.248340f, 0.188484f,  0.405678f,  -0.356889f, 0.248003f,
	0.386234f,  -0.458228f, 0.291996f,  0.362623f,  -0.533130f, 0.309169f,  0.330678f,  -0.562370f,
	0.103451f,  0.448734f,  -0.124579f, 0.182669f,  0.425123f,  -0.203796f, 0.271748f,  0.405678f,
	-0.292875f, 0.354910f,  0.386234f,  -0.376037f, 0.416377f,  0.362623f,  -0.437505f, 0.440373f,
	0.330678f,  -0.461500f, 0.130681f,  0.448734f,  -0.089161f, 0.227213f,  0.425123f,  -0.145857f,
	0.335762f,  0.405678f,  -0.209611f, 0.437101f,  0.386234f,  -0.269130f, 0.512003f,  0.362623f,
	-0.313123f, 0.541243f,  0.330678f,  -0.330296f, 0.148162f,  0.448734f,  -0.047115f, 0.255810f,
	0.425123f,  -0.077075f, 0.376859f,  0.405678f,  -0.110764f, 0.489867f,  0.386234f,  -0.142215f,
	0.573395f,  0.362623f,  -0.165462f, 0.606002f,  0.330678f,  -0.174537f,
};

static float teapotNormalsfloats[NUMTEAPOTVERTICES * 3] = {
	-0.945751f, -0.322256f, -0.041309f, -0.992771f, -0.120019f, -0.001089f, -0.842751f, 0.538169f,
	0.012052f,  -0.083588f, 0.996288f,  0.020560f,  0.532170f,  0.846603f,  0.007614f,  0.779300f,
	0.626641f,  0.003491f,  0.879896f,  0.475165f,  0.001103f,  -0.902413f, -0.322783f, -0.285416f,
	-0.958558f, -0.120097f, -0.258348f, -0.816875f, 0.538579f,  -0.206514f, -0.086190f, 0.996277f,
	-0.001604f, 0.511484f,  0.846942f,  0.145167f,  0.751363f,  0.627164f,  0.205227f,  0.849281f,
	0.475682f,  0.229015f,  -0.797449f, -0.323303f, -0.509461f, -0.858625f, -0.120328f, -0.498282f,
	-0.735017f, 0.538957f,  -0.411431f, -0.082580f, 0.996294f,  -0.024043f, 0.455735f,  0.847352f,
	0.272581f,  0.671856f,  0.627868f,  0.392927f,  0.760399f,  0.476384f,  0.441420f,  -0.639341f,
	-0.323439f, -0.697589f, -0.701183f, -0.120461f, -0.702731f, -0.604040f, 0.539064f,  -0.586980f,
	-0.073399f, 0.996309f,  -0.044511f, 0.369925f,  0.847499f,  0.380659f,  0.547722f,  0.628143f,
	0.552663f,  0.620826f,  0.476660f,  0.622391f,  -0.437782f, -0.323142f, -0.839003f, -0.496373f,
	-0.120437f, -0.859715f, -0.432443f, 0.538876f,  -0.722914f, -0.059523f, 0.996312f,  -0.061801f,
	0.259388f,  0.847326f,  0.463418f,  0.386844f,  0.627880f,  0.675366f,  0.439492f,  0.476398f,
	0.761506f,  -0.204681f, -0.322547f, -0.924159f, -0.256209f, -0.120257f, -0.959112f, -0.230122f,
	0.538458f,  -0.810621f, -0.041668f, 0.996304f,  -0.075119f, 0.130300f,  0.846904f,  0.515534f,
	0.198391f,  0.627182f,  0.753183f,  0.226852f,  0.475703f,  0.849850f,  0.035941f,  -0.330214f,
	-0.943221f, -0.001376f, -0.125569f, -0.992084f, -0.012701f, 0.535792f,  -0.844254f, -0.020672f,
	0.996343f,  -0.082901f, -0.007571f, 0.846427f,  0.532451f,  -0.003482f, 0.626608f,  0.779327f,
	-0.001103f, 0.475165f,  0.879896f,  0.269574f,  -0.386954f, -0.881814f, 0.249993f,  -0.181783f,
	-0.951030f, 0.211872f,  0.499984f,  -0.839718f, 0.002768f,  0.995768f,  -0.091859f, -0.146446f,
	0.844150f,  0.515718f,  -0.205497f, 0.625909f,  0.752335f,  -0.229034f, 0.475536f,  0.849358f,
	0.482854f,  -0.445924f, -0.753661f, 0.483883f,  -0.261599f, -0.835118f, 0.442338f,  0.434016f,
	-0.784836f, 0.036680f,  0.993502f,  -0.107746f, -0.278510f, 0.839949f,  0.465746f,  -0.394390f,
	0.624142f,  0.674465f,  -0.441541f, 0.475913f,  0.760624f,  0.669165f,  -0.453044f, -0.589041f,
	0.686401f,  -0.287530f, -0.667967f, 0.643212f,  0.404496f,  -0.650124f, 0.074604f,  0.991460f,
	-0.106959f, -0.391289f, 0.837987f,  0.380356f,  -0.555484f, 0.623132f,  0.550586f,  -0.622636f,
	0.476008f,  0.621080f,  0.821788f,  -0.407716f, -0.398036f, 0.849894f,  -0.244430f, -0.466834f,
	0.778095f,  0.435804f,  -0.452374f, 0.095458f,  0.992115f,  -0.081218f, -0.473659f, 0.839871f,
	0.265074f,  -0.678265f, 0.623724f,  0.388490f,  -0.761768f, 0.475842f,  0.439641f,  0.919150f,
	-0.348512f, -0.183583f, 0.956218f,  -0.171139f, -0.237398f, 0.838823f,  0.493898f,  -0.229000f,
	0.094322f,  0.994404f,  -0.047578f, -0.520640f, 0.843596f,  0.131452f,  -0.754753f, 0.625180f,
	0.198741f,  -0.849997f, 0.475426f,  0.226882f,  0.945537f,  -0.322183f, 0.046446f,  0.991881f,
	-0.126966f, 0.007216f,  0.847572f,  0.530605f,  -0.008996f, 0.087879f,  0.995918f,  -0.020615f,
	-0.533063f, 0.846041f,  -0.007711f, -0.779612f, 0.626253f,  -0.003532f, -0.879926f, 0.475109f,
	-0.001109f, 0.902413f,  -0.322783f, 0.285416f,  0.958558f,  -0.120097f, 0.258348f,  0.816875f,
	0.538579f,  0.206514f,  0.086190f,  0.996277f,  0.001604f,  -0.511484f, 0.846942f,  -0.145167f,
	-0.751363f, 0.627164f,  -0.205227f, -0.849281f, 0.475682f,  -0.229015f, 0.797449f,  -0.323303f,
	0.509461f,  0.858625f,  -0.120328f, 0.498282f,  0.735017f,  0.538957f,  0.411431f,  0.082580f,
	0.996294f,  0.024043f,  -0.455735f, 0.847352f,  -0.272581f, -0.671856f, 0.627868f,  -0.392927f,
	-0.760399f, 0.476384f,  -0.441420f, 0.639341f,  -0.323439f, 0.697589f,  0.701183f,  -0.120461f,
	0.702731f,  0.604040f,  0.539064f,  0.586980f,  0.073399f,  0.996309f,  0.044511f,  -0.369925f,
	0.847499f,  -0.380659f, -0.547722f, 0.628143f,  -0.552663f, -0.620826f, 0.476660f,  -0.622391f,
	0.437782f,  -0.323142f, 0.839003f,  0.496373f,  -0.120437f, 0.859715f,  0.432443f,  0.538876f,
	0.722914f,  0.059523f,  0.996312f,  0.061801f,  -0.259388f, 0.847326f,  -0.463418f, -0.386844f,
	0.627880f,  -0.675366f, -0.439492f, 0.476398f,  -0.761506f, 0.204681f,  -0.322547f, 0.924159f,
	0.256209f,  -0.120257f, 0.959112f,  0.230122f,  0.538458f,  0.810621f,  0.041668f,  0.996304f,
	0.075119f,  -0.130300f, 0.846904f,  -0.515534f, -0.198391f, 0.627182f,  -0.753183f, -0.226852f,
	0.475703f,  -0.849850f, -0.041309f, -0.322256f, 0.945751f,  -0.001089f, -0.120019f, 0.992771f,
	0.012052f,  0.538169f,  0.842751f,  0.020560f,  0.996288f,  0.083588f,  0.007614f,  0.846603f,
	-0.532170f, 0.003491f,  0.626641f,  -0.779300f, 0.001103f,  0.475165f,  -0.879896f, -0.285416f,
	-0.322783f, 0.902413f,  -0.258348f, -0.120097f, 0.958558f,  -0.206514f, 0.538579f,  0.816875f,
	-0.001604f, 0.996277f,  0.086190f,  0.145167f,  0.846942f,  -0.511484f, 0.205227f,  0.627164f,
	-0.751363f, 0.229015f,  0.475682f,  -0.849281f, -0.509461f, -0.323303f, 0.797449f,  -0.498282f,
	-0.120328f, 0.858625f,  -0.411431f, 0.538957f,  0.735017f,  -0.024043f, 0.996294f,  0.082580f,
	0.272581f,  0.847352f,  -0.455735f, 0.392927f,  0.627868f,  -0.671856f, 0.441420f,  0.476384f,
	-0.760399f, -0.697589f, -0.323439f, 0.639341f,  -0.702731f, -0.120461f, 0.701183f,  -0.586980f,
	0.539064f,  0.604040f,  -0.044511f, 0.996309f,  0.073399f,  0.380659f,  0.847499f,  -0.369925f,
	0.552663f,  0.628143f,  -0.547722f, 0.622391f,  0.476660f,  -0.620826f, -0.839003f, -0.323142f,
	0.437782f,  -0.859715f, -0.120437f, 0.496373f,  -0.722914f, 0.538876f,  0.432443f,  -0.061801f,
	0.996312f,  0.059523f,  0.463418f,  0.847326f,  -0.259388f, 0.675366f,  0.627880f,  -0.386844f,
	0.761506f,  0.476398f,  -0.439492f, -0.924159f, -0.322547f, 0.204681f,  -0.959112f, -0.120257f,
	0.256209f,  -0.810621f, 0.538458f,  0.230122f,  -0.075119f, 0.996304f,  0.041668f,  0.515534f,
	0.846904f,  -0.130300f, 0.753183f,  0.627182f,  -0.198391f, 0.849850f,  0.475703f,  -0.226852f,
	0.908180f,  0.418579f,  0.000170f,  0.920061f,  0.391776f,  0.000335f,  0.939254f,  0.343222f,
	0.000478f,  0.963807f,  0.266599f,  0.000552f,  0.988261f,  0.152772f,  0.000449f,  0.998933f,
	-0.046187f, -0.000262f, 0.876892f,  0.419073f,  0.235451f,  0.888349f,  0.392247f,  0.238702f,
	0.906891f,  0.343648f,  0.243832f,  0.930644f,  0.266938f,  0.250291f,  0.954351f,  0.152959f,
	0.256551f,  0.964867f,  -0.046304f, 0.258627f,  0.785456f,  0.419734f,  0.454843f,  0.795707f,
	0.392883f,  0.460971f,  0.812334f,  0.344228f,  0.470766f,  0.833667f,  0.267414f,  0.483207f,
	0.855012f,  0.153250f,  0.495448f,  0.864663f,  -0.046372f, 0.500207f,  0.641599f,  0.419990f,
	0.641841f,  0.649935f,  0.393130f,  0.650410f,  0.663494f,  0.344457f,  0.664173f,  0.680925f,
	0.267607f,  0.681710f,  0.698421f,  0.153377f,  0.699059f,  0.706532f,  -0.046369f, 0.706160f,
	0.454545f,  0.419737f,  0.785627f,  0.460384f,  0.392890f,  0.796043f,  0.469929f,  0.344241f,
	0.812813f,  0.482239f,  0.267436f,  0.834220f,  0.494660f,  0.153286f,  0.855462f,  0.500666f,
	-0.046300f, 0.864402f,  0.235117f,  0.419078f,  0.876980f,  0.238044f,  0.392258f,  0.888521f,
	0.242894f,  0.343667f,  0.907136f,  0.249206f,  0.266970f,  0.930926f,  0.255668f,  0.153012f,
	0.954579f,  0.259142f,  -0.046198f, 0.964734f,  -0.000170f, 0.418579f,  0.908181f,  -0.000335f,
	0.391776f,  0.920061f,  -0.000478f, 0.343222f,  0.939254f,  -0.000552f, 0.266599f,  0.963807f,
	-0.000449f, 0.152772f,  0.988261f,  0.000262f,  -0.046187f, 0.998933f,  -0.235451f, 0.419073f,
	0.876892f,  -0.238702f, 0.392247f,  0.888349f,  -0.243832f, 0.343648f,  0.906891f,  -0.250291f,
	0.266938f,  0.930644f,  -0.256551f, 0.152959f,  0.954351f,  -0.258627f, -0.046304f, 0.964867f,
	-0.454843f, 0.419734f,  0.785456f,  -0.460971f, 0.392883f,  0.795707f,  -0.470766f, 0.344228f,
	0.812334f,  -0.483207f, 0.267414f,  0.833667f,  -0.495448f, 0.153250f,  0.855012f,  -0.500207f,
	-0.046372f, 0.864663f,  -0.641841f, 0.419990f,  0.641599f,  -0.650410f, 0.393130f,  0.649935f,
	-0.664173f, 0.344457f,  0.663494f,  -0.681710f, 0.267607f,  0.680925f,  -0.699059f, 0.153377f,
	0.698421f,  -0.706160f, -0.046369f, 0.706532f,  -0.785627f, 0.419737f,  0.454545f,  -0.796043f,
	0.392890f,  0.460384f,  -0.812813f, 0.344241f,  0.469929f,  -0.834220f, 0.267436f,  0.482239f,
	-0.855462f, 0.153286f,  0.494660f,  -0.864402f, -0.046300f, 0.500666f,  -0.876980f, 0.419078f,
	0.235117f,  -0.888521f, 0.392258f,  0.238044f,  -0.907136f, 0.343667f,  0.242894f,  -0.930926f,
	0.266970f,  0.249206f,  -0.954579f, 0.153012f,  0.255668f,  -0.964734f, -0.046198f, 0.259142f,
	-0.908181f, 0.418579f,  -0.000170f, -0.920061f, 0.391776f,  -0.000335f, -0.939254f, 0.343222f,
	-0.000478f, -0.963807f, 0.266599f,  -0.000552f, -0.988261f, 0.152772f,  -0.000449f, -0.998933f,
	-0.046187f, 0.000262f,  -0.876892f, 0.419073f,  -0.235451f, -0.888349f, 0.392247f,  -0.238702f,
	-0.906891f, 0.343648f,  -0.243832f, -0.930644f, 0.266938f,  -0.250291f, -0.954351f, 0.152959f,
	-0.256551f, -0.964867f, -0.046304f, -0.258627f, -0.785456f, 0.419734f,  -0.454843f, -0.795707f,
	0.392883f,  -0.460971f, -0.812334f, 0.344228f,  -0.470766f, -0.833667f, 0.267414f,  -0.483207f,
	-0.855012f, 0.153250f,  -0.495448f, -0.864663f, -0.046372f, -0.500207f, -0.641599f, 0.419990f,
	-0.641841f, -0.649935f, 0.393130f,  -0.650410f, -0.663494f, 0.344457f,  -0.664173f, -0.680925f,
	0.267607f,  -0.681710f, -0.698421f, 0.153377f,  -0.699059f, -0.706532f, -0.046369f, -0.706160f,
	-0.454545f, 0.419737f,  -0.785627f, -0.460384f, 0.392890f,  -0.796043f, -0.469929f, 0.344241f,
	-0.812813f, -0.482239f, 0.267436f,  -0.834220f, -0.494660f, 0.153286f,  -0.855462f, -0.500666f,
	-0.046300f, -0.864402f, -0.235117f, 0.419078f,  -0.876980f, -0.238044f, 0.392258f,  -0.888521f,
	-0.242894f, 0.343667f,  -0.907136f, -0.249206f, 0.266970f,  -0.930926f, -0.255668f, 0.153012f,
	-0.954579f, -0.259142f, -0.046198f, -0.964734f, 0.000170f,  0.418579f,  -0.908181f, 0.000335f,
	0.391776f,  -0.920061f, 0.000478f,  0.343222f,  -0.939254f, 0.000552f,  0.266599f,  -0.963807f,
	0.000449f,  0.152772f,  -0.988261f, -0.000262f, -0.046187f, -0.998933f, 0.235451f,  0.419073f,
	-0.876892f, 0.238702f,  0.392247f,  -0.888349f, 0.243832f,  0.343648f,  -0.906891f, 0.250291f,
	0.266938f,  -0.930644f, 0.256551f,  0.152959f,  -0.954351f, 0.258627f,  -0.046304f, -0.964867f,
	0.454843f,  0.419734f,  -0.785456f, 0.460971f,  0.392883f,  -0.795707f, 0.470766f,  0.344228f,
	-0.812334f, 0.483207f,  0.267414f,  -0.833667f, 0.495448f,  0.153250f,  -0.855012f, 0.500207f,
	-0.046372f, -0.864663f, 0.641841f,  0.419990f,  -0.641599f, 0.650410f,  0.393130f,  -0.649935f,
	0.664173f,  0.344457f,  -0.663494f, 0.681710f,  0.267607f,  -0.680925f, 0.699059f,  0.153377f,
	-0.698421f, 0.706160f,  -0.046369f, -0.706532f, 0.785627f,  0.419737f,  -0.454545f, 0.796043f,
	0.392890f,  -0.460384f, 0.812813f,  0.344241f,  -0.469929f, 0.834220f,  0.267436f,  -0.482239f,
	0.855462f,  0.153286f,  -0.494660f, 0.864402f,  -0.046300f, -0.500666f, 0.876980f,  0.419078f,
	-0.235117f, 0.888521f,  0.392258f,  -0.238044f, 0.907136f,  0.343667f,  -0.242894f, 0.930926f,
	0.266970f,  -0.249206f, 0.954579f,  0.153012f,  -0.255668f, 0.964734f,  -0.046198f, -0.259142f,
	0.943833f,  -0.330414f, -0.002283f, 0.821403f,  -0.570341f, -0.002745f, 0.709541f,  -0.704661f,
	-0.001958f, 0.652305f,  -0.757957f, -0.000466f, 0.728669f,  -0.684856f, 0.003576f,  0.889124f,
	-0.457656f, 0.003164f,  0.912037f,  -0.330868f, 0.242313f,  0.793697f,  -0.570897f, 0.210051f,
	0.685340f,  -0.705168f, 0.181787f,  0.629635f,  -0.758420f, 0.168401f,  0.702387f,  -0.685364f,
	0.192168f,  0.857690f,  -0.458122f, 0.233435f,  0.817716f,  -0.331385f, 0.470664f,  0.711528f,
	-0.571608f, 0.408646f,  0.614071f,  -0.705839f, 0.353140f,  0.563713f,  -0.759034f, 0.325721f,
	0.627891f,  -0.686037f, 0.367569f,  0.767411f,  -0.458787f, 0.447879f,  0.668728f,  -0.331557f,
	0.665486f,  0.582010f,  -0.571874f, 0.578122f,  0.502096f,  -0.706097f, 0.499327f,  0.460496f,
	-0.759271f, 0.459838f,  0.511760f,  -0.686297f, 0.516816f,  0.625950f,  -0.459060f, 0.630437f,
	0.474660f,  -0.331321f, 0.815429f,  0.413434f,  -0.571590f, 0.708771f,  0.356547f,  -0.705839f,
	0.612100f,  0.326530f,  -0.759035f, 0.563244f,  0.361346f,  -0.686040f, 0.631489f,  0.442349f,
	-0.458832f, 0.770585f,  0.246794f,  -0.330773f, 0.910869f,  0.215429f,  -0.570870f, 0.792274f,
	0.185619f,  -0.705168f, 0.684313f,  0.169311f,  -0.758421f, 0.629390f,  0.185170f,  -0.685368f,
	0.704260f,  0.227231f,  -0.458188f, 0.859319f,  0.002283f,  -0.330414f, 0.943833f,  0.002745f,
	-0.570341f, 0.821403f,  0.001958f,  -0.704661f, 0.709541f,  0.000466f,  -0.757957f, 0.652305f,
	-0.003576f, -0.684856f, 0.728669f,  -0.003164f, -0.457656f, 0.889124f,  -0.242313f, -0.330868f,
	0.912037f,  -0.210051f, -0.570897f, 0.793697f,  -0.181787f, -0.705168f, 0.685340f,  -0.168401f,
	-0.758420f, 0.629635f,  -0.192168f, -0.685364f, 0.702387f,  -0.233435f, -0.458122f, 0.857690f,
	-0.470664f, -0.331385f, 0.817716f,  -0.408646f, -0.571608f, 0.711528f,  -0.353140f, -0.705839f,
	0.614071f,  -0.325721f, -0.759034f, 0.563713f,  -0.367569f, -0.686037f, 0.627891f,  -0.447879f,
	-0.458787f, 0.767411f,  -0.665486f, -0.331557f, 0.668728f,  -0.578122f, -0.571874f, 0.582010f,
	-0.499327f, -0.706097f, 0.502096f,  -0.459838f, -0.759271f, 0.460496f,  -0.516816f, -0.686297f,
	0.511760f,  -0.630437f, -0.459060f, 0.625950f,  -0.815429f, -0.331321f, 0.474660f,  -0.708771f,
	-0.571590f, 0.413434f,  -0.612100f, -0.705839f, 0.356547f,  -0.563244f, -0.759035f, 0.326530f,
	-0.631489f, -0.686040f, 0.361346f,  -0.770585f, -0.458832f, 0.442349f,  -0.910869f, -0.330773f,
	0.246794f,  -0.792274f, -0.570870f, 0.215429f,  -0.684313f, -0.705168f, 0.185619f,  -0.629390f,
	-0.758421f, 0.169311f,  -0.704260f, -0.685368f, 0.185170f,  -0.859319f, -0.458188f, 0.227231f,
	-0.943833f, -0.330414f, 0.002283f,  -0.821403f, -0.570341f, 0.002745f,  -0.709541f, -0.704661f,
	0.001958f,  -0.652305f, -0.757957f, 0.000466f,  -0.728669f, -0.684856f, -0.003576f, -0.889124f,
	-0.457656f, -0.003164f, -0.912037f, -0.330868f, -0.242313f, -0.793697f, -0.570897f, -0.210051f,
	-0.685340f, -0.705168f, -0.181787f, -0.629635f, -0.758420f, -0.168401f, -0.702387f, -0.685364f,
	-0.192168f, -0.857690f, -0.458122f, -0.233435f, -0.817716f, -0.331385f, -0.470664f, -0.711528f,
	-0.571608f, -0.408646f, -0.614071f, -0.705839f, -0.353140f, -0.563713f, -0.759034f, -0.325721f,
	-0.627891f, -0.686037f, -0.367569f, -0.767411f, -0.458787f, -0.447879f, -0.668728f, -0.331557f,
	-0.665486f, -0.582010f, -0.571874f, -0.578122f, -0.502096f, -0.706097f, -0.499327f, -0.460496f,
	-0.759271f, -0.459838f, -0.511760f, -0.686297f, -0.516816f, -0.625950f, -0.459060f, -0.630437f,
	-0.474660f, -0.331321f, -0.815429f, -0.413434f, -0.571590f, -0.708771f, -0.356547f, -0.705839f,
	-0.612100f, -0.326530f, -0.759035f, -0.563244f, -0.361346f, -0.686040f, -0.631489f, -0.442349f,
	-0.458832f, -0.770585f, -0.246794f, -0.330773f, -0.910869f, -0.215429f, -0.570870f, -0.792274f,
	-0.185619f, -0.705168f, -0.684313f, -0.169311f, -0.758421f, -0.629390f, -0.185170f, -0.685368f,
	-0.704260f, -0.227231f, -0.458188f, -0.859319f, -0.002283f, -0.330414f, -0.943833f, -0.002745f,
	-0.570341f, -0.821403f, -0.001958f, -0.704661f, -0.709541f, -0.000466f, -0.757957f, -0.652305f,
	0.003576f,  -0.684856f, -0.728669f, 0.003164f,  -0.457656f, -0.889124f, 0.242313f,  -0.330868f,
	-0.912037f, 0.210051f,  -0.570897f, -0.793697f, 0.181787f,  -0.705168f, -0.685340f, 0.168401f,
	-0.758420f, -0.629635f, 0.192168f,  -0.685364f, -0.702387f, 0.233435f,  -0.458122f, -0.857690f,
	0.470664f,  -0.331385f, -0.817716f, 0.408646f,  -0.571608f, -0.711528f, 0.353140f,  -0.705839f,
	-0.614071f, 0.325721f,  -0.759034f, -0.563713f, 0.367569f,  -0.686037f, -0.627891f, 0.447879f,
	-0.458787f, -0.767411f, 0.665486f,  -0.331557f, -0.668728f, 0.578122f,  -0.571874f, -0.582010f,
	0.499327f,  -0.706097f, -0.502096f, 0.459838f,  -0.759271f, -0.460496f, 0.516816f,  -0.686297f,
	-0.511760f, 0.630437f,  -0.459060f, -0.625950f, 0.815429f,  -0.331321f, -0.474660f, 0.708771f,
	-0.571590f, -0.413434f, 0.612100f,  -0.705839f, -0.356547f, 0.563244f,  -0.759035f, -0.326530f,
	0.631489f,  -0.686040f, -0.361346f, 0.770585f,  -0.458832f, -0.442349f, 0.910869f,  -0.330773f,
	-0.246794f, 0.792274f,  -0.570870f, -0.215429f, 0.684313f,  -0.705168f, -0.185619f, 0.629390f,
	-0.758421f, -0.169311f, 0.704260f,  -0.685368f, -0.185170f, 0.859319f,  -0.458188f, -0.227231f,
	0.777345f,  -0.628990f, -0.010332f, 0.361793f,  -0.932236f, -0.006477f, 0.152402f,  -0.988315f,
	-0.002559f, 0.066422f,  -0.997791f, -0.001190f, 0.027401f,  -0.999624f, -0.001027f, 0.000000f,
	-1.000000f, 0.000000f,  0.753154f,  -0.629440f, 0.191218f,  0.350766f,  -0.932386f, 0.087291f,
	0.147688f,  -0.988344f, 0.036926f,  0.064386f,  -0.997796f, 0.016021f,  0.026706f,  -0.999625f,
	0.006087f,  0.677297f,  -0.629962f, 0.380023f,  0.315543f,  -0.932612f, 0.175124f,  0.132774f,
	-0.988389f, 0.073881f,  0.057900f,  -0.997805f, 0.032133f,  0.024157f,  -0.999626f, 0.012794f,
	0.556310f,  -0.630147f, 0.541695f,  0.259523f,  -0.932707f, 0.250409f,  0.109137f,  -0.988408f,
	0.105540f,  0.047613f,  -0.997809f, 0.045941f,  0.020018f,  -0.999627f, 0.018575f,  0.398014f,
	-0.629932f, 0.666911f,  0.186318f,  -0.932635f, 0.308995f,  0.078296f,  -0.988394f, 0.130182f,
	0.034185f,  -0.997806f, 0.056696f,  0.014564f,  -0.999627f, 0.023117f,  0.211443f,  -0.629395f,
	0.747766f,  0.099921f,  -0.932420f, 0.347287f,  0.041912f,  -0.988352f, 0.146303f,  0.018338f,
	-0.997798f, 0.063741f,  0.008087f,  -0.999625f, 0.026150f,  0.010332f,  -0.628990f, 0.777345f,
	0.006477f,  -0.932236f, 0.361793f,  0.002559f,  -0.988315f, 0.152402f,  0.001190f,  -0.997791f,
	0.066422f,  0.001027f,  -0.999624f, 0.027401f,  -0.191218f, -0.629440f, 0.753154f,  -0.087291f,
	-0.932386f, 0.350766f,  -0.036926f, -0.988344f, 0.147688f,  -0.016021f, -0.997796f, 0.064386f,
	-0.006087f, -0.999625f, 0.026706f,  -0.380023f, -0.629962f, 0.677297f,  -0.175124f, -0.932612f,
	0.315543f,  -0.073881f, -0.988389f, 0.132774f,  -0.032133f, -0.997805f, 0.057900f,  -0.012794f,
	-0.999626f, 0.024157f,  -0.541695f, -0.630147f, 0.556310f,  -0.250409f, -0.932707f, 0.259523f,
	-0.105540f, -0.988408f, 0.109137f,  -0.045941f, -0.997809f, 0.047613f,  -0.018575f, -0.999627f,
	0.020018f,  -0.666911f, -0.629932f, 0.398014f,  -0.308995f, -0.932635f, 0.186318f,  -0.130182f,
	-0.988394f, 0.078296f,  -0.056696f, -0.997806f, 0.034185f,  -0.023117f, -0.999627f, 0.014564f,
	-0.747766f, -0.629395f, 0.211443f,  -0.347287f, -0.932420f, 0.099921f,  -0.146303f, -0.988352f,
	0.041912f,  -0.063741f, -0.997798f, 0.018338f,  -0.026150f, -0.999625f, 0.008087f,  -0.777345f,
	-0.628990f, 0.010332f,  -0.361793f, -0.932236f, 0.006477f,  -0.152402f, -0.988315f, 0.002559f,
	-0.066422f, -0.997791f, 0.001190f,  -0.027401f, -0.999624f, 0.001027f,  -0.753154f, -0.629440f,
	-0.191218f, -0.350766f, -0.932386f, -0.087291f, -0.147688f, -0.988344f, -0.036926f, -0.064386f,
	-0.997796f, -0.016021f, -0.026706f, -0.999625f, -0.006087f, -0.677297f, -0.629962f, -0.380023f,
	-0.315543f, -0.932612f, -0.175124f, -0.132774f, -0.988389f, -0.073881f, -0.057900f, -0.997805f,
	-0.032133f, -0.024157f, -0.999626f, -0.012794f, -0.556310f, -0.630147f, -0.541695f, -0.259523f,
	-0.932707f, -0.250409f, -0.109137f, -0.988408f, -0.105540f, -0.047613f, -0.997809f, -0.045941f,
	-0.020018f, -0.999627f, -0.018575f, -0.398014f, -0.629932f, -0.666911f, -0.186318f, -0.932635f,
	-0.308995f, -0.078296f, -0.988394f, -0.130182f, -0.034185f, -0.997806f, -0.056696f, -0.014564f,
	-0.999627f, -0.023117f, -0.211443f, -0.629395f, -0.747766f, -0.099921f, -0.932420f, -0.347287f,
	-0.041912f, -0.988352f, -0.146303f, -0.018338f, -0.997798f, -0.063741f, -0.008087f, -0.999625f,
	-0.026150f, -0.010332f, -0.628990f, -0.777345f, -0.006477f, -0.932236f, -0.361793f, -0.002559f,
	-0.988315f, -0.152402f, -0.001190f, -0.997791f, -0.066422f, -0.001027f, -0.999624f, -0.027401f,
	0.191218f,  -0.629440f, -0.753154f, 0.087291f,  -0.932386f, -0.350766f, 0.036926f,  -0.988344f,
	-0.147688f, 0.016021f,  -0.997796f, -0.064386f, 0.006087f,  -0.999625f, -0.026706f, 0.380023f,
	-0.629962f, -0.677297f, 0.175124f,  -0.932612f, -0.315543f, 0.073881f,  -0.988389f, -0.132774f,
	0.032133f,  -0.997805f, -0.057900f, 0.012794f,  -0.999626f, -0.024157f, 0.541695f,  -0.630147f,
	-0.556310f, 0.250409f,  -0.932707f, -0.259523f, 0.105540f,  -0.988408f, -0.109137f, 0.045941f,
	-0.997809f, -0.047613f, 0.018575f,  -0.999627f, -0.020018f, 0.666911f,  -0.629932f, -0.398014f,
	0.308995f,  -0.932635f, -0.186318f, 0.130182f,  -0.988394f, -0.078296f, 0.056696f,  -0.997806f,
	-0.034185f, 0.023117f,  -0.999627f, -0.014564f, 0.747766f,  -0.629395f, -0.211443f, 0.347287f,
	-0.932420f, -0.099921f, 0.146303f,  -0.988352f, -0.041912f, 0.063741f,  -0.997798f, -0.018338f,
	0.026150f,  -0.999625f, -0.008087f, 0.003252f,  -0.999017f, 0.044215f,  0.015240f,  -0.999884f,
	-0.000426f, 0.059928f,  -0.998202f, -0.000876f, 0.167134f,  -0.985934f, -0.001083f, 0.403838f,
	-0.914830f, -0.000203f, 0.792445f,  -0.609943f, 0.000242f,  0.995161f,  -0.098254f, -0.001013f,
	0.003195f,  -0.927908f, 0.372795f,  0.015041f,  -0.949764f, 0.312606f,  0.059227f,  -0.948266f,
	0.311904f,  0.164453f,  -0.933549f, 0.318499f,  0.388162f,  -0.854219f, 0.345890f,  0.729394f,
	-0.561905f, 0.390189f,  0.912351f,  -0.095332f, 0.398156f,  0.002232f,  -0.597680f, 0.801731f,
	0.010830f,  -0.681497f, 0.731741f,  0.043613f,  -0.679614f, 0.732272f,  0.120047f,  -0.660320f,
	0.741327f,  0.267930f,  -0.580441f, 0.768962f,  0.467285f,  -0.367107f, 0.804287f,  0.584006f,
	-0.067606f, 0.808929f,  -0.000653f, 0.152635f,  0.988282f,  -0.002559f, 0.000905f,  0.999996f,
	-0.007405f, 0.000384f,  0.999972f,  -0.016090f, -0.004746f, 0.999859f,  -0.025703f, -0.019620f,
	0.999477f,  -0.020936f, -0.035053f, 0.999166f,  -0.002824f, -0.023899f, 0.999710f,  -0.003296f,
	0.756255f,  0.654269f,  -0.015405f, 0.681251f,  0.731887f,  -0.059217f, 0.676283f,  0.734258f,
	-0.158438f, 0.643792f,  0.748619f,  -0.334170f, 0.526967f,  0.781432f,  -0.518177f, 0.278028f,
	0.808822f,  -0.588929f, 0.016391f,  0.808019f,  -0.004352f, 0.967350f,  0.253408f,  -0.020677f,
	0.949300f,  0.313691f,  -0.081844f, 0.945117f,  0.316317f,  -0.226175f, 0.916097f,  0.331076f,
	-0.500500f, 0.784289f,  0.366594f,  -0.804374f, 0.439635f,  0.399630f,  -0.916460f, 0.037237f,
	0.398390f,  -0.004517f, 0.999011f,  -0.044228f, -0.021584f, 0.999767f,  0.000265f,  -0.086245f,
	0.996274f,  0.000157f,  -0.240673f, 0.970606f,  -0.000608f, -0.540280f, 0.841484f,  -0.001597f,
	-0.877811f, 0.479008f,  0.000390f,  -0.999074f, 0.043021f,  0.000686f,  -0.004094f, 0.927919f,
	-0.372759f, -0.019687f, 0.949518f,  -0.313093f, -0.079023f, 0.945545f,  -0.315752f, -0.219600f,
	0.917458f,  -0.331734f, -0.488715f, 0.790534f,  -0.369071f, -0.797673f, 0.452036f,  -0.399226f,
	-0.916555f, 0.045675f,  -0.397293f, -0.002516f, 0.597699f,  -0.801716f, -0.012433f, 0.681272f,
	-0.731925f, -0.050950f, 0.677183f,  -0.734048f, -0.140298f, 0.648898f,  -0.747829f, -0.303501f,
	0.546934f,  -0.780224f, -0.495541f, 0.315794f,  -0.809143f, -0.586888f, 0.043544f,  -0.808497f,
	0.000557f,  -0.152599f, -0.988288f, 0.002074f,  -0.000969f, -0.999997f, 0.005499f,  -0.001410f,
	-0.999984f, 0.011569f,  0.000546f,  -0.999933f, 0.019331f,  0.010342f,  -0.999760f, 0.017294f,
	0.025347f,  -0.999529f, 0.002733f,  0.020710f,  -0.999782f, 0.002668f,  -0.756195f, -0.654340f,
	0.012416f,  -0.681586f, -0.731633f, 0.047946f,  -0.679845f, -0.731787f, 0.130533f,  -0.659594f,
	-0.740200f, 0.293034f,  -0.569168f, -0.768231f, 0.500213f,  -0.318883f, -0.805047f, 0.587808f,
	-0.026599f, -0.808563f, 0.003191f,  -0.967332f, -0.253494f, 0.014981f,  -0.949482f, -0.313464f,
	0.058954f,  -0.947784f, -0.313417f, 0.164056f,  -0.933187f, -0.319761f, 0.391212f,  -0.853217f,
	-0.344925f, 0.743675f,  -0.542841f, -0.390219f, 0.913602f,  -0.073956f, -0.399828f, 0.972925f,
	0.231121f,  -0.000918f, 0.912330f,  0.409438f,  -0.003849f, 0.828029f,  0.560649f,  -0.006408f,
	0.716807f,  0.697239f,  -0.006712f, 0.575989f,  0.817451f,  -0.003302f, 0.495133f,  0.867633f,
	-0.045350f, 0.893985f,  0.213142f,  0.394158f,  0.840605f,  0.383895f,  0.382108f,  0.768860f,
	0.531454f,  0.355543f,  0.672509f,  0.665677f,  0.323426f,  0.545610f,  0.779633f,  0.307380f,
	0.479303f,  0.843050f,  0.244000f,  0.576388f,  0.133958f,  0.806122f,  0.544470f,  0.253746f,
	0.799478f,  0.508754f,  0.364144f,  0.780108f,  0.461180f,  0.471780f,  0.751490f,  0.387281f,
	0.561166f,  0.731509f,  0.371347f,  0.666129f,  0.646818f,  0.002410f,  -0.014515f, 0.999892f,
	0.001301f,  -0.016411f, 0.999865f,  0.000720f,  -0.020201f, 0.999796f,  0.003256f,  -0.021359f,
	0.999767f,  0.008876f,  -0.013337f, 0.999872f,  0.072759f,  0.131709f,  0.988615f,  -0.569088f,
	-0.161451f, 0.806271f,  -0.524317f, -0.294841f, 0.798850f,  -0.472635f, -0.410610f, 0.779754f,
	-0.415783f, -0.508606f, 0.753953f,  -0.349674f, -0.579676f, 0.736006f,  -0.279208f, -0.530698f,
	0.800252f,  -0.885693f, -0.241406f, 0.396574f,  -0.803204f, -0.449996f, 0.390343f,  -0.697513f,
	-0.613444f, 0.370354f,  -0.588462f, -0.732277f, 0.342757f,  -0.485206f, -0.813008f, 0.321860f,
	-0.425879f, -0.823534f, 0.374725f,  -0.965787f, -0.259335f, 0.000592f,  -0.872611f, -0.488406f,
	0.003010f,  -0.748651f, -0.662945f, 0.005037f,  -0.622443f, -0.782648f, 0.005056f,  -0.509112f,
	-0.860697f, 0.002551f,  -0.455515f, -0.889038f, 0.046023f,  -0.888605f, -0.232245f, -0.395529f,
	-0.809378f, -0.443445f, -0.385051f, -0.704052f, -0.611598f, -0.360913f, -0.592713f, -0.733528f,
	-0.332607f, -0.486334f, -0.814293f, -0.316868f, -0.441890f, -0.860789f, -0.252538f, -0.574477f,
	-0.139332f, -0.806575f, -0.532235f, -0.275661f, -0.800460f, -0.480844f, -0.396171f, -0.782201f,
	-0.423172f, -0.499323f, -0.756044f, -0.355443f, -0.574187f, -0.737543f, -0.348424f, -0.670745f,
	-0.654753f, -0.001891f, 0.012937f,  -0.999915f, 0.001397f,  0.011921f,  -0.999928f, 0.005089f,
	0.014178f,  -0.999887f, 0.004896f,  0.016722f,  -0.999848f, -0.002003f, 0.012285f,  -0.999922f,
	-0.068183f, -0.130578f, -0.989091f, 0.573387f,  0.149188f,  -0.805587f, 0.541227f,  0.266714f,
	-0.797456f, 0.503525f,  0.377270f,  -0.777258f, 0.451452f,  0.484144f,  -0.749530f, 0.372386f,
	0.571022f,  -0.731616f, 0.289707f,  0.529053f,  -0.797604f, 0.892654f,  0.216131f,  -0.395546f,
	0.837234f,  0.384836f,  -0.388510f, 0.763231f,  0.531640f,  -0.367202f, 0.665469f,  0.666102f,
	-0.336837f, 0.537995f,  0.781974f,  -0.314766f, 0.455324f,  0.810920f,  -0.367545f, -0.145927f,
	0.987044f,  0.066705f,  -0.350253f, 0.936641f,  -0.005157f, -0.710995f, 0.703191f,  -0.003047f,
	-0.899400f, 0.437101f,  0.004678f,  -0.930238f, 0.366579f,  0.016656f,  -0.845840f, 0.533040f,
	0.020564f,  -0.646372f, 0.763018f,  0.002776f,  -0.128906f, 0.841567f,  0.524546f,  -0.292019f,
	0.852082f,  0.434375f,  -0.615355f, 0.675119f,  0.406882f,  -0.799678f, 0.453205f,  0.393853f,
	-0.814130f, 0.384381f,  0.435251f,  -0.711742f, 0.496654f,  0.496746f,  -0.538718f, 0.683956f,
	0.491922f,  -0.054328f, 0.445430f,  0.893667f,  -0.120328f, 0.535740f,  0.835765f,  -0.285367f,
	0.495269f,  0.820533f,  -0.427214f, 0.405516f,  0.808112f,  -0.455262f, 0.354182f,  0.816880f,
	-0.386518f, 0.375163f,  0.842530f,  -0.289150f, 0.468105f,  0.835027f,  0.075157f,  -0.092491f,
	0.992873f,  0.130249f,  0.040179f,  0.990667f,  0.205304f,  0.124938f,  0.970691f,  0.176764f,
	0.184322f,  0.966840f,  0.082193f,  0.182483f,  0.979767f,  0.009842f,  0.124532f,  0.992167f,
	-0.004171f, 0.105296f,  0.994432f,  0.213849f,  -0.587755f, 0.780264f,  0.361728f,  -0.447069f,
	0.818097f,  0.601635f,  -0.258541f, 0.755772f,  0.672221f,  -0.099063f, 0.733693f,  0.583247f,
	-0.084870f, 0.807849f,  0.409251f,  -0.235708f, 0.881451f,  0.284284f,  -0.385654f, 0.877755f,
	0.302637f,  -0.880762f, 0.364237f,  0.496428f,  -0.756105f, 0.426456f,  0.790450f,  -0.487110f,
	0.371365f,  0.895860f,  -0.277360f, 0.347141f,  0.865262f,  -0.295907f, 0.404673f,  0.690272f,
	-0.542643f, 0.478606f,  0.467747f,  -0.753579f, 0.461879f,  0.321563f,  -0.944505f, -0.067141f,
	0.531566f,  -0.847002f, 0.005046f,  0.833505f,  -0.552508f, 0.002163f,  0.944185f,  -0.329343f,
	-0.006880f, 0.932318f,  -0.361245f, -0.016874f, 0.768639f,  -0.639601f, -0.010215f, 0.513002f,
	-0.858387f, 0.000964f,  0.278331f,  -0.809595f, -0.516806f, 0.491568f,  -0.763636f, -0.418594f,
	0.788478f,  -0.493107f, -0.367624f, 0.891089f,  -0.275271f, -0.360815f, 0.856479f,  -0.282922f,
	-0.431739f, 0.692218f,  -0.527331f, -0.492704f, 0.473487f,  -0.749262f, -0.463052f, 0.166654f,
	-0.429938f, -0.887344f, 0.339768f,  -0.458348f, -0.821264f, 0.590160f,  -0.276240f, -0.758553f,
	0.668115f,  -0.103914f, -0.736766f, 0.590009f,  -0.076740f, -0.803741f, 0.433287f,  -0.219357f,
	-0.874154f, 0.299036f,  -0.368898f, -0.880052f, 0.027869f,  0.102187f,  -0.994375f, 0.088152f,
	0.031815f,  -0.995599f, 0.174456f,  0.096185f,  -0.979956f, 0.188708f,  0.161291f,  -0.968697f,
	0.127686f,  0.175774f,  -0.976115f, 0.054509f,  0.130986f,  -0.989885f, 0.015877f,  0.116730f,
	-0.993037f, -0.081072f, 0.607187f,  -0.790412f, -0.164116f, 0.522469f,  -0.836715f, -0.319626f,
	0.463405f,  -0.826495f, -0.422971f, 0.383450f,  -0.821013f, -0.424534f, 0.353597f,  -0.833511f,
	-0.351612f, 0.388106f,  -0.851905f, -0.270475f, 0.475063f,  -0.837352f, -0.133739f, 0.917541f,
	-0.374476f, -0.316043f, 0.839490f,  -0.442011f, -0.631181f, 0.656649f,  -0.412823f, -0.807405f,
	0.443017f,  -0.389658f, -0.821659f, 0.386229f,  -0.419171f, -0.707748f, 0.517393f,  -0.481037f,
	-0.526814f, 0.693790f,  -0.491043f, -0.461017f, 0.887371f,  -0.005987f, -0.290675f, 0.956710f,
	-0.014601f, 0.085518f,  0.995086f,  -0.049913f, 0.887713f,  0.456166f,  -0.062285f, 0.822992f,
	-0.567263f, 0.029937f,  0.659878f,  -0.743158f, 0.110798f,  -0.391094f, 0.831360f,  0.394824f,
	-0.253310f, 0.936825f,  0.241231f,  0.015366f,  0.995010f,  -0.098588f, 0.520185f,  0.549881f,
	-0.653482f, 0.628856f,  -0.382376f, -0.677000f, 0.578948f,  -0.646092f, -0.497378f, -0.223422f,
	0.660928f,  0.716420f,  -0.156131f, 0.874986f,  0.458282f,  -0.036467f, 0.998264f,  -0.046261f,
	0.156637f,  0.682491f,  -0.713913f, 0.263632f,  0.005571f,  -0.964607f, 0.312409f,  -0.324778f,
	-0.892704f, -0.001751f, 0.339383f,  0.940647f,  -0.021119f, 0.759902f,  0.649695f,  -0.044404f,
	0.998121f,  0.042219f,  -0.032529f, 0.802862f,  -0.595277f, -0.008745f, 0.371564f,  -0.928366f,
	0.042529f,  0.077913f,  -0.996053f, 0.280020f,  -0.238192f, 0.929975f,  0.227305f,  0.491486f,
	0.840699f,  -0.003105f, 0.987407f,  0.158172f,  -0.143918f, 0.895866f,  -0.420370f, -0.200177f,
	0.683872f,  -0.701604f, -0.187188f, 0.500198f,  -0.845437f, 0.453673f,  -0.746835f, 0.486229f,
	0.692158f,  -0.080062f, 0.717291f,  0.185758f,  0.942536f,  0.277704f,  -0.211188f, 0.955274f,
	-0.207004f, -0.312961f, 0.881061f,  -0.354665f, -0.336331f, 0.811345f,  -0.478122f, 0.482445f,
	-0.875816f, -0.013906f, 0.913013f,  -0.405572f, -0.043811f, 0.506909f,  0.853920f,  0.117742f,
	-0.234033f, 0.972124f,  0.014295f,  -0.348033f, 0.937468f,  0.005277f,  -0.384064f, 0.921073f,
	-0.064185f, 0.457762f,  -0.717668f, -0.524792f, 0.683347f,  -0.063014f, -0.727369f, 0.357361f,
	0.898186f,  -0.256038f, -0.207010f, 0.947863f,  0.242287f,  -0.314387f, 0.872357f,  0.374372f,
	-0.361040f, 0.872819f,  0.328385f,  0.280225f,  -0.218552f, -0.934724f, 0.261124f,  0.434074f,
	-0.862203f, 0.060553f,  0.978577f,  -0.196775f, -0.131809f, 0.881094f,  0.454203f,  -0.195016f,
	0.658858f,  0.726550f,  -0.247824f, 0.630359f,  0.735684f,  0.008860f,  0.321862f,  -0.946745f,
	0.001382f,  0.733189f,  -0.680023f, -0.012720f, 0.997949f,  -0.062734f, -0.011656f, 0.785221f,
	0.619106f,  0.000967f,  0.344022f,  0.938961f,  -0.037360f, 0.214324f,  0.976048f,  -0.213360f,
	0.648838f,  -0.730401f, -0.140052f, 0.865891f,  -0.480227f, -0.000809f, 0.999500f,  0.031611f,
	0.194529f,  0.659081f,  0.726478f,  0.266832f,  -0.005234f, 0.963729f,  0.219380f,  -0.217247f,
	0.951145f,  -0.384886f, 0.827121f,  -0.409553f, -0.240915f, 0.932642f,  -0.268588f, 0.065830f,
	0.996786f,  0.045658f,  0.597011f,  0.507703f,  0.621141f,  0.613004f,  -0.369418f, 0.698395f,
	0.486873f,  -0.566787f, 0.664610f,  0.000000f,  1.000000f,  0.000000f,  0.395791f,  0.918207f,
	0.015676f,  0.964544f,  0.263762f,  0.009177f,  0.839041f,  -0.544056f, -0.003654f, 0.788969f,
	-0.614430f, 0.001943f,  0.991025f,  -0.133647f, 0.002953f,  0.732531f,  0.680606f,  -0.013206f,
	0.377669f,  0.918491f,  0.117221f,  0.929557f,  0.263662f,  0.257694f,  0.811158f,  -0.544801f,
	0.212638f,  0.761156f,  -0.615195f, 0.205370f,  0.956515f,  -0.133833f, 0.259168f,  0.710689f,
	0.680955f,  0.176694f,  0.333696f,  0.918791f,  0.210878f,  0.830713f,  0.263784f,  0.490239f,
	0.727549f,  -0.545809f, 0.415650f,  0.681011f,  -0.616288f, 0.395491f,  0.856413f,  -0.134443f,
	0.498480f,  0.640176f,  0.681271f,  0.355027f,  0.267591f,  0.918878f,  0.289928f,  0.675416f,
	0.263955f,  0.688579f,  0.594970f,  -0.546203f, 0.589638f,  0.555330f,  -0.616730f, 0.557901f,
	0.698694f,  -0.134804f, 0.702606f,  0.526898f,  0.681345f,  0.508082f,  0.183499f,  0.918711f,
	0.349712f,  0.474031f,  0.264098f,  0.839969f,  0.422194f,  -0.545768f, 0.723802f,  0.392296f,
	-0.616276f, 0.682867f,  0.493598f,  -0.134679f, 0.859199f,  0.378184f,  0.681197f,  0.626856f,
	0.086498f,  0.918378f,  0.386136f,  0.239605f,  0.264096f,  0.934261f,  0.219887f,  -0.544743f,
	0.809262f,  0.201667f,  -0.615183f, 0.762155f,  0.253529f,  -0.134173f, 0.957977f,  0.202631f,
	0.680866f,  0.703820f,  -0.015676f, 0.918207f,  0.395791f,  -0.009177f, 0.263762f,  0.964544f,
	0.003654f,  -0.544057f, 0.839041f,  -0.001943f, -0.614430f, 0.788969f,  -0.002953f, -0.133647f,
	0.991025f,  0.013206f,  0.680606f,  0.732531f,  -0.117221f, 0.918491f,  0.377669f,  -0.257694f,
	0.263662f,  0.929557f,  -0.212638f, -0.544801f, 0.811158f,  -0.205370f, -0.615195f, 0.761156f,
	-0.259168f, -0.133833f, 0.956515f,  -0.176694f, 0.680955f,  0.710689f,  -0.210878f, 0.918791f,
	0.333696f,  -0.490239f, 0.263784f,  0.830713f,  -0.415650f, -0.545809f, 0.727549f,  -0.395491f,
	-0.616288f, 0.681011f,  -0.498480f, -0.134443f, 0.856413f,  -0.355027f, 0.681271f,  0.640176f,
	-0.289928f, 0.918878f,  0.267591f,  -0.688579f, 0.263955f,  0.675416f,  -0.589638f, -0.546203f,
	0.594970f,  -0.557901f, -0.616730f, 0.555330f,  -0.702606f, -0.134804f, 0.698694f,  -0.508082f,
	0.681345f,  0.526898f,  -0.349712f, 0.918711f,  0.183499f,  -0.839969f, 0.264098f,  0.474031f,
	-0.723802f, -0.545768f, 0.422194f,  -0.682867f, -0.616276f, 0.392296f,  -0.859199f, -0.134679f,
	0.493598f,  -0.626856f, 0.681197f,  0.378184f,  -0.386136f, 0.918378f,  0.086498f,  -0.934261f,
	0.264096f,  0.239605f,  -0.809262f, -0.544743f, 0.219887f,  -0.762155f, -0.615183f, 0.201667f,
	-0.957977f, -0.134173f, 0.253529f,  -0.703820f, 0.680866f,  0.202631f,  -0.395791f, 0.918207f,
	-0.015676f, -0.964544f, 0.263762f,  -0.009177f, -0.839041f, -0.544057f, 0.003654f,  -0.788969f,
	-0.614430f, -0.001943f, -0.991025f, -0.133647f, -0.002953f, -0.732531f, 0.680606f,  0.013206f,
	-0.377669f, 0.918491f,  -0.117221f, -0.929557f, 0.263662f,  -0.257694f, -0.811158f, -0.544801f,
	-0.212638f, -0.761156f, -0.615195f, -0.205370f, -0.956515f, -0.133833f, -0.259168f, -0.710689f,
	0.680955f,  -0.176694f, -0.333696f, 0.918791f,  -0.210878f, -0.830713f, 0.263784f,  -0.490239f,
	-0.727549f, -0.545809f, -0.415650f, -0.681011f, -0.616288f, -0.395491f, -0.856413f, -0.134443f,
	-0.498480f, -0.640176f, 0.681271f,  -0.355027f, -0.267591f, 0.918878f,  -0.289928f, -0.675416f,
	0.263955f,  -0.688579f, -0.594970f, -0.546203f, -0.589638f, -0.555330f, -0.616730f, -0.557901f,
	-0.698694f, -0.134804f, -0.702606f, -0.526898f, 0.681345f,  -0.508082f, -0.183499f, 0.918711f,
	-0.349712f, -0.474031f, 0.264098f,  -0.839969f, -0.422194f, -0.545768f, -0.723802f, -0.392296f,
	-0.616276f, -0.682867f, -0.493598f, -0.134679f, -0.859199f, -0.378184f, 0.681197f,  -0.626856f,
	-0.086498f, 0.918378f,  -0.386136f, -0.239605f, 0.264096f,  -0.934261f, -0.219887f, -0.544743f,
	-0.809262f, -0.201667f, -0.615183f, -0.762155f, -0.253529f, -0.134173f, -0.957977f, -0.202631f,
	0.680866f,  -0.703820f, 0.015676f,  0.918207f,  -0.395791f, 0.009177f,  0.263762f,  -0.964544f,
	-0.003654f, -0.544057f, -0.839041f, 0.001943f,  -0.614430f, -0.788969f, 0.002953f,  -0.133647f,
	-0.991025f, -0.013206f, 0.680606f,  -0.732531f, 0.117221f,  0.918491f,  -0.377669f, 0.257694f,
	0.263662f,  -0.929557f, 0.212638f,  -0.544801f, -0.811158f, 0.205370f,  -0.615195f, -0.761156f,
	0.259168f,  -0.133833f, -0.956515f, 0.176694f,  0.680955f,  -0.710689f, 0.210878f,  0.918791f,
	-0.333696f, 0.490239f,  0.263784f,  -0.830713f, 0.415650f,  -0.545809f, -0.727549f, 0.395491f,
	-0.616288f, -0.681011f, 0.498480f,  -0.134443f, -0.856413f, 0.355027f,  0.681271f,  -0.640176f,
	0.289928f,  0.918878f,  -0.267591f, 0.688579f,  0.263955f,  -0.675416f, 0.589638f,  -0.546203f,
	-0.594970f, 0.557901f,  -0.616730f, -0.555330f, 0.702606f,  -0.134804f, -0.698694f, 0.508082f,
	0.681345f,  -0.526898f, 0.349712f,  0.918711f,  -0.183499f, 0.839969f,  0.264098f,  -0.474031f,
	0.723802f,  -0.545768f, -0.422194f, 0.682867f,  -0.616276f, -0.392296f, 0.859199f,  -0.134679f,
	-0.493598f, 0.626856f,  0.681197f,  -0.378184f, 0.386136f,  0.918378f,  -0.086498f, 0.934261f,
	0.264096f,  -0.239605f, 0.809262f,  -0.544743f, -0.219887f, 0.762155f,  -0.615183f, -0.201667f,
	0.957977f,  -0.134173f, -0.253529f, 0.703820f,  0.680866f,  -0.202631f, 0.299763f,  0.954005f,
	-0.004004f, 0.180158f,  0.983637f,  -0.001176f, 0.158462f,  0.987365f,  0.000232f,  0.213709f,
	0.976895f,  0.002171f,  0.489301f,  0.872063f,  0.009504f,  0.686607f,  0.726410f,  -0.029990f,
	0.290238f,  0.954117f,  0.073644f,  0.174086f,  0.983681f,  0.045452f,  0.152777f,  0.987401f,
	0.041212f,  0.205547f,  0.976963f,  0.057393f,  0.469598f,  0.872357f,  0.135911f,  0.670656f,
	0.726754f,  0.148493f,  0.260698f,  0.954280f,  0.146242f,  0.156021f,  0.983742f,  0.088932f,
	0.136587f,  0.987448f,  0.079312f,  0.183282f,  0.977046f,  0.108577f,  0.417739f,  0.872696f,
	0.252776f,  0.608331f,  0.727460f,  0.317389f,  0.214008f,  0.954348f,  0.208377f,  0.127716f,
	0.983767f,  0.126063f,  0.111442f,  0.987466f,  0.111767f,  0.149005f,  0.977076f,  0.152056f,
	0.338347f,  0.872812f,  0.351738f,  0.505565f,  0.727811f,  0.463351f,  0.153158f,  0.954293f,
	0.256647f,  0.090962f,  0.983745f,  0.154830f,  0.078913f,  0.987448f,  0.136822f,  0.104831f,
	0.977040f,  0.185479f,  0.236319f,  0.872663f,  0.427333f,  0.369272f,  0.727651f,  0.578067f,
	0.081449f,  0.954136f,  0.288080f,  0.047744f,  0.983685f,  0.173450f,  0.040760f,  0.987400f,
	0.152903f,  0.053164f,  0.976955f,  0.206721f,  0.117360f,  0.872307f,  0.474665f,  0.207008f,
	0.727038f,  0.654648f,  0.004004f,  0.954005f,  0.299763f,  0.001176f,  0.983637f,  0.180158f,
	-0.000232f, 0.987365f,  0.158462f,  -0.002171f, 0.976895f,  0.213709f,  -0.009504f, 0.872063f,
	0.489301f,  0.029990f,  0.726410f,  0.686607f,  -0.073644f, 0.954117f,  0.290238f,  -0.045452f,
	0.983681f,  0.174086f,  -0.041212f, 0.987401f,  0.152777f,  -0.057393f, 0.976963f,  0.205547f,
	-0.135911f, 0.872357f,  0.469598f,  -0.148493f, 0.726754f,  0.670656f,  -0.146242f, 0.954280f,
	0.260698f,  -0.088932f, 0.983742f,  0.156021f,  -0.079312f, 0.987448f,  0.136587f,  -0.108577f,
	0.977046f,  0.183282f,  -0.252776f, 0.872696f,  0.417739f,  -0.317389f, 0.727460f,  0.608331f,
	-0.208377f, 0.954348f,  0.214008f,  -0.126063f, 0.983767f,  0.127716f,  -0.111767f, 0.987466f,
	0.111442f,  -0.152056f, 0.977076f,  0.149005f,  -0.351738f, 0.872812f,  0.338347f,  -0.463351f,
	0.727811f,  0.505565f,  -0.256647f, 0.954293f,  0.153158f,  -0.154830f, 0.983745f,  0.090962f,
	-0.136822f, 0.987448f,  0.078913f,  -0.185479f, 0.977040f,  0.104831f,  -0.427333f, 0.872663f,
	0.236319f,  -0.578067f, 0.727651f,  0.369272f,  -0.288080f, 0.954136f,  0.081449f,  -0.173450f,
	0.983685f,  0.047744f,  -0.152903f, 0.987400f,  0.040760f,  -0.206721f, 0.976955f,  0.053164f,
	-0.474665f, 0.872307f,  0.117360f,  -0.654648f, 0.727038f,  0.207008f,  -0.299763f, 0.954005f,
	0.004004f,  -0.180158f, 0.983637f,  0.001176f,  -0.158462f, 0.987365f,  -0.000232f, -0.213709f,
	0.976895f,  -0.002171f, -0.489301f, 0.872063f,  -0.009504f, -0.686607f, 0.726410f,  0.029990f,
	-0.290238f, 0.954117f,  -0.073644f, -0.174086f, 0.983681f,  -0.045452f, -0.152777f, 0.987401f,
	-0.041212f, -0.205547f, 0.976963f,  -0.057393f, -0.469598f, 0.872357f,  -0.135911f, -0.670656f,
	0.726754f,  -0.148493f, -0.260698f, 0.954280f,  -0.146242f, -0.156021f, 0.983742f,  -0.088932f,
	-0.136587f, 0.987448f,  -0.079312f, -0.183282f, 0.977046f,  -0.108577f, -0.417739f, 0.872696f,
	-0.252776f, -0.608331f, 0.727460f,  -0.317389f, -0.214008f, 0.954348f,  -0.208377f, -0.127716f,
	0.983767f,  -0.126063f, -0.111442f, 0.987466f,  -0.111767f, -0.149005f, 0.977076f,  -0.152056f,
	-0.338347f, 0.872812f,  -0.351738f, -0.505565f, 0.727811f,  -0.463351f, -0.153158f, 0.954293f,
	-0.256647f, -0.090962f, 0.983745f,  -0.154830f, -0.078913f, 0.987448f,  -0.136822f, -0.104831f,
	0.977040f,  -0.185479f, -0.236319f, 0.872663f,  -0.427333f, -0.369272f, 0.727651f,  -0.578067f,
	-0.081449f, 0.954136f,  -0.288080f, -0.047744f, 0.983685f,  -0.173450f, -0.040760f, 0.987400f,
	-0.152903f, -0.053164f, 0.976955f,  -0.206721f, -0.117360f, 0.872307f,  -0.474665f, -0.207008f,
	0.727038f,  -0.654648f, -0.004004f, 0.954005f,  -0.299763f, -0.001176f, 0.983637f,  -0.180158f,
	0.000232f,  0.987365f,  -0.158462f, 0.002171f,  0.976895f,  -0.213709f, 0.009504f,  0.872063f,
	-0.489301f, -0.029990f, 0.726410f,  -0.686607f, 0.073644f,  0.954117f,  -0.290238f, 0.045452f,
	0.983681f,  -0.174086f, 0.041212f,  0.987401f,  -0.152777f, 0.057393f,  0.976963f,  -0.205547f,
	0.135911f,  0.872357f,  -0.469598f, 0.148493f,  0.726754f,  -0.670656f, 0.146242f,  0.954280f,
	-0.260698f, 0.088932f,  0.983742f,  -0.156021f, 0.079312f,  0.987448f,  -0.136587f, 0.108577f,
	0.977046f,  -0.183282f, 0.252776f,  0.872696f,  -0.417739f, 0.317389f,  0.727460f,  -0.608331f,
	0.208377f,  0.954348f,  -0.214008f, 0.126063f,  0.983767f,  -0.127716f, 0.111767f,  0.987466f,
	-0.111442f, 0.152056f,  0.977076f,  -0.149005f, 0.351738f,  0.872812f,  -0.338347f, 0.463351f,
	0.727811f,  -0.505565f, 0.256647f,  0.954293f,  -0.153158f, 0.154830f,  0.983745f,  -0.090962f,
	0.136822f,  0.987448f,  -0.078913f, 0.185479f,  0.977040f,  -0.104831f, 0.427333f,  0.872663f,
	-0.236319f, 0.578067f,  0.727651f,  -0.369272f, 0.288080f,  0.954136f,  -0.081449f, 0.173450f,
	0.983685f,  -0.047744f, 0.152903f,  0.987400f,  -0.040760f, 0.206721f,  0.976955f,  -0.053164f,
	0.474665f,  0.872307f,  -0.117360f, 0.654648f,  0.727038f,  -0.207008f,
};

static std::uint32_t teapot_indices[NUMTEAPOTINDICES] = {
	0,	7,	8,	8,	1,	0,	1,	8,	9,	9,	2,	1,	2,	9,	10,   10,   3,
	2,	3,	10,   11,   11,   4,	3,	4,	11,   12,   12,   5,	4,	5,	12,   13,   13,
	6,	5,	7,	14,   15,   15,   8,	7,	8,	15,   16,   16,   9,	8,	9,	16,   17,
	17,   10,   9,	10,   17,   18,   18,   11,   10,   11,   18,   19,   19,   12,   11,   12,   19,
	20,   20,   13,   12,   14,   21,   22,   22,   15,   14,   15,   22,   23,   23,   16,   15,   16,
	23,   24,   24,   17,   16,   17,   24,   25,   25,   18,   17,   18,   25,   26,   26,   19,   18,
	19,   26,   27,   27,   20,   19,   21,   28,   29,   29,   22,   21,   22,   29,   30,   30,   23,
	22,   23,   30,   31,   31,   24,   23,   24,   31,   32,   32,   25,   24,   25,   32,   33,   33,
	26,   25,   26,   33,   34,   34,   27,   26,   28,   35,   36,   36,   29,   28,   29,   36,   37,
	37,   30,   29,   30,   37,   38,   38,   31,   30,   31,   38,   39,   39,   32,   31,   32,   39,
	40,   40,   33,   32,   33,   40,   41,   41,   34,   33,   35,   42,   43,   43,   36,   35,   36,
	43,   44,   44,   37,   36,   37,   44,   45,   45,   38,   37,   38,   45,   46,   46,   39,   38,
	39,   46,   47,   47,   40,   39,   40,   47,   48,   48,   41,   40,   42,   49,   50,   50,   43,
	42,   43,   50,   51,   51,   44,   43,   44,   51,   52,   52,   45,   44,   45,   52,   53,   53,
	46,   45,   46,   53,   54,   54,   47,   46,   47,   54,   55,   55,   48,   47,   49,   56,   57,
	57,   50,   49,   50,   57,   58,   58,   51,   50,   51,   58,   59,   59,   52,   51,   52,   59,
	60,   60,   53,   52,   53,   60,   61,   61,   54,   53,   54,   61,   62,   62,   55,   54,   56,
	63,   64,   64,   57,   56,   57,   64,   65,   65,   58,   57,   58,   65,   66,   66,   59,   58,
	59,   66,   67,   67,   60,   59,   60,   67,   68,   68,   61,   60,   61,   68,   69,   69,   62,
	61,   63,   70,   71,   71,   64,   63,   64,   71,   72,   72,   65,   64,   65,   72,   73,   73,
	66,   65,   66,   73,   74,   74,   67,   66,   67,   74,   75,   75,   68,   67,   68,   75,   76,
	76,   69,   68,   70,   77,   78,   78,   71,   70,   71,   78,   79,   79,   72,   71,   72,   79,
	80,   80,   73,   72,   73,   80,   81,   81,   74,   73,   74,   81,   82,   82,   75,   74,   75,
	82,   83,   83,   76,   75,   77,   84,   85,   85,   78,   77,   78,   85,   86,   86,   79,   78,
	79,   86,   87,   87,   80,   79,   80,   87,   88,   88,   81,   80,   81,   88,   89,   89,   82,
	81,   82,   89,   90,   90,   83,   82,   84,   91,   92,   92,   85,   84,   85,   92,   93,   93,
	86,   85,   86,   93,   94,   94,   87,   86,   87,   94,   95,   95,   88,   87,   88,   95,   96,
	96,   89,   88,   89,   96,   97,   97,   90,   89,   91,   98,   99,   99,   92,   91,   92,   99,
	100,  100,  93,   92,   93,   100,  101,  101,  94,   93,   94,   101,  102,  102,  95,   94,   95,
	102,  103,  103,  96,   95,   96,   103,  104,  104,  97,   96,   98,   105,  106,  106,  99,   98,
	99,   106,  107,  107,  100,  99,   100,  107,  108,  108,  101,  100,  101,  108,  109,  109,  102,
	101,  102,  109,  110,  110,  103,  102,  103,  110,  111,  111,  104,  103,  105,  112,  113,  113,
	106,  105,  106,  113,  114,  114,  107,  106,  107,  114,  115,  115,  108,  107,  108,  115,  116,
	116,  109,  108,  109,  116,  117,  117,  110,  109,  110,  117,  118,  118,  111,  110,  112,  119,
	120,  120,  113,  112,  113,  120,  121,  121,  114,  113,  114,  121,  122,  122,  115,  114,  115,
	122,  123,  123,  116,  115,  116,  123,  124,  124,  117,  116,  117,  124,  125,  125,  118,  117,
	119,  126,  127,  127,  120,  119,  120,  127,  128,  128,  121,  120,  121,  128,  129,  129,  122,
	121,  122,  129,  130,  130,  123,  122,  123,  130,  131,  131,  124,  123,  124,  131,  132,  132,
	125,  124,  126,  133,  134,  134,  127,  126,  127,  134,  135,  135,  128,  127,  128,  135,  136,
	136,  129,  128,  129,  136,  137,  137,  130,  129,  130,  137,  138,  138,  131,  130,  131,  138,
	139,  139,  132,  131,  133,  140,  141,  141,  134,  133,  134,  141,  142,  142,  135,  134,  135,
	142,  143,  143,  136,  135,  136,  143,  144,  144,  137,  136,  137,  144,  145,  145,  138,  137,
	138,  145,  146,  146,  139,  138,  140,  147,  148,  148,  141,  140,  141,  148,  149,  149,  142,
	141,  142,  149,  150,  150,  143,  142,  143,  150,  151,  151,  144,  143,  144,  151,  152,  152,
	145,  144,  145,  152,  153,  153,  146,  145,  147,  154,  155,  155,  148,  147,  148,  155,  156,
	156,  149,  148,  149,  156,  157,  157,  150,  149,  150,  157,  158,  158,  151,  150,  151,  158,
	159,  159,  152,  151,  152,  159,  160,  160,  153,  152,  154,  161,  162,  162,  155,  154,  155,
	162,  163,  163,  156,  155,  156,  163,  164,  164,  157,  156,  157,  164,  165,  165,  158,  157,
	158,  165,  166,  166,  159,  158,  159,  166,  167,  167,  160,  159,  161,  0,	1,	1,	162,
	161,  162,  1,	2,	2,	163,  162,  163,  2,	3,	3,	164,  163,  164,  3,	4,	4,
	165,  164,  165,  4,	5,	5,	166,  165,  166,  5,	6,	6,	167,  166,  6,	13,   174,
	174,  168,  6,	168,  174,  175,  175,  169,  168,  169,  175,  176,  176,  170,  169,  170,  176,
	177,  177,  171,  170,  171,  177,  178,  178,  172,  171,  172,  178,  179,  179,  173,  172,  13,
	20,   180,  180,  174,  13,   174,  180,  181,  181,  175,  174,  175,  181,  182,  182,  176,  175,
	176,  182,  183,  183,  177,  176,  177,  183,  184,  184,  178,  177,  178,  184,  185,  185,  179,
	178,  20,   27,   186,  186,  180,  20,   180,  186,  187,  187,  181,  180,  181,  187,  188,  188,
	182,  181,  182,  188,  189,  189,  183,  182,  183,  189,  190,  190,  184,  183,  184,  190,  191,
	191,  185,  184,  27,   34,   192,  192,  186,  27,   186,  192,  193,  193,  187,  186,  187,  193,
	194,  194,  188,  187,  188,  194,  195,  195,  189,  188,  189,  195,  196,  196,  190,  189,  190,
	196,  197,  197,  191,  190,  34,   41,   198,  198,  192,  34,   192,  198,  199,  199,  193,  192,
	193,  199,  200,  200,  194,  193,  194,  200,  201,  201,  195,  194,  195,  201,  202,  202,  196,
	195,  196,  202,  203,  203,  197,  196,  41,   48,   204,  204,  198,  41,   198,  204,  205,  205,
	199,  198,  199,  205,  206,  206,  200,  199,  200,  206,  207,  207,  201,  200,  201,  207,  208,
	208,  202,  201,  202,  208,  209,  209,  203,  202,  48,   55,   210,  210,  204,  48,   204,  210,
	211,  211,  205,  204,  205,  211,  212,  212,  206,  205,  206,  212,  213,  213,  207,  206,  207,
	213,  214,  214,  208,  207,  208,  214,  215,  215,  209,  208,  55,   62,   216,  216,  210,  55,
	210,  216,  217,  217,  211,  210,  211,  217,  218,  218,  212,  211,  212,  218,  219,  219,  213,
	212,  213,  219,  220,  220,  214,  213,  214,  220,  221,  221,  215,  214,  62,   69,   222,  222,
	216,  62,   216,  222,  223,  223,  217,  216,  217,  223,  224,  224,  218,  217,  218,  224,  225,
	225,  219,  218,  219,  225,  226,  226,  220,  219,  220,  226,  227,  227,  221,  220,  69,   76,
	228,  228,  222,  69,   222,  228,  229,  229,  223,  222,  223,  229,  230,  230,  224,  223,  224,
	230,  231,  231,  225,  224,  225,  231,  232,  232,  226,  225,  226,  232,  233,  233,  227,  226,
	76,   83,   234,  234,  228,  76,   228,  234,  235,  235,  229,  228,  229,  235,  236,  236,  230,
	229,  230,  236,  237,  237,  231,  230,  231,  237,  238,  238,  232,  231,  232,  238,  239,  239,
	233,  232,  83,   90,   240,  240,  234,  83,   234,  240,  241,  241,  235,  234,  235,  241,  242,
	242,  236,  235,  236,  242,  243,  243,  237,  236,  237,  243,  244,  244,  238,  237,  238,  244,
	245,  245,  239,  238,  90,   97,   246,  246,  240,  90,   240,  246,  247,  247,  241,  240,  241,
	247,  248,  248,  242,  241,  242,  248,  249,  249,  243,  242,  243,  249,  250,  250,  244,  243,
	244,  250,  251,  251,  245,  244,  97,   104,  252,  252,  246,  97,   246,  252,  253,  253,  247,
	246,  247,  253,  254,  254,  248,  247,  248,  254,  255,  255,  249,  248,  249,  255,  256,  256,
	250,  249,  250,  256,  257,  257,  251,  250,  104,  111,  258,  258,  252,  104,  252,  258,  259,
	259,  253,  252,  253,  259,  260,  260,  254,  253,  254,  260,  261,  261,  255,  254,  255,  261,
	262,  262,  256,  255,  256,  262,  263,  263,  257,  256,  111,  118,  264,  264,  258,  111,  258,
	264,  265,  265,  259,  258,  259,  265,  266,  266,  260,  259,  260,  266,  267,  267,  261,  260,
	261,  267,  268,  268,  262,  261,  262,  268,  269,  269,  263,  262,  118,  125,  270,  270,  264,
	118,  264,  270,  271,  271,  265,  264,  265,  271,  272,  272,  266,  265,  266,  272,  273,  273,
	267,  266,  267,  273,  274,  274,  268,  267,  268,  274,  275,  275,  269,  268,  125,  132,  276,
	276,  270,  125,  270,  276,  277,  277,  271,  270,  271,  277,  278,  278,  272,  271,  272,  278,
	279,  279,  273,  272,  273,  279,  280,  280,  274,  273,  274,  280,  281,  281,  275,  274,  132,
	139,  282,  282,  276,  132,  276,  282,  283,  283,  277,  276,  277,  283,  284,  284,  278,  277,
	278,  284,  285,  285,  279,  278,  279,  285,  286,  286,  280,  279,  280,  286,  287,  287,  281,
	280,  139,  146,  288,  288,  282,  139,  282,  288,  289,  289,  283,  282,  283,  289,  290,  290,
	284,  283,  284,  290,  291,  291,  285,  284,  285,  291,  292,  292,  286,  285,  286,  292,  293,
	293,  287,  286,  146,  153,  294,  294,  288,  146,  288,  294,  295,  295,  289,  288,  289,  295,
	296,  296,  290,  289,  290,  296,  297,  297,  291,  290,  291,  297,  298,  298,  292,  291,  292,
	298,  299,  299,  293,  292,  153,  160,  300,  300,  294,  153,  294,  300,  301,  301,  295,  294,
	295,  301,  302,  302,  296,  295,  296,  302,  303,  303,  297,  296,  297,  303,  304,  304,  298,
	297,  298,  304,  305,  305,  299,  298,  160,  167,  306,  306,  300,  160,  300,  306,  307,  307,
	301,  300,  301,  307,  308,  308,  302,  301,  302,  308,  309,  309,  303,  302,  303,  309,  310,
	310,  304,  303,  304,  310,  311,  311,  305,  304,  167,  6,	168,  168,  306,  167,  306,  168,
	169,  169,  307,  306,  307,  169,  170,  170,  308,  307,  308,  170,  171,  171,  309,  308,  309,
	171,  172,  172,  310,  309,  310,  172,  173,  173,  311,  310,  173,  179,  318,  318,  312,  173,
	312,  318,  319,  319,  313,  312,  313,  319,  320,  320,  314,  313,  314,  320,  321,  321,  315,
	314,  315,  321,  322,  322,  316,  315,  316,  322,  323,  323,  317,  316,  179,  185,  324,  324,
	318,  179,  318,  324,  325,  325,  319,  318,  319,  325,  326,  326,  320,  319,  320,  326,  327,
	327,  321,  320,  321,  327,  328,  328,  322,  321,  322,  328,  329,  329,  323,  322,  185,  191,
	330,  330,  324,  185,  324,  330,  331,  331,  325,  324,  325,  331,  332,  332,  326,  325,  326,
	332,  333,  333,  327,  326,  327,  333,  334,  334,  328,  327,  328,  334,  335,  335,  329,  328,
	191,  197,  336,  336,  330,  191,  330,  336,  337,  337,  331,  330,  331,  337,  338,  338,  332,
	331,  332,  338,  339,  339,  333,  332,  333,  339,  340,  340,  334,  333,  334,  340,  341,  341,
	335,  334,  197,  203,  342,  342,  336,  197,  336,  342,  343,  343,  337,  336,  337,  343,  344,
	344,  338,  337,  338,  344,  345,  345,  339,  338,  339,  345,  346,  346,  340,  339,  340,  346,
	347,  347,  341,  340,  203,  209,  348,  348,  342,  203,  342,  348,  349,  349,  343,  342,  343,
	349,  350,  350,  344,  343,  344,  350,  351,  351,  345,  344,  345,  351,  352,  352,  346,  345,
	346,  352,  353,  353,  347,  346,  209,  215,  354,  354,  348,  209,  348,  354,  355,  355,  349,
	348,  349,  355,  356,  356,  350,  349,  350,  356,  357,  357,  351,  350,  351,  357,  358,  358,
	352,  351,  352,  358,  359,  359,  353,  352,  215,  221,  360,  360,  354,  215,  354,  360,  361,
	361,  355,  354,  355,  361,  362,  362,  356,  355,  356,  362,  363,  363,  357,  356,  357,  363,
	364,  364,  358,  357,  358,  364,  365,  365,  359,  358,  221,  227,  366,  366,  360,  221,  360,
	366,  367,  367,  361,  360,  361,  367,  368,  368,  362,  361,  362,  368,  369,  369,  363,  362,
	363,  369,  370,  370,  364,  363,  364,  370,  371,  371,  365,  364,  227,  233,  372,  372,  366,
	227,  366,  372,  373,  373,  367,  366,  367,  373,  374,  374,  368,  367,  368,  374,  375,  375,
	369,  368,  369,  375,  376,  376,  370,  369,  370,  376,  377,  377,  371,  370,  233,  239,  378,
	378,  372,  233,  372,  378,  379,  379,  373,  372,  373,  379,  380,  380,  374,  373,  374,  380,
	381,  381,  375,  374,  375,  381,  382,  382,  376,  375,  376,  382,  383,  383,  377,  376,  239,
	245,  384,  384,  378,  239,  378,  384,  385,  385,  379,  378,  379,  385,  386,  386,  380,  379,
	380,  386,  387,  387,  381,  380,  381,  387,  388,  388,  382,  381,  382,  388,  389,  389,  383,
	382,  245,  251,  390,  390,  384,  245,  384,  390,  391,  391,  385,  384,  385,  391,  392,  392,
	386,  385,  386,  392,  393,  393,  387,  386,  387,  393,  394,  394,  388,  387,  388,  394,  395,
	395,  389,  388,  251,  257,  396,  396,  390,  251,  390,  396,  397,  397,  391,  390,  391,  397,
	398,  398,  392,  391,  392,  398,  399,  399,  393,  392,  393,  399,  400,  400,  394,  393,  394,
	400,  401,  401,  395,  394,  257,  263,  402,  402,  396,  257,  396,  402,  403,  403,  397,  396,
	397,  403,  404,  404,  398,  397,  398,  404,  405,  405,  399,  398,  399,  405,  406,  406,  400,
	399,  400,  406,  407,  407,  401,  400,  263,  269,  408,  408,  402,  263,  402,  408,  409,  409,
	403,  402,  403,  409,  410,  410,  404,  403,  404,  410,  411,  411,  405,  404,  405,  411,  412,
	412,  406,  405,  406,  412,  413,  413,  407,  406,  269,  275,  414,  414,  408,  269,  408,  414,
	415,  415,  409,  408,  409,  415,  416,  416,  410,  409,  410,  416,  417,  417,  411,  410,  411,
	417,  418,  418,  412,  411,  412,  418,  419,  419,  413,  412,  275,  281,  420,  420,  414,  275,
	414,  420,  421,  421,  415,  414,  415,  421,  422,  422,  416,  415,  416,  422,  423,  423,  417,
	416,  417,  423,  424,  424,  418,  417,  418,  424,  425,  425,  419,  418,  281,  287,  426,  426,
	420,  281,  420,  426,  427,  427,  421,  420,  421,  427,  428,  428,  422,  421,  422,  428,  429,
	429,  423,  422,  423,  429,  430,  430,  424,  423,  424,  430,  431,  431,  425,  424,  287,  293,
	432,  432,  426,  287,  426,  432,  433,  433,  427,  426,  427,  433,  434,  434,  428,  427,  428,
	434,  435,  435,  429,  428,  429,  435,  436,  436,  430,  429,  430,  436,  437,  437,  431,  430,
	293,  299,  438,  438,  432,  293,  432,  438,  439,  439,  433,  432,  433,  439,  440,  440,  434,
	433,  434,  440,  441,  441,  435,  434,  435,  441,  442,  442,  436,  435,  436,  442,  443,  443,
	437,  436,  299,  305,  444,  444,  438,  299,  438,  444,  445,  445,  439,  438,  439,  445,  446,
	446,  440,  439,  440,  446,  447,  447,  441,  440,  441,  447,  448,  448,  442,  441,  442,  448,
	449,  449,  443,  442,  305,  311,  450,  450,  444,  305,  444,  450,  451,  451,  445,  444,  445,
	451,  452,  452,  446,  445,  446,  452,  453,  453,  447,  446,  447,  453,  454,  454,  448,  447,
	448,  454,  455,  455,  449,  448,  311,  173,  312,  312,  450,  311,  450,  312,  313,  313,  451,
	450,  451,  313,  314,  314,  452,  451,  452,  314,  315,  315,  453,  452,  453,  315,  316,  316,
	454,  453,  454,  316,  317,  317,  455,  454,  317,  323,  462,  462,  456,  317,  456,  462,  463,
	463,  457,  456,  457,  463,  464,  464,  458,  457,  458,  464,  465,  465,  459,  458,  459,  465,
	466,  466,  460,  459,  460,  466,  461,  323,  329,  467,  467,  462,  323,  462,  467,  468,  468,
	463,  462,  463,  468,  469,  469,  464,  463,  464,  469,  470,  470,  465,  464,  465,  470,  471,
	471,  466,  465,  466,  471,  461,  329,  335,  472,  472,  467,  329,  467,  472,  473,  473,  468,
	467,  468,  473,  474,  474,  469,  468,  469,  474,  475,  475,  470,  469,  470,  475,  476,  476,
	471,  470,  471,  476,  461,  335,  341,  477,  477,  472,  335,  472,  477,  478,  478,  473,  472,
	473,  478,  479,  479,  474,  473,  474,  479,  480,  480,  475,  474,  475,  480,  481,  481,  476,
	475,  476,  481,  461,  341,  347,  482,  482,  477,  341,  477,  482,  483,  483,  478,  477,  478,
	483,  484,  484,  479,  478,  479,  484,  485,  485,  480,  479,  480,  485,  486,  486,  481,  480,
	481,  486,  461,  347,  353,  487,  487,  482,  347,  482,  487,  488,  488,  483,  482,  483,  488,
	489,  489,  484,  483,  484,  489,  490,  490,  485,  484,  485,  490,  491,  491,  486,  485,  486,
	491,  461,  353,  359,  492,  492,  487,  353,  487,  492,  493,  493,  488,  487,  488,  493,  494,
	494,  489,  488,  489,  494,  495,  495,  490,  489,  490,  495,  496,  496,  491,  490,  491,  496,
	461,  359,  365,  497,  497,  492,  359,  492,  497,  498,  498,  493,  492,  493,  498,  499,  499,
	494,  493,  494,  499,  500,  500,  495,  494,  495,  500,  501,  501,  496,  495,  496,  501,  461,
	365,  371,  502,  502,  497,  365,  497,  502,  503,  503,  498,  497,  498,  503,  504,  504,  499,
	498,  499,  504,  505,  505,  500,  499,  500,  505,  506,  506,  501,  500,  501,  506,  461,  371,
	377,  507,  507,  502,  371,  502,  507,  508,  508,  503,  502,  503,  508,  509,  509,  504,  503,
	504,  509,  510,  510,  505,  504,  505,  510,  511,  511,  506,  505,  506,  511,  461,  377,  383,
	512,  512,  507,  377,  507,  512,  513,  513,  508,  507,  508,  513,  514,  514,  509,  508,  509,
	514,  515,  515,  510,  509,  510,  515,  516,  516,  511,  510,  511,  516,  461,  383,  389,  517,
	517,  512,  383,  512,  517,  518,  518,  513,  512,  513,  518,  519,  519,  514,  513,  514,  519,
	520,  520,  515,  514,  515,  520,  521,  521,  516,  515,  516,  521,  461,  389,  395,  522,  522,
	517,  389,  517,  522,  523,  523,  518,  517,  518,  523,  524,  524,  519,  518,  519,  524,  525,
	525,  520,  519,  520,  525,  526,  526,  521,  520,  521,  526,  461,  395,  401,  527,  527,  522,
	395,  522,  527,  528,  528,  523,  522,  523,  528,  529,  529,  524,  523,  524,  529,  530,  530,
	525,  524,  525,  530,  531,  531,  526,  525,  526,  531,  461,  401,  407,  532,  532,  527,  401,
	527,  532,  533,  533,  528,  527,  528,  533,  534,  534,  529,  528,  529,  534,  535,  535,  530,
	529,  530,  535,  536,  536,  531,  530,  531,  536,  461,  407,  413,  537,  537,  532,  407,  532,
	537,  538,  538,  533,  532,  533,  538,  539,  539,  534,  533,  534,  539,  540,  540,  535,  534,
	535,  540,  541,  541,  536,  535,  536,  541,  461,  413,  419,  542,  542,  537,  413,  537,  542,
	543,  543,  538,  537,  538,  543,  544,  544,  539,  538,  539,  544,  545,  545,  540,  539,  540,
	545,  546,  546,  541,  540,  541,  546,  461,  419,  425,  547,  547,  542,  419,  542,  547,  548,
	548,  543,  542,  543,  548,  549,  549,  544,  543,  544,  549,  550,  550,  545,  544,  545,  550,
	551,  551,  546,  545,  546,  551,  461,  425,  431,  552,  552,  547,  425,  547,  552,  553,  553,
	548,  547,  548,  553,  554,  554,  549,  548,  549,  554,  555,  555,  550,  549,  550,  555,  556,
	556,  551,  550,  551,  556,  461,  431,  437,  557,  557,  552,  431,  552,  557,  558,  558,  553,
	552,  553,  558,  559,  559,  554,  553,  554,  559,  560,  560,  555,  554,  555,  560,  561,  561,
	556,  555,  556,  561,  461,  437,  443,  562,  562,  557,  437,  557,  562,  563,  563,  558,  557,
	558,  563,  564,  564,  559,  558,  559,  564,  565,  565,  560,  559,  560,  565,  566,  566,  561,
	560,  561,  566,  461,  443,  449,  567,  567,  562,  443,  562,  567,  568,  568,  563,  562,  563,
	568,  569,  569,  564,  563,  564,  569,  570,  570,  565,  564,  565,  570,  571,  571,  566,  565,
	566,  571,  461,  449,  455,  572,  572,  567,  449,  567,  572,  573,  573,  568,  567,  568,  573,
	574,  574,  569,  568,  569,  574,  575,  575,  570,  569,  570,  575,  576,  576,  571,  570,  571,
	576,  461,  455,  317,  456,  456,  572,  455,  572,  456,  457,  457,  573,  572,  573,  457,  458,
	458,  574,  573,  574,  458,  459,  459,  575,  574,  575,  459,  460,  460,  576,  575,  576,  460,
	461,  577,  584,  585,  585,  578,  577,  578,  585,  586,  586,  579,  578,  579,  586,  587,  587,
	580,  579,  580,  587,  588,  588,  581,  580,  581,  588,  589,  589,  582,  581,  582,  589,  590,
	590,  583,  582,  584,  591,  592,  592,  585,  584,  585,  592,  593,  593,  586,  585,  586,  593,
	594,  594,  587,  586,  587,  594,  595,  595,  588,  587,  588,  595,  596,  596,  589,  588,  589,
	596,  597,  597,  590,  589,  591,  598,  599,  599,  592,  591,  592,  599,  600,  600,  593,  592,
	593,  600,  601,  601,  594,  593,  594,  601,  602,  602,  595,  594,  595,  602,  603,  603,  596,
	595,  596,  603,  604,  604,  597,  596,  598,  605,  606,  606,  599,  598,  599,  606,  607,  607,
	600,  599,  600,  607,  608,  608,  601,  600,  601,  608,  609,  609,  602,  601,  602,  609,  610,
	610,  603,  602,  603,  610,  611,  611,  604,  603,  605,  612,  613,  613,  606,  605,  606,  613,
	614,  614,  607,  606,  607,  614,  615,  615,  608,  607,  608,  615,  616,  616,  609,  608,  609,
	616,  617,  617,  610,  609,  610,  617,  618,  618,  611,  610,  612,  619,  620,  620,  613,  612,
	613,  620,  621,  621,  614,  613,  614,  621,  622,  622,  615,  614,  615,  622,  623,  623,  616,
	615,  616,  623,  624,  624,  617,  616,  617,  624,  625,  625,  618,  617,  619,  626,  627,  627,
	620,  619,  620,  627,  628,  628,  621,  620,  621,  628,  629,  629,  622,  621,  622,  629,  630,
	630,  623,  622,  623,  630,  631,  631,  624,  623,  624,  631,  632,  632,  625,  624,  626,  633,
	634,  634,  627,  626,  627,  634,  635,  635,  628,  627,  628,  635,  636,  636,  629,  628,  629,
	636,  637,  637,  630,  629,  630,  637,  638,  638,  631,  630,  631,  638,  639,  639,  632,  631,
	633,  640,  641,  641,  634,  633,  634,  641,  642,  642,  635,  634,  635,  642,  643,  643,  636,
	635,  636,  643,  644,  644,  637,  636,  637,  644,  645,  645,  638,  637,  638,  645,  646,  646,
	639,  638,  640,  647,  648,  648,  641,  640,  641,  648,  649,  649,  642,  641,  642,  649,  650,
	650,  643,  642,  643,  650,  651,  651,  644,  643,  644,  651,  652,  652,  645,  644,  645,  652,
	653,  653,  646,  645,  647,  654,  655,  655,  648,  647,  648,  655,  656,  656,  649,  648,  649,
	656,  657,  657,  650,  649,  650,  657,  658,  658,  651,  650,  651,  658,  659,  659,  652,  651,
	652,  659,  660,  660,  653,  652,  654,  577,  578,  578,  655,  654,  655,  578,  579,  579,  656,
	655,  656,  579,  580,  580,  657,  656,  657,  580,  581,  581,  658,  657,  658,  581,  582,  582,
	659,  658,  659,  582,  583,  583,  660,  659,  583,  590,  667,  667,  661,  583,  661,  667,  668,
	668,  662,  661,  662,  668,  669,  669,  663,  662,  663,  669,  670,  670,  664,  663,  664,  670,
	671,  671,  665,  664,  665,  671,  672,  672,  666,  665,  590,  597,  673,  673,  667,  590,  667,
	673,  674,  674,  668,  667,  668,  674,  675,  675,  669,  668,  669,  675,  676,  676,  670,  669,
	670,  676,  677,  677,  671,  670,  671,  677,  678,  678,  672,  671,  597,  604,  679,  679,  673,
	597,  673,  679,  680,  680,  674,  673,  674,  680,  681,  681,  675,  674,  675,  681,  682,  682,
	676,  675,  676,  682,  683,  683,  677,  676,  677,  683,  684,  684,  678,  677,  604,  611,  685,
	685,  679,  604,  679,  685,  686,  686,  680,  679,  680,  686,  687,  687,  681,  680,  681,  687,
	688,  688,  682,  681,  682,  688,  689,  689,  683,  682,  683,  689,  690,  690,  684,  683,  611,
	618,  691,  691,  685,  611,  685,  691,  692,  692,  686,  685,  686,  692,  693,  693,  687,  686,
	687,  693,  694,  694,  688,  687,  688,  694,  695,  695,  689,  688,  689,  695,  696,  696,  690,
	689,  618,  625,  697,  697,  691,  618,  691,  697,  698,  698,  692,  691,  692,  698,  699,  699,
	693,  692,  693,  699,  700,  700,  694,  693,  694,  700,  701,  701,  695,  694,  695,  701,  702,
	702,  696,  695,  625,  632,  703,  703,  697,  625,  697,  703,  704,  704,  698,  697,  698,  704,
	705,  705,  699,  698,  699,  705,  706,  706,  700,  699,  700,  706,  707,  707,  701,  700,  701,
	707,  708,  708,  702,  701,  632,  639,  709,  709,  703,  632,  703,  709,  710,  710,  704,  703,
	704,  710,  711,  711,  705,  704,  705,  711,  712,  712,  706,  705,  706,  712,  713,  713,  707,
	706,  707,  713,  714,  714,  708,  707,  639,  646,  715,  715,  709,  639,  709,  715,  716,  716,
	710,  709,  710,  716,  717,  717,  711,  710,  711,  717,  718,  718,  712,  711,  712,  718,  719,
	719,  713,  712,  713,  719,  720,  720,  714,  713,  646,  653,  721,  721,  715,  646,  715,  721,
	722,  722,  716,  715,  716,  722,  723,  723,  717,  716,  717,  723,  724,  724,  718,  717,  718,
	724,  725,  725,  719,  718,  719,  725,  726,  726,  720,  719,  653,  660,  727,  727,  721,  653,
	721,  727,  728,  728,  722,  721,  722,  728,  729,  729,  723,  722,  723,  729,  730,  730,  724,
	723,  724,  730,  731,  731,  725,  724,  725,  731,  732,  732,  726,  725,  660,  583,  661,  661,
	727,  660,  727,  661,  662,  662,  728,  727,  728,  662,  663,  663,  729,  728,  729,  663,  664,
	664,  730,  729,  730,  664,  665,  665,  731,  730,  731,  665,  666,  666,  732,  731,  733,  740,
	741,  741,  734,  733,  734,  741,  742,  742,  735,  734,  735,  742,  743,  743,  736,  735,  736,
	743,  744,  744,  737,  736,  737,  744,  745,  745,  738,  737,  738,  745,  746,  746,  739,  738,
	740,  747,  748,  748,  741,  740,  741,  748,  749,  749,  742,  741,  742,  749,  750,  750,  743,
	742,  743,  750,  751,  751,  744,  743,  744,  751,  752,  752,  745,  744,  745,  752,  753,  753,
	746,  745,  747,  754,  755,  755,  748,  747,  748,  755,  756,  756,  749,  748,  749,  756,  757,
	757,  750,  749,  750,  757,  758,  758,  751,  750,  751,  758,  759,  759,  752,  751,  752,  759,
	760,  760,  753,  752,  754,  761,  762,  762,  755,  754,  755,  762,  763,  763,  756,  755,  756,
	763,  764,  764,  757,  756,  757,  764,  765,  765,  758,  757,  758,  765,  766,  766,  759,  758,
	759,  766,  767,  767,  760,  759,  761,  768,  769,  769,  762,  761,  762,  769,  770,  770,  763,
	762,  763,  770,  771,  771,  764,  763,  764,  771,  772,  772,  765,  764,  765,  772,  773,  773,
	766,  765,  766,  773,  774,  774,  767,  766,  768,  775,  776,  776,  769,  768,  769,  776,  777,
	777,  770,  769,  770,  777,  778,  778,  771,  770,  771,  778,  779,  779,  772,  771,  772,  779,
	780,  780,  773,  772,  773,  780,  781,  781,  774,  773,  775,  782,  783,  783,  776,  775,  776,
	783,  784,  784,  777,  776,  777,  784,  785,  785,  778,  777,  778,  785,  786,  786,  779,  778,
	779,  786,  787,  787,  780,  779,  780,  787,  788,  788,  781,  780,  782,  789,  790,  790,  783,
	782,  783,  790,  791,  791,  784,  783,  784,  791,  792,  792,  785,  784,  785,  792,  793,  793,
	786,  785,  786,  793,  794,  794,  787,  786,  787,  794,  795,  795,  788,  787,  789,  796,  797,
	797,  790,  789,  790,  797,  798,  798,  791,  790,  791,  798,  799,  799,  792,  791,  792,  799,
	800,  800,  793,  792,  793,  800,  801,  801,  794,  793,  794,  801,  802,  802,  795,  794,  796,
	803,  804,  804,  797,  796,  797,  804,  805,  805,  798,  797,  798,  805,  806,  806,  799,  798,
	799,  806,  807,  807,  800,  799,  800,  807,  808,  808,  801,  800,  801,  808,  809,  809,  802,
	801,  803,  810,  811,  811,  804,  803,  804,  811,  812,  812,  805,  804,  805,  812,  813,  813,
	806,  805,  806,  813,  814,  814,  807,  806,  807,  814,  815,  815,  808,  807,  808,  815,  816,
	816,  809,  808,  810,  733,  734,  734,  811,  810,  811,  734,  735,  735,  812,  811,  812,  735,
	736,  736,  813,  812,  813,  736,  737,  737,  814,  813,  814,  737,  738,  738,  815,  814,  815,
	738,  739,  739,  816,  815,  739,  746,  823,  823,  817,  739,  817,  823,  824,  824,  818,  817,
	818,  824,  825,  825,  819,  818,  819,  825,  826,  826,  820,  819,  820,  826,  827,  827,  821,
	820,  821,  827,  828,  828,  822,  821,  746,  753,  829,  829,  823,  746,  823,  829,  830,  830,
	824,  823,  824,  830,  831,  831,  825,  824,  825,  831,  832,  832,  826,  825,  826,  832,  833,
	833,  827,  826,  827,  833,  834,  834,  828,  827,  753,  760,  835,  835,  829,  753,  829,  835,
	836,  836,  830,  829,  830,  836,  837,  837,  831,  830,  831,  837,  838,  838,  832,  831,  832,
	838,  839,  839,  833,  832,  833,  839,  840,  840,  834,  833,  760,  767,  841,  841,  835,  760,
	835,  841,  842,  842,  836,  835,  836,  842,  843,  843,  837,  836,  837,  843,  844,  844,  838,
	837,  838,  844,  845,  845,  839,  838,  839,  845,  846,  846,  840,  839,  767,  774,  847,  847,
	841,  767,  841,  847,  848,  848,  842,  841,  842,  848,  849,  849,  843,  842,  843,  849,  850,
	850,  844,  843,  844,  850,  851,  851,  845,  844,  845,  851,  852,  852,  846,  845,  774,  781,
	853,  853,  847,  774,  847,  853,  854,  854,  848,  847,  848,  854,  855,  855,  849,  848,  849,
	855,  856,  856,  850,  849,  850,  856,  857,  857,  851,  850,  851,  857,  858,  858,  852,  851,
	781,  788,  859,  859,  853,  781,  853,  859,  860,  860,  854,  853,  854,  860,  861,  861,  855,
	854,  855,  861,  862,  862,  856,  855,  856,  862,  863,  863,  857,  856,  857,  863,  864,  864,
	858,  857,  788,  795,  865,  865,  859,  788,  859,  865,  866,  866,  860,  859,  860,  866,  867,
	867,  861,  860,  861,  867,  868,  868,  862,  861,  862,  868,  869,  869,  863,  862,  863,  869,
	870,  870,  864,  863,  795,  802,  871,  871,  865,  795,  865,  871,  872,  872,  866,  865,  866,
	872,  873,  873,  867,  866,  867,  873,  874,  874,  868,  867,  868,  874,  875,  875,  869,  868,
	869,  875,  876,  876,  870,  869,  802,  809,  877,  877,  871,  802,  871,  877,  878,  878,  872,
	871,  872,  878,  879,  879,  873,  872,  873,  879,  880,  880,  874,  873,  874,  880,  881,  881,
	875,  874,  875,  881,  882,  882,  876,  875,  809,  816,  883,  883,  877,  809,  877,  883,  884,
	884,  878,  877,  878,  884,  885,  885,  879,  878,  879,  885,  886,  886,  880,  879,  880,  886,
	887,  887,  881,  880,  881,  887,  888,  888,  882,  881,  816,  739,  817,  817,  883,  816,  883,
	817,  818,  818,  884,  883,  884,  818,  819,  819,  885,  884,  885,  819,  820,  820,  886,  885,
	886,  820,  821,  821,  887,  886,  887,  821,  822,  822,  888,  887,  896,  890,  889,  890,  896,
	897,  897,  891,  890,  891,  897,  898,  898,  892,  891,  892,  898,  899,  899,  893,  892,  893,
	899,  900,  900,  894,  893,  894,  900,  901,  901,  895,  894,  902,  896,  889,  896,  902,  903,
	903,  897,  896,  897,  903,  904,  904,  898,  897,  898,  904,  905,  905,  899,  898,  899,  905,
	906,  906,  900,  899,  900,  906,  907,  907,  901,  900,  908,  902,  889,  902,  908,  909,  909,
	903,  902,  903,  909,  910,  910,  904,  903,  904,  910,  911,  911,  905,  904,  905,  911,  912,
	912,  906,  905,  906,  912,  913,  913,  907,  906,  914,  908,  889,  908,  914,  915,  915,  909,
	908,  909,  915,  916,  916,  910,  909,  910,  916,  917,  917,  911,  910,  911,  917,  918,  918,
	912,  911,  912,  918,  919,  919,  913,  912,  920,  914,  889,  914,  920,  921,  921,  915,  914,
	915,  921,  922,  922,  916,  915,  916,  922,  923,  923,  917,  916,  917,  923,  924,  924,  918,
	917,  918,  924,  925,  925,  919,  918,  926,  920,  889,  920,  926,  927,  927,  921,  920,  921,
	927,  928,  928,  922,  921,  922,  928,  929,  929,  923,  922,  923,  929,  930,  930,  924,  923,
	924,  930,  931,  931,  925,  924,  932,  926,  889,  926,  932,  933,  933,  927,  926,  927,  933,
	934,  934,  928,  927,  928,  934,  935,  935,  929,  928,  929,  935,  936,  936,  930,  929,  930,
	936,  937,  937,  931,  930,  938,  932,  889,  932,  938,  939,  939,  933,  932,  933,  939,  940,
	940,  934,  933,  934,  940,  941,  941,  935,  934,  935,  941,  942,  942,  936,  935,  936,  942,
	943,  943,  937,  936,  944,  938,  889,  938,  944,  945,  945,  939,  938,  939,  945,  946,  946,
	940,  939,  940,  946,  947,  947,  941,  940,  941,  947,  948,  948,  942,  941,  942,  948,  949,
	949,  943,  942,  950,  944,  889,  944,  950,  951,  951,  945,  944,  945,  951,  952,  952,  946,
	945,  946,  952,  953,  953,  947,  946,  947,  953,  954,  954,  948,  947,  948,  954,  955,  955,
	949,  948,  956,  950,  889,  950,  956,  957,  957,  951,  950,  951,  957,  958,  958,  952,  951,
	952,  958,  959,  959,  953,  952,  953,  959,  960,  960,  954,  953,  954,  960,  961,  961,  955,
	954,  962,  956,  889,  956,  962,  963,  963,  957,  956,  957,  963,  964,  964,  958,  957,  958,
	964,  965,  965,  959,  958,  959,  965,  966,  966,  960,  959,  960,  966,  967,  967,  961,  960,
	968,  962,  889,  962,  968,  969,  969,  963,  962,  963,  969,  970,  970,  964,  963,  964,  970,
	971,  971,  965,  964,  965,  971,  972,  972,  966,  965,  966,  972,  973,  973,  967,  966,  974,
	968,  889,  968,  974,  975,  975,  969,  968,  969,  975,  976,  976,  970,  969,  970,  976,  977,
	977,  971,  970,  971,  977,  978,  978,  972,  971,  972,  978,  979,  979,  973,  972,  980,  974,
	889,  974,  980,  981,  981,  975,  974,  975,  981,  982,  982,  976,  975,  976,  982,  983,  983,
	977,  976,  977,  983,  984,  984,  978,  977,  978,  984,  985,  985,  979,  978,  986,  980,  889,
	980,  986,  987,  987,  981,  980,  981,  987,  988,  988,  982,  981,  982,  988,  989,  989,  983,
	982,  983,  989,  990,  990,  984,  983,  984,  990,  991,  991,  985,  984,  992,  986,  889,  986,
	992,  993,  993,  987,  986,  987,  993,  994,  994,  988,  987,  988,  994,  995,  995,  989,  988,
	989,  995,  996,  996,  990,  989,  990,  996,  997,  997,  991,  990,  998,  992,  889,  992,  998,
	999,  999,  993,  992,  993,  999,  1000, 1000, 994,  993,  994,  1000, 1001, 1001, 995,  994,  995,
	1001, 1002, 1002, 996,  995,  996,  1002, 1003, 1003, 997,  996,  1004, 998,  889,  998,  1004, 1005,
	1005, 999,  998,  999,  1005, 1006, 1006, 1000, 999,  1000, 1006, 1007, 1007, 1001, 1000, 1001, 1007,
	1008, 1008, 1002, 1001, 1002, 1008, 1009, 1009, 1003, 1002, 1010, 1004, 889,  1004, 1010, 1011, 1011,
	1005, 1004, 1005, 1011, 1012, 1012, 1006, 1005, 1006, 1012, 1013, 1013, 1007, 1006, 1007, 1013, 1014,
	1014, 1008, 1007, 1008, 1014, 1015, 1015, 1009, 1008, 1016, 1010, 889,  1010, 1016, 1017, 1017, 1011,
	1010, 1011, 1017, 1018, 1018, 1012, 1011, 1012, 1018, 1019, 1019, 1013, 1012, 1013, 1019, 1020, 1020,
	1014, 1013, 1014, 1020, 1021, 1021, 1015, 1014, 1022, 1016, 889,  1016, 1022, 1023, 1023, 1017, 1016,
	1017, 1023, 1024, 1024, 1018, 1017, 1018, 1024, 1025, 1025, 1019, 1018, 1019, 1025, 1026, 1026, 1020,
	1019, 1020, 1026, 1027, 1027, 1021, 1020, 1028, 1022, 889,  1022, 1028, 1029, 1029, 1023, 1022, 1023,
	1029, 1030, 1030, 1024, 1023, 1024, 1030, 1031, 1031, 1025, 1024, 1025, 1031, 1032, 1032, 1026, 1025,
	1026, 1032, 1033, 1033, 1027, 1026, 890,  1028, 889,  1028, 890,  891,  891,  1029, 1028, 1029, 891,
	892,  892,  1030, 1029, 1030, 892,  893,  893,  1031, 1030, 1031, 893,  894,  894,  1032, 1031, 1032,
	894,  895,  895,  1033, 1032, 895,  901,  1040, 1040, 1034, 895,  1034, 1040, 1041, 1041, 1035, 1034,
	1035, 1041, 1042, 1042, 1036, 1035, 1036, 1042, 1043, 1043, 1037, 1036, 1037, 1043, 1044, 1044, 1038,
	1037, 1038, 1044, 1045, 1045, 1039, 1038, 901,  907,  1046, 1046, 1040, 901,  1040, 1046, 1047, 1047,
	1041, 1040, 1041, 1047, 1048, 1048, 1042, 1041, 1042, 1048, 1049, 1049, 1043, 1042, 1043, 1049, 1050,
	1050, 1044, 1043, 1044, 1050, 1051, 1051, 1045, 1044, 907,  913,  1052, 1052, 1046, 907,  1046, 1052,
	1053, 1053, 1047, 1046, 1047, 1053, 1054, 1054, 1048, 1047, 1048, 1054, 1055, 1055, 1049, 1048, 1049,
	1055, 1056, 1056, 1050, 1049, 1050, 1056, 1057, 1057, 1051, 1050, 913,  919,  1058, 1058, 1052, 913,
	1052, 1058, 1059, 1059, 1053, 1052, 1053, 1059, 1060, 1060, 1054, 1053, 1054, 1060, 1061, 1061, 1055,
	1054, 1055, 1061, 1062, 1062, 1056, 1055, 1056, 1062, 1063, 1063, 1057, 1056, 919,  925,  1064, 1064,
	1058, 919,  1058, 1064, 1065, 1065, 1059, 1058, 1059, 1065, 1066, 1066, 1060, 1059, 1060, 1066, 1067,
	1067, 1061, 1060, 1061, 1067, 1068, 1068, 1062, 1061, 1062, 1068, 1069, 1069, 1063, 1062, 925,  931,
	1070, 1070, 1064, 925,  1064, 1070, 1071, 1071, 1065, 1064, 1065, 1071, 1072, 1072, 1066, 1065, 1066,
	1072, 1073, 1073, 1067, 1066, 1067, 1073, 1074, 1074, 1068, 1067, 1068, 1074, 1075, 1075, 1069, 1068,
	931,  937,  1076, 1076, 1070, 931,  1070, 1076, 1077, 1077, 1071, 1070, 1071, 1077, 1078, 1078, 1072,
	1071, 1072, 1078, 1079, 1079, 1073, 1072, 1073, 1079, 1080, 1080, 1074, 1073, 1074, 1080, 1081, 1081,
	1075, 1074, 937,  943,  1082, 1082, 1076, 937,  1076, 1082, 1083, 1083, 1077, 1076, 1077, 1083, 1084,
	1084, 1078, 1077, 1078, 1084, 1085, 1085, 1079, 1078, 1079, 1085, 1086, 1086, 1080, 1079, 1080, 1086,
	1087, 1087, 1081, 1080, 943,  949,  1088, 1088, 1082, 943,  1082, 1088, 1089, 1089, 1083, 1082, 1083,
	1089, 1090, 1090, 1084, 1083, 1084, 1090, 1091, 1091, 1085, 1084, 1085, 1091, 1092, 1092, 1086, 1085,
	1086, 1092, 1093, 1093, 1087, 1086, 949,  955,  1094, 1094, 1088, 949,  1088, 1094, 1095, 1095, 1089,
	1088, 1089, 1095, 1096, 1096, 1090, 1089, 1090, 1096, 1097, 1097, 1091, 1090, 1091, 1097, 1098, 1098,
	1092, 1091, 1092, 1098, 1099, 1099, 1093, 1092, 955,  961,  1100, 1100, 1094, 955,  1094, 1100, 1101,
	1101, 1095, 1094, 1095, 1101, 1102, 1102, 1096, 1095, 1096, 1102, 1103, 1103, 1097, 1096, 1097, 1103,
	1104, 1104, 1098, 1097, 1098, 1104, 1105, 1105, 1099, 1098, 961,  967,  1106, 1106, 1100, 961,  1100,
	1106, 1107, 1107, 1101, 1100, 1101, 1107, 1108, 1108, 1102, 1101, 1102, 1108, 1109, 1109, 1103, 1102,
	1103, 1109, 1110, 1110, 1104, 1103, 1104, 1110, 1111, 1111, 1105, 1104, 967,  973,  1112, 1112, 1106,
	967,  1106, 1112, 1113, 1113, 1107, 1106, 1107, 1113, 1114, 1114, 1108, 1107, 1108, 1114, 1115, 1115,
	1109, 1108, 1109, 1115, 1116, 1116, 1110, 1109, 1110, 1116, 1117, 1117, 1111, 1110, 973,  979,  1118,
	1118, 1112, 973,  1112, 1118, 1119, 1119, 1113, 1112, 1113, 1119, 1120, 1120, 1114, 1113, 1114, 1120,
	1121, 1121, 1115, 1114, 1115, 1121, 1122, 1122, 1116, 1115, 1116, 1122, 1123, 1123, 1117, 1116, 979,
	985,  1124, 1124, 1118, 979,  1118, 1124, 1125, 1125, 1119, 1118, 1119, 1125, 1126, 1126, 1120, 1119,
	1120, 1126, 1127, 1127, 1121, 1120, 1121, 1127, 1128, 1128, 1122, 1121, 1122, 1128, 1129, 1129, 1123,
	1122, 985,  991,  1130, 1130, 1124, 985,  1124, 1130, 1131, 1131, 1125, 1124, 1125, 1131, 1132, 1132,
	1126, 1125, 1126, 1132, 1133, 1133, 1127, 1126, 1127, 1133, 1134, 1134, 1128, 1127, 1128, 1134, 1135,
	1135, 1129, 1128, 991,  997,  1136, 1136, 1130, 991,  1130, 1136, 1137, 1137, 1131, 1130, 1131, 1137,
	1138, 1138, 1132, 1131, 1132, 1138, 1139, 1139, 1133, 1132, 1133, 1139, 1140, 1140, 1134, 1133, 1134,
	1140, 1141, 1141, 1135, 1134, 997,  1003, 1142, 1142, 1136, 997,  1136, 1142, 1143, 1143, 1137, 1136,
	1137, 1143, 1144, 1144, 1138, 1137, 1138, 1144, 1145, 1145, 1139, 1138, 1139, 1145, 1146, 1146, 1140,
	1139, 1140, 1146, 1147, 1147, 1141, 1140, 1003, 1009, 1148, 1148, 1142, 1003, 1142, 1148, 1149, 1149,
	1143, 1142, 1143, 1149, 1150, 1150, 1144, 1143, 1144, 1150, 1151, 1151, 1145, 1144, 1145, 1151, 1152,
	1152, 1146, 1145, 1146, 1152, 1153, 1153, 1147, 1146, 1009, 1015, 1154, 1154, 1148, 1009, 1148, 1154,
	1155, 1155, 1149, 1148, 1149, 1155, 1156, 1156, 1150, 1149, 1150, 1156, 1157, 1157, 1151, 1150, 1151,
	1157, 1158, 1158, 1152, 1151, 1152, 1158, 1159, 1159, 1153, 1152, 1015, 1021, 1160, 1160, 1154, 1015,
	1154, 1160, 1161, 1161, 1155, 1154, 1155, 1161, 1162, 1162, 1156, 1155, 1156, 1162, 1163, 1163, 1157,
	1156, 1157, 1163, 1164, 1164, 1158, 1157, 1158, 1164, 1165, 1165, 1159, 1158, 1021, 1027, 1166, 1166,
	1160, 1021, 1160, 1166, 1167, 1167, 1161, 1160, 1161, 1167, 1168, 1168, 1162, 1161, 1162, 1168, 1169,
	1169, 1163, 1162, 1163, 1169, 1170, 1170, 1164, 1163, 1164, 1170, 1171, 1171, 1165, 1164, 1027, 1033,
	1172, 1172, 1166, 1027, 1166, 1172, 1173, 1173, 1167, 1166, 1167, 1173, 1174, 1174, 1168, 1167, 1168,
	1174, 1175, 1175, 1169, 1168, 1169, 1175, 1176, 1176, 1170, 1169, 1170, 1176, 1177, 1177, 1171, 1170,
	1033, 895,  1034, 1034, 1172, 1033, 1172, 1034, 1035, 1035, 1173, 1172, 1173, 1035, 1036, 1036, 1174,
	1173, 1174, 1036, 1037, 1037, 1175, 1174, 1175, 1037, 1038, 1038, 1176, 1175, 1176, 1038, 1039, 1039,
	1177, 1176,
};

void triangle_mesh_tools::create_teapot(std::vector<math::vec3>& out_vertices,
										std::vector<std::uint32_t>& out_indices, bool y_up)
{
	out_vertices.resize(NUMTEAPOTVERTICES);
	out_indices.resize(NUMTEAPOTINDICES);

	for(int i = 0; i < NUMTEAPOTVERTICES; i++)
		out_vertices[i] = math::vec3(teapot_vertices_pos_only[i * 3 + 0], teapot_vertices_pos_only[i * 3 + 2],
									 teapot_vertices_pos_only[i * 3 + 1]);

	for(int i = 0; i < NUMTEAPOTINDICES; i += 3)
	{
		out_indices[i + 0] = teapot_indices[i + 0];
		out_indices[i + 1] = teapot_indices[i + 2];
		out_indices[i + 2] = teapot_indices[i + 1];
	}

	if(y_up)
		convert_to_y_up(out_vertices);
}
