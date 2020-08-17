/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm/gm.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkScalar.h"

namespace {
// Concave test
void test_concave(SkCanvas* canvas, const SkPaint& paint) {
    canvas->translate(0, 0);
    canvas->drawPath(SkPath::Polygon({{20,20}, {80,20}, {30,30}, {20,80}}, false), paint);
}

// Reverse concave test
void test_reverse_concave(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(100, 0);
    canvas->drawPath(SkPath::Polygon({{20,20}, {20,80}, {30,30}, {80,20}}, false), paint);
    canvas->restore();
}

// Bowtie (intersection)
void test_bowtie(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(200, 0);
    canvas->drawPath(SkPath::Polygon({{20,20}, {80,80}, {80,20}, {20,80}}, false), paint);
    canvas->restore();
}

// "fake" bowtie (concave, but no intersection)
void test_fake_bowtie(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(300, 0);
    canvas->drawPath(SkPath::Polygon({{20,20}, {50,40}, {80,20}, {80,80}, {50,60}, {20,80}},
                                     false), paint);
    canvas->restore();
}

// Bowtie with a smaller right hand lobe. The outer vertex of the left hand
// lobe intrudes into the interior of the right hand lobe.
void test_intruding_vertex(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(400, 0);
    canvas->drawPath(SkPath::Polygon({{20,20}, {50,50}, {68,20}, {68,80}, {50,50}, {20,80}},
                                     false, SkPathFillType::kWinding, true), paint);
    canvas->restore();
}

// A shape with an edge that becomes inverted on AA stroking and that also contains
// a repeated start/end vertex.
void test_inversion_repeat_vertex(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(400, 100);
    const SkPoint pts[] = {
        {80,50}, {40,80}, {60,20}, {20,20}, {39.99f,80}, {80,50},
    };
    canvas->drawPath(SkPath::Polygon(pts, SK_ARRAY_COUNT(pts), false,
                                     SkPathFillType::kWinding, true), paint);
    canvas->restore();
}

// Fish test (intersection/concave)
void test_fish(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(0, 100);
    canvas->drawPath(SkPath::Polygon({{20,20}, {80,80}, {70,50}, {80,20}, {20,80}, {0,50}}, false,
                                     SkPathFillType::kWinding, true), paint);
    canvas->restore();
}

// Overlapping "Fast-forward" icon: tests coincidence of inner and outer
// vertices generated by intersection.
void test_fast_forward(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(100, 100);
    auto path = SkPathBuilder().addPolygon({{20,20}, {60,50}, {20,80}}, false)
                               .addPolygon({{40,20}, {40,80}, {80,50}}, false)
                               .detach();
    canvas->drawPath(path, paint);
    canvas->restore();
}

// Square polygon with a square hole.
void test_hole(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(200, 100);
    auto path = SkPathBuilder().addPolygon({{20,20}, {80,20}, {80,80}, {20,80}}, false)
                               .addPolygon({{30,30}, {30,70}, {70,70}, {70,30}}, false)
                               .detach();
    canvas->drawPath(path, paint);
    canvas->restore();
}

// Star test (self-intersecting)
void test_star(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(300, 100);
    canvas->drawPath(SkPath().addPoly({{30,20}, {50,80}, {70,20}, {20,57}, {80,57}}, false),
                     paint);
    canvas->restore();
}

// Exercise a case where the intersection is below a bottom edge.
void test_twist(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(420, 220);
    canvas->scale(10, 10);
    const SkPoint pts[] = {
        {0.5f, 6},
        {5.8070392608642578125f, 6.4612660408020019531f},
        {-2.9186885356903076172f, 2.811046600341796875f},
        {0.49999994039535522461f, -1.4124038219451904297f},
    };
    canvas->drawPath(SkPath::Polygon(pts, SK_ARRAY_COUNT(pts), false), paint);
    canvas->restore();
}

// Stairstep with repeated vert (intersection)
void test_stairstep(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(0, 200);
    canvas->drawPath(SkPath::Polygon({{50,50}, {50,20}, {80,20}, {50,50}, {20,50}, {20,80}}, false),
                     paint);
    canvas->restore();
}

void test_stairstep2(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(100, 200);
    canvas->drawPath(SkPath::Polygon({{20,60}, {35,80}, {50,60}, {65,80}, {80,60}}, false), paint);
    canvas->restore();
}

// Overlapping segments
void test_overlapping(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(200, 200);
    canvas->drawPath(SkPath::Polygon({{20,80}, {80,80}, {80,20}, {80,30}}, false), paint);
    canvas->restore();
}

// Two "island" triangles inside a containing rect.
// This exercises the partnering code in the tessellator.
void test_partners(SkCanvas* canvas, const SkPaint& paint) {
    canvas->save();
    canvas->translate(300, 200);
    auto path = SkPathBuilder().addPolygon({{20,80}, {80,80}, {80,20}, {20,20}}, false)
                               .addPolygon({{30,30}, {45,50}, {30,70}}, false)
                               .addPolygon({{70,30}, {70,70}, {55,50}}, false)
                               .detach();
    canvas->drawPath(path, paint);
    canvas->restore();
}

// A split edge causes one half to be merged to zero winding (destroyed).
// Test that the other half of the split doesn't also get zero winding.
void test_winding_merged_to_zero(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(400, 350);
    path.moveTo(20, 80);
    path.moveTo(70,  -0.000001f);
    path.lineTo(70,   0.0);
    path.lineTo(60, -30.0);
    path.lineTo(40,  20.0);
    path.moveTo(50,  50.0);
    path.lineTo(50, -50.0);
    path.lineTo(10,  50.0);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Monotone test 1 (point in the middle)
void test_monotone_1(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(0, 300);
    path.moveTo(20, 20);
    path.quadTo(20, 50, 80, 50);
    path.quadTo(20, 50, 20, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Monotone test 2 (point at the top)
void test_monotone_2(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(100, 300);
    path.moveTo(20, 20);
    path.lineTo(80, 30);
    path.quadTo(20, 20, 20, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Monotone test 3 (point at the bottom)
void test_monotone_3(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(200, 300);
    path.moveTo(20, 80);
    path.lineTo(80, 70);
    path.quadTo(20, 80, 20, 20);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Monotone test 4 (merging of two monotones)
void test_monotone_4(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(300, 300);
    path.moveTo(80, 25);
    path.lineTo(50, 39);
    path.lineTo(20, 25);
    path.lineTo(40, 45);
    path.lineTo(70, 50);
    path.lineTo(80, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Monotone test 5 (aborted merging of two monotones)
void test_monotone_5(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(0, 400);
    path.moveTo(50, 20);
    path.lineTo(80, 80);
    path.lineTo(50, 50);
    path.lineTo(20, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Degenerate intersection test
void test_degenerate(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(100, 400);
    path.moveTo(50, 20);
    path.lineTo(70, 30);
    path.lineTo(20, 50);
    path.moveTo(50, 20);
    path.lineTo(80, 80);
    path.lineTo(50, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Two triangles with a coincident edge.
void test_coincident_edge(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(200, 400);

    path.moveTo(80, 20);
    path.lineTo(80, 80);
    path.lineTo(20, 80);

    path.moveTo(20, 20);
    path.lineTo(80, 80);
    path.lineTo(20, 80);

    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Bowtie with a coincident triangle (one triangle vertex coincident with the
// bowtie's intersection).
void test_bowtie_coincident_triangle(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(300, 400);
    path.moveTo(20, 20);
    path.lineTo(80, 80);
    path.lineTo(80, 20);
    path.lineTo(20, 80);
    path.moveTo(50, 50);
    path.lineTo(80, 20);
    path.lineTo(80, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Collinear outer boundary edges. In the edge-AA codepath, this creates an overlap region
// which contains a boundary edge. It can't be removed, but it must have the correct winding.
void test_collinear_outer_boundary_edge(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(400, 400);
    path.moveTo(20, 20);
    path.lineTo(20, 50);
    path.lineTo(50, 50);
    path.moveTo(80, 50);
    path.lineTo(50, 50);
    path.lineTo(80, 20);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

// Coincident edges (big ones first, coincident vert on top).
void test_coincident_edges_1(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(0, 500);
    path.moveTo(20, 20);
    path.lineTo(80, 80);
    path.lineTo(20, 80);
    path.moveTo(20, 20);
    path.lineTo(50, 50);
    path.lineTo(20, 50);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Coincident edges (small ones first, coincident vert on top).
void test_coincident_edges_2(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(100, 500);
    path.moveTo(20, 20);
    path.lineTo(50, 50);
    path.lineTo(20, 50);
    path.moveTo(20, 20);
    path.lineTo(80, 80);
    path.lineTo(20, 80);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Coincident edges (small ones first, coincident vert on bottom).
void test_coincident_edges_3(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(200, 500);
    path.moveTo(20, 80);
    path.lineTo(20, 50);
    path.lineTo(50, 50);
    path.moveTo(20, 80);
    path.lineTo(20, 20);
    path.lineTo(80, 20);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}
// Coincident edges (big ones first, coincident vert on bottom).
void test_coincident_edges_4(SkCanvas* canvas, const SkPaint& paint) {
    SkPathBuilder path;
    canvas->save();
    canvas->translate(300, 500);
    path.moveTo(20, 80);
    path.lineTo(20, 20);
    path.lineTo(80, 20);
    path.moveTo(20, 80);
    path.lineTo(20, 50);
    path.lineTo(50, 50);
    canvas->drawPath(path.detach(), paint);
    canvas->restore();
}

}  // namespace

DEF_SIMPLE_GM(concavepaths, canvas, 500, 600) {
    SkPaint paint;

    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);

    test_concave(canvas, paint);
    test_reverse_concave(canvas, paint);
    test_bowtie(canvas, paint);
    test_fake_bowtie(canvas, paint);
    test_intruding_vertex(canvas, paint);
    test_fish(canvas, paint);
    test_fast_forward(canvas, paint);
    test_hole(canvas, paint);
    test_star(canvas, paint);
    test_twist(canvas, paint);
    test_inversion_repeat_vertex(canvas, paint);
    test_stairstep(canvas, paint);
    test_stairstep2(canvas, paint);
    test_overlapping(canvas, paint);
    test_partners(canvas, paint);
    test_winding_merged_to_zero(canvas, paint);
    test_monotone_1(canvas, paint);
    test_monotone_2(canvas, paint);
    test_monotone_3(canvas, paint);
    test_monotone_4(canvas, paint);
    test_monotone_5(canvas, paint);
    test_degenerate(canvas, paint);
    test_coincident_edge(canvas, paint);
    test_bowtie_coincident_triangle(canvas, paint);
    test_collinear_outer_boundary_edge(canvas, paint);
    test_coincident_edges_1(canvas, paint);
    test_coincident_edges_2(canvas, paint);
    test_coincident_edges_3(canvas, paint);
    test_coincident_edges_4(canvas, paint);
}
