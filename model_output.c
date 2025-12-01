/**
 * Auto-generated C file from 3MF model data.
 * File: PolySphere_Dodecahedron.3mf
 */

#include "screenDriver.h"

void loadModel(uint16_t color) {
    triangle t;
    t.color = color;
    t.raytracedStrength = 0; // Default to 0 as requested

    // Triangle 0
    t.p1.x = -10.0f; t.p1.y = 0.0f; t.p1.z = -15.388417f;
    t.p2.x = 10.0f; t.p2.y = 0.0f; t.p2.z = -15.388417f;
    t.p3.x = -16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = -0.3568220763848094f; t.normal.y = -0.7946544867085036f; t.normal.z = -0.49112345958880615f;
    addTriangle(t);

    // Triangle 1
    t.p1.x = -16.18034f; t.p1.y = 0.0f; t.p1.z = 3.632712f;
    t.p2.x = 10.0f; t.p2.y = 0.0f; t.p2.z = -15.388417f;
    t.p3.x = 16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = -0.5773502660714492f; t.normal.y = -0.7946544786689065f; t.normal.z = 0.18759245666783964f;
    addTriangle(t);

    // Triangle 2
    t.p1.x = -16.18034f; t.p1.y = 0.0f; t.p1.z = 3.632712f;
    t.p2.x = 16.18034f; t.p2.y = 0.0f; t.p2.z = 3.632712f;
    t.p3.x = 0.0f; t.p3.y = 0.0f; t.p3.z = 15.388417f;
    t.normal.x = -0.5773502660714492f; t.normal.y = -0.7946544786689065f; t.normal.z = 0.18759245666783964f;
    addTriangle(t);

    // Triangle 3
    t.p1.x = 0.0f; t.p1.y = 17.013016f; t.p1.z = 25.90304f;
    t.p2.x = -16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = 0.0f; t.p3.y = 0.0f; t.p3.z = 15.388417f;
    t.normal.x = 0.0f; t.normal.y = -0.18759252160893639f; t.normal.z = 0.9822469373005959f;
    addTriangle(t);

    // Triangle 4
    t.p1.x = 0.0f; t.p1.y = 0.0f; t.p1.z = 15.388417f;
    t.p2.x = -16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = -16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = 8.731963365414788e-17f; t.normal.y = -0.7946544888917132f; t.normal.z = 0.6070619764770729f;
    addTriangle(t);

    // Triangle 5
    t.p1.x = -16.18034f; t.p1.y = 0.0f; t.p1.z = 3.632712f;
    t.p2.x = -16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = -26.18034f; t.p3.y = 17.013016f; t.p3.z = 6.881909f;
    t.normal.x = -0.5773502660714492f; t.normal.y = -0.7946544786689065f; t.normal.z = 0.18759245666783964f;
    addTriangle(t);

    // Triangle 6
    t.p1.x = 0.0f; t.p1.y = 17.013016f; t.p1.z = 25.90304f;
    t.p2.x = 16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = -16.18034f; t.p3.y = 27.527638f; t.p3.z = 20.64573f;
    t.normal.x = 0.0f; t.normal.y = -0.18759252160893639f; t.normal.z = 0.9822469373005959f;
    addTriangle(t);

    // Triangle 7
    t.p1.x = -16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = 16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = -10.0f; t.p3.y = 44.540652f; t.p3.z = 12.139221f;
    t.normal.x = -0.5773502711216867f; t.normal.y = 0.18759247776008167f; t.normal.z = 0.7946544700204914f;
    addTriangle(t);

    // Triangle 8
    t.p1.x = -10.0f; t.p1.y = 44.540652f; t.p1.z = 12.139221f;
    t.p2.x = 16.18034f; t.p2.y = 27.527638f; t.p2.z = 20.64573f;
    t.p3.x = 10.0f; t.p3.y = 44.540652f; t.p3.z = 12.139221f;
    t.normal.x = -0.3568220683338081f; t.normal.y = 0.7946545034739857f; t.normal.z = 0.49112343831107935f;
    addTriangle(t);

    // Triangle 9
    t.p1.x = 0.0f; t.p1.y = 17.013016f; t.p1.z = 25.90304f;
    t.p2.x = 0.0f; t.p2.y = 0.0f; t.p2.z = 15.388417f;
    t.p3.x = 16.18034f; t.p3.y = 27.527638f; t.p3.z = 20.64573f;
    t.normal.x = 0.0f; t.normal.y = -0.18759252160893639f; t.normal.z = 0.9822469373005959f;
    addTriangle(t);

    // Triangle 10
    t.p1.x = 16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = 0.0f; t.p2.y = 0.0f; t.p2.z = 15.388417f;
    t.p3.x = 16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = 0.5773502660481462f; t.normal.y = 0.187592476904633f; t.normal.z = 0.7946544739085782f;
    addTriangle(t);

    // Triangle 11
    t.p1.x = 16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = 16.18034f; t.p2.y = 0.0f; t.p2.z = 3.632712f;
    t.p3.x = 26.18034f; t.p3.y = 17.013016f; t.p3.z = 6.881909f;
    t.normal.x = 0.5773502660481462f; t.normal.y = 0.187592476904633f; t.normal.z = 0.7946544739085782f;
    addTriangle(t);

    // Triangle 12
    t.p1.x = 0.0f; t.p1.y = 44.540652f; t.p1.z = -18.637616f;
    t.p2.x = 16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = 0.0f; t.p3.y = 27.527638f; t.p3.z = -29.152236f;
    t.normal.x = 0.0f; t.normal.y = 0.7946544510216639f; t.normal.z = -0.6070620260496105f;
    addTriangle(t);

    // Triangle 13
    t.p1.x = 0.0f; t.p1.y = 27.527638f; t.p1.z = -29.152236f;
    t.p2.x = 16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = 16.18034f; t.p3.y = 17.013016f; t.p3.z = -23.894926f;
    t.normal.x = 0.0f; t.normal.y = 0.1875925140859897f; t.normal.z = -0.9822469387373512f;
    addTriangle(t);

    // Triangle 14
    t.p1.x = 16.18034f; t.p1.y = 17.013016f; t.p1.z = -23.894926f;
    t.p2.x = 16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = 26.18034f; t.p3.y = 27.527638f; t.p3.z = -10.131106f;
    t.normal.x = 0.577350261398401f; t.normal.y = -0.187592454144848f; t.normal.z = -0.7946544826596723f;
    addTriangle(t);

    // Triangle 15
    t.p1.x = 26.18034f; t.p1.y = 17.013016f; t.p1.z = 6.881909f;
    t.p2.x = 26.18034f; t.p2.y = 27.527638f; t.p2.z = -10.131106f;
    t.p3.x = 16.18034f; t.p3.y = 27.527638f; t.p3.z = 20.64573f;
    t.normal.x = 0.934172367632336f; t.normal.y = -0.18759248203396955f; t.normal.z = 0.3035309675083093f;
    addTriangle(t);

    // Triangle 16
    t.p1.x = 16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = 26.18034f; t.p2.y = 27.527638f; t.p2.z = -10.131106f;
    t.p3.x = 16.18034f; t.p3.y = 44.540652f; t.p3.z = -6.881909f;
    t.normal.x = 0.5773502660481462f; t.normal.y = 0.187592476904633f; t.normal.z = 0.7946544739085782f;
    addTriangle(t);

    // Triangle 17
    t.p1.x = 16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = 16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = 10.0f; t.p3.y = 44.540652f; t.p3.z = 12.139221f;
    t.normal.x = 0.5773502660481462f; t.normal.y = 0.187592476904633f; t.normal.z = 0.7946544739085782f;
    addTriangle(t);

    // Triangle 18
    t.p1.x = -10.0f; t.p1.y = 44.540652f; t.p1.z = 12.139221f;
    t.p2.x = 10.0f; t.p2.y = 44.540652f; t.p2.z = 12.139221f;
    t.p3.x = -16.18034f; t.p3.y = 44.540652f; t.p3.z = -6.881909f;
    t.normal.x = -0.3568220683338081f; t.normal.y = 0.7946545034739857f; t.normal.z = 0.49112343831107935f;
    addTriangle(t);

    // Triangle 19
    t.p1.x = -16.18034f; t.p1.y = 44.540652f; t.p1.z = -6.881909f;
    t.p2.x = 10.0f; t.p2.y = 44.540652f; t.p2.z = 12.139221f;
    t.p3.x = 16.18034f; t.p3.y = 44.540652f; t.p3.z = -6.881909f;
    t.normal.x = -0.5773502534093506f; t.normal.y = 0.7946544875490463f; t.normal.z = -0.18759245802089547f;
    addTriangle(t);

    // Triangle 20
    t.p1.x = -16.18034f; t.p1.y = 44.540652f; t.p1.z = -6.881909f;
    t.p2.x = 16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = 0.0f; t.p3.y = 44.540652f; t.p3.z = -18.637616f;
    t.normal.x = -0.5773502534093506f; t.normal.y = 0.7946544875490463f; t.normal.z = -0.18759245802089547f;
    addTriangle(t);

    // Triangle 21
    t.p1.x = 26.18034f; t.p1.y = 27.527638f; t.p1.z = -10.131106f;
    t.p2.x = 26.18034f; t.p2.y = 17.013016f; t.p2.z = 6.881909f;
    t.p3.x = 16.18034f; t.p3.y = 17.013016f; t.p3.z = -23.894926f;
    t.normal.x = 0.9341723548727545f; t.normal.y = 0.18759250332259778f; t.normal.z = -0.30353099362116825f;
    addTriangle(t);

    // Triangle 22
    t.p1.x = 16.18034f; t.p1.y = 17.013016f; t.p1.z = -23.894926f;
    t.p2.x = 26.18034f; t.p2.y = 17.013016f; t.p2.z = 6.881909f;
    t.p3.x = 16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = 0.577350261398401f; t.normal.y = -0.187592454144848f; t.normal.z = -0.7946544826596723f;
    addTriangle(t);

    // Triangle 23
    t.p1.x = 16.18034f; t.p1.y = 17.013016f; t.p1.z = -23.894926f;
    t.p2.x = 16.18034f; t.p2.y = 0.0f; t.p2.z = 3.632712f;
    t.p3.x = 10.0f; t.p3.y = 0.0f; t.p3.z = -15.388417f;
    t.normal.x = 0.577350261398401f; t.normal.y = -0.187592454144848f; t.normal.z = -0.7946544826596723f;
    addTriangle(t);

    // Triangle 24
    t.p1.x = 0.0f; t.p1.y = 27.527638f; t.p1.z = -29.152236f;
    t.p2.x = 16.18034f; t.p2.y = 17.013016f; t.p2.z = -23.894926f;
    t.p3.x = -16.18034f; t.p3.y = 17.013016f; t.p3.z = -23.894926f;
    t.normal.x = 0.0f; t.normal.y = 0.1875925140859897f; t.normal.z = -0.9822469387373512f;
    addTriangle(t);

    // Triangle 25
    t.p1.x = -16.18034f; t.p1.y = 17.013016f; t.p1.z = -23.894926f;
    t.p2.x = 16.18034f; t.p2.y = 17.013016f; t.p2.z = -23.894926f;
    t.p3.x = -10.0f; t.p3.y = 0.0f; t.p3.z = -15.388417f;
    t.normal.x = -0.5773502624552724f; t.normal.y = -0.18759245432304683f; t.normal.z = -0.794654481849743f;
    addTriangle(t);

    // Triangle 26
    t.p1.x = -10.0f; t.p1.y = 0.0f; t.p1.z = -15.388417f;
    t.p2.x = 16.18034f; t.p2.y = 17.013016f; t.p2.z = -23.894926f;
    t.p3.x = 10.0f; t.p3.y = 0.0f; t.p3.z = -15.388417f;
    t.normal.x = -0.3568220763848094f; t.normal.y = -0.7946544867085036f; t.normal.z = -0.49112345958880615f;
    addTriangle(t);

    // Triangle 27
    t.p1.x = -26.18034f; t.p1.y = 17.013016f; t.p1.z = 6.881909f;
    t.p2.x = -26.18034f; t.p2.y = 27.527638f; t.p2.z = -10.131106f;
    t.p3.x = -16.18034f; t.p3.y = 0.0f; t.p3.z = 3.632712f;
    t.normal.x = -0.9341723715645655f; t.normal.y = -0.1875924680150895f; t.normal.z = 0.30353096407029545f;
    addTriangle(t);

    // Triangle 28
    t.p1.x = -16.18034f; t.p1.y = 0.0f; t.p1.z = 3.632712f;
    t.p2.x = -26.18034f; t.p2.y = 27.527638f; t.p2.z = -10.131106f;
    t.p3.x = -16.18034f; t.p3.y = 17.013016f; t.p3.z = -23.894926f;
    t.normal.x = -0.5773502660714492f; t.normal.y = -0.7946544786689065f; t.normal.z = 0.18759245666783964f;
    addTriangle(t);

    // Triangle 29
    t.p1.x = -16.18034f; t.p1.y = 0.0f; t.p1.z = 3.632712f;
    t.p2.x = -16.18034f; t.p2.y = 17.013016f; t.p2.z = -23.894926f;
    t.p3.x = -10.0f; t.p3.y = 0.0f; t.p3.z = -15.388417f;
    t.normal.x = -0.5773502660714492f; t.normal.y = -0.7946544786689065f; t.normal.z = 0.18759245666783964f;
    addTriangle(t);

    // Triangle 30
    t.p1.x = 0.0f; t.p1.y = 44.540652f; t.p1.z = -18.637616f;
    t.p2.x = 0.0f; t.p2.y = 27.527638f; t.p2.z = -29.152236f;
    t.p3.x = -16.18034f; t.p3.y = 44.540652f; t.p3.z = -6.881909f;
    t.normal.x = 0.0f; t.normal.y = 0.7946544510216639f; t.normal.z = -0.6070620260496105f;
    addTriangle(t);

    // Triangle 31
    t.p1.x = -16.18034f; t.p1.y = 44.540652f; t.p1.z = -6.881909f;
    t.p2.x = 0.0f; t.p2.y = 27.527638f; t.p2.z = -29.152236f;
    t.p3.x = -16.18034f; t.p3.y = 17.013016f; t.p3.z = -23.894926f;
    t.normal.x = -0.5773502534093506f; t.normal.y = 0.7946544875490463f; t.normal.z = -0.18759245802089547f;
    addTriangle(t);

    // Triangle 32
    t.p1.x = -16.18034f; t.p1.y = 44.540652f; t.p1.z = -6.881909f;
    t.p2.x = -16.18034f; t.p2.y = 17.013016f; t.p2.z = -23.894926f;
    t.p3.x = -26.18034f; t.p3.y = 27.527638f; t.p3.z = -10.131106f;
    t.normal.x = -0.5773502534093506f; t.normal.y = 0.7946544875490463f; t.normal.z = -0.18759245802089547f;
    addTriangle(t);

    // Triangle 33
    t.p1.x = -10.0f; t.p1.y = 44.540652f; t.p1.z = 12.139221f;
    t.p2.x = -16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = -16.18034f; t.p3.y = 27.527638f; t.p3.z = 20.64573f;
    t.normal.x = -0.3568220683338081f; t.normal.y = 0.7946545034739857f; t.normal.z = 0.49112343831107935f;
    addTriangle(t);

    // Triangle 34
    t.p1.x = -16.18034f; t.p1.y = 27.527638f; t.p1.z = 20.64573f;
    t.p2.x = -16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = -26.18034f; t.p3.y = 17.013016f; t.p3.z = 6.881909f;
    t.normal.x = -0.5773502711216867f; t.normal.y = 0.18759247776008167f; t.normal.z = 0.7946544700204914f;
    addTriangle(t);

    // Triangle 35
    t.p1.x = -26.18034f; t.p1.y = 17.013016f; t.p1.z = 6.881909f;
    t.p2.x = -16.18034f; t.p2.y = 44.540652f; t.p2.z = -6.881909f;
    t.p3.x = -26.18034f; t.p3.y = 27.527638f; t.p3.z = -10.131106f;
    t.normal.x = -0.9341723715645655f; t.normal.y = -0.1875924680150895f; t.normal.z = 0.30353096407029545f;
    addTriangle(t);

}
