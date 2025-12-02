# Semi‑Realtime Rasterizer Pipeline for STM32

A tiny, self‑contained software rasterizer for Cortex‑M4F microcontrollers with an FPU. 

---

## Overview
- **Self contained** — the renderer requires **no external headers**; drop the source into your project and compile.  
- **Target platform** — Cortex‑M4F with hardware FPU needed.

---

## Requirements
- **RAM**: **≥ 100 KB** of SRAM or PSRAM available at runtime.  
- **Display bus**: The LCD drivers are made for the Elegoo 2.8 in. TFT LCD. You can find a wiring guide in my operating system repository.
- **Triangle budget**: example loaders and models are kept modest — **≤ 100 triangles** per model to stay within memory limits.

---

## Features
- **Render resolution**: 120 × 120 pixels.  
- **Reserved area**: bottom 40 × 20 pixel grid intentionally left blank to conserve RAM.  
- **Tile system**: renders the screen in 4 tiles to avoid a full‑screen framebuffer; this trades a small amount of extra compute for a large memory saving.  
- **Rasterization**: uses barycentric coordinates for triangle rasterization — depth, color, normal, and other attribute interpolation are straightforward and always available.  
- **Per‑tile depth buffer**: correct occlusion without a full‑screen Z buffer.  
- **Raytracing helpers**: exposes simple data structures and utilities that can supplement a basic raytracer (vertex lists, triangle records, normals, basic vector ops.)

---

## Performance
- **Honestly fairly slow...** —  The screen's small bus coupled with the lack of SIMD with floats honestly makes this rasterizer slow for modern standards, but acceptable in the context of embedded

---

## Future Things I Want to do
- **Triangles in RAM now**; Planned migration to flash to reduce RAM pressure and allow larger models.
- **Phong Model**; This shading model is a lot nicer than the one I'm currently using(flat shading).
- **Incorporate a Raytracer**; I am currently in the process of adding raytraced shadows.


# DEMOS!!!


https://github.com/user-attachments/assets/8e711835-2d67-47a4-a9c1-9b1e0dfb6262

![unnamed](https://github.com/user-attachments/assets/717b9c16-f86c-4b62-ae0b-1c1269fce28d)
