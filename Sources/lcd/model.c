/**
 * Auto-generated C file from 3MF model data.
 * File: PolySphere_Dodecahedron.3mf
 */

#include "screenDriver.h"

/**
 * Auto-generated C file from 3MF model data.
 * File: PolySphere_Dodecahedron.3mf
 */

#include "screenDriver.h"

// Cube: center (0,0,200), side = 100 -> 12 triangles
void loadCube(const uint16_t color) {
    triangle t;
    t.color = color;
    t.raytracedStrength = 0;

    const float half = 100.0f;
    const float cx = 0.0f, cy = 200.0f, cz = 200.0f;

    // Back face (-Z)
    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy - half; t.p2.z = cz - half;
    t.p3.x = cx + half; t.p3.y = cy + half; t.p3.z = cz - half;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = -1.0f; addTriangle(t);

    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz - half;
    t.p3.x = cx - half; t.p3.y = cy + half; t.p3.z = cz - half;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = -1.0f; addTriangle(t);

    // Front face (+Z)
    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz + half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz + half;
    t.p3.x = cx + half; t.p3.y = cy - half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = 1.0f; addTriangle(t);

    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz + half;
    t.p2.x = cx - half; t.p2.y = cy + half; t.p2.z = cz + half;
    t.p3.x = cx + half; t.p3.y = cy + half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = 1.0f; addTriangle(t);

    // Bottom (-Y)
    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy - half; t.p2.z = cz - half;
    t.p3.x = cx + half; t.p3.y = cy - half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy - half; t.p2.z = cz + half;
    t.p3.x = cx - half; t.p3.y = cy - half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);

    // Top (+Y)
    t.p1.x = cx - half; t.p1.y = cy + half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz - half;
    t.p3.x = cx + half; t.p3.y = cy + half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = 1.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx - half; t.p1.y = cy + half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz + half;
    t.p3.x = cx - half; t.p3.y = cy + half; t.p3.z = cz + half;
    t.normal.x = 0.0f; t.normal.y = 1.0f; t.normal.z = 0.0f; addTriangle(t);

    // Left (-X)
    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx - half; t.p2.y = cy + half; t.p2.z = cz - half;
    t.p3.x = cx - half; t.p3.y = cy + half; t.p3.z = cz + half;
    t.normal.x = -1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx - half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx - half; t.p2.y = cy + half; t.p2.z = cz + half;
    t.p3.x = cx - half; t.p3.y = cy - half; t.p3.z = cz + half;
    t.normal.x = -1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    // Right (+X)
    t.p1.x = cx + half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz - half;
    t.p3.x = cx + half; t.p3.y = cy + half; t.p3.z = cz + half;
    t.normal.x = 1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx + half; t.p1.y = cy - half; t.p1.z = cz - half;
    t.p2.x = cx + half; t.p2.y = cy + half; t.p2.z = cz + half;
    t.p3.x = cx + half; t.p3.y = cy - half; t.p3.z = cz + half;
    t.normal.x = 1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);
}

// Pyramid: square base at y=120, apex at y=160, base centered at (0,120,200) -> 6 triangles
void loadPyramid(const uint16_t color) {
    triangle t;
    t.color = color;
    t.raytracedStrength = 0;

    const float baseHalf = 25.0f;
    const float bx = -75.0f, by = 100.0f, bz = 200.0f;
    const float apexY = -50.0f;

    // base (two triangles) pointing down
    t.p1.x = bx - baseHalf; t.p1.y = by; t.p1.z = bz - baseHalf;
    t.p2.x = bx + baseHalf; t.p2.y = by; t.p2.z = bz - baseHalf;
    t.p3.x = bx + baseHalf; t.p3.y = by; t.p3.z = bz + baseHalf;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = bx - baseHalf; t.p1.y = by; t.p1.z = bz - baseHalf;
    t.p2.x = bx + baseHalf; t.p2.y = by; t.p2.z = bz + baseHalf;
    t.p3.x = bx - baseHalf; t.p3.y = by; t.p3.z = bz + baseHalf;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);

    // four sides
    // front
    t.p1.x = bx - baseHalf; t.p1.y = by;        t.p1.z = bz - baseHalf;
    t.p2.x = bx + baseHalf; t.p2.y = by;        t.p2.z = bz - baseHalf;
    t.p3.x = bx;            t.p3.y = apexY;     t.p3.z = bz;
    t.normal.x = 0.0f; t.normal.y = 0.7071f; t.normal.z = -0.7071f; addTriangle(t);

    // right
    t.p1.x = bx + baseHalf; t.p1.y = by;        t.p1.z = bz - baseHalf;
    t.p2.x = bx + baseHalf; t.p2.y = by;        t.p2.z = bz + baseHalf;
    t.p3.x = bx;            t.p3.y = apexY;     t.p3.z = bz;
    t.normal.x = 0.7071f; t.normal.y = 0.7071f; t.normal.z = 0.0f; addTriangle(t);

    // back
    t.p1.x = bx + baseHalf; t.p1.y = by;        t.p1.z = bz + baseHalf;
    t.p2.x = bx - baseHalf; t.p2.y = by;        t.p2.z = bz + baseHalf;
    t.p3.x = bx;            t.p3.y = apexY;     t.p3.z = bz;
    t.normal.x = 0.0f; t.normal.y = 0.7071f; t.normal.z = 0.7071f; addTriangle(t);

    // left
    t.p1.x = bx - baseHalf; t.p1.y = by;        t.p1.z = bz + baseHalf;
    t.p2.x = bx - baseHalf; t.p2.y = by;        t.p2.z = bz - baseHalf;
    t.p3.x = bx;            t.p3.y = apexY;     t.p3.z = bz;
    t.normal.x = -0.7071f; t.normal.y = 0.7071f; t.normal.z = 0.0f; addTriangle(t);
}

// Column: thin rectangular prism at (90,0,220) -> 12 triangles
void loadColumn(const uint16_t color) {
    triangle t;
    t.color = color;
    t.raytracedStrength = 0;

    const float halfX = 20.0f, halfY = 100.0f, halfZ = 20.0f;
    const float cx = 90.0f, cy = 140.0f, cz = 140.0f;

    // Back (-Z)
    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx + halfX; t.p2.y = cy - halfY; t.p2.z = cz - halfZ;
    t.p3.x = cx + halfX; t.p3.y = cy + halfY; t.p3.z = cz - halfZ;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = -1.0f; addTriangle(t);

    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx + halfX; t.p2.y = cy + halfY; t.p2.z = cz - halfZ;
    t.p3.x = cx - halfX; t.p3.y = cy + halfY; t.p3.z = cz - halfZ;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = -1.0f; addTriangle(t);

    // Front (+Z)
    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz + halfZ;
    t.p2.x = cx + halfX; t.p2.y = cy + halfY; t.p2.z = cz + halfZ;
    t.p3.x = cx + halfX; t.p3.y = cy - halfY; t.p3.z = cz + halfZ;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = 1.0f; addTriangle(t);

    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz + halfZ;
    t.p2.x = cx - halfX; t.p2.y = cy + halfY; t.p2.z = cz + halfZ;
    t.p3.x = cx + halfX; t.p3.y = cy + halfY; t.p3.z = cz + halfZ;
    t.normal.x = 0.0f; t.normal.y = 0.0f; t.normal.z = 1.0f; addTriangle(t);

    // Left (-X)
    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx - halfX; t.p2.y = cy + halfY; t.p2.z = cz - halfZ;
    t.p3.x = cx - halfX; t.p3.y = cy + halfY; t.p3.z = cz + halfZ;
    t.normal.x = -1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx - halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx - halfX; t.p2.y = cy + halfY; t.p2.z = cz + halfZ;
    t.p3.x = cx - halfX; t.p3.y = cy - halfY; t.p3.z = cz + halfZ;
    t.normal.x = -1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    // Right (+X)
    t.p1.x = cx + halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx + halfX; t.p2.y = cy + halfY; t.p2.z = cz - halfZ;
    t.p3.x = cx + halfX; t.p3.y = cy + halfY; t.p3.z = cz + halfZ;
    t.normal.x = 1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = cx + halfX; t.p1.y = cy - halfY; t.p1.z = cz - halfZ;
    t.p2.x = cx + halfX; t.p2.y = cy + halfY; t.p2.z = cz + halfZ;
    t.p3.x = cx + halfX; t.p3.y = cy - halfY; t.p3.z = cz + halfZ;
    t.normal.x = 1.0f; t.normal.y = 0.0f; t.normal.z = 0.0f; addTriangle(t);
}

// Ground plane square centered at (0,-150,200), side = 400 -> 2 triangles
void loadGround(const uint16_t color) {
    triangle t;
    t.color = color;
    t.raytracedStrength = 0;

    const float half = 200.0f;
    const float gx = 0.0f, gy = 300.0f, gz = 200.0f;

    t.p1.x = gx - half; t.p1.y = gy; t.p1.z = gz - half;
    t.p2.x = gx + half; t.p2.y = gy; t.p2.z = gz - half;
    t.p3.x = gx + half; t.p3.y = gy; t.p3.z = gz + half;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);

    t.p1.x = gx - half; t.p1.y = gy; t.p1.z = gz - half;
    t.p2.x = gx + half; t.p2.y = gy; t.p2.z = gz + half;
    t.p3.x = gx - half; t.p3.y = gy; t.p3.z = gz + half;
    t.normal.x = 0.0f; t.normal.y = -1.0f; t.normal.z = 0.0f; addTriangle(t);
}
