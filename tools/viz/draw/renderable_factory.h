#ifndef SPACE_VIZ_DRAW_RENDERABLE_FACTORY_H
#define SPACE_VIZ_DRAW_RENDERABLE_FACTORY_H

#include "draw.h"
#include "geom/line_segment.h"
#include "geom/sphere.h"
#include "renderable.h"
#include <vector>

namespace viz {
    namespace draw {
        Renderable::Ref CreateGrid2d(const Vec3 &start,
                                     const Vec3 &end,
                                     uint32_t divisions,
                                     uint32_t color);
        Renderable::Ref CreateAxes(float length, uint32_t color);

        template <class T>
        Renderable::Ref Create(const std::vector<T> &points, GLenum primitive, uint32_t color)
        {
            return std::make_shared<ExplicitRenderable>(
                Pipeline::Create("color", points), primitive, color);
        }

        Renderable::Ref Create(const LineSegment &line_segment, uint32_t color);
        Renderable::Ref Create(const Circle &circle, uint32_t color);
        Renderable::Ref Create(const space::geom::Sphere<Vec3> &sphere,
                               uint32_t color,
                               float tol = 1e-3f);
    }
}

#endif