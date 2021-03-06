#ifndef GRAPPLEMAP_RENDERING_HPP
#define GRAPPLEMAP_RENDERING_HPP

#include "math.hpp"
#include "util.hpp"
#include "viables.hpp"

#ifdef USE_FTGL
#include <FTGL/ftgl.h>
#endif

struct GLFWwindow;

namespace GrappleMap
{
	struct Camera;
	struct Graph;

	struct View
	{
		double x, y, w, h; // all in [0,1]
		optional<PlayerNum> first_person;
		double fov;
	};

	struct Style
	{
		V3 grid_color {.5, .5, .5};
		V3 background_color {0, 0, 0};
		unsigned grid_size = 2;
		unsigned grid_line_width = 2;

		#ifdef USE_FTGL
			FTGLPixmapFont font{"DejaVuSans.ttf"};
		#endif

		Style();
	};

	#ifdef USE_FTGL
	void renderText(FTGLPixmapFont const &, V2 where, string const &, V3 color);
	#endif

	void renderWindow(vector<View> const &,
		Viables const *, Graph const &, Position const &,
		Camera, optional<PlayerJoint> highlight_joint, bool edit_mode,
		int left, int bottom, int width, int height,
		SeqNum current_sequence,
		Style const &);

	inline vector<View> third_person_windows_in_corner(double w, double h, double hborder, double vborder)
	{
		return
			{ {0, 0, 1, 1, none, 50}
			, {1-w-hborder, vborder, w, h, optional<unsigned>(0), 80}
			, {hborder, vborder, w, h, optional<unsigned>(1), 80}
			};
	}
}

#endif
